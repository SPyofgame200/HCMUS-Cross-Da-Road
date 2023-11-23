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
class cApp;
class cZone;
class hPlayerMovement;

/// @brief Class for player management, movement, and rendering
class hPlayer
{
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
	cApp* app;
	std::string Name;

public: // Constructors & Destructor
	hPlayer();
	hPlayer(cApp* app);
	~hPlayer();

public: // Initializer & Clean-up
	bool SetupTarget(cApp* app);

private: // Reseter helpers
	void ResetDirection();
	void ResetAnimation();
	void ResetPosition();
	void ResetVelocity();

public: // Reseters
	void Reset();

private: // Checkers helpers
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

public: // Collision Detection
	bool IsPlatform() const;
	bool IsHit() const;
	bool IsBlocked() const;

private: // Validators
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
	void SetPlayerName(std::string Name);

public: // Movements
	bool PlayerMoveX(float fFactorX, int nStep = 16);
	bool PlayerMoveY(float fFactorX, int nStep = 16);
	bool PlayerMove(float fFactorX, float fFactorY, float fFactorScale = 1, int nStep = 16);
	bool PlayerMoveLeft(float factor = 1, bool forced = false);
	bool PlayerMoveRight(float factor = 1, bool forced = false);
	bool PlayerMoveUp(float factor = 1, bool forced = false);
	bool PlayerMoveDown(float factor = 1, bool forced = false);
	bool PlayerMoveTryAll(float factor = 1, bool forced = false);
	bool PlayerPlatformMoveX(float fFactorX, int nStep = 16);
	bool PlayerPlatformMoveY(float fFactorY, int nStep = 16);

public: // Movements
	bool PlayerPlatformDetector(int nStep = app_const::CELL_SIZE, float fFactor = 1.0f / app_const::CELL_SIZE);
	bool PlayerPlatformMove(float fFactorX, float fFactorY, float fFactorScale = 1, int nStep = 16);

private: // Validators & Fixers
	bool OnFixPlayerPosition();

private: // Logic Updater
	bool OnUpdatePlayerIdle();
	bool OnUpdatePlayerJumpStart();
	bool OnUpdatePlayerJumpContinue();
	bool OnUpdatePlayerJumpStop();

private: // Player Renderer 
	bool OnRenderPlayerIdle() const;
	bool OnRenderPlayerJumpStart() const;
	bool OnRenderPlayerJumpContinue() const;
	bool OnRenderPlayerJumpStop() const;

public: // Player Renderers
	bool OnRenderPlayer() const;
	bool OnRenderPlayerDeath();

public: // Logic-Render Control
	bool OnPlayerMove();
};

#endif // H_PLAYER_H