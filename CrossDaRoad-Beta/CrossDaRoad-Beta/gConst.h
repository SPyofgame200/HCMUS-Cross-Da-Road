#ifndef G_CONST_H
#define G_CONST_H

/**
 * @file gConst.h
 *
 * @brief Contains game engine constants
 *
 * This file contains game engine constants for error handling, event handling, and other purposes.
**/

/// @brief Namespace for game engine constants
namespace engine
{
	/// @brief Enumeration of codes in the game engine (for error handling)
	enum Code
	{
		// Successful codes
		SUCCESS = 0,         ///< The program executed successfully without errors
		SUCCESS_WARNING = 1, ///< The program succeeded, but ignore non-fatal warnings
		SUCCESS_DANGER = 2,  ///< The program is partially succeeded, with fatal warnings and potential bugs
		SUCCESS_RISK = 3,    ///< The program is partially succeeded, produce minor or even major issues

		// General error codes
		FAILURE = -1,         ///< Generic failure code, indicating an unspecified error
		ACCESS_DENIED = -2,   ///< The user doesn't have permission for the requested operation
		INCOMPATIBILITY = -3, ///< Default settings are incompatible with custom settings

		// Invalid codes
		INVALID_SIZE = -10,          ///< Size is too large or not positive
		INVALID_WIDTH = -11,         ///< Width is too large or not positive
		INVALID_HEIGHT = -12,        ///< Height is too large or not positive
		INVALID_PROCESS = -13,       ///< The act of calling the function currently is invalid
		INVALID_ARGUMENT = -14,      ///< Command line arguments or inputs are invalid
		INVALID_PARAMETER = -15,     ///< Passed parameter is not valid
		INVALID_ALLOCATION = -16,    ///< Failed to allocate the position
		INVALID_INTERACTION = -17,   ///< Failed interactions among objects
		INVALID_INPUT_FORMAT = -18,  ///< The input format is not as expected
		INVALID_OUTPUT_FORMAT = -19, ///< The output format is not as expected

		// Limit control codes
		TIME_LIMIT_EXCEED = -20,    ///< Running time is more than allowed
		ASSET_LIMIT_EXCEED = -21,   ///< The number of assets or resources created or used has exceeded the allowed limit
		MEMORY_LIMIT_EXCEED = -22,  ///< Memory usage is more than allowed
		COUNTER_LIMIT_EXCEED = -23, ///< Like time_limit_exceed code, but using counter measurement instead of time

		// File related
		FILE_NOT_FOUND = -30,       ///< The specified file or resource does not exist
		FILE_READ_ERROR = -31,      ///< Error reading from a file
		FILE_WRITE_ERROR = -32,     ///< Error writing to a file
		FILE_FORMAT_ERROR = -33,    ///< Error file format compares to standard
		FILE_ACCESS_DENIED = -34,   ///< Access to the file is denied
		FILE_UNRECOGNIZABLE = -35,  ///< File has been corrupted
		FILE_EXTENSION_ERROR = -36, ///< File extension do not have a suitable implementation

	};

	constexpr const char* ENGINE_NAME = "GAME_ENGINE";
	constexpr const wchar_t* ENGINE_WIDE_NAME = L"GAME_ENGINE";
	constexpr const char* ICON_FILE_PATH = "data/icons/icon.ico";
	constexpr const char* FAVICON_FILE_PATH = "data/icons/favicon.ico";

	/// @brief Enumeration of ticks in the game engine (for event handling)
	enum Tick
	{
		// Engine Main Events
		BEFORE_CREATE_EVENT,
		AFTER_CREATE_EVENT,
		BEFORE_UPDATE_EVENT,
		AFTER_UPDATE_EVENT,
		BEFORE_SCENE_RENDER_EVENT,
		AFTER_SCENE_RENDER_EVENT,
		BEFORE_POST_PROCCESSING_EVENT,
		AFTER_POST_PROCCESSING_EVENT,
		BEFORE_DESTROY_EVENT,
		AFTER_DESTROY_EVENT,
		PRE_RUNNING_EVENT,
		POST_RUNNING_EVENT,

		// Window Events
		CREATE_WINDOW_EVENT,
		DESTROY_WINDOW_EVENT,
		PRE_WINDOW_UPDATE_EVENT,
		POST_WINDOW_UPDATE_EVENT,
		NO_WINDOW_UPDATE_EVENT,

		// Load Events
		BEFORE_LOAD_KEYBOARD_EVENT,
		AFTER_LOAD_KEYBOARD_EVENT,

		// Update Events
		AFTER_UPDATE_KEYBOARD_EVENT,
		AFTER_UPDATE_TITLE_EVENT,

		// Render Events
		AFTER_RENDER_EVENT,

		// Special Events
		ON_PAUSE_EVENT,
		ON_UNPAUSE_EVENT,
	};
}

#endif // G_CONST_H