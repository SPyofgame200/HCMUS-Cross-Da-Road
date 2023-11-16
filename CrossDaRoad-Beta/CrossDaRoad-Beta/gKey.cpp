/**
 * @file gKey.cpp
 *
 * @brief Contains key enumeration and key map
 *
 * This file implements key enumeration for keyboard input and key map for mapping key to its code
**/

#include "gKey.h"
#include <Windows.h>
#include <map>

namespace app
{
	template <typename key_t, typename data_t>
	void MergeMapKey(std::map<key_t, data_t>& dest, const std::map<key_t, data_t>& source)
	{
		dest.insert(source.begin(), source.end());
	}

	/// @brief Create the map for the alphabet category. This contains 26 keys {
	/// @brief     A, B, C, D, E, F, G, H, I, J, K, L, M,
	/// @brief     N, O, P, Q, R, S, T, U, V, W, X, Y, Z
	/// @brief }
	/// @return A map with keys in the alphabet category.
	/// @retval std::map<uint16_t, uint8_t> A map with keys in the alphabet
	/// category.
	std::map<uint16_t, uint8_t> CreateMapKeyAlphabet()
	{
		std::map<uint16_t, uint8_t> mapKeys;
		mapKeys[0x41] = Key::A;
		mapKeys[0x42] = Key::B;
		mapKeys[0x43] = Key::C;
		mapKeys[0x44] = Key::D;
		mapKeys[0x45] = Key::E;
		mapKeys[0x46] = Key::F;
		mapKeys[0x47] = Key::G;
		mapKeys[0x48] = Key::H;
		mapKeys[0x49] = Key::I;
		mapKeys[0x4A] = Key::J;
		mapKeys[0x4B] = Key::K;
		mapKeys[0x4C] = Key::L;
		mapKeys[0x4D] = Key::M;
		mapKeys[0x4E] = Key::N;
		mapKeys[0x4F] = Key::O;
		mapKeys[0x50] = Key::P;
		mapKeys[0x51] = Key::Q;
		mapKeys[0x52] = Key::R;
		mapKeys[0x53] = Key::S;
		mapKeys[0x54] = Key::T;
		mapKeys[0x55] = Key::U;
		mapKeys[0x56] = Key::V;
		mapKeys[0x57] = Key::W;
		mapKeys[0x58] = Key::X;
		mapKeys[0x59] = Key::Y;
		mapKeys[0x5A] = Key::Z;
		return mapKeys;
	}

	/// @brief Create the map for the numeric category. This contains 10 keys {
	/// @brief     K0, K1, K2, K3, K4,
	/// @brief     K5, K6, K7, K8, K9
	/// @brief }
	/// @return A map with keys in the numeric category.
	/// @retval std::map<uint16_t, uint8_t> A map with keys in the numeric category.
	std::map<uint16_t, uint8_t> CreateMapKeyNumeric()
	{
		std::map<uint16_t, uint8_t> mapKeys;
		mapKeys[0x30] = Key::K0;
		mapKeys[0x31] = Key::K1;
		mapKeys[0x32] = Key::K2;
		mapKeys[0x33] = Key::K3;
		mapKeys[0x34] = Key::K4;
		mapKeys[0x35] = Key::K5;
		mapKeys[0x36] = Key::K6;
		mapKeys[0x37] = Key::K7;
		mapKeys[0x38] = Key::K8;
		mapKeys[0x39] = Key::K9;
		return mapKeys;
	}

	/// @brief Create the map for the function key category. This contains 12 keys {
	/// @brief     F1, F2, F3,  F4,  F5,  F6,
	/// @brief     F7, F8, F9, F10, F11, F12
	/// @brief }
	/// @return A map with keys in the function key category.
	/// @retval std::map<uint16_t, uint8_t> A map with keys in the function key
	/// category.
	std::map<uint16_t, uint8_t> CreateMapKeyFunction()
	{
		std::map<uint16_t, uint8_t> mapKeys;
		mapKeys[VK_F1] = Key::F1;
		mapKeys[VK_F2] = Key::F2;
		mapKeys[VK_F3] = Key::F3;
		mapKeys[VK_F4] = Key::F4;
		mapKeys[VK_F5] = Key::F5;
		mapKeys[VK_F6] = Key::F6;
		mapKeys[VK_F7] = Key::F7;
		mapKeys[VK_F8] = Key::F8;
		mapKeys[VK_F9] = Key::F9;
		mapKeys[VK_F10] = Key::F10;
		mapKeys[VK_F11] = Key::F11;
		mapKeys[VK_F12] = Key::F12;
		return mapKeys;
	}

