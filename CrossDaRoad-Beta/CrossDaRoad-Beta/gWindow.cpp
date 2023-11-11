#include "gUtils.h"
#include "gWindow.h"
#include "gGameEngine.h"

namespace app
{
	GameEngine* Window::sge = nullptr;

	HWND Window::GetWindowHandler() const
	{
		return windowHandler;
	}

	/// @brief Handles Windows messages in the main application window.
	/// @return True if message handling was successful.
	bool Window::HandleWindowMessage()
	{
		MSG msg;
		while (GetMessage(&msg, nullptr, 0, 0) > 0) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (msg.message == -1) {
			std::cerr << "GetMessage failed with error code: " << std::to_string(GetLastError()) << std::endl;
			return false;
		}
		return true;
	}

	bool Window::SetTarget(GameEngine* sge)
	{
		if (sge == nullptr) {
			return false;
		}
		this->sge = sge;
		return true;
	}

	// Function to register the window class
	bool Window::RegisterWindowClass()
	{
		WNDCLASS windowClass = {};

		// Set the window's cursor to the arrow cursor
		windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);

		// Specify window styles, including redrawing when resized and owning the
		// device context
		windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

		// Get the module handle for the application
		windowClass.hInstance = GetModuleHandle(nullptr);

		// Set the window procedure for handling window events
		windowClass.lpfnWndProc = WindowEvent;

		// These two values are typically not used in modern applications
		windowClass.cbClsExtra = 0;
		windowClass.cbWndExtra = 0;

		// Set the window's menu name and background brush (none in this case)
		windowClass.lpszMenuName = nullptr;
		windowClass.hbrBackground = nullptr;

		// Set the window class name (converted from ENGINE_NAME)
		windowClass.lpszClassName = to_text(engine::ENGINE_NAME);

		// Register the window class
		RegisterClass(&windowClass);

