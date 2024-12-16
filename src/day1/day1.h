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

/**
 * @brief Calculate the distances between pairs of location IDs.
 *
 * Given a left and a right location list,
 * this function pairs up the smallest elements of each list and calculates their distance.
 * Then it pairs up the second-smallest elements of each list and calculates their distance,
 * and so on.
 * All the calculated distances are returned in a vector.
 *
 * @remark
 * Note that this function requires ownership of the vector objects.
 * Use @c std::move if possible, or make a copy.
 *
 * @param left_list The left list of location IDs.
 * @param right_list The right list of location IDs.
 * @return The distances between each pair of location IDs.
 */
[[nodiscard]] std::vector<int> calculate_distances(std::vector<int>&& left_list,
                                                   std::vector<int>&& right_list);

}  // namespace aoc24::day1

#endif  // AOC24_CPP_SRC_DAY1_DAY1_H_