	/// @brief Create the map for the arrow key category. This contains 4 keys {
	/// @brief     UP, DOWN, LEFT, RIGHT
	/// @brief }
	/// @return A map with keys in the arrow key category.
	/// @retval std::map<uint16_t, uint8_t> A map with keys in the arrow key
	/// category.
	std::map<uint16_t, uint8_t> CreateMapKeyArrow()
	{
		std::map<uint16_t, uint8_t> mapKeys;
		mapKeys[VK_UP] = Key::UP;
		mapKeys[VK_DOWN] = Key::DOWN;
		mapKeys[VK_LEFT] = Key::LEFT;
		mapKeys[VK_RIGHT] = Key::RIGHT;
		return mapKeys;
	}

	/// @brief Create the map for the special key category. This category includes
	/// 15 keys {
	/// @brief     SPACE, TAB, SHIFT, CONTROL, INS,
	/// @brief     DEL, HOME, END, PGUP, PGDN,
	/// @brief     BACK, ESCAPE, ENTER, PAUSE, SCROLL
	/// @brief }
	/// @return A map with keys in the special key category.
	/// @retval std::map<uint16_t, uint8_t> A map with keys in the special key
	/// category.
	std::map<uint16_t, uint8_t> CreateMapKeySpecial()
	{
		std::map<uint16_t, uint8_t> mapKeys;
		mapKeys[VK_SPACE] = Key::SPACE;
		mapKeys[VK_TAB] = Key::TAB;
		mapKeys[VK_SHIFT] = Key::SHIFT;
		mapKeys[VK_CONTROL] = Key::CONTROL;
		mapKeys[VK_INSERT] = Key::INS;
		mapKeys[VK_DELETE] = Key::DEL;
		mapKeys[VK_HOME] = Key::HOME;
		mapKeys[VK_END] = Key::END;
		mapKeys[VK_PRIOR] = Key::PGUP;
		mapKeys[VK_NEXT] = Key::PGDN;
		mapKeys[VK_BACK] = Key::BACK;
		mapKeys[VK_ESCAPE] = Key::ESCAPE;
		mapKeys[VK_RETURN] = Key::ENTER;
		mapKeys[VK_PAUSE] = Key::PAUSE;
		mapKeys[VK_SCROLL] = Key::SCROLL;
		return mapKeys;
	}

	/// @brief Create the map for the numpad category. This contains 10 keys {
	/// @brief     NP0, NP1, NP2, NP3, NP4,
	/// @brief     NP5, NP6, NP7, NP8, NP9
	/// @brief }
	/// @return A map with keys in the numpad category.
	/// @retval std::map<uint16_t, uint8_t> A map with keys in the numpad category.
	std::map<uint16_t, uint8_t> CreateMapKeyNumpad()
	{
		std::map<uint16_t, uint8_t> mapKeys;
		mapKeys[VK_NUMPAD0] = Key::NP0;
		mapKeys[VK_NUMPAD1] = Key::NP1;
		mapKeys[VK_NUMPAD2] = Key::NP2;
		mapKeys[VK_NUMPAD3] = Key::NP3;
		mapKeys[VK_NUMPAD4] = Key::NP4;
		mapKeys[VK_NUMPAD5] = Key::NP5;
		mapKeys[VK_NUMPAD6] = Key::NP6;
		mapKeys[VK_NUMPAD7] = Key::NP7;
		mapKeys[VK_NUMPAD8] = Key::NP8;
		mapKeys[VK_NUMPAD9] = Key::NP9;
		return mapKeys;
	}

