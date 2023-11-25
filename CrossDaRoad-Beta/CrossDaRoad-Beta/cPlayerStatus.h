/**
 * @file cApp.cpp
 * @brief Contain player states and flags
 *
**/

#ifndef C_PLAYER_STATUS_H
#define C_PLAYER_STATUS_H

#include <initializer_list>

class cPlayerStatus
{
public:
	static const int EMPTY_FLAG = 0;

public: /// @brief Direction enumeration for player movement
	enum Direction
	{
		LEFT = 1,			///< Left direction for player movement
		RIGHT = 2, 			///< Right direction for player movement
		LEFT_UP = 3, 		///< Left-up direction for player movement
		RIGHT_UP = 4, 		///< Right-up direction for player movement
		LEFT_DOWN = 5, 		///< Left-down direction for player movement
		RIGHT_DOWN = 6, 	///< Right-down direction for player movement
	};

public: /// @brief Animation enumeration for player animation
	enum Animation
	{
		IDLE = 1,			///< When the player doing nothing
		JUMP = 2,			///< When the player is moving, it jumps
		LAND = 3,			///< When the player stopped jumpings
		MOVE = 4,			///< [Unused] When the player can not jump, for example: sinksand
		SWIM = 5,			///< [Unused] When the player moving in a fluide environment like lakes
		TRAP = 6,			///< [Unused] When the player is locked in a position
	};

public: /// @brief Situation enumeration for player interaction
	enum Situation
	{
		ALIVE = 1,	/// [TODO] When the player is fine
		DEATH = 2,	/// [TODO] When the player is killed
		WIN = 3,	/// [Unused] When the player passed a level
		LOSE = 4,	/// [Unused] When the player died all its life
	};

public: /// @brief Intention flags for player actions
	enum Intention
	{
		NONE = 0,
		GO_LEFT = 1,
		GO_RIGHT = 2,
		GO_UP = 3,
		GO_DOWN = 4,
	};

private: /// Single Status
	Direction eDirection;
	Animation eAnimation;
	Situation eSituation;
	Intention eIntention; // [Unused]

private: /// Chained Status
	using flag_t = int;
	flag_t nDirectionFlag; // [Unused]
	flag_t nAnimationFlag; // [Unused]
	flag_t nSituationFlag; // [Unused]
	flag_t nIntentionFlag;
	
public: /// Constructors & Destructor
	cPlayerStatus();

public: /// Initializer & Clean-up
	void Reset();

public: /// Checkers
	bool IsExactDirection(Direction eCompare) const;
	bool IsExactAnimation(Animation eCompare) const;
	bool IsExactSituation(Situation eCompare) const;
	bool IsExactIntention(Intention eCompare) const;
	bool IsLeftDirection() const;
	bool IsRightDirection() const;
	bool IsJumpAnimation() const;
	bool IsIdleAnimation() const;

public: /// Getters
	Direction GetDirection() const;
	Animation GetAnimation() const;
	Situation GetSituation() const;
	Intention GetIntention() const;

public: // Setters
	void SetDirection(Direction eNewDirection);
	void SetAnimation(Animation eNewAnimation);
	void SetSituation(Situation eNewSituation);
	void SetIntention(Intention eNewIntention);

private: /// Utilities
	int Value(Intention eIntention) const;

public: /// Single Intention
	void Modify(Intention eIntention, bool bValue);
	void Insert(Intention eIntention);
	void Remove(Intention eIntention);
	void Toggle(Intention eIntention);

public: /// Chained Intentions
	void Modify(std::initializer_list<Intention> eIntentionList, bool bValue);
	void Insert(std::initializer_list<Intention> eIntentionList);
	void Remove(std::initializer_list<Intention> eIntentionList);
	void Toggle(std::initializer_list<Intention> eIntentionList);

public: /// Checkers
	bool IsMove() const;
	bool IsMove(Intention) const;
	bool IsMove(std::initializer_list<Intention> eIntention) const;
	bool IsMoveLeft() const;
	bool IsMoveRight() const;
	bool IsMoveUp() const;
	bool IsMoveDown() const;

public: /// Animation
	bool IsPlayerStartingJump() const;
	bool IsPlayerIdling() const;
};

using PlayerDirection = cPlayerStatus::Direction;
using PlayerAnimation = cPlayerStatus::Animation;
using PlayerSituation = cPlayerStatus::Situation;
using PlayerIntention = cPlayerStatus::Intention;

#endif C_PLAYER_STATUS_H