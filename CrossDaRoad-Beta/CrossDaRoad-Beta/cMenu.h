#ifndef C_MENU_H
#define C_MENU_H

#include "uSound.h"
#include "uAppConst.h"
#include "cAssetManager.h"
#include <vector>

/**
 * @file cMenu.h
 *
 * @brief Contains menu class
 *
 * This file contains menu class for menu window management.
**/


class cApp; // Forward declaration of cApp class

/// @brief Class for menu window management
class cMenu
{
public:
	/// @brief  Enumeration for menu options 
	enum AppOption
	{
		NEW_GAME = 0, ///< New game window
		CONTINUE = 1, ///< Continue game window
		SETTINGS = 2, ///< Settings window
		ABOUT_US = 3, ///< About us window
		APP_EXIT = 4, ///< Exit application window
		APP_MENU = 5, ///< Menu window
	};
	enum PauseOption
	{
		RESUMING = 0,
		APP_SAVE = 1,
		APP_BACK = 2,
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
	PauseOption ePauseOption;
	std::string sPauseOptionLabels[3] = { "resume", "save", "exit" };
	int nPauseOptionValue;
	int nPauseOptionLimit;

public: // Constructor & Destructor
	cMenu();
	cMenu(cApp* app);
	~cMenu();

public: // Initialization & Clean-up
	bool SetTarget(cApp* app);
	bool InitMenu();
	bool ResetMenu();
	bool ExitMenu();

public: // Managements
	bool CloseMenu();
	bool LoadAppOption();
	bool LoadPauseOption();
	bool OpenMenu();

public: // Checkers
	bool IsOnMenu() const;

public: // Validators
	int FixOption(int& value, int limit);

public: // Updaters
	bool UpdateAppMenu();
	bool UpdateSetting();
	bool UpdateAboutUs();
	bool UpdateAppExit();
	bool UpdatePausing();
	bool Update(const float fElapsedTime);

public: // Renderers
	bool RenderAppMenu();
	bool RenderSetting() const;
	bool RenderAboutUs() const;
	bool RenderAppExit() const;
	bool RenderPausing();
	bool Render();
};

#endif // C_MENU_H
