/**
 * @file hMenu.h
 *
 * @brief Contains menu class
 *
 * This file contains menu class for menu window management.
**/

#ifndef C_MENU_H
#define C_MENU_H

#include "uSound.h"
#include "uAppConst.h"
#include "cAssetManager.h"
#include <vector>

// Forward declaration
class cApp;

/// @brief Class for menu window management
class hMenu
{
public:
	/// @brief  Enumeration for menu options 
	enum AppOption
	{
		NEW_GAME = 0, ///< New game window
		APP_GAME = 1, ///< Continue game window
		SETTINGS = 2, ///< Settings window
		ABOUT_US = 3, ///< About us window
		APP_EXIT = 4, ///< Exit application window
		APP_MENU = 5, ///< Menu window
	};
	enum PauseOption
	{
		RESUMING = 0, ///< Resume game 
		APP_SAVE = 1, ///< Save game
		APP_BACK = 2, ///< Back to menu
	};

private: /// Target
	cApp* app;

private: /// Checker
	bool bWantToExit;

private: /// Music
	bool bMusicPlaying = false; ///< Flag for music playing state (true = playing, false = not playing)

private: /// Menu HUD
	AppOption eMenuOption;							 ///< Current option
	std::vector<const char*> sAppOptionLabels;  ///< AppOption labels for menu window
	int nAppOptionLimit;						 ///< Maximum number of options
	int nAppOptionValue; 						 ///< Current option index

private: /// Pause HUD
	PauseOption ePauseOption; ///< Current option 
	std::string sPauseOptionLabels[3] = { "resume", "save", "exit" };  ///< PauseOption labels for pause window
	int nPauseOptionValue; ///< Current option index
	int nPauseOptionLimit; ///< Maximum number of options

private: /// Game Over HUD
	bool bPlayAgain = true;

public: // Constructor & Destructor
	hMenu();
	hMenu(cApp* app);
	~hMenu();

public: // Initialization & Clean-up
	bool SetupTarget(cApp* app);
	bool InitMenu();
	bool ResetMenu();
	bool ExitMenu();

public: // Managements
	bool OpenMenu();

private: // Management helpers
	bool LoadAppOption();
	bool LoadPauseOption();
	bool CloseMenu() const;

public: // Checkers
	bool IsOnMenu() const;
	bool IsOnGame() const;

public: // Validators
	static int FixOption(int& value, int limit);

private: // Updater helpers
	bool UpdateAppMenu();
	bool UpdateSetting();
	bool UpdateAboutUs();
	bool UpdateAppExit();

public: // Updaters
	bool UpdatePausing();
	bool UpdateGameOver();
	bool Update(float fElapsedTime);

private: // Renderer helpers
	bool RenderAppMenu();
	bool RenderSetting() const;
	bool RenderAboutUs() const;
	bool RenderAppExit() const;

public: // Renderers
	bool RenderPausing() const;
	bool RenderGameOver() const;
	bool Render();
};

#endif // C_MENU_H
