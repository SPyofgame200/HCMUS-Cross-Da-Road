#include "cPlayerStatus.h"

cPlayerStatus::cPlayerStatus()
{
	Reset();
}

void cPlayerStatus::Reset()
{
	eDirection = RIGHT;
	eAnimation = IDLE;
	eSituation = ALIVE;
}

/// @brief Check if player is facing exact direction
/// @param eCompare Direction to compare
/// @return True if player is facing exact direction, false otherwise
bool cPlayerStatus::IsExactDirection(Direction eCompare) const
{
	return eDirection == eCompare;
}

/// @brief Check if player is doing exact animation
/// @param eCompare Animation to compare
/// @return True if player is doing exact animation, false otherwise
bool cPlayerStatus::IsExactAnimation(Animation eCompare) const
{
	return eAnimation == eCompare;
}

/// @brief Check if player is doing exact animation
/// @param eCompare Animation to compare
/// @return True if player is doing exact animation, false otherwise
bool cPlayerStatus::IsExactSituation(Situation eCompare) const
{
	return eSituation == eCompare;
}

/// @brief Check if player is facing left direction
/// @return True if player is facing left direction, false otherwise
bool cPlayerStatus::IsLeftDirection() const
{
	return (eDirection == LEFT)
		|| (eDirection == LEFT_UP)
		|| (eDirection == LEFT_DOWN);
}
/// @brief Check if player is facing right direction
/// @return True if player is facing right direction, false otherwise
bool cPlayerStatus::IsRightDirection() const
{
	return (eDirection == RIGHT)
		|| (eDirection == RIGHT_UP)
		|| (eDirection == RIGHT_DOWN);
}

/// @brief Check if player is jumping
/// @return True if player is jumping, false otherwise
bool cPlayerStatus::IsJumpAnimation() const
{
	return (eAnimation == JUMP);
}

bool cPlayerStatus::IsIdleAnimation() const
{
	return (eAnimation == IDLE);
}

/// @brief Getter for current direction of player
cPlayerStatus::Direction cPlayerStatus::GetDirection() const
{
	return eDirection;
}
/// @brief Getter for current animation of player
cPlayerStatus::Animation cPlayerStatus::GetAnimation() const
{
	return eAnimation;
}

/// @brief Getter for current animation of player
cPlayerStatus::Situation cPlayerStatus::GetSituation() const
{
	return eSituation;
}

/// @brief Setter for current direction of player
/// @param eNewDirection New direction of player
void cPlayerStatus::SetDirection(Direction eNewDirection)
{
	eDirection = eNewDirection;
}
/// @brief Setter for current direction of player
/// @param eNewDirection New direction of player
void cPlayerStatus::SetAnimation(Animation eNewAnimation)
{
	eAnimation = eNewAnimation;
}
/// @brief Setter for current animation of player
/// @param eNewAnimation New animation of player
void cPlayerStatus::SetSituation(Situation eNewSituation)
{
	eSituation = eNewSituation;
}