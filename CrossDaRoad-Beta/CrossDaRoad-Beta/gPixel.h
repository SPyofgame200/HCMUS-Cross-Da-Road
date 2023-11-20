/**
 * @file gPixel.h
 *
 * @brief Contains pixel struct
 *
 * This file contains pixel struct for pixel object in game (for graphics).
**/

#ifndef G_PIXEL_H
#define G_PIXEL_H

#include <cstdint>
#include <iostream>


namespace app
{
    /// @brief Struct for pixel object in game (for graphics)
    struct Pixel
    {
        union
        {
            uint32_t n = 0xFF000000;
            struct
            {
                uint8_t r;
                uint8_t g;
                uint8_t b;
                uint8_t a;
            };
        };

        // Constructors
        Pixel();
        Pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255);
        Pixel(uint32_t p);

        /// @brief Enumeration of modes of pixel in game (for graphics)
        enum Mode
        {
            NORMAL,    ///< Normal mode (default) - no blending is performed (alpha is ignored)
            MASK,      ///< Mask mode - alpha is checked and if alpha is 0 then the pixel is not drawn
            ALPHA,     ///< Alpha mode - alpha is used to blend between the pixel and the background
            BACKGROUND ///< Background mode - alpha is used to blend between the pixel and the background
        };

        // Friend functions
        friend Pixel blend(const Pixel& LHS, const Pixel& RHS, float blendFactor);
        friend std::ostream& operator<<(std::ostream& os, const Pixel& pixel);
    };

    // Some constants for symbolic naming of Pixels
    static const Pixel
        VERY_LIGHT_GREY(255, 255, 255),
        LIGHT_GREY(223, 223, 223),
        GREY(192, 192, 192),
        DARK_GREY(128, 128, 128),
        VERY_DARK_GREY(64, 64, 64),

        VERY_LIGHT_RED(255, 204, 204),
        LIGHT_RED(255, 102, 102),
        RED(255, 0, 0),
        DARK_RED(128, 0, 0),
        VERY_DARK_RED(64, 0, 0),

        VERY_LIGHT_YELLOW(255, 255, 204),
        LIGHT_YELLOW(255, 255, 102),
        YELLOW(255, 255, 0),
        DARK_YELLOW(128, 128, 0),
        VERY_DARK_YELLOW(64, 64, 0),

        VERY_LIGHT_GREEN(204, 255, 204),
        LIGHT_GREEN(102, 255, 102),
        GREEN(0, 255, 0),
        DARK_GREEN(0, 128, 0),
        VERY_DARK_GREEN(0, 64, 0),

        VERY_LIGHT_CYAN(204, 255, 255),
        LIGHT_CYAN(102, 255, 255),
        CYAN(0, 255, 255),
        DARK_CYAN(0, 128, 128),
        VERY_DARK_CYAN(0, 64, 64),

        VERY_LIGHT_BLUE(204, 204, 255),
        LIGHT_BLUE(102, 102, 255),
        BLUE(0, 0, 255),
        DARK_BLUE(0, 0, 128),
        VERY_DARK_BLUE(0, 0, 64),

        VERY_LIGHT_MAGENTA(255, 204, 255),
        LIGHT_MAGENTA(255, 102, 255),
        MAGENTA(255, 0, 255),
        DARK_MAGENTA(128, 0, 128),
        VERY_DARK_MAGENTA(64, 0, 64),

        VERY_LIGHT_ORANGE(255, 221, 204),
        LIGHT_ORANGE(255, 193, 102),
        ORANGE(255, 165, 0),
        DARK_ORANGE(255, 140, 0),
        VERY_DARK_ORANGE(255, 69, 0),

        VERY_LIGHT_PURPLE(179, 0, 179),
        LIGHT_PURPLE(153, 0, 153),
        PURPLE(128, 0, 128),
        DARK_PURPLE(85, 0, 85),
        VERY_DARK_PURPLE(43, 0, 43),

        VERY_LIGHT_PINK(255, 204, 229),
        LIGHT_PINK(255, 153, 204),
        PINK(255, 105, 180),
        DARK_PINK(255, 20, 147),
        VERY_DARK_PINK(139, 0, 139),

        VERY_LIGHT_BROWN(229, 153, 153),
        LIGHT_BROWN(204, 102, 102),
        BROWN(165, 42, 42),
        DARK_BROWN(139, 69, 19),
        VERY_DARK_BROWN(101, 67, 33),

        VERY_LIGHT_TEAL(204, 229, 229),
        LIGHT_TEAL(102, 178, 178),
        TEAL(0, 128, 128),
        DARK_TEAL(0, 102, 102),
        VERY_DARK_TEAL(0, 51, 51),

        VERY_LIGHT_LIME(204, 255, 204),
        LIGHT_LIME(153, 255, 153),
        LIME(0, 255, 0),
        DARK_LIME(0, 204, 0),
        VERY_DARK_LIME(0, 153, 0),

        VERY_LIGHT_AQUA(204, 255, 255),
        LIGHT_AQUA(153, 255, 255),
        AQUA(0, 255, 255),
        DARK_AQUA(0, 204, 204),
        VERY_DARK_AQUA(0, 153, 153),

        VERY_LIGHT_OLIVE(229, 229, 153),
        LIGHT_OLIVE(178, 178, 102),
        OLIVE(128, 128, 0),
        DARK_OLIVE(102, 102, 0),
        VERY_DARK_OLIVE(51, 51, 0),

        VERY_LIGHT_MAROON(229, 153, 153),
        LIGHT_MAROON(178, 102, 102),
        MAROON(128, 0, 0),
        DARK_MAROON(102, 0, 0),
        VERY_DARK_MAROON(51, 0, 0),

        WHITE(255, 255, 255),
        BLACK(0, 0, 0),
        BLANK(0, 0, 0, 0);
}

#endif // G_PIXEL_H
