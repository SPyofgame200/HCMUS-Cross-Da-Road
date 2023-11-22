#include "uConsoleColor.h"
#include "gPixel.h"
#include <cmath>

namespace console
{
    int ClosestColor(int r, int g, int b) {
        int gray = static_cast<int>(std::round(0.299 * r + 0.587 * g + 0.114 * b));

        constexpr int ANSI_BLACK = 30;
        constexpr int ANSI_WHITE = 97;

        int closestCode = ANSI_BLACK + static_cast<int>((static_cast<double>(gray) / 255) * (ANSI_WHITE - ANSI_BLACK));

        return closestCode;
    }

    std::string GetTextColor(const app::Pixel& pixel) {
        int colorCode = ClosestColor(pixel.r, pixel.g, pixel.b);
        return "\033[38;5;" + std::to_string(colorCode) + "m";
    }

    std::string SetBackgroundColor(const app::Pixel& pixel) {
        int colorCode = ClosestColor(pixel.r, pixel.g, pixel.b);
        return "\033[48;5;" + std::to_string(colorCode) + "m";
    }

    std::string SetTextColor() {
        return text::RESET;
    }

    std::string SetBackgroundColor() {
        return background::RESET;
    }
}