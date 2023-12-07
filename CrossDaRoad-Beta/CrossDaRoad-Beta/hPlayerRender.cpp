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

bool hPlayerRender::OnRenderPlayerIdle(bool bSwim) const
{
    OnRenderPlayer(bSwim);
    return true;
}

bool hPlayerRender::OnRenderPlayerJumpStart(bool bSwim) const
{
    OnRenderPlayer(bSwim);
    return true;
}

bool hPlayerRender::OnRenderPlayerJumpContinue(bool bSwim) const
{
    OnRenderPlayer(bSwim);
    return true;
}

bool hPlayerRender::OnRenderPlayerJumpStop(bool bSwim) const
{
    OnRenderPlayer(bSwim);
    return true;
}

/// @brief Render player animation to screen
/// @return Always true by default
bool hPlayerRender::OnRenderPlayer(bool bSwim) const
{
    const int nID = ptrPlayer->Moment().GetAnimationID();
    const bool bLeft = (ptrPlayer->Status().IsLeftDirection());
    const bool bMove = (ptrPlayer->Status().IsJumpAnimation());
    std::string sPlayerState;
    std::string sPlayerDirection;
    if (bSwim)
    {
        sPlayerState = std::string(bMove ? "_swim" : "_swim_idle");
        sPlayerDirection = std::string(bLeft ? "_left" : "");
    }
    else
    {
        sPlayerState = std::string(bMove ? "_jump" : "");
        sPlayerDirection = std::string(bLeft ? "_left" : "");
    }
    const std::string sPlayerAnimationID = (bMove ? std::to_string(nID) : "");
	const std::string sPlayerName = "froggy" + sPlayerState + sPlayerDirection + sPlayerAnimationID;
	ptrPlayer->Draw(sPlayerName);
    return true;
}

bool hPlayerRender::OnRender(bool bSwim) const
{
    if (ptrPlayer->Status().IsIdling()) {
        return OnRenderPlayerIdle(bSwim);
    }
    if (ptrPlayer->Status().IsStartJumping()) {
        return OnRenderPlayerJumpStart(bSwim);
    }
    if (!ptrPlayer->Moment().IsJumpingStop()) {
        return OnRenderPlayerJumpContinue(bSwim);
    }
    else { /// Jump completed
        return OnRenderPlayerJumpStop(bSwim);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// LOGIC-RENDER CONTROL /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
