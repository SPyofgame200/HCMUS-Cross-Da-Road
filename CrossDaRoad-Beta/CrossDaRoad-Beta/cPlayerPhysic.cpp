#include "cPlayerPhysic.h"
#include "uAppConst.h"
#include "uAppUtils.h"
#include <cmath>

cPlayerPhysic::cPlayerPhysic()
{
    Reset();
}

void cPlayerPhysic::Reset()
{
    fFrogAnimPosX = app_const::FROG_X_RESET;
    fFrogAnimPosY = app_const::FROG_Y_RESET;
    fFrogLogicPosX = app_const::FROG_X_RESET;
    fFrogLogicPosY = app_const::FROG_Y_RESET;
    fFrogVelocityX = app_const::FROG_X_VELOCITY;
    fFrogVelocityY = app_const::FROG_Y_VELOCITY;
}

/// @brief Check if player is out of bounds of map border
/// @return True if player is out of bounds, false otherwise
bool cPlayerPhysic::IsPlayerOutOfBounds() const
{
    if (fFrogLogicPosX < app_const::LEFT_BORDER) {
        return true;
    }
    if (fFrogLogicPosX > app_const::RIGHT_BORDER) {
        return true;
    }
    if (fFrogLogicPosY < app_const::TOP_BORDER) {
        return true;
    }
    if (fFrogLogicPosY > app_const::BOTTOM_BORDER) {
        return true;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// VALIDATORS ///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Check if player can move left
/// @return True if player can move left, false otherwise
bool cPlayerPhysic::CanMoveLeft() const
{
    return fFrogAnimPosX > app_const::LEFT_BORDER;
}
/// @brief Check if player can move right
/// @return True if player can move right, false otherwise
bool cPlayerPhysic::CanMoveRight() const
{
    return fFrogAnimPosX < app_const::RIGHT_BORDER;
}
/// @brief Check if player can move up
/// @return True if player can move up, false otherwise
bool cPlayerPhysic::CanMoveUp() const
{
    return fFrogAnimPosY > app_const::TOP_BORDER;
}
/// @brief Check if player can move down
/// @return True if player can move down, false otherwise
bool cPlayerPhysic::CanMoveDown() const
{
    return fFrogAnimPosY < app_const::BOTTOM_BORDER;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// GETTERS ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\

/// @brief Getter for animation position of player in X-axis
float cPlayerPhysic::GetPlayerAnimationPositionX() const
{
    return fFrogAnimPosX;
}
/// @brief Getter for animation position of player in Y-axis
float cPlayerPhysic::GetPlayerAnimationPositionY() const
{
    return fFrogAnimPosY;
}
/// @brief Getter for logic position of player in X-axis
float cPlayerPhysic::GetPlayerLogicPositionX() const
{
    return fFrogLogicPosX;
}
/// @brief Getter for logic position of player in Y-axis
float cPlayerPhysic::GetPlayerLogicPositionY() const
{
    return fFrogLogicPosY;
}
/// @brief Getter for velocity of player in X-axis
float cPlayerPhysic::GetPlayerVelocityX() const
{
    return fFrogVelocityX;
}
/// @brief Getter for velocity of player in Y-axis
float cPlayerPhysic::GetPlayerVelocityY() const
{
    return fFrogVelocityY;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// UTILITIES /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/// @brief Make the float [fValue] to only care about first [nDigits] digits after decimal points, others remain closest to ,...00000
float cPlayerPhysic::FixFloat(float fValue, int nDigits)
{
    return ldexpf(roundf(ldexpf(fValue, nDigits)), -nDigits);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// SETTERS ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Setter for animation position of player in X-axis
/// @param fVelocityX New animation position of player in X-axis
void cPlayerPhysic::SetVelocityX(float fVelocityX)
{
    fFrogVelocityX = FixFloat(fVelocityX);
}
/// @brief Setter for animation position of player in Y-axis
/// @param fVelocityY New animation position of player in Y-axis
void cPlayerPhysic::SetVelocityY(float fVelocityY)
{
    fFrogVelocityY = FixFloat(fVelocityY);
}
/// @brief Setter for velocity of player 
/// @param fVelocityX New velocity of player in X-axis
/// @param fVelocityY New velocity of player in Y-axis
void cPlayerPhysic::SetVelocity(float fVelocityX, float fVelocityY)
{
    SetVelocityX(fVelocityX);
    SetVelocityY(fVelocityY);
}
/// @brief Setter for animation position of player in X-axis
/// @param fPositionX New animation position of player in X-axis
void cPlayerPhysic::SetAnimationPositionX(float fPositionX)
{
    fFrogAnimPosX = FixFloat(fPositionX);
}
/// @brief Setter for animation position of player in Y-axis
/// @param fPositionY New animation position of player in Y-axis
void cPlayerPhysic::SetAnimationPositionY(float fPositionY)
{
    fFrogAnimPosY = FixFloat(fPositionY);
}
/// @brief Setter for animation position of player
/// @param fPositionX New animation position of player in X-axis
/// @param fPositionY New animation position of player in Y-axis
void cPlayerPhysic::SetAnimationPosition(float fPositionX, float fPositionY)
{
    SetAnimationPositionX(fPositionX);
    SetAnimationPositionY(fPositionY);
}
/// @brief Setter for logic position of player in X-axis
/// @param fPositionX New logic position of player in X-axis
void cPlayerPhysic::SetLogicPositionX(float fPositionX)
{
    fFrogLogicPosX = FixFloat(fPositionX);
}
/// @brief Setter for logic position of player in Y-axis
/// @param fPositionY Logic position of player in Y-axis
void cPlayerPhysic::SetLogicPositionY(float fPositionY)
{
    fFrogLogicPosY = FixFloat(fPositionY);
}
/// @brief Setter for logic position of player
/// @param fPositionX Logic position of player in X-axis
/// @param fPositionY Logic position of player in Y-axis
void cPlayerPhysic::SetLogicPosition(float fPositionX, float fPositionY)
{
    SetLogicPositionX(fPositionX);
    SetLogicPositionY(fPositionY);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// SYNCHRONIZER ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void cPlayerPhysic::SynchronizePosition(bool bAnimToLogic)
{
    if (bAnimToLogic) {
        float fAnimPosX = GetPlayerAnimationPositionX();
        float fAnimPosY = GetPlayerAnimationPositionY();
        SetLogicPosition(fAnimPosX, fAnimPosY);
    }
    else {
        float fLogicPosX = GetPlayerLogicPositionX();
        float fLogicPosY = GetPlayerLogicPositionY();
        SetAnimationPosition(fLogicPosX, fLogicPosY);
    }
}

/// @brief Fix player position
/// @return True if player position is fixed, false otherwise
bool cPlayerPhysic::OnFixPlayerPosition()
{
    const float fFixedX = utils::Clamp(FixFloat(GetPlayerAnimationPositionX(), 1), app_const::LEFT_BORDER, app_const::RIGHT_BORDER);
    const float fFixedY = utils::Clamp(FixFloat(GetPlayerAnimationPositionY(), 1), app_const::TOP_BORDER, app_const::BOTTOM_BORDER);
    SetAnimationPosition(fFixedX, fFixedY);
    return true;
}

// Implement Read and Write functions for cPlayerPhysic
void cPlayerPhysic::Read(std::istream& input) {
    // Read each property from the input stream
    input >> fFrogVelocityX >> fFrogVelocityY >> fFrogAnimPosX >> fFrogAnimPosY >> fFrogLogicPosX >> fFrogLogicPosY;
}

void cPlayerPhysic::Write(std::ostream& output) const {
    // Write each property to the output stream
    output << fFrogVelocityX << " "
        << fFrogVelocityY << " "
        << fFrogAnimPosX << " "
        << fFrogAnimPosY << " "
        << fFrogLogicPosX << " "
        << fFrogLogicPosY;
}

std::istream& operator>>(std::istream& input, cPlayerPhysic& playerPhysic) {
    playerPhysic.Read(input);
    return input;
}

std::ostream& operator<<(std::ostream& output, const cPlayerPhysic& playerPhysic) {
    playerPhysic.Write(output);
    return output;
}