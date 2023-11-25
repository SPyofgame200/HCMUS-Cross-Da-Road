#include "hPlayerHitbox.h"
#include "hPlayerMotion.h"
#include "cPlayerAction.h"
#include "uAppConst.h"
#include "hPlayer.h"
#include <iostream>

hPlayerMotion::hPlayerMotion() : ptrPlayer(nullptr)
{

}

hPlayerMotion::hPlayerMotion(hPlayer* ptrPlayer) : ptrPlayer(nullptr)
{
	SetupTarget(ptrPlayer);
}

hPlayerMotion::~hPlayerMotion()
{
	ptrPlayer = nullptr;
	std::cerr << "hPlayerMotion::~hPlayerMotion(): Successfully destructed" << std::endl;
}

bool hPlayerMotion::SetupTarget(hPlayer* ptrPlayer)
{
	if (!ptrPlayer) {
		return false;
	}
	this->ptrPlayer = ptrPlayer;
	return true;
}

bool hPlayerMotion::MoveX(float fFactorX, int nStep) const
{
	const float fPosX = ptrPlayer->Physic().GetPlayerAnimationPositionX();
	const float fPosY = ptrPlayer->Physic().GetPlayerAnimationPositionY();
	for (int nPos = nStep; nPos >= 0; --nPos) {
		const float fPartial = (nPos == nStep ? 1.0f : static_cast<float>(nPos) / nStep);
		const float fOffsetPartialX = ptrPlayer->Physic().GetPlayerVelocityX() * fFactorX * fPartial;
		ptrPlayer->Physic().SetAnimationPosition(fPosX + fOffsetPartialX, fPosY);
		if (!ptrPlayer->Hitbox().IsBlocked() && !ptrPlayer->Physic().IsPlayerOutOfBounds()) {
			break;
		}
	}
	return true;
}

bool hPlayerMotion::MoveY(float fFactorY, int nStep)
{
	const float fPosX = ptrPlayer->Physic().GetPlayerAnimationPositionX();
	const float fPosY = ptrPlayer->Physic().GetPlayerAnimationPositionY();
	for (int nPos = nStep; nPos >= 0; --nPos) {
		const float fPartial = (nPos == nStep ? 1.0f : static_cast<float>(nPos) / nStep);
		const float fOffsetPartialY = ptrPlayer->Physic().GetPlayerVelocityY() * fFactorY * fPartial;
		ptrPlayer->Physic().SetAnimationPosition(fPosX, fPosY + fOffsetPartialY);
		if (!ptrPlayer->Hitbox().IsBlocked() && !ptrPlayer->Physic().IsPlayerOutOfBounds()) {
			break;
		}
	}
	return true;
}

bool hPlayerMotion::Move(float fFactorX, float fFactorY, float fFactorScale, int nStep)
{
	return MoveX(fFactorX * fFactorScale, nStep) && MoveY(fFactorY * fFactorScale, nStep);
}

bool hPlayerMotion::MoveLeft(float factor, bool forced)
{
	if ((forced || ptrPlayer->Action().IsMoveLeft()) && ptrPlayer->Physic().CanMoveLeft()) {
		Move(-1, 0, factor);
	}
	return true;
}

bool hPlayerMotion::MoveRight(float factor, bool forced)
{
	if ((forced || ptrPlayer->Action().IsMoveRight()) && ptrPlayer->Physic().CanMoveRight()) {
		Move(+1, 0, factor);
	}
	return true;
}

bool hPlayerMotion::MoveUp(float factor, bool forced)
{
	if ((forced || ptrPlayer->Action().IsMoveUp()) && ptrPlayer->Physic().CanMoveUp()) {
		Move(0, -1, factor);
	}
	return true;
}

bool hPlayerMotion::MoveDown(float factor, bool forced)
{
	if ((forced || ptrPlayer->Action().IsMoveDown()) && ptrPlayer->Physic().CanMoveDown()) {
		Move(0, +1, factor);
	}
	return true;
}

bool hPlayerMotion::MoveTryAll(float factor, bool forced)
{
	bool ok = true;
	ok &= MoveLeft(factor, forced);
	ok &= MoveRight(factor, forced);
	ok &= MoveUp(factor, forced);
	ok &= MoveDown(factor, forced);
	return ok;
}

bool hPlayerMotion::PlatformMoveX(float fFactorX, int nStep)
{
	const float fRealPosX = ptrPlayer->Physic().GetPlayerLogicPositionX();
	const float fRealPosY = ptrPlayer->Physic().GetPlayerLogicPositionY();
	const float fPosX = ptrPlayer->Physic().GetPlayerAnimationPositionX();
	const float fPosY = ptrPlayer->Physic().GetPlayerAnimationPositionY();
	const float fOffsetX = ptrPlayer->Physic().GetPlayerVelocityX() * fFactorX;
	for (int nPos = nStep; nPos >= 0; --nPos) {
		const float fOffsetPartialX = fOffsetX * nPos / nStep;
		ptrPlayer->Physic().SetAnimationPosition(fPosX + fOffsetPartialX, fPosY);
		ptrPlayer->Physic().SetLogicPosition(fRealPosX + fOffsetPartialX, fRealPosY);
		if (!ptrPlayer->Hitbox().IsBlocked()) {
			break;
		}
	}
	return true;
}

bool hPlayerMotion::PlatformMoveY(float fFactorY, int nStep)
{
	const float fRealPosX = ptrPlayer->Physic().GetPlayerLogicPositionX();
	const float fRealPosY = ptrPlayer->Physic().GetPlayerLogicPositionY();
	const float fPosX = ptrPlayer->Physic().GetPlayerAnimationPositionX();
	const float fPosY = ptrPlayer->Physic().GetPlayerAnimationPositionY();
	const float fOffsetY = ptrPlayer->Physic().GetPlayerVelocityY() * fFactorY;
	for (int nPos = nStep; nPos >= 0; --nPos) {
		const float fOffsetPartialY = fOffsetY * nPos / nStep;
		ptrPlayer->Physic().SetAnimationPosition(fPosX, fPosY + fOffsetPartialY);
		ptrPlayer->Physic().SetLogicPosition(fRealPosX, fRealPosY + fOffsetPartialY);
		if (!ptrPlayer->Hitbox().IsBlocked()) {
			break;
		}
	}
	return true;
}

bool hPlayerMotion::PlatformDetector(int nStep, float fFactor)
{
	if (ptrPlayer->Action().IsMoveRight() && ptrPlayer->IsKilled()) {
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
	if (!ptrPlayer->Action().IsMoveLeft() && ptrPlayer->IsKilled()) {
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

bool hPlayerMotion::PlatformDetector(int nCellSize)
{
	return PlatformDetector(nCellSize, 1.0f / nCellSize);
}

bool hPlayerMotion::PlatformDetector()
{
	return PlatformDetector(app_const::CELL_SIZE);
}


bool hPlayerMotion::PlatformMove(float fFactorX, float fFactorY, float fFactorScale, int nStep)
{
	return PlatformMoveX(fFactorX * fFactorScale, nStep) && PlatformMoveY(fFactorY * fFactorScale, nStep);
}
