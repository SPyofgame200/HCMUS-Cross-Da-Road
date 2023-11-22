#include "uConsoleColor.h"
#include "gPixel.h"
#include <cmath>
#include <iomanip>

namespace console
{
    int ClosestColor(int r, int g, int b) {
        int gray = static_cast<int>(std::round(0.299 * r + 0.587 * g + 0.114 * b));

        constexpr int ANSI_BLACK = 30;
        constexpr int ANSI_WHITE = 97;

        int closestCode = ANSI_BLACK + static_cast<int>((static_cast<double>(gray) / 255) * (ANSI_WHITE - ANSI_BLACK));

        return closestCode;
    }

    std::string TextColor(const app::Pixel& pixel) {
        int colorCode = ClosestColor(pixel.r, pixel.g, pixel.b);
        return "\033[38;5;" + std::to_string(colorCode) + "m";
    }

    std::string BackgroundColor(const app::Pixel& pixel) {
        int colorCode = ClosestColor(pixel.r, pixel.g, pixel.b);
        return "\033[48;5;" + std::to_string(colorCode) + "m";
    }

    std::string ResetTextColor() {
        return text::RESET;
    }

    std::string ResetBackgroundColor() {
        return background::RESET;
    }

    void ShowConsoleColor()
    {
        std::cout << "Text Colors:\n";
        for (int i = 0; i < static_cast<int>(Color::VERY_DARK_BLACK); i++)
        {
            std::cout << text::S_COLORS[i] << console::sColorNames[i] << text::RESET;
            std::cout << " - ";
            std::cout << background::S_COLORS[i] << console::sColorNames[i] << background::RESET;
            std::cout << std::endl;
        }
        std::cout << text::RESET << '\n';
    }

    void ShowConsoleTextColor()
    {
        std::cout << "Text Colors:\n";
        for (int i = 0; i < static_cast<int>(Color::VERY_DARK_BLACK); i++)
        {
            std::cout << text::S_COLORS[i] << console::sColorNames[i];
            std::cout << text::RESET << std::endl;
        }
        std::cout << text::RESET << '\n';
    }

    void ShowConsoleBackgroundColor()
    {
        std::cout << "Background Colors:\n";
        for (int i = 0; i < static_cast<int>(Color::VERY_DARK_BLACK); i++)
        {
            std::cout << background::S_COLORS[i] << console::sColorNames[i];
            std::cout << background::RESET << std::endl;
        }
        std::cout << background::RESET << '\n';
    }
}