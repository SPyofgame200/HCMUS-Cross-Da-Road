#include "uConsoleColor.h"
#include "gPixel.h"

//=================================================================================================
// Include new header files here

//=================================================================================================

namespace console
{
    int ClosestColor(int r, int g, int b) {
	    const int gray = static_cast<int>(std::round(0.299 * r + 0.587 * g + 0.114 * b));

        constexpr int ANSI_BLACK = 30;
        constexpr int ANSI_WHITE = 97;

	    const int closestCode = ANSI_BLACK + static_cast<int>((static_cast<double>(gray) / 255) * (ANSI_WHITE - ANSI_BLACK));

        return closestCode;
    }

    std::string TextColor(const app::Pixel& pixel) {
	    const int colorCode = ClosestColor(pixel.r, pixel.g, pixel.b);
        return "\033[38;5;" + std::to_string(colorCode) + "m";
    }

    std::string TextColor(int r, int g, int b) {
	    const int colorCode = ClosestColor(r, g, b);
        return "\033[38;5;" + std::to_string(colorCode) + "m";
    }

    std::string BackgroundColor(const app::Pixel& pixel) {
	    const int colorCode = ClosestColor(pixel.r, pixel.g, pixel.b);
        return "\033[48;5;" + std::to_string(colorCode) + "m";
    }

    std::string BackgroundColor(int r, int g, int b) {
	    const int colorCode = ClosestColor(r, g, b);
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
        for (int id = 1; id < console::N_SIZE; id++)
        {
            std::cout << text::S_COLORS[id] << console::sColorNames[id] << text::RESET;
            std::cout << " - ";
            std::cout << background::S_COLORS[id] << console::sColorNames[id] << background::RESET;
            std::cout << std::endl;
        }
        std::cout << text::RESET << '\n';
    }

    void ShowConsoleTextColor()
    {
        std::cout << "Text Colors:\n";
        for (int id = 1; id < console::N_SIZE; id++)
        {
            std::cout << text::S_COLORS[id] << console::sColorNames[id];
            std::cout << text::RESET << std::endl;
        }
        std::cout << text::RESET << '\n';
    }

    void ShowConsoleBackgroundColor()
    {
        std::cout << "Background Colors:\n";
        for (int id = 1; id < console::N_SIZE; id++)
        {
            std::cout << background::S_COLORS[id] << console::sColorNames[id];
            std::cout << background::RESET << std::endl;
        }
        std::cout << background::RESET << '\n';
    }
}