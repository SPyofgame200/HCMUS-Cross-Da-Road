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

