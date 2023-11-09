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
	enum Option
	{
		APP_MENU, ///< Menu window
		NEW_GAME, ///< New game window
		CONTINUE, ///< Continue game window
		SETTINGS, ///< Settings window
		ABOUT_US, ///< About us window
		EXIT_APP, ///< Exit application window
		GAMEPLAY  ///< Gameplay window
	};

public:
	Option eAppOption; ///< Current option
	int nOption; 	 ///< Current option index
	bool isMusicPlaying = false; ///< Flag for music playing state (true = playing, false = not playing)

	std::vector<const char*> sOptionLabels;  ///< Option labels for menu window
	int nOptionLimit;                        ///< Maximum number of options

public: // Constructor & Destructor
	cMenu();
	~cMenu();

public: // Menu management
	bool InitMenu();
	bool ExitMenu();

	bool LoadOption(cApp* App);

	bool DisplayMenu(cApp* App);
	bool OpenMenu(cApp* App);
	bool UpdateMenu(cApp* App);
	bool CloseMenu(cApp* App);

	bool DisplaySettings(cApp* App) const;
	bool UpdateSettings(cApp* App);
};

#endif // C_MENU_H
