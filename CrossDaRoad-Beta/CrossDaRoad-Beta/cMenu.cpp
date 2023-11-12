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
	nOption = INIT_MENU_OPTION;
	bWantToExit = false;
	nPauseOption = 1;
	nOptionLimit = static_cast<int>(std::size(MENU_OPTIONS));
	sOptionLabels = { MENU_OPTIONS, MENU_OPTIONS + nOptionLimit };
	return true;
}
/// @brief Free memory of option when exit
/// @return Always return true by default
bool cMenu::ExitMenu()
{
	sOptionLabels.clear();
	return true;
}
/// @brief Load option and draw it on screen
/// @param App Pointer to application
/// @return Always return true by default
bool cMenu::LoadOption(cApp* App)
{
	nOption = (nOption % nOptionLimit + nOptionLimit) % nOptionLimit;
	CloseMenu(App);

	switch (nOption) 
	{
		case 0:
			eAppOption = cMenu::Option::NEW_GAME;
			App->GameReset();
			break;
		case 1:
			eAppOption = cMenu::Option::CONTINUE;
			App->GameReset();
			App->OnGameLoad();
			break;
		case 2:
			eAppOption = cMenu::Option::SETTINGS;
			break;
		case 3:
			eAppOption = cMenu::Option::ABOUT_US;
			break;
		case 4:
			eAppOption = cMenu::Option::APP_EXIT;
			break;
		default:
			break;
	}

	RenderAppMenu(App);
	return true;
}

/// @brief Display menu on screen
/// @param App Pointer to application
/// @return Always return true by default
bool cMenu::RenderAppMenu(cApp* App)
{
	nOption = (nOption % nOptionLimit + nOptionLimit) % nOptionLimit;

	App->Clear(app::BLACK);
	App->DrawSprite(0, 0, cAssetManager::GetInstance().GetSprite("menu_background"));
	for (int id = 0; id < nOptionLimit; id++) {
		const std::string optionName = std::string(sOptionLabels[id]) + (id == nOption ? "_chosen" : "");
		const app::Sprite* optionSprite = cAssetManager::GetInstance().GetSprite(optionName);
		App->SetPixelMode(app::Pixel::MASK);
		App->DrawSprite(146, 65 + id * 10, optionSprite);
		if (id == nOption) {
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
	RenderAppMenu(App);
	eAppOption = cMenu::Option::APP_MENU;
	return true;
}

/// @brief Update menu on screen when user press key
/// @param App Pointer to application
/// @return Always return true by default
bool cMenu::UpdateAppMenu(cApp* App)
{
	if (App->GetKey(app::Key::UP) == Button::RELEASED) {
		--nOption;
	}
	if (App->GetKey(app::Key::DOWN) == Button::RELEASED) {
		++nOption;
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
	if (isMusicPlaying) {
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
		if (isMusicPlaying) {
			app_sound::StopMusic();
			isMusicPlaying = false;
		}
		else {
			app_sound::PlayMusic("ncs0");
			isMusicPlaying = true;
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
			eAppOption = cMenu::Option::APP_MENU;
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
	bool bToPause = (eAppOption != cMenu::Option::APP_MENU && App->IsKeyReleased(app::Key::ESCAPE));
	if (App->IsEnginePause() || bToPause) {
		App->PauseEngine();
		// Load option pause menu
		if (App->IsKeyReleased(app::Key::UP)) {
			nPauseOption--;
		}
		else if (App->IsKeyReleased(app::Key::DOWN)) {
			nPauseOption++;
		}
		else if (App->IsKeyReleased(app::Key::ENTER)) {
			nPauseOption = (nPauseOption % 3 + 3) % 3;
			switch (nPauseOption) {
			case 0:
			{
				OpenMenu(App);
				eAppOption = cMenu::Option::APP_MENU;
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
	const std::string sPauseOptionName = "pause_" + choices[(nPauseOption % 3 + 3) % 3];
	App->SetPixelMode(app::Pixel::MASK);
	App->DrawSprite(120, 55, cAssetManager::GetInstance().GetSprite(sPauseOptionName));
	App->SetPixelMode(app::Pixel::NORMAL);
	return true;
}

bool cMenu::Update(cApp* App, const float fElapsedTime)
{
	switch (eAppOption)
	{
	case cMenu::Option::NEW_GAME:
		return App->OnGameUpdate(fElapsedTime);
	case cMenu::Option::CONTINUE:
		return App->OnGameUpdate(fElapsedTime);
	case cMenu::Option::SETTINGS:
		return UpdateSettings(App);
	case cMenu::Option::ABOUT_US:
		return UpdateAboutUs(App);
	case cMenu::Option::APP_EXIT:
		return UpdateAppExit(App);
	case cMenu::Option::APP_MENU:
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
	switch (eAppOption)
	{
	case cMenu::Option::NEW_GAME:
		return App->OnGameRender();
	case cMenu::Option::CONTINUE:
		return App->OnGameRender();
	case cMenu::Option::SETTINGS:
		return RenderSettings(App);
	case cMenu::Option::ABOUT_US:
		return RenderAboutUs(App);
	case cMenu::Option::APP_EXIT:
		return RenderAppExit(App);
	case cMenu::Option::APP_MENU:
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