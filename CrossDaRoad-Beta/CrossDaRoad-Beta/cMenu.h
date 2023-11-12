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
	std::string sPauseOptionLabels[3] = { "exit", "resume", "save" };
	int nPauseOptionValue;
	int nPauseOptionLimit;

public: // Constructor & Destructor
	cMenu();
	~cMenu();

public: // Initialization & Clean-up
	bool InitMenu();
	bool ResetMenu();
	bool ExitMenu();

public: // Managements
	bool CloseMenu(cApp* App);
	bool LoadAppOption(cApp* App);
	bool LoadPauseOption(cApp* App);
	bool OpenMenu(cApp* App);

public: // Checkers
	bool IsOnMenu() const;

public: // Validators
	int FixOption(int& value, int limit);

public: // Updaters
	bool UpdateAppMenu(cApp* App);
	bool UpdateSettings(cApp* App);
	bool UpdateAboutUs(cApp* App);
	bool UpdateAppExit(cApp* App);
	bool UpdatePausing(cApp* App);
	bool Update(cApp* App, const float fElapsedTime);

public: // Renderers
	bool RenderAppMenu(cApp* App);
	bool RenderSettings(cApp* App) const;
	bool RenderAboutUs(cApp* App) const;
	bool RenderAppExit(cApp* App) const;
	bool RenderPausing(cApp* App);
	bool Render(cApp* App);
};

#endif // C_MENU_H
