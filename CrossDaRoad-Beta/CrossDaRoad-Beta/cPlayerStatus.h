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

public: /// @brief Using a flag_t
	using flag_t = unsigned int;

private: /// Single Status
	Direction eDirection;
	Animation eAnimation;
	Situation eSituation;
	Intention eIntention; // [Unused]

private: /// Chained Status
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
	template<typename EnumType>
	int Value(EnumType eValue) const;

	template<typename EnumType>
	flag_t& Flag(EnumType ePlaceHolder);

public: /// Single Intention
	template<typename EnumType>
	void Modify(EnumType eValue, bool bValue);
	template<typename EnumType>
	void Insert(EnumType eValue);
	template<typename EnumType>
	void Remove(EnumType eValue);
	template<typename EnumType>
	void Toggle(EnumType eValue);

public: /// Chained Intentions
	template<typename EnumType>
	void Modify(std::initializer_list<EnumType> eList, bool bValue);
	template<typename EnumType>
	void Insert(std::initializer_list<EnumType> eList);
	template<typename EnumType>
	void Remove(std::initializer_list<EnumType> eList);
	template<typename EnumType>
	void Toggle(std::initializer_list<EnumType> eList);

public: /// Checkers
	bool IsMove() const;
	template<typename EnumType>
	bool IsMove(EnumType) const;
	template<typename EnumType>
	bool IsMove(std::initializer_list<EnumType> eList) const;

public: /// Motion
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

// Explicit instantiation
template int cPlayerStatus::Value<PlayerDirection>(PlayerDirection eValue) const;
template int cPlayerStatus::Value<PlayerAnimation>(PlayerAnimation eValue) const;
template int cPlayerStatus::Value<PlayerSituation>(PlayerSituation eValue) const;
template int cPlayerStatus::Value<PlayerIntention>(PlayerIntention eValue) const;

template void cPlayerStatus::Modify<PlayerIntention>(PlayerIntention eValue, bool bValue);
template void cPlayerStatus::Modify<PlayerDirection>(PlayerDirection eValue, bool bValue);
template void cPlayerStatus::Modify<PlayerAnimation>(PlayerAnimation eValue, bool bValue);
template void cPlayerStatus::Modify<PlayerSituation>(PlayerSituation eValue, bool bValue);

template void cPlayerStatus::Insert<PlayerIntention>(PlayerIntention eValue);
template void cPlayerStatus::Insert<PlayerDirection>(PlayerDirection eValue);
template void cPlayerStatus::Insert<PlayerAnimation>(PlayerAnimation eValue);
template void cPlayerStatus::Insert<PlayerSituation>(PlayerSituation eValue);

template void cPlayerStatus::Remove<PlayerIntention>(PlayerIntention eValue);
template void cPlayerStatus::Remove<PlayerDirection>(PlayerDirection eValue);
template void cPlayerStatus::Remove<PlayerAnimation>(PlayerAnimation eValue);
template void cPlayerStatus::Remove<PlayerSituation>(PlayerSituation eValue);

template void cPlayerStatus::Toggle<PlayerIntention>(PlayerIntention eValue);
template void cPlayerStatus::Toggle<PlayerDirection>(PlayerDirection eValue);
template void cPlayerStatus::Toggle<PlayerAnimation>(PlayerAnimation eValue);
template void cPlayerStatus::Toggle<PlayerSituation>(PlayerSituation eValue);

template bool cPlayerStatus::IsMove<PlayerDirection>(PlayerDirection eValue) const;
template bool cPlayerStatus::IsMove<PlayerAnimation>(PlayerAnimation eValue) const;
template bool cPlayerStatus::IsMove<PlayerSituation>(PlayerSituation eValue) const;
template bool cPlayerStatus::IsMove<PlayerIntention>(PlayerIntention eValue) const;

template void cPlayerStatus::Modify<PlayerDirection>(std::initializer_list<PlayerDirection> eList, bool bValue);
template void cPlayerStatus::Modify<PlayerAnimation>(std::initializer_list<PlayerAnimation> eList, bool bValue);
template void cPlayerStatus::Modify<PlayerSituation>(std::initializer_list<PlayerSituation> eList, bool bValue);
template void cPlayerStatus::Modify<PlayerIntention>(std::initializer_list<PlayerIntention> eList, bool bValue);

template void cPlayerStatus::Insert<PlayerDirection>(std::initializer_list<PlayerDirection> eList);
template void cPlayerStatus::Insert<PlayerAnimation>(std::initializer_list<PlayerAnimation> eList);
template void cPlayerStatus::Insert<PlayerSituation>(std::initializer_list<PlayerSituation> eList);
template void cPlayerStatus::Insert<PlayerIntention>(std::initializer_list<PlayerIntention> eList);

template void cPlayerStatus::Remove<PlayerDirection>(std::initializer_list<PlayerDirection> eList);
template void cPlayerStatus::Remove<PlayerAnimation>(std::initializer_list<PlayerAnimation> eList);
template void cPlayerStatus::Remove<PlayerSituation>(std::initializer_list<PlayerSituation> eList);
template void cPlayerStatus::Remove<PlayerIntention>(std::initializer_list<PlayerIntention> eList);

template void cPlayerStatus::Toggle<PlayerDirection>(std::initializer_list<PlayerDirection> eList);
template void cPlayerStatus::Toggle<PlayerAnimation>(std::initializer_list<PlayerAnimation> eList);
template void cPlayerStatus::Toggle<PlayerSituation>(std::initializer_list<PlayerSituation> eList);
template void cPlayerStatus::Toggle<PlayerIntention>(std::initializer_list<PlayerIntention> eList);

template bool cPlayerStatus::IsMove<PlayerDirection>(std::initializer_list<PlayerDirection> eList) const;
template bool cPlayerStatus::IsMove<PlayerAnimation>(std::initializer_list<PlayerAnimation> eList) const;
template bool cPlayerStatus::IsMove<PlayerSituation>(std::initializer_list<PlayerSituation> eList) const;
template bool cPlayerStatus::IsMove<PlayerIntention>(std::initializer_list<PlayerIntention> eList) const;

#endif C_PLAYER_STATUS_H