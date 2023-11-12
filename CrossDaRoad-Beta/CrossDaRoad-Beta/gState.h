#ifndef G_STATE_H
#define G_STATE_H

#include "gKey.h"
#include <cstring>
#include <cstdint>
#include <iostream>
#include <chrono>
#include <string>

#define BUTTON_STATE
#ifdef BUTTON_STATE

/**
 * @file gState.h
 *
 * @brief Contains button enumeration, state of button, screen, viewport, frame, keyboard, and mouse
 *
 * This file contains button enumeration for button input (prototype) and button state for storing button state,
 * screen state for storing screen state, viewport state for storing viewport state, frame state for storing frame state,
 * keyboard state for storing keyboard state, and mouse state for storing mouse state.
**/
enum Button
{
	IDLING,				///< The button is waiting for the next action
	PRESSED,			///< The button was actively pressed	
	HOLDING,			///< The button is being continuously held down
	RELEASED,			///< The button was released after being pressed
	DISABLED_IDLING,    ///< The button is wating for the next action, even though being disabled
	DISABLED_PRESSED,   ///< The button was pressed, but it is disabled
	DISABLED_HOLDING,   ///< The button is being held, but it is disabled
	DISABLED_RELEASED,	///< The button was released, but it is disabled
};

/// @brief Class for storing the state of a button.
class ButtonState
{
public:
	bool bPressed;  ///< Set once during the frame the event occurs
	bool bHolding;  ///< Set true for all frames between pressed and released events
	bool bReleased; ///< Set once during the frame the event occurs
	bool bDisabled; ///< If the button shouldnt be used

public:
	/// @brief Default constructor 
	ButtonState()
	{
		bPressed = false;
		bHolding = false;
		bReleased = false;
		bDisabled = false;
	}
};

#endif // BUTTON_STATE

#define SCREEN_STATE
#ifdef SCREEN_STATE
/// @brief Class for storing the state of the screen.
class ScreenState
{
private:
	uint32_t nScreenWidth;  ///< Screen width in pixels
	uint32_t nScreenHeight; ///< Screen height in pixels
	uint32_t nPixelWidth;   ///< Pixel width in pixels
	uint32_t nPixelHeight;  ///< Pixel height in pixels
	int32_t nWindowWidth;   ///< Window width in pixels
	int32_t nWindowHeight;  ///< Window height in pixels (negative value means fullscreen)

public: // Constructor
	/// @brief Default constructor
	ScreenState()
	{
		SetScreenSize(256, 240);
		SetPixelSize(4, 4);
		SetWindowSize(0, 0);
	}

public: // Setters
	void SetScreenWidth(uint32_t nWidth);
	void SetScreenHeight(uint32_t nHeight);
	void SetScreenSize(uint32_t nWidth, uint32_t nHeight);
	void SetPixelWidth(uint32_t nWidth);
	void SetPixelHeight(uint32_t nHeight);
	void SetPixelSize(uint32_t nWidth, uint32_t nHeight);
	void SetWindowWidth(int32_t nWidth);
	void SetWindowHeight(int32_t nHeight);
	void SetWindowSize(int32_t nWidth, int32_t nHeight);

public: // Getters
	uint32_t GetScreenWidth() const;
	uint32_t GetScreenHeight() const;
	uint32_t GetScreenSize() const;
	uint32_t GetPixelWidth() const;
	uint32_t GetPixelHeight() const;
	uint32_t GetPixelSize() const;
	int32_t GetWindowWidth() const;
	int32_t GetWindowHeight() const;
	int32_t GetWindowSize() const;

public: // Methods
	void SetupWindowSize();
};
#endif // SCREEN_STATE

#define VIEWPORT_STATE
#ifdef VIEWPORT_STATE

/// @brief Class for storing the state of the viewport.
class ViewportState
{
private:
	int32_t nWidth;  ///< Viewport width in pixels
	int32_t nHeight; ///< Viewport height in pixels
	int32_t nPosX;   ///< Viewport X position in pixels
	int32_t nPosY;   ///< Viewport Y position in pixels

public: // Constructor
	/// @brief Default constructor
	ViewportState()
	{
		SetSize(0, 0);
		SetPosition(0, 0);
	}

public: // Setters
	void SetWidth(int32_t width);
	void SetHeight(int32_t height);
	void SetSize(int32_t width, int32_t height);
	void SetX(int32_t x);
	void SetY(int32_t y);
	void SetPosition(int32_t x, int32_t y);

public: // Getters
	int32_t GetWidth() const;
	int32_t GetHeight() const;
	int32_t GetX() const;
	int32_t GetY() const;

public: // Methods
	bool UpdateByScreen(const ScreenState& screen);
};
#endif // VIEWPORT STATE

#define FRAME_STATE
#ifdef FRAME_STATE

