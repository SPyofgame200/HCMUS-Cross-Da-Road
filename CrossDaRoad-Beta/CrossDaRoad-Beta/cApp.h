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
private: // [Data Component]
    cZone cDangerZone;
    cZone cPlatformZone;
    cZone cBlockedZone;
    cMapLoader MapLoader;

private: // [Handle Component]
    hMenu Menu;
    hPlayer Player;
    hMapDrawer MapDrawer;

private: // [Friend Property]
    friend class hMenu;
    friend class hPlayer;
    friend class hMapDrawer;

private: // [Member Property]
    std::string playerName;
    int nScore = 0;
    int nLife;
    float fTimeSinceStart;

public: // [Constructor] & [Destructor]
    cApp();
    ~cApp() override;
    int GetLife() const;
    void SetLife(int Life);
    void SetPlayerName(std::string Nm);
protected: // [Initializer] & [Disposer]
    bool GameInit();
    bool GameExit();

protected: // [Reseter]
    bool GameReset();
    bool GameNext();
    bool GamePrev();

protected: // [Core] App events
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

protected: // [Evaluation]
    float GetPlatformVelocity(float fElapsedTime) const;

protected: // [Event]
    bool OnGameUpdate(float fElapsedTime);
    bool OnPlayerDeath();
    bool OnGameRender(bool bRenderPlayer = false);

private: // [Handler]
    bool DrawAllLanes() const;
    bool DrawBigText(const std::string& sText, int x, int y, int space = 0);
    bool DrawBigText1(const std::string& sText, int x, int y, int space = 0);
    bool DrawStatusBar();
    bool Draw(const std::string& sSpriteName, bool bReloadMap = false, bool bForceRender = false);

protected: // [File]
    static std::string GetFilePathLocation(bool isSaven, std::string fileName);
    bool OnGameSave();
    bool OnGameLoad(const std::string& pPath, const std::string& PlayerName);

private: // [Utility]
    void ForceSleep(float fTime);
};

#endif // C_APP_H
