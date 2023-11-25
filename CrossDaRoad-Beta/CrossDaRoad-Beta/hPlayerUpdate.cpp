#include "hPlayerUpdate.h"
#include "hPlayerMotion.h"
#include "cFrameManager.h"
#include "hPlayer.h"

//=================================================================================================
// Include new header files here

//=================================================================================================

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
	ptrPlayer->Physic().SynchronizePosition();
	return true;
}

/// @brief Update animation when player start jumping
/// @return True if player animation is updated, false otherwise
bool hPlayerUpdate::OnUpdatePlayerJumpStart()
{
	if (ptrPlayer->Status().IsMoveLeft()) {
		ptrPlayer->Status().SetAnimation(PlayerAnimation::JUMP);
		ptrPlayer->Status().SetDirection(PlayerDirection::LEFT);
	}
	else if (ptrPlayer->Status().IsMoveRight()) {
		ptrPlayer->Status().SetAnimation(PlayerAnimation::JUMP);
		ptrPlayer->Status().SetDirection(PlayerDirection::RIGHT);
	}
	else if (ptrPlayer->Status().IsMoveUp()) {
		ptrPlayer->Status().SetAnimation(PlayerAnimation::JUMP);
		if (ptrPlayer->Status().IsLeftDirection()) {
			ptrPlayer->Status().SetDirection(PlayerDirection::LEFT_UP);
		}
		else {
			ptrPlayer->Status().SetDirection(PlayerDirection::RIGHT_UP);
		}
	}
	else if (ptrPlayer->Status().IsMoveDown()) {
		ptrPlayer->Status().SetAnimation(PlayerAnimation::JUMP);
		if (ptrPlayer->Status().IsLeftDirection()) {
			ptrPlayer->Status().SetDirection(PlayerDirection::LEFT_DOWN);
		}
		else {
			ptrPlayer->Status().SetDirection(PlayerDirection::RIGHT_DOWN);
		}
	}
	ptrPlayer->Physic().SynchronizePosition();
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
	ptrPlayer->Physic().OnFixPlayerPosition();
	ptrPlayer->Physic().SynchronizePosition();
	if (ptrPlayer->Status().GetAnimation() == PlayerAnimation::JUMP) {
		ptrPlayer->Status().SetAnimation(PlayerAnimation::IDLE);
		return true;
	}
	return false;
}

bool hPlayerUpdate::OnUpdate()
{
	if (ptrPlayer->IsPlayerIdling()) {
		return OnUpdatePlayerIdle();
	}
	if (ptrPlayer->IsPlayerStartingJump()) {
		return OnUpdatePlayerJumpStart();
	}
	if (!ptrPlayer->IsPlayerLanding()) {
		return OnUpdatePlayerJumpContinue();
	}
	else { /// Jump completed
		return OnUpdatePlayerJumpStop();
	}
	return false;
}