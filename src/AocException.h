#ifndef AOC24_CPP_SRC_AOC_EXCEPTION_H_
#define AOC24_CPP_SRC_AOC_EXCEPTION_H_

#include <cstring>
#include <exception>
#include <filesystem>
#include <string>
#include <string_view>

namespace aoc24 {

/**
 * @brief Base exception class for reporting errors in the application.
 */
class AocException : public std::exception {};

/**
 * @brief Exception class for errors occurring during file reading operations.
 *
 * This exception is thrown when a file cannot be opened or read successfully.
 * It provides a detailed error message,
 * including the file path and the corresponding error message.
 */
class FileReadException final : public AocException {
    const std::string full_message_{};

  public:
    /**
     * @brief Constructs a FileReadException from a file path and a system error number.
     *
     * @param file_path The path of the file that caused the error.
     * @param error_num The system error number corresponding to the file operation failure.
     */
    FileReadException(const std::filesystem::path& file_path, const int error_num) noexcept
        : full_message_{create_message(file_path, std::strerror(error_num))} {}

    /**
     * @brief Constructs a FileReadException from a file path and an error message.
     *
     * @param file_path The path of the file that caused the error.
     * @param error_message A message describing the cause of the error.
     */
    FileReadException(const std::filesystem::path& file_path,
                      const std::string_view error_message) noexcept
        : full_message_{create_message(file_path, error_message)} {}

    /**
     * @brief Returns a C-style string describing the error.
     *
     * @return A constant pointer to a null-terminated string containing the detailed error
     * message.
     */
    [[nodiscard]] const char* what() const noexcept override { return full_message_.c_str(); }

  private:
    [[nodiscard]] static constexpr std::string create_message(
        const std::filesystem::path& file_path, std::string_view error_message) noexcept;
};

/**
 * @brief Exception class for errors occurring during parsing operations.
 *
 * This exception is thrown when parsing input fails.
 * It provides a detailed error message describing the nature of the parsing failure.
 */
class ParseException final : public AocException {
    const std::string full_message_{};

  public:
    /**
     * @brief Constructs a ParseException from a detailed error message.
     *
     * @param error_message A message describing the cause of the parsing error.
     */
    explicit ParseException(const std::string_view error_message) noexcept
        : full_message_{create_message(error_message)} {}

    /**
     * @brief Returns a C-style string describing the error.
     *
     * @return A constant pointer to a null-terminated string containing the detailed error
     * message.
     */
    [[nodiscard]] const char* what() const noexcept override { return full_message_.c_str(); }

  private:
    [[nodiscard]] static constexpr std::string create_message(
        const std::string_view error_message) noexcept {
        return "Failed to parse input.\n\n" + std::string{error_message};
    }
};

}  // namespace aoc24

#endif  // AOC24_CPP_SRC_AOC_EXCEPTION_H_
