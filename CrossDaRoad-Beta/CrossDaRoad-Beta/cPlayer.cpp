#include "cPlayer.h"
#include "cZone.h"
#include "cApp.h"
#include "uAppConst.h"

/**
 * @file cPlayer.cpp
 *
 * @brief Contains player class implementation
 *
 * This file implements player class for player management, movement, and rendering.
**/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// CONSTRUCTORS & DESTRUCTOR ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Default constructor
cPlayer::cPlayer()
{
	Reset();
}

/// @brief Constructor with app pointer
cPlayer::cPlayer(cApp* app)
{
	SetupTarget(app);
	Reset();
}

/// @brief Destructor
cPlayer::~cPlayer()
{
	// No, we are not deleting anything, cApp* app is controlled by cApp
	app = nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// RESETTERS /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Reset player direction
void cPlayer::ResetDirection()
{
	eDirection = RIGHT;
	eAnimation = IDLE;
}
/// @brief Reset player animation
void cPlayer::ResetAnimation()
{
	frame4_id = 0;
	frame4_id_limit = 4;
	frame4_val = 0;

	frame6_id = 0;
	frame6_id_limit = 6;
	frame6_val = 0;

	frame6_id_animation = 0;
	frame6_id_animation_safe = 6;
	/// todo: id_safe for background detection is high (6)
	///           but for deadly objects is smaller for friendly jump
	frame6_val_animation_cur = 0;
	frame6_val_animation_last = 0;
}
/// @brief Reset player position
void cPlayer::ResetPosition()
{
	fFrogAnimPosX = app_const::FROG_X_RESET;
	fFrogAnimPosY = app_const::FROG_Y_RESET;
	fFrogLogicPosX = app_const::FROG_X_RESET;
	fFrogLogicPosY = app_const::FROG_Y_RESET;
}
/// @brief Reset player velocity
void cPlayer::ResetVelocity()
{
	fFrogVelocityX = app_const::FROG_X_VELOCITY;
	fFrogVelocityY = app_const::FROG_Y_VELOCITY;
}
/// @brief Reset player properties
void cPlayer::Reset()
{
	ResetDirection();
	ResetAnimation();
	ResetPosition();
	ResetVelocity();
}
/// @brief Setup app pointer
/// @param app Pointer to app
void cPlayer::SetupTarget(cApp* app)
{
	this->app = app;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// CHECKERS /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Check if player is facing exact direction
/// @param eCompare Direction to compare
/// @return True if player is facing exact direction, false otherwise
bool cPlayer::IsExactDirection(Direction eCompare) const
{
	return eDirection == eCompare;
}

bool cPlayer::IsExactAnimation(Animation eCompare) const
{
	return eAnimation == eCompare;
}

bool cPlayer::IsLeftDirection() const
{
	return (eDirection == LEFT)
		|| (eDirection == LEFT_UP)
		|| (eDirection == LEFT_DOWN);
}

bool cPlayer::IsRightDirection() const
{
	return (eDirection == RIGHT)
		|| (eDirection == RIGHT_UP)
		|| (eDirection == RIGHT_DOWN);
}

bool cPlayer::IsPlayerJumping() const
{
	return (GetAnimation() == JUMP);
}

bool cPlayer::IsPlayerIdling() const
{
	return (GetAnimation() == IDLE);
}

bool cPlayer::IsPlayerLanding() const
{
	return frame6_id_animation > frame6_id_limit;
}

bool cPlayer::IsPlayerCollisionSafe() const
{
	return frame6_id_animation <= frame6_id_animation_safe;
}
/// @brief Check if player is out of bounds of map border
bool cPlayer::IsPlayerOutOfBounds() const
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
bool cPlayer::IsHitTopLeft() const
{
	const float fPosX = GetPlayerLogicPositionX();
	const float fPosY = GetPlayerLogicPositionY();
	const bool isHitTopLeft = app->Zone.IsDangerTopLeft(fPosX, fPosY, app_const::CELL_SIZE);
	return isHitTopLeft;
}
/// @brief Check if player is hit by danger zone at top right corner
bool cPlayer::IsHitTopRight() const
{
	const float fPosX = GetPlayerLogicPositionX();
	const float fPosY = GetPlayerLogicPositionY();
	const bool isHitTopRight = app->Zone.IsDangerTopRight(fPosX, fPosY, app_const::CELL_SIZE);
	return isHitTopRight;
}
/// @brief Check if player is hit by danger zone at bottom left corner
bool cPlayer::IsHitBottomLeft() const
{
	const float fPosX = GetPlayerLogicPositionX();
	const float fPosY = GetPlayerLogicPositionY();
	const bool isHitBottomLeft = app->Zone.IsDangerBottomLeft(fPosX, fPosY, app_const::CELL_SIZE);
	return isHitBottomLeft;
}
/// @brief Check if player is hit by danger zone at bottom right corner
bool cPlayer::IsHitBottomRight() const
{
	const float fPosX = GetPlayerLogicPositionX();
	const float fPosY = GetPlayerLogicPositionY();
	const bool isHitBottomRight = app->Zone.IsDangerBottomRight(fPosX, fPosY, app_const::CELL_SIZE);
	return isHitBottomRight;
}
/// @brief Check if player is hit by danger zone
bool cPlayer::IsHit() const
{
	return IsHitTopLeft()
		|| IsHitTopRight()
		|| IsHitBottomLeft()
		|| IsHitBottomRight();
}
/// @brief Check if player is blocked by block zone at top left corner
bool cPlayer::IsBlockedTopLeft() const
{
	const float fPosX = GetPlayerAnimationPositionX();
	const float fPosY = GetPlayerAnimationPositionY();
	const bool isBlockedTopLeft = app->Zone.IsBlockedTopLeft(fPosX, fPosY, app_const::CELL_SIZE);
	return isBlockedTopLeft;
}
/// @brief Check if player is blocked by block zone at top right corner
bool cPlayer::IsBlockedTopRight() const
{
	const float fPosX = GetPlayerAnimationPositionX();
	const float fPosY = GetPlayerAnimationPositionY();
	const bool isBlockedTopRight = app->Zone.IsBlockedTopRight(fPosX, fPosY, app_const::CELL_SIZE);
	return isBlockedTopRight;
}
/// @brief Check if player is blocked by block zone at bottom left corner
bool cPlayer::IsBlockedBottomLeft() const
{
	const float fPosX = GetPlayerAnimationPositionX();
	const float fPosY = GetPlayerAnimationPositionY();
	const bool isBlockedBottomLeft = app->Zone.IsBlockedBottomLeft(fPosX, fPosY, app_const::CELL_SIZE);
	return isBlockedBottomLeft;
}
/// @brief Check if player is blocked by block zone at bottom right corner
bool cPlayer::IsBlockedBottomRight() const
{
	const float fPosX = GetPlayerAnimationPositionX();
	const float fPosY = GetPlayerAnimationPositionY();
	const bool isBlockedBottomRight = app->Zone.IsBlockedBottomRight(fPosX, fPosY, app_const::CELL_SIZE);
	return isBlockedBottomRight;
}
/// @brief Check if player is blocked by block zone
bool cPlayer::IsBlocked() const
{
	return IsBlockedTopLeft()
		|| IsBlockedTopRight()
		|| IsBlockedBottomLeft()
		|| IsBlockedBottomRight();
}
/// @brief Check if player is win (go to next level)
bool cPlayer::IsPlayerWin() const
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
bool cPlayer::CanMoveLeft() const
{
	return fFrogAnimPosX > app_const::LEFT_BORDER;
}
/// @brief Check if player can move right
bool cPlayer::CanMoveRight() const
{
	return fFrogAnimPosX < app_const::RIGHT_BORDER;
}
/// @brief Check if player can move up
bool cPlayer::CanMoveUp() const
{
	return fFrogAnimPosY > app_const::TOP_BORDER;
}
/// @brief Check if player can move down
bool cPlayer::CanMoveDown() const
{
	return fFrogAnimPosY < app_const::BOTTOM_BORDER;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// GETTERS ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

cPlayer::Direction cPlayer::GetDirection() const
{
	return eDirection;
}

cPlayer::Animation cPlayer::GetAnimation() const
{
	return eAnimation;
}

int cPlayer::GetFrameID(const frame_t frame) const
{
	if (frame == frame4_id_limit) {
		return frame4_id;
	}
	else if (frame == frame6_id_limit) {
		return frame6_id_animation;
	}
	return 0;
}

std::string cPlayer::ShowFrameID(const frame_t frame) const
{
	return std::to_string(GetFrameID(frame));
}

float cPlayer::GetPlayerAnimationPositionX() const
{
	return fFrogAnimPosX;
}

float cPlayer::GetPlayerAnimationPositionY() const
{
	return fFrogAnimPosY;
}

float cPlayer::GetPlayerLogicPositionX() const
{
	return fFrogLogicPosX;
}

float cPlayer::GetPlayerLogicPositionY() const
{
	return fFrogLogicPosY;
}

float cPlayer::GetPlayerVelocityX() const
{
	return fFrogVelocityX;
}

float cPlayer::GetPlayerVelocityY() const
{
	return fFrogVelocityY;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// SETTERS ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// Make the float [fValue] to only care about first [nDigits] digits after decimal points, others remain closest to ,...00000
float cPlayer::FixFloat(float fValue, int nDigits)
{
	return ldexpf(roundf(ldexpf(fValue, nDigits)), -nDigits);
}

void cPlayer::SetDirection(Direction eNewDirection)
{
	eDirection = eNewDirection;
}

void cPlayer::SetAnimation(Animation eNewAnimation)
{
	eAnimation = eNewAnimation;
}

void cPlayer::SetPlayerVelocityX(float fVelocityX)
{
	fFrogVelocityX = FixFloat(fVelocityX);
}

void cPlayer::SetPlayerVelocityY(float fVelocityY)
{
	fFrogVelocityY = FixFloat(fVelocityY);
}

void cPlayer::SetPlayerVelocity(float fVelocityX, float fVelocityY)
{
	SetPlayerVelocityX(fVelocityX);
	SetPlayerVelocityY(fVelocityY);
}

void cPlayer::SetPlayerAnimationPositionX(float fPositionX)
{
	fFrogAnimPosX = FixFloat(fPositionX);
}

void cPlayer::SetPlayerAnimationPositionY(float fPositionY)
{
	fFrogAnimPosY = FixFloat(fPositionY);
}

void cPlayer::SetPlayerAnimationPosition(float fPositionX, float fPositionY)
{
	SetPlayerAnimationPositionX(fPositionX);
	SetPlayerAnimationPositionY(fPositionY);
}

void cPlayer::SetPlayerLogicPositionX(float fPositionX)
{
	fFrogLogicPosX = FixFloat(fPositionX);
}

void cPlayer::SetPlayerLogicPositionY(float fPositionY)
{
	fFrogLogicPosY = FixFloat(fPositionY);
}

void cPlayer::SetPlayerLogicPosition(float fPositionX, float fPositionY)
{
	SetPlayerLogicPositionX(fPositionX);
	SetPlayerLogicPositionY(fPositionY);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// MOVEMENTS ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool cPlayer::PlayerMoveX(float fFactorX, int nStep)
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

bool cPlayer::PlayerMoveY(float fFactorY, int nStep)
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
bool cPlayer::PlayerMove(float fFactorX, float fFactorY, float fFactorScale, int nStep)
{
	return PlayerMoveX(fFactorX * fFactorScale, nStep)
		&& PlayerMoveY(fFactorY * fFactorScale, nStep);
}
/// @brief Check if Player successfully moved left (by key released)
bool cPlayer::PlayerMoveLeft(float factor, bool forced)
{
	if ((forced || app->IsMoveLeft()) && CanMoveLeft()) {
		PlayerMove(-1, 0, factor);
	}
	return true;
}
/// @brief Check if Player successfully moved right (by key released)
bool cPlayer::PlayerMoveRight(float factor, bool forced)
{
	if ((forced || app->IsMoveRight()) && CanMoveRight()) {
		PlayerMove(+1, 0, factor);
	}
	return true;
}
/// @brief Check if Player successfully moved up (by key released)
bool cPlayer::PlayerMoveUp(float factor, bool forced)
{
	if ((forced || app->IsMoveUp()) && CanMoveUp()) {
		PlayerMove(0, -1, factor);
	}
	return true;
}
//// @brief Check if Player successfully moved down (by key released)
bool cPlayer::PlayerMoveDown(float factor, bool forced)
{
	if ((forced || app->IsMoveDown()) && CanMoveDown()) {
		PlayerMove(0, +1, factor);
	}
	return true;
}
/// @brief Check if Player successfully moved (by key released)
bool cPlayer::PlayerMoveTryAll(float factor, bool forced)
{
	bool ok = true;
	ok &= PlayerMoveLeft(factor, forced);
	ok &= PlayerMoveRight(factor, forced);
	ok &= PlayerMoveUp(factor, forced);
	ok &= PlayerMoveDown(factor, forced);
	return ok;
}
bool cPlayer::PlayerPlatformDetector(int nStep, float fFactor)
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
bool cPlayer::PlayerPlatformMoveX(float fFactorX, int nStep)
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
bool cPlayer::PlayerPlatformMoveY(float fFactorY, int nStep)
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
bool cPlayer::PlayerPlatformMove(float fFactorX, float fFactorY, float fFactorScale, int nStep)
{
	return PlayerPlatformMoveX(fFactorX * fFactorScale) && PlayerPlatformMoveY(fFactorY * fFactorScale);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// LOGIC UPDATES ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool cPlayer::OnUpdatePlayerLane()
{
	const float fFixedX = std::clamp(FixFloat(GetPlayerAnimationPositionX(), 1), app_const::LEFT_BORDER, app_const::RIGHT_BORDER);
	const float fFixedY = std::clamp(FixFloat(GetPlayerAnimationPositionY(), 1), app_const::TOP_BORDER, app_const::BOTTOM_BORDER);
	SetPlayerAnimationPosition(fFixedX, fFixedY);
	return true;
}

bool cPlayer::OnUpdatePlayerJumpContinue()
{
	if (GetAnimation() == IDLE) {
		return false;
	}
	if (frame6_val_animation_cur < frame6_val) {
		frame6_val_animation_cur = frame6_val;
		if (GetDirection() == LEFT) {
			if (!PlayerMoveLeft(1.0f / frame6_id_limit, true)) {
				return false;
			}
		}
		else if (GetDirection() == RIGHT) {
			if (!PlayerMoveRight(1.0f / frame6_id_limit, true)) {
				return false;
			}
		}
		else if (GetDirection() == LEFT_UP || GetDirection() == RIGHT_UP) {
			if (!PlayerMoveUp(1.0f / frame6_id_limit, true)) {
				return false;
			}
		}
		else if (GetDirection() == LEFT_DOWN || GetDirection() == RIGHT_DOWN) {
			if (!PlayerMoveDown(1.0f / frame6_id_limit, true)) {
				return false;
			}
		}
	}
	return true;
}

bool cPlayer::OnUpdatePlayerJumpStop()
{
	std::cerr << "Stop" << std::endl;
	OnUpdatePlayerLane();
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

bool cPlayer::OnRenderPlayerIdle()
{
	SetPlayerLogicPosition(fFrogAnimPosX, fFrogAnimPosY);
	OnRenderPlayer();
	return true;
}

bool cPlayer::OnRenderPlayerJumpStart()
{
	frame6_val_animation_last = frame6_val;
	frame6_id_animation = (frame6_val - frame6_val_animation_last + 1);
	SetPlayerLogicPosition(fFrogAnimPosX, fFrogAnimPosY);
	OnRenderPlayer();
	return true;
}

bool cPlayer::OnRenderPlayerJumpContinue()
{
	frame6_id_animation = (frame6_val - frame6_val_animation_last + 1);
	OnRenderPlayer();
	return true;
}

bool cPlayer::OnRenderPlayerJumpStop() const
{
	OnRenderPlayer();
	return true;
}

bool cPlayer::OnRenderPlayer() const
{
	const bool isValidID = (1 <= frame6_id_animation && frame6_id_animation <= frame6_id_limit);
	const bool isLeft = (IsLeftDirection());
	const bool isJump = (IsPlayerJumping()) && (isValidID);
	const std::string froggy_state = std::string(isJump ? "_jump" : "");
	const std::string froggy_direction = std::string(isLeft ? "_left" : "");
	const std::string froggy_id = (isJump ? std::to_string(frame6_id_animation) : "");
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

bool cPlayer::OnRenderPlayerDeath()
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

bool cPlayer::OnPlayerMove()
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

bool cPlayer::OnUpdateFrame(float fTickTime)
{
	frame4_val = static_cast<int>(std::floor(fTickTime / (0.0006f * 1000000 / app->GetFrameDelay())));
	frame6_val = static_cast<int>(std::floor(fTickTime / (0.0004f * 1000000 / app->GetFrameDelay())));
	frame4_id = frame4_val % frame4_id_limit + 1;
	frame6_id = frame6_val % frame6_id_limit + 1;
	return true;
}

bool cPlayer::AddExtraFrame(int nExtra)
{
	frame6_val_animation_last += nExtra;
	frame6_val_animation_cur += nExtra;
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// END OF FILE ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////