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

#ifndef AOC24_CPP_SRC_DAY1_DAY1_H_
#define AOC24_CPP_SRC_DAY1_DAY1_H_

#include <filesystem>
#include <utility>
#include <vector>

#include "../utils.h"

namespace aoc24::day1 {

/**
 * @brief The path to the file containing the location lists.
 */
const std::filesystem::path kLocationListsFilePath{utils::kInputDir / "day1.txt"};

/**
 * @brief Reads location data from a file and returns two separate lists of integers.
 *
 * @param file_path The path to the file containing the location data.
 *                  It must point to a valid and readable file.
 * @return A pair of vectors containing two lists of integers:
 *         - The first vector represents the left list of locations.
 *         - The second vector represents the right list of locations.
 * @throws FileReadException If the file cannot be opened or read.
 * @throws ParseException If the file content cannot be successfully parsed.
 */
[[nodiscard]] std::pair<std::vector<int>, std::vector<int>> read_location_lists(
    const std::filesystem::path& file_path);

/**
 * @brief Calculate the distances between pairs of location IDs.
 *
 * Given a left and a right location list,
 * this function pairs up the smallest elements of each list and calculates their distance.
 * Then it pairs up the second-smallest elements of each list and calculates their distance,
 * and so on.
 * All the calculated distances are returned in a vector.
 *
 * @param left_list The left list of location IDs.
 * @param right_list The right list of location IDs.
 * @return The distances between each pair of location IDs.
 *
 * @remark
 * Note that this function requires ownership of the vector objects.
 * Use @c std::move if possible, or make a copy otherwise.
 */
[[nodiscard]] std::vector<int> calculate_distances(std::vector<int>&& left_list,
                                                   std::vector<int>&& right_list);

/**
 * @brief Calculates the similarity score between the two location lists.
 *
 * The similarity score is calculated as follows:
 * For each value in the left list, count how many times it appears in the right list.
 * Then multiply that frequency by the value of the number that was counted
 * and sum up all those numbers.
 * This value is the similarity score.
 *
 * @param left_list The left list of location IDs.
 * @param right_list The right list of location IDs.
 *
 * @remark
 * Note that this function requires ownership of the vector object representing the right list.
 * Use @c std::move if possible, or make a copy otherwise.
 */
[[nodiscard]] int calculate_similarity_score(const std::vector<int>& left_list,
                                             std::vector<int>&& right_list);

}  // namespace aoc24::day1

#endif  // AOC24_CPP_SRC_DAY1_DAY1_H_
