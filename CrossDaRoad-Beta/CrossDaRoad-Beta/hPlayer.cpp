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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// CONSTRUCTORS & DESTRUCTOR ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Default constructor
hPlayer::hPlayer() : ptrApp(nullptr)
{
	hMotion.SetupTarget(this);
	hRender.SetupTarget(this);
	Reset();
}

/// @brief Constructor with ptrApp pointer
hPlayer::hPlayer(cApp* ptrApp) : ptrApp(nullptr)
{
	hMotion.SetupTarget(this);
	hRender.SetupTarget(this);
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

/// @brief Reset player direction
void hPlayer::ResetDirection()
{
	eDirection = RIGHT;
	eAnimation = IDLE;
}
/// @brief Reset player animation
void hPlayer::ResetAnimation()
{
	frame6_id_animation_safe = 5;
}
/// @brief Reset player position
void hPlayer::ResetPosition()
{
	fFrogAnimPosX = app_const::FROG_X_RESET;
	fFrogAnimPosY = app_const::FROG_Y_RESET;
	fFrogLogicPosX = app_const::FROG_X_RESET;
	fFrogLogicPosY = app_const::FROG_Y_RESET;
}
/// @brief Reset player velocity
void hPlayer::ResetVelocity()
{
	fFrogVelocityX = app_const::FROG_X_VELOCITY;
	fFrogVelocityY = app_const::FROG_Y_VELOCITY;
}
/// @brief Reset player properties
void hPlayer::Reset()
{
	ResetDirection();
	ResetAnimation();
	ResetPosition();
	ResetVelocity();
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// CHECKERS /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Check if player is facing exact direction
/// @param eCompare Direction to compare
/// @return True if player is facing exact direction, false otherwise
bool hPlayer::IsExactDirection(Direction eCompare) const
{
	return eDirection == eCompare;
}

/// @brief Check if player is doing exact animation
/// @param eCompare Animation to compare
/// @return True if player is doing exact animation, false otherwise
bool hPlayer::IsExactAnimation(Animation eCompare) const
{
	return eAnimation == eCompare;
}

/// @brief Check if player is facing left direction
/// @return True if player is facing left direction, false otherwise
bool hPlayer::IsLeftDirection() const
{
	return (eDirection == LEFT)
		|| (eDirection == LEFT_UP)
		|| (eDirection == LEFT_DOWN);
}
/// @brief Check if player is facing right direction
/// @return True if player is facing right direction, false otherwise
bool hPlayer::IsRightDirection() const
{
	return (eDirection == RIGHT)
		|| (eDirection == RIGHT_UP)
		|| (eDirection == RIGHT_DOWN);
}
/// @brief Check if player is jumping
/// @return True if player is jumping, false otherwise
bool hPlayer::IsPlayerJumping() const
{
	return (GetAnimation() == JUMP);
}
/// @brief Check if player is idling
/// @return True if player is idling, false otherwise
bool hPlayer::IsPlayerIdling() const
{
	return (GetAnimation() == IDLE);
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// COLLISIONS DETECTION /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Check if player is hit by danger zone at top left corner
/// @return True if player is hit by danger zone at top left corner, false otherwise
bool hPlayer::IsHitTopLeft() const
{
	const float fPosX = GetPlayerLogicPositionX();
	const float fPosY = GetPlayerLogicPositionY();
	const bool isHitTopLeft = ptrApp->Zone.IsDangerTopLeft(fPosX, fPosY, app_const::CELL_SIZE);
	return isHitTopLeft;
}
/// @brief Check if player is hit by danger zone at top right corner
/// @return True if player is hit by danger zone at top right corner, false otherwise
bool hPlayer::IsHitTopRight() const
{
	const float fPosX = GetPlayerLogicPositionX();
	const float fPosY = GetPlayerLogicPositionY();
	const bool isHitTopRight = ptrApp->Zone.IsDangerTopRight(fPosX, fPosY, app_const::CELL_SIZE);
	return isHitTopRight;
}
/// @brief Check if player is hit by danger zone at bottom left corner
/// @return True if player is hit by danger zone at bottom left corner, false otherwise
bool hPlayer::IsHitBottomLeft() const
{
	const float fPosX = GetPlayerLogicPositionX();
	const float fPosY = GetPlayerLogicPositionY();
	const bool isHitBottomLeft = ptrApp->Zone.IsDangerBottomLeft(fPosX, fPosY, app_const::CELL_SIZE);
	return isHitBottomLeft;
}
/// @brief Check if player is hit by danger zone at bottom right corner
/// @return True if player is hit by danger zone at bottom right corner, false otherwise
bool hPlayer::IsHitBottomRight() const
{
	const float fPosX = GetPlayerLogicPositionX();
	const float fPosY = GetPlayerLogicPositionY();
	const bool isHitBottomRight = ptrApp->Zone.IsDangerBottomRight(fPosX, fPosY, app_const::CELL_SIZE);
	return isHitBottomRight;
}
/// @brief Check if player is hit by danger zone
/// @return True if player is hit by danger zone, false otherwise
bool hPlayer::IsHit() const
{
	return IsHitTopLeft()
		|| IsHitTopRight()
		|| IsHitBottomLeft()
		|| IsHitBottomRight();
}
/// @brief Check if player is blocked by block zone at top left corner
/// @return True if player is blocked by block zone at top left corner, false otherwise
bool hPlayer::IsBlockedTopLeft() const
{
	const float fPosX = GetPlayerAnimationPositionX();
	const float fPosY = GetPlayerAnimationPositionY();
	const bool isBlockedTopLeft = ptrApp->Zone.IsBlockedTopLeft(fPosX, fPosY, app_const::CELL_SIZE);
	return isBlockedTopLeft;
}
/// @brief Check if player is blocked by block zone at top right corner
/// @return True if player is blocked by block zone at top right corner, false otherwise
bool hPlayer::IsBlockedTopRight() const
{
	const float fPosX = GetPlayerAnimationPositionX();
	const float fPosY = GetPlayerAnimationPositionY();
	const bool isBlockedTopRight = ptrApp->Zone.IsBlockedTopRight(fPosX, fPosY, app_const::CELL_SIZE);
	return isBlockedTopRight;
}
/// @brief Check if player is blocked by block zone at bottom left corner
/// @return True if player is blocked by block zone at bottom left corner, false otherwise
bool hPlayer::IsBlockedBottomLeft() const
{
	const float fPosX = GetPlayerAnimationPositionX();
	const float fPosY = GetPlayerAnimationPositionY();
	const bool isBlockedBottomLeft = ptrApp->Zone.IsBlockedBottomLeft(fPosX, fPosY, app_const::CELL_SIZE);
	return isBlockedBottomLeft;
}
/// @brief Check if player is blocked by block zone at bottom right corner
/// @return True if player is blocked by block zone at bottom right corner, false otherwise
bool hPlayer::IsBlockedBottomRight() const
{
	const float fPosX = GetPlayerAnimationPositionX();
	const float fPosY = GetPlayerAnimationPositionY();
	const bool isBlockedBottomRight = ptrApp->Zone.IsBlockedBottomRight(fPosX, fPosY, app_const::CELL_SIZE);
	return isBlockedBottomRight;
}
/// @brief Check if player is blocked by block zone
/// @return True if player is blocked by block zone, false otherwise
bool hPlayer::IsBlocked() const
{
	return IsBlockedTopLeft()
		|| IsBlockedTopRight()
		|| IsBlockedBottomLeft()
		|| IsBlockedBottomRight();
}
/// @brief Check if player is on a platform at top left corner
/// @return True if player is on a platform at top left corner, false otherwise
bool hPlayer::IsOnPlatformTopLeft() const
{
	const float fPosX = GetPlayerAnimationPositionX();
	const float fPosY = GetPlayerAnimationPositionY();
	const bool isOnPlatformTopLeft = ptrApp->Zone.IsPlatformTopLeft(fPosX, fPosY, app_const::CELL_SIZE);
	return isOnPlatformTopLeft;
}

/// @brief Check if player is on a platform at top right corner
/// @return True if player is on a platform at top right corner, false otherwise
bool hPlayer::IsOnPlatformTopRight() const
{
	const float fPosX = GetPlayerAnimationPositionX();
	const float fPosY = GetPlayerAnimationPositionY();
	const bool isOnPlatformTopRight = ptrApp->Zone.IsPlatformTopRight(fPosX, fPosY, app_const::CELL_SIZE);
	return isOnPlatformTopRight;
}

/// @brief Check if player is on a platform at bottom left corner
/// @return True if player is on a platform at bottom left corner, false otherwise
bool hPlayer::IsOnPlatformBottomLeft() const
{
	const float fPosX = GetPlayerAnimationPositionX();
	const float fPosY = GetPlayerAnimationPositionY();
	const bool isOnPlatformBottomLeft = ptrApp->Zone.IsPlatformBottomLeft(fPosX, fPosY, app_const::CELL_SIZE);
	return isOnPlatformBottomLeft;
}

/// @brief Check if player is on a platform at bottom right corner
/// @return True if player is on a platform at bottom right corner, false otherwise
bool hPlayer::IsOnPlatformBottomRight() const
{
	const float fPosX = GetPlayerAnimationPositionX();
	const float fPosY = GetPlayerAnimationPositionY();
	const bool isOnPlatformBottomRight = ptrApp->Zone.IsPlatformBottomRight(fPosX, fPosY, app_const::CELL_SIZE);
	return isOnPlatformBottomRight;
}

/// @brief Check if player is on a platform
/// @return True if player is on a platform, false otherwise
bool hPlayer::IsOnPlatform() const
{
	return IsOnPlatformTopLeft()
		|| IsOnPlatformTopRight()
		|| IsOnPlatformBottomLeft()
		|| IsOnPlatformBottomRight();
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
	return ptrApp->IsKilled();
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Getter for current direction of player
hPlayer::Direction hPlayer::GetDirection() const
{
	return eDirection;
}
/// @brief Getter for current animation of player
hPlayer::Animation hPlayer::GetAnimation() const
{
	return eAnimation;
}

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

/// @brief Setter for current direction of player
/// @param eNewDirection New direction of player
void hPlayer::SetDirection(Direction eNewDirection)
{
	eDirection = eNewDirection;
}
/// @brief Setter for current animation of player
/// @param eNewAnimation New animation of player
void hPlayer::SetAnimation(Animation eNewAnimation)
{
	eAnimation = eNewAnimation;
}
/// @brief Setter for animation position of player in X-axis
/// @param fVelocityX New animation position of player in X-axis
void hPlayer::SetPlayerVelocityX(float fVelocityX)
{
	fFrogVelocityX = FixFloat(fVelocityX);
}
/// @brief Setter for animation position of player in Y-axis
/// @param fVelocityY New animation position of player in Y-axis
void hPlayer::SetPlayerVelocityY(float fVelocityY)
{
	fFrogVelocityY = FixFloat(fVelocityY);
}
/// @brief Setter for velocity of player 
/// @param fVelocityX New velocity of player in X-axis
/// @param fVelocityY New velocity of player in Y-axis
void hPlayer::SetPlayerVelocity(float fVelocityX, float fVelocityY)
{
	SetPlayerVelocityX(fVelocityX);
	SetPlayerVelocityY(fVelocityY);
}
/// @brief Setter for animation position of player in X-axis
/// @param fPositionX New animation position of player in X-axis
void hPlayer::SetPlayerAnimationPositionX(float fPositionX)
{
	fFrogAnimPosX = FixFloat(fPositionX);
}
/// @brief Setter for animation position of player in Y-axis
/// @param fPositionY New animation position of player in Y-axis
void hPlayer::SetPlayerAnimationPositionY(float fPositionY)
{
	fFrogAnimPosY = FixFloat(fPositionY);
}
/// @brief Setter for animation position of player
/// @param fPositionX New animation position of player in X-axis
/// @param fPositionY New animation position of player in Y-axis
void hPlayer::SetPlayerAnimationPosition(float fPositionX, float fPositionY)
{
	SetPlayerAnimationPositionX(fPositionX);
	SetPlayerAnimationPositionY(fPositionY);
}
/// @brief Setter for logic position of player in X-axis
/// @param fPositionX New logic position of player in X-axis
void hPlayer::SetPlayerLogicPositionX(float fPositionX)
{
	fFrogLogicPosX = FixFloat(fPositionX);
}
/// @brief Setter for logic position of player in Y-axis
/// @param fPositionY Logic position of player in Y-axis
void hPlayer::SetPlayerLogicPositionY(float fPositionY)
{
	fFrogLogicPosY = FixFloat(fPositionY);
}
/// @brief Setter for logic position of player
/// @param fPositionX Logic position of player in X-axis
/// @param fPositionY Logic position of player in Y-axis
void hPlayer::SetPlayerLogicPosition(float fPositionX, float fPositionY)
{
	SetPlayerLogicPositionX(fPositionX);
	SetPlayerLogicPositionY(fPositionY);
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
	SetPlayerAnimationPosition(fFixedX, fFixedY);
	return true;
}

/// @brief Update animation when player idling
/// @return Always true by default
bool hPlayer::OnUpdatePlayerIdle()
{
	SetPlayerLogicPosition(fFrogAnimPosX, fFrogAnimPosY);
	return true;
}

/// @brief Update animation when player start jumping
/// @return True if player animation is updated, false otherwise
bool hPlayer::OnUpdatePlayerJumpStart()
{
	SetPlayerLogicPosition(fFrogAnimPosX, fFrogAnimPosY);
	return cFrameManager::GetFrame6().StartAnimation();
}
/// @brief Update animation when player continue jumping
/// @return True if player animation is updated, false otherwise
bool hPlayer::OnUpdatePlayerJumpContinue() const
{
	if (GetAnimation() == IDLE) {
		return false;
	}
	if (cFrameManager::GetFrame6().NextAnimation()) {
		if (GetDirection() == LEFT) {
			if (!hMotion.MoveLeft(1.0f / cFrameManager::GetFrame6().GetLimit(), true)) {
				return false;
			}
		}
		else if (GetDirection() == RIGHT) {
			if (!hMotion.MoveRight(1.0f / cFrameManager::GetFrame6().GetLimit(), true)) {
				return false;
			}
		}
		else if (GetDirection() == LEFT_UP || GetDirection() == RIGHT_UP) {
			if (!hMotion.MoveUp(1.0f / cFrameManager::GetFrame6().GetLimit(), true)) {
				return false;
			}
		}
		else if (GetDirection() == LEFT_DOWN || GetDirection() == RIGHT_DOWN) {
			if (!hMotion.MoveDown(1.0f / cFrameManager::GetFrame6().GetLimit(), true)) {
				return false;
			}
		}
	}
	return true;
}

/// @brief Update animation when player stop jumping
/// @return True if player animation is updated, false otherwise
bool hPlayer::OnUpdatePlayerJumpStop()
{
	OnFixPlayerPosition();
	SetPlayerLogicPosition(fFrogAnimPosX, fFrogAnimPosY);
	if (GetAnimation() == JUMP) {
		SetAnimation(IDLE);
		return true;
	}
	return false;
}

/// @brief Update player animation and render to screen
/// @return Always true by default
bool hPlayer::OnPlayerMove()
{
	if (IsPlayerIdling()) {
		if (ptrApp->IsMoveLeft()) {
			SetAnimation(JUMP);
			SetDirection(LEFT);
		}
		else if (ptrApp->IsMoveRight()) {
			SetAnimation(JUMP);
			SetDirection(RIGHT);
		}
		else if (ptrApp->IsMoveUp()) {
			SetAnimation(JUMP);
			SetDirection(IsLeftDirection() ? LEFT_UP : RIGHT_UP);
		}
		else if (ptrApp->IsMoveDown()) {
			SetAnimation(JUMP);
			SetDirection(IsLeftDirection() ? LEFT_DOWN : RIGHT_DOWN);
		}

		if (IsPlayerJumping()) {
			OnUpdatePlayerJumpStart();
			hRender.OnRenderPlayerJumpStart();
		}
		else {
			OnUpdatePlayerIdle();
			hRender.OnRenderPlayerIdle();
		}
		return true;
	}

	if (!IsPlayerLanding()) {
		OnUpdatePlayerJumpContinue();
		hRender.OnRenderPlayerJumpContinue();
	}
	else { /// Jump completed
		OnUpdatePlayerJumpStop();
		hRender.OnRenderPlayerJumpStop();
	}
	return true;
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// END OF FILE ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////