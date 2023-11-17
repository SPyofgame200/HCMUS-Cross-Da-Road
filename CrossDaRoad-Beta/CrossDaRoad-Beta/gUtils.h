/**
 * @file gUtils.h
 *
 * @brief Contains utility functions for string conversion
 *
 * This file contains utility function prototypes for string conversion between different types.
**/

#ifndef G_UTILS_H
#define G_UTILS_H

#include <Windows.h>
#include <string>
#include <memory>



namespace app
{
	std::wstring to_wstring(const std::string& utf8String);
	std::string to_string(const std::wstring& wideString);

#ifdef UNICODE
#define to_text to_wtext
	typedef wchar_t text_t;
	typedef char itext_t; // inverted
#else
#define to_text to_utext
	typedef char text_t;
	typedef wchar_t itext_t; // inverted
#endif

	const wchar_t* to_wtext(const char* input);
	const wchar_t* to_wtext(const wchar_t* input);
	const wchar_t* to_wtext(const std::string& input);
	const wchar_t* to_wtext(const std::wstring& input);
	const char* to_utext(const char* input);
	const char* to_utext(const wchar_t* input);
	const char* to_utext(const std::string& input);
	const char* to_utext(const std::wstring& input);
}

#endif // G_UTILS_H
