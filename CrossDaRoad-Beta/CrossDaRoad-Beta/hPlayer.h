#ifndef C_PLAYER_H
#define C_PLAYER_H

#include <string>
#include "cFrame.h"
#include "uAppConst.h"
class cApp;
class cZone;

/**
 * @file hPlayer.h
 *
 * @brief Contains player class
 *
 * This file contains player class for player management, movement, and rendering.
**/
class hPlayer
{
public:
	enum Direction
	{
		LEFT = 1,
		RIGHT = 2,
		LEFT_UP = 3,
		RIGHT_UP = 4,
		LEFT_DOWN = 5,
		RIGHT_DOWN = 6,
		FRONT_VIEW = 7, /// [unused], for front view
	};
	enum Animation
	{
		IDLE = 0,
		JUMP = 1,
		LAND = 2,
	};
	typedef int frame_t; // for later use

private:
	float fFrogVelocityX;
	float fFrogVelocityY;
	float fFrogAnimPosX;
	float fFrogAnimPosY;
	float fFrogLogicPosX;
	float fFrogLogicPosY;

private:
	frame4_t frame4;
	frame6_t frame6;
	frame8_t frame8;

	frame_t frame6_id_animation_safe;

private:
	Direction eDirection;
	Animation eAnimation;

private:
	cApp* app;

public: // Constructors & Destructor
	hPlayer();
	hPlayer(cApp* app);
	~hPlayer();

public: // Reseters
	void ResetDirection();
	void ResetAnimation();
	void ResetPosition();
	void ResetVelocity();
	void Reset();
	void SetupTarget(cApp* app);

public: // Checkers
	bool IsExactDirection(Direction eCompare) const;
	bool IsExactAnimation(Animation eCompare) const;
	bool IsLeftDirection() const;
	bool IsRightDirection() const;
	bool IsPlayerJumping() const;
	bool IsPlayerIdling() const;
	bool IsPlayerLanding() const;
	bool IsPlayerCollisionSafe() const;
	bool IsPlayerOutOfBounds() const;
	bool IsPlayerWin() const;

public: // Collision Detection
	bool IsHitTopLeft() const;
	bool IsHitTopRight() const;
	bool IsHitBottomLeft() const;
	bool IsHitBottomRight() const;
	bool IsHit() const;
	bool IsBlockedTopLeft() const;
	bool IsBlockedTopRight() const;
	bool IsBlockedBottomLeft() const;
	bool IsBlockedBottomRight() const;
	bool IsBlocked() const;

public: // Validators
	bool CanMoveLeft() const;
	bool CanMoveRight() const;
	bool CanMoveUp() const;
	bool CanMoveDown() const;

public: // Getters
	Direction GetDirection() const;
	Animation GetAnimation() const;
	int GetFrameID(frame_t frame) const;
	std::string ShowFrameID(frame_t frame) const;
	float GetPlayerAnimationPositionX() const;
	float GetPlayerAnimationPositionY() const;
	float GetPlayerLogicPositionX() const;
	float GetPlayerLogicPositionY() const;
	float GetPlayerVelocityX()const;
	float GetPlayerVelocityY()const;

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

public: // Movements
	bool PlayerMoveX(float fFactorX, int nStep = 16);
	bool PlayerMoveY(float fFactorX, int nStep = 16);
	bool PlayerMove(float fFactorX, float fFactorY, float fFactorScale = 1, int nStep = 16);
	bool PlayerMoveLeft(float factor = 1, bool forced = false);
	bool PlayerMoveRight(float factor = 1, bool forced = false);
	bool PlayerMoveUp(float factor = 1, bool forced = false);
	bool PlayerMoveDown(float factor = 1, bool forced = false);
	bool PlayerMoveTryAll(float factor = 1, bool forced = false);
	bool PlayerPlatformDetector(int nStep = app_const::CELL_SIZE, float fFactor = 1.0f / app_const::CELL_SIZE);
	bool PlayerPlatformMoveX(float fFactorX, int nStep = 16);
	bool PlayerPlatformMoveY(float fFactorY, int nStep = 16);
	bool PlayerPlatformMove(float fFactorX, float fFactorY, float fFactorScale = 1, int nStep = 16);

public: /// Validators & Fixers
	bool OnFixPlayerPosition();

public: // Logic Updater
	bool OnUpdatePlayerIdle();
	bool OnUpdatePlayerJumpStart();
	bool OnUpdatePlayerJumpContinue();
	bool OnUpdatePlayerJumpStop();

public: // Player Renderer
	bool OnRenderPlayerIdle() const;
	bool OnRenderPlayerJumpStart() const;
	bool OnRenderPlayerJumpContinue() const;
	bool OnRenderPlayerJumpStop() const;
	bool OnRenderPlayer() const;
	bool OnRenderPlayerDeath();

public: // Logic-Render Control
	bool OnPlayerMove();
	bool OnUpdateFrame(float fTickTime);
};

#endif // C_PLAYER_H