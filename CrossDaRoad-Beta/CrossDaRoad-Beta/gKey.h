
/**
 * @file gKey.h
 *
 * @brief Contains key enumeration and key map
 *
 * This file contains key enumeration for keyboard input (prototype) and key map for mapping key to its code
**/

#ifndef G_KEY_H
#define G_KEY_H

#include <map>

//=================================================================================================
// Include new header files here

//=================================================================================================

namespace app
{
    /// @brief Enumeration of keys in the game CrossDaRoad (for keyboard input)
    enum Key
    {
        // <1 key> No key is pressed
        NONE,

        // <26 keys> Alphabetic keys
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,

        // <10 keys> Numeric keys
        K0,
        K1,
        K2,
        K3,
        K4,
        K5,
        K6,
        K7,
        K8,
        K9,

        // <12 keys> Function keys
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,

        // <4 keys> Arrow keys
        UP,
        DOWN,
        LEFT,
        RIGHT,

        // <15 keys> Special keys
        SPACE,   // Spacebar
        TAB,     // Tab key
        SHIFT,   // Shift key
        CONTROL, // Control key
        INS,     // Insert key
        DEL,     // Delete key
        HOME,    // Home key
        END,     // End key
        PGUP,    // Page Up key
        PGDN,    // Page Down key
        BACK,    // Backspace key
        ESCAPE,  // Escape key
        ENTER,   // Enter key
        PAUSE,   // Pause key
        SCROLL,  // Scroll Lock key

        // <10 keys> Numpad keys
        NP0,
        NP1,
        NP2,
        NP3,
        NP4,
        NP5,
        NP6,
        NP7,
        NP8,
        NP9,

        // <5 keys> Operator keys
        NP_MUL,     // Multiplication (asterisk) key on the numeric keypad
        NP_DIV,     // Division (slash) key on the numeric keypad
        NP_ADD,     // Addition (plus) key on the numeric keypad
        NP_SUB,     // Subtraction (minus) key on the numeric keypad
        NP_DECIMAL, // Decimal point (period) key on the numeric keypad

        //  <6 keys> Additional special keys
        PRINT,     // Print Screen key
        BREAK,     // Pause/Break key
        MENU,      // Application/Menu key
        POWER,     // Power/Sleep key
        SLEEP,     // Sleep key
        CAPS_LOCK, // Caps Lock key

        // <6 keys> Media special keys
        MEDIA_PLAY, // Media Play key
        MEDIA_STOP, // Media Stop key
        MEDIA_PREV, // Media Previous key
        MEDIA_NEXT, // Media Next key
        MEDIA_UP,   // Volume Up key
        MEDIA_DOWN, // Volume Down key

        // <12 keys> Vendor keys
        EQUAL,         // Equal key
        COMMA,         // Comma key
        MINUS,         // Minus key
        PERIOD,        // Period key
        SEMICOLON,     // Semicolon key
        SLASH,         // Slash key
        BACKTICK,      // Backtick key
        LEFT_BRACKET,  // Left Bracket key
        BACKSLASH,     // Backslash key
        RIGHT_BRACKET, // Right Bracket key
        APOSTROPHE,    // Apostrophe key
        VENDOR,        // Vendor-specific key (You can comment this out)

        // Undefined key
        UNDEFINED, // Cannot detect if pressed or not

        // [Unused] Unknown keys
        UNKNOWN_KEY,        // Any key is pressed
        UNKNOWN_ARROW,      // Any arrow key is pressed
        UNKNOWN_KEYPAD,     // Any keypad key is pressed
        UNKNOWN_SPECIAL,    // Any special key is pressed
        UNKNOWN_NUMERIC,    // Any numeric key is pressed
        UNKNOWN_FUNCTION,   // Any function key is pressed
        UNKNOWN_OPERATOR,   // Any operator key is pressed
        UNKNOWN_ADDITIONAL, // Any additional key is pressed
        UNKNOWN_ALPHABETIC, // Any alphabetic key is pressed

        // [Unused] Additional special keys
        WAKE,        // Wake Up key
        CALCULATOR,  // Calculator key
        MY_COMPUTER, // My Computer key
        EMAIL,       // Email key
        WEB,         // Web/Home key
        SEARCH,      // Search key
        FAVORITES,   // Favorites key
        LOCK_SCREEN, // Lock Screen key
        EJECT,       // Eject key
        LBUTTON,     // Left Button key (Mouse)
        RBUTTON,     // Right Button key (Mouse)
        MBUTTON,     // Mouse Wheel key (Mouse)
        CUSTOM_KEY1, // Custom user-defined key 1
        CUSTOM_KEY2, // Custom user-defined key 2

        // [Unused] Unused unknown keys
        UNUSED
    };

    using mapkeys_t = std::map<uint16_t, Key>;

    template <typename key_t, typename data_t>
    void MergeMapKey(std::map<key_t, data_t>& dest, const std::map<key_t, data_t>& source);

    mapkeys_t CreateMapKeyAlphabet();
    mapkeys_t CreateMapKeyNumeric();
    mapkeys_t CreateMapKeyFunction();
    mapkeys_t CreateMapKeyArrow();
    mapkeys_t CreateMapKeySpecial();
    mapkeys_t CreateMapKeyNumpad();
    mapkeys_t CreateMapKeyOperator();
    mapkeys_t CreateMapKeyAdditional();
    mapkeys_t CreateMapKeyMedia();
    mapkeys_t CreateMapKeyVendor();
    mapkeys_t CreateMapKey();

    bool IsKeyAlphabet(Key key);
    bool IsKeyNumeric(Key key);
    bool IsKeyFunction(Key key);
    bool IsKeyArrow(Key key);
    bool IsKeySpecial(Key key);
    bool IsKeyNumpad(Key key);
    bool IsKeyAdditional(Key key);
    bool IsKeyMedia(Key key);
    bool IsKeyVendor(Key key);
    bool IsKeyUnused(Key key);
    bool IsKey(Key key);

    enum class KeyCategory
    {
        ALPHABET,
        NUMERIC,
        FUNCTION,
        ARROW,
        SPECIAL,
        NUMPAD,
        OPERATOR,
        ADDITIONAL,
        MEDIA,
        VENDOR,
        UNKNOWN
    };
    KeyCategory GetKeyCategory(Key key);
    bool IsKeyCategory(Key key, KeyCategory category);
} // namespace app

#endif
