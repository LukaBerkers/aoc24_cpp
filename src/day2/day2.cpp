#include "day2.h"

#include <spdlog/spdlog.h>

#include <algorithm>
#include <cstddef>
#include <filesystem>
#include <lexy/action/parse.hpp>
#include <lexy/dsl.hpp>
#include <lexy/input/string_input.hpp>
#include <lexy_ext/report_error.hpp>
#include <string>
#include <vector>

#include "../AocException.h"
#include "Report.h"

namespace aoc24::day2 {

namespace {

namespace dsl = lexy::dsl;

struct ReportParser {
    static constexpr auto whitespace{dsl::ascii::blank};

    static constexpr auto level{dsl::integer<Report::Level>};

    static constexpr auto rule{dsl::times<Report::kLevelsPerReport>(level)};

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

[[nodiscard]] bool report_is_safe(const Report& report) {
    static_assert(Report::kLevelsPerReport >= 2);
    const auto levels{report.levels()};

    if (levels[0] > levels[1]) {
        for (std::size_t i{2}; i < Report::kLevelsPerReport; ++i) {
            const auto diff{levels[i - 1] - levels[i]};
            if (diff <= 0 || diff > 3) return false;
        }
    } else if (levels[0] < levels[1]) {
        for (std::size_t i{2}; i < Report::kLevelsPerReport; ++i) {
            const auto diff{levels[i] - levels[i - 1]};
            if (diff <= 0 || diff > 3) return false;
        }
    } else {
        return false;
    }

    return true;
}

std::ptrdiff_t count_safe_reports(const std::vector<Report>& reports) {
    return std::count_if(reports.begin(), reports.end(), report_is_safe);
}

}  // namespace aoc24::day2
