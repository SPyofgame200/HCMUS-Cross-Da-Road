/**
 * @file gState.cpp
 *
 * @brief Contains button enumeration, state of button, screen, viewport, frame, keyboard, and mouse implementation
 *
 * This file implements button enumeration, state of button, screen, viewport, frame, keyboard, and mouse for game state management.
**/
#include "gState.h"

//===========================================================================================
//========================= SCREEN STATE ====================================================
//===========================================================================================

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// SETTERS ////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Setter for the screen width.
/// @param nWidth width of the screen
void ScreenState::SetScreenWidth(uint32_t nWidth)
{
	nScreenWidth = nWidth;
}

/// @brief Setter for the screen height.
/// @param nHeight height of the screen
void ScreenState::SetScreenHeight(uint32_t nHeight)
{
	nScreenHeight = nHeight;
}

/// @brief Setter for the screen size.
/// @param nWidth width of the screen
/// @param nHeight height of the screen
void ScreenState::SetScreenSize(uint32_t nWidth, uint32_t nHeight)
{
	SetScreenWidth(nWidth);
	SetScreenHeight(nHeight);
}

/// @brief Setter for the pixel width.
/// @param nWidth width of the pixel
void ScreenState::SetPixelWidth(uint32_t nWidth)
{
	nPixelWidth = nWidth;
}

/// @brief Setter for the pixel height.
/// @param nHeight height of the pixel
void ScreenState::SetPixelHeight(uint32_t nHeight)
{
	nPixelHeight = nHeight;
}

/// @brief Setter for the pixel size.
/// @param nWidth width of the pixel
/// @param nHeight height of the pixel
void ScreenState::SetPixelSize(uint32_t nWidth, uint32_t nHeight)
{
	SetPixelWidth(nWidth);
	SetPixelHeight(nHeight);
}

/// @brief Setter for the window width.
/// @param nWidth width of the window
void ScreenState::SetWindowWidth(int32_t nWidth)
{
	nWindowWidth = nWidth;
}

/// @brief Setter for the window height.
/// @param nHeight height of the window
void ScreenState::SetWindowHeight(int32_t nHeight)
{
	nWindowHeight = nHeight;
}

