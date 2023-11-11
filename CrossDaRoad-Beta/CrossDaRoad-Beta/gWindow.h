#ifndef G_WINDOW_H
#define G_WINDOW_H

#pragma comment(lib, "user32.lib")
#include <windows.h>
#include <string>

namespace app
{
	class GameEngine;
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
		bool SetIcon(const std::string& sFilePath) const;
		bool SetFavicon(const std::string& sFilePath) const;

	public: /// Window Event
		bool HandleMessage();

	private: /// Internalities
		bool SetTarget(GameEngine* sge);
		bool RegisterWindowClass();
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
