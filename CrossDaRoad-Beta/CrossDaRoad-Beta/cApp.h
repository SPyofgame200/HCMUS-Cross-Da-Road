/**
 * @file cApp.h
 * @brief Contains application class
 *
 * This file contains application class for application management (init, exit, update, render).
**/

#ifndef C_APP_H
#define C_APP_H

// Core game
#include "gGameEngine.h"
// Utilities
#include "uAppConst.h"
// Game Data
#include "cMapObject.h"
#include "cZone.h"
// UI & HUD
#include "cAssetManager.h"
#include "cMapLoader.h"
#include "hMapDrawer.h"
#include "cFrame.h"
// Event Handlers
#include "hPlayer.h"
#include "hMenu.h"
// Standard
#include <map>
#include <string>
#include <vector>

/// @brief Class for application management (init, exit, update, render) inherited from app::GameEngine
class cApp : public app::GameEngine
{
	friend class hMenu;
	friend class hPlayer;
	friend class hMapDrawer;

private: // Interactive Properties (control the map)
	hMenu Menu;
	hPlayer Player;
	int nameBoxOption = 0;
	std::string playerName;
private: // Reinitializable Properties (depended on each map)
	cZone Zone;
	cMapLoader MapLoader;
	hMapDrawer MapDrawer;

private: // Customizable Properties (applied to all maps)
	int nLaneWidth;
	int nCellSize;
	int nScore = 0;

private: // Event timers
	float fTimeSinceStart;

private: // Animator
	frame4_t frame4;
	frame6_t frame6;
	frame8_t frame8;

private: // Special variables
	std::atomic<bool> bDeath;

public: // Constructor & Destructor
	cApp();
	~cApp() override;

protected: // Constructor & Destructor Procedure
	bool GameInit();
	bool GameExit();
	bool GameNext();
	bool GamePrev();
	bool GameReset();

protected: // Collision Detection
	MapObject GetHitBox(float x, float y) const;
	MapObject GetHitBox() const;
	std::string GetPlayerDeathMessage() const;
	float GetPlatformVelocity(float fElapsedTime) const;

	bool IsKilled(bool bDebug = false) const;
	bool IsPlatformLeft() const;
	bool IsPlatformRight() const;
	bool IsPlatformCenter() const;
	bool IsOnPlatform() const;

protected: /// Game Updates
	bool OnGameUpdate(float fElapsedTime);
	bool OnPlayerDeath();
	bool OnGameRender();
	bool OnCreateEvent() override;
	bool OnFixedUpdateEvent(float fTickTime, const engine::Tick& eTickMessage) override;
	bool OnUpdateEvent(float fElapsedTime) override;
	bool OnLateUpdateEvent(float fElapsedTime, float fLateElapsedTime) override;

	bool OnGameSave() const;
	bool OnGameLoad();
	bool OnCreateNewName();
	bool DrawNameBox();
	bool UpdateDrawNameBox();
	bool OnDisplaySaveBox();
	bool OnRenderEvent() override;
	bool OnPauseEvent() override;
	bool OnForcePauseEvent() override;
	bool OnDestroyEvent() override;
	bool OnForceDestroyEvent() override;

protected: // File Management
	static std::string GetFilePathLocation(bool isSaven, std::string fileName);

private: // Game Rendering
	bool DrawAllLanes() const;
	bool DrawBigText(const std::string& sText, int x, int y);
	bool DrawStatusBar();

private: // Animator
	int GetFrameID(int frame) const;
	int GetFrameID(int frame, float fTickRate) const;
	std::string ShowFrameID(int frame) const;
	std::string ShowFrameID(int frame, float fTickRate) const;
	bool OnUpdateFrame(float fTickTime, float fTickRate = 0.01f);
};

#endif // C_APP_H
