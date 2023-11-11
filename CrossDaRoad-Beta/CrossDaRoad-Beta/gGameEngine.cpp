#ifndef G_GAME_ENGINE_H
#include "gGameEngine.h"
#endif

#ifndef G_GAME_ENGINE_CPP
#define G_GAME_ENGINE_CPP
#pragma once

#include "gConst.h"
#include "gUtils.h"
#include <iostream>

/**
 * @namespace app
 * @brief Size-related getters
 **/
namespace app
{
	/// @brief Retrieves the screen width.
	/// @return The width of the screen.
	int32_t GameEngine::ScreenWidth() const
	{
		return static_cast<int32_t>(screen.GetScreenWidth());
	}

	/// @brief Retrieves the screen height.
	/// @return The height of the screen.
	int32_t GameEngine::ScreenHeight() const
	{
		return static_cast<int32_t>(screen.GetScreenHeight());
	}

	/// @brief Retrieves the pixel width.
	/// @return The width of each pixel.
	int32_t GameEngine::PixelWidth() const
	{
		return static_cast<int32_t>(screen.GetPixelWidth());
	}

	/// @brief Retrieves the pixel height.
	/// @return The height of each pixel.
	int32_t GameEngine::PixelHeight() const
	{
		return static_cast<int32_t>(screen.GetPixelHeight());
	}

	/// @brief Retrieves the window width.
	/// @return The width of each window.
	int32_t GameEngine::WindowWidth() const
	{
		return screen.GetWindowWidth();
	}

	/// @brief Retrieves the window height.
	/// @return The height of each window.
	int32_t GameEngine::WindowHeight() const
	{
		return screen.GetWindowHeight();
	}
} // namespace app

/**
 * @namespace app
 * @brief Constructor and Resource Collectors
 **/
namespace app
{
	/// @brief Constructor for the GameEngine class.
	GameEngine::GameEngine()
	{
		sAppName = engine::ENGINE_NAME;
	}

	/// @brief Construct the game engine with specified parameters.
	/// @param screen_width The screen width.
	/// @param screen_height The screen height.
	/// @param pixel_width The pixel width.
	/// @param pixel_height The pixel height.
	/// @param full_screen Whether to run in full screen mode.
	/// @return The result code.
	engine::Code GameEngine::Construct(const uint32_t screen_width, const uint32_t screen_height, const uint32_t pixel_width, const uint32_t pixel_height, bool full_screen)
	{
		// Set screen dimensions and pixel dimensions
		screen.SetScreenSize(screen_width, screen_height);
		screen.SetPixelSize(pixel_width, pixel_height);

		// Check for invalid dimensions
		if (PixelWidth() <= 0 || PixelHeight() <= 0) {
			std::cerr << "Error: Invalid pixel size (width = " << PixelWidth()
				<< ", height = " << PixelHeight() << ")";
			std::cerr << ", expected positive integer parameters" << std::endl;
			return engine::FAILURE;
		}

		if (ScreenWidth() == 0 || ScreenHeight() == 0) {
			std::cerr << "Error: Invalid screen size (width = " << ScreenWidth()
				<< ", height = " << ScreenHeight() << ")";
			std::cerr << ", expected positive integer parameters" << std::endl;
			return engine::FAILURE;
		}

		// Create a sprite that represents the primary drawing target.
		texture.SetDefaultDrawTarget(ScreenWidth(), ScreenHeight());
		texture.SetDrawTarget(nullptr);
		return engine::SUCCESS;
	}

	/// @brief Start the game engine.
	/// @return The result code.
	engine::Code GameEngine::Start()
	{
		// Construct the window.
		if (!window.WindowCreate(this)) {
			std::cerr << "Error: Failed to create the window." << std::endl;
			return engine::FAILURE;
		}

		StartEngineThread();
		return engine::SUCCESS;
	}
} // namespace app

/**
 * @namespace app
 * @brief Engine Thread Events
 **/
