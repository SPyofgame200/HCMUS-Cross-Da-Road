#ifndef H_PLAYER_MOVEMENT_H
#define H_PLAYER_MOVEMENT_H

#include "uAppConst.h"
// forward declaration
class hPlayer;

class hPlayerMovement
{
private:
	hPlayer* ptrPlayer;

public: // Constructors & Destructor
	hPlayerMovement();
	hPlayerMovement(hPlayer* ptrPlayer);
	~hPlayerMovement();

public: // Initializer & Clean-up
	bool SetupTarget(hPlayer* ptrPlayer);
	bool PlayerMoveX(float fFactorX, int nStep = 16);
	bool PlayerMoveY(float fFactorX, int nStep = 16);
	bool PlayerMove(float fFactorX, float fFactorY, float fFactorScale = 1, int nStep = 16);
	bool PlayerMoveLeft(float factor = 1, bool forced = false);
	bool PlayerMoveRight(float factor = 1, bool forced = false);
	bool PlayerMoveUp(float factor = 1, bool forced = false);
	bool PlayerMoveDown(float factor = 1, bool forced = false);
	bool PlayerMoveTryAll(float factor = 1, bool forced = false);
	bool PlayerPlatformMoveX(float fFactorX, int nStep = 16);
	bool PlayerPlatformMoveY(float fFactorY, int nStep = 16);
	bool PlayerPlatformDetector(int nStep = app_const::CELL_SIZE, float fFactor = 1.0f / app_const::CELL_SIZE);
	bool PlayerPlatformMove(float fFactorX, float fFactorY, float fFactorScale = 1, int nStep = 16);
};

#endif H_PLAYER_MOVEMENT_H
