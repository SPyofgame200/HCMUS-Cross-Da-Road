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

constexpr float fConst = 2.0f;

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// CONSTRUCTOR & DESTRUCTOR ////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Default constructor init menu and game
cApp::cApp()
{
	SetDefaultTargetSize(app_const::SPRITE_WIDTH, app_const::SPRITE_HEIGHT);
	Zone.SetCellSize(app_const::CELL_SIZE, app_const::CELL_SIZE);
	Player = hPlayer(this);
	MapDrawer = hMapDrawer(this);
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
/// @return true if success, false otherwise
bool cApp::GameInit()
{
	using namespace app_const;
	fTimeSinceStart = 0;
	sAppName = APP_NAME;
	nLaneWidth = LANE_WIDTH;
	nCellSize = CELL_SIZE;
	nScore = 0;
	MapLoader.Init();
	return true;
}

/// @brief Exit game, clear data
bool cApp::GameExit()
{
	MapLoader.Destruct();
	return true;
}
/// @brief Go to next map level
bool cApp::GameNext()
{
	MapLoader.NextLevel();
	GameReset();
	return true;
}
//// @brief Go to previous map level
bool cApp::GamePrev()
{
	MapLoader.PrevLevel();
	GameReset();
	return true;
}
/// @brief Reset game, clear data, load map, reset Player position, danger area, score
bool cApp::GameReset()
{
	fTimeSinceStart = 0.0f;

	sAppName = "Cross Da Road " + MapLoader.ShowMapInfo();
	Zone.CreateZone(ScreenWidth(), ScreenHeight());
	Player.Reset();

	Clear(app::BLACK);
	MapLoader.LoadMapLevel();
	Zone.SetPattern(MapLoader.GetDangerPattern().c_str(), MapLoader.GetBlockPattern().c_str());
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// COLLISION DETECTION ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief 
///	@param x - X position of Player
///	@param y - Y position of Player
///	@return MapObject of hitbox of Player
MapObject cApp::GetHitBox(float x, float y) const
{
	const cMapLane lane = MapLoader.GetLaneRound(y);
	const int nStartPos = lane.GetStartPos(fTimeSinceStart);
	const char graphic = lane.GetLaneGraphic(nStartPos + static_cast<int>(x));
	return MapLoader.GetSpriteData(graphic);
}
/// @brief 
MapObject cApp::GetHitBox() const
{
	const float fPosX = Player.GetPlayerLogicPositionX();
	const float fPosY = Player.GetPlayerLogicPositionY();
	return GetHitBox(fPosX, fPosY);
}
/// @brief 
/// @param bDebug 
/// @return 
bool cApp::IsKilled(bool bDebug) const
{
	const float fPosY = Player.GetPlayerLogicPositionY();
	const float fPosX = Player.GetPlayerLogicPositionX();
	const bool isHit = Player.IsHit();
	if (!isHit) {
		return false;
	}

	const MapObject dataLeft = GetHitBox(fPosX - static_cast<float>(nCellSize) / fConst, fPosY);
	const MapObject dataRight = GetHitBox(fPosX + static_cast<float>(nCellSize) / fConst, fPosY);
	if (bDebug) {
		std::cerr << "Left touching[" << dataLeft.encode << "]: ";
		std::cerr << "sprite \"" << dataLeft.sSpriteName << "\" ";
		std::cerr << "background = \"" << dataLeft.sBackgroundName << "\" ";
		std::cerr << "platform speed = " << dataLeft.fPlatform << " ";
		std::cerr << "lane speed = " << MapLoader.GetLaneRound(fPosY).GetVelocity() << " ";
		std::cerr << "is Player jumping safe = " << std::boolalpha << Player.IsPlayerCollisionSafe() << " ";
		std::cerr << std::endl;
		std::cerr << "Right touching[" << dataRight.encode << "]: ";
		std::cerr << "sprite \"" << dataRight.sSpriteName << "\" ";
		std::cerr << "background = \"" << dataRight.sBackgroundName << "\" ";
		std::cerr << "platform speed = " << dataRight.fPlatform << " ";
		std::cerr << "lane speed = " << MapLoader.GetLaneRound(fPosY).GetVelocity() << " ";
		std::cerr << "is Player jumping safe = " << std::boolalpha << Player.IsPlayerCollisionSafe() << " ";
		std::cerr << std::endl;
	}


	if (Player.IsPlayerCollisionSafe()) {
		return false;
	}

	return true;
}
/// @brief 
/// @return 
std::string cApp::GetPlayerDeathMessage() const
{
	float fPosX = Player.GetPlayerLogicPositionX();
	float fPosY = Player.GetPlayerLogicPositionY();
	constexpr  float fConst = 2.0;
	const MapObject leftData = GetHitBox(fPosX - static_cast<float>(nCellSize) / fConst, fPosY);
	const MapObject rightData = GetHitBox(fPosX + static_cast<float>(nCellSize) / fConst, fPosY);
	const std::string sLeft = leftData.sSpriteName;
	const std::string sRight = rightData.sSpriteName;

	if (sLeft.empty() && sRight.empty()) {
		return "Player has been force killed";
	}
	else {
		if (!sLeft.empty()) {
			return "Player has been killed by " + sLeft;
		}
		else {
			return "Player has been killed by " + sRight;
		}
	}
}
/// @brief 
/// @return 
bool cApp::IsPlatformLeft() const
{
	const float fPosX = Player.GetPlayerLogicPositionX();
	const float fPosY = Player.GetPlayerLogicPositionY();
	const MapObject leftData = GetHitBox(fPosX - static_cast<float>(nCellSize) / fConst, fPosY);
	return !leftData.sSpriteName.empty() && std::fabs(leftData.fPlatform) > 0;
}
/// @brief 
/// @return 
bool cApp::IsPlatformRight() const
{
	const float fPosX = Player.GetPlayerLogicPositionX();
	const float fPosY = Player.GetPlayerLogicPositionY();
	const MapObject rightData = GetHitBox(fPosX + static_cast<float>(nCellSize) / fConst, fPosY);
	return !rightData.sSpriteName.empty() && std::fabs(rightData.fPlatform) > 0;
}
/// @brief 
/// @return 
bool cApp::IsPlatformCenter() const
{
	const float fPosX = Player.GetPlayerLogicPositionX();
	const float fPosY = Player.GetPlayerLogicPositionY();
	const MapObject rightData = GetHitBox(fPosX, fPosY);
	return !rightData.sSpriteName.empty() && std::fabs(rightData.fPlatform) > 0;
}
/// @brief 
/// @return 
bool cApp::IsOnPlatform() const
{
	return IsPlatformLeft()
		|| IsPlatformRight()
		|| IsPlatformCenter();
}
/// @brief 
/// @param fElapsedTime 
/// @return 
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

/// @brief 
/// @param fElapsedTime 
/// @return 
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
	if (Player.IsPlayerOutOfBounds() || IsKilled(true)) {
		return OnPlayerDeath();
	}
	return true;
}
/// @brief 
/// @return 
bool cApp::OnPlayerDeath()
{
	std::cout << GetPlayerDeathMessage() << std::endl;
	bDeath = true;
	Player.OnRenderPlayerDeath();
	Player.Reset();
	bDeath = false;
	return true;
}
/// @brief Draw all lanes, render Player, draw status bar
bool cApp::OnGameRender()
{
	DrawAllLanes();
	Player.OnRenderPlayer();
	DrawStatusBar();
	return true;
}
// @brief Set frame delay, load all sprites, open menu
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
		Player.OnUpdateFrame(fTickTime);
	}
	return true;
}
/// @brief Update event that called when application is updated
///	@parma fElapsedTime - Time elapsed since last update
bool cApp::OnUpdateEvent(const float fElapsedTime)
{
	if (!Menu.Update(fElapsedTime)) {
		return false;
	}
	return true;
}
/// @brief
///	@param fElapsedTime
///	@param fLateElapsedTime
bool cApp::OnLateUpdateEvent(float fElapsedTime, float fLateElapsedTime)
{
	return true;
}
bool cApp::OnCreateNewName()
{

	return true;
}
bool cApp::OnDisplaySaveBox()
{

	return false;
}

