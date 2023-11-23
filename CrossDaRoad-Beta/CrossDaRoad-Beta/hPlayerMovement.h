#ifndef H_PLAYER_MOVEMENT_H
#define H_PLAYER_MOVEMENT_H

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

private: // Initializer & Clean-up
	bool SetupTarget(hPlayer* ptrPlayer);
};

#endif H_PLAYER_MOVEMENT_H
