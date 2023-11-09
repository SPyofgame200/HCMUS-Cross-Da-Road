#ifndef G_TEXTURE_H
#define G_TEXTURE_H

#pragma comment(lib, "opengl32.lib")
#include <Windows.h>
#include <GL/gl.h>
#include "gPixel.h"
#include "gState.h"
#include "gSprite.h"

/**
 * @file gTexture.h
 *
 * @brief Contains texture class
 *
 * This file contains texture class for drawing textures on screen using OpenGL.
 */

namespace app
{
	/// @brief OpenGL function pointers for dynamic linking
	typedef BOOL(WINAPI wglSwapInterval_t)(int interval);
	static wglSwapInterval_t* wglSwapInterval;
	/// @brief Class for drawing textures on screen using OpenGL
	class Texture
	{
	private: // OpenGL Environment variables
		HDC glDeviceContext;   ///< Device context for OpenGL rendering context
		HGLRC glRenderContext; ///< Rendering context for OpenGL
		GLuint glBuffer;       ///< OpenGL buffer for texture

	private: // Drawing variables
		Sprite* pDefaultDrawTarget; ///< Default draw target for drawing on screen (window) using OpenGL functions
		Sprite* pDrawTarget;        ///< Draw target for drawing on screen (window) using OpenGL functions
		Pixel::Mode nPixelMode;     ///< Pixel mode for drawing on screen (window) using OpenGL functions
		float fBlendFactor;         ///< Blend factor for drawing on screen (window) using OpenGL functions

	public: // Constructors & Destructors
		Texture();
		Texture(HWND windowHandler);
		~Texture();
		bool InitDevice();
		bool CreateDeviceContext(HWND windowHandler);
		bool ExitDevice() const;

	public: // Setup enviroment
		bool SetupFormatter() const;
		bool SetupRendering(ViewportState viewport);
		bool SetupTexturing();
		bool SetupEnvironment(int width, int height) const;
		bool CreateTexture2D(int width, int height, ViewportState viewport);

	public: // Updater
		void SetViewport(ViewportState viewport) const;
		void UpdateTexture(int width, int height, const Pixel* data) const;
		void DrawTextureOnScreen() const;
		bool RenderTexture(int width, int height, ViewportState viewport) const;

	public: // Drawing Getters
		Sprite* GetDrawTarget() const;
		Sprite* GetDefaultDrawTarget() const;
		int32_t GetDrawTargetWidth() const;
		int32_t GetDrawTargetHeight() const;
		int32_t GetDrawTargetSize() const;
		float GetBlendFactor() const;
		Pixel::Mode GetPixelMode() const;

	public: // Drawing Setters
		void SetDrawTarget(Sprite* target);
		void SetPixelMode(Pixel::Mode m);
		void SetBlendFactor(float fBlend);
		bool SetDefaultDrawTarget(int32_t width, int32_t height);

	public: // Drawing functions
		bool Draw(int32_t x, int32_t y, Pixel current_pixel = app::WHITE, uint32_t uScale = 1);
		void DrawSprite(int32_t nOffsetX, int32_t nOffsetY, const Sprite* pSprite, uint32_t uScale = 1);
		void DrawPartialSprite(int32_t nOffsetX, int32_t nOffsetY, const Sprite* pSprite, int32_t nOriginX, int32_t nOriginY, int32_t nWidth, int32_t nHeight, uint32_t uScale = 1);
		void Clear(Pixel pixel = app::BLACK) const;
	};
}

#endif // G_TEXTURE_H
