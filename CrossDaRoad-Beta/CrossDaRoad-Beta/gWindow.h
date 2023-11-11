#ifndef G_WINDOW_H
#define G_WINDOW_H

#pragma comment(lib, "user32.lib")
#include <windows.h>

namespace app
{
	class GameEngine;
	class Window
	{
	public:
		HWND windowHandler = nullptr;

	private:
		static GameEngine* sge;
		void SetTarget(GameEngine* sge);
		void RegisterWindowClass(WNDCLASS& wc);
		void CreateMainWindow();
		static LRESULT CALLBACK WindowEvent(HWND windowHandler, UINT uMsg, WPARAM wParam, LPARAM lParam);

	public:
		bool HandleWindowMessage();
		HWND WindowCreate(GameEngine* sge);
	};
}

#endif // G_WINDOW_H
