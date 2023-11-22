#ifndef U_CONSOLE_COLOR_H
#define U_CONSOLE_COLOR_H

// Forward Declartion
namespace app {
    struct Pixel;
}

#include <string>
namespace console
{
    int ClosestColor(int r, int g, int b);
    std::string TextColor(const app::Pixel& pixel);
    std::string BackgroundColor(const app::Pixel& pixel);
    std::string ResetTextColor();
    std::string ResetBackgroundColor();
    void ShowConsoleColor();
    void ShowConsoleTextColor();
    void ShowConsoleBackgroundColor();
}

namespace console
{
    // Enum for text colors
    enum Color
    {
        RESET,
        BLACK,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE,
        ORANGE,
        PINK,
        PURPLE,
        LIME,
        TEAL,
        OLIVE,
        BROWN,
        GRAY,
        BRIGHT_BLACK,
        BRIGHT_RED,
        BRIGHT_GREEN,
        BRIGHT_YELLOW,
        BRIGHT_BLUE,
        BRIGHT_MAGENTA,
        BRIGHT_CYAN,
        BRIGHT_WHITE,
        BRIGHT_ORANGE,
        BRIGHT_PINK,
        BRIGHT_PURPLE,
        BRIGHT_LIME,
        BRIGHT_TEAL,
        BRIGHT_OLIVE,
        BRIGHT_BROWN,
        BRIGHT_GRAY,
        VERY_LIGHT_BLACK,
        VERY_LIGHT_RED,
        VERY_LIGHT_GREEN,
        VERY_LIGHT_YELLOW,
        VERY_LIGHT_BLUE,
        VERY_LIGHT_MAGENTA,
        VERY_LIGHT_CYAN,
        VERY_LIGHT_WHITE,
        VERY_LIGHT_ORANGE,
        VERY_LIGHT_PINK,
        VERY_LIGHT_PURPLE,
        VERY_LIGHT_LIME,
        VERY_LIGHT_TEAL,
        VERY_LIGHT_OLIVE,
        VERY_LIGHT_BROWN,
        VERY_LIGHT_GRAY,
        LIGHT_BLACK,
        LIGHT_RED,
        LIGHT_GREEN,
        LIGHT_YELLOW,
        LIGHT_BLUE,
        LIGHT_MAGENTA,
        LIGHT_CYAN,
        LIGHT_WHITE,
        LIGHT_ORANGE,
        LIGHT_PINK,
        LIGHT_PURPLE,
        LIGHT_LIME,
        LIGHT_TEAL,
        LIGHT_OLIVE,
        LIGHT_BROWN,
        LIGHT_GRAY,
        DARK_BLACK,
        DARK_RED,
        DARK_GREEN,
        DARK_YELLOW,
        DARK_BLUE,
        DARK_MAGENTA,
        DARK_CYAN,
        DARK_WHITE,
        DARK_ORANGE,
        DARK_PINK,
        DARK_PURPLE,
        DARK_LIME,
        DARK_TEAL,
        DARK_OLIVE,
        DARK_BROWN,
        DARK_GRAY,
        VERY_DARK_BLACK,
        VERY_DARK_RED,
        VERY_DARK_GREEN,
        VERY_DARK_YELLOW,
        VERY_DARK_BLUE,
        VERY_DARK_MAGENTA,
        VERY_DARK_CYAN,
        VERY_DARK_WHITE,
        VERY_DARK_ORANGE,
        VERY_DARK_PINK,
        VERY_DARK_PURPLE,
        VERY_DARK_LIME,
        VERY_DARK_TEAL,
        VERY_DARK_OLIVE,
        VERY_DARK_BROWN,
        VERY_DARK_GRAY,
        NO_COLOR,
    };
    constexpr int N_SIZE = Color::NO_COLOR + 1;

