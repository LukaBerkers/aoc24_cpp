#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <iostream>
#include <utility>
#include <vector>

#include "day1/day1.h"

using namespace aoc24;

enum class ExitCode : int {
    success = 0,
    file_read_error,
};

void configure_logger() {
    const auto logger{spdlog::stderr_color_st("main")};
    logger->set_level(spdlog::level::info);
    logger->set_pattern("%Y-%m-%d %T.%e%z [%^%l%$] %v");
    spdlog::set_default_logger(logger);
}

ExitCode program() {
    std::pair<std::vector<int>, std::vector<int>> location_lists{};

    try {
        location_lists = day1::read_location_lists(day1::kLocationListsFilePath);
    } catch (const FileReadException& error) {
        spdlog::critical(error.error_message());
        std::cout << error.user_message() << '\n';
        return ExitCode::file_read_error;
    }

    std::cout << "First list:\n";
    for (const int location : location_lists.first) std::cout << "  " << location << '\n';
    std::cout << "Second list:\n";
    for (const int location : location_lists.second) std::cout << "  " << location << '\n';
    return ExitCode::success;
}

int main() {
    configure_logger();
    const auto exit_code{program()};
    return static_cast<int>(exit_code);
}
