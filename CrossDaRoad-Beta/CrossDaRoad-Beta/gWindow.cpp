#include "gUtils.h"
#include "gWindow.h"
#include "gGameEngine.h"

namespace app
{
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

	void Window::SetTarget(GameEngine* sge)
	{
		this->sge = sge;
	}

	// Function to register the window class
	void Window::RegisterWindowClass(WNDCLASS& windowClass)
	{
		// Set the window's cursor to the arrow cursor
		windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);

		// Specify window styles, including redrawing when resized and owning the
		// device context
		windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

		// Get the module handle for the application
		windowClass.hInstance = GetModuleHandle(nullptr);

		// Set the window procedure for handling window events
		windowClass.lpfnWndProc = sge->WindowEvent;

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
	}

	// Main function for creating the window
	HWND Window::WindowCreate(GameEngine *sge)
	{
		WNDCLASS windowClass = {};

		// Register the window class
		SetTarget(sge);
		RegisterWindowClass(windowClass);

		// Update viewport
		sge->screen.SetupWindowSize();
		sge->viewport.UpdateByScreen(sge->screen);

		// Create the main window
		sge->CreateMainWindow();

		// Return the window handler
		return windowHandler;
	}
}