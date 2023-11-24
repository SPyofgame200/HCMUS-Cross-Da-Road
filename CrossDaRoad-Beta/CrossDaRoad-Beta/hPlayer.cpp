/**
 * @file hPlayer.cpp
 *
 * @brief Contains player class implementation
 *
 * This file implements player class for player management, movement, and rendering.
**/

#include "hPlayer.h"
#include "cZone.h"
#include "cApp.h"
#include "uAppConst.h"
#include "cFrameManager.h"
#include "hPlayerMotion.h"
#include "hPlayerRender.h"
#include "hPlayerHitbox.h"
#include "hPlayerUpdate.h"


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

cPlayerStatus& hPlayer::Status()
{
	return status;
}

cPlayerPhysic& hPlayer::Physic()
{
	return physic;
}

const cPlayerStatus& hPlayer::Status() const
{
	return status;
}

const cPlayerPhysic& hPlayer::Physic() const
{
	return physic;
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
	frame6_id_animation_safe = 5;
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


/// @brief Check if player is jumping
/// @return True if player is jumping, false otherwise
bool hPlayer::IsPlayerJumping() const
{
	return (status.GetAnimation() == cPlayerStatus::JUMP);
}
bool hPlayer::IsPlayerMoving() const
{
	return (IsMoveUp())
		|| (IsMoveDown())
		|| (IsMoveLeft())
		|| (IsMoveRight());
}
bool hPlayer::IsPlayerStartingJump() const
{
	return (status.GetAnimation() == cPlayerStatus::IDLE) && IsPlayerMoving();
}
/// @brief Check if player is idling
/// @return True if player is idling, false otherwise
bool hPlayer::IsPlayerIdling() const
{
	return (status.GetAnimation() == cPlayerStatus::IDLE) && !IsPlayerMoving();
}
/// @brief Check if player is landing
/// @return True if player is landing, false otherwise
bool hPlayer::IsPlayerLanding() const
{
	return cFrameManager::GetFrame6().IsStopAnimation();
}
/// @brief Check if player is safe when having collision
/// @return True if player is safe, false otherwise
bool hPlayer::IsPlayerCollisionSafe() const
{
	return cFrameManager::GetFrame6().GetAnimationID() <= frame6_id_animation_safe;
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
	return Physic().IsPlayerOutOfBounds();
}
bool hPlayer::IsKilled() const
{
	if (IsPlayerCollisionSafe()) {
		return false;
	}
	return Hitbox().IsHit();
}

bool hPlayer::IsMoveLeft() const
{
	return ptrApp->IsMoveLeft();
}
bool hPlayer::IsMoveRight() const
{
	return ptrApp->IsMoveRight();
}
bool hPlayer::IsMoveUp() const
{
	return ptrApp->IsMoveUp();
}
bool hPlayer::IsMoveDown() const
{
	return ptrApp->IsMoveDown();
}

/// @brief Getter for player name
std::string hPlayer::GetPlayerName() const
{
	return Name;
}

/// @brief Setter for player name
/// @param Name Name of player
void hPlayer::SetPlayerName(const std::string& Name)
{
	this->Name = Name;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// LOGIC UPDATES ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Update player animation and render to screen
/// @return Always true by default
bool hPlayer::OnUpdate()
{
	if (IsPlayerIdling()) {
		return hUpdate.OnUpdatePlayerIdle();
	}
	if (IsPlayerStartingJump()) {
		return hUpdate.OnUpdatePlayerJumpStart();
	}
	if (!IsPlayerLanding()) {
		return hUpdate.OnUpdatePlayerJumpContinue();
	}
	else { /// Jump completed
		return hUpdate.OnUpdatePlayerJumpStop();
	}
	return false;
}

bool hPlayer::OnRender()
{
	if (IsPlayerIdling()) {
		return hRender.OnRenderPlayerIdle();
	}
	if (IsPlayerStartingJump()) {
		return hRender.OnRenderPlayerJumpStart();
	}
	if (!IsPlayerLanding()) {
		return hRender.OnRenderPlayerJumpContinue();
	}
	else { /// Jump completed
		return hRender.OnRenderPlayerJumpStop();
	}
	return false;
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
	const int32_t frogXPosition = static_cast<int32_t>(Physic().GetPlayerAnimationPositionX() * nCellSize);
	const int32_t frogYPosition = static_cast<int32_t>(Physic().GetPlayerAnimationPositionY() * nCellSize);
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