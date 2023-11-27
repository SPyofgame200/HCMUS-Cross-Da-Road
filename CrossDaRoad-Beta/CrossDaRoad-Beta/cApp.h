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
// Game Data
#include "cZone.h"
// UI & HUD
#include "cMapLoader.h"
#include "hMapDrawer.h"
// Event Handlers
#include "hPlayer.h"
#include "hMenu.h"

//=================================================================================================
// Include new header files here

//=================================================================================================


/// @brief Class for application management (init, exit, update, render) inherited from app::GameEngine
class cApp final : public app::GameEngine
{
	friend class hMenu;
	friend class hPlayer;
	friend class hMapDrawer;

private: // Interactive Properties (control the map)
	hMenu Menu;
	hPlayer Player;
	std::string playerName;

private: // Reinitializable Properties (depended on each map)
	cZone Zone;
	cMapLoader MapLoader;
	hMapDrawer MapDrawer;

private: // Customizable Properties (applied to all maps)
	int nScore = 0;
	int nLife;

private: // Event timers
	float fTimeSinceStart;

public: // Constructor & Destructor
	cApp();
	~cApp() override;

protected: // Initializers & Clean-up
	bool GameInit();
	bool GameExit();
	bool GameNext();
	bool GamePrev();
	bool GameReset();

protected: // Utilities
	float GetPlatformVelocity(float fElapsedTime) const;

protected: /// Game Events
	bool OnGameUpdate(float fElapsedTime);
	bool OnPlayerDeath(float fTickTime);
	bool OnGameRender(bool bRenderPlayer = false);
	bool OnGameSave() const;
	bool OnGameLoad();

protected: /// Core Events
	bool OnCreateEvent() override;
	bool OnTriggerEvent(float fTickTime, const engine::Triggerer& eTriggerer) override;
	bool OnFixedUpdateEvent(float fTickTime) override;
	bool OnUpdateEvent(float fElapsedTime) override;
	bool OnLateUpdateEvent(float fTickTime, float fElapsedTime, float fLateElapsedTime) override;
	bool OnRenderEvent() override;
	bool OnPauseEvent(float fTickTime) override;
	bool OnForcePauseEvent() override;
	bool OnDestroyEvent() override;
	bool OnForceDestroyEvent() override;

protected: // File Management
	static std::string GetFilePathLocation(bool isSaven, std::string fileName);

private: // Game Rendering
	bool DrawAllLanes() const;
	bool DrawBigText(const std::string& sText, int x, int y);
	bool DrawBigText1(const std::string& sText, int x, int y);
	bool DrawStatusBar();
	void ForceSleep(float fTime) { Sleep(static_cast<DWORD>(fTime)); }
};

#endif // C_APP_H
