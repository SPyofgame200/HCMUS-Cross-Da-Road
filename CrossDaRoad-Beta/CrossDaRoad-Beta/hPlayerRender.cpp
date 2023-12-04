#include "hPlayerRender.h"
#include "cAssetManager.h"
#include "hPlayer.h"

//=================================================================================================
// Include new header files here

//=================================================================================================

hPlayerRender::hPlayerRender() : ptrPlayer(nullptr)
{

}

hPlayerRender::hPlayerRender(hPlayer* ptrPlayer) : ptrPlayer(nullptr)
{
    SetupTarget(ptrPlayer);
}

hPlayerRender::~hPlayerRender()
{
    ptrPlayer = nullptr;
    std::cerr << "hPlayerRender::~hPlayerRender(): Successfully destructed" << std::endl;
}

bool hPlayerRender::SetupTarget(hPlayer* ptrPlayer)
{
    if (!ptrPlayer) {
        return false;
    }
    this->ptrPlayer = ptrPlayer;
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// PLAYER RENDERER ///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool hPlayerRender::OnRenderPlayerIdle() const
{
    OnRenderPlayer();
    return true;
}

bool hPlayerRender::OnRenderPlayerJumpStart() const
{
    OnRenderPlayer();
    return true;
}

bool hPlayerRender::OnRenderPlayerJumpContinue() const
{
    OnRenderPlayer();
    return true;
}

bool hPlayerRender::OnRenderPlayerJumpStop() const
{
    OnRenderPlayer();
    return true;
}

/// @brief Render player animation to screen
/// @return Always true by default
bool hPlayerRender::OnRenderPlayer() const
{
    const int nID = ptrPlayer->Moment().GetAnimationID();
    const bool isLeft = (ptrPlayer->Status().IsLeftDirection());
    const bool isJump = (ptrPlayer->Status().IsJumpAnimation());
    const std::string sPlayerState = std::string(isJump ? "_jump" : "");
    const std::string sPlayerDirection = std::string(isLeft ? "_left" : "");
    const std::string sPlayerID = (isJump ? std::to_string(nID) : "");
    const std::string sPlayerName = "froggy" + sPlayerState + sPlayerDirection + sPlayerID;
    ptrPlayer->Draw(sPlayerName);
    return true;
}

bool hPlayerRender::OnRender()
{
    if (ptrPlayer->Status().IsIdling()) {
        return OnRenderPlayerIdle();
    }
    if (ptrPlayer->Status().IsStartJumping()) {
        return OnRenderPlayerJumpStart();
    }
    if (!ptrPlayer->Moment().IsJumpingStop()) {
        return OnRenderPlayerJumpContinue();
    }
    else { /// Jump completed
        return OnRenderPlayerJumpStop();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// LOGIC-RENDER CONTROL /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
