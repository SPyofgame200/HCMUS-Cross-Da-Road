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
    eIntention = NONE;

    nDirectionFlag = EMPTY_FLAG;
    nAnimationFlag = EMPTY_FLAG;
    nSituationFlag = EMPTY_FLAG;
    nIntentionFlag = EMPTY_FLAG;
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

/// @brief Check if player is doing exact animation
/// @param eCompare Animation to compare
/// @return True if player is doing exact animation, false otherwise
bool cPlayerStatus::IsExactIntention(Intention eCompare) const
{
    return eIntention == eCompare;
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

/// @brief Getter for current animation of player
cPlayerStatus::Intention cPlayerStatus::GetIntention() const
{
    return eIntention;
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
void cPlayerStatus::SetIntention(Intention eNewIntention)
{
    eIntention = eNewIntention;
}

template<typename EnumType>
int cPlayerStatus::Value(EnumType eValue) const
{
    return 1 << static_cast<int>(eValue);
}

template<typename EnumType>
typename cPlayerStatus::flag_t& cPlayerStatus::Flag(EnumType ePlaceHolder)
{
    static_assert(sizeof(EnumType) == 0, "Flag function not specialized for this enum type");
}

template<>
cPlayerStatus::flag_t& cPlayerStatus::Flag<PlayerDirection>(PlayerDirection ePlaceHolder)
{
    return nDirectionFlag;
}

template<>
cPlayerStatus::flag_t& cPlayerStatus::Flag<PlayerAnimation>(PlayerAnimation ePlaceHolder)
{
    return nAnimationFlag;
}

template<>
cPlayerStatus::flag_t& cPlayerStatus::Flag<PlayerSituation>(PlayerSituation ePlaceHolder)
{
    return nSituationFlag;
}

template<>
cPlayerStatus::flag_t& cPlayerStatus::Flag<PlayerIntention>(PlayerIntention ePlaceHolder)
{
    return nIntentionFlag;
}

template<typename EnumType>
void cPlayerStatus::Modify(EnumType eValue, bool bValue)
{
    Flag(eValue) ^= (-bValue ^ nIntentionFlag) & Value<EnumType>(eValue);
}

template<typename EnumType>
void cPlayerStatus::Insert(EnumType eValue)
{
    Flag(eValue) |= Value(eValue);
}

template<typename EnumType>
void cPlayerStatus::Remove(EnumType eValue)
{
    Flag(eValue) &= ~Value(eValue);
}

template<typename EnumType>
void cPlayerStatus::Toggle(EnumType eValue)
{
    Flag(eValue) ^= Value(eValue);
}

template<typename EnumType>
void cPlayerStatus::Modify(std::initializer_list<EnumType> eList, bool bValue)
{
    for (EnumType eValue : eList) {
        Modify(eValue, bValue);
    }
}

template<typename EnumType>
void cPlayerStatus::Insert(std::initializer_list<EnumType> eList)
{
    for (EnumType eValue : eList) {
        Insert(eValue);
    }
}

template<typename EnumType>
void cPlayerStatus::Remove(std::initializer_list<EnumType> eList)
{
    for (EnumType eValue : eList) {
        Remove(eValue);
    }
}

template<typename EnumType>
void cPlayerStatus::Toggle(std::initializer_list<EnumType> eList)
{
    for (EnumType eValue : eList) {
        Toggle(eValue);
    }
}

bool cPlayerStatus::IsMove() const
{
    return nIntentionFlag != NONE;
}

template<typename EnumType>
bool cPlayerStatus::IsMove(EnumType eValue) const
{
    return (nIntentionFlag & Value(eValue)) != 0;
}

template<typename EnumType>
bool cPlayerStatus::IsMove(std::initializer_list<EnumType> eList) const
{
    for (EnumType eValue : eList) {
        if (IsMove(eValue)) {
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

bool cPlayerStatus::IsPlayerStartingJump() const
{
    return (IsIdleAnimation()) && (IsMove());
}
/// @brief Check if player is idling
/// @return True if player is idling, false otherwise
bool cPlayerStatus::IsPlayerIdling() const
{
    return (IsIdleAnimation()) && !(IsMove());
}