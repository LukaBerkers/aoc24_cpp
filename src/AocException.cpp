#include "AocException.h"

#include <filesystem>
#include <string>
#include <string_view>

namespace aoc24 {

constexpr std::string FileReadException::create_message(
    const std::filesystem::path& file_path, const std::string_view error_message) noexcept {
    return "Failed to open or read file: " + file_path.string() +
           ".\nError: " + std::string{error_message} + '.';
}

}  // namespace aoc24