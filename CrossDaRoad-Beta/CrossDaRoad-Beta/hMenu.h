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
#include <vector>
#include "cAssetManager.h"

//=================================================================================================
// Include new header files here

//=================================================================================================

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
		CONTINUE = 1,
		SETTINGS = 2, ///< Settings window
		ABOUT_US = 3, ///< About us window
		APP_EXIT = 4, ///< Exit application window
		APP_MENU = 5, ///< Menu window
		APP_GAME = 6, ///< Continue game window
	};
	enum PauseOption
	{
		RESUMING = 0, ///< Resume game 
		APP_SAVE = 1, ///< Save game
		APP_BACK = 2, ///< Back to menu
	};
	enum SaveBox
	{
		LOCATION = 0,
		OK = 1,
		CANCLE = 2,
		SAVING = 3,
	};
private: /// Target
    cApp* app;

private: /// Checker
    bool bWantToExit;

private: /// Music
    bool bMusicPlaying = false; ///< Flag for music playing state (true = playing, false = not playing)

private: /// Menu HUD
    AppOption eMenuOption;                             ///< Current option
    std::vector<const char*> sAppOptionLabels;  ///< AppOption labels for menu window
    int nAppOptionLimit;                         ///< Maximum number of options
    int nAppOptionValue;                          ///< Current option index
private: 
	int ContinueMenuOption = 0;
	bool start = false;	
	int nameBoxOption = 0;
private:
	SaveBox SaveBoxOption = LOCATION;
	bool isSave = false;
	std::string SaveLocation = "D:/C++/OOP/PROJECT/CrossDaRoad-Beta/CrossDaRoad-Beta/CrossDaRoad-Beta/data/save/";
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
    bool CloseMenu() const;
    bool HandlePause(bool bAppPaused);
    bool HandleResume(bool bAppPaused);

private: // Loaders
	bool LoadAppOption();
	bool LoadPauseOption();
	bool LoadSaveOption();
private: // Validators
    static int FixOption(int& value, int limit);

public: // Checkers
    bool IsOnMenu() const;
    bool IsOnGame() const;

public: // Validators
	bool isSaving();
	std::string GetFileLocation() const;
private: // Updater helpers
    bool UpdateNewGame();
    bool UpdateAppMenu();
    bool UpdateProceed();
    bool UpdateSetting();
    bool UpdateAboutUs();
    bool UpdateAppExit();
    bool UpdateNameBox();

private: // Renderer handlers
    bool RenderAppMenu() const;
    bool RenderProceed() const;
    bool RenderSetting() const;
    bool RenderAboutUs() const;
    bool RenderAppExit() const;
    bool RenderNameBox() const;

public: // Updaters
    bool UpdatePausing();
    bool UpdateSaveBox();
    bool UpdateEndGame();

public: // Renderers
    bool RenderPausing() const;
    bool RenderSaveBox() const;
    bool RenderEndGame() const;

public:
    bool Update(float fElapsedTime);
    bool Render() const;
};

#endif // C_MENU_H
