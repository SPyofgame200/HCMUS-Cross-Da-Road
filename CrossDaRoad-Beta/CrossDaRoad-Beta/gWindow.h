/**
 * @file gWindow.h
 * @brief Contains window class for creating and managing windows using Win32 API
 *
**/

#ifndef G_WINDOW_H
#define G_WINDOW_H

#pragma comment(lib, "user32.lib")
#include <windows.h>
#include <string>

//=================================================================================================
// Include new header files here

//=================================================================================================

namespace app
{
	class GameEngine;
	/// @brief Class for creating and managing windows using Win32 API
	class Window
	{
	private: /// Properties
		HWND windowHandler;
		static GameEngine* sge;

	public: // Constructors & Destructor
		Window();
		Window(GameEngine* sge);
		~Window();

	public: // Constructor & Destructor functions
		bool Create(GameEngine* sge);
		bool Destroy() const;

	public: // Getters
		HWND GetWindowHandler() const;

	public: // Setters
		bool SetTitle(const std::string& sTitle) const;
		bool SetIcon(const std::string& sFilePath);
		bool SetFavicon(const std::string& sFilePath);

	public: // Window Event
		static bool HandleMessage();

	private: /// Internalities
		bool SetupTarget(GameEngine* sge);
		static bool RegisterWindowClass();
		bool CreateMainWindow();

	private: /// Static Internalities
		static LRESULT CALLBACK WindowEvent(HWND windowHandler, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static bool HandleWindowEvent(UINT uMsg, WPARAM wParam, LPARAM lParam);
		static bool HandleWindowLifecycleEvent(UINT uMsg);
		static bool HandleWindowKeyboardEvent(UINT uMsg, WPARAM wParam);
		static bool HandleWindowResizeEvent(WPARAM wParam, LPARAM lParam);
		static bool HandleWindowMouseEvent(UINT uMsg, WPARAM wParam, LPARAM lParam);
	};
}

#endif // G_WINDOW_H
