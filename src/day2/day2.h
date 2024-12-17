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

[[nodiscard]] std::vector<Report> read_reactor_data(
    const std::filesystem::path& file_path = kReactorDataFilePath);

[[nodiscard]] std::ptrdiff_t count_safe_reports(const std::vector<Report>& reports);

}  // namespace aoc24::day2

#endif  // AOC24_CPP_SRC_DAY2_DAY2_H_
