#ifndef AOC24_CPP_SRC_DAY1_DAY1_H_
#define AOC24_CPP_SRC_DAY1_DAY1_H_

#include <filesystem>
#include <utility>
#include <vector>

#include "../utils.h"

namespace aoc24::day1 {

const std::filesystem::path kLocationListsFilePath{utils::kInputDir / "test.txt"};

[[nodiscard]] std::pair<std::vector<int>, std::vector<int>> read_location_lists(
    const std::filesystem::path& file_path);

}  // namespace aoc24::day1

#endif  // AOC24_CPP_SRC_DAY1_DAY1_H_
