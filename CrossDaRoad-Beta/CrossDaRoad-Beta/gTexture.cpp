/**
 * @file gTexture.cpp
 *
 * @brief Contains texture class implementation
 *
 * This file implement texture class for texture management (rendering, etc.).
 **/

#include "gTexture.h"
#include <iostream>


namespace app
{
	///////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////// CONSTRUCTOR AND DESTRUCTOR /////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor
	Texture::Texture()
	{
		InitDevice();
	}
	/// @brief Parameterized constructor
	/// @param windowHandler The window handler for the window to draw on
	Texture::Texture(const HWND windowHandler)
	{
		InitDevice();
		CreateDeviceContext(windowHandler);
	}
	/// @brief Destructor
	Texture::~Texture()
	{
		ExitDevice();
		std::cerr << "app::Texture::~Texture(): Successfully destructed" << std::endl;
	}
	/// @brief Initialize the device context
	/// @return Always returns true by default
	bool Texture::InitDevice()
	{
		pDefaultDrawTarget = nullptr;
		pDrawTarget = nullptr;
		nPixelMode = Pixel::NORMAL;
		fBlendFactor = 1.0f;
		nDefaultWidth = 0;
		nDefaultHeight = 0;

		glDeviceContext = nullptr;
		glRenderContext = nullptr;
		glBuffer = 0;
		return true;
	}
	/// @brief Create the device context for the window to draw on
	/// @param windowHandler  The window handler for the window to draw on
	/// @return True if the device context was created successfully, false otherwise
	bool Texture::CreateDeviceContext(const HWND windowHandler)
	{
		glDeviceContext = GetDC(windowHandler);
		return glDeviceContext != nullptr;
	}
	/// @brief Exit the device context, releasing all resources
	/// @return Always returns true by default
	bool Texture::ExitDevice() const
	{
		wglDeleteContext(glRenderContext);
		return true;
	}

	///////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////// SETUP ENVIRONMENT //////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////

