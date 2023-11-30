#include "hPlayerHitbox.h"
#include "hPlayer.h"
#include "cZone.h"
#include <iostream>

//=================================================================================================
// Include new header files here

//=================================================================================================

hPlayerHitbox::hPlayerHitbox() : ptrPlayer(nullptr)
{

}

hPlayerHitbox::hPlayerHitbox(hPlayer* ptrPlayer) : ptrPlayer(nullptr)
{
    SetupTarget(ptrPlayer);
}

hPlayerHitbox::~hPlayerHitbox()
{
    ptrPlayer = nullptr;
    std::cerr << "hPlayerHitbox::~hPlayerHitbox(): Successfully destructed" << std::endl;
}

bool hPlayerHitbox::SetupTarget(hPlayer* ptrPlayer)
{
    if (!ptrPlayer) {
        return false;
    }
    this->ptrPlayer = ptrPlayer;
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// COLLISIONS DETECTION /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Check if player is hit by danger zone at top left corner
/// @return True if player is hit by danger zone at top left corner, false otherwise
bool hPlayerHitbox::IsHitTopLeft() const
{
    const float fPosX = ptrPlayer->Physic().GetPlayerLogicPositionX();
    const float fPosY = ptrPlayer->Physic().GetPlayerLogicPositionY();
    const bool isHitTopLeft = ptrPlayer->GetZone()->IsDangerTopLeft(fPosX, fPosY, app_const::CELL_SIZE);
    return isHitTopLeft;
}
/// @brief Check if player is hit by danger zone at top right corner
/// @return True if player is hit by danger zone at top right corner, false otherwise
bool hPlayerHitbox::IsHitTopRight() const
{
    const float fPosX = ptrPlayer->Physic().GetPlayerLogicPositionX();
    const float fPosY = ptrPlayer->Physic().GetPlayerLogicPositionY();
    const bool isHitTopRight = ptrPlayer->GetZone()->IsDangerTopRight(fPosX, fPosY, app_const::CELL_SIZE);
    return isHitTopRight;
}
/// @brief Check if player is hit by danger zone at bottom left corner
/// @return True if player is hit by danger zone at bottom left corner, false otherwise
bool hPlayerHitbox::IsHitBottomLeft() const
{
    const float fPosX = ptrPlayer->Physic().GetPlayerLogicPositionX();
    const float fPosY = ptrPlayer->Physic().GetPlayerLogicPositionY();
    const bool isHitBottomLeft = ptrPlayer->GetZone()->IsDangerBottomLeft(fPosX, fPosY, app_const::CELL_SIZE);
    return isHitBottomLeft;
}
/// @brief Check if player is hit by danger zone at bottom right corner
/// @return True if player is hit by danger zone at bottom right corner, false otherwise
bool hPlayerHitbox::IsHitBottomRight() const
{
    const float fPosX = ptrPlayer->Physic().GetPlayerLogicPositionX();
    const float fPosY = ptrPlayer->Physic().GetPlayerLogicPositionY();
    const bool isHitBottomRight = ptrPlayer->GetZone()->IsDangerBottomRight(fPosX, fPosY, app_const::CELL_SIZE);
    return isHitBottomRight;
}
/// @brief Check if player is hit by danger zone
/// @return True if player is hit by danger zone, false otherwise
bool hPlayerHitbox::IsHit() const
{
    return IsHitTopLeft()
        || IsHitTopRight()
        || IsHitBottomLeft()
        || IsHitBottomRight();
}
/// @brief Check if player is blocked by block zone at top left corner
/// @return True if player is blocked by block zone at top left corner, false otherwise
bool hPlayerHitbox::IsBlockedTopLeft() const
{
    const float fPosX = ptrPlayer->Physic().GetPlayerAnimationPositionX();
    const float fPosY = ptrPlayer->Physic().GetPlayerAnimationPositionY();
    const bool isBlockedTopLeft = ptrPlayer->GetZone()->IsBlockedTopLeft(fPosX, fPosY, app_const::CELL_SIZE);
    return isBlockedTopLeft;
}
/// @brief Check if player is blocked by block zone at top right corner
/// @return True if player is blocked by block zone at top right corner, false otherwise
bool hPlayerHitbox::IsBlockedTopRight() const
{
    const float fPosX = ptrPlayer->Physic().GetPlayerAnimationPositionX();
    const float fPosY = ptrPlayer->Physic().GetPlayerAnimationPositionY();
    const bool isBlockedTopRight = ptrPlayer->GetZone()->IsBlockedTopRight(fPosX, fPosY, app_const::CELL_SIZE);
    return isBlockedTopRight;
}
/// @brief Check if player is blocked by block zone at bottom left corner
/// @return True if player is blocked by block zone at bottom left corner, false otherwise
bool hPlayerHitbox::IsBlockedBottomLeft() const
{
    const float fPosX = ptrPlayer->Physic().GetPlayerAnimationPositionX();
    const float fPosY = ptrPlayer->Physic().GetPlayerAnimationPositionY();
    const bool isBlockedBottomLeft = ptrPlayer->GetZone()->IsBlockedBottomLeft(fPosX, fPosY, app_const::CELL_SIZE);
    return isBlockedBottomLeft;
}
/// @brief Check if player is blocked by block zone at bottom right corner
/// @return True if player is blocked by block zone at bottom right corner, false otherwise
bool hPlayerHitbox::IsBlockedBottomRight() const
{
    const float fPosX = ptrPlayer->Physic().GetPlayerAnimationPositionX();
    const float fPosY = ptrPlayer->Physic().GetPlayerAnimationPositionY();
    const bool isBlockedBottomRight = ptrPlayer->GetZone()->IsBlockedBottomRight(fPosX, fPosY, app_const::CELL_SIZE);
    return isBlockedBottomRight;
}
/// @brief Check if player is blocked by block zone
/// @return True if player is blocked by block zone, false otherwise
bool hPlayerHitbox::IsBlocked() const
{
    return IsBlockedTopLeft()
        || IsBlockedTopRight()
        || IsBlockedBottomLeft()
        || IsBlockedBottomRight();
}
/// @brief Check if player is on a platform at top left corner
/// @return True if player is on a platform at top left corner, false otherwise
bool hPlayerHitbox::IsOnPlatformTopLeft() const
{
    const float fPosX = ptrPlayer->Physic().GetPlayerAnimationPositionX();
    const float fPosY = ptrPlayer->Physic().GetPlayerAnimationPositionY();
    const bool isOnPlatformTopLeft = ptrPlayer->GetZone()->IsPlatformTopLeft(fPosX, fPosY, app_const::CELL_SIZE);
    return isOnPlatformTopLeft;
}

/// @brief Check if player is on a platform at top right corner
/// @return True if player is on a platform at top right corner, false otherwise
bool hPlayerHitbox::IsOnPlatformTopRight() const
{
    const float fPosX = ptrPlayer->Physic().GetPlayerAnimationPositionX();
    const float fPosY = ptrPlayer->Physic().GetPlayerAnimationPositionY();
    const bool isOnPlatformTopRight = ptrPlayer->GetZone()->IsPlatformTopRight(fPosX, fPosY, app_const::CELL_SIZE);
    return isOnPlatformTopRight;
}

/// @brief Check if player is on a platform at bottom left corner
/// @return True if player is on a platform at bottom left corner, false otherwise
bool hPlayerHitbox::IsOnPlatformBottomLeft() const
{
    const float fPosX = ptrPlayer->Physic().GetPlayerAnimationPositionX();
    const float fPosY = ptrPlayer->Physic().GetPlayerAnimationPositionY();
    const bool isOnPlatformBottomLeft = ptrPlayer->GetZone()->IsPlatformBottomLeft(fPosX, fPosY, app_const::CELL_SIZE);
    return isOnPlatformBottomLeft;
}

/// @brief Check if player is on a platform at bottom right corner
/// @return True if player is on a platform at bottom right corner, false otherwise
bool hPlayerHitbox::IsOnPlatformBottomRight() const
{
    const float fPosX = ptrPlayer->Physic().GetPlayerAnimationPositionX();
    const float fPosY = ptrPlayer->Physic().GetPlayerAnimationPositionY();
    const bool isOnPlatformBottomRight = ptrPlayer->GetZone()->IsPlatformBottomRight(fPosX, fPosY, app_const::CELL_SIZE);
    return isOnPlatformBottomRight;
}

/// @brief Check if player is on a platform
/// @return True if player is on a platform, false otherwise
bool hPlayerHitbox::IsOnPlatform() const
{
    return IsOnPlatformTopLeft()
        || IsOnPlatformTopRight()
        || IsOnPlatformBottomLeft()
        || IsOnPlatformBottomRight();
}