	/// @brief Create the map for the operator category. This contains 5 keys {
	/// @brief     NP_MUL, NP_DIV, NP_ADD, NP_SUB, NP_DECIMAL
	/// @brief }
	/// @return A map with keys in the operator category.
	/// @retval std::map<uint16_t, uint8_t> A map with keys in the operator
	/// category.
	std::map<uint16_t, uint8_t> CreateMapKeyOperator()
	{
		std::map<uint16_t, uint8_t> mapKeys;
		mapKeys[VK_MULTIPLY] = Key::NP_MUL;
		mapKeys[VK_DIVIDE] = Key::NP_DIV;
		mapKeys[VK_ADD] = Key::NP_ADD;
		mapKeys[VK_SUBTRACT] = Key::NP_SUB;
		mapKeys[VK_DECIMAL] = Key::NP_DECIMAL;
		return mapKeys;
	}

	/// @brief Create the map for the additional key category. This contains 6 keys
	/// {
	/// @brief     PRINT, BREAK, MENU, POWER, SLEEP, CAPS_LOCK
	/// @brief }
	/// @return A map with keys in the additional key category.
	/// @retval std::map<uint16_t, uint8_t> A map with keys in the additional key
	/// category.
	std::map<uint16_t, uint8_t> CreateMapKeyAdditional()
	{
		std::map<uint16_t, uint8_t> mapKeys;
		mapKeys[VK_PRINT] = Key::PRINT;
		mapKeys[VK_PAUSE] = Key::BREAK;
		mapKeys[VK_MENU] = Key::MENU;
		mapKeys[VK_SLEEP] = Key::POWER;
		mapKeys[VK_SLEEP] = Key::SLEEP;
		mapKeys[VK_CAPITAL] = Key::CAPS_LOCK;
		return mapKeys;
	}

	/// @brief Create the map for the additional key category. This contains 6 keys
	/// {
	/// @brief     MEDIA_PLAY, MEDIA_STOP,
	/// @brief     MEDIA_PREV, MEDIA_NEXT,
	/// @brief     MEDIA_UP,   MEDIA_DOWN
	/// @brief }
	/// @return A map with keys in the media key category.
	/// @retval std::map<uint16_t, uint8_t> A map with keys in the media key
	/// category.
	std::map<uint16_t, uint8_t> CreateMapKeyMedia()
	{
		std::map<uint16_t, uint8_t> mapKeys;
		mapKeys[VK_MEDIA_PLAY_PAUSE] = Key::MEDIA_PLAY;
		mapKeys[VK_MEDIA_STOP] = Key::MEDIA_STOP;
		mapKeys[VK_MEDIA_PREV_TRACK] = Key::MEDIA_PREV;
		mapKeys[VK_MEDIA_NEXT_TRACK] = Key::MEDIA_NEXT;
		mapKeys[VK_VOLUME_UP] = Key::MEDIA_UP;
		mapKeys[VK_VOLUME_DOWN] = Key::MEDIA_DOWN;
		return mapKeys;
	}

	/// @brief Create the map for the vendor key category. This contains 12 keys {
	/// @brief     EQUAL, COMMA, MINUS, PERIOD,
	/// @brief     SEMICOLON, SLASH, BACKTICK, LEFT_BRACKET,
	/// @brief     BACKSLASH, RIGHT_BRACKET, APOSTROPHE, VENDOR
	/// @brief }
	/// @return A map with keys in the vendor key category.
	/// @retval std::map<uint16_t, uint8_t> A map with keys in the vendor key
	/// category.
	std::map<uint16_t, uint8_t> CreateMapKeyVendor()
	{
		std::map<uint16_t, uint8_t> mapKeys;
		mapKeys[VK_OEM_PLUS] = Key::EQUAL;
		mapKeys[VK_OEM_COMMA] = Key::COMMA;
		mapKeys[VK_OEM_MINUS] = Key::MINUS;
		mapKeys[VK_OEM_PERIOD] = Key::PERIOD;
		mapKeys[VK_OEM_1] = Key::SEMICOLON;
		mapKeys[VK_OEM_2] = Key::SLASH;
		mapKeys[VK_OEM_3] = Key::BACKTICK;
		mapKeys[VK_OEM_4] = Key::LEFT_BRACKET;
		mapKeys[VK_OEM_5] = Key::BACKSLASH;
		mapKeys[VK_OEM_6] = Key::RIGHT_BRACKET;
		mapKeys[VK_OEM_7] = Key::APOSTROPHE;
		mapKeys[VK_OEM_8] = Key::VENDOR;
		return mapKeys;
	}