	/// @brief Setup the pixel format for the device context
	/// @return True if the pixel format was setup successfully, false otherwise
	bool Texture::SetupFormatter() const
	{
		// Define a combination of window and OpenGL flags
		constexpr DWORD WindowGraphicFlags = 0
			| PFD_DRAW_TO_WINDOW   // Allow drawing to a window
			| PFD_SUPPORT_OPENGL   // Support for OpenGL
			| PFD_DOUBLEBUFFER     // Enable double buffering for smoother rendering
			;

		// Define a PIXELFORMATDESCRIPTOR structure with specific configuration
		// options
		constexpr PIXELFORMATDESCRIPTOR descriptor = {
			sizeof(PIXELFORMATDESCRIPTOR), // Size of the structure
			1,                             // Version number
			WindowGraphicFlags,            // Window and OpenGL flags
			PFD_TYPE_RGBA,                 // Pixel format is RGBA
			32,                            // Color depth (32 bits per pixel)
			0, 0, 0, 0,					   // Color bits ignored
			0,							   // No alpha buffer
			0,							   // Shift bit ignored
			0, 0, 0, 0,					   // Accumulation buffer ignored
			0,							   // Accumulation bits ignored
			0, 0, 0, 0,					   // Depth and stencil buffers ignored
			PFD_MAIN_PLANE,				   // Main layer
			0,							   // Reserved
			0, 0, 0						   // Layer masks ignored
		};

		// Choose a pixel format that matches the specified configuration
		const int nPixelFormat = ChoosePixelFormat(glDeviceContext, &descriptor);
		if (!nPixelFormat) {
			std::cerr << "Error: Unable to choose pixel format" << std::endl;
			return false;
		}

		// Set the chosen pixel format for rendering
		if (!SetPixelFormat(glDeviceContext, nPixelFormat, &descriptor)) {
			std::cerr << "Error: Unable to set pixel format" << std::endl;
			return false;
		}

		return true;
	}
	/// @brief Setup rendering for the device context with the specified viewport
	/// @param viewport The viewport state for the rendering context
	/// @return true If rendering was setup successfully, false otherwise
	bool Texture::SetupRendering(const ViewportState viewport)
	{
		// Create an OpenGL rendering context associated with the device context
		glRenderContext = wglCreateContext(glDeviceContext);
		if (!glRenderContext) {
			std::cerr << "Error: Unable to create rendering context" << std::endl;
			return false;
		}

		// Make the created rendering context current for rendering
		if (!wglMakeCurrent(glDeviceContext, glRenderContext)) {
			std::cerr << "Error: Unable to make rendering context current" << std::endl;
			return false;
		}

		// Set the viewport for rendering based on the specified viewport state
		glViewport(
			viewport.GetX(),     // X-coordinate of the viewport's lower-left corner.
			viewport.GetY(),     // Y-coordinate of the viewport's lower-left corner.
			viewport.GetWidth(), // width of the viewport.
			viewport.GetHeight() // height of the viewport.
		);
		return true;
	}
	/// @brief Setup texturing for the rendering context, enabling 2D texturing
	/// @return true If texturing was setup successfully, false otherwise
	bool Texture::SetupTexturing()
	{
		// Get and initialize the function pointer for wglSwapInterval
		wglSwapInterval = reinterpret_cast<wglSwapInterval_t*>(
			wglGetProcAddress("wglSwapIntervalEXT"));

		// If wglSwapInterval is available, set it to 0 to disable V-Sync
		if (wglSwapInterval) {
			wglSwapInterval(0);
		}

		// Enable 2D texturing in OpenGL
		glEnable(GL_TEXTURE_2D);

		// Generate and bind a texture
		GLuint textureID;
		glGenTextures(1, &textureID);
		if (textureID == 0) {
			std::cerr << "Error: Unable to generate a texture" << std::endl;
			return false;
		}
		// Bind 2D texture with texture ID
		glBindTexture(GL_TEXTURE_2D, // target texture, which is 2D in this case.
			textureID      // texture ID to bind to the target.
		);

		// Set the texture magnification filter to GL_NEAREST
		glTexParameteri(
			GL_TEXTURE_2D,         // target texture (2D in this case).
			GL_TEXTURE_MAG_FILTER, // parameter to set (magnification filter).
			GL_NEAREST // filter mode, where GL_NEAREST means nearest-neighbor
					   // filtering.
		);

		// Set the texture minification filter to GL_NEAREST
		glTexParameteri(
			GL_TEXTURE_2D,         // target texture (2D in this case).
			GL_TEXTURE_MIN_FILTER, // parameter to set (minification filter).
			GL_NEAREST // filter mode, where GL_NEAREST means nearest-neighbor
					   // filtering.
		);

		return true;
	}
	/// @brief Setup the texture environment for the rendering context
	/// @param width width of the texture.
	/// @param height height of the texture.
	/// @return true If the texture environment was setup successfully, false
	bool Texture::SetupEnvironment(const int width, const int height) const
	{
		// Get the pixel data from the default draw target
		const Pixel* target = pDefaultDrawTarget->GetData();
		if (!target) {
			std::cerr << "Error: Unable to get valid target data" << std::endl;
			return false;
		}

		// Set the OpenGL texture environment mode to GL_DECAL
		glTexEnvf(
			GL_TEXTURE_ENV, // Specifies the target texture environment to modify.
			GL_TEXTURE_ENV_MODE, // Specifies that you're setting the texture
			// environment mode.
			GL_DECAL             // Set a mode (REPLACE, MODULATE, DECAL, BLEND, ADD)
					 //     GL_DECAL means the texture replaces the object's color.
		);

		// Specify the texture image data
		glTexImage2D(
			GL_TEXTURE_2D, // target texture type, which is 2D in this case.
			0,       // level of detail for the mipmap level (0 is the base level).
			GL_RGBA, // internal format of the texture, in this case, RGBA.
			width, height,    // width and height of the texture.
			0,                // border width (usually set to 0).
			GL_RGBA,          // format of the pixel data (RGBA).
			GL_UNSIGNED_BYTE, // data type of the pixel data (unsigned bytes).
			target            // source of the image data (the 'target' variable).
		);

		return true;
	}
	/// @brief Create a 2D texture with the specified width and height
	/// @param width Width of the texture
	/// @param height Height of the texture
	/// @param viewport The viewport state for the rendering context
	/// @return True if the texture was created successfully, false otherwise
	bool Texture::CreateTexture2D(const int width, const int height, const ViewportState viewport)
	{
		if (!SetupFormatter()) {
			std::cerr << "Texture::CreateTexture2D: Found an error in Texture::SetupFormatter()" << std::endl;
			return false;
		}
		if (!SetupRendering(viewport)) {
			std::cerr << "Texture::CreateTexture2D: Found an error in Texture::SetupRendering()" << std::endl;
			return false;
		}
		if (!SetupTexturing()) {
			std::cerr << "Texture::CreateTexture2D: Found an error in Texture::SetupTexturing()" << std::endl;
			return false;
		}
		if (!SetupEnvironment(width, height)) {
			std::cerr << "Texture::CreateTexture2D: Found an error in Texture::SetupEnvironment()" << std::endl;
			return false;
		}
		return true;
	}