namespace app
{
	/// @brief Called once on application startup, use it to load your resources.
	/// @return Always returns false by default.
	bool GameEngine::OnCreateEvent()
	{
		// TODO: Load and initialize resources here.
		// If successful, return true; otherwise, return false.
		return false;
	}

	/// @brief Real time fixed updates, called bewteen frames and between window
	/// messages
	/// @param fTickTime The current time since the engine creation.
	/// @param eTickMessage The message being broadcast indicating changes
	/// @return Always returns false by default.
	bool GameEngine::OnFixedUpdateEvent(float fTickTime, const engine::Tick& eTickMessage)
	{
		// TODO: Update the game side effects
		// If the game should continue, return true; otherwise, return false.
		return false;
	}

	/// @brief Called every frame, providing you with a time per frame value.
	/// @param fElapsedTime The elapsed time since the last frame.
	/// @return Always returns false by default.
	bool GameEngine::OnUpdateEvent(float fElapsedTime)
	{
		// TODO: Update the game logic and render the frame here.
		// If the game should continue, return true; otherwise, return false.
		return false;
	}

	/// @brief Called after all other updates, allowing for additional processing
	/// and bug fixing.
	/// @param fElapsedTime The same elapsed time since the last frame called in
	/// OnUpdateEvent()
	/// @param fLateElapsedTime The current elapsed time since the last frame.
	/// @return Always returns true by default.
	bool GameEngine::OnLateUpdateEvent(float fElapsedTime, float fLateElapsedTime)
	{
		// TODO: Update camera following, resolve drawing conflicts, post-processing
		// effects, ... If update is important, and failed to handle the bugs, return
		// false; otherwise, return true.
		return true;
	}

	/// @brief Called every frame to handle rendering.
	/// @return Always returns false by default.
	bool GameEngine::OnRenderEvent()
	{
		// TODO: Handle rendering here.
		// If rendering is successful, return true; otherwise, return false.
		return false;
	}

	/// @brief Called when the application is paused.
	/// @return Always returns true by default.
	bool GameEngine::OnPauseEvent()
	{
		// TODO: Handle pausing the application and its behavior.
		// If pause handling is successful, return true; otherwise, return false (keep
		// pausing).
		return true;
	}

	/// @brief Called once on application termination, for cleanup.
	/// @return Always returns true by default.
	bool GameEngine::OnDestroyEvent()
	{
		// TODO: Perform cleanup and release resources here.
		// If cleanup is successful, return true; otherwise, return false.
		return true;
	}

	/// @brief Called suddenly during the running time, to force close the app
	/// @return Always returns true by default.
	bool GameEngine::OnForceDestroyEvent()
	{
		// TODO: Perform force cleanup, force release resources and ignore all other
		// actions If cleanup is successful, return true; otherwise, return false.
		return true;
	}
} // namespace app

/**
 * @namespace app
 * @brief Hardware interactions
 **/
namespace app
{
	/// @brief Check if the application has input focus.
	/// @return True if the application has input focus, false otherwise.
	bool GameEngine::IsFocused() const
	{
		return keyboard.IsFocused();
	}

	bool GameEngine::DisableKey(const Key k)
	{
		return keyboard.DisableKey(k);
	}

	bool GameEngine::EnableKey(const Key k)
	{
		return keyboard.EnableKey(k);
	}
	/// @brief Get the state of a keyboard key.
	/// @param k The key to check.
	/// @return The state of the key.
	Button GameEngine::GetKey(const Key k) const
	{
		return keyboard.GetKey(k);
	}

	bool GameEngine::IsKeyIdling(const app::Key& key, bool bIgnoreDisability) const
	{
		return keyboard.IsKeyIdling(key, bIgnoreDisability);
	}

	bool GameEngine::IsKeyPressed(const app::Key& key, bool bIgnoreDisability) const
	{
		return keyboard.IsKeyPressed(key, bIgnoreDisability);
	}

	bool GameEngine::IsKeyHolding(const app::Key& key, bool bIgnoreDisability) const
	{
		return keyboard.IsKeyHolding(key, bIgnoreDisability);
	}

