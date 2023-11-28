/**
 * @file uStringUtils.cpp
 * @author SPyOfGame
 *
 * @brief Contains string utilities
 *
 * This file implements string utility functions.
 **/

#include "uStringUtils.h"

 //=================================================================================================
 // Include new header files here

 //=================================================================================================

namespace utils
{
    const char* sSpacePattern = " ";
    /// @brief Trim from start of string (left)
    /// @param raw The string to be trimmed
    /// @param pattern The pattern to be trimmed
    /// @return The trimmed string
    /// @example ltrim("  spy  of  game  ")
    ///        returns "spy  of  game  "
    std::string& ltrim(std::string& raw, const char* pattern)
    {
        raw.erase(0, raw.find_first_not_of(pattern));
        return raw;
    }

    /// @brief Trim from end of string (right)
    /// @param raw The string to be trimmed
    /// @param pattern The pattern to be trimmed
    /// @return The trimmed string
    /// @example rtrim("  spy  of  game  ")
    ///        returns "  spy  of  game"
    std::string& rtrim(std::string& raw, const char* pattern)
    {
        raw.erase(raw.find_last_not_of(pattern) + 1);
        return raw;
    }

    /// @brief Trim from both ends of string (left & right)
    /// @param raw String to be trimmed
    /// @param pattern Pattern to be trimmed
    /// @return Trimmed string
    /// @example trim("  spy  of  game  ")
    ///       returns "spy  of  game"
    std::string& trim(std::string& raw, const char* pattern)
    {
        return ltrim(rtrim(raw, pattern), pattern);
    }

    /// @brief Left-pad a string with a character to a certain length
    /// @param input Input string
    /// @param paddingChar Padding character
    /// @param length Length of the padded string 
    /// @return String with padding
    /// @example lpad("spyofgame", '*', 5)
    ///       returns "spyofgame*****"
    std::string lpad(const std::string& input, const char paddingChar, const size_t length)
    {
        if (input.length() >= length) {
            return input;
        }
        return std::string(length - input.length(), paddingChar) + input;
    }

    /// @brief Right-pad a string with a character to a certain length
    /// @param input String to be padded
    /// @param paddingChar Character to be padded
    /// @param length Length of the padded string
    /// @return Padding string
    /// @example rpad("spyofgame", '*', 5)
    ///       returns "spyofgame*****"
    std::string rpad(const std::string& input, const char paddingChar, const size_t length)
    {
        if (input.length() >= length) {
            return input;
        }
        return input + std::string(length - input.length(), paddingChar);
    }

    std::string& lowerize(std::string& raw)
    {
        for (char& c : raw) {
            if ('A' <= c && c <= 'Z') {
                c |= 32;
            }
        }
        return raw;
    }

    std::string& upperize(std::string& raw)
    {
        for (char& c : raw) {
            if ('a' <= c && c <= 'z') {
                c &= ~32;
            }
        }
        return raw;
    }

    /// @brief Remove duplicate characters in a string
    /// @param raw String to be deduplicated
    /// @param pattern Pattern to be deduplicated
    /// @return Deduplicated string
    /// @example deduplicate("spy of game", " ")
    ///              returns "spy ofgame"
    std::string& deduplicate(std::string& raw, const char* pattern)
    {
        if (pattern == nullptr) {
            return raw;
        }
        const auto new_end = std::unique(raw.begin(), raw.end(),
            [pattern](const char lhs, const char rhs) {
                return (lhs == rhs) && (strchr(pattern, lhs) != nullptr);
            });
        raw.erase(new_end, raw.end());
        return raw;
    }

    /// @brief Convert camel case to snake case (lowercase with underscores)
    /// @param raw Input string
    /// @return String in snake case
    /// @example camelCaseToSnake("spyOfGame")
    ///                   returns "spy_of_game"
    std::string& camelCaseToSnake(std::string& raw)
    {
        for (auto it = raw.begin(); it != raw.end(); ++it) {
            if (isupper(*it)) {
                it = raw.insert(it, '_');
                it = raw.insert(it + 2, tolower(*(it + 2)));
            }
        }
        return raw;
    }