#ifdef OLD_DELAY
//               Best              Smooth             <MEDIUM>                  Good
// Microseconds:   1  500 1000 2500 5000 6000 7200 8000 9000 10000 12500 15000 17500 20000 27000
//  Average FPS: 360+ 300  240  185  120  111   96   90   80    75    64    55    48    45    32
//                       <HIGH>              Stable                 Safe                   <SLOW>
enum FrameDelay
{
	// SLOW_FPS
	SLOW_FPS_DELAY = 27000,  ///<  32 FPS
	GOOD_FPS_DELAY = 17500,  ///<  48 FPS
	SAFE_FPS_DELAY = 12500,  ///<  64 FPS
	// MEDIUM_FPS
	MEDIUM_FPS_DELAY = 9000, ///<  80 FPS
	STABLE_FPS_DELAY = 7200, ///<  96 FPS
	SMOOTH_FPS_DELAY = 5000, ///< 120 FPS
	// HIGH_FPS
	HIGH_FPS_DELAY = 1000,   ///< 240 FPS
	BEST_FPS_DELAY = 1,      ///< 360 FPS
	ZERO_FPS_DELAY = 0,      ///< ... FPS
};
#else
/// @brief Enumeration for the frame delay values.
enum FrameDelay
{
	// SLOWEST_FPS (for debugging)
	DEBUG1_FPS_DELAY = 1000000, ///< 1 FPS
	DEBUG2_FPS_DELAY = 500000,  ///< 2 FPS
	DEBUG3_FPS_DELAY = 333333,  ///< 3 FPS
	DEBUG4_FPS_DELAY = 250000,  ///< 4 FPS
	DEBUG6_FPS_DELAY = 166666,  ///< 6 FPS
	DEBUG8_FPS_DELAY = 125000,  ///< 8 FPS
	DEBUG10_FPS_DELAY = 100000, ///< 10 FPS
	DEBUG12_FPS_DELAY = 83333,  ///< 12 FPS
	DEBUG16_FPS_DELAY = 62500,  ///< 16 FPS

	// SLOW_FPS (bad gaming experience)
	SLOW_FPS_DELAY = 31250, ///< 32 FPS
	GOOD_FPS_DELAY = 20833, ///< 48 FPS
	SAFE_FPS_DELAY = 15625, ///< 64 FPS

	// MEDIUM_FPS (game recommendation)
	MEDIUM_FPS_DELAY = 12500, ///<  80 FPS
	STABLE_FPS_DELAY = 10416, ///<  96 FPS <--- Default
	SMOOTH_FPS_DELAY = 8333,  ///< 120 FPS

	// HIGH_FPS (requires good computer)
	HIGH_FPS_DELAY = 4166, ///< 240 FPS
	BEST_FPS_DELAY = 2777, ///< 360 FPS
	ZERO_FPS_DELAY = 0,    ///< +oo FPS
};
#endif

/// @brief Class for storing the state of the frame.
class FrameState
{
private:
	using clock_t = std::chrono::time_point<std::chrono::system_clock>; ///< Clock type for the timer.
	clock_t clockTimer;                                                 ///< The timer for the clock.
	clock_t frameTimer;                                                 ///< The timer for the frame.
	float fFrameTimer;                                                  ///< The timer for the frame.
	int nFrameCount;                                                    ///< The frame count.
	int nCurrentFPS;                                                    ///< The current FPS.
	FrameDelay eFrameDelay;                                             ///< The frame delay. (default: STABLE_FPS_DELAY)
	float fRewindTime;
	float fRewindTemp;

public: // Constructor
	FrameState(float fTimer = 0, float fRewind = 0, int nFrame = 0, int nFPS = 0);

public: // Setters
	bool SetDelay(FrameDelay eDelay);
	void CreateTimer(float fTimer = 0, float fRewind = 0, int nFrame = 0, int nFPS = 0);
	void ResetTimer();

public: // Getters
	FrameDelay GetDelay() const;
	int GetFPS() const;
	std::string ShowFPS() const;
	float GetTickTime() const;
	float GetElapsedTime(bool bUpdate = true);

public: // Update & Wait methods
	bool FrameUpdate(float fElapsedTime);
	bool Rewind(float fRewind);
	static void WaitMicroseconds(const int32_t& nWait);
	static void WaitMicroseconds(const int32_t& nWait, const float& fPassedTime);
};
#endif // FRAME_STATE

#define KEYBOARD_STATE
#ifdef KEYBOARD_STATE
constexpr size_t KEYBOARD_SIZE = 256;