	///////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////// UPDATER ///////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////

	/// @brief Set the viewport for rendering based on the specified viewport state
	/// @param viewport Viewport state for the rendering context
	void Texture::SetViewport(const ViewportState viewport)
	{
		glViewport(viewport.GetX(), viewport.GetY(), viewport.GetWidth(), viewport.GetHeight());
	}
	/// @brief Update the texture with new image data (subimage)
	/// @param width Width of the texture
	/// @param height Height of the texture
	/// @param data Pixel data for the texture
	void Texture::UpdateTexture(const int width, const int height, const Pixel* data)
	{
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	/// @brief Display the texture on the screen
	void Texture::DrawTextureOnScreen()
	{
		glBegin(GL_QUADS);

		// Define vertices and texture coordinates for a quadrilateral
		glTexCoord2f(0.0, 1.0);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-1.0f, +1.0f, 0.0f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(+1.0f, +1.0f, 0.0f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(+1.0f, -1.0f, 0.0f);

		// Finish drawing the quadrilateral
		glEnd();
	}
	/// @brief Render the texture on the screen
	/// @param width Width of the texture
	/// @param height Height of the texture
	/// @param viewport The viewport state for the rendering context
	/// @return Always returns true by default
	bool Texture::RenderTexture(const int width, const int height, const ViewportState viewport) const
	{
		// Retrieve pixel data from the default draw target
		const Pixel* target = pDefaultDrawTarget->GetData();

		// Set the viewport for rendering based on the specified viewport state
		SetViewport(viewport);

		// Update the texture with new image data (subimage)
		UpdateTexture(width, height, target);

		// Display the texture on the screen
		DrawTextureOnScreen();

		// Present graphics to the screen (swap buffers)
		SwapBuffers(glDeviceContext);

		return true;
	}

	///////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////// DRAWING GETTERS //////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////

	/// @brief Getter for the draw target.
	Sprite* Texture::GetDrawTarget() const
	{
		return pDrawTarget;
	}
	/// @brief Getter for the default draw target.
	Sprite* Texture::GetDefaultDrawTarget() const
	{
		return pDefaultDrawTarget;
	}
	/// @brief Getter for the width of the draw target.
	int32_t Texture::GetDrawTargetWidth() const
	{
		if (pDrawTarget) {
			return pDrawTarget->Width();
		}
		else {
			return 0;
		}
	}
	/// @brief Getter for the height of the draw target.
	int32_t Texture::GetDrawTargetHeight() const
	{
		if (pDrawTarget) {
			return pDrawTarget->Height();
		}
		else {
			return 0;
		}
	}
	/// @brief Getter for the size of the draw target.
	int32_t Texture::GetDrawTargetSize() const
	{
		return static_cast<int32_t>(static_cast<int64_t>(1) * GetDrawTargetHeight() * GetDrawTargetWidth());
	}
	/// @brief Getter for pixel blend factor.
	float Texture::GetBlendFactor() const
	{
		return fBlendFactor;
	}
	/// @brief Getter for current pixel drawing mode.
	Pixel::Mode Texture::GetPixelMode() const
	{
		return nPixelMode;
	}

	///////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////// DRAWING SETTERS //////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////

	/// @brief Set the draw target.
	/// @param target Sprite to set as the draw target.
	void Texture::SetDrawTarget(Sprite* target)
	{
		pDrawTarget = target ? target : pDefaultDrawTarget;
	}
	/// @brief Setter for the current pixel drawing mode.
	/// @param m Mode to set.
	void Texture::SetPixelMode(const Pixel::Mode m)
	{
		nPixelMode = m;
	}
	/// @brief Setter for the pixel blend factor.
	/// @param fBlend The blend factor to set.
	void Texture::SetBlendFactor(const float fBlend)
	{
		fBlendFactor = fBlend;
		if (fBlendFactor < 0.0f)
			fBlendFactor = 0.0f;
		if (fBlendFactor > 1.0f)
			fBlendFactor = 1.0f;
	}
	/// @brief Set the default draw target.
	/// @param width Width of the draw target.
	/// @param height Height of the draw target.
	/// @return True if the draw target was set successfully, false otherwise.
	bool Texture::SetDefaultDrawTarget(const int32_t width, const int32_t height)
	{
		if (width <= 0 || height <= 0) {
			pDefaultDrawTarget = nullptr;
			return false;
		}
		pDefaultDrawTarget = new Sprite(width, height);
		return true;
	}
	/// @brief Set the default target size.
	/// @param width Width of the target.
	/// @param height Height of the target.
	/// @return True if the target size was set successfully, false otherwise.
	bool Texture::SetDefaultTargetSize(const int32_t width, const int32_t height)
	{
		if (width <= 0 || height <= 0) {
			nDefaultWidth = 0;
			nDefaultHeight = 0;
			return false;
		}
		nDefaultWidth = width;
		nDefaultHeight = height;
		return true;
	}

	///////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////// DRAWING FUNCTIONS ////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////

	/// @brief Draw a pixel at the specified coordinates with the given color.
	/// @brief  - Solid color without transparency: <app::Pixel::NORMAL>
	/// @brief  - Only draw solid color (alpha = 255): <app::Pixel::MASK>
	/// @brief  - Fully transparent with alpha blending: <app::Pixel::ALPHA>
	/// @brief  - Only transparency color (alpha # 255): <app::Pixel::BACKGROUND>
	///
	/// @param x The X-coordinate.
	/// @param y The Y-coordinate.
	/// @param current_pixel The pixel color being applied.
	/// @param uScale The scaling factor of pixel being drawn
	/// @return True if all the pixels was drawn successfully, false otherwise.
	bool Texture::Draw(const int32_t x, const int32_t y, const Pixel current_pixel, const uint32_t uScale)
	{
		if (!pDrawTarget) {
			std::cerr << "Error: Draw target is not set." << std::endl;
			return false;
		}

		if (uScale == 0) {
			std::cerr << "Error: Zero scaling factor means drawing nothing" << std::endl;
			return false;
		}

		if (uScale > 1) { // Enlarge the pixel being drawn
			bool success = true;
			for (uint32_t uScaledX = x; uScaledX < x + uScale; uScaledX++) {
				for (uint32_t uScaledY = y; uScaledY < y + uScale; uScaledY++) {
					success &= Draw(uScaledX, uScaledY, current_pixel);
				}
			}
			return success;
		}

		if (nPixelMode == Pixel::NORMAL) {
			return pDrawTarget->SetPixel(x, y, current_pixel);
		}

		if (nPixelMode == Pixel::MASK) {
			if (current_pixel.a == 255) {
				return pDrawTarget->SetPixel(x, y, current_pixel);
			}
		}

		if (nPixelMode == Pixel::BACKGROUND) {
			if (current_pixel.a != 255) {
				return pDrawTarget->SetPixel(x, y, current_pixel);
			}
		}

		if (nPixelMode == Pixel::ALPHA) {
			const Pixel existed_pixel = pDrawTarget->GetPixel(x, y);
			const Pixel blended_pixel = blend(current_pixel, existed_pixel, GetBlendFactor());
			return pDrawTarget->SetPixel(x, y, blended_pixel);
		}

		return false;
	}
	/// @brief Draw a scaled sprite at the specified coordinates.
	/// @param nOffsetX The top left X-coordinate.
	/// @param nOffsetY The top left Y-coordinate.
	/// @param pSprite  The sprite to draw.
	/// @param uScale   The scaling factor (initially 1)
	void Texture::DrawSprite(const int32_t nOffsetX, const int32_t nOffsetY, const Sprite* pSprite, const uint32_t uScale)
	{
		if (pSprite == nullptr || uScale == 0) {
			return;
		}
		for (int32_t nSpriteX = 0; nSpriteX < pSprite->Width(); nSpriteX++) {
			for (int32_t nSpriteY = 0; nSpriteY < pSprite->Height(); nSpriteY++) {
				const Pixel pixel = pSprite->GetPixel(nSpriteX, nSpriteY);
				Draw(nOffsetX + nSpriteX * uScale, nOffsetY + nSpriteY * uScale, pixel,
					uScale);
			}
		}
	}
	/// @brief Draw a scaled portion of a sprite at the specified coordinates with scaling.
	/// @param nOffsetX The X-coordinate for drawing.
	/// @param nOffsetY The Y-coordinate for drawing.
	/// @param pSprite The sprite to draw.
	/// @param nOriginX The X-coordinate of the source area (top-left corner).
	/// @param nOriginY The Y-coordinate of the source area (top-left corner).
	/// @param nWidth The width of the source area.
	/// @param nHeight The height of the source area.
	/// @param uScale The scaling factor to apply when drawing the sprite.
	void Texture::DrawPartialSprite(const int32_t nOffsetX, const int32_t nOffsetY, const Sprite* pSprite, const int32_t nOriginX, const int32_t nOriginY, const int32_t nWidth, const int32_t nHeight, const uint32_t uScale)
	{
		if (pSprite == nullptr || uScale == 0) {
			return;
		}
		for (int32_t nPartialX = 0; nPartialX < nWidth; nPartialX++) {
			for (int32_t nPartialY = 0; nPartialY < nHeight; nPartialY++) {
				const int nPosX = nOffsetX + (nPartialX * uScale);
				const int nPosY = nOffsetY + (nPartialY * uScale);
				const Pixel pixel = pSprite->GetPixel(nPartialX + nOriginX, nPartialY + nOriginY);
				Draw(nPosX, nPosY, pixel, uScale);
			}
		}
	}
	/// @brief Draw partial sprite with default scaling factor, width and height.
	/// @param nOffsetX The X-coordinate for drawing.
	/// @param nOffsetY The Y-coordinate for drawing.
	/// @param pSprite The sprite to draw.
	/// @param nOriginX The X-coordinate of the source area (top-left corner).
	/// @param nOriginY The Y-coordinate of the source area (top-left corner).
	void Texture::DrawPartialSprite(const int32_t nOffsetX, const int32_t nOffsetY, const Sprite* pSprite, const int32_t nOriginX, const int32_t nOriginY)
	{
		return DrawPartialSprite(nOffsetX, nOffsetY, pSprite, nOriginX, nOriginY, nDefaultWidth, nDefaultHeight);
	}
	/// @brief Clear the draw target with the specified color.
	/// @param pixel Pixel color to clear
	void Texture::Clear(const Pixel pixel) const
	{
		const int size = GetDrawTargetSize();
		Pixel* targets = GetDrawTarget()->GetData();
		std::fill_n(targets, size, pixel);
	}
} // namespace app

///////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// END OF FILE ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
