#ifndef AOC24_CPP_SRC_DAY2_REPORT_H_
#define AOC24_CPP_SRC_DAY2_REPORT_H_

#include <spdlog/formatter.h>

#include <cstddef>
#include <initializer_list>
#include <string>
#include <vector>

namespace aoc24::day2 {

/**
 * @brief Represents a report containing a collection of levels.
 */
class Report final {
  public:
    /**
     * @brief The type that represents each recorded level in a report.
     */
    using Level = int;

  private:
    std::vector<Level> levels_{};

  public:
    /**
     * @brief Constructs a Report object from a specified collection of levels.
     *
     * @param levels A vector of levels representing the data for the report.
     */
    explicit Report(const std::vector<Level>& levels) : levels_{levels} {}

    /**
     * @brief Constructs a Report object by moving a specified collection of levels.
     *
     * This constructor allows efficient transfer of a level collection
     * by taking ownership of the provided vector.
     *
     * @param levels An rvalue reference to a vector of levels representing the data
     *               for the report.
     */
    explicit Report(std::vector<Level>&& levels) : levels_{std::move(levels)} {}

    /**
     * @brief Constructs a Report object from an initializer list of levels.
     *
     * This constructor initializes the report
     * using the provided collection of levels given as an initializer list.
     *
     * @param levels An initializer list of levels representing the data for the report,
     *               used to populate the report.
     */
    Report(const std::initializer_list<Level> levels) : levels_{levels} {}

    /**
     * @brief Get the levels of the report.
     *
     * @return A constant reference to a vector containing the levels of the report.
     */
    [[nodiscard]] const std::vector<Level>& levels() const { return levels_; }
};

}  // namespace aoc24::day2

namespace fmt {

using namespace aoc24::day2;

/**
 * @brief Specialization of the @c formatter template for formatting @c Report objects.
 */
template <>
struct formatter<Report> : formatter<std::string> {
    /**
     * @brief Formats a @c Report object into a string for output.
     *
     * @param report The @c Report object to be formatted.
     * @param ctx The format context to which the formatted string is written.
     * @return An iterator pointing to the end of the formatted content in the context.
     */
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
