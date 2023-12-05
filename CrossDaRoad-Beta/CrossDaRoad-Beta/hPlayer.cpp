/**
 * @file hPlayer.cpp
 *
 * @brief Contains player class implementation
 *
 * This file implements player class for player management, movement, and rendering.
**/

#include "hPlayer.h"
// Dependencies
#include "cFrameManager.h"
#include "cApp.h"
// Component
#include "hPlayerMotion.h"
#include "hPlayerRender.h"
#include "hPlayerHitbox.h"
#include "hPlayerUpdate.h"

//=================================================================================================
// Include new header files here

//=================================================================================================

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// COMPONENT HANDLER ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

cApp* hPlayer::ptrApp = nullptr;
hPlayerMotion hPlayer::hMotion;
hPlayerRender hPlayer::hRender;
hPlayerHitbox hPlayer::hHitbox;
hPlayerUpdate hPlayer::hUpdate;

hPlayerMotion& hPlayer::Motion()
{
    return hMotion;
}

hPlayerRender& hPlayer::Render()
{
    return hRender;
}

hPlayerHitbox& hPlayer::Hitbox()
{
    return hHitbox;
}

hPlayerUpdate& hPlayer::Update()
{
    return hUpdate;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// DATA MANAGEMENT ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


cPlayerStatus& hPlayer::Status()
{
    return cStatus;
}

cPlayerPhysic& hPlayer::Physic()
{
    return cPhysic;
}

cPlayerRecord& hPlayer::Record()
{
    return cRecord;
}

cPlayerMoment& hPlayer::Moment()
{
    return cMoment;
}

const cPlayerStatus& hPlayer::Status() const
{
    return cStatus;
}

const cPlayerPhysic& hPlayer::Physic() const
{
    return cPhysic;
}

const cPlayerRecord& hPlayer::Record() const
{
    return cRecord;
}

const cPlayerMoment& hPlayer::Moment() const
{
    return cMoment;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// CONSTRUCTORS & DESTRUCTOR ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Default constructor
hPlayer::hPlayer()
{
    SetupComponents();
    Reset();
}

/// @brief Constructor with ptrApp pointer
hPlayer::hPlayer(cApp* ptrApp)
{
    SetupComponents();
    SetupTarget(ptrApp);
    Reset();
}

/// @brief Destructor
hPlayer::~hPlayer()
{
    // No, we are not deleting anything, cApp* ptrApp is controlled by cApp
    ptrApp = nullptr;
    std::cerr << "hPlayer::~hPlayer(): Successfully destructed" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// RESETTERS /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Reset player properties
void hPlayer::Reset()
{
    cStatus.Reset();
    cPhysic.Reset();
    cRecord.Reset();
    cMoment.Reset();
}

/// @brief Setup ptrApp pointer
/// @param ptrApp Pointer to ptrApp
bool hPlayer::SetupTarget(cApp* ptrApp)
{
    if (!ptrApp) {
        return false;
    }
    this->ptrApp = ptrApp;
    return true;
}

bool hPlayer::SetupComponents()
{
    if (!hHitbox.SetupTarget(this)) {
        std::cerr << "hPlayer::SetupComponent(): Failed to setup hitbox component" << std::endl;
        return false;
    }
    if (!hMotion.SetupTarget(this)) {
        std::cerr << "hPlayer::SetupComponent(): Failed to setup motion component" << std::endl;
        return false;
    }
    if (!hUpdate.SetupTarget(this)) {
        std::cerr << "hPlayer::SetupComponent(): Failed to setup update component" << std::endl;
        return false;
    }
    if (!hRender.SetupTarget(this)) {
        std::cerr << "hPlayer::SetupComponent(): Failed to setup render component" << std::endl;
        return false;
    }
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// CHECKERS /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Check if player is win (go to next level)
/// @return True if player is win, false otherwise
bool hPlayer::IsPlayerWin() const
{
    if (Status().IsMoveUp() && !Physic().CanMoveUp()) { /// Win by moving above the top lane
        return true;
    }
    const float fPosY = Physic().GetPlayerLogicPositionY();
    return (fPosY < app_const::TOP_BORDER);
}
bool hPlayer::IsForceKilled() const
{
    return Physic().IsPlayerOutOfBounds();
}
bool hPlayer::IsKilled() const
{
    if (Status().IsJumpAnimation() && Moment().IsJumpingSafe()) {
        return false;
    }
    return Hitbox().IsHit();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// HARDWARE INTERACTION /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool hPlayer::UpdateAction(bool bLeft, bool bRight, bool bUp, bool bDown)
{
    cStatus.Modify(PlayerIntention::GO_LEFT, bLeft);
    cStatus.Modify(PlayerIntention::GO_RIGHT, bRight);
    cStatus.Modify(PlayerIntention::GO_UP, bUp);
    cStatus.Modify(PlayerIntention::GO_DOWN, bDown);
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////// LOGIC UPDATES //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Update player animation and render to screen
/// @return Always true by default
bool hPlayer::OnUpdate()
{
    return hUpdate.OnUpdate();
}

bool hPlayer::OnRender()
{
    return hRender.OnRender();
}

bool hPlayer::Draw(const std::string &sSpriteName, bool bReloadMap, bool bForceRender)
{
    return ptrApp->Draw(sSpriteName, bReloadMap, bForceRender);
}

void hPlayer::Sleep(float fTime)
{
    ptrApp->ForceSleep(fTime);
}

cZone* hPlayer::GetDangerZone()
{
    if (ptrApp) {
        return &(ptrApp->cDangerZone);
    }
    else {
        return nullptr; // or handle the case where ptrApp is null
    }
}
cZone* hPlayer::GetBlockedZone()
{
    if (ptrApp) {
        return &(ptrApp->cBlockedZone);
    }
    else {
        return nullptr; // or handle the case where ptrApp is null
    }
}
cZone* hPlayer::GetPlatformZone()
{
    if (ptrApp) {
        return &(ptrApp->cPlatformZone);
    }
    else {
        return nullptr; // or handle the case where ptrApp is null
    }
}
cZone* hPlayer::GetWinningZone()
{
    if (ptrApp) {
        return &(ptrApp->cPlatformZone);
    }
    else {
        return nullptr; // or handle the case where ptrApp is null
    }
}

void hPlayer::Read(std::istream& input) {
    input >> cStatus;
    input >> cPhysic;
    input >> cRecord;
    input >> cMoment;
}

void hPlayer::Write(std::ostream& output) const {
    output << cStatus;
    output << cPhysic;
    output << cRecord;
    output << cMoment;
}

std::istream& operator>>(std::istream& input, hPlayer& player) {
    input >> player.cStatus;
    input >> player.cPhysic;
    input >> player.cRecord;
    input >> player.cMoment;
    return input;
}

std::ostream& operator<<(std::ostream& output, const hPlayer& player) {
    output << player.cStatus;
    output << player.cPhysic;
    output << player.cRecord;
    output << player.cMoment;
    return output;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// END OF FILE ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////