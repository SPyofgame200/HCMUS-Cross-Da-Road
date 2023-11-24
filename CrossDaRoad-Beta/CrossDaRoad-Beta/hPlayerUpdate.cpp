#include "hPlayerUpdate.h"
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
