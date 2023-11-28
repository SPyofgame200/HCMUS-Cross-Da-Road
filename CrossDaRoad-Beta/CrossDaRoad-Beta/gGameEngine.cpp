#ifndef G_GAME_ENGINE_H
#include "gGameEngine.h"
#endif

#ifndef G_GAME_ENGINE_CPP
#define G_GAME_ENGINE_CPP
#pragma once

#include <thread>

//=================================================================================================
// Include new header files here

//=================================================================================================

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// PROPERTY GETTERS ///////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// CONSTRUCTORS & DESTRUCTORS ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace app
{
    /// @brief Default constructor.
    GameEngine::GameEngine()
    {
        sAppName = engine::ENGINE_NAME;
        bEngineRunning = false;
        bEnginePausing = false;
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
        if (!window.Create(this)) {
            std::cerr << "Error: Failed to create the window." << std::endl;
            return engine::FAILURE;
        }

        StartEngineThread();
        return engine::SUCCESS;
    }
} // namespace app

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// OVERRIDE INTERFACES ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

    /// @brief Real time trigger updates, called bewteen frames and between window messages
    /// @param fTickTime The current time since the engine creation.
    /// @param eTriggerer The message being broadcast indicating changes
    /// @return Always returns false by default.
    bool GameEngine::OnTriggerEvent(float fTickTime, const engine::Triggerer& eTriggerer)
    {
        // TODO: Update the game side effects
        // If the game should continue, return true; otherwise, return false.
        return false;
    }

    /// @brief Called in each game loop, for initializations, physic updates and hardware interactions
    /// @param fTickTime The current time since the engine creation.
    /// @return Always returns false by default.
    bool GameEngine::OnFixedUpdateEvent(float fTickTime)
    {
        // TODO: Initialize values, update the physics and hardware interactions
        // If the game should continue, return true; otherwise, return false.
        return false;
    }

    /// @brief Called in each game loop, for controlling main update events
    /// @param fElapsedTime The elapsed time since the last frame.
    /// @return Always returns false by default.
    bool GameEngine::OnUpdateEvent(float fElapsedTime)
    {
        // TODO: Update the game logic and render the frame here.
        // If the game should continue, return true; otherwise, return false.
        return false;
    }

    /// @brief Called after all other updates, allowing for additional processing and bug fixing.
    /// @param fTickTime The current time since the engine creation.
    /// @param fElapsedTime The same elapsed time since the last frame called
    /// @param fLateElapsedTime The current elapsed time since the last frame.
    /// @return Always returns true by default.
    bool GameEngine::OnLateUpdateEvent(float fTickTime, float fElapsedTime, float fLateElapsedTime)
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
    bool GameEngine::OnPauseEvent(float fTickTime)
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

    /// @brief Called suddenly during the running time, to force pause the app
    /// @return Always returns true by default.
    bool GameEngine::OnForcePauseEvent()
    {
        // TODO: Perform force pausing, force stop updating and rendering events
        // actions If force pausing is successful, return true; otherwise return false
        return true;
    }

    /// @brief Called suddenly during the running time, to force close the app
    /// @return Always returns true by default.
    bool GameEngine::OnForceDestroyEvent()
    {
        // TODO: Perform force cleanup, force release resources and ignore all other
        // actions If cleanup is successful, return true;
        // ....... otherwise, return false and detecting issues and EXIT BUG.
        return true;
    }
} // namespace app

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// HARDWARE INTERFACES ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace app
{
    /// @brief Check if the application has input focus.
    /// @return True if the application has input focus, false otherwise.
    bool GameEngine::IsFocused() const
    {
        return keyboard.IsFocused();
    }
    /// @brief Disable a keyboard key.
    /// @param k Key to disable.
    /// @return Always returns true by default.
    bool GameEngine::DisableKey(const Key k)
    {
        return keyboard.DisableKey(k);
    }
    /// @brief Enable a keyboard key.
    /// @param k Key to enable.
    /// @return Always returns true by default.
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
    /// @brief Check if a key is idling.
    /// @param key Key to check.
    /// @param bIgnoreDisability Ignore the key's disability.
    /// @return True if the key is idling, false otherwise.
    bool GameEngine::IsKeyIdling(const app::Key& key, bool bIgnoreDisability) const
    {
        return keyboard.IsKeyIdling(key, bIgnoreDisability);
    }
    /// @brief Check if a key is pressed.
    /// @param key Key to check.
    /// @param bIgnoreDisability Ignore the key's disability. 
    /// @return True if the key is pressed, false otherwise.
    bool GameEngine::IsKeyPressed(const app::Key& key, bool bIgnoreDisability) const
    {
        return keyboard.IsKeyPressed(key, bIgnoreDisability);
    }
    /// @brief Check if a key is holding.
    /// @param key Key to check.
    /// @param bIgnoreDisability Ignore the key's disability.
    /// @return True if the key is holding, false otherwise.
    bool GameEngine::IsKeyHolding(const app::Key& key, bool bIgnoreDisability) const
    {
        return keyboard.IsKeyHolding(key, bIgnoreDisability);
    }
    /// @brief Check if a key is released.
    /// @param key Key to check.
    /// @param bIgnoreDisability Ignore the key's disability. 
    /// @return True if the key is released, false otherwise.
    bool GameEngine::IsKeyReleased(const app::Key& key, bool bIgnoreDisability) const
    {
        return keyboard.IsKeyReleased(key, bIgnoreDisability);
    }
    /// @brief Check if player is moving left (by key released)
    /// @param eButton The button to check.
    /// @return True if the player is moving left, false otherwise.
    bool GameEngine::IsMoveLeft(const Button& eButton) const
    {
        return (GetKey(app::Key::A) == eButton) || (GetKey(app::Key::LEFT) == eButton);
    }
    /// @brief Check if player is moving right (by key released)
    /// @param eButton The button to check.
    /// @return True if the player is moving right, false otherwise.
    bool GameEngine::IsMoveRight(const Button& eButton) const
    {
        return (GetKey(app::Key::D) == eButton) || (GetKey(app::Key::RIGHT) == eButton);
    }
    /// @brief Check if player is moving up (by key released)
    /// @param eButton The button to check.
    /// @return True if the player is moving up, false otherwise.
    bool GameEngine::IsMoveUp(const Button& eButton) const
    {
        return (GetKey(app::Key::W) == eButton) || (GetKey(app::Key::UP) == eButton);
    }
    /// @brief Check if player is moving down (by key released)
    /// @param eButton The button to check.
    /// @return True if the player is moving down, false otherwise.
    bool GameEngine::IsMoveDown(const Button& eButton) const
    {
        return (GetKey(app::Key::S) == eButton) || (GetKey(app::Key::DOWN) == eButton);
    }
    /// @brief Check if player is moving (by key released)
    /// @param eButton The button to check.
    /// @return True if the player is moving, false otherwise.
    bool GameEngine::IsMove(const Button& eButton) const
    {
        return IsMoveLeft(eButton) || IsMoveRight(eButton) || IsMoveUp(eButton) || IsMoveDown(eButton);
    }
} // namespace app

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// DRAW ROUTINES /////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
    /// @brief Set the default target size of the pixel drawing.
    /// @param width The width of the target.
    /// @param height The height of the target.
    /// @return True if the target size was set successfully, false otherwise.
    bool GameEngine::SetDefaultTargetSize(int32_t width, int32_t height)
    {
        return texture.SetDefaultTargetSize(width, height);
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

    /// @brief Draw a scaled portion of a sprite at the specified coordinates with scaling.
    /// @param nOffsetX The X-coordinate for drawing.
    /// @param nOffsetY The Y-coordinate for drawing.
    /// @param pSprite The sprite to draw.
    /// @param nOriginX The X-coordinate of the source area (top-left corner).
    /// @param nOriginY The Y-coordinate of the source area (top-left corner).
    /// @param nWidth The width of the source area.
    /// @param nHeight The height of the source area.
    /// @param uScale The scaling factor to apply when drawing the sprite.
    void GameEngine::DrawPartialSprite(const int32_t nOffsetX, const int32_t nOffsetY, const Sprite* pSprite, const int32_t nOriginX, const int32_t nOriginY, const int32_t nWidth, const int32_t nHeight, const uint32_t uScale)
    {
        return texture.DrawPartialSprite(nOffsetX, nOffsetY, pSprite, nOriginX, nOriginY, nWidth, nHeight, uScale);
    }

    /// @brief Draw partial sprite with default scaling factor, width and height.
    /// @param nOffsetX The X-coordinate for drawing.
    /// @param nOffsetY The Y-coordinate for drawing.
    /// @param pSprite The sprite to draw.
    /// @param nOriginX The X-coordinate of the source area (top-left corner).
    /// @param nOriginY The Y-coordinate of the source area (top-left corner).
    void GameEngine::DrawPartialSprite(const int32_t nOffsetX, const int32_t nOffsetY, const Sprite* pSprite, const int32_t nOriginX, const int32_t nOriginY)
    {
        return texture.DrawPartialSprite(nOffsetX, nOffsetY, pSprite, nOriginX, nOriginY);
    }

    /// @brief Clear the drawing target with the specified pixel color.
    /// @param pixel The pixel color to use for clearing.
    void GameEngine::Clear(const Pixel pixel) const
    {
        return texture.Clear(pixel);
    }
} // namespace app

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ENGINE CUSTOMIZATION ///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace app
{
    /// @brief Get the current frame delay.
    /// @return The current frame delay.
    FrameDelay GameEngine::GetFrameDelay() const
    {
        return frame.GetDelay();
    }

    /// @brief Get the current application FPS.
    /// @return The current application FPS.
    int GameEngine::GetAppFPS() const
    {
        return frame.GetFPS();
    }

    /// @brief Set the frame delay.
    /// @param eFrameDelay Frame delay to set.
    /// @return Always returns true by default.
    bool GameEngine::SetFrameDelay(FrameDelay eFrameDelay)
    {
        return frame.SetDelay(eFrameDelay);
    }
    /// @brief Check if the engine is pausing
    /// @return True if the engine is pausing, false otherwise.
    bool GameEngine::IsEnginePause() const
    {
        return bEnginePausing;
    }
    /// @brief Resume the engine
    void GameEngine::ResumeEngine()
    {
        bEnginePausing = false;
    }
    /// @brief Pause the engine
    void GameEngine::PauseEngine()
    {
        bEnginePausing = true;
    }
} // namespace app

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ENGINE INTERNALITIES ///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace app
{
    /// @brief Broadcast Triggerer messages with additional informations
    /// @return Always return true on default
    bool GameEngine::OnTriggerEvent(const engine::Triggerer& eTriggerer)
    {
        OnTriggerEvent(frame.GetTickTime(), eTriggerer);
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

    /// @brief Updates the window title suffix.
    /// @param sTitleSuffix The suffix to append to the window title.
    /// @return Always returns true by default.
    bool GameEngine::UpdateWindowTitleSuffix(const std::string& sTitleSuffix)
    {
        const std::string sTitle = sAppName + sTitleSuffix;
        return window.SetTitle(sTitle);
    }
    /// @brief Creates the window icon.
    /// @return True if the window icon was created successfully, false otherwise.
    bool GameEngine::CreateWindowIcon()
    {
        return window.SetIcon(engine::ICON_FILE_PATH) && window.SetFavicon(engine::FAVICON_FILE_PATH);
    }

    /// @brief Creates the viewport.
    /// @return Always returns true by default.
    bool GameEngine::CreateViewport()
    {
        screen.SetupWindowSize();
        viewport.UpdateByScreen(screen);
        return true;
    }

    /// @brief Initializes the engine thread.
    /// @return True if initialization was successful.
    bool GameEngine::InitEngineThread()
    {
        CreateWindowIcon();
        texture.CreateDeviceContext(window.GetWindowHandler());
        texture.CreateTexture2D(ScreenWidth(), ScreenHeight(), viewport);
        return true;
    }

    /// @brief Handles the engine event loop.
    /// @return True if the event loop should continue running.
    bool GameEngine::UpdateEngineEvent()
    {
        frame.ResetTimer();

        OnTriggerEvent(engine::BEFORE_CREATE_EVENT);
        bEngineRunning = OnCreateEvent(); // Start the event if the user creates it
        OnTriggerEvent(engine::AFTER_CREATE_EVENT);

        float fLastRunTime = 0;
        while (bEngineRunning) {
            OnTriggerEvent(engine::PRE_RUNNING_EVENT);

            /// Scope: Initialization
            {
                if (!OnFixedUpdateEvent(frame.GetTickTime())) { // Stop <=> no more updates
                    bEngineRunning = false; // Do not return, using break instead
                    break;                  // so we can use OnDestroyEvent()
                }
                UpdateKeyboardInput();
                OnTriggerEvent(engine::AFTER_LOAD_KEYBOARD_EVENT);
            }
            // Scope: Update game
            {
                OnTriggerEvent(engine::BEFORE_UPDATE_EVENT);
                const float fElapsedTime = frame.GetElapsedTime(true);
                if (!OnUpdateEvent(fElapsedTime)) { // Stop <=> no more updates
                    bEngineRunning = false; // Do not return, using break instead
                    break;                  // so we can use OnDestroyEvent()
                }
                UpdateWindowTitleSuffix(frame.ShowFPS());
                OnTriggerEvent(engine::AFTER_UPDATE_TITLE_EVENT);
                if (!OnLateUpdateEvent(frame.GetTickTime(), fElapsedTime, fElapsedTime + frame.GetElapsedTime(false))) {
                    bEngineRunning = false; // Do not return, using break instead
                    break;                  // so we can use OnDestroyEvent()
                }
                OnTriggerEvent(engine::AFTER_UPDATE_EVENT);
            }
            // Scope: Rendering scence
            {
                OnTriggerEvent(engine::BEFORE_SCENE_RENDER_EVENT);
                if (!OnRenderEvent()) {
                    bEngineRunning = false; // Do not return, using break instead
                    break;                  // so we can use OnDestroyEvent()
                }
                OnTriggerEvent(engine::AFTER_SCENE_RENDER_EVENT);
                RenderTexture();
                OnTriggerEvent(engine::AFTER_RENDER_EVENT);
            }
            // Scope: Post proccessing
            {
                OnTriggerEvent(engine::BEFORE_POST_PROCCESSING_EVENT);
                frame.WaitMicroseconds(frame.GetDelay(), (frame.GetTickTime() - fLastRunTime) * 1000000);
                fLastRunTime = frame.GetTickTime();
                OnTriggerEvent(engine::AFTER_POST_PROCCESSING_EVENT);
                const float fStartPauseTime = frame.GetTickTime();
                while (bEngineRunning && !OnPauseEvent(frame.GetTickTime())) {
                    frame.WaitMicroseconds(frame.GetDelay());
                    RenderTexture();
                    UpdateKeyboardInput();
                }
                const float fEndPauseTime = frame.GetTickTime();
                frame.Rewind(fEndPauseTime - fStartPauseTime);
                OnTriggerEvent(engine::ON_UNPAUSE_EVENT);
            }
            OnTriggerEvent(engine::POST_RUNNING_EVENT);
        }

        OnTriggerEvent(engine::BEFORE_DESTROY_EVENT);
        const bool result = !OnDestroyEvent(); // Continue the thread until it gets destroyed
        OnTriggerEvent(engine::AFTER_DESTROY_EVENT);

        return result;
    }

    /// @brief Exits the engine thread and cleans up resources.
    /// @return True if exit was successful.
    bool GameEngine::ExitEngineThread() const
    {
        texture.ExitDevice();
        window.Destroy();
        return true;
    }

    /// @brief Handles the engine thread, including initialization, event loop, and exit.
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
        window.HandleMessage();
        thread.join();
        return true;
    }
} // namespace app

#endif // G_GAME_ENGINE_CPP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// END OF FILE ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////