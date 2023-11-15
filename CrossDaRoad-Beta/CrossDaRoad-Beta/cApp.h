#ifndef C_APP_H
#define C_APP_H

// Core game
#include "gGameEngine.h"
// Utilities
#include "uAppConst.h"
// Objects & Hitboxes
#include "hPlayer.h"
#include "cMapObject.h"
#include "cZone.h"
// Assets
#include "cAssetManager.h"
// Maps
#include "cMapLoader.h"
#include "hMapDrawer.h"
// HUD
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
	float fTimeSinceLastDrawn;

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
	bool OnRenderEvent() override;
	bool OnPauseEvent() override;
	bool OnForcePauseEvent() override;
	bool OnDestroyEvent() override;
	bool OnForceDestroyEvent() override;

protected: // File Management
	static std::string SelectFilePath(const char* filter, const char* initialDir, bool saveDialog = false);
	static std::string SelectTextFilePath(const char* initialDir, const std::string& sDefaultFilePath = "");
	static std::string GetFilePartLocation(bool isSave);

private: // Game Rendering
	bool DrawAllLanes();
	bool DrawBigText(const std::string& sText, int x, int y);
	bool DrawStatusBar();
};

#endif // C_APP_H
