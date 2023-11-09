#ifndef G_SPRITE_H
#define G_SPRITE_H

#include <string>
#include "gResourcePack.h"
#include "gConst.h"

/**
 * @file gSprite.h
 *
 * @brief Contains sprite class
 *
 * This file contains sprite class for storing and manipulating sprites.
**/

namespace app
{
	/// @brief  Class for storing and manipulating sprites
	class Sprite
	{
	private:
		int32_t width = 0;  ///< Width of the sprite
		int32_t height = 0; ///< Height of the sprite

		/// @brief Enumeration of modes in game (for graphics)
		enum Mode
		{
			NORMAL,  ///< Normal mode (default) - no blending is performed (alpha is ignored)
			PERIODIC ///< Periodic mode - the sprite is repeated if it is drawn outside of the bounds of the sprite
		};

	private:
		Pixel* pColData = nullptr;      ///< Pointer to the pixel data
		Mode modeSample = Mode::NORMAL; ///< Mode for sampling outside the bounds of the sprite (default is NORMAL)

	public: // Constructors & Destructor
		Sprite();
		Sprite(const std::string& sImageFile);
		Sprite(const std::string& sImageFile, app::ResourcePack* pack);
		Sprite(int32_t w, int32_t h);
		~Sprite();

	public: // Loaders & Savers
		engine::Code ReadData(std::istream& is);
		engine::Code LoadFromFile(const std::string& s_image_file, app::ResourcePack* pack = nullptr);
		engine::Code GetSpriteStream(std::istream& stream, const std::string& sImageFile, app::ResourcePack* pack);
		engine::Code LoadSpriteFile(const std::string& sImageFile, app::ResourcePack* pack = nullptr);
		engine::Code SaveSpriteFile(const std::string& sImageFile);

	public: // Setters
		void SetSampleMode(app::Sprite::Mode mode = app::Sprite::Mode::NORMAL);
		bool SetPixel(int32_t x, int32_t y, Pixel p) const;

	public: // Getters
		bool Inside(int32_t x, int32_t y) const;
		int32_t Width() const;
		int32_t Height() const;
		Pixel GetPixel(int32_t x, int32_t y) const;
		Pixel* GetData() const;
	};
}

#endif // G_SPRITE_H

