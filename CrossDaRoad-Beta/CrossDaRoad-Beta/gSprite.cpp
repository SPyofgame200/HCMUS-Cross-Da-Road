/**
 * @file gSprite.h
 *
 * @brief Contains sprite class implementation
 *
 * This file implement sprite class for sprite management (load, save, etc.).
**/

#include "gSprite.h"
#include "gUtils.h"

#include <Windows.h>
#include <algorithm>
#include <cwchar>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Graphic Interface
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "gdiplus.lib")
#include <gdiplus.h>

#undef min
#undef max



namespace app
{
	/// @brief Static class for GDI+ initialization and conversion from GDI+ color to Pixel color
	static class GDIP
	{
	public:
		/// @brief Constructor for the GDIP class
		GDIP()
		{
			// Initialize GDI+ (required for loading images)
			const Gdiplus::GdiplusStartupInput startupInput;
			ULONG_PTR token;

			Gdiplus::GdiplusStartup(&token, &startupInput, nullptr);
		}

		/// @brief Convert pixel color from GDI+ to Pixel
		/// @param pixelColor  GDI+ color
		/// @return Pixel color (r, g, b, a)
		static Pixel to_pixel(const Gdiplus::Color& pixelColor)
		{
			return { pixelColor.GetRed(), pixelColor.GetGreen(), pixelColor.GetBlue(), pixelColor.GetAlpha() };
		}
	} gdistartup;


	//////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////// CONSTRUCTORS & DESTRUCTOR ////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor
	Sprite::Sprite()
	{
		pColData = nullptr;
		width = 0;
		height = 0;
	}

	/// @brief Parameterized constructor with image
	/// @param imageFilePath Image file path
	Sprite::Sprite(const std::string& imageFilePath)
	{
		LoadFromFile(imageFilePath);
	}

	/// @brief Constructor with image and pack
	/// @param imageFilePath Image file path
	/// @param pack Resource pack
	Sprite::Sprite(const std::string& imageFilePath, app::ResourcePack* pack)
	{
		LoadSpriteFile(imageFilePath, pack);
	}

	/// @brief Constructor with size
	/// @param w Width of sprite
	/// @param h Height of sprite
	Sprite::Sprite(const int32_t w, const int32_t h)
	{
		delete[] pColData;

		if (w <= 0 || h <= 0) {
			width = 0;
			height = 0;
			pColData = nullptr;
			std::cerr << "Invalid sprite size (width = " << w << ", height = " << h << "), expected positive integer parameters" << std::endl;
		}
		else {
			width = w;
			height = h;
			pColData = new Pixel[width * height];
			if (pColData) {
				std::fill_n(pColData, width * height, Pixel());
			}
			else {
				std::cerr << "Failed to allocate memory for pColData" << std::endl;
			}
		}
	}

	/// @brief Destructor
	Sprite::~Sprite()
	{
		if (pColData) {
			delete pColData;
			pColData = nullptr;
		}
		std::cerr << "app::Sprite::~Sprite(): Successfully destructed" << std::endl;
	}

	//////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////// LOADERS & SAVERS ///////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////

