// This file is part of my solutions for Advent of Code 2024.
// Copyright (C) 2024  Luka Berkers
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef NDEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#else
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO
#endif

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

    std::ptrdiff_t safe_reports_count{};

    try {
        safe_reports_count = day2::count_safe_reports_with_problem_dampener(reports);
    } catch (const OverflowException& error) {
        SPDLOG_CRITICAL(error.error_message());
        std::cout << error.user_message() << '\n';
        return ExitCode::parse_error;
    }

    std::cout << "There are " << safe_reports_count << " safe reports.\n";
    return ExitCode::success;
}

int main() {
    configure_logger();
    const auto exit_code{program()};
    return static_cast<int>(exit_code);
}
