#ifndef U_CONSOLE_COLOR_H
#define U_CONSOLE_COLOR_H

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
    // Bright text color
    constexpr const char* BRIGHT_BLACK = "\033[1;30m";
    constexpr const char* BRIGHT_RED = "\033[1;31m";
    constexpr const char* BRIGHT_GREEN = "\033[1;32m";
    constexpr const char* BRIGHT_YELLOW = "\033[1;33m";
    constexpr const char* BRIGHT_BLUE = "\033[1;34m";
    constexpr const char* BRIGHT_MAGENTA = "\033[1;35m";
    constexpr const char* BRIGHT_CYAN = "\033[1;36m";
    constexpr const char* BRIGHT_WHITE = "\033[1;37m";
    // Additional text colors
    constexpr const char* ORANGE = "\033[38;5;208m";
    constexpr const char* PINK = "\033[38;5;200m";
    constexpr const char* PURPLE = "\033[38;5;171m";
    constexpr const char* LIME = "\033[38;5;154m";
    constexpr const char* TEAL = "\033[38;5;30m";
    constexpr const char* OLIVE = "\033[38;5;58m";
    constexpr const char* BROWN = "\033[38;5;130m";
    constexpr const char* GRAY = "\033[90m";
}

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
    // Bright blackground colors
    constexpr const char* BRIGHT_BLACK = "\033[1;40m";
    constexpr const char* BRIGHT_RED = "\033[1;41m";
    constexpr const char* BRIGHT_GREEN = "\033[1;42m";
    constexpr const char* BRIGHT_YELLOW = "\033[1;43m";
    constexpr const char* BRIGHT_BLUE = "\033[1;44m";
    constexpr const char* BRIGHT_MAGENTA = "\033[1;45m";
    constexpr const char* BRIGHT_CYAN = "\033[1;46m";
    constexpr const char* BRIGHT_WHITE = "\033[1;47m";
    // Additional background colors
    constexpr const char* ORANGE = "\033[48;5;208m";
    constexpr const char* PINK = "\033[48;5;200m";
    constexpr const char* PURPLE = "\033[48;5;171m";
    constexpr const char* LIME = "\033[48;5;154m";
    constexpr const char* TEAL = "\033[48;5;30m";
    constexpr const char* OLIVE = "\033[48;5;58m";
    constexpr const char* BROWN = "\033[48;5;130m";
    constexpr const char* GRAY = "\033[100m";
}

namespace app {
    struct Pixel;
}

#include <string>
namespace console
{
    int ClosestColor(int r, int g, int b);
    std::string GetTextColor(const app::Pixel& pixel);
    std::string SetBackgroundColor(const app::Pixel& pixel);
    std::string SetTextColor();
    std::string SetBackgroundColor();
}

#endif // U_CONSOLE_COLOR_H