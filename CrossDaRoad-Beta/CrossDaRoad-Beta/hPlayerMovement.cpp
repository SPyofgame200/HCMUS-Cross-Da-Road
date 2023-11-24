#include "hPlayerMovement.h"
#include "uAppConst.h"
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

bool hPlayerMovement::MoveX(float fFactorX, int nStep)
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

bool hPlayerMovement::MoveY(float fFactorY, int nStep)
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

bool hPlayerMovement::Move(float fFactorX, float fFactorY, float fFactorScale, int nStep)
{
	return MoveX(fFactorX * fFactorScale, nStep) && MoveY(fFactorY * fFactorScale, nStep);
}

bool hPlayerMovement::MoveLeft(float factor, bool forced)
{
	if ((forced || ptrPlayer->IsMoveLeft()) && ptrPlayer->CanMoveLeft()) {
		Move(-1, 0, factor);
	}
	return true;
}

bool hPlayerMovement::MoveRight(float factor, bool forced)
{
	if ((forced || ptrPlayer->IsMoveRight()) && ptrPlayer->CanMoveRight()) {
		Move(+1, 0, factor);
	}
	return true;
}

bool hPlayerMovement::MoveUp(float factor, bool forced)
{
	if ((forced || ptrPlayer->IsMoveUp()) && ptrPlayer->CanMoveUp()) {
		Move(0, -1, factor);
	}
	return true;
}

bool hPlayerMovement::MoveDown(float factor, bool forced)
{
	if ((forced || ptrPlayer->IsMoveDown()) && ptrPlayer->CanMoveDown()) {
		Move(0, +1, factor);
	}
	return true;
}

bool hPlayerMovement::MoveTryAll(float factor, bool forced)
{
	bool ok = true;
	ok &= MoveLeft(factor, forced);
	ok &= MoveRight(factor, forced);
	ok &= MoveUp(factor, forced);
	ok &= MoveDown(factor, forced);
	return ok;
}

bool hPlayerMovement::PlatformMoveX(float fFactorX, int nStep)
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

bool hPlayerMovement::PlatformMoveY(float fFactorY, int nStep)
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

bool hPlayerMovement::PlatformDetector(int nStep, float fFactor)
{
	if (ptrPlayer->IsMoveRight() && ptrPlayer->IsKilled()) {
		for (int step = 1; step <= nStep; ++step) {
			MoveRight(fFactor, true);
			if (!ptrPlayer->IsKilled()) {
				return false;
			}
		}
		for (int step = 1; step <= nStep; ++step) {
			MoveLeft(fFactor, true);
			if (!ptrPlayer->IsKilled()) {
				return false;
			}
		}
	}
	if (!ptrPlayer->IsMoveLeft() && ptrPlayer->IsKilled()) {
		for (int step = 1; step <= nStep; ++step) {
			MoveLeft(fFactor, true);
			if (!ptrPlayer->IsKilled()) {
				return false;
			}
		}
		for (int step = 1; step <= nStep; ++step) {
			MoveRight(fFactor, true);
			if (!ptrPlayer->IsKilled()) {
				return false;
			}
		}
	}
	return true;
}

bool hPlayerMovement::PlatformDetector(int nCellSize)
{
	return PlatformDetector(nCellSize, 1.0f / nCellSize);
}

bool hPlayerMovement::PlatformDetector()
{
	return PlatformDetector(app_const::CELL_SIZE);
}


bool hPlayerMovement::PlatformMove(float fFactorX, float fFactorY, float fFactorScale, int nStep)
{
	return PlatformMoveX(fFactorX * fFactorScale, nStep) && PlatformMoveY(fFactorY * fFactorScale, nStep);
}