	bool GameEngine::IsKeyReleased(const app::Key& key, bool bIgnoreDisability) const
	{
		return keyboard.IsKeyReleased(key, bIgnoreDisability);
	}

	/// @brief Check if player is moving left (by key released)
	bool GameEngine::IsMoveLeft(const Button& eButton) const
	{
		return (GetKey(app::Key::A) == eButton) || (GetKey(app::Key::LEFT) == eButton);
	}
	/// @brief Check if player is moving right (by key released)
	bool GameEngine::IsMoveRight(const Button& eButton) const
	{
		return (GetKey(app::Key::D) == eButton) || (GetKey(app::Key::RIGHT) == eButton);
	}
	/// @brief Check if player is moving up (by key released)
	bool GameEngine::IsMoveUp(const Button& eButton) const
	{
		return (GetKey(app::Key::W) == eButton) || (GetKey(app::Key::UP) == eButton);
	}
	/// @brief Check if player is moving down (by key released)
	bool GameEngine::IsMoveDown(const Button& eButton) const
	{
		return (GetKey(app::Key::S) == eButton) || (GetKey(app::Key::DOWN) == eButton);
	}
	/// @brief Check if player is moving (by key released)
	bool GameEngine::IsMove(const Button& eButton) const
	{
		return IsMoveLeft(eButton) || IsMoveRight(eButton) || IsMoveUp(eButton) || IsMoveDown(eButton);
	}
} // namespace app

/**
 * @namespace app
 * @brief Drawer functions
 **/
namespace app
{
	/// @brief Set the pixel drawing mode.
	/// @param m The pixel drawing mode to set.
	void GameEngine::SetPixelMode(const Pixel::Mode m)
	{
		return texture.SetPixelMode(m);
	}

	/// @brief Get the current pixel drawing mode.
	/// @return The current pixel drawing mode.
	Pixel::Mode GameEngine::GetPixelMode() const
	{
		return texture.GetPixelMode();
	}

	/// @brief Set the pixel blend factor.
	/// @param fBlend The blend factor to set.
	void GameEngine::SetBlendFactor(const float fBlend)
	{
		return texture.SetBlendFactor(fBlend);
	}

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
	bool GameEngine::Draw(const int32_t x, const int32_t y, const Pixel current_pixel, const uint32_t uScale)
	{
		return texture.Draw(x, y, current_pixel, uScale);
	}

	/// @brief Draw a scaled sprite at the specified coordinates.
	/// @param nOffsetX The top left X-coordinate.
	/// @param nOffsetY The top left Y-coordinate.
	/// @param pSprite  The sprite to draw.
	/// @param uScale   The scaling factor (initially 1)
	void GameEngine::DrawSprite(const int32_t nOffsetX, const int32_t nOffsetY, const Sprite* pSprite, const uint32_t uScale)
	{
		return texture.DrawSprite(nOffsetX, nOffsetY, pSprite, uScale);
	}

	/// @brief Draw a scaled portion of a sprite at the specified coordinates with
	/// scaling.
	/// @param nOffsetX The X-coordinate for drawing.
	/// @param nOffsetY The Y-coordinate for drawing.
	/// @param pSprite The sprite to draw.
	/// @param nOriginX The X-coordinate of the source area (top-left corner).
	/// @param nOriginY The Y-coordinate of the source area (top-left corner).
	/// @param nWidth The width of the source area.
	/// @param nHeight The height of the source area.
	/// @param uScale The scaling factor to apply when drawing the sprite.
	void GameEngine::DrawPartialSprite(
		const int32_t nOffsetX, const int32_t nOffsetY, const Sprite* pSprite,
		const int32_t nOriginX, const int32_t nOriginY, const int32_t nWidth,
		const int32_t nHeight, const uint32_t uScale)
	{
		return texture.DrawPartialSprite(nOffsetX, nOffsetY, pSprite, nOriginX, nOriginY, nWidth, nHeight, uScale);
	}

	/// @brief Clear the drawing target with the specified pixel color.
	/// @param pixel The pixel color to use for clearing.
	void GameEngine::Clear(const Pixel pixel) const
	{
		return texture.Clear(pixel);
	}
} // namespace app