    const std::string sColorNames[N_SIZE] = {
        "RESET",
        "BLACK",
        "RED",
        "GREEN",
        "YELLOW",
        "BLUE",
        "MAGENTA",
        "CYAN",
        "WHITE",
        "ORANGE",
        "PINK",
        "PURPLE",
        "LIME",
        "TEAL",
        "OLIVE",
        "BROWN",
        "GRAY",
        "BRIGHT_BLACK",
        "BRIGHT_RED",
        "BRIGHT_GREEN",
        "BRIGHT_YELLOW",
        "BRIGHT_BLUE",
        "BRIGHT_MAGENTA",
        "BRIGHT_CYAN",
        "BRIGHT_WHITE",
        "BRIGHT_ORANGE",
        "BRIGHT_PINK",
        "BRIGHT_PURPLE",
        "BRIGHT_LIME",
        "BRIGHT_TEAL",
        "BRIGHT_OLIVE",
        "BRIGHT_BROWN",
        "BRIGHT_GRAY",
        "VERY_LIGHT_BLACK",
        "VERY_LIGHT_RED",
        "VERY_LIGHT_GREEN",
        "VERY_LIGHT_YELLOW",
        "VERY_LIGHT_BLUE",
        "VERY_LIGHT_MAGENTA",
        "VERY_LIGHT_CYAN",
        "VERY_LIGHT_WHITE",
        "VERY_LIGHT_ORANGE",
        "VERY_LIGHT_PINK",
        "VERY_LIGHT_PURPLE",
        "VERY_LIGHT_LIME",
        "VERY_LIGHT_TEAL",
        "VERY_LIGHT_OLIVE",
        "VERY_LIGHT_BROWN",
        "VERY_LIGHT_GRAY",
        "LIGHT_BLACK",
        "LIGHT_RED",
        "LIGHT_GREEN",
        "LIGHT_YELLOW",
        "LIGHT_BLUE",
        "LIGHT_MAGENTA",
        "LIGHT_CYAN",
        "LIGHT_WHITE",
        "LIGHT_ORANGE",
        "LIGHT_PINK",
        "LIGHT_PURPLE",
        "LIGHT_LIME",
        "LIGHT_TEAL",
        "LIGHT_OLIVE",
        "LIGHT_BROWN",
        "LIGHT_GRAY",
        "DARK_BLACK",
        "DARK_RED",
        "DARK_GREEN",
        "DARK_YELLOW",
        "DARK_BLUE",
        "DARK_MAGENTA",
        "DARK_CYAN",
        "DARK_WHITE",
        "DARK_ORANGE",
        "DARK_PINK",
        "DARK_PURPLE",
        "DARK_LIME",
        "DARK_TEAL",
        "DARK_OLIVE",
        "DARK_BROWN",
        "DARK_GRAY",
        "VERY_DARK_BLACK",
        "VERY_DARK_RED",
        "VERY_DARK_GREEN",
        "VERY_DARK_YELLOW",
        "VERY_DARK_BLUE",
        "VERY_DARK_MAGENTA",
        "VERY_DARK_CYAN",
        "VERY_DARK_WHITE",
        "VERY_DARK_ORANGE",
        "VERY_DARK_PINK",
        "VERY_DARK_PURPLE",
        "VERY_DARK_LIME",
        "VERY_DARK_TEAL",
        "VERY_DARK_OLIVE",
        "VERY_DARK_BROWN",
        "VERY_DARK_GRAY"
        "NO_COLOR"
    };
}

