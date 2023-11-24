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
#include "hPlayerMovement.h"
#include "hPlayerRenderer.h"

class cApp;
class cZone;

/// @brief Class for player management, movement, and rendering
class hPlayer
{
private: /// Componnets handlers
	static hPlayerMovement hMovement;
	static hPlayerRenderer hRenderer;

public: /// Components getters
	static hPlayerMovement& Movement();
	static hPlayerRenderer& Renderer();

public:
	/// @brief Direction enumeration for player movement
	enum Direction
	{
		LEFT = 1,			///< Left direction for player movement
		RIGHT = 2, 			///< Right direction for player movement
		LEFT_UP = 3, 		///< Left-up direction for player movement
		RIGHT_UP = 4, 		///< Right-up direction for player movement
		LEFT_DOWN = 5, 		///< Left-down direction for player movement
		RIGHT_DOWN = 6, 	///< Right-down direction for player movement
	};
	/// @brief Animation enumeration for player animation
	enum Animation
	{
		IDLE = 0,			///< Idle animation for player
		JUMP = 1,			///< Jump animation for player
		LAND = 2,			///< Land animation for player
	};

	enum State
	{
		ALIVE = 0,
		DEATH = 1,
		VICTORY = 2,
	};

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
	Direction eDirection;
	Animation eAnimation;

private:
	cApp* ptrApp;
	std::string Name;

public: // Constructors & Destructor
	hPlayer();
	hPlayer(cApp* ptrApp);
	~hPlayer();

public: // Initializer & Clean-up
	bool SetupTarget(cApp* ptrApp);

private: // Reseter helpers
	void ResetDirection();
	void ResetAnimation();
	void ResetPosition();
	void ResetVelocity();

public: // Reseters
	void Reset();

public: // Checkers helpers
	bool IsExactDirection(Direction eCompare) const;
	bool IsExactAnimation(Animation eCompare) const;
	bool IsLeftDirection() const;
	bool IsRightDirection() const;
	bool IsPlayerJumping() const;
	bool IsPlayerIdling() const;
	bool IsPlayerLanding() const;

public: // Checkers
	bool IsPlayerCollisionSafe() const;
	bool IsPlayerOutOfBounds() const;
	bool IsPlayerWin() const;
	bool IsKilled() const;

public: /// Movement Checkers
	bool IsMoveLeft() const;
	bool IsMoveRight() const;
	bool IsMoveUp() const;
	bool IsMoveDown() const;

public: // Collision Detection
	bool IsPlatform() const;
	bool IsHit() const;
	bool IsBlocked() const;

public: // Validators
	bool CanMoveLeft() const;
	bool CanMoveRight() const;
	bool CanMoveUp() const;
	bool CanMoveDown() const;

public: // Getters
	Direction GetDirection() const;
	Animation GetAnimation() const;
	float GetPlayerAnimationPositionX() const;
	float GetPlayerAnimationPositionY() const;
	float GetPlayerLogicPositionX() const;
	float GetPlayerLogicPositionY() const;
	float GetPlayerVelocityX()const;
	float GetPlayerVelocityY()const;
	std::string GetPlayerName() const;

public: // Setters
	static float FixFloat(float fValue, int nDigits = 9);
	void SetDirection(Direction eNewDirection);
	void SetAnimation(Animation eNewAnimation);
	void SetPlayerVelocityX(float fVelocityX);
	void SetPlayerVelocityY(float fVelocityY);
	void SetPlayerVelocity(float fVelocityX, float fVelocityY);
	void SetPlayerAnimationPositionX(float fPositionX);
	void SetPlayerAnimationPositionY(float fPositionY);
	void SetPlayerAnimationPosition(float fPositionX, float fPositionY);
	void SetPlayerLogicPositionX(float fPositionX);
	void SetPlayerLogicPositionY(float fPositionY);
	void SetPlayerLogicPosition(float fPositionX, float fPositionY);
	void SetPlayerName(const std::string& Name);

private: // Validators & Fixers
	bool OnFixPlayerPosition();

private: // Logic Updater
	bool OnUpdatePlayerIdle();
	bool OnUpdatePlayerJumpStart();
	bool OnUpdatePlayerJumpContinue() const;
	bool OnUpdatePlayerJumpStop();

public: // Logic-Render Control
	bool OnPlayerMove();
	bool Draw(const std::string& sSpriteName, bool bReloadMap = false, bool bForceRender = false);
	void Sleep(float fTime);
};

#endif // H_PLAYER_H