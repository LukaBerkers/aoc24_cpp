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

#include "day1.h"

#ifndef NDEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#else
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO
#endif

#include <spdlog/spdlog.h>

#include <algorithm>
#include <cstddef>
#include <filesystem>
#include <functional>
#include <iterator>
#include <lexy/action/parse.hpp>
#include <lexy/callback.hpp>
#include <lexy/dsl.hpp>
#include <lexy/input/string_input.hpp>
#include <lexy_ext/report_error.hpp>
#include <string>
#include <utility>
#include <vector>

#include "../utils.h"

namespace aoc24::day1 {

namespace {

namespace dsl = lexy::dsl;

struct LocationListsParser {
    static constexpr auto whitespace{dsl::ascii::blank};

    static constexpr auto rule{[] {
        constexpr auto line{dsl::integer<int> + dsl::integer<int>};
        constexpr auto sep{dsl::sep(dsl::ascii::newline)};
        return dsl::list(line, sep);
    }()};

    static constexpr auto value{lexy::fold_inplace<std::pair<std::vector<int>, std::vector<int>>>(
        std::make_pair(std::vector<int>{}, std::vector<int>{}),
        [](auto& pair, const int left_val, const int right_val) {
            pair.first.push_back(left_val);
            pair.second.push_back(right_val);
        })};
};

}  // namespace

[[nodiscard]] std::pair<std::vector<int>, std::vector<int>> parse_location_lists(
    const std::string& file_contents, const std::filesystem::path& file_path) {
    const auto input{lexy::string_input{file_contents}};
    std::string error_message{};

    const auto result{lexy::parse<LocationListsParser>(
        input,
        lexy_ext::report_error.path(file_path.c_str()).to(std::back_inserter(error_message)))};

    if (!result.has_value()) throw ParseException{error_message};
    if (!error_message.empty()) SPDLOG_ERROR(error_message);
    return result.value();
}

std::pair<std::vector<int>, std::vector<int>> read_location_lists(
    const std::filesystem::path& file_path) {
    const std::function file_parser{parse_location_lists};
    return utils::read_input_file(file_path, file_parser);
}

std::vector<int> calculate_distances(std::vector<int>&& left_list, std::vector<int>&& right_list) {
    // Sort the vectors.
    std::sort(left_list.begin(), left_list.end());
    std::sort(right_list.begin(), right_list.end());

    // Calculate the distances.
    std::vector<int> distances{};
    const std::size_t shortest_list_size{std::min(left_list.size(), right_list.size())};

    for (std::size_t i{}; i < shortest_list_size; ++i)
        distances.push_back(std::abs(left_list[i] - right_list[i]));

    // Return the distances.
    return distances;
}

int calculate_similarity_score(const std::vector<int>& left_list, std::vector<int>&& right_list) {
    // Sort the right list.
    std::sort(right_list.begin(), right_list.end());

    // Calculate the similarity score.
    std::ptrdiff_t similarity_score{0};

    for (const int left_val : left_list) {
        // Get the frequency of `left_val` in the right list.
        const auto [l, r] = std::equal_range(right_list.begin(), right_list.end(), left_val);
        const auto frequency{std::distance(l, r)};
        // Update the similarity score.
        similarity_score += left_val * frequency;
    }

    // Check if the value is in range of the return type.
    if (similarity_score < std::numeric_limits<int>::min() ||
        similarity_score > std::numeric_limits<int>::max())
        SPDLOG_ERROR("Similarity score is out of range. Calculated value: {}, returned value: {}",
                     similarity_score, static_cast<int>(similarity_score));

    // Return the similarity score.
    return static_cast<int>(similarity_score);
}

}  // namespace aoc24::day1
