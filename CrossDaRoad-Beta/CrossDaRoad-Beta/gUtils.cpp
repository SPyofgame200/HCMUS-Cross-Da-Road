/**
 * @file gUtils.cpp
 *
 * @brief Contains utility functions for string conversion
 *
 * This file implements utility functions for string conversion between different types.
**/

#include "gUtils.h"


/**
 * @namespace app
 * @brief Utility functions
 **/
namespace app
{
	/// @brief Converts a string to a wide string (UTF-8 to wide string)
	/// @param utf8String The string to be converted.
	/// @return The converted wide string.
	std::wstring to_wstring(const std::string& utf8String)
	{
		const int wideStringSize =
			MultiByteToWideChar(CP_UTF8, 0, utf8String.c_str(), -1, nullptr, 0);
		if (wideStringSize == 0) {
			return L"";
		}
		const std::unique_ptr<wchar_t[]> wideBuffer(new wchar_t[wideStringSize]);
		if (MultiByteToWideChar(CP_UTF8, 0, utf8String.c_str(), -1, wideBuffer.get(), wideStringSize) == 0) {
			return L"";
		}
		return std::wstring(wideBuffer.get());
	}

	/// @brief Converts a wide string to a string (wide string to UTF-8)
	/// @param wideString The string to be converted.
	/// @return The converted utf8 string.
	std::string to_string(const std::wstring& wideString)
	{
		const int utf8StringSize = WideCharToMultiByte(CP_UTF8, 0, wideString.c_str(), -1, nullptr, 0, nullptr, nullptr);
		if (utf8StringSize == 0) {
			return "";
		}
		const std::unique_ptr<char[]> utf8Buffer(new char[utf8StringSize]);
		if (WideCharToMultiByte(CP_UTF8, 0, wideString.c_str(), -1, utf8Buffer.get(), utf8StringSize, nullptr, nullptr) == 0) {
			return "";
		}
		return std::string(utf8Buffer.get());
	}

	static std::wstring WTEXT; // use local variable to avoid pointer issues

	/// @brief Converts a string to a wide string 
	/// @param input The string to be converted.
	/// @return The converted wide string.
	const wchar_t* to_wtext(const char* input)
	{
		return (WTEXT = to_wstring(std::string(input))).c_str();
	}

	/// @brief Converts a string to a wide string
	/// @param input The string to be converted.
	/// @return The converted wide string.
	const wchar_t* to_wtext(const wchar_t* input)
	{
		return input;
	}

	/// @brief Converts a string to a wide string
	/// @param input The string to be converted.
	/// @return The converted wide string.
	const wchar_t* to_wtext(const std::string& input)
	{
		return (WTEXT = to_wstring(input)).c_str();
	}

	/// @brief Converts a string to a wide string
	/// @param input The string to be converted.
	/// @return The converted wide string.
	const wchar_t* to_wtext(const std::wstring& input)
	{
		return input.c_str();
	}

	static std::string UTEXT; // use local variable to avoid pointer issues

	/// @brief Converts a wide string to a string
	/// @param input Wide string to be converted.
	/// @return The converted string.	
	const char* to_utext(const char* input)
	{
		return input;
	}

	/// @brief Converts a wide string to a string
	/// @param input Wide string to be converted.
	/// @return The converted string.	
	const char* to_utext(const wchar_t* input)
	{
		return (UTEXT = to_string(std::wstring(input))).c_str();
	}

	/// @brief Converts a wide string to a string
	/// @param input Wide string to be converted.
	/// @return The converted string.	
	const char* to_utext(const std::string& input)
	{
		return (UTEXT = std::string(input)).c_str();
	}

	/// @brief Converts a wide string to a string
	/// @param input Wide string to be converted.
	/// @return The converted string.	
	const char* to_utext(const std::wstring& input)
	{
		return (UTEXT = to_string(input)).c_str();
	}
} // namespace app

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// END OF FILE ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////