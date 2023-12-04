#include "hPlayerUpdate.h"
#include "hPlayerMotion.h"
#include "hPlayer.h"

//=================================================================================================
// Include new header files here

//=================================================================================================

hPlayerUpdate::hPlayerUpdate() : ptrPlayer(nullptr)
{

}

hPlayerUpdate::hPlayerUpdate(hPlayer* ptrPlayer) : ptrPlayer(nullptr)
{
    SetupTarget(ptrPlayer);
}

hPlayerUpdate::~hPlayerUpdate()
{
    ptrPlayer = nullptr;
    std::cerr << "hPlayerUpdate::~hPlayerUpdate(): Successfully destructed" << std::endl;
}

bool hPlayerUpdate::SetupTarget(hPlayer* ptrPlayer)
{
    if (!ptrPlayer) {
        return false;
    }
    this->ptrPlayer = ptrPlayer;
    return true;
}

/// @brief Update animation when player idling
/// @return Always true by default
bool hPlayerUpdate::OnUpdatePlayerIdle()
{
    ptrPlayer->Physic().SynchronizePosition();
    return true;
}

/// @brief Update animation when player start jumping
/// @return True if player animation is updated, false otherwise
bool hPlayerUpdate::OnUpdatePlayerJumpStart()
{
    if (ptrPlayer->Status().IsMoveLeft()) {
        ptrPlayer->Status().SetAnimation(PlayerAnimation::JUMP);
        ptrPlayer->Status().SetDirection(PlayerDirection::LEFT);
    }
    else if (ptrPlayer->Status().IsMoveRight()) {
        ptrPlayer->Status().SetAnimation(PlayerAnimation::JUMP);
        ptrPlayer->Status().SetDirection(PlayerDirection::RIGHT);
    }
    else if (ptrPlayer->Status().IsMoveUp()) {
        ptrPlayer->Status().SetAnimation(PlayerAnimation::JUMP);
        if (ptrPlayer->Status().IsLeftDirection()) {
            ptrPlayer->Status().SetDirection(PlayerDirection::LEFT_UP);
        }
        else {
            ptrPlayer->Status().SetDirection(PlayerDirection::RIGHT_UP);
        }
    }
    else if (ptrPlayer->Status().IsMoveDown()) {
        ptrPlayer->Status().SetAnimation(PlayerAnimation::JUMP);
        if (ptrPlayer->Status().IsLeftDirection()) {
            ptrPlayer->Status().SetDirection(PlayerDirection::LEFT_DOWN);
        }
        else {
            ptrPlayer->Status().SetDirection(PlayerDirection::RIGHT_DOWN);
        }
    }
    ptrPlayer->Physic().SynchronizePosition();
    return ptrPlayer->Moment().StartAnimation();
}
/// @brief Update animation when player continue jumping
/// @return True if player animation is updated, false otherwise
bool hPlayerUpdate::OnUpdatePlayerJumpContinue() const
{
    if (ptrPlayer->Status().GetAnimation() == PlayerAnimation::IDLE) {
        return false;
    }
    if (ptrPlayer->Moment().NextAnimation()) {
	    const float fSpeed = 1.0f / ptrPlayer->Moment().FrameLimit();
        if (ptrPlayer->Status().IsDirection(PlayerDirection::LEFT)) {
            if (!ptrPlayer->Motion().MoveLeft(fSpeed, true)) {
                return false;
            }
        }
        else if (ptrPlayer->Status().IsDirection(PlayerDirection::RIGHT)) {
            if (!ptrPlayer->Motion().MoveRight(fSpeed, true)) {
                return false;
            }
        }
        else if (ptrPlayer->Status().IsDirection({ PlayerDirection::LEFT_UP, PlayerDirection::RIGHT_UP })) {
            if (!ptrPlayer->Motion().MoveUp(fSpeed, true)) {
                return false;
            }
        }
        else if (ptrPlayer->Status().IsDirection({ PlayerDirection::LEFT_DOWN, PlayerDirection::RIGHT_DOWN })) {
            if (!ptrPlayer->Motion().MoveDown(fSpeed, true)) {
                return false;
            }
        }
    }
    return true;
}

/// @brief Update animation when player stop jumping
/// @return True if player animation is updated, false otherwise
bool hPlayerUpdate::OnUpdatePlayerJumpStop()
{
    ptrPlayer->Physic().OnFixPlayerPosition();
    ptrPlayer->Physic().SynchronizePosition();
    if (ptrPlayer->Status().IsAnimation(PlayerAnimation::JUMP)) {
        ptrPlayer->Status().SetAnimation(PlayerAnimation::IDLE);
        return true;
    }
    return false;
}

bool hPlayerUpdate::OnUpdate()
{
    if (ptrPlayer->Status().IsIdling()) {
        return OnUpdatePlayerIdle();
    }
    if (ptrPlayer->Status().IsStartJumping()) {
        return OnUpdatePlayerJumpStart();
    }
    if (!ptrPlayer->Moment().IsJumpingStop()) {
        return OnUpdatePlayerJumpContinue();
    }
    else { /// Jump completed
        return OnUpdatePlayerJumpStop();
    }
}
