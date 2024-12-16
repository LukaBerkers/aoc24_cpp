#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

#include "day1/day1.h"

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
    std::pair<std::vector<int>, std::vector<int>> location_lists{};

    try {
        location_lists = day1::read_location_lists(day1::kLocationListsFilePath);
    } catch (const FileReadException& error) {
        SPDLOG_CRITICAL(error.error_message());
        std::cout << error.user_message() << '\n';
        return ExitCode::file_read_error;
    } catch (const ParseException& error) {
        SPDLOG_CRITICAL(error.error_message());
        std::cout << error.user_message() << '\n';
        return ExitCode::parse_error;
    }

    const auto similarity_score{
        day1::calculate_similarity_score(location_lists.first, std::move(location_lists.second))};
    std::cout << "Similarity score: " << similarity_score << '\n';
    return ExitCode::success;
}

int main() {
    configure_logger();
    const auto exit_code{program()};
    return static_cast<int>(exit_code);
}
