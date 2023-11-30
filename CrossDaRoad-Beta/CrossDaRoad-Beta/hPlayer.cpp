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
    return status;
}

cPlayerPhysic& hPlayer::Physic()
{
    return physic;
}

cPlayerRecord& hPlayer::Record()
{
    return record;
}

cPlayerMoment& hPlayer::Moment()
{
    return moment;
}

const cPlayerStatus& hPlayer::Status() const
{
    return status;
}

const cPlayerPhysic& hPlayer::Physic() const
{
    return physic;
}

const cPlayerRecord& hPlayer::Record() const
{
    return record;
}

const cPlayerMoment& hPlayer::Moment() const
{
    return moment;
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
    status.Reset();
    physic.Reset();
    record.Reset();
    moment.Reset();
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
    if (Status().IsMoveUp() && !Physic().CanMoveUp()) {
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
    status.Modify(PlayerIntention::GO_LEFT, bLeft);
    status.Modify(PlayerIntention::GO_RIGHT, bRight);
    status.Modify(PlayerIntention::GO_UP, bUp);
    status.Modify(PlayerIntention::GO_DOWN, bDown);
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
    const auto froggy = cAssetManager::GetInstance().GetSprite(sSpriteName);
    if (froggy == nullptr) {
        std::cerr << "WTF, cant found " << sSpriteName << std::endl;
    }

    if (bReloadMap) {
        ptrApp->DrawAllLanes();
    }
    ptrApp->SetPixelMode(app::Pixel::MASK);
    constexpr float nCellSize = static_cast<float>(app_const::CELL_SIZE);
    const float fPosX = Physic().GetPlayerAnimationPositionX();
    const float fPosY = Physic().GetPlayerAnimationPositionY();
    const int32_t frogXPosition = static_cast<int32_t>(fPosX * nCellSize);
    const int32_t frogYPosition = static_cast<int32_t>(fPosY * nCellSize);
    ptrApp->DrawSprite(frogXPosition, frogYPosition, froggy);
    ptrApp->SetPixelMode(app::Pixel::NORMAL);
    if (bForceRender) {
        ptrApp->DrawStatusBar();
        ptrApp->RenderTexture();
    }
    return true;
}

void hPlayer::Sleep(float fTime)
{
    ptrApp->ForceSleep(fTime);
}

cZone* hPlayer::GetZone()
{
    if (ptrApp) {
        return &(ptrApp->Zone);
    }
    else {
        return nullptr; // or handle the case where ptrApp is null
    }
}

void hPlayer::Read(std::istream& input) {
    input >> status;
    input >> physic;
    input >> record;
    input >> moment;
}

void hPlayer::Write(std::ostream& output) const {
    output << status;
    output << physic;
    output << record;
    output << moment;
}

std::istream& operator>>(std::istream& input, hPlayer& player) {
    input >> player.status;
    input >> player.physic;
    input >> player.record;
    input >> player.moment;
    return input;
}

std::ostream& operator<<(std::ostream& output, const hPlayer& player) {
    output << player.status;
    output << player.physic;
    output << player.record;
    output << player.moment;
    return output;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// END OF FILE ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////