/**
 * @namespace app
 * @brief Engine Customization
 **/
namespace app
{
	FrameDelay GameEngine::GetFrameDelay() const
	{
		return frame.GetDelay();
	}

	int GameEngine::GetAppFPS() const
	{
		return frame.GetFPS();
	}

	bool GameEngine::SetFrameDelay(FrameDelay eFrameDelay)
	{
		return frame.SetDelay(eFrameDelay);
	}
} // namespace app

/**
 * @namespace app
 * @brief Engine Internalities and Private Functions
 **/
namespace app
{
	/// @brief Broadcast Tick messages with additional informations
	/// @return Always return true on default
	bool GameEngine::OnFixedUpdateEvent(const engine::Tick& eTickMessage)
	{
		OnFixedUpdateEvent(frame.GetTickTime(), eTickMessage);
		return true;
	}

	/// @brief Updates keyboard input and updates the keyboard state.
	/// @return True if the input handling was successful.
	bool GameEngine::UpdateKeyboardInput()
	{
		keyboard.UpdateKeyboard();
		return true;
	}

	/// @brief Updates rendering of the game.
	/// @param fElapsedTime - The elapsed time since the last frame.
	/// @return True if rendering was successful.
	bool GameEngine::RenderTexture() const
	{
		texture.RenderTexture(ScreenWidth(), ScreenHeight(), viewport);
		return true;
	}

	bool GameEngine::UpdateWindowTitleSuffix(
		const std::string& sTitleSuffix) const
	{
		const std::string sTitle = sAppName + sTitleSuffix;
		SetWindowText(window.windowHandler, to_text(sTitle));
		return true;
	}

	bool GameEngine::CreateWindowIcon() const
	{
		auto hIcon = static_cast<HICON>(LoadImage(nullptr, to_text(engine::ICON_FILE_PATH), IMAGE_ICON, 0, 0, LR_LOADFROMFILE));
		if (hIcon) {
			std::cerr << "Successfully loaded engine icon (path = \""
				<< engine::ICON_FILE_PATH << "\")" << std::endl;
			SendMessage(window.windowHandler, WM_SETICON, ICON_SMALL,
				reinterpret_cast<LPARAM>(hIcon));
		}
		else {
			std::cerr << "Can not open engine icon (path = \"" << engine::ICON_FILE_PATH
				<< "\")" << std::endl;
			return false;
		}

		if (auto hFavicon = static_cast<HICON>(
			LoadImage(nullptr, to_text(engine::FAVICON_FILE_PATH), IMAGE_ICON, 0,
				0, LR_LOADFROMFILE))) {
			std::cerr << "Successfully loaded engine favicon (path = \""
				<< engine::FAVICON_FILE_PATH << "\")" << std::endl;
			SendMessage(window.windowHandler, WM_SETICON, ICON_BIG,
				reinterpret_cast<LPARAM>(hFavicon));
		}
		else {
			std::cerr << "Can not open engine favicon (path = \""
				<< engine::FAVICON_FILE_PATH << "\")";
			std::cerr << ", switching to the usable engine icon (path = \""
				<< engine::ICON_FILE_PATH << "\")" << std::endl;
			SendMessage(window.windowHandler, WM_SETICON, ICON_BIG,
				reinterpret_cast<LPARAM>(hIcon));
			return false;
		}

		return true;
	}

	/// @brief Initializes the engine thread.
	/// @return True if initialization was successful.
	bool GameEngine::InitEngineThread()
	{
		CreateWindowIcon();
		texture.CreateDeviceContext(window.windowHandler);
		texture.CreateTexture2D(ScreenWidth(), ScreenHeight(), viewport);
		return true;
	}

