#ifndef C_APP_H
#define C_APP_H

#include "cPlayer.h"
#include "cAssetManager.h"
#include "cMapLoader.h"
#include "cMenu.h"
#include "cZone.h"
#include "gGameEngine.h"
#include "uAppConst.h"
#include <map>
#include <string>
#include <vector>

/// @brief Class for application management (init, exit, update, render) inherited from app::GameEngine
class cApp : public app::GameEngine
{
	friend class cMenu;
	friend class cPlayer;

private: // Interactive Properties (control the map)
	cMenu Menu; 
	cPlayer Player;

private: // Reinitializable Properties (depended on each map)
	cZone Zone;
	cMapLoader MapLoader;

private: // Customizable Properties (applied to all maps)
	int nLaneWidth;
	int nCellSize;
	int nScore = 0;
	bool wantToExit = true;

private: // Event timers
	float fTimeSinceStart;
	float fTimeSinceLastDrawn;

private: // Special states (applied to freeze frames)
	bool bPause = false;
	bool bDeath = false;

private:
	int pauseOption = 1;
	std::string choices[3] = { "exit", "resume", "save" };

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
	SpriteData GetHitBox(float x, float y) const;
	SpriteData GetHitBox() const;
	std::string GetPlayerDeathMessage() const;
	float GetPlatformVelocity(float fElapsedTime) const;

	bool IsKilled(bool bDebug = false) const;
	bool IsPlatformLeft() const;
	bool IsPlatformRight() const;
	bool IsPlatformCenter() const;
	bool IsOnPlatform() const;
	
protected: /// Game Updates
	bool OnPlayerUpdate(float fElapsedTime);
	bool OnPlayerDeath();
	bool OnGameUpdate();
	bool OnCreateEvent() override;
	bool OnFixedUpdateEvent(float fTickTime, const engine::Tick& eTickMessage) override;
	bool OnUpdateEvent(float fElapsedTime) override;
	bool OnLateUpdateEvent(float fElapsedTime, float fLateElapsedTime) override;
	bool OnGameSave();
	bool OnGameLoad();
	bool OnRenderEvent() override;
	bool OnPauseEvent() override;
	bool OnDestroyEvent() override;
	bool OnForceDestroyEvent() override;

protected: // File Management
	std::string SelectTextFilePath(const char* initialDir, const std::string& sDefaultFilePath = "") const;
	std::string GetFilePartLocation(bool isSave);

private: // Game Rendering
	bool DisplayPauseMenu();
	bool DrawLane(const cLane& lane, int nRow, int nCol);
	bool DrawAllLanes();
	bool DrawBigText(const std::string& sText, int x, int y);
	bool DrawStatusBar();
};

#endif // C_APP_H