	/// @brief Create a map of used keys. This contains 10 categories {
	/// @brief      26 x Alphabet, 10 x Numeric, 12 x Function, 4 x Arrow, 15 x
	/// Special,
	/// @brief      10 x Numpad, 5 x Operator, 6 x Additional, 6 x Media, 12 x
	/// Vendor
	/// @brief }
	/// @brief with extra 2 keys [0x00] = NONE, [0xFF] = UNDEFINED
	/// @return A map keys of all categories
	/// @retval std::map<uint16_t, uint8_t> A map keys of all categories
	std::map<uint16_t, uint8_t> CreateMapKey()
	{
		std::map<uint16_t, uint8_t> mapKeys;

		mapKeys[0x00] = NONE;
		MergeMapKey(mapKeys, CreateMapKeyAlphabet());
		MergeMapKey(mapKeys, CreateMapKeyNumeric());
		MergeMapKey(mapKeys, CreateMapKeyFunction());
		MergeMapKey(mapKeys, CreateMapKeyArrow());
		MergeMapKey(mapKeys, CreateMapKeySpecial());
		MergeMapKey(mapKeys, CreateMapKeyNumpad());
		MergeMapKey(mapKeys, CreateMapKeyOperator());
		MergeMapKey(mapKeys, CreateMapKeyAdditional());
		MergeMapKey(mapKeys, CreateMapKeyMedia());
		MergeMapKey(mapKeys, CreateMapKeyVendor());
		mapKeys[0xFF] = UNDEFINED;

		return mapKeys;
	}

	/// @brief Check if a key is in the alphabet category. This contains 26 keys {
	/// @brief     A, B, C, D, E, F, G, H, I, J, K, L, M,
	/// @brief     N, O, P, Q, R, S, T, U, V, W, X, Y, Z
	/// @brief }
	/// @return True if the key is in the alphabet category; otherwise, false.
	bool IsKeyAlphabet(const Key key)
	{
		return (key >= A && key <= Z);
	}

	/// @brief Check if a key is in the numeric category. This contains 10 keys {
	/// @brief     K0, K1, K2, K3, K4,
	/// @brief     K5, K6, K7, K8, K9
	/// @brief }
	/// @return True if the key is in the numeric category; otherwise, false.
	bool IsKeyNumeric(const Key key)
	{
		return (key >= K0 && key <= K9);
	}

	/// @brief Check if a key is in the function key category. This contains 12 keys
	/// {
	/// @brief     F1, F2, F3, F4, F5, F6,
	/// @brief     F7, F8, F9, F10, F11, F12
	/// @brief }
	/// @return True if the key is in the function key category; otherwise, false.
	bool IsKeyFunction(const Key key)
	{
		return (key >= F1 && key <= F12);
	}

	/// @brief Check if a key is in the arrow key category. This contains 4 keys {
	/// @brief     UP, DOWN, LEFT, RIGHT
	/// @brief }
	/// @return True if the key is in the arrow key category; otherwise, false.
	bool IsKeyArrow(const Key key)
	{
		return (key >= UP && key <= RIGHT);
	}

	/// @brief Check if a key is in the special key category. This category includes
	/// 15 keys {
	/// @brief     SPACE, TAB, SHIFT, CONTROL, INS, DEL, HOME, END,
	/// @brief     PGUP, PGDN, BACK, ESCAPE, ENTER, PAUSE, SCROLL
	/// @brief }
	/// @return True if the key is in the special key category; otherwise, false.
	bool IsKeySpecial(const Key key)
	{
		return (key >= SPACE && key <= SCROLL);
	}