	/// @brief Handles the engine event loop.
	/// @return True if the event loop should continue running.
	bool GameEngine::UpdateEngineEvent()
	{
		frame.ResetTimer();

		OnFixedUpdateEvent(engine::BEFORE_CREATE_EVENT);
		bEngineRunning = OnCreateEvent(); // Start the event if the user creates it
		OnFixedUpdateEvent(engine::AFTER_CREATE_EVENT);

		float fLastRunTime = 0;
		while (bEngineRunning) {
			OnFixedUpdateEvent(engine::PRE_RUNNING_EVENT);

			/// Scope: Load data
			{
				UpdateKeyboardInput();
				OnFixedUpdateEvent(engine::AFTER_LOAD_KEYBOARD_EVENT);
			}
			// Scope: Update game
			{
				OnFixedUpdateEvent(engine::BEFORE_UPDATE_EVENT);
				const float fElapsedTime = frame.GetElapsedTime(true);
				if (!OnUpdateEvent(fElapsedTime)) { // Stop <=> no more updates
					bEngineRunning = false;           // Do not return, using break instead
					break;                            // so we can use OnDestroyEvent()
				}
				UpdateWindowTitleSuffix(frame.ShowFPS());
				OnFixedUpdateEvent(engine::AFTER_UPDATE_TITLE_EVENT);
				OnLateUpdateEvent(fElapsedTime, fElapsedTime + frame.GetElapsedTime(false));
				OnFixedUpdateEvent(engine::AFTER_UPDATE_EVENT);
			}
			// Scope: Rendering scence
			{
				OnFixedUpdateEvent(engine::BEFORE_SCENE_RENDER_EVENT);
				if (!OnRenderEvent()) {
					bEngineRunning = false; // Do not return, using break instead
					break;                  // so we can use OnDestroyEvent()
				}
				OnFixedUpdateEvent(engine::AFTER_SCENE_RENDER_EVENT);
				RenderTexture();
				OnFixedUpdateEvent(engine::AFTER_RENDER_EVENT);
			}
			// Scope: Post proccessing
			{
				OnFixedUpdateEvent(engine::BEFORE_POST_PROCCESSING_EVENT);
				frame.WaitMicroseconds(frame.GetDelay(), (frame.GetTickTime() - fLastRunTime) * 1000000);
				fLastRunTime = frame.GetTickTime();
				OnFixedUpdateEvent(engine::AFTER_POST_PROCCESSING_EVENT);
				const float fStartPauseTime = frame.GetTickTime();
				while (bEngineRunning && !OnPauseEvent()) {
					frame.WaitMicroseconds(frame.GetDelay());
					RenderTexture();
					UpdateKeyboardInput();
				}
				const float fEndPauseTime = frame.GetTickTime();
				frame.Rewind(fEndPauseTime - fStartPauseTime);
				OnFixedUpdateEvent(engine::ON_UNPAUSE_EVENT);
			}
			OnFixedUpdateEvent(engine::POST_RUNNING_EVENT);
		}

		OnFixedUpdateEvent(engine::BEFORE_DESTROY_EVENT);
		const bool result = !OnDestroyEvent(); // Continue the thread until it gets destroyed
		OnFixedUpdateEvent(engine::AFTER_DESTROY_EVENT);

		return result;
	}

	/// @brief Exits the engine thread and cleans up resources.
	/// @return True if exit was successful.
	bool GameEngine::ExitEngineThread() const
	{
		texture.ExitDevice();
		PostMessage(window.windowHandler, WM_DESTROY, 0, 0);
		return true;
	}

	/// @brief Handles the engine thread, including initialization, event loop, and
	/// exit.
	/// @return True if the thread execution was successful.
	bool GameEngine::HandleEngineThread()
	{
		InitEngineThread();
		while ((bEngineRunning = UpdateEngineEvent())) Sleep(270); /// basic minor delay that user cant differentiate
		ExitEngineThread();
		return true;
	}

	/// @brief Starts the engine thread and message handling.
	/// @return True if thread startup and message handling were successful.
	bool GameEngine::StartEngineThread()
	{
		auto thread = std::thread(&GameEngine::HandleEngineThread, this);
		window.HandleWindowMessage();
		thread.join();
		return true;
	}
} // namespace app

/**
 * @namespace app
 * @brief Window functions
 **/
namespace app
{
} // namespace app

#endif // G_GAME_ENGINE_CPP