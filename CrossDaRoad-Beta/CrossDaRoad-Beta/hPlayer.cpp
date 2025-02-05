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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// CONSTRUCTORS & DESTRUCTOR ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Default constructor
hPlayer::hPlayer()
{
	Reset();
}

/// @brief Constructor with app pointer
hPlayer::hPlayer(cApp* app)
{
	SetupTarget(app);
	Reset();
}

/// @brief Destructor
hPlayer::~hPlayer()
{
	// No, we are not deleting anything, cApp* app is controlled by cApp
	app = nullptr;
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
/// @brief Setup app pointer
/// @param app Pointer to app
void hPlayer::SetupTarget(cApp* app)
{
	this->app = app;
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
	return app->frame6.IsStopAnimation();
}
/// @brief Check if player is safe when having collision
/// @return True if player is safe, false otherwise
bool hPlayer::IsPlayerCollisionSafe() const
{
	return app->frame6.GetAnimationID() <= frame6_id_animation_safe;
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
	const bool isHitTopLeft = app->Zone.IsDangerTopLeft(fPosX, fPosY, app_const::CELL_SIZE);
	return isHitTopLeft;
}
/// @brief Check if player is hit by danger zone at top right corner
/// @return True if player is hit by danger zone at top right corner, false otherwise
bool hPlayer::IsHitTopRight() const
{
	const float fPosX = GetPlayerLogicPositionX();
	const float fPosY = GetPlayerLogicPositionY();
	const bool isHitTopRight = app->Zone.IsDangerTopRight(fPosX, fPosY, app_const::CELL_SIZE);
	return isHitTopRight;
}
/// @brief Check if player is hit by danger zone at bottom left corner
/// @return True if player is hit by danger zone at bottom left corner, false otherwise
bool hPlayer::IsHitBottomLeft() const
{
	const float fPosX = GetPlayerLogicPositionX();
	const float fPosY = GetPlayerLogicPositionY();
	const bool isHitBottomLeft = app->Zone.IsDangerBottomLeft(fPosX, fPosY, app_const::CELL_SIZE);
	return isHitBottomLeft;
}
/// @brief Check if player is hit by danger zone at bottom right corner
/// @return True if player is hit by danger zone at bottom right corner, false otherwise
bool hPlayer::IsHitBottomRight() const
{
	const float fPosX = GetPlayerLogicPositionX();
	const float fPosY = GetPlayerLogicPositionY();
	const bool isHitBottomRight = app->Zone.IsDangerBottomRight(fPosX, fPosY, app_const::CELL_SIZE);
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
	const bool isBlockedTopLeft = app->Zone.IsBlockedTopLeft(fPosX, fPosY, app_const::CELL_SIZE);
	return isBlockedTopLeft;
}
/// @brief Check if player is blocked by block zone at top right corner
/// @return True if player is blocked by block zone at top right corner, false otherwise
bool hPlayer::IsBlockedTopRight() const
{
	const float fPosX = GetPlayerAnimationPositionX();
	const float fPosY = GetPlayerAnimationPositionY();
	const bool isBlockedTopRight = app->Zone.IsBlockedTopRight(fPosX, fPosY, app_const::CELL_SIZE);
	return isBlockedTopRight;
}
/// @brief Check if player is blocked by block zone at bottom left corner
/// @return True if player is blocked by block zone at bottom left corner, false otherwise
bool hPlayer::IsBlockedBottomLeft() const
{
	const float fPosX = GetPlayerAnimationPositionX();
	const float fPosY = GetPlayerAnimationPositionY();
	const bool isBlockedBottomLeft = app->Zone.IsBlockedBottomLeft(fPosX, fPosY, app_const::CELL_SIZE);
	return isBlockedBottomLeft;
}
/// @brief Check if player is blocked by block zone at bottom right corner
/// @return True if player is blocked by block zone at bottom right corner, false otherwise
bool hPlayer::IsBlockedBottomRight() const
{
	const float fPosX = GetPlayerAnimationPositionX();
	const float fPosY = GetPlayerAnimationPositionY();
	const bool isBlockedBottomRight = app->Zone.IsBlockedBottomRight(fPosX, fPosY, app_const::CELL_SIZE);
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
/// @brief Check if player is win (go to next level)
/// @return True if player is win, false otherwise
bool hPlayer::IsPlayerWin() const
{
	if (app->IsMoveUp() && !CanMoveUp()) {
		return true;
	}
	const float fPosY = GetPlayerLogicPositionY();
	return (fPosY < app_const::TOP_BORDER);
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
void hPlayer::SetPlayerName(std::string Name)
{
	this->Name = Name;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// MOVEMENTS ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Move player in X-axis
/// @param fFactorX Factor of movement in X-axis
/// @param nStep Number of steps to move
/// @return Always true by default
bool hPlayer::PlayerMoveX(float fFactorX, int nStep)
{
	const float fPosX = GetPlayerAnimationPositionX();
	const float fPosY = GetPlayerAnimationPositionY();
	for (int nPos = nStep; nPos >= 0; --nPos) {
		const float fPartial = (nPos == nStep ? 1.0f : nPos / nStep);
		const float fOffsetPartialX = fFrogVelocityX * fFactorX * fPartial;
		SetPlayerAnimationPosition(fPosX + fOffsetPartialX, fPosY);
		if (!IsBlocked() && !IsPlayerOutOfBounds()) {
			break;
		}
	}
	return true;
}
/// @brief Move player in Y-axis
/// @param fFactorY Factor of movement in Y-axis
/// @param nStep Number of steps to move
/// @return Always true by default
bool hPlayer::PlayerMoveY(float fFactorY, int nStep)
{
	const float fPosX = GetPlayerAnimationPositionX();
	const float fPosY = GetPlayerAnimationPositionY();
	for (int nPos = nStep; nPos >= 0; --nPos) {
		const float fPartial = (nPos == nStep ? 1.0f : nPos / nStep);
		const float fOffsetPartialY = fFrogVelocityY * fFactorY * fPartial;
		SetPlayerAnimationPosition(fPosX, fPosY + fOffsetPartialY);
		if (!IsBlocked() && !IsPlayerOutOfBounds()) {
			break;
		}
	}
	return true;
}
/// @brief Move player in X-axis and Y-axis
/// @param fFactorX Factor of movement in X-axis
/// @param fFactorY Factor of movement in Y-axis
/// @param fFactorScale Factor of movement scale
/// @param nStep Number of steps to move
/// @return True if player successfully moved, false otherwise
bool hPlayer::PlayerMove(float fFactorX, float fFactorY, float fFactorScale, int nStep)
{
	return PlayerMoveX(fFactorX * fFactorScale, nStep)
		&& PlayerMoveY(fFactorY * fFactorScale, nStep);
}
/// @brief Check if Player successfully moved left (by key released)
bool hPlayer::PlayerMoveLeft(float factor, bool forced)
{
	if ((forced || app->IsMoveLeft()) && CanMoveLeft()) {
		PlayerMove(-1, 0, factor);
	}
	return true;
}
/// @brief Check if Player successfully moved right (by key released)
bool hPlayer::PlayerMoveRight(float factor, bool forced)
{
	if ((forced || app->IsMoveRight()) && CanMoveRight()) {
		PlayerMove(+1, 0, factor);
	}
	return true;
}
/// @brief Check if Player successfully moved up (by key released)
bool hPlayer::PlayerMoveUp(float factor, bool forced)
{
	if ((forced || app->IsMoveUp()) && CanMoveUp()) {
		PlayerMove(0, -1, factor);
	}
	return true;
}
//// @brief Check if Player successfully moved down (by key released)
bool hPlayer::PlayerMoveDown(float factor, bool forced)
{
	if ((forced || app->IsMoveDown()) && CanMoveDown()) {
		PlayerMove(0, +1, factor);
	}
	return true;
}
/// @brief Check if Player successfully moved (by key released)
bool hPlayer::PlayerMoveTryAll(float factor, bool forced)
{
	bool ok = true;
	ok &= PlayerMoveLeft(factor, forced);
	ok &= PlayerMoveRight(factor, forced);
	ok &= PlayerMoveUp(factor, forced);
	ok &= PlayerMoveDown(factor, forced);
	return ok;
}
/// @brief Detect if player is on platform
/// @param nStep Number of steps to detect
/// @param fFactor Factor of movement scale
/// @return True if player is on platform, false otherwise
bool hPlayer::PlayerPlatformDetector(int nStep, float fFactor)
{
	if (app->IsMoveRight() && app->IsKilled()) {
		for (int step = 1; step <= nStep; ++step) {
			PlayerMoveRight(fFactor, true);
			if (!app->IsKilled()) {
				return false;
			}
		}
		for (int step = 1; step <= nStep; ++step) {
			PlayerMoveLeft(fFactor, true);
			if (!app->IsKilled()) {
				return false;
			}
		}
	}
	if (!app->IsMoveLeft() && app->IsKilled()) {
		for (int step = 1; step <= nStep; ++step) {
			PlayerMoveLeft(fFactor, true);
			if (!app->IsKilled()) {
				return false;
			}
		}
		for (int step = 1; step <= nStep; ++step) {
			PlayerMoveRight(fFactor, true);
			if (!app->IsKilled()) {
				return false;
			}
		}
	}
	return true;
}

/// @brief Check if Player successfully moved on platform in X-axis
/// @param fFactorX Factor of movement in X-axis
/// @param nStep Number of steps to move
/// @return Always true by default
bool hPlayer::PlayerPlatformMoveX(float fFactorX, int nStep)
{
	const float fRealPosX = GetPlayerLogicPositionX();
	const float fRealPosY = GetPlayerLogicPositionY();
	const float fPosX = GetPlayerAnimationPositionX();
	const float fPosY = GetPlayerAnimationPositionY();
	const float fOffsetX = fFrogVelocityX * fFactorX;
	for (int nPos = nStep; nPos >= 0; --nPos) {
		const float fOffsetPartialX = fFrogVelocityX * fFactorX * nPos / nStep;
		SetPlayerAnimationPosition(fPosX + fOffsetPartialX, fPosY);
		SetPlayerLogicPosition(fRealPosX + fOffsetPartialX, fRealPosY);
		if (!IsBlocked()) {
			break;
		}
	}
	return true;
}
/// @brief Check if Player successfully moved on platform in Y-axis
/// @param fFactorY Factor of movement in Y-axis
/// @param nStep Number of steps to move
/// @return Always true by default
bool hPlayer::PlayerPlatformMoveY(float fFactorY, int nStep)
{
	const float fRealPosX = GetPlayerLogicPositionX();
	const float fRealPosY = GetPlayerLogicPositionY();
	const float fPosX = GetPlayerAnimationPositionX();
	const float fPosY = GetPlayerAnimationPositionY();
	const float fOffsetY = fFrogVelocityY * fFactorY;
	for (int nPos = nStep; nPos >= 0; --nPos) {
		const float fOffsetPartialY = fFrogVelocityY * fFactorY * nPos / nStep;
		SetPlayerAnimationPosition(fPosX, fPosY + fOffsetPartialY);
		SetPlayerLogicPosition(fRealPosX, fRealPosY + fOffsetPartialY);
		if (!IsBlocked()) {
			break;
		}
	}
	return true;
}
/// @brief Check if Player successfully moved on platform
/// @param fFactorX Factor of movement in X-axis
/// @param fFactorY Factor of movement in Y-axis
/// @param fFactorScale Factor of movement scale
/// @param nStep Number of steps to move
/// @return Always true by default
bool hPlayer::PlayerPlatformMove(float fFactorX, float fFactorY, float fFactorScale, int nStep)
{
	return PlayerPlatformMoveX(fFactorX * fFactorScale) && PlayerPlatformMoveY(fFactorY * fFactorScale);
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
	return app->frame6.StartAnimation();
}
/// @brief Update animation when player continue jumping
/// @return True if player animation is updated, false otherwise
bool hPlayer::OnUpdatePlayerJumpContinue()
{
	if (GetAnimation() == IDLE) {
		return false;
	}
	if (app->frame6.NextAnimation()) {
		if (GetDirection() == LEFT) {
			if (!PlayerMoveLeft(1.0f / app->frame6.GetLimit(), true)) {
				return false;
			}
		}
		else if (GetDirection() == RIGHT) {
			if (!PlayerMoveRight(1.0f / app->frame6.GetLimit(), true)) {
				return false;
			}
		}
		else if (GetDirection() == LEFT_UP || GetDirection() == RIGHT_UP) {
			if (!PlayerMoveUp(1.0f / app->frame6.GetLimit(), true)) {
				return false;
			}
		}
		else if (GetDirection() == LEFT_DOWN || GetDirection() == RIGHT_DOWN) {
			if (!PlayerMoveDown(1.0f / app->frame6.GetLimit(), true)) {
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// PLAYER RENDERER ///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool hPlayer::OnRenderPlayerIdle() const
{
	OnRenderPlayer();
	return true;
}

bool hPlayer::OnRenderPlayerJumpStart() const
{
	OnRenderPlayer();
	return true;
}

bool hPlayer::OnRenderPlayerJumpContinue() const
{
	OnRenderPlayer();
	return true;
}

bool hPlayer::OnRenderPlayerJumpStop() const
{
	OnRenderPlayer();
	return true;
}

/// @brief Render player animation to screen
/// @return Always true by default
bool hPlayer::OnRenderPlayer() const
{
	const int nID = app->frame6.GetAnimationID();
	const bool isValidID = app->frame6.IsValidID(nID);
	const bool isLeft = (IsLeftDirection());
	const bool isJump = (IsPlayerJumping()) && (isValidID);
	const std::string froggy_state = std::string(isJump ? "_jump" : "");
	const std::string froggy_direction = std::string(isLeft ? "_left" : "");
	const std::string froggy_id = (isJump ? std::to_string(nID) : "");
	const std::string froggy_name = "froggy" + froggy_state + froggy_direction + froggy_id;
	const auto froggy = cAssetManager::GetInstance().GetSprite(froggy_name);
	if (froggy == nullptr) {
		std::cerr << "WTF, cant found " << froggy_name << std::endl;
	}

	app->SetPixelMode(app::Pixel::MASK);
	const float nCellSize = static_cast<float>(app->nCellSize);
	const int32_t frogXPosition = static_cast<int32_t>(fFrogAnimPosX * nCellSize);
	const int32_t frogYPosition = static_cast<int32_t>(fFrogAnimPosY * nCellSize);
	app->DrawSprite(frogXPosition, frogYPosition, froggy);
	app->SetPixelMode(app::Pixel::NORMAL);
	return true;
}

/// @brief Render player death animation to screen
/// @return Always true by default
bool hPlayer::OnRenderPlayerDeath()
{
	for (int id = 1; id <= 6; ++id) {
		const std::string froggy_name = "froggy_death" + std::to_string(id);;
		const auto froggy = cAssetManager::GetInstance().GetSprite(froggy_name);
		if (froggy == nullptr) {
			std::cerr << "WTF, cant found \"" << froggy_name << ".png\"" << std::endl;
		}

		const float nCellSize = static_cast<float>(app->nCellSize);
		const int32_t frogXPosition = static_cast<int32_t>(GetPlayerAnimationPositionX() * nCellSize);
		const int32_t frogYPosition = static_cast<int32_t>(GetPlayerAnimationPositionY() * nCellSize);
		app->DrawAllLanes();
		app->SetPixelMode(app::Pixel::MASK);
		app->DrawSprite(frogXPosition, frogYPosition, froggy);
		app->SetPixelMode(app::Pixel::NORMAL);
		app->DrawStatusBar();

		app->RenderTexture();
		Sleep(100);
	}
	Reset();
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// LOGIC-RENDER CONTROL /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Update player animation and render to screen
/// @return Always true by default
bool hPlayer::OnPlayerMove()
{
	if (IsPlayerIdling()) {
		if (app->IsMoveLeft()) {
			SetAnimation(JUMP);
			SetDirection(LEFT);
		}
		else if (app->IsMoveRight()) {
			SetAnimation(JUMP);
			SetDirection(RIGHT);
		}
		else if (app->IsMoveUp()) {
			SetAnimation(JUMP);
			SetDirection(IsLeftDirection() ? LEFT_UP : RIGHT_UP);
		}
		else if (app->IsMoveDown()) {
			SetAnimation(JUMP);
			SetDirection(IsLeftDirection() ? LEFT_DOWN : RIGHT_DOWN);
		}

		if (IsPlayerJumping()) {
			OnUpdatePlayerJumpStart();
			OnRenderPlayerJumpStart();
		}
		else {
			OnRenderPlayerIdle();
		}
		return true;
	}

	if (!IsPlayerLanding()) {
		OnUpdatePlayerJumpContinue();
		OnRenderPlayerJumpContinue();
	}
	else { /// Jump completed
		OnUpdatePlayerJumpStop();
		OnRenderPlayerJumpStop();
	}
	return true;
}

/// @brief Update player animation frame 
/// @param fTickTime Time elapsed since last frame
/// @return Always true by default
bool hPlayer::OnUpdateFrame(float fTickTime)
{
	app->frame4.UpdateFrame(fTickTime, app->GetFrameDelay());
	app->frame6.UpdateFrame(fTickTime, app->GetFrameDelay());
	app->frame8.UpdateFrame(fTickTime, app->GetFrameDelay());
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// END OF FILE ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////