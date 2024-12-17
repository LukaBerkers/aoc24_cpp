#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <iostream>
#include <vector>

#include "AocException.h"
#include "day2/Report.h"
#include "day2/day2.h"

using namespace aoc24;

enum class ExitCode : int {
    success = 0,
    file_read_error,
    parse_error,
};

void configure_logger() {
    const auto logger{spdlog::stderr_color_st("main")};
    logger->set_level(spdlog::level::info);
    logger->set_pattern("%Y-%m-%d %T.%e%z [%^%l%$] %s:%# - %v");
    spdlog::set_default_logger(logger);
}

ExitCode program() {
    std::vector<day2::Report> reports{};

    try {
        reports = day2::read_reactor_data();
    } catch (const FileReadException& error) {
        SPDLOG_CRITICAL(error.error_message());
        std::cout << error.user_message() << '\n';
        return ExitCode::file_read_error;
    } catch (const ParseException& error) {
        SPDLOG_CRITICAL(error.error_message());
        std::cout << error.user_message() << '\n';
        return ExitCode::parse_error;
    }

    const auto safe_reports_count{day2::count_safe_reports(reports)};
    std::cout << "There are " << safe_reports_count << " safe reports.\n";
    return ExitCode::success;
}

int main() {
    configure_logger();
    const auto exit_code{program()};
    return static_cast<int>(exit_code);
}