/// Compile time console text color values
namespace text
{
    // Reset
    constexpr const char* RESET = "\033[0m";
    // Text color
    constexpr const char* BLACK = "\033[30m";
    constexpr const char* RED = "\033[31m";
    constexpr const char* GREEN = "\033[32m";
    constexpr const char* YELLOW = "\033[33m";
    constexpr const char* BLUE = "\033[34m";
    constexpr const char* MAGENTA = "\033[35m";
    constexpr const char* CYAN = "\033[36m";
    constexpr const char* WHITE = "\033[37m";
    constexpr const char* ORANGE = "\033[38;5;208m";
    constexpr const char* PINK = "\033[38;5;200m";
    constexpr const char* PURPLE = "\033[38;5;171m";
    constexpr const char* LIME = "\033[38;5;154m";
    constexpr const char* TEAL = "\033[38;5;30m";
    constexpr const char* OLIVE = "\033[38;5;58m";
    constexpr const char* BROWN = "\033[38;5;130m";
    constexpr const char* GRAY = "\033[90m";
    // Bright text color
    constexpr const char* BRIGHT_BLACK = "\033[1;30m";
    constexpr const char* BRIGHT_RED = "\033[1;31m";
    constexpr const char* BRIGHT_GREEN = "\033[1;32m";
    constexpr const char* BRIGHT_YELLOW = "\033[1;33m";
    constexpr const char* BRIGHT_BLUE = "\033[1;34m";
    constexpr const char* BRIGHT_MAGENTA = "\033[1;35m";
    constexpr const char* BRIGHT_CYAN = "\033[1;36m";
    constexpr const char* BRIGHT_WHITE = "\033[1;37m";
    constexpr const char* BRIGHT_ORANGE = "\033[1;38;5;208m";
    constexpr const char* BRIGHT_PINK = "\033[1;38;5;200m";
    constexpr const char* BRIGHT_PURPLE = "\033[1;38;5;171m";
    constexpr const char* BRIGHT_LIME = "\033[1;38;5;154m";
    constexpr const char* BRIGHT_TEAL = "\033[1;38;5;30m";
    constexpr const char* BRIGHT_OLIVE = "\033[1;38;5;58m";
    constexpr const char* BRIGHT_BROWN = "\033[1;38;5;130m";
    constexpr const char* BRIGHT_GRAY = "\033[1;90m";
    // Very light text Colors
    constexpr const char* VERY_LIGHT_BLACK = "\033[38;2;128;128;128m";
    constexpr const char* VERY_LIGHT_RED = "\033[38;2;255;204;204m";
    constexpr const char* VERY_LIGHT_GREEN = "\033[38;2;204;255;204m";
    constexpr const char* VERY_LIGHT_YELLOW = "\033[38;2;255;255;204m";
    constexpr const char* VERY_LIGHT_BLUE = "\033[38;2;204;204;255m";
    constexpr const char* VERY_LIGHT_MAGENTA = "\033[38;2;255;204;255m";
    constexpr const char* VERY_LIGHT_CYAN = "\033[38;2;204;255;255m";
    constexpr const char* VERY_LIGHT_WHITE = "\033[38;2;255;255;255m";
    constexpr const char* VERY_LIGHT_ORANGE = "\033[38;2;255;165;0m";
    constexpr const char* VERY_LIGHT_PINK = "\033[38;2;255;182;193m";
    constexpr const char* VERY_LIGHT_PURPLE = "\033[38;2;230;230;250m";
    constexpr const char* VERY_LIGHT_LIME = "\033[38;2;144;238;144m";
    constexpr const char* VERY_LIGHT_TEAL = "\033[38;2;0;128;128m";
    constexpr const char* VERY_LIGHT_OLIVE = "\033[38;2;128;128;0m";
    constexpr const char* VERY_LIGHT_BROWN = "\033[38;2;165;42;42m";
    constexpr const char* VERY_LIGHT_GRAY = "\033[38;2;169;169;169m";
    // Light text Colors
    constexpr const char* LIGHT_BLACK = "\033[38;2;64;64;64m";
    constexpr const char* LIGHT_RED = "\033[38;2;255;102;102m";
    constexpr const char* LIGHT_GREEN = "\033[38;2;102;255;102m";
    constexpr const char* LIGHT_YELLOW = "\033[38;2;255;255;102m";
    constexpr const char* LIGHT_BLUE = "\033[38;2;102;102;255m";
    constexpr const char* LIGHT_MAGENTA = "\033[38;2;255;102;255m";
    constexpr const char* LIGHT_CYAN = "\033[38;2;102;255;255m";
    constexpr const char* LIGHT_WHITE = "\033[38;2;223;223;223m";
    constexpr const char* LIGHT_ORANGE = "\033[38;2;255;140;0m";
    constexpr const char* LIGHT_PINK = "\033[38;2;255;182;193m";
    constexpr const char* LIGHT_PURPLE = "\033[38;2;218;112;214m";
    constexpr const char* LIGHT_LIME = "\033[38;2;144;238;144m";
    constexpr const char* LIGHT_TEAL = "\033[38;2;0;128;128m";
    constexpr const char* LIGHT_OLIVE = "\033[38;2;128;128;0m";
    constexpr const char* LIGHT_BROWN = "\033[38;2;165;42;42m";
    constexpr const char* LIGHT_GRAY = "\033[38;2;192;192;192m";
    // Dark text colors
    constexpr const char* DARK_BLACK = "\033[38;2;32;32;32m";
    constexpr const char* DARK_RED = "\033[38;2;128;0;0m";
    constexpr const char* DARK_GREEN = "\033[38;2;0;128;0m";
    constexpr const char* DARK_YELLOW = "\033[38;2;128;128;0m";
    constexpr const char* DARK_BLUE = "\033[38;2;0;0;128m";
    constexpr const char* DARK_MAGENTA = "\033[38;2;128;0;128m";
    constexpr const char* DARK_CYAN = "\033[38;2;0;128;128m";
    constexpr const char* DARK_WHITE = "\033[38;2;192;192;192m";
    constexpr const char* DARK_ORANGE = "\033[38;2;255;69;0m";
    constexpr const char* DARK_PINK = "\033[38;2;255;20;147m";
    constexpr const char* DARK_PURPLE = "\033[38;2;148;0;211m";
    constexpr const char* DARK_LIME = "\033[38;2;50;205;50m";
    constexpr const char* DARK_TEAL = "\033[38;2;0;128;128m";
    constexpr const char* DARK_OLIVE = "\033[38;2;128;128;0m";
    constexpr const char* DARK_BROWN = "\033[38;2;139;69;19m";
    constexpr const char* DARK_GRAY = "\033[38;2;105;105;105m";
    // Very dark text colors
    constexpr const char* VERY_DARK_BLACK = "\033[38;2;16;16;16m";
    constexpr const char* VERY_DARK_RED = "\033[38;2;64;0;0m";
    constexpr const char* VERY_DARK_GREEN = "\033[38;2;0;64;0m";
    constexpr const char* VERY_DARK_YELLOW = "\033[38;2;64;64;0m";
    constexpr const char* VERY_DARK_BLUE = "\033[38;2;0;0;64m";
    constexpr const char* VERY_DARK_MAGENTA = "\033[38;2;64;0;64m";
    constexpr const char* VERY_DARK_CYAN = "\033[38;2;0;64;64m";
    constexpr const char* VERY_DARK_WHITE = "\033[38;2;128;128;128m";
    constexpr const char* VERY_DARK_ORANGE = "\033[38;2;255;69;0m";
    constexpr const char* VERY_DARK_PINK = "\033[38;2;219;112;147m";
    constexpr const char* VERY_DARK_PURPLE = "\033[38;2;148;0;211m";
    constexpr const char* VERY_DARK_LIME = "\033[38;2;34;139;34m";
    constexpr const char* VERY_DARK_TEAL = "\033[38;2;0;128;128m";
    constexpr const char* VERY_DARK_OLIVE = "\033[38;2;128;128;0m";
    constexpr const char* VERY_DARK_BROWN = "\033[38;2;139;69;19m";
    constexpr const char* VERY_DARK_GRAY = "\033[38;2;64;64;64m";
    // Special colors
    constexpr const char* NO_COLOR = RESET;
}