bool cApp::UpdateDrawNameBox()
{
	if (IsKeyReleased(app::Key::DOWN)) {
		nameBoxOption++;
	}
	if (IsKeyReleased(app::Key::UP)) {
		nameBoxOption--;
	}

	return true;
}

bool cApp::DrawNameBox()
{
	const app::Sprite* NameBox = cAssetManager::GetInstance().GetSprite("createNameBox");
	const app::Sprite* NameBoxChosen = cAssetManager::GetInstance().GetSprite("start_chosen");

	Clear(app::BLACK);
	if (nameBoxOption % 2 == 0)
		DrawSprite(0, 0, NameBox);
	else
		DrawSprite(0, 0, NameBoxChosen);
	if (IsKeyHolding(app::Key::K)) {
		SetPixelMode(app::Pixel::MASK);
		DrawBigText("SPyofgame", 27, 27);
		SetPixelMode(app::Pixel::NORMAL);
	}
	return true;
}

/// @brief Rendering menu and game (if game is running)
bool cApp::OnRenderEvent()
{
	if (!Menu.Render()) {
		return false;
	}
	return true;
}
/// @brief 
/// @return 
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
/// @brief 
/// @return 
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
		Menu.UpdatePausing();
		OnGameRender();
		Menu.RenderPausing();
		return false;
	}
	return true; // succesfully handle the pause event
}
/// @brief Event that called when application is force paused
bool cApp::OnForcePauseEvent()
{
	if (!Menu.IsOnGame()) {
		return false;
	}
	PauseEngine();
	return true;
}
/// @brief Event that called when application is destroyed normally
bool cApp::OnDestroyEvent()
{
	GameExit();
	return true;
}
/// @brief Event that called when application is destroyed forcefully
bool cApp::OnForceDestroyEvent()
{
	GameExit();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// FILE MANAGEMENT ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief 
/// @param isSave 
/// @return 
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
////////////////////////////////////// GAME RENDERING ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

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
		DrawPartialSprite(x + i * app_const::FONT_WIDTH, y, cAssetManager::GetInstance().GetSprite("font"), nDrawX, nDrawY, app_const::FONT_WIDTH, app_const::FONT_HEIGHT);
		i++;
	}
	return true;
}
/// @brief Draw the status bar beside the game map
bool cApp::DrawStatusBar()
{
	const std::string score_board_dynamic = "score_bar" + Player.ShowFrameID(4);
	const auto object = cAssetManager::GetInstance().GetSprite(score_board_dynamic);
	constexpr int32_t nOffSetX_sb = 272;
	constexpr int32_t nOffSetY_sb = 0;
	constexpr int32_t nOriginX_sb = 0;
	constexpr int32_t nOriginY_sb = 0;
	constexpr int32_t nWidth_sb = 80;
	constexpr int32_t nHeight_sb = 160;

	constexpr int32_t nPosX_level = 321;
	constexpr int32_t nPosY_level = 90;
	DrawPartialSprite(nOffSetX_sb, nOffSetY_sb, object, nOriginX_sb, nOriginY_sb, nWidth_sb, nHeight_sb);
	SetPixelMode(app::Pixel::MASK);
	DrawBigText(MapLoader.ShowMapLevel(), nPosX_level, nPosY_level);
	SetPixelMode(app::Pixel::NORMAL);
	return true;
}



///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// END OF FILE ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////