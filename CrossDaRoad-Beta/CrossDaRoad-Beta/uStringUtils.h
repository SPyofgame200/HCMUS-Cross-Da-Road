/**
 * @file uStringUtils.h
 *
 * @brief Contains string utilities
 *
 * This file contains string utility function prototypes and constants for string manipulation.
**/

#ifndef U_STRING_UTILS_H
#define U_STRING_UTILS_H

#include <random>

//=================================================================================================
// Include new header files here

//=================================================================================================

/// @brief String utilities
namespace utils
{
    extern const char* sSpacePattern; ///< Pattern for space characters

    std::string& ltrim(std::string& raw, const char* pattern = sSpacePattern);
    std::string& rtrim(std::string& raw, const char* pattern = sSpacePattern);
    std::string& trim(std::string& raw, const char* pattern = sSpacePattern);

    std::string lpad(const std::string& input, char paddingChar, size_t length = 1);
    std::string rpad(const std::string& input, char paddingChar, size_t length = 1);

    std::string& lowerize(std::string& raw);
    std::string& upperize(std::string& raw);
    std::string& deduplicate(std::string& raw, const char* pattern = sSpacePattern);

    std::string& camelCaseToSnake(std::string& raw);
    std::string& snakeCaseToCamel(std::string& raw);

    std::string& reverse(std::string& raw);
    std::string& shuffle(std::string& raw);

    std::string& stripHtml(std::string& raw, bool keepTagContent = false);

    std::vector<std::string> split(const std::string& raw, const char* delimiter = " ", bool ignore_null = false);
    std::string concat(const std::vector<std::string>& substrings, const char* delimiter = " ", const char* ending = "");
}

#endif // U_STRING_UTILS_H
