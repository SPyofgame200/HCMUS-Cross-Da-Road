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
#include "uAppConst.h"
#include "cPlayerStatus.h"

class cApp;
class cZone;
class hPlayerHitbox;
class hPlayerMotion;
class hPlayerUpdate;
class hPlayerRender;

/// @brief Class for player management, movement, and rendering

class hPlayer
{
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

public: /// Data getters
	cPlayerStatus& Status();

private:
	float fFrogVelocityX;   ///< Velocity of player in X-axis
	float fFrogVelocityY;  	///< Velocity of player in Y-axis
	float fFrogAnimPosX;	///< Animation position of player in X-axis
	float fFrogAnimPosY;	///< Animation position of player in Y-axis
	float fFrogLogicPosX;	///< Logic position of player in X-axis
	float fFrogLogicPosY;	///< Logic position of player in Y-axis

private:
	int frame6_id_animation_safe;

private:
	cApp* ptrApp;
	std::string Name;

public: // Constructors & Destructor
	hPlayer();
	hPlayer(cApp* ptrApp);
	~hPlayer();

public: // Initializer & Clean-up
	bool SetupTarget(cApp* ptrApp);
	bool SetupComponents();

public: // Reseters
	void Reset();
	void SynchronizePosition(bool bAnimToLogic = true);

public: // Checkers helpers
	bool IsPlayerMoving() const;
	bool IsPlayerJumping() const;
	bool IsPlayerStartingJump() const;
	bool IsPlayerIdling() const;
	bool IsPlayerLanding() const;

public: // Checkers
	bool IsPlayerCollisionSafe() const;
	bool IsPlayerOutOfBounds() const;
	bool IsPlayerWin() const;
	bool IsKilled() const;

public: /// Motion Checkers
	bool IsMoveLeft() const;
	bool IsMoveRight() const;
	bool IsMoveUp() const;
	bool IsMoveDown() const;

public: // Validators
	bool CanMoveLeft() const;
	bool CanMoveRight() const;
	bool CanMoveUp() const;
	bool CanMoveDown() const;

public: // Getters
	float GetPlayerAnimationPositionX() const;
	float GetPlayerAnimationPositionY() const;
	float GetPlayerLogicPositionX() const;
	float GetPlayerLogicPositionY() const;
	float GetPlayerVelocityX()const;
	float GetPlayerVelocityY()const;
	std::string GetPlayerName() const;

public: // Setters
	static float FixFloat(float fValue, int nDigits = 9);
	void SetVelocityX(float fVelocityX);
	void SetVelocityY(float fVelocityY);
	void SetVelocity(float fVelocityX, float fVelocityY);
	void SetAnimationPositionX(float fPositionX);
	void SetAnimationPositionY(float fPositionY);
	void SetAnimationPosition(float fPositionX, float fPositionY);
	void SetLogicPositionX(float fPositionX);
	void SetLogicPositionY(float fPositionY);
	void SetLogicPosition(float fPositionX, float fPositionY);
	void SetPlayerName(const std::string& Name);

private: // Validators & Fixers
	bool OnFixPlayerPosition();

public: // Logic-Render Control
	bool OnUpdate();
	bool OnRender();
	bool Draw(const std::string& sSpriteName, bool bReloadMap = false, bool bForceRender = false);

public: // Special
	void Sleep(float fTime);
	cZone* GetZone();
};

#endif // H_PLAYER_H