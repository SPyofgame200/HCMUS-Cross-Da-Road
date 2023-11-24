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
#include "uAppUtils.h"
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
	frame6_id_animation_safe = 5;
	fFrogAnimPosX = app_const::FROG_X_RESET;
	fFrogAnimPosY = app_const::FROG_Y_RESET;
	fFrogLogicPosX = app_const::FROG_X_RESET;
	fFrogLogicPosY = app_const::FROG_Y_RESET;
	fFrogVelocityX = app_const::FROG_X_VELOCITY;
	fFrogVelocityY = app_const::FROG_Y_VELOCITY;
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

void hPlayer::SynchronizePosition(bool bAnimToLogic)
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
/// @brief Check if player is out of bounds of map border
/// @return True if player is out of bounds, false otherwise
bool hPlayer::IsPlayerOutOfBounds() const
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
/// @brief Check if player is win (go to next level)
/// @return True if player is win, false otherwise
bool hPlayer::IsPlayerWin() const
{
	if (ptrApp->IsMoveUp() && !CanMoveUp()) {
		return true;
	}
	const float fPosY = GetPlayerLogicPositionY();
	return (fPosY < app_const::TOP_BORDER);
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// VALIDATORS ///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Check if player can move left
/// @return True if player can move left, false otherwise
bool hPlayer::CanMoveLeft() const
{
	return fFrogAnimPosX > app_const::LEFT_BORDER;
}
/// @brief Check if player can move right
/// @return True if player can move right, false otherwise
bool hPlayer::CanMoveRight() const
{
	return fFrogAnimPosX < app_const::RIGHT_BORDER;
}
/// @brief Check if player can move up
/// @return True if player can move up, false otherwise
bool hPlayer::CanMoveUp() const
{
	return fFrogAnimPosY > app_const::TOP_BORDER;
}
/// @brief Check if player can move down
/// @return True if player can move down, false otherwise
bool hPlayer::CanMoveDown() const
{
	return fFrogAnimPosY < app_const::BOTTOM_BORDER;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// GETTERS ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\

/// @brief Getter for animation position of player in X-axis
float hPlayer::GetPlayerAnimationPositionX() const
{
	return fFrogAnimPosX;
}
/// @brief Getter for animation position of player in Y-axis
float hPlayer::GetPlayerAnimationPositionY() const
{
	return fFrogAnimPosY;
}
/// @brief Getter for logic position of player in X-axis
float hPlayer::GetPlayerLogicPositionX() const
{
	return fFrogLogicPosX;
}
/// @brief Getter for logic position of player in Y-axis
float hPlayer::GetPlayerLogicPositionY() const
{
	return fFrogLogicPosY;
}
/// @brief Getter for velocity of player in X-axis
float hPlayer::GetPlayerVelocityX() const
{
	return fFrogVelocityX;
}
/// @brief Getter for velocity of player in Y-axis
float hPlayer::GetPlayerVelocityY() const
{
	return fFrogVelocityY;
}
/// @brief Getter for player name
std::string hPlayer::GetPlayerName() const
{
	return Name;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// SETTERS ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Make the float [fValue] to only care about first [nDigits] digits after decimal points, others remain closest to ,...00000
float hPlayer::FixFloat(float fValue, int nDigits)
{
	return ldexpf(roundf(ldexpf(fValue, nDigits)), -nDigits);
}


/// @brief Setter for animation position of player in X-axis
/// @param fVelocityX New animation position of player in X-axis
void hPlayer::SetVelocityX(float fVelocityX)
{
	fFrogVelocityX = FixFloat(fVelocityX);
}
/// @brief Setter for animation position of player in Y-axis
/// @param fVelocityY New animation position of player in Y-axis
void hPlayer::SetVelocityY(float fVelocityY)
{
	fFrogVelocityY = FixFloat(fVelocityY);
}
/// @brief Setter for velocity of player 
/// @param fVelocityX New velocity of player in X-axis
/// @param fVelocityY New velocity of player in Y-axis
void hPlayer::SetVelocity(float fVelocityX, float fVelocityY)
{
	SetVelocityX(fVelocityX);
	SetVelocityY(fVelocityY);
}
/// @brief Setter for animation position of player in X-axis
/// @param fPositionX New animation position of player in X-axis
void hPlayer::SetAnimationPositionX(float fPositionX)
{
	fFrogAnimPosX = FixFloat(fPositionX);
}
/// @brief Setter for animation position of player in Y-axis
/// @param fPositionY New animation position of player in Y-axis
void hPlayer::SetAnimationPositionY(float fPositionY)
{
	fFrogAnimPosY = FixFloat(fPositionY);
}
/// @brief Setter for animation position of player
/// @param fPositionX New animation position of player in X-axis
/// @param fPositionY New animation position of player in Y-axis
void hPlayer::SetAnimationPosition(float fPositionX, float fPositionY)
{
	SetAnimationPositionX(fPositionX);
	SetAnimationPositionY(fPositionY);
}
/// @brief Setter for logic position of player in X-axis
/// @param fPositionX New logic position of player in X-axis
void hPlayer::SetLogicPositionX(float fPositionX)
{
	fFrogLogicPosX = FixFloat(fPositionX);
}
/// @brief Setter for logic position of player in Y-axis
/// @param fPositionY Logic position of player in Y-axis
void hPlayer::SetLogicPositionY(float fPositionY)
{
	fFrogLogicPosY = FixFloat(fPositionY);
}
/// @brief Setter for logic position of player
/// @param fPositionX Logic position of player in X-axis
/// @param fPositionY Logic position of player in Y-axis
void hPlayer::SetLogicPosition(float fPositionX, float fPositionY)
{
	SetLogicPositionX(fPositionX);
	SetLogicPositionY(fPositionY);
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

/// @brief Fix player position
/// @return True if player position is fixed, false otherwise
bool hPlayer::OnFixPlayerPosition()
{
	const float fFixedX = utils::Clamp(FixFloat(GetPlayerAnimationPositionX(), 1), app_const::LEFT_BORDER, app_const::RIGHT_BORDER);
	const float fFixedY = utils::Clamp(FixFloat(GetPlayerAnimationPositionY(), 1), app_const::TOP_BORDER, app_const::BOTTOM_BORDER);
	SetAnimationPosition(fFixedX, fFixedY);
	return true;
}

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
	const int32_t frogXPosition = static_cast<int32_t>(GetPlayerAnimationPositionX() * nCellSize);
	const int32_t frogYPosition = static_cast<int32_t>(GetPlayerAnimationPositionY() * nCellSize);
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