	/// @brief Check if a key is in the numpad category. This contains 10 keys {
	/// @brief     NP0, NP1, NP2, NP3, NP4,
	/// @brief     NP5, NP6, NP7, NP8, NP9
	/// @brief }
	/// @return True if the key is in the numpad category; otherwise, false.
	bool IsKeyNumpad(const Key key)
	{
		return (key >= NP0 && key <= NP_DECIMAL);
	}

	/// @brief Check if a key is in the operator category. This contains 5 keys {
	/// @brief     NP_MUL, NP_DIV, NP_ADD, NP_SUB, NP_DECIMAL
	/// @brief }
	/// @return True if the key is in the operator category; otherwise, false.
	bool IsKeyOperator(const Key key)
	{
		return (key >= NP0 && key <= NP_DECIMAL);
	}

	/// @brief Check if a key is in the additional key category. This contains 6
	/// keys {
	/// @brief     PRINT, BREAK, MENU, POWER, SLEEP, CAPS_LOCK
	/// @brief }
	/// @return True if the key is in the additional key category; otherwise, false.
	bool IsKeyAdditional(const Key key)
	{
		return (key >= PRINT && key <= CAPS_LOCK);
	}

	/// @brief Check if a key is in the additional key category. This contains 6
	/// keys {
	/// @brief     MEDIA_PLAY, MEDIA_STOP,
	/// @brief     MEDIA_PREV, MEDIA_NEXT,
	/// @brief     MEDIA_UP,   MEDIA_DOWN
	/// @brief }
	/// @return True if the key is in the additional key category; otherwise, false.
	bool IsKeyMedia(const Key key)
	{
		return (key >= MEDIA_PLAY && key <= MEDIA_DOWN);
	}
	///
	/// @brief Check if a key is in the vendor key category. This contains 8 keys {
	/// @brief     SEMICOLON, SLASH, BACKTICK, LEFT_BRACKET,
	/// @brief     BACKSLASH, RIGHT_BRACKET, APOSTROPHE, VENDOR
	/// @brief }
	/// @return True if the key is in the vendor key category; otherwise, false.
	bool IsKeyVendor(const Key key)
	{
		return (key >= EQUAL && key <= VENDOR);
	}

	/// @brief Check if a key is unused in the enum
	/// @return True if the key is unused
	bool IsKeyUnused(const Key key)
	{
		return (key >= UNKNOWN_KEY && key <= UNUSED);
	}

	/// @brief Check if a key is used in map keys (using CreateMapKey())
	/// @return True if the key is used
	bool IsKey(const Key key)
	{
		return (key >= NONE && key <= UNDEFINED);
	}

	/// @brief Get the category of a key.
	/// @param key The key code to determine the category for.
	/// @return The category of the key.
	KeyCategory GetKeyCategory(const Key key)
	{
		if (IsKeyAlphabet(key)) {
			return KeyCategory::ALPHABET;
		}
		else if (IsKeyNumeric(key)) {
			return KeyCategory::NUMERIC;
		}
		else if (IsKeyFunction(key)) {
			return KeyCategory::FUNCTION;
		}
		else if (IsKeyArrow(key)) {
			return KeyCategory::ARROW;
		}
		else if (IsKeySpecial(key)) {
			return KeyCategory::SPECIAL;
		}
		else if (IsKeyNumpad(key)) {
			return KeyCategory::NUMPAD;
		}
		else if (IsKeyOperator(key)) {
			return KeyCategory::OPERATOR;
		}
		else if (IsKeyAdditional(key)) {
			return KeyCategory::ADDITIONAL;
		}
		else if (IsKeyMedia(key)) {
			return KeyCategory::MEDIA;
		}
		else if (IsKeyVendor(key)) {
			return KeyCategory::VENDOR;
		}
		return KeyCategory::UNKNOWN;
	}

	/// @brief Check if a key belongs to a specific category.
	/// @param key The key code to check.
	/// @param category The category of keys to check against.
	/// @return True if the key is in the specified category; otherwise, false.
	bool IsKeyCategory(const Key key, const KeyCategory category)
	{
		return GetKeyCategory(key) == category;
	}
} // namespace app
