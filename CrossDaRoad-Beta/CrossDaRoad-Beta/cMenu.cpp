#include "cMenu.h"

#include "cApp.h"

/**
 * @file cMenu.cpp
 *
 * @brief Contains menu class implementation
 *
 * This file implements menu class for menu window management.
**/

////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// CONSTRUCTORS & DESTRUCTOR ////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Default constructor
cMenu::cMenu()
{
	InitMenu();
}

/// @brief Destructor
cMenu::~cMenu()
{
	ExitMenu();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// MENU MANAGEMENT //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////


/// @brief Initialize properties of option for menu management
/// @return Always return true by default
bool cMenu::InitMenu()
{
	using namespace app_const;
	eMenuOption = MenuOption::APP_MENU;
	nMenuOptionLimit = static_cast<int>(std::size(MENU_OPTIONS));
	sMenuOptionLabels = { MENU_OPTIONS, MENU_OPTIONS + nMenuOptionLimit };
	ResetMenu();
	return true;
}

bool cMenu::ResetMenu()
{
	nMenuOptionValue = app_const::INIT_MENU_OPTION;
	nPauseOptionValue = 1;
	bWantToExit = false;

	nPauseOptionLimit = 3;
	return true;
}

/// @brief Free memory of option when exit
/// @return Always return true by default
bool cMenu::ExitMenu()
{
	sMenuOptionLabels.clear();
	return true;
}
/// @brief Load option and draw it on screen
/// @param App Pointer to application
/// @return Always return true by default
bool cMenu::LoadOption(cApp* App)
{
	CloseMenu(App);

	switch (nMenuOptionValue) 
	{
		case 0:
			eMenuOption = MenuOption::NEW_GAME;
			App->GameReset();
			break;
		case 1:
			eMenuOption = MenuOption::CONTINUE;
			App->GameReset();
			App->OnGameLoad();
			break;
		case 2:
			eMenuOption = MenuOption::SETTINGS;
			break;
		case 3:
			eMenuOption = MenuOption::ABOUT_US;
			break;
		case 4:
			eMenuOption = MenuOption::APP_EXIT;
			break;
		default:
			break;
	}

	RenderAppMenu(App);
	return true;
}

bool cMenu::IsOnMenu() const
{
	return eMenuOption == MenuOption::APP_MENU;
}

/// @brief Display menu on screen
/// @param App Pointer to application
/// @return Always return true by default
bool cMenu::RenderAppMenu(cApp* App)
{
	nMenuOptionValue = (nMenuOptionValue % nMenuOptionLimit + nMenuOptionLimit) % nMenuOptionLimit;

	App->Clear(app::BLACK);
	App->DrawSprite(0, 0, cAssetManager::GetInstance().GetSprite("menu_background"));
	for (int id = 0; id < nMenuOptionLimit; id++) {
		const std::string optionName = std::string(sMenuOptionLabels[id]) + (id == nMenuOptionValue ? "_chosen" : "");
		const app::Sprite* optionSprite = cAssetManager::GetInstance().GetSprite(optionName);
		App->SetPixelMode(app::Pixel::MASK);
		App->DrawSprite(146, 65 + id * 10, optionSprite);
		if (id == nMenuOptionValue) {
			App->SetPixelMode(app::Pixel::NORMAL);
		}
	}
	return true;
}
bool cMenu::RenderAboutUs(cApp* App) const
{
	App->Clear(app::BLACK);
	const std::string about_us_dynamic = "about_us_page" + App->Player.ShowFrameID(4);
	const auto object = cAssetManager::GetInstance().GetSprite(about_us_dynamic);
	App->DrawSprite(0, 0, object);
	return true;
}

bool cMenu::RenderAppExit(cApp* App) const
{
	App->Clear(app::BLACK);
	if (bWantToExit) {
		App->DrawSprite(0, 0, cAssetManager::GetInstance().GetSprite("exit_yes"));
	}
	else {
		App->DrawSprite(0, 0, cAssetManager::GetInstance().GetSprite("exit_no"));
	}
	return true;
}
/// @brief Open and display menu on screen
/// @param App Pointer to application
/// @return Always return true by default
bool cMenu::OpenMenu(cApp* App)
{
	ResetMenu();
	RenderAppMenu(App);
	eMenuOption = MenuOption::APP_MENU;
	return true;
}

/// @brief Update menu on screen when user press key
/// @param App Pointer to application
/// @return Always return true by default
bool cMenu::UpdateAppMenu(cApp* App)
{
	if (App->GetKey(app::Key::UP) == Button::RELEASED) {
		if (--nMenuOptionValue < 0) {
			nMenuOptionValue %= nMenuOptionLimit;
			if (nMenuOptionValue < 0) {
				nMenuOptionValue += nMenuOptionLimit;
			}
		}
	}
	if (App->GetKey(app::Key::DOWN) == Button::RELEASED) {
		if (++nMenuOptionValue >= nMenuOptionLimit) {
			nMenuOptionValue %= nMenuOptionLimit;
			if (nMenuOptionValue >= nMenuOptionLimit) {
				nMenuOptionValue -= nMenuOptionLimit;
			}
		}
	}
	if (App->GetKey(app::Key::ENTER) == Button::RELEASED) {
		LoadOption(App);
	}
	return true;
}

/// @brief Close menu on screen
/// @param App Pointer to application
/// @return Always return true by default
bool cMenu::CloseMenu(cApp* App)
{
	App->Clear(app::BLACK);
	return true;
}
/// @brief Display settings on screen (sound on/off)
/// @param App Pointer to application
/// @return Always return true by default
bool cMenu::RenderSettings(cApp* App) const
{
	App->Clear(app::BLACK);
	App->DrawSprite(0, 0, cAssetManager::GetInstance().GetSprite("menu_background"));
	if (bMusicPlaying) {
		App->DrawSprite(146, 65, cAssetManager::GetInstance().GetSprite("sound_on"));
	}
	else {
		App->DrawSprite(146, 65, cAssetManager::GetInstance().GetSprite("sound_off"));
	}
	return true;
}

/// @brief Check if music is playing or not, then turn on/off music (until now)
/// @param App Pointer to application
/// @return Always return true by default
bool cMenu::UpdateSettings(cApp* App)
{
	if (App->IsKeyReleased(app::Key::ENTER)) {
		if (bMusicPlaying) {
			app_sound::StopMusic();
			bMusicPlaying = false;
		}
		else {
			app_sound::PlayMusic("ncs0");
			bMusicPlaying = true;
		}
	}
	if (App->IsKeyReleased(app::Key::ESCAPE)) {
		OpenMenu(App);
		return true;
	}
	return true;
}

bool cMenu::UpdateAboutUs(cApp* App)
{
	if (App->IsKeyReleased(app::Key::ESCAPE)) {
		OpenMenu(App);
		return true;
	}
	return true;
}

bool cMenu::UpdateAppExit(cApp* App)
{
	if (App->IsKeyReleased(app::Key::RIGHT)) {
		bWantToExit = false;
	}
	if (App->IsKeyReleased(app::Key::LEFT)) {
		bWantToExit = true;
	}
	if (App->IsKeyReleased(app::Key::ENTER)) {
		if (bWantToExit) {
			App->OnDestroyEvent();
			return false;
		}
		else {
			OpenMenu(App);
			eMenuOption = MenuOption::APP_MENU;
			return true;
		}
	}
	if (App->IsKeyReleased(app::Key::ESCAPE)) {
		OpenMenu(App);
		bWantToExit = true;
		return true;
	}
	return true;
}

bool cMenu::UpdatePausing(cApp *App)
{
	if (App->IsEnginePause() && App->IsKeyReleased(app::Key::ESCAPE)) {
		App->ResumeEngine();
		return true;
	}
	bool bToPause = (eMenuOption != MenuOption::APP_MENU && App->IsKeyReleased(app::Key::ESCAPE));
	if (App->IsEnginePause() || bToPause) {
		App->PauseEngine();
		// Load option pause menu
		if (App->IsKeyReleased(app::Key::UP)) {
			if (--nPauseOptionValue < 0) {
				nPauseOptionValue %= nPauseOptionLimit;
				if (nPauseOptionValue < 0) {
					nPauseOptionValue += nPauseOptionLimit;
				}
			}
		}
		else if (App->IsKeyReleased(app::Key::DOWN)) {
			if (++nPauseOptionValue >= nPauseOptionLimit) {
				nPauseOptionValue %= nPauseOptionLimit;
				if (nPauseOptionValue >= nPauseOptionLimit) {
					nPauseOptionValue -= nPauseOptionLimit;
				}
			}
		}
		else if (App->IsKeyReleased(app::Key::ENTER)) {
			switch (nPauseOptionValue) {
			case 0:
			{
				OpenMenu(App);
				eMenuOption = MenuOption::APP_MENU;
				App->ResumeEngine();
				break;
			}
			case 1: App->ResumeEngine(); break;
			case 2: App->OnGameSave(); break;
			}
		}
	}
	if (App->IsEnginePause()) { // continue the pause event
		return false;
	}
	return true; // succesfully handle the pause event
}

bool cMenu::RenderPausing(cApp* App)
{
	App->OnGameRender();
	App->SetPixelMode(app::Pixel::ALPHA);
	App->SetBlendFactor(170.0f / 255.0f);
	App->DrawSprite(0, 0, cAssetManager::GetInstance().GetSprite("black_alpha"));
	App->SetBlendFactor(255.0f / 255.0f);
	App->SetPixelMode(app::Pixel::NORMAL);
	const std::string sPauseOptionName = "pause_" + sPauseOptionLabels[nPauseOptionValue];
	App->SetPixelMode(app::Pixel::MASK);
	App->DrawSprite(120, 55, cAssetManager::GetInstance().GetSprite(sPauseOptionName));
	App->SetPixelMode(app::Pixel::NORMAL);
	return true;
}

bool cMenu::Update(cApp* App, const float fElapsedTime)
{
	switch (eMenuOption)
	{
	case MenuOption::NEW_GAME:
		return App->OnGameUpdate(fElapsedTime);
	case MenuOption::CONTINUE:
		return App->OnGameUpdate(fElapsedTime);
	case MenuOption::SETTINGS:
		return UpdateSettings(App);
	case MenuOption::ABOUT_US:
		return UpdateAboutUs(App);
	case MenuOption::APP_EXIT:
		return UpdateAppExit(App);
	case MenuOption::APP_MENU:
		return UpdateAppMenu(App);
	default:
		std::cerr << "cMenu::Update(*App, fElapsedTime=" << fElapsedTime << "):";
		std::cerr << "Menu went wrong" << std::endl;
		return false;
	}
	return false;
}

bool cMenu::Render(cApp* App)
{
	switch (eMenuOption)
	{
	case MenuOption::NEW_GAME:
		return App->OnGameRender();
	case MenuOption::CONTINUE:
		return App->OnGameRender();
	case MenuOption::SETTINGS:
		return RenderSettings(App);
	case MenuOption::ABOUT_US:
		return RenderAboutUs(App);
	case MenuOption::APP_EXIT:
		return RenderAppExit(App);
	case MenuOption::APP_MENU:
		return RenderAppMenu(App);
	default:
		std::cerr << "cMenu::Render(*App):";
		std::cerr << "Menu went wrong" << std::endl;
		return false;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// END OF FILE ///////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////