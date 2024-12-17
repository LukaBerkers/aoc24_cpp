#ifndef AOC24_CPP_SRC_DAY2_REPORT_H_
#define AOC24_CPP_SRC_DAY2_REPORT_H_

#include <array>
#include <cstddef>

namespace aoc24::day2 {

class Report final {
  public:
    using Level = int;
    static constexpr std::size_t kLevelsPerReport{5};

  private:
    std::array<Level, kLevelsPerReport> levels_{};

  public:
    explicit Report(const std::array<Level, kLevelsPerReport>& levels) : levels_{levels} {}

    Report(const Level a, const Level b, const Level c, const Level d, const Level e)
        : levels_{a, b, c, d, e} {}

    [[nodiscard]] const std::array<Level, kLevelsPerReport>& levels() const { return levels_; }
};

}  // namespace aoc24::day2

#endif  // AOC24_CPP_SRC_DAY2_REPORT_H_