namespace text
{
    // Array of color codes corresponding to the Color enum
    constexpr const char* S_COLORS[console::N_SIZE] = {
        RESET,
        BLACK,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE,
        ORANGE,
        PINK,
        PURPLE,
        LIME,
        TEAL,
        OLIVE,
        BROWN,
        GRAY,
        BRIGHT_BLACK,
        BRIGHT_RED,
        BRIGHT_GREEN,
        BRIGHT_YELLOW,
        BRIGHT_BLUE,
        BRIGHT_MAGENTA,
        BRIGHT_CYAN,
        BRIGHT_WHITE,
        BRIGHT_ORANGE,
        BRIGHT_PINK,
        BRIGHT_PURPLE,
        BRIGHT_LIME,
        BRIGHT_TEAL,
        BRIGHT_OLIVE,
        BRIGHT_BROWN,
        BRIGHT_GRAY,
        VERY_LIGHT_BLACK,
        VERY_LIGHT_RED,
        VERY_LIGHT_GREEN,
        VERY_LIGHT_YELLOW,
        VERY_LIGHT_BLUE,
        VERY_LIGHT_MAGENTA,
        VERY_LIGHT_CYAN,
        VERY_LIGHT_WHITE,
        VERY_LIGHT_ORANGE,
        VERY_LIGHT_PINK,
        VERY_LIGHT_PURPLE,
        VERY_LIGHT_LIME,
        VERY_LIGHT_TEAL,
        VERY_LIGHT_OLIVE,
        VERY_LIGHT_BROWN,
        VERY_LIGHT_GRAY,
        LIGHT_BLACK,
        LIGHT_RED,
        LIGHT_GREEN,
        LIGHT_YELLOW,
        LIGHT_BLUE,
        LIGHT_MAGENTA,
        LIGHT_CYAN,
        LIGHT_WHITE,
        LIGHT_ORANGE,
        LIGHT_PINK,
        LIGHT_PURPLE,
        LIGHT_LIME,
        LIGHT_TEAL,
        LIGHT_OLIVE,
        LIGHT_BROWN,
        LIGHT_GRAY,
        DARK_BLACK,
        DARK_RED,
        DARK_GREEN,
        DARK_YELLOW,
        DARK_BLUE,
        DARK_MAGENTA,
        DARK_CYAN,
        DARK_WHITE,
        DARK_ORANGE,
        DARK_PINK,
        DARK_PURPLE,
        DARK_LIME,
        DARK_TEAL,
        DARK_OLIVE,
        DARK_BROWN,
        DARK_GRAY,
        VERY_DARK_BLACK,
        VERY_DARK_RED,
        VERY_DARK_GREEN,
        VERY_DARK_YELLOW,
        VERY_DARK_BLUE,
        VERY_DARK_MAGENTA,
        VERY_DARK_CYAN,
        VERY_DARK_WHITE,
        VERY_DARK_ORANGE,
        VERY_DARK_PINK,
        VERY_DARK_PURPLE,
        VERY_DARK_LIME,
        VERY_DARK_TEAL,
        VERY_DARK_OLIVE,
        VERY_DARK_BROWN,
        VERY_DARK_GRAY,
        NO_COLOR
    };
}