/// @brief Class for storing the state of the keyboard.
class KeyboardState
{
private:
	bool bHasInputFocus;                   ///< True if the window has input focus.
	bool bKeys[KEYBOARD_SIZE];             ///< The current state of the keyboard.
	bool bKeysCache[KEYBOARD_SIZE];        ///< The cached state of the keyboard.
	ButtonState pKeysState[KEYBOARD_SIZE]; ///< The state of the keyboard.
	std::map<uint16_t, uint8_t> mapKeys;   ///< The map of the keyboard.

public: // Constructors & Destructor
	KeyboardState();
	~KeyboardState();

public: // Setters
	void ResetKeyboard();
	void SetFocus(bool bValue);
	bool DisableKey(const app::Key& key);
	bool EnableKey(const app::Key& key);

public: // Getters
	Button GetKey(const app::Key& key) const;
	ButtonState GetKeyState(const app::Key& key) const;

public: // Checkers
	bool IsFocused() const;
	bool IsKeyIdling(const app::Key& key, bool bIgnoreDisability = false) const;
	bool IsKeyPressed(const app::Key& key, bool bIgnoreDisability = false) const;
	bool IsKeyHolding(const app::Key& key, bool bIgnoreDisability = false) const;
	bool IsKeyReleased(const app::Key& key, bool bIgnoreDisability = false) const;

public: // Update methods
	template <class Integer>
	void UpdateKey(const Integer& nID, const bool bValue)
	{
		const uint16_t keyID = static_cast<uint16_t>(nID);
		bKeysCache[mapKeys[keyID]] = bValue;
	}
	void UpdateKeyboard();
};
#endif // KEYBOARD_STATE

// Currently unused
// #define MOUSE_STATE
#ifdef MOUSE_STATE
class MouseState
{
private:
	int32_t nMousePosX;
	int32_t nMousePosY;
	int32_t nMouseWheelDelta;
	int32_t nMouseCachePosX;
	int32_t nMouseCachePosY;
	int32_t nMouseCacheWheelDelta;
	bool bHasMouseFocus;
	bool pMouseNewState[5];
	bool pMouseOldState[5];
	ButtonState pMouseState[5];

public:
	MouseState()
	{
		nMousePosX = 0;
		nMousePosY = 0;
		nMouseWheelDelta = 0;

		nMouseCachePosX = 0;
		nMouseCachePosY = 0;
		nMouseCacheWheelDelta = 0;

		bHasMouseFocus = false;

		memset(pMouseNewState, false, sizeof(pMouseNewState));
		memset(pMouseOldState, false, sizeof(pMouseOldState));
		memset(pMouseState, false, sizeof(pMouseState));
	}

public:
	void SetMousePosX(int32_t nPosX)
	{
		nMousePosX = nPosX;
	}
	void SetMousePosY(int32_t nPosY)
	{
		nMousePosY = nPosY;
	}
	void SetMousePosition(int32_t nPosX, int32_t nPosY)
	{
		SetMousePosX(nPosX);
		SetMousePosY(nPosY);
	}
	void SetMouseWheel(int32_t nDelta)
	{
		nMouseWheelDelta = nDelta;
	}

	void SetMouseCachePosX(int32_t nPosX)
	{
		nMouseCachePosX = nPosX;
	}
	void SetMouseCachePosY(int32_t nPosY)
	{
		nMouseCachePosY = nPosY;
	}
	void SetMouseCachePosition(int32_t nPosX, int32_t nPosY)
	{
		SetMouseCachePosX(nPosX);
		SetMouseCachePosY(nPosY);
	}

	void SetMouseCacheWheel(int32_t nDelta)
	{
		nMouseCacheWheelDelta = nDelta;
	}
	void SetMouseFocus(bool bFocus)
	{
		bHasMouseFocus = bFocus;
	}

	void UpdateMouseState(int32_t nID, bool bState)
	{
		pMouseNewState[nID] = bState;
	}

public:
	int32_t GetMousePosX() const
	{
		return nMousePosX;
	}
	int32_t GetMousePosY() const
	{
		return nMousePosY;
	}
	int32_t GetMouseWheel() const
	{
		return nMouseWheelDelta;
	}
	int32_t GetMouseCachePosX() const
	{
		return nMouseCachePosX;
	}
	int32_t GetMouseCachePosY() const
	{
		return nMouseCachePosY;
	}
	int32_t GetMouseCacheWheel() const
	{
		return nMouseCacheWheelDelta;
	}
	int32_t IsMouseFocus() const
	{
		return bHasMouseFocus;
	}
	ButtonState GetMouseState(int32_t nID) const
	{
		return pMouseState[nID];
	}

public:
	void UpdateState()
	{
		const int size = sizeof(pMouseState) / sizeof(pMouseState[0]);
		for (int button = 0; button < 5; button++) {
			// Reset button press and release flags
			pMouseState[button].bPressed = false;
			pMouseState[button].bReleased = false;
			if (pMouseNewState[button] != pMouseOldState[button]) {
				if (pMouseNewState[button]) { // Button is newly pressed
					pMouseState[button].bPressed = !pMouseState[button].bHolding;
					pMouseState[button].bHolding = true;
				}
				else { // Button is newly released
					pMouseState[button].bReleased = true;
					pMouseState[button].bHolding = false;
				}
			}
			pMouseOldState[button] = pMouseNewState[button];
		}
	}

	void FlushCache()
	{
		nMousePosX = nMouseCachePosX;
		nMousePosY = nMouseCachePosY;
		nMouseWheelDelta = nMouseCacheWheelDelta;
		nMouseCacheWheelDelta = 0;
	}
};
#endif // BUTTON_STATE

#endif // G_STATE_H
