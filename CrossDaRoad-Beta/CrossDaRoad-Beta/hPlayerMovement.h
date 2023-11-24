#ifndef H_PLAYER_MOVEMENT_H
#define H_PLAYER_MOVEMENT_H

// forward declaration
class hPlayer;

class hPlayerMovement
{
private: // Dependency
	hPlayer* ptrPlayer;

public: // Constructors & Destructor
	hPlayerMovement();
	hPlayerMovement(hPlayer* ptrPlayer);
	~hPlayerMovement();

public: // Initializer & Clean-up
	bool SetupTarget(hPlayer* ptrPlayer);

public: /// Positional Move
	bool MoveX(float fFactorX, int nStep = 16);
	bool MoveY(float fFactorX, int nStep = 16);
	bool Move(float fFactorX, float fFactorY, float fFactorScale = 1, int nStep = 16);

public: /// Directional Move
	bool MoveLeft(float factor = 1, bool forced = false);
	bool MoveRight(float factor = 1, bool forced = false);
	bool MoveUp(float factor = 1, bool forced = false);
	bool MoveDown(float factor = 1, bool forced = false);
	bool MoveTryAll(float factor = 1, bool forced = false);

public: // Dependent Move
	bool PlatformMoveX(float fFactorX, int nStep = 16);
	bool PlatformMoveY(float fFactorY, int nStep = 16);
	bool PlatformDetector(int nStep, float fFactor);
	bool PlatformDetector(int nCellSize);
	bool PlatformDetector();
	bool PlatformMove(float fFactorX, float fFactorY, float fFactorScale = 1, int nStep = 16);
};

#endif H_PLAYER_MOVEMENT_H