/// Compile time console background color values
namespace background
{
    // Reset
    constexpr const char* RESET = "\033[49m";
    // Background color
    constexpr const char* BLACK = "\033[40m";
    constexpr const char* RED = "\033[41m";
    constexpr const char* GREEN = "\033[42m";
    constexpr const char* YELLOW = "\033[43m";
    constexpr const char* BLUE = "\033[44m";
    constexpr const char* MAGENTA = "\033[45m";
    constexpr const char* CYAN = "\033[46m";
    constexpr const char* WHITE = "\033[47m";
    constexpr const char* ORANGE = "\033[48;5;208m";
    constexpr const char* PINK = "\033[48;5;200m";
    constexpr const char* PURPLE = "\033[48;5;171m";
    constexpr const char* LIME = "\033[48;5;154m";
    constexpr const char* TEAL = "\033[48;5;30m";
    constexpr const char* OLIVE = "\033[48;5;58m";
    constexpr const char* BROWN = "\033[48;5;130m";
    constexpr const char* GRAY = "\033[48;5;245m";  // Adjusted to a lighter gray
    // Bright background color
    constexpr const char* BRIGHT_BLACK = "\033[100m";
    constexpr const char* BRIGHT_RED = "\033[101m";
    constexpr const char* BRIGHT_GREEN = "\033[102m";
    constexpr const char* BRIGHT_YELLOW = "\033[103m";
    constexpr const char* BRIGHT_BLUE = "\033[104m";
    constexpr const char* BRIGHT_MAGENTA = "\033[105m";
    constexpr const char* BRIGHT_CYAN = "\033[106m";
    constexpr const char* BRIGHT_WHITE = "\033[107m";
    constexpr const char* BRIGHT_ORANGE = "\033[48;5;208;1m";
    constexpr const char* BRIGHT_PINK = "\033[48;5;200;1m";
    constexpr const char* BRIGHT_PURPLE = "\033[48;5;171;1m";
    constexpr const char* BRIGHT_LIME = "\033[48;5;154;1m";
    constexpr const char* BRIGHT_TEAL = "\033[48;5;30;1m";
    constexpr const char* BRIGHT_OLIVE = "\033[48;5;58;1m";
    constexpr const char* BRIGHT_BROWN = "\033[48;5;130;1m";
    constexpr const char* BRIGHT_GRAY = "\033[48;5;245;1m";
    // Very light background color
    constexpr const char* VERY_LIGHT_BLACK = "\033[48;2;128;128;128m";
    constexpr const char* VERY_LIGHT_RED = "\033[48;2;255;204;204m";
    constexpr const char* VERY_LIGHT_GREEN = "\033[48;2;204;255;204m";
    constexpr const char* VERY_LIGHT_YELLOW = "\033[48;2;255;255;204m";
    constexpr const char* VERY_LIGHT_BLUE = "\033[48;2;204;204;255m";
    constexpr const char* VERY_LIGHT_MAGENTA = "\033[48;2;255;204;255m";
    constexpr const char* VERY_LIGHT_CYAN = "\033[48;2;204;255;255m";
    constexpr const char* VERY_LIGHT_WHITE = "\033[48;2;255;255;255m";
    constexpr const char* VERY_LIGHT_ORANGE = "\033[48;2;255;165;0m";
    constexpr const char* VERY_LIGHT_PINK = "\033[48;2;255;182;193m";
    constexpr const char* VERY_LIGHT_PURPLE = "\033[48;2;230;230;250m";
    constexpr const char* VERY_LIGHT_LIME = "\033[48;2;144;238;144m";
    constexpr const char* VERY_LIGHT_TEAL = "\033[48;2;0;128;128m";
    constexpr const char* VERY_LIGHT_OLIVE = "\033[48;2;128;128;0m";
    constexpr const char* VERY_LIGHT_BROWN = "\033[48;2;165;42;42m";
    constexpr const char* VERY_LIGHT_GRAY = "\033[48;2;169;169;169m";
    // Light background color
    constexpr const char* LIGHT_BLACK = "\033[48;2;64;64;64m";
    constexpr const char* LIGHT_RED = "\033[48;2;255;102;102m";
    constexpr const char* LIGHT_GREEN = "\033[48;2;102;255;102m";
    constexpr const char* LIGHT_YELLOW = "\033[48;2;255;255;102m";
    constexpr const char* LIGHT_BLUE = "\033[48;2;102;102;255m";
    constexpr const char* LIGHT_MAGENTA = "\033[48;2;255;102;255m";
    constexpr const char* LIGHT_CYAN = "\033[48;2;102;255;255m";
    constexpr const char* LIGHT_WHITE = "\033[48;2;223;223;223m";
    constexpr const char* LIGHT_ORANGE = "\033[48;2;255;140;0m";
    constexpr const char* LIGHT_PINK = "\033[48;2;255;182;193m";
    constexpr const char* LIGHT_PURPLE = "\033[48;2;218;112;214m";
    constexpr const char* LIGHT_LIME = "\033[48;2;144;238;144m";
    constexpr const char* LIGHT_TEAL = "\033[48;2;0;128;128m";
    constexpr const char* LIGHT_OLIVE = "\033[48;2;128;128;0m";
    constexpr const char* LIGHT_BROWN = "\033[48;2;165;42;42m";
    constexpr const char* LIGHT_GRAY = "\033[48;2;192;192;192m";
    // Dark background color
    constexpr const char* DARK_BLACK = "\033[48;2;32;32;32m";
    constexpr const char* DARK_RED = "\033[48;2;128;0;0m";
    constexpr const char* DARK_GREEN = "\033[48;2;0;128;0m";
    constexpr const char* DARK_YELLOW = "\033[48;2;128;128;0m";
    constexpr const char* DARK_BLUE = "\033[48;2;0;0;128m";
    constexpr const char* DARK_MAGENTA = "\033[48;2;128;0;128m";
    constexpr const char* DARK_CYAN = "\033[48;2;0;128;128m";
    constexpr const char* DARK_WHITE = "\033[48;2;192;192;192m";
    constexpr const char* DARK_ORANGE = "\033[48;2;255;69;0m";
    constexpr const char* DARK_PINK = "\033[48;2;255;20;147m";
    constexpr const char* DARK_PURPLE = "\033[48;2;148;0;211m";
    constexpr const char* DARK_LIME = "\033[48;2;50;205;50m";
    constexpr const char* DARK_TEAL = "\033[48;2;0;128;128m";
    constexpr const char* DARK_OLIVE = "\033[48;2;128;128;0m";
    constexpr const char* DARK_BROWN = "\033[48;2;139;69;19m";
    constexpr const char* DARK_GRAY = "\033[48;2;105;105;105m";
    // Very dark background color
    constexpr const char* VERY_DARK_BLACK = "\033[48;2;16;16;16m";
    constexpr const char* VERY_DARK_RED = "\033[48;2;64;0;0m";
    constexpr const char* VERY_DARK_GREEN = "\033[48;2;0;64;0m";
    constexpr const char* VERY_DARK_YELLOW = "\033[48;2;64;64;0m";
    constexpr const char* VERY_DARK_BLUE = "\033[48;2;0;0;64m";
    constexpr const char* VERY_DARK_MAGENTA = "\033[48;2;64;0;64m";
    constexpr const char* VERY_DARK_CYAN = "\033[48;2;0;64;64m";
    constexpr const char* VERY_DARK_WHITE = "\033[48;2;128;128;128m";
    constexpr const char* VERY_DARK_ORANGE = "\033[48;2;255;69;0m";
    constexpr const char* VERY_DARK_PINK = "\033[48;2;219;112;147m";
    constexpr const char* VERY_DARK_PURPLE = "\033[48;2;148;0;211m";
    constexpr const char* VERY_DARK_LIME = "\033[48;2;34;139;34m";
    constexpr const char* VERY_DARK_TEAL = "\033[48;2;0;128;128m";
    constexpr const char* VERY_DARK_OLIVE = "\033[48;2;128;128;0m";
    constexpr const char* VERY_DARK_BROWN = "\033[48;2;139;69;19m";
    constexpr const char* VERY_DARK_GRAY = "\033[48;2;64;64;64m";
    // Special colors
    constexpr const char* NO_COLOR = RESET;
}

