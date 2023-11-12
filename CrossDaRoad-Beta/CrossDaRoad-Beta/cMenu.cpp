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
	eMenuOption = AppOption::APP_MENU;
	nAppOptionLimit = static_cast<int>(std::size(MENU_OPTIONS));
	sAppOptionLabels = { MENU_OPTIONS, MENU_OPTIONS + nAppOptionLimit };
	ResetMenu();
	return true;
}

bool cMenu::ResetMenu()
{
	nAppOptionValue = app_const::INIT_MENU_OPTION;
	nPauseOptionValue = 1;
	bWantToExit = false;

	nPauseOptionLimit = 3;
	return true;
}

/// @brief Free memory of option when exit
/// @return Always return true by default
bool cMenu::ExitMenu()
{
	sAppOptionLabels.clear();
	return true;
}
/// @brief Load option and draw it on screen
/// @param App Pointer to application
/// @return Always return true by default
bool cMenu::LoadAppOption(cApp* App)
{
	CloseMenu(App);

	int nOption = FixOption(nAppOptionValue, nAppOptionLimit);
	switch (nOption)
	{
		case NEW_GAME:
			eMenuOption = AppOption::NEW_GAME;
			App->GameReset();
			break;
		case CONTINUE:
			eMenuOption = AppOption::CONTINUE;
			App->GameReset();
			App->OnGameLoad();
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
			break;
	}

	return true;
}

bool cMenu::LoadPauseOption(cApp* App)
{
	switch (nPauseOptionValue) 
	{
	case 0:
	{
		OpenMenu(App);
		eMenuOption = AppOption::APP_MENU;
		App->ResumeEngine();
		break;
	}
	case 1: App->ResumeEngine(); break;
	case 2: App->OnGameSave(); break;
	}
	return true;
}

bool cMenu::IsOnMenu() const
{
	return eMenuOption == AppOption::APP_MENU;
}

int cMenu::FixOption(int& value, int limit)
{
	value %= limit; /// (-limit, +limit)
	if (value < 0) {
		value += limit; /// [0, +limit)
	}
	return value;
}

/// @brief Display menu on screen
/// @param App Pointer to application
/// @return Always return true by default
bool cMenu::RenderAppMenu(cApp* App)
{
	nAppOptionValue = (nAppOptionValue % nAppOptionLimit + nAppOptionLimit) % nAppOptionLimit;

	App->Clear(app::BLACK);
	App->DrawSprite(0, 0, cAssetManager::GetInstance().GetSprite("menu_background"));
	for (int id = 0; id < nAppOptionLimit; id++) {
		const std::string optionName = std::string(sAppOptionLabels[id]) + (id == nAppOptionValue ? "_chosen" : "");
		const app::Sprite* optionSprite = cAssetManager::GetInstance().GetSprite(optionName);
		App->SetPixelMode(app::Pixel::MASK);
		App->DrawSprite(146, 65 + id * 10, optionSprite);
		if (id == nAppOptionValue) {
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
	eMenuOption = AppOption::APP_MENU;
	return true;
}

/// @brief Update menu on screen when user press key
/// @param App Pointer to application
/// @return Always return true by default
bool cMenu::UpdateAppMenu(cApp* App)
{
	if (App->GetKey(app::Key::UP) == Button::RELEASED) {
		FixOption(--nAppOptionValue, nAppOptionLimit);
	}
	if (App->GetKey(app::Key::DOWN) == Button::RELEASED) {
		FixOption(++nAppOptionValue, nAppOptionLimit);
	}
	if (App->GetKey(app::Key::ENTER) == Button::RELEASED) {
		LoadAppOption(App);
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
			eMenuOption = AppOption::APP_MENU;
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
	bool bToPause = (!IsOnMenu() && App->IsKeyReleased(app::Key::ESCAPE));
	if (App->IsEnginePause() || bToPause) {
		App->PauseEngine();
		// Load option pause menu

		if (App->IsKeyReleased(app::Key::UP)) {
			FixOption(--nPauseOptionValue, nPauseOptionLimit);
		}
		else if (App->IsKeyReleased(app::Key::DOWN)) {
			FixOption(++nPauseOptionValue, nPauseOptionLimit);
		}
		else if (App->IsKeyReleased(app::Key::ENTER)) {
			LoadPauseOption(App);
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
	case AppOption::NEW_GAME:
		return App->OnGameUpdate(fElapsedTime);
	case AppOption::CONTINUE:
		return App->OnGameUpdate(fElapsedTime);
	case AppOption::SETTINGS:
		return UpdateSettings(App);
	case AppOption::ABOUT_US:
		return UpdateAboutUs(App);
	case AppOption::APP_EXIT:
		return UpdateAppExit(App);
	case AppOption::APP_MENU:
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
	case AppOption::NEW_GAME:
		return App->OnGameRender();
	case AppOption::CONTINUE:
		return App->OnGameRender();
	case AppOption::SETTINGS:
		return RenderSettings(App);
	case AppOption::ABOUT_US:
		return RenderAboutUs(App);
	case AppOption::APP_EXIT:
		return RenderAppExit(App);
	case AppOption::APP_MENU:
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