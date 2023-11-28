#include "cPlayerStatus.h"

#define EXPLICIT_INSTANTIATION(Type) \
    template cPlayerStatus::flag_t cPlayerStatus::Value<Type>(Type eValue) const; \
    template void cPlayerStatus::Modify<Type>(Type eValue, bool bValue); \
    template void cPlayerStatus::Insert<Type>(Type eValue); \
    template void cPlayerStatus::Remove<Type>(Type eValue); \
    template void cPlayerStatus::Toggle<Type>(Type eValue); \
    template void cPlayerStatus::Modify<Type>(std::initializer_list<Type> eList, bool bValue); \
    template void cPlayerStatus::Insert<Type>(std::initializer_list<Type> eList); \
    template void cPlayerStatus::Remove<Type>(std::initializer_list<Type> eList); \
    template void cPlayerStatus::Toggle<Type>(std::initializer_list<Type> eList); \

EXPLICIT_INSTANTIATION(PlayerDirection)
EXPLICIT_INSTANTIATION(PlayerAnimation)
EXPLICIT_INSTANTIATION(PlayerSituation)
EXPLICIT_INSTANTIATION(PlayerIntention)

#undef EXPLICIT_INSTANTIATION

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
bool cPlayerStatus::IsDirection(Direction eCompare) const
{
    return eDirection == eCompare;
}

/// @brief Check if player is doing exact animation
/// @param eCompare Animation to compare
/// @return True if player is doing exact animation, false otherwise
bool cPlayerStatus::IsAnimation(Animation eCompare) const
{
    return eAnimation == eCompare;
}

/// @brief Check if player is doing exact animation
/// @param eCompare Animation to compare
/// @return True if player is doing exact animation, false otherwise
bool cPlayerStatus::IsSituation(Situation eCompare) const
{
    return eSituation == eCompare;
}

/// @brief Check if player is doing exact animation
/// @param eCompare Animation to compare
/// @return True if player is doing exact animation, false otherwise
bool cPlayerStatus::IsIntention(Intention eCompare) const
{
    return eIntention == eCompare;
}

bool cPlayerStatus::IsDirection(std::initializer_list<Direction> eCompareList) const
{
    for (const Direction eCompare : eCompareList) {
        if (IsDirection(eCompare)) {
            return true;
        }
    }
    return false;
}

bool cPlayerStatus::IsAnimation(std::initializer_list<Animation> eCompareList) const
{
    for (const Animation eCompare : eCompareList) {
        if (IsAnimation(eCompare)) {
            return true;
        }
    }
    return false;
}

bool cPlayerStatus::IsSituation(std::initializer_list<Situation> eCompareList) const
{
    for (const Situation eCompare : eCompareList) {
        if (IsSituation(eCompare)) {
            return true;
        }
    }
    return false;
}

bool cPlayerStatus::IsIntention(std::initializer_list<Intention> eCompareList) const
{
    for (const Intention eCompare : eCompareList) {
        if (IsIntention(eCompare)) {
            return true;
        }
    }
    return false;
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
cPlayerStatus::flag_t cPlayerStatus::Value(EnumType eValue) const
{
    return 1 << static_cast<int>(eValue);
}

template<typename EnumType>
cPlayerStatus::flag_t& cPlayerStatus::Flag()
{
    static_assert(sizeof(EnumType) == 0, "Flag function not specialized for this enum type");
}

template<>
cPlayerStatus::flag_t& cPlayerStatus::Flag<PlayerDirection>()
{
    return nDirectionFlag;
}

template<>
cPlayerStatus::flag_t& cPlayerStatus::Flag<PlayerAnimation>()
{
    return nAnimationFlag;
}

template<>
cPlayerStatus::flag_t& cPlayerStatus::Flag<PlayerSituation>()
{
    return nSituationFlag;
}

template<>
cPlayerStatus::flag_t& cPlayerStatus::Flag<PlayerIntention>()
{
    return nIntentionFlag;
}

template<typename EnumType>
void cPlayerStatus::Modify(EnumType eValue, bool bValue)
{
    Flag<EnumType>() ^= (-static_cast<int>(bValue) ^ nIntentionFlag) & Value<EnumType>(eValue);
}

template<typename EnumType>
void cPlayerStatus::Insert(EnumType eValue)
{
    Flag<EnumType>() |= Value(eValue);
}

template<typename EnumType>
void cPlayerStatus::Remove(EnumType eValue)
{
    Flag<EnumType>() &= ~Value(eValue);
}

template<typename EnumType>
void cPlayerStatus::Toggle(EnumType eValue)
{
    Flag<EnumType>() ^= Value(eValue);
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

bool cPlayerStatus::IsMove() const
{
    return nIntentionFlag != NONE;
}

bool cPlayerStatus::IsMove(Intention eValue) const
{
    return (nIntentionFlag & Value(eValue)) != 0;
}

bool cPlayerStatus::IsMove(std::initializer_list<Intention> eList) const
{
    for (const Intention eValue : eList) {
        if (IsMove(eValue)) {
            return true;
        }
    }
    return false;
}

bool cPlayerStatus::IsStartJumping() const
{
    return (IsIdleAnimation()) && (IsMove());
}
/// @brief Check if player is idling
/// @return True if player is idling, false otherwise
bool cPlayerStatus::IsIdling() const
{
    return (IsIdleAnimation()) && !(IsMove());
}

bool cPlayerStatus::IsDeath() const
{
    return (eSituation == DEATH);
}

void cPlayerStatus::Read(std::istream& is) {
    // Read each property from the input stream
    int direction, animation, situation, intention;
    is >> direction >> animation >> situation >> intention;

    // Set the values read from the stream
    eDirection = static_cast<Direction>(direction);
    eAnimation = static_cast<Animation>(animation);
    eSituation = static_cast<Situation>(situation);
    eIntention = static_cast<Intention>(intention);
}

void cPlayerStatus::Write(std::ostream& os) const {
    // Write each property to the output stream
    os  << static_cast<int>(eDirection) << " "
        << static_cast<int>(eAnimation) << " "
        << static_cast<int>(eSituation) << " "
        << static_cast<int>(eIntention);
}

std::istream& operator>>(std::istream& is, cPlayerStatus& playerStatus) {
    playerStatus.Read(is);
    return is;
}

std::ostream& operator<<(std::ostream& os, const cPlayerStatus& playerStatus) {
    playerStatus.Write(os);
    return os;
}