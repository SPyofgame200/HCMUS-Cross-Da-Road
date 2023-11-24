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
		IDLE = 0,			///< When the player doing nothing
		JUMP = 1,			///< When the player is moving, it jumps
		LAND = 2,			///< When the player stopped jumpings
		MOVE = 3,			///< [Unused] When the player can not jump, for example: sinksand
		SWIM = 4,			///< [Unused] When the player moving in a fluide environment like lakes
		TRAP = 5,			///< [Unused] When the player is locked in a position
	};
	/// @brief Situation enumeration for player interaction
	enum Situation
	{
		ALIVE = 0,	/// [TODO] When the player is fine
		DEATH = 1,	/// [TODO] When the player is killed
		WIN = 2,	/// [Unused] When the player passed a level
		LOSE = 3,	/// [Unused] When the player died all its life
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
	Situation eSituation;

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

private: // Reseter helpers
	void ResetDirection();
	void ResetAnimation();
	void ResetPosition();
	void ResetVelocity();

public: // Reseters
	void Reset();
	void SynchronizePosition(bool bAnimToLogic = true);

public: // Checkers helpers
	bool IsExactDirection(Direction eCompare) const;
	bool IsExactAnimation(Animation eCompare) const;
	bool IsExactSituation(Situation eCompare) const;
	bool IsLeftDirection() const;
	bool IsRightDirection() const;
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
	Direction GetDirection() const;
	Animation GetAnimation() const;
	Situation GetSituation() const;
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
	void SetAnimation(Situation eNewAnimation);
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