#include "hPlayerMovement.h"
#include "hPlayer.h"
#include <iostream>

hPlayerMovement::hPlayerMovement() : ptrPlayer(nullptr)
{

}

hPlayerMovement::hPlayerMovement(hPlayer* ptrPlayer) : ptrPlayer(nullptr)
{
	SetupTarget(ptrPlayer);
}

hPlayerMovement::~hPlayerMovement()
{
	ptrPlayer = nullptr;
	std::cerr << "hPlayerMovement::~hPlayerMovement(): Successfully destructed" << std::endl;
}

bool hPlayerMovement::SetupTarget(hPlayer* ptrPlayer)
{
	if (!ptrPlayer) {
		return false;
	}
	this->ptrPlayer = ptrPlayer;
	return true;
}

bool hPlayerMovement::PlayerMoveX(float fFactorX, int nStep)
{
	const float fPosX = ptrPlayer->GetPlayerAnimationPositionX();
	const float fPosY = ptrPlayer->GetPlayerAnimationPositionY();
	for (int nPos = nStep; nPos >= 0; --nPos) {
		const float fPartial = (nPos == nStep ? 1.0f : static_cast<float>(nPos) / nStep);
		const float fOffsetPartialX = ptrPlayer->GetPlayerVelocityX() * fFactorX * fPartial;
		ptrPlayer->SetPlayerAnimationPosition(fPosX + fOffsetPartialX, fPosY);
		if (!ptrPlayer->IsBlocked() && !ptrPlayer->IsPlayerOutOfBounds()) {
			break;
		}
	}
	return true;
}

bool hPlayerMovement::PlayerMoveY(float fFactorY, int nStep)
{
	const float fPosX = ptrPlayer->GetPlayerAnimationPositionX();
	const float fPosY = ptrPlayer->GetPlayerAnimationPositionY();
	for (int nPos = nStep; nPos >= 0; --nPos) {
		const float fPartial = (nPos == nStep ? 1.0f : static_cast<float>(nPos) / nStep);
		const float fOffsetPartialY = ptrPlayer->GetPlayerVelocityY() * fFactorY * fPartial;
		ptrPlayer->SetPlayerAnimationPosition(fPosX, fPosY + fOffsetPartialY);
		if (!ptrPlayer->IsBlocked() && !ptrPlayer->IsPlayerOutOfBounds()) {
			break;
		}
	}
	return true;
}

bool hPlayerMovement::PlayerMove(float fFactorX, float fFactorY, float fFactorScale, int nStep)
{
	return PlayerMoveX(fFactorX * fFactorScale, nStep) && PlayerMoveY(fFactorY * fFactorScale, nStep);
}

bool hPlayerMovement::PlayerMoveLeft(float factor, bool forced)
{
	if ((forced || ptrPlayer->IsMoveLeft()) && ptrPlayer->CanMoveLeft()) {
		PlayerMove(-1, 0, factor);
	}
	return true;
}

bool hPlayerMovement::PlayerMoveRight(float factor, bool forced)
{
	if ((forced || ptrPlayer->IsMoveRight()) && ptrPlayer->CanMoveRight()) {
		PlayerMove(+1, 0, factor);
	}
	return true;
}

bool hPlayerMovement::PlayerMoveUp(float factor, bool forced)
{
	if ((forced || ptrPlayer->IsMoveUp()) && ptrPlayer->CanMoveUp()) {
		PlayerMove(0, -1, factor);
	}
	return true;
}

bool hPlayerMovement::PlayerMoveDown(float factor, bool forced)
{
	if ((forced || ptrPlayer->IsMoveDown()) && ptrPlayer->CanMoveDown()) {
		PlayerMove(0, +1, factor);
	}
	return true;
}

bool hPlayerMovement::PlayerMoveTryAll(float factor, bool forced)
{
	bool ok = true;
	ok &= PlayerMoveLeft(factor, forced);
	ok &= PlayerMoveRight(factor, forced);
	ok &= PlayerMoveUp(factor, forced);
	ok &= PlayerMoveDown(factor, forced);
	return ok;
}

bool hPlayerMovement::PlayerPlatformDetector(int nStep, float fFactor)
{
	if (ptrPlayer->IsMoveRight() && ptrPlayer->IsKilled()) {
		for (int step = 1; step <= nStep; ++step) {
			PlayerMoveRight(fFactor, true);
			if (!ptrPlayer->IsKilled()) {
				return false;
			}
		}
		for (int step = 1; step <= nStep; ++step) {
			PlayerMoveLeft(fFactor, true);
			if (!ptrPlayer->IsKilled()) {
				return false;
			}
		}
	}
	if (!ptrPlayer->IsMoveLeft() && ptrPlayer->IsKilled()) {
		for (int step = 1; step <= nStep; ++step) {
			PlayerMoveLeft(fFactor, true);
			if (!ptrPlayer->IsKilled()) {
				return false;
			}
		}
		for (int step = 1; step <= nStep; ++step) {
			PlayerMoveRight(fFactor, true);
			if (!ptrPlayer->IsKilled()) {
				return false;
			}
		}
	}
	return true;
}

bool hPlayerMovement::PlayerPlatformMoveX(float fFactorX, int nStep)
{
	const float fRealPosX = ptrPlayer->GetPlayerLogicPositionX();
	const float fRealPosY = ptrPlayer->GetPlayerLogicPositionY();
	const float fPosX = ptrPlayer->GetPlayerAnimationPositionX();
	const float fPosY = ptrPlayer->GetPlayerAnimationPositionY();
	const float fOffsetX = ptrPlayer->GetPlayerVelocityX() * fFactorX;
	for (int nPos = nStep; nPos >= 0; --nPos) {
		const float fOffsetPartialX = fOffsetX * nPos / nStep;
		ptrPlayer->SetPlayerAnimationPosition(fPosX + fOffsetPartialX, fPosY);
		ptrPlayer->SetPlayerLogicPosition(fRealPosX + fOffsetPartialX, fRealPosY);
		if (!ptrPlayer->IsBlocked()) {
			break;
		}
	}
	return true;
}

bool hPlayerMovement::PlayerPlatformMoveY(float fFactorY, int nStep)
{
	const float fRealPosX = ptrPlayer->GetPlayerLogicPositionX();
	const float fRealPosY = ptrPlayer->GetPlayerLogicPositionY();
	const float fPosX = ptrPlayer->GetPlayerAnimationPositionX();
	const float fPosY = ptrPlayer->GetPlayerAnimationPositionY();
	const float fOffsetY = ptrPlayer->GetPlayerVelocityY() * fFactorY;
	for (int nPos = nStep; nPos >= 0; --nPos) {
		const float fOffsetPartialY = fOffsetY * nPos / nStep;
		ptrPlayer->SetPlayerAnimationPosition(fPosX, fPosY + fOffsetPartialY);
		ptrPlayer->SetPlayerLogicPosition(fRealPosX, fRealPosY + fOffsetPartialY);
		if (!ptrPlayer->IsBlocked()) {
			break;
		}
	}
	return true;
}

bool hPlayerMovement::PlayerPlatformMove(float fFactorX, float fFactorY, float fFactorScale, int nStep)
{
	return PlayerPlatformMoveX(fFactorX * fFactorScale, nStep) && PlayerPlatformMoveY(fFactorY * fFactorScale, nStep);
}
