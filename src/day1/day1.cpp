#include "day1.h"

#include <filesystem>
#include <functional>
#include <iterator>
#include <lexy/action/parse.hpp>
#include <lexy/callback.hpp>
#include <lexy/dsl.hpp>
#include <lexy/input/string_input.hpp>
#include <lexy_ext/report_error.hpp>
#include <string>
#include <utility>
#include <vector>

#include "../utils.h"

namespace aoc24::day1 {

namespace {

namespace dsl = lexy::dsl;

struct LocationListsParser {
    static constexpr auto whitespace{dsl::ascii::blank};

    static constexpr auto rule{[] {
        constexpr auto line{dsl::integer<int> + dsl::integer<int>};
        constexpr auto sep{dsl::sep(dsl::ascii::newline)};
        return dsl::list(line, sep);
    }()};

    static constexpr auto value{lexy::fold_inplace<std::pair<std::vector<int>, std::vector<int>>>(
        std::make_pair(std::vector<int>{}, std::vector<int>{}),
        [](auto& pair, const int first_val, const int second_val) {
            pair.first.push_back(first_val);
            pair.second.push_back(second_val);
        })};
};

}  // namespace

[[nodiscard]] std::pair<std::vector<int>, std::vector<int>> parse_location_lists(
    const std::string& file_contents, const std::filesystem::path& file_path) {
    const auto input{lexy::string_input{file_contents}};
    std::string error_message{};

    const auto result{lexy::parse<LocationListsParser>(
        input,
        lexy_ext::report_error.path(file_path.c_str()).to(std::back_inserter(error_message)))};

    if (!result.has_value())
        throw std::runtime_error{"Failed to parse the input:\n" + error_message};

    return result.value();
}

std::pair<std::vector<int>, std::vector<int>> read_location_lists(
    const std::filesystem::path& file_path) {
    const std::function file_parser{parse_location_lists};
    return utils::read_input_file(file_path, file_parser);
}

}  // namespace aoc24::day1