/// @brief Setter for the window size.
/// @param nWidth width of the window
/// @param nHeight height of the window
void ScreenState::SetWindowSize(int32_t nWidth, int32_t nHeight)
{
	SetWindowWidth(nWidth);
	SetWindowHeight(nHeight);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// GETTERS ////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Getter for the screen width.
uint32_t ScreenState::GetScreenWidth() const
{
	return nScreenWidth;
}

/// @brief Getter for the screen height.
uint32_t ScreenState::GetScreenHeight() const
{
	return nScreenHeight;
}

/// @brief Getter for the screen size.
uint32_t ScreenState::GetScreenSize() const
{
	return static_cast<uint32_t>(static_cast<uint64_t>(1) * GetScreenWidth() * GetScreenHeight());
}

/// @brief Getter for the pixel width.
uint32_t ScreenState::GetPixelWidth() const
{
	return nPixelHeight;
}

/// @brief Getter for the pixel height.
uint32_t ScreenState::GetPixelHeight() const
{
	return nPixelHeight;
}

/// @brief Getter for the pixel size.
uint32_t ScreenState::GetPixelSize() const
{
	return static_cast<uint32_t>(static_cast<uint64_t>(1) * GetPixelWidth() * GetPixelHeight());
}

/// @brief Getter for the window width.
int32_t ScreenState::GetWindowWidth() const
{
	return nWindowWidth;
}

/// @brief Getter for the window height.
int32_t ScreenState::GetWindowHeight() const
{
	return nWindowHeight;
}

/// @brief Getter for the window size.
int32_t ScreenState::GetWindowSize() const
{
	return static_cast<int32_t>(static_cast<int64_t>(1) * GetWindowWidth() * GetWindowHeight());
}

/// @brief Setup the window size by the screen state data
void ScreenState::SetupWindowSize()
{
	nWindowWidth = static_cast<int32_t>(nScreenWidth * nPixelWidth);
	nWindowHeight = static_cast<int32_t>(nScreenHeight * nPixelHeight);
}

//=============================================================================================
//========================= VIEWPORT STATE ====================================================
//=============================================================================================

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// SETTERS ////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Setter for the viewport width.
/// @param width width of the viewport
void ViewportState::SetWidth(const int32_t width)
{
	nWidth = width;
}

/// @brief Setter for the viewport height.
/// @param height height of the viewport
void ViewportState::SetHeight(const int32_t height)
{
	nHeight = height;
}
/// @brief Setter for the viewport size.
/// @param width width of the viewport
/// @param height height of the viewport
void ViewportState::SetSize(const int32_t width, const int32_t height)
{
	SetWidth(width);
	SetHeight(height);
}

/// @brief Setter for the viewport x position.
/// @param x x position of the viewport
void ViewportState::SetX(const int32_t x)
{
	nPosX = x;
}

/// @brief Setter for the viewport y position.
/// @param y y position of the viewport
void ViewportState::SetY(const int32_t y)
{
	nPosY = y;
}

/// @brief Setter for the viewport position.
/// @param x x position of the viewport
/// @param y y position of the viewport
void ViewportState::SetPosition(const int32_t x, const int32_t y)
{
	SetX(x);
	SetY(y);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// GETTERS ////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Getter for the viewport width.
int32_t ViewportState::GetWidth() const
{
	return nWidth;
}

/// @brief Getter for the viewport height.
int32_t ViewportState::GetHeight() const
{
	return nHeight;
}

/// @brief Getter for x position of the viewport.
int32_t ViewportState::GetX() const
{
	return nPosX;
}

/// @brief Getter for y position of the viewport.
int32_t ViewportState::GetY() const
{
	return nPosY;
}

/// @brief Update the viewport state by the screen state data.
/// @param screen The screen state data.
/// @return true If the viewport state was updated, false otherwise.
bool ViewportState::UpdateByScreen(const ScreenState& screen)
{
	// Extract screen data
	const int32_t nScreenWidth = screen.GetScreenWidth();
	const int32_t nScreenHeight = screen.GetScreenHeight();
	const int32_t nPixelWidth = screen.GetPixelWidth();
	const int32_t nPixelHeight = screen.GetPixelHeight();
	const int32_t nWindowWidth = screen.GetWindowWidth();
	const int32_t nWindowHeight = screen.GetWindowHeight();
	const float nScreenAspect = static_cast<float>(nScreenWidth * nPixelWidth) / static_cast<float>(nScreenHeight * nPixelHeight);

	// Calculate the viewport width and height to maintain the screen aspect ratio
	int32_t nViewportWidth = nWindowWidth;
	int32_t nViewportHeight = static_cast<int32_t>(nViewportWidth / nScreenAspect);

	// Adjust if the calculated height is greater than the window height
	if (nViewportHeight > nWindowHeight) {
		nViewportHeight = nWindowHeight;
		nViewportWidth = static_cast<int32_t>(nViewportHeight * nScreenAspect);
	}

	// No suitable aspect found
	if (nViewportWidth > nWindowWidth) {
		return false;
	}

	// Center the viewport within the window
	const int32_t nViewportX = (nWindowWidth - nViewportWidth) / 2;
	const int32_t nViewportY = (nWindowHeight - nViewportHeight) / 2;

	// Update the viewport properties
	SetSize(nViewportWidth, nViewportHeight);
	SetPosition(nViewportX, nViewportY);
	return true;
}

//=============================================================================================
//========================= FRAME STATE =======================================================
//=============================================================================================

/// @brief Parameterized constructor
/// @param fTimer Timer in
/// @param nFrame 
/// @param nFPS  
FrameState::FrameState(const float fTimer, const float fRewind, const int nFrame, const int nFPS)
{
	CreateTimer(fTimer, fRewind, nFrame, nFPS);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// SETTERS ////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Setter for the frame delay.
/// @param eDelay The frame delay to set.
/// @return Always return true by default.
bool FrameState::SetDelay(FrameDelay eDelay)
{
	eFrameDelay = eDelay;
	return true;
}
/// @brief Create the frame timer.
/// @param fTimer Timer in seconds.
/// @param nFrame Frame count.
/// @param nFPS FPS count.
void FrameState::CreateTimer(const float fTimer, const float fRewind, const int nFrame, const int nFPS)
{
	fFrameTimer = fTimer;
	fRewindTime = fRewind;
	nFrameCount = nFrame;
	nCurrentFPS = nFPS;
	eFrameDelay = FrameDelay::STABLE_FPS_DELAY;
	clockTimer = std::chrono::system_clock::now();
	frameTimer = std::chrono::system_clock::now();
}

/// @brief Reset the frame timer.
void FrameState::ResetTimer()
{
	frameTimer = std::chrono::system_clock::now();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// GETTERS ////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Getter for the frame delay.
FrameDelay FrameState::GetDelay() const
{
	return eFrameDelay;
}
/// @brief Getter for the frame timer.
int FrameState::GetFPS() const
{
	return nCurrentFPS;
}
/// @brief Getter for FPS as a string.
std::string FrameState::ShowFPS() const
{
	return "[FPS: " + std::to_string(GetFPS()) + "]";
}
/// @brief Getter for tick time 
float FrameState::GetTickTime() const
{
	const clock_t currentTimer = std::chrono::system_clock::now();
	const float fTickTime = std::chrono::duration<float>(currentTimer - clockTimer).count() - fRewindTime;
	return fTickTime;
}
/// @brief Getter for elapsed time
/// @param bUpdate If true, update the frame state
/// @return The elapsed time
float FrameState::GetElapsedTime(const bool bUpdate)
{
	const clock_t currentTimer = std::chrono::system_clock::now();
	const float fElapsedTime = std::chrono::duration<float>(currentTimer - frameTimer).count() - fRewindTemp;
	if (bUpdate) {
		frameTimer = currentTimer;
		FrameUpdate(fElapsedTime);
		fRewindTemp = 0;
	}
	return fElapsedTime;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// UPDATE & WAIT METHODS //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Update the frame 
/// @param fElapsedTime elapsed time 
/// @return true if the frame is updated, false otherwise.
bool FrameState::FrameUpdate(const float fElapsedTime)
{
	fFrameTimer += fElapsedTime;
	nFrameCount++;
	if (fFrameTimer >= 1.0f) {
		const int nSecondPassed = static_cast<int>(floor(fFrameTimer)) + 1;
		fFrameTimer = fmod(fFrameTimer, 1.0f);
		fFrameTimer -= 1.0f;
		nCurrentFPS = nFrameCount / nSecondPassed;
		nFrameCount = 0;
		return true;
	}
	return false;
}
/// @brief Rewind the frame timer
/// @param fRewind The time to rewind
/// @return True if the frame timer is rewinded, false otherwise
bool FrameState::Rewind(float fRewind)
{
	fRewindTemp += fRewind;
	fRewindTime += fRewind;
	return true;
}
/// @brief Wait microseconds for the frame timer to be stable before continuing
/// @param nWait The time to wait
void FrameState::WaitMicroseconds(const int32_t& nWait)
{
	if (nWait <= 0) {
		return;
	}
	const auto start = std::chrono::high_resolution_clock::now();
	while (true) {
		auto now = std::chrono::high_resolution_clock::now();
		auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(now - start);
		if (microseconds.count() >= nWait) {
			break;
		}
	}
}
/// @brief Wait microseconds for the frame timer to be stable before continuing
/// @param nWait The time to wait
void FrameState::WaitMicroseconds(const int32_t& nWait, const float& fPassedTime)
{
	if (nWait <= static_cast<int32_t>(fPassedTime)) {
		return;
	}
	return WaitMicroseconds(nWait - static_cast<int32_t>(fPassedTime));
}



/// @brief Default constructor
KeyboardState::KeyboardState()
{
	ResetKeyboard();
}

/// @brief Destructor
KeyboardState::~KeyboardState()
{
	mapKeys.clear();
	std::cerr << "app::KeyboardState::~KeyboardState(): Successfully destructed" << std::endl;
}

/// @brief Setter to reset the keyboard state object
void KeyboardState::ResetKeyboard()
{
	mapKeys = app::CreateMapKey();
	bHasInputFocus = false;
	memset(bKeysCache, false, sizeof(bKeysCache));
	memset(bKeys, false, sizeof(bKeys));
	memset(pKeysState, false, sizeof(pKeysState));
}

/// @brief Setter for the key state of the keyboard state object
/// @param bValue Value to set (true: pressed, false: released)
void KeyboardState::SetFocus(const bool bValue)
{
	bHasInputFocus = bValue;
}

/// @brief Check if the keyboard state object has input focus
/// @return true if the keyboard state object has input focus, false otherwise
bool KeyboardState::IsFocused() const
{
	return bHasInputFocus;
}

/// @brief Update the keyboard state object
void KeyboardState::UpdateKeyboard()
{
	for (int key = 0; key < KEYBOARD_SIZE; key++) {
		// Reset key press and release flags
		pKeysState[key].bPressed = false;
		pKeysState[key].bReleased = false;
		if (bKeysCache[key] != bKeys[key]) {
			if (bKeysCache[key]) { // Key is newly pressed
				pKeysState[key].bPressed = !pKeysState[key].bHolding;
				pKeysState[key].bHolding = true;
			}
			else { // Key is newly released
				pKeysState[key].bReleased = true;
				pKeysState[key].bHolding = false;
			}
		}
		bKeys[key] = bKeysCache[key];
	}
}

/// @brief Setter to disable a key of the keyboard state object
/// @param key The key to disable
/// @return Always return true by default
bool KeyboardState::DisableKey(const app::Key& key)
{
	pKeysState[key].bDisabled = true;
	return true;
}
/// @brief Setter to enable a key of the keyboard state object
/// @param key The key to enable
/// @return Always return true by default
bool KeyboardState::EnableKey(const app::Key& key)
{
	pKeysState[key].bDisabled = false;
	return true;
}
/// @brief Getter for the key state of the keyboard state object
/// @param key The key to get the state
/// @return State of the key (Button)
Button KeyboardState::GetKey(const app::Key& key) const
{
	if (pKeysState[key].bReleased) {
		return (pKeysState->bDisabled) ? Button::DISABLED_RELEASED : Button::RELEASED;
	}
	else if (pKeysState[key].bHolding) {
		return (pKeysState->bDisabled) ? Button::DISABLED_HOLDING : Button::HOLDING;
	}
	else if (pKeysState[key].bPressed) {
		return (pKeysState->bDisabled) ? Button::DISABLED_PRESSED : Button::PRESSED;
	}
	else {
		return (pKeysState->bDisabled) ? Button::DISABLED_IDLING : Button::IDLING;
	}
}
/// @brief Getter for the key state of the keyboard state object
/// @param key Key to get the state
/// @return Button state of the key
ButtonState KeyboardState::GetKeyState(const app::Key& key) const
{
	return pKeysState[key];
}

/// @brief Check if the key is idling
/// @param key Key to check
/// @param bIgnoreDisability If true, ignore the key disability
/// @return true if the key is idling, false otherwise
bool KeyboardState::IsKeyIdling(const app::Key& key, bool bIgnoreDisability) const
{
	return (GetKey(key) == IDLING) || (bIgnoreDisability && GetKey(key) == DISABLED_IDLING);
}

/// @brief Check if the key is pressed
/// @param key Key to check 
/// @param bIgnoreDisability If true, ignore the key disability
/// @return true if the key is pressed, false otherwise
bool KeyboardState::IsKeyPressed(const app::Key& key, bool bIgnoreDisability) const
{
	return (GetKey(key) == PRESSED) || (bIgnoreDisability && GetKey(key) == DISABLED_PRESSED);
}

/// @brief Check if the key is holding
/// @param key Key to check
/// @param bIgnoreDisability If true, ignore the key disability 
/// @return true if the key is holding, false otherwise
bool KeyboardState::IsKeyHolding(const app::Key& key, bool bIgnoreDisability) const
{
	return (GetKey(key) == HOLDING) || (bIgnoreDisability && GetKey(key) == DISABLED_HOLDING);
}

/// @brief Check if the key is released
/// @param key Key to check
/// @param bIgnoreDisability If true, ignore the key disability 
/// @return true if the key is released, false otherwise
bool KeyboardState::IsKeyReleased(const app::Key& key, bool bIgnoreDisability) const
{
	return (GetKey(key) == RELEASED) || (bIgnoreDisability && GetKey(key) == DISABLED_RELEASED);
}

