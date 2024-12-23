#ifndef AOC24_CPP_SRC_DAY2_REPORT_H_
#define AOC24_CPP_SRC_DAY2_REPORT_H_

#include <cstddef>
#include <initializer_list>
#include <string>
#include <vector>

namespace aoc24::day2 {

class Report final {
  public:
    using Level = int;

  private:
    std::vector<Level> levels_{};

  public:
    explicit Report(const std::vector<Level>& levels) : levels_{levels} {}

    explicit Report(std::vector<Level>&& levels) : levels_{std::move(levels)} {}

    Report(const std::initializer_list<Level> levels) : levels_{levels} {}

    [[nodiscard]] const std::vector<Level>& levels() const { return levels_; }
};

}  // namespace aoc24::day2

#endif  // AOC24_CPP_SRC_DAY2_REPORT_H_
