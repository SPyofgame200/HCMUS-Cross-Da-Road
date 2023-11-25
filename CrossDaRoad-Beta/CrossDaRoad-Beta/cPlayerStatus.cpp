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
    nIntentionFlag = NONE;
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

void cPlayerStatus::Modify(Intention status, bool bValue)
{
    return (bValue == true) ? Insert(status) : Remove(status);
}

void cPlayerStatus::Insert(Intention status)
{
    nIntentionFlag |= static_cast<int>(status);
}

void cPlayerStatus::Remove(Intention status)
{
    nIntentionFlag &= ~static_cast<int>(status);
}

void cPlayerStatus::Toggle(Intention status)
{
    nIntentionFlag ^= static_cast<int>(status);
}

void cPlayerStatus::Modify(std::initializer_list<Intention> actions, bool bValue)
{
    for (Intention status : actions) {
        Modify(status, bValue);
    }
}

void cPlayerStatus::Insert(std::initializer_list<Intention> actions)
{
    for (Intention status : actions) {
        Insert(status);
    }
}

void cPlayerStatus::Remove(std::initializer_list<Intention> actions)
{
    for (Intention status : actions) {
        Remove(status);
    }
}

void cPlayerStatus::Toggle(std::initializer_list<Intention> actions)
{
    for (Intention status : actions) {
        Toggle(status);
    }
}

bool cPlayerStatus::IsMove() const
{
    return nIntentionFlag != NONE;
}

bool cPlayerStatus::IsMove(Intention status) const
{
    return (nIntentionFlag & static_cast<int>(status)) != 0;
}

bool cPlayerStatus::IsMove(std::initializer_list<Intention> actions) const
{
    for (Intention status : actions) {
        if (IsMove(status)) {
            return true;
        }
    }
    return false;
}

bool cPlayerStatus::IsMoveLeft() const
{
    return IsMove(GO_LEFT);
}
bool cPlayerStatus::IsMoveRight() const
{
    return IsMove(GO_RIGHT);
}
bool cPlayerStatus::IsMoveUp() const
{
    return IsMove(GO_UP);
}
bool cPlayerStatus::IsMoveDown() const
{
    return IsMove(GO_DOWN);
}