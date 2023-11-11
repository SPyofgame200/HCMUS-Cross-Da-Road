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
		GameEngine* sge = nullptr;
		HWND windowHandler = nullptr;
		bool HandleWindowMessage();
		void SetTarget(GameEngine* sge);
		void RegisterWindowClass(WNDCLASS& wc);
		HWND WindowCreate(GameEngine* sge);
	};
}

#endif // G_WINDOW_H
