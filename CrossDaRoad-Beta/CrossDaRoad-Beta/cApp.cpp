/**
 * @file cApp.cpp
 * @brief Contains application class implementations
 *
 * This file implements application class for application management (init, exit, update, render).
**/

#include "cApp.h"
#include "uSound.h"
#include "uStringUtils.h"
#include <Windows.h>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <thread>
#include "cFrameManager.h"

constexpr float fConst = 2.0f;

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// CONSTRUCTOR & DESTRUCTOR ////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Default constructor init menu and game
cApp::cApp()
{
	SetDefaultTargetSize(app_const::SPRITE_WIDTH, app_const::SPRITE_HEIGHT);
	Zone.SetCellSize(app_const::CELL_SIZE, app_const::CELL_SIZE);
	Player.SetupTarget(this);
	MapDrawer.SetupTarget(this);
	Menu.InitMenu();
	GameInit();
}
/// @brief Default destructor exit menu and game
cApp::~cApp()
{
	Menu.ExitMenu();
	GameExit();
	std::cerr << "cApp::~cApp(): Successfully destructed" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// CONSTRUCTOR & DESTRUCTOR PROCEDURE /////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Initialize game, load map
/// @return True if success, false otherwise
bool cApp::GameInit()
{
	using namespace app_const;
	fTimeSinceStart = 0;
	sAppName = APP_NAME;
	nScore = 0;
	nLife = 3;
	MapLoader.Init();
	return true;
}
/// @brief Exit game, clear data
/// @return Always returns true by default
bool cApp::GameExit()
{
	MapLoader.Destruct();
	return true;
}
/// @brief Go to next map level
/// @return Always returns true by default
bool cApp::GameNext()
{
	MapLoader.NextLevel();
	GameReset();
	return true;
}
/// @brief Go to previous map level
/// @return Always returns true by default
bool cApp::GamePrev()
{
	MapLoader.PrevLevel();
	GameReset();
	return true;
}
/// @brief Reset game, clear data, load map, reset Player position, danger area, score
/// @return Always returns true by default
bool cApp::GameReset()
{
	fTimeSinceStart = 0.0f;

	sAppName = "Cross Da Road " + MapLoader.ShowMapInfo();
	Zone.CreateZone(ScreenWidth(), ScreenHeight());
	Player.Reset();
	cFrameManager::GetInstance().Reset();

	Clear(app::BLACK);
	MapLoader.LoadMapLevel();
	Zone.SetPattern(
		MapLoader.GetPlatformPattern().c_str(), 
		MapLoader.GetDangerPattern().c_str(),
		MapLoader.GetBlockPattern().c_str()
	);
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// COLLISION DETECTION ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Check if Player is killed by any object
/// @param bDebug Whether to print debug information or not
/// @return True if Player is killed, false otherwise
bool cApp::IsKilled() const
{
	if (Player.IsPlayerCollisionSafe()) {
		return false;
	}
	return Player.IsHit();
}
/// @brief Get death message of Player
/// @return String of death message
std::string cApp::GetPlayerDeathMessage() const
{
	return "";
}
/// @brief Check if Player is on platform
/// @return True if Player is on platform, false otherwise
bool cApp::IsOnPlatform() const
{
	return Player.IsPlatform();
}
/// @brief Get platform velocity
/// @param fElapsedTime Time elapsed since last update
/// @return Velocity of platform
float cApp::GetPlatformVelocity(const float fElapsedTime) const
{
	const float fPosY = Player.GetPlayerLogicPositionY();
	const float fVelocityX = MapLoader.GetLaneRound(fPosY).GetVelocity();
	const float fMovedX = fVelocityX * fElapsedTime;
	return fMovedX;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// GAME UPDATES //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Update all game objects
/// @param fElapsedTime Time elapsed since last update
/// @return Always returns true by default
bool cApp::OnGameUpdate(const float fElapsedTime)
{
	Player.OnPlayerMove();
	if (IsOnPlatform()) { // Frog is moved by platforms
		Player.PlayerPlatformMove(-GetPlatformVelocity(fElapsedTime), 0);
		Player.PlayerPlatformDetector();
	}
	if (Player.IsPlayerWin()) {
		return GameNext();
	}
	if (Player.IsPlayerOutOfBounds() || IsKilled()) {
		return OnPlayerDeath();
	}
	return true;
}
/// @brief Update Player when Player is killed
/// @return Always returns true by default
bool cApp::OnPlayerDeath()
{
	std::cout << GetPlayerDeathMessage() << std::endl;
	bDeath = true;
	Player.OnRenderPlayerDeath();
	Player.Reset();
	if (--nLife <= 0) {
		PauseEngine();
		
		//GameInit();
	}
	bDeath = false;
	return true;
}
/// @brief Draw all lanes, render Player, draw status bar
/// @return Always returns true by default
bool cApp::OnGameRender()
{
	DrawAllLanes();
	Player.OnRenderPlayer();
	DrawStatusBar();
	return true;
}
/// @brief Set frame delay, load all sprites, open menu
/// @return Always returns true by default
bool cApp::OnCreateEvent()
{
	Menu.SetupTarget(this);
	SetFrameDelay(FrameDelay::STABLE_FPS_DELAY);
	cAssetManager::GetInstance().LoadAllSprites();
	Menu.OpenMenu();
	return true;
}
/// @brief
///	@param fTickTime - Time elapsed since last update
///	@param eTickMessage - Tick message that contains information about tick
bool cApp::OnFixedUpdateEvent(float fTickTime, const engine::Tick& eTickMessage)
{
	if (!IsEnginePause() && !bDeath) {
		fTimeSinceStart = fTickTime;
		cFrameManager::GetInstance().UpdateFrame(fTimeSinceStart, GetFrameDelay());
	}
	return true;
}
/// @brief Update event that called when application is updated
///	@param fElapsedTime - Time elapsed since last update
bool cApp::OnUpdateEvent(const float fElapsedTime)
{
	if (!Menu.Update(fElapsedTime)) {
		return false;
	}
	return true;
}
/// @brief Update event that called when application is updated
///	@param fElapsedTime Time elapsed since last update
///	@param fLateElapsedTime Time elapsed since last late update
/// @return Always returns true by default
bool cApp::OnLateUpdateEvent(float fElapsedTime, float fLateElapsedTime)
{
	return true;
}
/// @brief 
/// @return 
bool cApp::OnCreateNewName()
{

	return true;
}
/// @brief 
/// @return 
bool cApp::OnDisplaySaveBox()
{

	return false;
}
/// @brief 
/// @return 
bool cApp::UpdateDrawNameBox()
{
	if (IsKeyReleased(app::Key::DOWN)) {
		nameBoxOption++;
	}
	if (IsKeyReleased(app::Key::UP)) {
		nameBoxOption--;
	}
	if (IsKeyReleased(app::Key::BACK))
	{	
		if(playerName.size() > 0)
			playerName.pop_back();
		return true;
	}
	if (nameBoxOption % 2 == 0)
	{
		if (playerName.size() < 9)
		{

			std::map<uint16_t, app::Key> mapKeyAlphabet = app::CreateMapKeyAlphabet();
			char currentKeyA = 'A';
			for (const auto &it : mapKeyAlphabet)
			{	
				if (IsKeyReleased(it.second))
				{
					playerName += currentKeyA;
					return true;
				}
				++currentKeyA;
			}
			std::map<uint16_t, app::Key> mapKeyNumeric = app::CreateMapKeyNumeric();
			char currentKeyN = '0';
			for(const auto &it : mapKeyNumeric)
			{
				if (IsKeyReleased(it.second))
				{
					playerName += currentKeyN;
					return true;
				}
				++currentKeyN;
			}
		}
	}
	
	return true; 
}
/// @brief 
/// @return 
bool cApp::DrawNameBox()
{
	const app::Sprite* NameBox = cAssetManager::GetInstance().GetSprite("createNameBox");
	const app::Sprite* NameBoxChosen = cAssetManager::GetInstance().GetSprite("start_chosen");

	Clear(app::BLACK);
	if (nameBoxOption % 2 == 0)
		DrawSprite(0, 0, NameBox);
	else
		DrawSprite(0, 0, NameBoxChosen);

	SetPixelMode(app::Pixel::MASK);
	if (playerName.empty()) {
		DrawBigText("Input name", 157, 70);
	}
	else {
		DrawBigText1(playerName, 157, 70);
	}
	SetPixelMode(app::Pixel::NORMAL);
	return true;
}
/// @brief Check if game is rendering or not
/// @return True if game is rendering, false otherwise
bool cApp::OnRenderEvent()
{
	if (!Menu.Render()) {
		return false;
	}
	return true;
}
/// @brief Save current game state to file
/// @return True if game is saved successfully, false otherwise
bool cApp::OnGameSave() const
{
	std::string FileName = Player.GetPlayerName();
	const std::string sSaveFilePath = GetFilePathLocation(true, FileName);
	if (!sSaveFilePath.empty()) {
		std::ofstream fout(sSaveFilePath);
		if (fout.is_open()) {
			fout << MapLoader.GetMapLevel() << std::endl;
			fout << Player.GetPlayerVelocityX() << std::endl;
			fout << Player.GetPlayerVelocityY() << std::endl;
			fout << Player.GetPlayerAnimationPositionX() << std::endl;
			fout << Player.GetPlayerAnimationPositionY() << std::endl;
			fout << Player.GetPlayerLogicPositionX() << std::endl;
			fout << Player.GetPlayerLogicPositionY();
			fout.close();
			return true;
		}
		else {
			std::cerr << "Can't open the selected file for writing." << std::endl;
			return false;
		}
	}
	else {
		std::cerr << "User canceled the save operation." << std::endl;
		return false;
	}
}
/// @brief Load game state from file
/// @return True if game is loaded successfully, false otherwise
bool cApp::OnGameLoad()
{
	const std::string sLoadFilePath = GetFilePathLocation(false, "");

	if (!sLoadFilePath.empty()) {
		std::ifstream fin(sLoadFilePath);
		if (fin.is_open()) {
			float VelocityX;
			float VelocityY;
			float AnimationPositionX;
			float AnimationPositionY;
			float LogicPositionX;
			float LogicPositionY;
			int MapLevel;

			if (fin >> MapLevel >> VelocityX >> VelocityY >> AnimationPositionX >> AnimationPositionY >> LogicPositionX >> LogicPositionY) {
				MapLoader.SetMapLevel(MapLevel);
				Player.SetPlayerAnimationPosition(AnimationPositionX, AnimationPositionY);
				Player.SetPlayerLogicPosition(LogicPositionX, LogicPositionY);
				Player.SetPlayerVelocity(VelocityX, VelocityY);
				fin.close();
				return true;
			}
			else {
				std::cerr << "Failed to read data from the file." << std::endl;
			}
		}
		else {
			std::cerr << "Failed to open the selected file for reading." << std::endl;
		}
	}
	else {
		std::cerr << "User canceled the load operation." << std::endl;
	}

	return false;
}
/// @brief Event that called when application is paused
bool cApp::OnPauseEvent()
{
	if (IsEnginePause() && IsKeyReleased(app::Key::ESCAPE)) {
		Menu.ResetMenu();
		ResumeEngine();
	}
	else if (Menu.IsOnGame() && IsKeyReleased(app::Key::ESCAPE)) {
		PauseEngine();
	}
	if (IsEnginePause()) { // continue the pause event
		if (nLife == 0) {
			Menu.UpdateGameOver();
			OnGameRender();
			Menu.RenderGameOver();
		}
		else {
			Menu.UpdatePausing();
			OnGameRender();
			Menu.RenderPausing();
		}
		return false;
	}
	return true; // succesfully handle the pause event
}
/// @brief Event that called when application is force paused
/// @return True if pause event was handled successfully, false otherwise
bool cApp::OnForcePauseEvent()
{
	if (!Menu.IsOnGame()) {
		return false;
	}
	PauseEngine();
	return true;
}
/// @brief Event that called when application is destroyed normally
/// @return Always returns true by default
bool cApp::OnDestroyEvent()
{
	GameExit();
	return true;
}
/// @brief Event that called when application is destroyed forcefully
/// @return Always returns true by default
bool cApp::OnForceDestroyEvent()
{
	GameExit();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// FILE MANAGEMENT ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Get file path location from user 
/// @param isSave True if user want to save file, false otherwise
/// @return File path location
std::string cApp::GetFilePathLocation(bool isSave, std::string fileName)
{
	OPENFILENAME ofn;
	wchar_t szFileNameW[MAX_PATH] = L"";
	char szFileName[MAX_PATH] = "";

	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFilter = L"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = szFileNameW;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrInitialDir = L"./data/save";
	ofn.lpstrDefExt = L"txt";


	size_t count;

	if (isSave) {
		ofn.Flags = OFN_EXPLORER | OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;
		GetSaveFileName(&ofn);
		wcstombs_s(&count, szFileName, szFileNameW, MAX_PATH);
		std::cout << "Selected File: " << szFileName << std::endl;
		return szFileName;
	}
	else {
		ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;
		GetOpenFileName(&ofn);
		wcstombs_s(&count, szFileName, szFileNameW, MAX_PATH);
		std::cout << "Selected File: " << szFileName << std::endl;
		return szFileName;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// GAME RENDERING /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Draw all lanes on screen
/// @return Always returns true by default
bool cApp::DrawAllLanes() const
{
	return MapDrawer.DrawAllLanes();
}

/// @brief Draw text to screen at (x, y) position
/// @param sText Text (std::string) (in bytes)
/// @param x X (int) (in bytes)
/// @param y Y (int) (in bytes)
/// @return true if text was drawn successfully, false otherwise
bool cApp::DrawBigText(const std::string& sText, const int x, const int y)
{
	int i = 0;
	for (const auto c : sText) {
		constexpr int nFirstASCII = 32;
		constexpr int nCharsInRow = 16;
		const int nDrawX = ((c - nFirstASCII) % nCharsInRow) * app_const::FONT_WIDTH;
		const int nDrawY = ((c - nFirstASCII) / nCharsInRow) * app_const::FONT_HEIGHT;

		SetPixelMode(app::Pixel::MASK);
		DrawPartialSprite(x + i * app_const::FONT_WIDTH, y, cAssetManager::GetInstance().GetSprite("font"), nDrawX, nDrawY, app_const::FONT_WIDTH, app_const::FONT_HEIGHT);
		i++;
		SetPixelMode(app::Pixel::NORMAL);
	}
	return true;
}
bool cApp::DrawBigText1(const std::string& sText, const int x, const int y)
{
	int i = 0;
	for (const auto c : sText) {
		constexpr int nFirstASCII = 32;
		constexpr int nCharsInRow = 16;
		const int nDrawX = ((c - nFirstASCII) % nCharsInRow) * app_const::FONT_WIDTH;
		const int nDrawY = ((c - nFirstASCII) / nCharsInRow) * app_const::FONT_HEIGHT;

		SetPixelMode(app::Pixel::MASK);
		DrawPartialSprite(x + i * app_const::FONT_WIDTH, y, cAssetManager::GetInstance().GetSprite("font1"), nDrawX, nDrawY, app_const::FONT_WIDTH, app_const::FONT_HEIGHT);
		SetPixelMode(app::Pixel::NORMAL);
		i++;
	}
	return true;
}

/// @brief Draw the status bar beside the game map
/// @return Always returns true by default
bool cApp::DrawStatusBar()
{
	const std::string score_board_dynamic = "score_bar" + cFrameManager::GetInstance().ShowFrameID(4, 0.005f);
	const auto object = cAssetManager::GetInstance().GetSprite(score_board_dynamic);
	constexpr int32_t nOffSetX_sb = 272;
	constexpr int32_t nOffSetY_sb = 0;
	constexpr int32_t nOriginX_sb = 0;
	constexpr int32_t nOriginY_sb = 0;
	constexpr int32_t nWidth_sb = 80;
	constexpr int32_t nHeight_sb = 160;
	constexpr int32_t nPosX_level = 321;
	constexpr int32_t nPosY_level = 80;
	int nPosX_PlayerName = 312 - playerName.size() * 4;
	int nPosY_PlayerName = 63;
	DrawPartialSprite(nOffSetX_sb, nOffSetY_sb, object, nOriginX_sb, nOriginY_sb, nWidth_sb, nHeight_sb);
	SetPixelMode(app::Pixel::MASK);
	DrawBigText(playerName, nPosX_PlayerName, nPosY_PlayerName);
	DrawBigText(MapLoader.ShowMapLevel(), nPosX_level, nPosY_level);
	SetPixelMode(app::Pixel::NORMAL);
	DrawBigText(std::to_string(nLife), nPosX_level, 99);
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// END OF FILE ////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////