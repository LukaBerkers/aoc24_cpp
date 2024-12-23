#ifndef AOC24_CPP_SRC_DAY2_REPORT_H_
#define AOC24_CPP_SRC_DAY2_REPORT_H_

#include <spdlog/formatter.h>

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

namespace fmt {

using namespace aoc24::day2;

template <>
struct formatter<Report> : formatter<std::string> {
    format_context::iterator format(const Report& report, format_context& ctx) const {
        const auto& levels{report.levels()};
        std::string levels_str{'['};

        for (std::size_t i{0}; i < levels.size() - 1; ++i) {
            levels_str += std::to_string(levels[i]) + ", ";
        }

        levels_str += std::to_string(levels.back()) + ']';
        const std::string output{"Report { levels: " + levels_str + " }"};
        return formatter<std::string>::format(output, ctx);
    }
};

}  // namespace fmt

#endif  // AOC24_CPP_SRC_DAY2_REPORT_H_
