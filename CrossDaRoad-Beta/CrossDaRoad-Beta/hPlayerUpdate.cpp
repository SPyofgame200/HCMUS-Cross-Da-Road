#include "hPlayerUpdate.h"
#include "hPlayerMotion.h"
#include "cAssetManager.h"
#include "cFrameManager.h"
#include "cPlayerStatus.h"
#include "uAppConst.h"
#include "hPlayer.h"
#include <iostream>

hPlayerUpdate::hPlayerUpdate() : ptrPlayer(nullptr)
{

}

hPlayerUpdate::hPlayerUpdate(hPlayer* ptrPlayer) : ptrPlayer(nullptr)
{
	SetupTarget(ptrPlayer);
}

hPlayerUpdate::~hPlayerUpdate()
{
	ptrPlayer = nullptr;
	std::cerr << "hPlayerUpdate::~hPlayerUpdate(): Successfully destructed" << std::endl;
}

bool hPlayerUpdate::SetupTarget(hPlayer* ptrPlayer)
{
	if (!ptrPlayer) {
		return false;
	}
	this->ptrPlayer = ptrPlayer;
	return true;
}

/// @brief Update animation when player idling
/// @return Always true by default
bool hPlayerUpdate::OnUpdatePlayerIdle()
{
	ptrPlayer->SynchronizePosition();
	return true;
}

/// @brief Update animation when player start jumping
/// @return True if player animation is updated, false otherwise
bool hPlayerUpdate::OnUpdatePlayerJumpStart()
{
	if (ptrPlayer->IsMoveLeft()) {
		ptrPlayer->Status().SetAnimation(PlayerAnimation::JUMP);
		ptrPlayer->Status().SetDirection(PlayerDirection::LEFT);
	}
	else if (ptrPlayer->IsMoveRight()) {
		ptrPlayer->Status().SetAnimation(PlayerAnimation::JUMP);
		ptrPlayer->Status().SetDirection(PlayerDirection::RIGHT);
	}
	else if (ptrPlayer->IsMoveUp()) {
		ptrPlayer->Status().SetAnimation(PlayerAnimation::JUMP);
		if (ptrPlayer->Status().IsLeftDirection()) {
			ptrPlayer->Status().SetDirection(PlayerDirection::LEFT_UP);
		}
		else {
			ptrPlayer->Status().SetDirection(PlayerDirection::RIGHT_UP);
		}
	}
	else if (ptrPlayer->IsMoveDown()) {
		ptrPlayer->Status().SetAnimation(PlayerAnimation::JUMP);
		if (ptrPlayer->Status().IsLeftDirection()) {
			ptrPlayer->Status().SetDirection(PlayerDirection::LEFT_DOWN);
		}
		else {
			ptrPlayer->Status().SetDirection(PlayerDirection::RIGHT_DOWN);
		}
	}
	ptrPlayer->SynchronizePosition();
	return cFrameManager::GetFrame6().StartAnimation();
}
/// @brief Update animation when player continue jumping
/// @return True if player animation is updated, false otherwise
bool hPlayerUpdate::OnUpdatePlayerJumpContinue() const
{
	if (ptrPlayer->Status().GetAnimation() == PlayerAnimation::IDLE) {
		return false;
	}
	if (cFrameManager::GetFrame6().NextAnimation()) {
		if (ptrPlayer->Status().GetDirection() == PlayerDirection::LEFT) {
			if (!ptrPlayer->Motion().MoveLeft(1.0f / cFrameManager::GetFrame6().GetLimit(), true)) {
				return false;
			}
		}
		else if (ptrPlayer->Status().GetDirection() == PlayerDirection::RIGHT) {
			if (!ptrPlayer->Motion().MoveRight(1.0f / cFrameManager::GetFrame6().GetLimit(), true)) {
				return false;
			}
		}
		else if (ptrPlayer->Status().GetDirection() == PlayerDirection::LEFT_UP 
			  || ptrPlayer->Status().GetDirection() == PlayerDirection::RIGHT_UP) {
			if (!ptrPlayer->Motion().MoveUp(1.0f / cFrameManager::GetFrame6().GetLimit(), true)) {
				return false;
			}
		}
		else if (ptrPlayer->Status().GetDirection() == PlayerDirection::LEFT_DOWN
			  || ptrPlayer->Status().GetDirection() == PlayerDirection::RIGHT_DOWN) {
			if (!ptrPlayer->Motion().MoveDown(1.0f / cFrameManager::GetFrame6().GetLimit(), true)) {
				return false;
			}
		}
	}
	return true;
}

/// @brief Update animation when player stop jumping
/// @return True if player animation is updated, false otherwise
bool hPlayerUpdate::OnUpdatePlayerJumpStop()
{
	ptrPlayer->SynchronizePosition();
	if (ptrPlayer->Status().GetAnimation() == PlayerAnimation::JUMP) {
		ptrPlayer->Status().SetAnimation(PlayerAnimation::IDLE);
		return true;
	}
	return false;
}