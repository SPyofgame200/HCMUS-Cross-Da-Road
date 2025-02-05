#ifndef G_GAME_ENGINE_CORE_H
#define G_GAME_ENGINE_CORE_H
#pragma once

#pragma comment(lib, "user32.lib")
#include <thread>
#include <windows.h>

#include "gConst.h"
#include "gKey.h"
#include "gPixel.h"
#include "gResourcePack.h"
#include "gSprite.h"
#include "gState.h"
#include "gTexture.h"
#include "gWindow.h"

#ifndef G_GAME_ENGINE_DEF
#define G_GAME_ENGINE_DEF

/**
 * @brief Provide Strict Interface for Inherited Classes
 * @brief Functions will not return internal data, all manipulation is doing inside the interface
**/
namespace app
{
	class GameEngine
	{
		friend class Window;

	public: // Branding
		std::string sAppName;

	public: // Constructor & Destructor
		virtual ~GameEngine() = default;
		GameEngine();

	public: // Construction functions
		engine::Code Construct(uint32_t screen_w, uint32_t screen_h, uint32_t pixel_w, uint32_t pixel_h, bool full_screen = false);
		engine::Code Start();

	public: // Override Interfaces
		virtual bool OnCreateEvent();
		virtual bool OnFixedUpdateEvent(float fTickTime, const engine::Tick& eTickMessage);
		virtual bool OnUpdateEvent(float fElapsedTime);
		virtual bool OnLateUpdateEvent(float fElapsedTime, float fLateElapsedTime);
		virtual bool OnRenderEvent();
		virtual bool OnPauseEvent();
		virtual bool OnDestroyEvent();
		virtual bool OnForcePauseEvent();
		virtual bool OnForceDestroyEvent();

	public: // Hardware Interfaces
		bool IsFocused() const;
		bool DisableKey(Key k);
		bool EnableKey(Key k);
		Button GetKey(Key k) const;
		bool IsKeyIdling(const app::Key& key, bool bIgnoreDisability = false) const;
		bool IsKeyPressed(const app::Key& key, bool bIgnoreDisability = false) const;
		bool IsKeyHolding(const app::Key& key, bool bIgnoreDisability = false) const;
		bool IsKeyReleased(const app::Key& key, bool bIgnoreDisability = false) const;
		bool IsMoveLeft(const Button& eButton = Button::RELEASED) const;
		bool IsMoveRight(const Button& eButton = Button::RELEASED) const;
		bool IsMoveUp(const Button& eButton = Button::RELEASED) const;
		bool IsMoveDown(const Button& eButton = Button::RELEASED) const;
		bool IsMove(const Button& eButton = Button::RELEASED) const;

	public: // Property Getters
		int32_t ScreenWidth() const;
		int32_t ScreenHeight() const;
		int32_t PixelWidth() const;
		int32_t PixelHeight() const;
		int32_t WindowWidth() const;
		int32_t WindowHeight() const;

	public: // Draw Routines
		Pixel::Mode GetPixelMode() const;
		void SetPixelMode(Pixel::Mode m);
		void SetBlendFactor(float fBlend);
		bool SetDefaultTargetSize(int32_t width, int32_t height);
		bool Draw(int32_t x, int32_t y, Pixel current_pixel = app::WHITE, uint32_t uScale = 1);
		void DrawSprite(int32_t nOffsetX, int32_t nOffsetY, const Sprite* pSprite, uint32_t uScale = 1);
		void DrawPartialSprite(int32_t nOffsetX, int32_t nOffsetY, const Sprite* pSprite, int32_t nOriginX, int32_t nOriginY, int32_t nWidth, int32_t nHeight, uint32_t uScale = 1);
		void DrawPartialSprite(int32_t nOffsetX, int32_t nOffsetY, const Sprite* pSprite, int32_t nOriginX, int32_t nOriginY);
		void Clear(Pixel p = app::BLACK) const;

	public: // Engine Customization
		FrameDelay GetFrameDelay() const;
		int GetAppFPS() const;
		bool SetFrameDelay(FrameDelay eFrameDelay);
		bool RenderTexture() const;
		bool IsEnginePause() const;
		void ResumeEngine();
		void PauseEngine();

	private: // Engine Internalities
		ScreenState screen;
		ViewportState viewport;
		KeyboardState keyboard;
		Texture texture;
		FrameState frame;
		Window window;
		// MouseState mouse; [unused]

		bool OnFixedUpdateEvent(const engine::Tick& eTickMessage);
		bool UpdateKeyboardInput();
		bool UpdateWindowTitleSuffix(const std::string& sTitleSuffix);
		bool CreateWindowIcon();
		bool CreateViewport();
		bool InitEngineThread();
		bool ExitEngineThread() const;
		bool UpdateEngineEvent();
		bool HandleEngineThread();
		bool StartEngineThread();
		// If anything sets this flag to false the engine "should" shut down gracefully
		std::atomic<bool> bEngineRunning;
		std::atomic<bool> bEnginePausing;
	};
} // namespace app
#endif // G_GAME_ENGINE_DEF

#endif // G_GAME_ENGINE_CORE_H