    /// @brief Convert snake case to camel case 
    /// @param raw Input string
    /// @return Camel case string
    /// @example snakeCaseToCamel("spy_of_game")
    ///                   returns "spyOfGame"
    std::string& snakeCaseToCamel(std::string& raw)
    {
        for (auto it = raw.begin(); it != raw.end(); ++it) {
            if (*it == '_') {
                it = raw.erase(it);
                if (it != raw.end()) {
                    *it = toupper(*it);
                }
            }
        }
        return raw;
    }

    /// @brief Reverse a string in place (in memory)
    /// @param raw String to be reversed
    /// @return Reversed string
    /// @example reverse("spyofgame")
    ///          returns "emagofyps"
    std::string& reverse(std::string& raw)
    {
        std::reverse(raw.begin(), raw.end()); // Reverse the characters in the string
        return raw;
    }

    /// @brief Shuffle a string in place (in memory)
    /// @param raw String to be shuffled
    /// @return Shuffled string
    /// @example shuffle("spyofgame")
    ///          returns "gofysemap"
    std::string& shuffle(std::string& raw)
    {
        std::string result = raw;
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(result.begin(), result.end(), g); // Shuffle the characters using a random generator
        raw = result;
        return raw;
    }

    /// @brief Strip HTML tags from a string
    /// @param raw String to be stripped
    /// @param keepTagContent  Whether to keep the content of the HTML tags
    /// @return  Stripped string
    /// @example stripHtml("<b>spy</b> of <i>game</i>")
    ///            returns "spy of game"
    /// @example stripHtml("<b>spy</b> of <i>game</i>", true)
    ///            returns "<b>spy</b> of <i>game</i>"
    std::string& stripHtml(std::string& raw, const bool keepTagContent)
    {
        std::string result;
        bool inTag = false;

        for (const char c : raw) {
            if (c == '<') {
                inTag = true; // Entering an HTML tag
                if (keepTagContent)
                    result += c;
            }
            else if (c == '>') {
                inTag = false; // Exiting an HTML tag
                if (keepTagContent)
                    result += c;
            }
            else if (!inTag) {
                result += c; // Append non-tag content
            }
        }

        raw = result;
        return raw;
    }

    /// @brief  Split a string into a vector of substrings by a delimiter
    /// @param raw String to be split
    /// @param delimiter Delimiter to split the string
    /// @param ignore_null Whether to ignore null substrings
    /// @return Vector of substrings
    /// @example split("spy of game")
    ///      returns { "spy", "of", "game" }
    /// @example split("spy of game", "of")
    ///      returns { "spy ", " game" }
    /// @example split("spy of game", "of", true)
    ///      returns { "spy ", " game" }
    /// @example split("spy of game", "of", false)
    ///      returns { "spy", " ", "game" }
    std::vector<std::string> split(const std::string& raw, const char* delimiter, const bool ignore_null)
    {
        std::vector<std::string> result;
        std::string input = input;
        size_t pos = 0;
        while ((pos = input.find(delimiter)) != std::string::npos) {
            std::string token = input.substr(0, pos);
            if (!ignore_null || !token.empty()) {
                result.push_back(token);
            }
            input.erase(0, pos + strlen(delimiter));
        }
        result.push_back(input);
        return result;
    }

    /// @brief Concatenate a vector of substrings into a string by a delimiter
    /// @param substrings Vector of substrings to be concatenated
    /// @param delimiter Delimiter to concatenate the substrings
    /// @param ending Ending to be added
    /// @return Concatenated string
    /// @example concat({ "spy", "of", "game" })
    ///           returns "spy of game"
    /// @example concat({ "spy", "of", "game" }, " of ")
    ///           returns "spy of game"
    /// @example concat({ "spy", "of", "game" }, " of ", ".")
    ///           returns "spy of game."
    std::string concat(const std::vector<std::string>& substrings, const char* delimiter, const char* ending)
    {
        std::string result;
        for (const std::string& sub : substrings) {
            result += sub;
            result += delimiter;
        }
        if (!result.empty()) {
            result.erase(result.size() - strlen(delimiter));
            result += ending;
        }
        return result;
    }
}; // namespace utils

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// END OF FILE ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////