/**
 * @file hPlayer.h
 *
 * @brief Contains player class
 *
 * This file contains player class for player management, movement, and rendering.
**/

#ifndef H_PLAYER_H
#define H_PLAYER_H

#include <string>
// Utilities
#include "uAppConst.h"
// Data managements
#include "cPlayerStatus.h"
#include "cPlayerPhysic.h"
#include "cPlayerRecord.h"
#include "cPlayerAction.h"
	
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
	cApp* ptrApp;

private: /// Componnets handlers
	static hPlayerHitbox hHitbox;
	static hPlayerMotion hMotion;
	static hPlayerUpdate hUpdate;
	static hPlayerRender hRender;

public: /// Components getters
	static hPlayerHitbox& Hitbox();
	static hPlayerMotion& Motion();
	static hPlayerUpdate& Update();
	static hPlayerRender& Render();

private: /// Data management
	cPlayerStatus status;
	cPlayerPhysic physic;
	cPlayerRecord record;
	cPlayerAction action;

public: /// Data getters
	cPlayerStatus& Status();
	cPlayerPhysic& Physic();
	cPlayerRecord& Record();
	cPlayerAction& Action();
	const cPlayerStatus& Status() const;
	const cPlayerPhysic& Physic() const;
	const cPlayerRecord& Record() const;
	const cPlayerAction& Action() const;

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
	bool IsPlayerMoving() const;
	bool IsPlayerJumping() const;
	bool IsPlayerStartingJump() const;
	bool IsPlayerIdling() const;
	bool IsPlayerLanding() const;

public: // Checkers
	bool IsPlayerCollisionSafe() const;
	bool IsPlayerWin() const;
	bool IsForceKilled() const;
	bool IsKilled() const;

public: // Logic-Render Control
	bool UpdateAction(bool bLeft, bool bRight, bool bUp, bool bDown);
	bool OnUpdate();
	bool OnRender();
	bool Draw(const std::string& sSpriteName, bool bReloadMap = false, bool bForceRender = false);

public: // Special
	void Sleep(float fTime);
	cZone* GetZone();
};

#endif // H_PLAYER_H