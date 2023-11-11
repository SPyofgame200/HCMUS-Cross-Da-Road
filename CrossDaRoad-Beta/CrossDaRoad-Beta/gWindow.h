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
	private: /// Window Internality
		HWND windowHandler = nullptr;
		static GameEngine* sge;
		bool SetTarget(GameEngine* sge);
		bool RegisterWindowClass();
		bool CreateMainWindow();
		static LRESULT CALLBACK WindowEvent(HWND windowHandler, UINT uMsg, WPARAM wParam, LPARAM lParam);

	public: // Getters
		HWND GetWindowHandler() const;

	public: // Setters
		bool SetTitle(const std::string& sTitle) const;
		bool SetIcon(const std::string& sFilePath) const;
		bool SetFavicon(const std::string& sFilePath) const;

	public: /// Window Event
		bool HandleWindowMessage();
		bool Create(GameEngine* sge);
		bool Destroy() const;
	};
}

#endif // G_WINDOW_H