namespace background
{
    // Array of color codes corresponding to the Color enum
    constexpr const char* S_COLORS[console::N_SIZE] = {
        RESET,
        BLACK,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE,
        ORANGE,
        PINK,
        PURPLE,
        LIME,
        TEAL,
        OLIVE,
        BROWN,
        GRAY,
        BRIGHT_BLACK,
        BRIGHT_RED,
        BRIGHT_GREEN,
        BRIGHT_YELLOW,
        BRIGHT_BLUE,
        BRIGHT_MAGENTA,
        BRIGHT_CYAN,
        BRIGHT_WHITE,
        BRIGHT_ORANGE,
        BRIGHT_PINK,
        BRIGHT_PURPLE,
        BRIGHT_LIME,
        BRIGHT_TEAL,
        BRIGHT_OLIVE,
        BRIGHT_BROWN,
        BRIGHT_GRAY,
        VERY_LIGHT_BLACK,
        VERY_LIGHT_RED,
        VERY_LIGHT_GREEN,
        VERY_LIGHT_YELLOW,
        VERY_LIGHT_BLUE,
        VERY_LIGHT_MAGENTA,
        VERY_LIGHT_CYAN,
        VERY_LIGHT_WHITE,
        VERY_LIGHT_ORANGE,
        VERY_LIGHT_PINK,
        VERY_LIGHT_PURPLE,
        VERY_LIGHT_LIME,
        VERY_LIGHT_TEAL,
        VERY_LIGHT_OLIVE,
        VERY_LIGHT_BROWN,
        VERY_LIGHT_GRAY,
        LIGHT_BLACK,
        LIGHT_RED,
        LIGHT_GREEN,
        LIGHT_YELLOW,
        LIGHT_BLUE,
        LIGHT_MAGENTA,
        LIGHT_CYAN,
        LIGHT_WHITE,
        LIGHT_ORANGE,
        LIGHT_PINK,
        LIGHT_PURPLE,
        LIGHT_LIME,
        LIGHT_TEAL,
        LIGHT_OLIVE,
        LIGHT_BROWN,
        LIGHT_GRAY,
        DARK_BLACK,
        DARK_RED,
        DARK_GREEN,
        DARK_YELLOW,
        DARK_BLUE,
        DARK_MAGENTA,
        DARK_CYAN,
        DARK_WHITE,
        DARK_ORANGE,
        DARK_PINK,
        DARK_PURPLE,
        DARK_LIME,
        DARK_TEAL,
        DARK_OLIVE,
        DARK_BROWN,
        DARK_GRAY,
        VERY_DARK_BLACK,
        VERY_DARK_RED,
        VERY_DARK_GREEN,
        VERY_DARK_YELLOW,
        VERY_DARK_BLUE,
        VERY_DARK_MAGENTA,
        VERY_DARK_CYAN,
        VERY_DARK_WHITE,
        VERY_DARK_ORANGE,
        VERY_DARK_PINK,
        VERY_DARK_PURPLE,
        VERY_DARK_LIME,
        VERY_DARK_TEAL,
        VERY_DARK_OLIVE,
        VERY_DARK_BROWN,
        VERY_DARK_GRAY,
        NO_COLOR
    };
}

#endif // U_CONSOLE_COLOR_H