	/// @brief Load sprite from file and pack
	/// @param imageFilePath Image file path
	/// @param pack Resource pack
	/// @return engine::Code engine::SUCCESS if sprite was loaded from file, engine::FAILURE otherwise
	engine::Code Sprite::LoadFromFile(const std::string& imageFilePath, app::ResourcePack* pack)
	{
		Gdiplus::Bitmap* bitmap = Gdiplus::Bitmap::FromFile(to_text(imageFilePath));
		if (bitmap == nullptr) {
			return engine::FILE_NOT_FOUND;
		}

		width = bitmap->GetWidth();
		if (width <= 0) {
			delete bitmap;
			return engine::INVALID_WIDTH;
		}

		height = bitmap->GetHeight();
		if (height <= 0) {
			delete bitmap;
			return engine::INVALID_HEIGHT;
		}

		pColData = new Pixel[width * height];
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				Gdiplus::Color pixelColor;
				bitmap->GetPixel(x, y, &pixelColor);
				SetPixel(x, y, GDIP::to_pixel(pixelColor));
			}
		}

		delete bitmap;
		return engine::SUCCESS;
	}

	/// @brief Reads the pixel data from the specified input stream into the sprite object
	/// @param is The input stream to read from
	/// @return The error code
	/// @retval engine::SUCCESS The pixel data was read successfully
	/// @retval engine::INVALID_WIDTH The width of the sprite is invalid
	/// @retval engine::INVALID_HEIGHT The height of the sprite is invalid
	/// @retval engine::INVALID_SIZE The size of the sprite is invalid
	/// @retval engine::INVALID_ALLOCATION The memory allocation for the sprite failed
	/// @retval engine::FILE_READ_ERROR The pixel data could not be read from the input stream
	/// @note The input stream should be opened in binary mode
	/// @note The input stream should be positioned at the start of the pixel data
	engine::Code Sprite::ReadData(std::istream& is)
	{
		// Read width
		is.read(reinterpret_cast<char*>(&width), sizeof(int32_t));
		if (is.fail()) {
			return engine::INVALID_WIDTH;
		}

		// Read height
		is.read(reinterpret_cast<char*>(&height), sizeof(int32_t));
		if (is.fail()) {
			return engine::INVALID_HEIGHT;
		}

		// Re-check the size
		if (width <= 0 || height <= 0) {
			return engine::INVALID_SIZE;
		}

		// Allocate memory for pColData
		pColData = new Pixel[width * height];
		if (pColData == nullptr) {
			return engine::INVALID_ALLOCATION;
		}

		// Read pixel data
		is.read(reinterpret_cast<char*>(pColData), width * height * sizeof(uint32_t));
		if (is.fail()) {
			delete[] pColData;
			pColData = nullptr;
			return engine::FILE_READ_ERROR;
		}

		return engine::SUCCESS;
	}

	/// @brief Gets the input stream for the specified image file
	/// @param stream The input stream to get
	///@param imageFilePath The path to the image file to load
	/// @param pack The resource pack to use
	/// @return The error code
	/// @retval engine::SUCCESS The input stream was retrieved successfully
	/// @retval engine::FAILURE The input stream could not be retrieved
	/// @note The input stream should be opened in binary mode
	engine::Code Sprite::GetSpriteStream(std::istream& stream, const std::string& imageFilePath, app::ResourcePack* pack)
	{
		if (pack) {
			auto streamBuffer = pack->GetStreamBuffer(imageFilePath);
			stream.rdbuf(&streamBuffer);
			return engine::SUCCESS;
		}
		const std::ifstream ifs(imageFilePath, std::ifstream::binary);
		if (ifs.is_open()) {
			stream.rdbuf(ifs.rdbuf());
			return engine::SUCCESS;
		}
		return engine::FAILURE;
	}

	/// @brief Loads the pixel data from the specified image file into the sprite
	/// @param imageFilePath The path to the image file to load
	/// @param pack The resource pack to use
	engine::Code Sprite::LoadSpriteFile(const std::string& imageFilePath, app::ResourcePack* pack)
	{
		if (pColData) {
			delete[] pColData;
			pColData = nullptr;
		}

		std::istream inputStream(nullptr);
		const engine::Code code = GetSpriteStream(inputStream, imageFilePath, pack);
		if (code == engine::SUCCESS) {
			ReadData(inputStream);
		}
		return code;
	}

	/// @brief  Saves the pixel data of the sprite to the specified file
	/// @param imageFilePath The path to the image file to save
	/// @return The error code
	/// @retval engine::SUCCESS The pixel data was saved successfully
	/// @retval engine::FAILURE The pixel data could not be saved
	engine::Code Sprite::SaveSpriteFile(const std::string& imageFilePath)
	{
		if (pColData == nullptr) {
			return engine::FAILURE;
		}

		std::ofstream ofs;
		ofs.open(imageFilePath, std::ifstream::binary);
		if (ofs.is_open()) {
			ofs.write(reinterpret_cast<char*>(&width), sizeof(int32_t));
			ofs.write(reinterpret_cast<char*>(&height), sizeof(int32_t));
			ofs.write(reinterpret_cast<char*>(pColData), width * height * sizeof(uint32_t));
			ofs.close();
			return engine::SUCCESS;
		}

		return engine::FAILURE;
	}

	//////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////// SETTERS /////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////

	/// @brief Sets the sample mode for the sprite
	/// @param mode The sample mode to set (NORMAL or PERIODIC)
	void Sprite::SetSampleMode(const app::Sprite::Mode mode)
	{
		modeSample = mode;
	}
	/// @brief Sets the pixel at the specified coordinates
	/// @param x x-coordinate of the pixel to set
	/// @param y y-coordinate of the pixel to set
	/// @param p Pixel to set
	bool Sprite::SetPixel(const int32_t x, const int32_t y, const Pixel p)
	{
		if (Inside(x, y)) {
			pColData[y * width + x] = p;
			return true;
		}
		return false;
	}

	//////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////// GETTERS /////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////

	/// @brief Checks if the specified coordinates are inside the bounds of the sprite
	/// @param x x-coordinate to check
	/// @param y y-coordinate to check
	/// @return true if the coordinates are inside the bounds of the sprite, false otherwise
	bool Sprite::Inside(int32_t x, int32_t y) const
	{
		return (x >= 0 && x < width && y >= 0 && y < height);
	}

	/// @brief Gets the width of the sprite
	int32_t Sprite::Width() const
	{
		return width;
	}

	/// @brief Gets the height of the sprite
	int32_t Sprite::Height() const
	{
		return height;
	}

	/// @brief Gets the pixel at the specified coordinates
	/// @param x  x-coordinate of the pixel to get
	/// @param y y-coordinate of the pixel to get
	/// @return Pixel at the specified coordinates
	Pixel Sprite::GetPixel(int32_t x, int32_t y) const
	{
		if (modeSample == app::Sprite::Mode::NORMAL) {
			if (Inside(x, y)) {
				return pColData[y * width + x];
			}
			return { 0, 0, 0, 0 };
		}
		return pColData[abs(y %= height) * width + abs(x %= width)];
	}

	/// @brief Gets the pixel data of the sprite
	/// @return Pointer to the pixel data
	Pixel* Sprite::GetData() const
	{
		return pColData;
	}

} // namespace app

//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// END OF FILE ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////