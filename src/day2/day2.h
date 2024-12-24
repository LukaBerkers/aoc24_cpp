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

#ifndef AOC24_CPP_SRC_DAY2_DAY2_H_
#define AOC24_CPP_SRC_DAY2_DAY2_H_

#include <cstddef>
#include <filesystem>
#include <vector>

#include "../utils.h"
#include "Report.h"

namespace aoc24::day2 {

/**
 * @brief The path to the file containing the reactor data.
 */
const std::filesystem::path kReactorDataFilePath{utils::kInputDir / "day2.txt"};

/**
 * @brief Reads and parses the reactor data from the specified source file.
 *
 * @param file_path The path to the file containing the reactor data.
 * @return A vector containing each report of reactor data.
 * @throws FileReadException If the file cannot be opened or read.
 * @throws ParseException If the file content cannot be successfully parsed.
 */
[[nodiscard]] std::vector<Report> read_reactor_data(
    const std::filesystem::path& file_path = kReactorDataFilePath);

/**
 * @brief Counts the number of safe reports in the given collection.
 *
 * @param reports A collection to analyze for safe reports.
 * @return The total count of safe reports in the provided data.
 */
[[nodiscard]] std::ptrdiff_t count_safe_reports(const std::vector<Report>& reports);

/**
 * @brief Counts safe reports when using the problem dampener.
 *
 * This function analyzes the provided reports to count the number of safe ones
 * when applying additional adjustments defined by the "problem dampener" mechanism.
 *
 * @param reports A collection of reports to evaluate.
 * @return The count of safe reports when using the problem dampener logic.
 * @throw OverflowException Possibly, when the collection is larger than
 *                          @c std::numeric_limits<std::ptrdiff_t>::max().
 */
[[nodiscard]] std::ptrdiff_t count_safe_reports_with_problem_dampener(
    const std::vector<Report>& reports);

}  // namespace aoc24::day2

#endif  // AOC24_CPP_SRC_DAY2_DAY2_H_
