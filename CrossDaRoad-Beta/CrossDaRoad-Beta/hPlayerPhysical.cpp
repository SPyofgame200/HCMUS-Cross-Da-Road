#include "hPlayerPhysical.h"
#include "cAssetManager.h"
#include "cFrameManager.h"
#include "uAppConst.h"
#include "hPlayer.h"
#include <iostream>

hPlayerPhysical::hPlayerPhysical() : ptrPlayer(nullptr)
{

}

hPlayerPhysical::hPlayerPhysical(hPlayer* ptrPlayer) : ptrPlayer(nullptr)
{
	SetupTarget(ptrPlayer);
}

hPlayerPhysical::~hPlayerPhysical()
{
	ptrPlayer = nullptr;
	std::cerr << "hPlayerPhysical::~hPlayerPhysical(): Successfully destructed" << std::endl;
}

bool hPlayerPhysical::SetupTarget(hPlayer* ptrPlayer)
{
	if (!ptrPlayer) {
		return false;
	}
	this->ptrPlayer = ptrPlayer;
	return true;
}
