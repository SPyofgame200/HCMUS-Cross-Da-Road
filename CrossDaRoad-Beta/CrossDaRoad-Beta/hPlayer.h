/**
 * @file hPlayer.h
 *
 * @brief Contains player class
 *
 * This file contains player class for player management, movement, and rendering.
**/

#ifndef H_PLAYER_H
#define H_PLAYER_H

// Utilities
#include "uAppConst.h"
// Data managements
#include "cPlayerStatus.h"
#include "cPlayerPhysic.h"
#include "cPlayerRecord.h"
#include "cPlayerMoment.h"

//=================================================================================================
// Include new header files here

//=================================================================================================
    
class cApp;
class cZone;
class hPlayerHitbox;
class hPlayerMotion;
class hPlayerUpdate;
class hPlayerRender;

/// @brief Class for player management, movement, and rendering

class hPlayer
{
private: /// Dependency
    static cApp* ptrApp;

private: /// Componnets handlers
    static hPlayerHitbox hHitbox;
    static hPlayerMotion hMotion;
    static hPlayerUpdate hUpdate;
    static hPlayerRender hRender;

private: /// Data management
    cPlayerStatus cStatus; // handle flag related data
    cPlayerPhysic cPhysic; // handle physical & collisions
    cPlayerRecord cRecord; // handle user saved data
    cPlayerMoment cMoment; // handle time related data

public: /// Components getters
    static hPlayerHitbox& Hitbox();
    static hPlayerMotion& Motion();
    static hPlayerUpdate& Update();
    static hPlayerRender& Render();

public: /// Data getters
    cPlayerStatus& Status();
    cPlayerPhysic& Physic();
    cPlayerRecord& Record();
    cPlayerMoment& Moment();

public: /// Data const getters
    const cPlayerStatus& Status() const;
    const cPlayerPhysic& Physic() const;
    const cPlayerRecord& Record() const;
    const cPlayerMoment& Moment() const;

public: // Constructors & Destructor
    hPlayer();
    hPlayer(cApp* ptrApp);
    ~hPlayer();

public: // Initializer & Clean-up
    bool SetupTarget(cApp* ptrApp);
    bool SetupComponents();

public: // Reseters
    void Reset();

public: // Checkers
    bool IsPlayerWin() const;
    bool IsForceKilled() const;
    bool IsKilled() const;

public: // Logic-Render Control
    bool UpdateAction(bool bLeft, bool bRight, bool bUp, bool bDown);
    bool OnUpdate();
    bool OnRender(bool bSwim = false);
    bool Draw(const std::string& sSpriteName, bool bReloadMap = false, bool bForceRender = false);

public: // Special
    void Sleep(float fTime);
    cZone* GetDangerZone();
    cZone* GetBlockedZone();
    cZone* GetWinningZone();
    cZone* GetPlatformZone();

public: // Input - Output
    void Read(std::istream& input);
    void Write(std::ostream& output) const;
    friend std::istream& operator>>(std::istream& input, hPlayer& player);
    friend std::ostream& operator<<(std::ostream& output, const hPlayer& player);
};

#endif // H_PLAYER_H