#ifndef AOC24_CPP_SRC_UTILS_H_
#define AOC24_CPP_SRC_UTILS_H_

#include <cerrno>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <functional>
#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>

namespace aoc24::utils {

/**
 * The directory where the input files are stored.
 */
const std::filesystem::path kInputDir{"input"};

/**
 * Reads a file line by line and parses each line using the provided parser.
 *
 * @tparam T The type of the parsed output elements.
 * @param file_path The path to the file to be read.
 * @param line_parser A function to parse an individual line of the file to a type T.
 * @return A vector of parsed elements of type T.
 * @throw std::runtime_error If the file cannot be opened, an exception is thrown with a relevant
 * error message.
 */
template <typename T>
std::vector<T> read_input_lines(const std::filesystem::path& file_path,
                                const std::function<T(const std::string&)>& line_parser) {
    std::ifstream file{file_path};

    if (!file.is_open()) {
        const auto error_message{std::strerror(errno)};
        throw std::runtime_error{"Failed to open file: " + file_path.string() +
                                 ". Error: " + error_message};
    }

    std::vector<T> parsed_lines{};

    for (std::string line{}; std::getline(file, line);) {
        parsed_lines.push_back(line_parser(line));
    }

    return parsed_lines;
}

/**
 * Reads the content of a file and processes it using a provided parser function.
 *
 * @tparam T The type that the file's content will be converted to.
 * @param file_path The path to the file to be read.
 * @param file_parser A function that takes the file's content and converts it to type T.
 * @return The parsed content of the file.
 * @throws std::runtime_error If the file could not be opened, an exception is thrown with the
 * corresponding error message.
 */
template <typename T>
T read_input_file(const std::filesystem::path& file_path,
                  const std::function<T(const std::string&)>& file_parser) {
    const std::ifstream file{file_path};

    if (!file.is_open()) {
        const auto error_message{std::strerror(errno)};
        throw std::runtime_error{"Failed to open file: " + file_path.string() +
                                 ". Error: " + error_message};
    }

    std::ostringstream file_contents_stream{};
    file_contents_stream << file.rdbuf();
    return file_parser(file_contents_stream.str());
}

}  // namespace aoc24::utils

#endif  // AOC24_CPP_SRC_UTILS_H_