		return true;
	}

	// Function to create the window
	bool Window::CreateMainWindow()
	{
		constexpr DWORD extendedStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		constexpr DWORD style = WS_CAPTION | WS_SYSMENU | WS_VISIBLE;
		constexpr int cosmeticOffset = 27;

		// Calculate the window client size
		RECT windowRect = { 0, 0, sge->WindowWidth(), sge->WindowHeight() };
		AdjustWindowRectEx(&windowRect, style, FALSE, extendedStyle);
		const int width = windowRect.right - windowRect.left;
		const int height = windowRect.bottom - windowRect.top;

		// Create the application's main window
		windowHandler = CreateWindowEx(
			extendedStyle,                  // Extended window style
			engine::ENGINE_WIDE_NAME,       // Window class name
			engine::ENGINE_WIDE_NAME,       // Window default title
			style,                          // Window style
			cosmeticOffset, cosmeticOffset, // (X, Y) position of the window
			width, height,                  // Window size
			nullptr,                  // Handle to parent window (none in this case)
			nullptr,                  // Handle to menu (none in this case)
			GetModuleHandle(nullptr), // Handle to application instance
			sge // Pointer to user-defined data (typically used for storing object instance)
		);
		return true;
	}

	LRESULT CALLBACK Window::WindowEvent(const HWND windowHandler, const UINT uMsg, const WPARAM wParam, const LPARAM lParam)
	{
		/// Engine events
		if (sge)
			sge->OnFixedUpdateEvent(engine::PRE_WINDOW_EVENT);
		switch (uMsg) {
		case WM_CREATE:
			sge = static_cast<GameEngine*>(reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams);
			return 0;
		case WM_CLOSE:
			if (sge) {
				sge->bEngineRunning = false;
			}
			return 0;
		case WM_DESTROY:
			if (sge) {
				sge->OnForceDestroyEvent();
			}
			PostQuitMessage(0);
			return 0;
		}

		/// Load keyboard
		if (sge) {
			sge->OnFixedUpdateEvent(engine::BEFORE_LOAD_KEYBOARD_EVENT);
			switch (uMsg) {
			case WM_SETFOCUS:
				sge->keyboard.SetFocus(true);
				return 0;
			case WM_KILLFOCUS:
				sge->keyboard.SetFocus(false);
				return 0;
			case WM_KEYDOWN:
				sge->keyboard.UpdateKey(wParam, true);
				return 0;
			case WM_KEYUP:
				sge->keyboard.UpdateKey(wParam, false);
				return 0;
			}
		}

		// Calling handling function on default
		if (sge)
			sge->OnFixedUpdateEvent(engine::POST_WINDOW_EVENT);
		return DefWindowProc(windowHandler, uMsg, wParam, lParam);
	}



	// Main function for creating the window
	bool Window::Create(GameEngine* sge)
	{

		// Setup Window Target for Event Handling
		if (!SetTarget(sge)) {
			std::cerr << "Window::WindowCreate(*sge" << (sge == nullptr ? "= nullptr" : "") << "):";
			std::cerr << "Failed to setup a window target" << std::endl;
			return false;
		}

		// Register the window class
		if (!RegisterWindowClass()) {
			std::cerr << "Window::WindowCreate(*sge" << (sge == nullptr ? "= nullptr" : "") << "):";
			std::cerr << "Failed to register a window class" << std::endl;
			return false;
		}

		// Update viewport
		sge->screen.SetupWindowSize();
		sge->viewport.UpdateByScreen(sge->screen);

		// Create the main window
		if (!CreateMainWindow()) {
			std::cerr << "Window::WindowCreate(*sge" << (sge == nullptr ? "= nullptr" : "") << "):";
			std::cerr << "Failed to create a main window" << std::endl;
			return false;
		}

		// Return the window handler
		return true;
	}

	bool Window::Destroy() const
	{
		PostMessage(windowHandler, WM_DESTROY, 0, 0);
		return true;
	}

	bool Window::SetTitle(const std::string& sTitle) const
	{
		SetWindowText(windowHandler, to_text(sTitle));
		return true;
	}

	bool Window::SetIcon(const std::string& sFilePath) const
	{
		HANDLE hLoader = LoadImage(
			nullptr,                            // Module handle (nullptr for current process)
			to_text(engine::ICON_FILE_PATH),    // File path of the favicon
			IMAGE_ICON,                         // Specifies that an icon is being loaded
			0, 0,                               // Default width and height of the icon
			LR_LOADFROMFILE                     // Load the icon from a file
		);

		HICON hIcon = static_cast<HICON>(hLoader);

		if (!hIcon) {
			std::cerr << "Window::SetFavicon(sFilePath=\"" << engine::ICON_FILE_PATH << "\"): ";
			std::cerr << "Failed to load the icon" << std::endl;
			return false;
		}
		std::cerr << "Window::SetFavicon(sFilePath=\"" << engine::ICON_FILE_PATH << "\"): ";
		std::cerr << "Successfully loaded the application icon " << std::endl;
		SendMessage(windowHandler, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(hIcon));
		return true;
	}

	bool Window::SetFavicon(const std::string& sFilePath) const
	{
		HANDLE hLoader = LoadImage(
			nullptr,                            // Module handle (nullptr for current process)
			to_text(engine::FAVICON_FILE_PATH), // File path of the favicon
			IMAGE_ICON,                         // Specifies that an icon is being loaded
			0, 0,                               // Default width and height of the icon
			LR_LOADFROMFILE                     // Load the icon from a file
		);

		HICON hFavicon = static_cast<HICON>(hLoader);

		if (!hFavicon) {
			std::cerr << "Can not open engine favicon (path = \"" << sFilePath << "\")" << std::endl;
			std::cerr << "Failed to load the favicon" << std::endl;
			return false;
		}
		std::cerr << "Window::SetFavicon(sFilePath=\"" << engine::FAVICON_FILE_PATH << "\"): ";
		std::cerr << "Successfully loaded the application favicon " << std::endl;
		SendMessage(windowHandler, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hFavicon));
		return true;
	}
}