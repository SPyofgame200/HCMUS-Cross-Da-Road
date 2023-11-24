#include "hPlayerUpdate.h"
#include "hPlayerMotion.h"
#include "cAssetManager.h"
#include "cFrameManager.h"
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
	ptrPlayer->SynchronizePosition();
	return cFrameManager::GetFrame6().StartAnimation();
}
/// @brief Update animation when player continue jumping
/// @return True if player animation is updated, false otherwise
bool hPlayerUpdate::OnUpdatePlayerJumpContinue() const
{
	if (ptrPlayer->GetAnimation() == ptrPlayer->IDLE) {
		return false;
	}
	if (cFrameManager::GetFrame6().NextAnimation()) {
		if (ptrPlayer->GetDirection() == ptrPlayer->LEFT) {
			if (!ptrPlayer->Motion().MoveLeft(1.0f / cFrameManager::GetFrame6().GetLimit(), true)) {
				return false;
			}
		}
		else if (ptrPlayer->GetDirection() == ptrPlayer->RIGHT) {
			if (!ptrPlayer->Motion().MoveRight(1.0f / cFrameManager::GetFrame6().GetLimit(), true)) {
				return false;
			}
		}
		else if (ptrPlayer->GetDirection() == ptrPlayer->LEFT_UP || ptrPlayer->GetDirection() == ptrPlayer->RIGHT_UP) {
			if (!ptrPlayer->Motion().MoveUp(1.0f / cFrameManager::GetFrame6().GetLimit(), true)) {
				return false;
			}
		}
		else if (ptrPlayer->GetDirection() == ptrPlayer->LEFT_DOWN || ptrPlayer->GetDirection() == ptrPlayer->RIGHT_DOWN) {
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
	if (ptrPlayer->GetAnimation() == ptrPlayer->JUMP) {
		ptrPlayer->SetAnimation(ptrPlayer->IDLE);
		return true;
	}
	return false;
}