#include "day2.h"

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO

#include <spdlog/spdlog.h>

#include <algorithm>
#include <cstddef>
#include <filesystem>
#include <lexy/action/parse.hpp>
#include <lexy/dsl.hpp>
#include <lexy/input/string_input.hpp>
#include <lexy_ext/report_error.hpp>
#include <limits>
#include <string>
#include <vector>

#include "../AocException.h"
#include "Report.h"

namespace aoc24::day2 {

namespace {

namespace dsl = lexy::dsl;

struct ReportParser {
    struct Levels {
        static constexpr auto level{dsl::integer<Report::Level>};

        static constexpr auto level_sep{dsl::sep(dsl::ascii::blank)};

        static constexpr auto rule{dsl::list(level, level_sep)};

        static constexpr auto value{lexy::as_list<std::vector<Report::Level>>};
    };

    static constexpr auto rule{dsl::p<Levels>};

    static constexpr auto value{lexy::construct<Report>};
};

}  // namespace

[[nodiscard]] Report parse_reactor_data_line(const std::string& line) {
    const auto input{lexy::string_input{line}};
    std::string error_message{};

    const auto result{lexy::parse<ReportParser>(
        input, lexy_ext::report_error.to(std::back_inserter(error_message)))};

    if (!result.has_value()) throw ParseException{error_message};
    // Report any non-fatal errors.
    if (!error_message.empty()) SPDLOG_ERROR(error_message);
    return result.value();
}

std::vector<Report> read_reactor_data(const std::filesystem::path& file_path) {
    const std::function line_parser{parse_reactor_data_line};
    return utils::read_input_lines(file_path, line_parser);
}

[[nodiscard]] std::size_t report_is_safe_until(const Report& report) {
    const auto& levels{report.levels()};
    const auto levels_count{levels.size()};
    if (levels_count < 2) return levels_count;

    if (levels[0] > levels[1]) {
        for (std::size_t i{1}; i < levels_count; ++i) {
            const auto diff{levels[i - 1] - levels[i]};
            if (diff < 1 || diff > 3) return i;
        }
    } else if (levels[0] < levels[1]) {
        for (std::size_t i{1}; i < levels_count; ++i) {
            const auto diff{levels[i] - levels[i - 1]};
            if (diff < 1 || diff > 3) return i;
        }
    } else {
        return 1;
    }

    return levels_count;
}

[[nodiscard]] bool report_is_safe(const Report& report) {
    return report_is_safe_until(report) == report.levels().size();
}

std::ptrdiff_t count_safe_reports(const std::vector<Report>& reports) {
    return std::count_if(reports.begin(), reports.end(), report_is_safe);
}

[[nodiscard]] bool report_is_safe_with_problem_dampener(const Report& report) {
    const auto problem_index_as_size_t{report_is_safe_until(report)};
    // Return true if the report is safe on its own.
    if (problem_index_as_size_t == report.levels().size()) return true;

    // Check the range and convert to std::ptrdiff_t.
    if (problem_index_as_size_t > std::numeric_limits<std::ptrdiff_t>::max())
        throw OverflowException{"Problem index is out of range. Index was: " +
                                std::to_string(problem_index_as_size_t)};

    const auto problem_index{static_cast<std::ptrdiff_t>(problem_index_as_size_t)};
    // Retry with the element before the problem index removed.
    auto dampened_report{report};
    auto& levels{dampened_report.levels()};
    levels.erase(levels.cbegin() + problem_index - 1);
    if (report_is_safe_until(dampened_report) == levels.size()) return true;
    // Retry with the element at the problem index removed.
    dampened_report = report;
    levels = dampened_report.levels();
    levels.erase(levels.cbegin() + problem_index);
    if (report_is_safe_until(dampened_report) == levels.size()) return true;

    // If the problem index is two, we also need to try with the first element removed.
    if (problem_index == 2) {
        dampened_report = report;
        levels = dampened_report.levels();
        levels.erase(levels.cbegin());
        if (report_is_safe_until(dampened_report) == levels.size()) return true;
    }

    return false;
}

std::ptrdiff_t count_safe_reports_with_problem_dampener(const std::vector<Report>& reports) {
    return std::count_if(reports.begin(), reports.end(), report_is_safe_with_problem_dampener);
}

}  // namespace aoc24::day2
