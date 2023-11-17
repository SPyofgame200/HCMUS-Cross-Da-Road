/**
 * @file gPixel.h
 *
 * @brief Contains pixel struct
 *
 * This file contains pixel struct for pixel object in game (for graphics) and its implementation.
**/

#include "gPixel.h"
#include <cstdint>



namespace app
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////// CONSTRUCTORS & DESTRUCTOR ///////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor 
	Pixel::Pixel()
	{
		r = 0;
		g = 0;
		b = 0;
		a = 255;
	}

	/// @brief Parameterized constructor
	/// @param red The red value
	/// @param green The green value
	/// @param blue The blue value
	/// @param alpha The alpha value
	Pixel::Pixel(const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t alpha)
	{
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}
	/// @brief Parameterized constructor
	/// @param p The pixel value
	Pixel::Pixel(const uint32_t p)
	{
		n = p;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////// FRIEND FUNCTIONS ///////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////

	/// @brief Blends two pixels together
	/// @param LHS Left hand side pixel
	/// @param RHS Right hand side pixel
	/// @param blendFactor The blend factor (0-255) 
	/// @return The blended pixel 
	Pixel blend(const Pixel& LHS, const Pixel& RHS, const float blendFactor)
	{
		const float oneMinusBlendFactor = 1.0f - blendFactor;

		uint8_t newR = static_cast<uint8_t>((LHS.r * blendFactor) + (RHS.r * oneMinusBlendFactor));
		uint8_t newG = static_cast<uint8_t>((LHS.g * blendFactor) + (RHS.g * oneMinusBlendFactor));
		uint8_t newB = static_cast<uint8_t>((LHS.b * blendFactor) + (RHS.b * oneMinusBlendFactor));
		uint8_t newA = static_cast<uint8_t>((LHS.a * blendFactor) + (RHS.a * oneMinusBlendFactor));

		return { newR, newG, newB, newA };
	}

	/// @brief Friend operator for outputting pixel to stream
	/// @param os The output stream
	/// @param pixel Pixel to output
	/// @return Output stream of pixel
	std::ostream& operator<<(std::ostream& os, const Pixel& pixel)
	{
		os << std::dec << "Pixel(r=" << static_cast<uint32_t>(pixel.r) << ", g=" << static_cast<uint32_t>(pixel.g) << ", b=" << static_cast<uint32_t>(pixel.b) << ", a=" << static_cast<uint32_t>(pixel.a) << ")";
		return os;
	}
} // namespace app

////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// END OF FILE //////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////