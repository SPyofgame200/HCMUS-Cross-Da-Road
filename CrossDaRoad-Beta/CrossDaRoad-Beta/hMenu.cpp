/**
 * @file hMenu.cpp
 *
 * @brief Contains menu class implementation
 *
 * This file implements menu class for menu window management.
**/

#include "hMenu.h"
#include "cApp.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// CONSTRUCTORS & DESTRUCTOR ////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Default constructor
hMenu::hMenu()
{
	InitMenu();
}

/// @brief  Parameterized constructor with pointer to application
/// @param app Pointer to application
hMenu::hMenu(cApp* app)
{
	SetupTarget(app);
	InitMenu();
}

/// @brief Destructor
hMenu::~hMenu()
{
	ExitMenu();
	std::cerr << "hMenu::~hMenu(): Successfully destructed" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// INITIALIZATION & CLEAN-UP ////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Set pointer to application 
/// @param app Pointer to application
/// @return True if pointer is not null, false otherwise
bool hMenu::SetupTarget(cApp* app)
{
	if (app == nullptr) {
		return false;
	}
	this->app = app;
	return true;
}

/// @brief Initialize properties of option for menu management
/// @return Always return true by default
bool hMenu::InitMenu()
{
	using namespace app_const;
	eMenuOption = AppOption::APP_MENU;
	nAppOptionLimit = static_cast<int>(std::size(APP_OPTIONS));
	sAppOptionLabels = { APP_OPTIONS, APP_OPTIONS + nAppOptionLimit };
	nPauseOptionLimit = static_cast<int>(std::size(PAUSE_OPTIONS));
	//sPauseOptionLabels = { PAUSE_OPTIONS, PAUSE_OPTIONS + nPauseOptionLimit };
	ResetMenu();
	return true;
}

/// @brief Reset option when exit to default
/// @return Always return true by default
bool hMenu::ResetMenu()
{
	nAppOptionValue = app_const::INIT_MENU_OPTION;
	nPauseOptionValue = app_const::INIT_PAUSE_OPTION;
	bWantToExit = false;

	nPauseOptionLimit = 3;
	return true;
}

/// @brief Free memory of option when exit
/// @return Always return true by default
bool hMenu::ExitMenu()
{
	sAppOptionLabels.clear();
	//sPauseOptionLabels.clear();
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// MANAGEMENTS //////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Open menu on screen
/// @return Always return true by default
bool hMenu::OpenMenu()
{
	ResetMenu();
	RenderAppMenu();
	eMenuOption = AppOption::APP_MENU;
	return true;
}

/// @brief Load option and draw it on screen
/// @param app Pointer to application
/// @return Always return true by default
bool hMenu::LoadAppOption()
{
	CloseMenu();

	switch (const int nOption = FixOption(nAppOptionValue, nAppOptionLimit)) {
		case NEW_GAME:
			eMenuOption = AppOption::NEW_GAME;
			break;
		case APP_GAME:
			eMenuOption = AppOption::APP_GAME;
			app->GameReset();
			app->OnGameLoad();
			break;
		case SETTINGS:
			eMenuOption = AppOption::SETTINGS;
			break;
		case ABOUT_US:
			eMenuOption = AppOption::ABOUT_US;
			break;
		case APP_EXIT:
			eMenuOption = AppOption::APP_EXIT;
			break;
		default:
			std::cerr << "hMenu::LoadAppOption(): ";
			std::cerr << "Unknown option = " << nOption << ", expected [0.." << nAppOptionLimit - 1 << "]" << std::endl;
			return false;
	}

	return true;
}

/// @brief Load pause game option and draw it on screen
/// @return True if option is valid, false otherwise
bool hMenu::LoadPauseOption()
{
	switch (const int nOption = FixOption(nPauseOptionValue, nPauseOptionLimit)) {
		case RESUMING:
			app->ResumeEngine();
			break;
		case APP_SAVE:
			app->OnGameSave();
			break;
		case APP_BACK:
			app->ResumeEngine();
			OpenMenu();
			break;
		default:
			std::cerr << "hMenu::LoadPauseOption(): ";
			std::cerr << "Unknown option = " << nOption << ", expected [0.." << nPauseOptionLimit - 1 << "]" << std::endl;
			return false;
	}
	return true;
}

/// @brief Close menu on screen
/// @param app Pointer to application
/// @return Always return true by default
bool hMenu::CloseMenu() const
{
	app->Clear(app::BLACK);
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// CHECKERS ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Check if current option is menu or not
/// @return True if current option is menu, false otherwise
bool hMenu::IsOnMenu() const
{
	return eMenuOption == AppOption::APP_MENU;
}

/// @brief Check if current option is game or not
/// @return True if current option is game, false otherwise
bool hMenu::IsOnGame() const
{
	return eMenuOption == AppOption::APP_GAME;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// VALIDATORS //////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief  Fix option value to be in range [0, limit)
/// @param value Value to be fixed
/// @param limit Maximum value of option
/// @return Fixed value
int hMenu::FixOption(int& value, int limit)
{
	value %= limit; /// (-limit, +limit)
	if (value < 0) {
		value += limit; /// [0, +limit)
	}
	return value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// UPDATERS ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

bool hMenu::UpdateNewGame()
{	
	bool result = app->UpdateDrawNameBox();
	if (app->nameBoxOption % 2 != 0 && app->IsKeyReleased(app::Key::ENTER) && !app->playerName.empty())
	{
		eMenuOption = APP_GAME;
		app->GameReset();
	}
	return result;
}

/// @brief Update menu on screen when user press key
/// @param app Pointer to application
/// @return Always return true by default
bool hMenu::UpdateAppMenu()
{
	if (app->IsKeyReleased(app::Key::UP)) {
		FixOption(--nAppOptionValue, nAppOptionLimit);
	}
	if (app->IsKeyReleased(app::Key::DOWN)) {
		FixOption(++nAppOptionValue, nAppOptionLimit);
	}
	if (app->IsKeyReleased(app::Key::ENTER)) {
		LoadAppOption();
	}
	return true;
}


/// @brief Display settings on screen (sound on/off)
/// @param app Pointer to application
/// @return Always return true by default
bool hMenu::RenderSetting() const
{
	app->Clear(app::BLACK);
	app->DrawSprite(0, 0, cAssetManager::GetInstance().GetSprite("menu_background"));
	if (bMusicPlaying) {
		app->DrawSprite(146, 65, cAssetManager::GetInstance().GetSprite("sound_on"));
	}
	else {
		app->DrawSprite(146, 65, cAssetManager::GetInstance().GetSprite("sound_off"));
	}
	return true;
}

/// @brief Check if music is playing or not, then turn on/off music (until now)
/// @return Always return true by default
bool hMenu::UpdateSetting()
{
	if (app->IsKeyReleased(app::Key::ENTER)) {
		if (bMusicPlaying) {
			app_sound::StopMusic();
			bMusicPlaying = false;
		}
		else {
			app_sound::PlayMusic("ncs0");
			bMusicPlaying = true;
		}
	}
	if (app->IsKeyReleased(app::Key::ESCAPE)) {
		OpenMenu();
		return true;
	}
	return true;
}

/// @brief Display about us on screen
/// @return Always return true by default
bool hMenu::UpdateAboutUs()
{
	if (app->IsKeyReleased(app::Key::ESCAPE)) {
		OpenMenu();
		return true;
	}
	return true;
}

/// @brief Update exit window when user press key 
/// @return False if user want to exit, true otherwise
bool hMenu::UpdateAppExit()
{
	if (app->IsKeyReleased(app::Key::RIGHT)) {
		bWantToExit = false;
	}
	if (app->IsKeyReleased(app::Key::LEFT)) {
		bWantToExit = true;
	}
	if (app->IsKeyReleased(app::Key::ENTER)) {
		if (bWantToExit) {
			app->OnDestroyEvent();
			return false;
		}
		else {
			OpenMenu();
			eMenuOption = AppOption::APP_MENU;
			return true;
		}
	}
	if (app->IsKeyReleased(app::Key::ESCAPE)) {
		OpenMenu();
		bWantToExit = true;
		return true;
	}
	return true;
}

/// @brief Update menu screen
/// @return Always return true by default
bool hMenu::UpdatePausing()
{
	if (app->IsKeyReleased(app::Key::UP)) {
		FixOption(--nPauseOptionValue, nPauseOptionLimit);
	}
	else if (app->IsKeyReleased(app::Key::DOWN)) {
		FixOption(++nPauseOptionValue, nPauseOptionLimit);
	}
	else if (app->IsKeyReleased(app::Key::ENTER)) {
		LoadPauseOption();
	}
	return true; // succesfully handle the pause event
}

/// @brief Update all app screen (menu, pause, about us, exit)
/// @param fElapsedTime Time elapsed since last frame
/// @return True if update successfully, false otherwise
bool hMenu::Update(const float fElapsedTime)
{
	switch (eMenuOption) {
		case AppOption::NEW_GAME:
			return UpdateNewGame();
		case AppOption::APP_GAME:
			return UpdateProcced();
		case AppOption::SETTINGS:
			return UpdateSetting();
		case AppOption::ABOUT_US:
			return UpdateAboutUs();
		case AppOption::APP_EXIT:
			return UpdateAppExit();
		case AppOption::APP_MENU:
			return UpdateAppMenu();
		default:
			std::cerr << "hMenu::Update(fElapsedTime=" << fElapsedTime << "):";
			std::cerr << "Menu went wrong" << std::endl;
			return false;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// RENDERERS ///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Display menu on screen
/// @param app Pointer to application
/// @return Always return true by default
bool hMenu::RenderAppMenu()
{
	nAppOptionValue = (nAppOptionValue % nAppOptionLimit + nAppOptionLimit) % nAppOptionLimit;

	app->Clear(app::BLACK);
	app->DrawSprite(0, 0, cAssetManager::GetInstance().GetSprite("menu_background"));
	for (int id = 0; id < nAppOptionLimit; id++) {
		const std::string optionName = std::string(sAppOptionLabels[id]) + (id == nAppOptionValue ? "_chosen" : "");
		const app::Sprite* optionSprite = cAssetManager::GetInstance().GetSprite(optionName);
		app->SetPixelMode(app::Pixel::MASK);
		app->DrawSprite(146, 65 + id * 10, optionSprite);
		if (id == nAppOptionValue) {
			app->SetPixelMode(app::Pixel::NORMAL);
		}
	}
	return true;
}

bool hMenu::RenderProcced() const
{
	return false;
}

/// @brief Render about us on screen
/// @return Always return true by default
bool hMenu::RenderAboutUs() const
{
	app->Clear(app::BLACK);
	const std::string about_us_dynamic = "about_us_page" + app->ShowFrameID(4);
	const auto object = cAssetManager::GetInstance().GetSprite(about_us_dynamic);
	app->DrawSprite(0, 0, object);
	return true;
}

/// @brief Render exit window on screen
/// @return Always return true by default
bool hMenu::RenderAppExit() const
{
	app->Clear(app::BLACK);
	if (bWantToExit) {
		app->DrawSprite(0, 0, cAssetManager::GetInstance().GetSprite("exit_yes"));
	}
	else {
		app->DrawSprite(0, 0, cAssetManager::GetInstance().GetSprite("exit_no"));
	}
	return true;
}

/// @brief Pause game and display pause window on screen
/// @return Always return true by default
bool hMenu::RenderPausing() const
{
	/// Overlay
	app->SetPixelMode(app::Pixel::ALPHA);
	app->SetBlendFactor(170.0f / 255.0f);
	app->DrawSprite(0, 0, cAssetManager::GetInstance().GetSprite("black_alpha"));
	app->SetBlendFactor(255.0f / 255.0f);
	app->SetPixelMode(app::Pixel::NORMAL);
	/// Pause Selection
	const std::string sSelectedLabel = sPauseOptionLabels[nPauseOptionValue];
	const std::string sOptionName = "pause_" + sSelectedLabel;
	app->SetPixelMode(app::Pixel::MASK);
	app->DrawSprite(120, 55, cAssetManager::GetInstance().GetSprite(sOptionName));
	app->SetPixelMode(app::Pixel::NORMAL);
	return true;
}

/// @brief Render all app screen (menu, pause, about us, exit)
/// @return True if render successfully, false otherwise
bool hMenu::Render()
{
	switch (eMenuOption) {
		case AppOption::NEW_GAME:
			return app->DrawNameBox();
		case AppOption::APP_GAME:
			return app->OnGameRender();
		case AppOption::SETTINGS:
			return RenderSetting();
		case AppOption::ABOUT_US:
			return RenderAboutUs();
		case AppOption::APP_EXIT:
			return RenderAppExit();
		case AppOption::APP_MENU:
			return RenderAppMenu();
		default:
			std::cerr << "hMenu::Render(*app):";
			std::cerr << "Menu went wrong" << std::endl;
			return false;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// END OF FILE ///////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////