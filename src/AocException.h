// This file is part of my solutions for Advent of Code 2024.
// Copyright (C) 2024  Luka Berkers
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef AOC24_CPP_SRC_AOC_EXCEPTION_H_
#define AOC24_CPP_SRC_AOC_EXCEPTION_H_

#include <cstring>
#include <exception>
#include <filesystem>
#include <string>
#include <string_view>

namespace aoc24 {

/**
 * @brief Base class for exceptions thrown by this project.
 */
class AocException : public std::exception {
  public:
    /**
     * @brief Retrieves the detailed error message written for logging.
     * @return A string view representing the detailed error message.
     */
    [[nodiscard]] virtual std::string_view error_message() const = 0;

    /**
     * @brief Retrieves a user-friendly error message intended for displaying to end-users.
     * @return A string view containing the user-friendly error message.
     */
    [[nodiscard]] virtual std::string_view user_message() const = 0;

    /**
     * @brief Destructor for the AocException class.
     *
     * Ensures proper cleanup of resources
     * and allows derived exception classes to override destruction behavior safely.
     */
    ~AocException() noexcept override = default;
};

/**
 * @brief Exception class for file read errors.
 *
 * This exception is thrown when a file operation such as opening or reading a file fails.
 * It provides a detailed error message including the file path and the corresponding error reason.
 */
class FileReadException final : public AocException {
    const std::string message_{};

  public:
    /**
     * @brief Constructs a FileReadException from a file path and a system error number.
     *
     * Combines the file path and a descriptive error message generated from the system error
     * number to create a detailed exception message.
     *
     * @param file_path The path of the file that caused the error.
     * @param error_num The system error number corresponding to the file operation failure.
     */
    FileReadException(const std::filesystem::path& file_path, const int error_num) noexcept
        : message_{create_message(file_path, std::strerror(error_num))} {}
    /**
     * @brief Constructs a FileReadException from a file path and an error message.
     *
     * Combines the file path and a descriptive error message
     * to create a comprehensive detailed exception message.
     *
     * @param file_path The path of the file that caused the error.
     * @param error_message A descriptive message explaining the nature of the error.
     */
    FileReadException(const std::filesystem::path& file_path,
                      const std::string_view error_message) noexcept
        : message_{create_message(file_path, error_message)} {}

    /**
     * @brief Returns a C-style string describing the error and its cause.
     *
     * This function is mainly included
     * so that a message is shown upon termination when the exception is never caught.
     * Use of @c error_message or @c user_message is preferred
     * to get a string view describing the error.
     *
     * @return A pointer to a null-terminated string containing the error message.
     */
    [[nodiscard]] const char* what() const noexcept override { return message_.c_str(); }

    /**
     * @brief Retrieves the detailed error message written for logging.
     * @return A string view representing the detailed error message.
     */
    [[nodiscard]] std::string_view error_message() const override { return message_; }

    /**
     * @brief Retrieves a user-friendly error message intended for displaying to end-users.
     * @return A string view containing the user-friendly error message.
     */
    [[nodiscard]] std::string_view user_message() const override { return message_; }

  private:
    [[nodiscard]] static std::string create_message(
        const std::filesystem::path& file_path, const std::string_view error_message) noexcept {
        return "Failed to open or read file: " + file_path.string() + ": " +
               std::string{error_message} + '.';
    }
};

/**
 * @brief Exception class for parsing errors.
 *
 * This exception is thrown when input parsing fails.
 * It provides a detailed error message for logging purposes
 * and a user-friendly message suitable for end-user display.
 */
class ParseException final : public AocException {
    const std::string error_message_{};
    static constexpr auto user_message_{"Failed tot parse the input. See the log for details."};

  public:
    /**
     * @brief Constructs a ParseException with a detailed error message.
     *
     * This constructor initializes the exception with a specific error message
     * that describes the cause of the parsing failure.
     *
     * @param error_message A detailed description of the parsing error.
     */
    explicit ParseException(const std::string_view error_message) noexcept
        : error_message_{error_message} {}

    /**
     * @brief Returns a C-style string describing the error and its cause.
     *
     * This function is mainly included
     * so that a message is shown upon termination when the exception is never caught.
     * Use of @c error_message or @c user_message is preferred
     * to get a string view describing the error.
     *
     * @return A pointer to a null-terminated string containing the error message.
     */
    [[nodiscard]] const char* what() const noexcept override { return error_message_.c_str(); }

    /**
     * @brief Retrieves the detailed error message written for logging.
     * @return A string view representing the detailed error message.
     */
    [[nodiscard]] std::string_view error_message() const override { return error_message_; }

    /**
     * @brief Retrieves a user-friendly error message intended for displaying to end-users.
     * @return A string view containing the user-friendly error message.
     */
    [[nodiscard]] std::string_view user_message() const override { return user_message_; }
};

/**
 * @brief Exception class for overflow errors.
 *
 * This exception is thrown when an integer overflow is detected
 * and provides both a detailed error message for logging
 * and a user-friendly message for end-users.
 */
class OverflowException final : public AocException {
    const std::string error_message_{};
    static constexpr auto user_message_{"Overflow detected. See the log for details."};

  public:
    /**
     * @brief Constructs an OverflowException with a detailed error message.
     *
     * @param error_message A string view containing specific details about the overflow error.
     */
    explicit OverflowException(const std::string_view error_message) noexcept
        : error_message_{create_message(error_message)} {}

    /**
     * @brief Returns a C-style string describing the error and its cause.
     *
     * This function is mainly included
     * so that a message is shown upon termination when the exception is never caught.
     * Use of @c error_message or @c user_message is preferred
     * to get a string view describing the error.
     *
     * @return A pointer to a null-terminated string containing the error message.
     */
    [[nodiscard]] const char* what() const noexcept override { return error_message_.c_str(); }

    /**
     * @brief Retrieves the detailed error message written for logging.
     * @return A string view representing the detailed error message.
     */
    [[nodiscard]] std::string_view error_message() const override { return error_message_; }

    /**
     * @brief Retrieves a user-friendly error message intended for displaying to end-users.
     * @return A string view containing the user-friendly error message.
     */
    [[nodiscard]] std::string_view user_message() const override { return user_message_; }

  private:
    [[nodiscard]] static std::string create_message(
        const std::string_view error_message) noexcept {
        return "Overflow detected: " + std::string{error_message} + '.';
    }
};

}  // namespace aoc24

#endif  // AOC24_CPP_SRC_AOC_EXCEPTION_H_
