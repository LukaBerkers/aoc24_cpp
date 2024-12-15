#ifndef AOC24_CPP_SRC_DAY1_DAY1_H_
#define AOC24_CPP_SRC_DAY1_DAY1_H_

#include <filesystem>
#include <utility>
#include <vector>

#include "../utils.h"

namespace aoc24::day1 {

const std::filesystem::path kLocationListsFilePath{utils::kInputDir / "test.txt"};

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

}  // namespace aoc24::day1

#endif  // AOC24_CPP_SRC_DAY1_DAY1_H_
