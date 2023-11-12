#include "cApp.h"
#include "uSound.h"
#include "uStringUtils.h"
#include <Windows.h>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <thread>

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// CONSTRUCTOR & DESTRUCTOR ////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Default constructor init menu and game
cApp::cApp()
{
	Player = cPlayer(this);
	Menu.InitMenu();
	GameInit();
}
/// @brief Default destructor exit menu and game
cApp::~cApp()
{
	Menu.ExitMenu();
	GameExit();
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
	fTimeSinceLastDrawn = 0;
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
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// COLLISION DETECTION ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief 
///	@param x - X position of Player
///	@param y - Y position of Player
///	@return SpriteData of hitbox of Player
SpriteData cApp::GetHitBox(float x, float y) const
{
	const cLane lane = MapLoader.GetLaneRound(y);
	int nStartPos = static_cast<int>(x + fTimeSinceLastDrawn * lane.GetVelocity()) % app_const::MAP_WIDTH_LIMIT;
	const int nCellOffset = static_cast<int>(static_cast<float>(nCellSize) * fTimeSinceStart * lane.GetVelocity()) % nCellSize;
	if (nStartPos < 0) {
		nStartPos = app_const::MAP_WIDTH_LIMIT - (abs(nStartPos) % app_const::MAP_WIDTH_LIMIT);
	}
	const char graphic = lane.GetLane()[(nStartPos) % app_const::MAP_WIDTH_LIMIT];
	return MapLoader.GetSpriteData(graphic);
}
/// @brief 
SpriteData cApp::GetHitBox() const
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

	const SpriteData dataLeft = GetHitBox(fPosX - nCellSize / 2.0f, fPosY);
	const SpriteData dataRight = GetHitBox(fPosX + nCellSize / 2.0f, fPosY);
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
	const SpriteData leftData = GetHitBox(fPosX - nCellSize / 2.0f, fPosY);
	const SpriteData rightData = GetHitBox(fPosX + nCellSize / 2.0f, fPosY);
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
	return "Player has been killed both " + sLeft + " & " + sRight;
}
/// @brief 
/// @return 
bool cApp::IsPlatformLeft() const
{
	const float fPosX = Player.GetPlayerLogicPositionX();
	const float fPosY = Player.GetPlayerLogicPositionY();
	const SpriteData leftData = GetHitBox(fPosX - nCellSize / 2.0f, fPosY);
	return !leftData.sSpriteName.empty() && std::fabs(leftData.fPlatform) > 0;
}
/// @brief 
/// @return 
bool cApp::IsPlatformRight() const
{
	const float fPosX = Player.GetPlayerLogicPositionX();
	const float fPosY = Player.GetPlayerLogicPositionY();
	const SpriteData rightData = GetHitBox(fPosX + nCellSize / 2.0f, fPosY);
	return !rightData.sSpriteName.empty() && std::fabs(rightData.fPlatform) > 0;
}
/// @brief 
/// @return 
bool cApp::IsPlatformCenter() const
{
	const float fPosX = Player.GetPlayerLogicPositionX();
	const float fPosY = Player.GetPlayerLogicPositionY();
	const SpriteData rightData = GetHitBox(fPosX, fPosY);
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
	std::cerr << GetPlayerDeathMessage() << std::endl;
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
	SetFrameDelay(FrameDelay::STABLE_FPS_DELAY);
	cAssetManager::GetInstance().LoadAllSprites();
	Menu.OpenMenu(this);
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
	if (!Menu.Update(this, fElapsedTime)) {
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
/// @brief Rendering menu and game (if game is running)
bool cApp::OnRenderEvent()
{
	if (!Menu.Render(this)) {
		return false;
	}
	return true;
}
/// @brief 
/// @return 
bool cApp::OnGameSave()
{
	const std::string sSaveFilePath = GetFilePartLocation(true);
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
	const std::string sLoadFilePath = GetFilePartLocation(false);

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
	if (!Menu.UpdatePausing(this)) {
		Menu.RenderPausing(this);
		return false;
	}
	return true; // succesfully handle the pause event
}
/// @brief Event that called when application is force paused
bool cApp::OnForcePauseEvent()
{
	if (Menu.IsOnMenu()) {
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


std::string cApp ::SelectFilePath(const char* filter, const char* initialDir, bool saveDialog) const
{
	char previousDir[MAX_PATH];

	if (GetCurrentDirectoryA(MAX_PATH, previousDir) == 0) {
		std::cerr << "Error getting the current directory." << std::endl;
		return "";
	}

	OPENFILENAMEA ofn = {};
	char filePath[MAX_PATH] = "";
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFile = filePath;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = initialDir; // Set the initial directory

	if (saveDialog) {
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		if (!GetSaveFileNameA(&ofn)) {
			std::cerr << "User canceled the operation." << std::endl;
			return "";
		}
	}
	else {
		ofn.Flags = OFN_FILEMUSTEXIST;
		if (!GetOpenFileNameA(&ofn)) {
			std::cerr << "User canceled the operation." << std::endl;
			return "";
		}
	}

	// Restore the previous working directory
	if (!SetCurrentDirectoryA(previousDir)) {
		std::cerr << "Error restoring the previous working directory." << std::endl;
	}

	const std::string sFilePath = (filePath);
	return sFilePath;
}

/// @brief 
/// @param initialDir 
/// @param sDefaultFilePath 
/// @return 
std::string cApp::SelectTextFilePath(const char* initialDir, const std::string& sDefaultFilePath) const
{
	const char* cTextFilePatterns = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
	const std::string& sFilePath = SelectFilePath(cTextFilePatterns, initialDir);
	if (sFilePath.empty()) { // The user didnt select any file
		return sDefaultFilePath;
	}
	else { // File Path is selected
		return sFilePath;
	}
}
/// @brief 
/// @param isSave 
/// @return 
std::string cApp::GetFilePartLocation(bool isSave)
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
	ofn.lpstrDefExt = L"txt";

	size_t count;
	wcstombs_s(&count, szFileName, szFileNameW, MAX_PATH);

	if (isSave) {
		ofn.Flags = OFN_EXPLORER | OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;
		GetSaveFileName(&ofn);
		std::cout << "Selected File: " << szFileName << std::endl;
		return szFileName;
	}
	else {
		ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;
		GetOpenFileName(&ofn);
		std::cout << "Selected File: " << szFileName << std::endl;
		return szFileName;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// GAME RENDERING ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Draw a lane to the screen
///	@param lane - Lane to draw
///	@param nRow - Row to draw lane on
///	@param nCol - Column to draw lane on (default: -1)
///	@return true if lane was drawn successfully, false otherwise
bool cApp::DrawLane(const cLane& lane, const int nRow, const int nCol = -1)
{
	// Find lane offset start
	int nStartPos = static_cast<int>(fTimeSinceStart * lane.GetVelocity()) % app_const::MAP_WIDTH_LIMIT;
	const int nCellOffset = static_cast<int>(static_cast<float>(nCellSize) * fTimeSinceStart * lane.GetVelocity()) % nCellSize;
	if (nStartPos < 0) nStartPos %= app_const::MAP_WIDTH_LIMIT;
	if (nStartPos < 0) nStartPos += app_const::MAP_WIDTH_LIMIT;

	fTimeSinceLastDrawn = fTimeSinceStart;
	auto drawCharacter = [&](const int nLaneIndex, SpriteData& sprite, const int sx, const int sy, bool drawBackground) {
		const int32_t nPosX = (nCol + nLaneIndex) * nCellSize - nCellOffset;
		const int32_t nPosY = nRow * nCellSize;
		constexpr int32_t nWidth = app_const::SPRITE_WIDTH;
		constexpr int32_t nHeight = app_const::SPRITE_HEIGHT;
		if (drawBackground) {
			const std::string sName = sprite.sBackgroundName;
			if (sName.size()) {
				const app::Sprite* background = cAssetManager::GetInstance().GetSprite(sName);
				SetPixelMode(app::Pixel::NORMAL);
				DrawPartialSprite(nPosX + nCellOffset, nPosY, background, sx, sy, nWidth, nHeight);
				SetPixelMode(app::Pixel::NORMAL);
			}
		}
		else {
			const std::string sName = sprite.sSpriteName + (sprite.nID <= 0 ? "" : Player.ShowFrameID(sprite.nID));
			if (sName.size()) {
				const app::Sprite* object = cAssetManager::GetInstance().GetSprite(sName);
				SetPixelMode(app::Pixel::MASK);
				DrawPartialSprite(nPosX, nPosY, object, sx, sy, nWidth, nHeight);
				SetPixelMode(app::Pixel::NORMAL);
			}
			if (sprite.SuccessSummon(nStartPos + nLaneIndex, nRow, fTimeSinceLastDrawn, GetAppFPS(), !IsEnginePause())) {
				const std::string sSummonName = sprite.summon->sSpriteName + (sprite.summon->nID <= 0 ? "" : Player.ShowFrameID(sprite.summon->nID));
				if (sSummonName.size()) {
					const app::Sprite* summoned_object = cAssetManager::GetInstance().GetSprite(sSummonName);
					SetPixelMode(app::Pixel::MASK);
					DrawPartialSprite(nPosX, nPosY, summoned_object, sx, sy, nWidth, nHeight);
					SetPixelMode(app::Pixel::NORMAL);
				}
			}
		}
		};
	for (int nLaneIndex = 0; nLaneIndex <= nLaneWidth; nLaneIndex++) {
		const char graphic = lane.GetLane()[(nStartPos + nLaneIndex) % app_const::MAP_WIDTH_LIMIT];
		SpriteData data = MapLoader.GetSpriteData(graphic);
		drawCharacter(nLaneIndex, data, data.nBackgroundPosX * app_const::SPRITE_WIDTH, data.nBackgroundPosY * app_const::SPRITE_HEIGHT, true);
	}
	for (int nLaneIndex = 0; nLaneIndex <= nLaneWidth; nLaneIndex++) {
		const char graphic = lane.GetLane()[(nStartPos + nLaneIndex) % app_const::MAP_WIDTH_LIMIT];
		SpriteData data = MapLoader.GetSpriteData(graphic);
		drawCharacter(nLaneIndex, data, data.nSpritePosX * app_const::SPRITE_WIDTH, data.nSpritePosY * app_const::SPRITE_HEIGHT, false);
	}
	for (int nLaneIndex = 0; nLaneIndex <= nLaneWidth; nLaneIndex++) {
		const char graphic = lane.GetLane()[(nStartPos + nLaneIndex) % app_const::MAP_WIDTH_LIMIT];
		// Fill Danger buffer
		const int nTopLeftX = (nCol + nLaneIndex) * nCellSize - nCellOffset;
		const int nTopLeftY = nRow * nCellSize;
		const int nBottomRightX = (nCol + nLaneIndex + 1) * nCellSize - nCellOffset;
		const int nBottomRightY = (nRow + 1) * nCellSize;
		// std::cerr << "block pattern: \"" << blockPattern << "\"" << std::endl;
		Zone.FillDanger(nTopLeftX, nTopLeftY, nBottomRightX, nBottomRightY, graphic, MapLoader.GetDangerPattern().c_str());
		Zone.FillBlocked(nTopLeftX, nTopLeftY, nBottomRightX, nBottomRightY, graphic, MapLoader.GetBlockPattern().c_str());
	}
	return true;
}
/// @brief Draw all lanes  to screen
bool cApp::DrawAllLanes()
{
	int nRow = 0;
	const std::vector<cLane> vecLanes = MapLoader.GetLanes();
	for (const cLane& lane : vecLanes) {
		DrawLane(lane, nRow++);
	}

	return true;
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
		const int sx = ((c - 32) % 16) * app_const::FONT_WIDTH;  // 16: number of characters in a nRow
		const int sy = ((c - 32) / 16) * app_const::FONT_HEIGHT; // 32: ASCII code of the first character in the font
		DrawPartialSprite(x + i * app_const::FONT_WIDTH, y, cAssetManager::GetInstance().GetSprite("font"), sx, sy, app_const::FONT_WIDTH, app_const::FONT_HEIGHT);
		i++;
	}
	return true;
}
/// @brief Draw the status bar beside the game map
bool cApp::DrawStatusBar()
{
	const std::string score_board_dynamic = "score_bar" + Player.ShowFrameID(4);
	const auto object = cAssetManager::GetInstance().GetSprite(score_board_dynamic);
	DrawPartialSprite(272, 0, object, 0, 0, 80, 160);
	SetPixelMode(app::Pixel::MASK);
	DrawBigText(MapLoader.ShowMapLevel(), 321, 80);
	SetPixelMode(app::Pixel::NORMAL);
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// END OF FILE ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////