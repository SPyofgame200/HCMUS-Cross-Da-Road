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
#include "cZone.h"
#include "cApp.h"
// Utilities
#include "uAppConst.h"
// Component
#include "hPlayerMotion.h"
#include "hPlayerRender.h"
#include "hPlayerHitbox.h"
#include "hPlayerUpdate.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// COMPONENT HANDLER ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

cPlayerAction& hPlayer::Action()
{
	return action;
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

const cPlayerAction& hPlayer::Action() const
{
	return action;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// CONSTRUCTORS & DESTRUCTOR ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Default constructor
hPlayer::hPlayer() : ptrApp(nullptr)
{
	SetupComponents();
	Reset();
}

/// @brief Constructor with ptrApp pointer
hPlayer::hPlayer(cApp* ptrApp) : ptrApp(nullptr)
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
	action.Reset();
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


bool hPlayer::IsPlayerStartingJump() const
{
	return (status.IsIdleAnimation()) && (action.IsMove());
}
/// @brief Check if player is idling
/// @return True if player is idling, false otherwise
bool hPlayer::IsPlayerIdling() const
{
	return (status.IsIdleAnimation()) && !(action.IsMove());
}
/// @brief Check if player is landing
/// @return True if player is landing, false otherwise
bool hPlayer::IsPlayerLanding() const
{
	return cFrameManager::GetFrame6().IsStopAnimation();
}
/// @brief Check if player is win (go to next level)
/// @return True if player is win, false otherwise
bool hPlayer::IsPlayerWin() const
{
	if (ptrApp->IsMoveUp() && !Physic().CanMoveUp()) {
		return true;
	}
	const float fPosY = Physic().GetPlayerLogicPositionY();
	return (fPosY < app_const::TOP_BORDER);
}
bool hPlayer::IsForceKilled() const
{
	std::cout << Physic().GetPlayerLogicPositionX() << " " << Physic().GetPlayerLogicPositionY() << std::endl;
	return Physic().IsPlayerOutOfBounds();
}
bool hPlayer::IsKilled() const
{
	if (Render().IsCollisionSafe()) {
		return false;
	}
	return Hitbox().IsHit();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// HARDWARE INTERACTION /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool hPlayer::UpdateAction(bool bLeft, bool bRight, bool bUp, bool bDown)
{
	action.Modify(PlayerAction::LEFT, bLeft);
	action.Modify(PlayerAction::RIGHT, bRight);
	action.Modify(PlayerAction::UP, bUp);
	action.Modify(PlayerAction::DOWN, bDown);
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
	const float nCellSize = static_cast<float>(app_const::CELL_SIZE);
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// END OF FILE ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////