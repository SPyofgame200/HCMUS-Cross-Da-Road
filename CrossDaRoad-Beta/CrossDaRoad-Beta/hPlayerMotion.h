#ifndef H_PLAYER_MOTION_H
#define H_PLAYER_MOTION_H

// forward declaration
class hPlayer;

class hPlayerMotion
{
private: // Dependency
	hPlayer* ptrPlayer;

public: // Constructors & Destructor
	hPlayerMotion();
	hPlayerMotion(hPlayer* ptrPlayer);
	~hPlayerMotion();

public: // Initializer & Clean-up
	bool SetupTarget(hPlayer* ptrPlayer);

public: /// Positional Move
	bool MoveX(float fFactorX, int nStep = 16) const;
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

#endif // H_PLAYER_MOTION_H
