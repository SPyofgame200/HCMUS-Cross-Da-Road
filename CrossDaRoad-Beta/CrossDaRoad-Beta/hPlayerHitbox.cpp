#include "hPlayerHitbox.h"
#include "cAssetManager.h"
#include "cFrameManager.h"
#include "uAppConst.h"
#include "hPlayer.h"
#include <iostream>

hPlayerHitbox::hPlayerHitbox() : ptrPlayer(nullptr)
{

}

hPlayerHitbox::hPlayerHitbox(hPlayer* ptrPlayer) : ptrPlayer(nullptr)
{
	SetupTarget(ptrPlayer);
}

hPlayerHitbox::~hPlayerHitbox()
{
	ptrPlayer = nullptr;
	std::cerr << "hPlayerHitbox::~hPlayerHitbox(): Successfully destructed" << std::endl;
}

bool hPlayerHitbox::SetupTarget(hPlayer* ptrPlayer)
{
	if (!ptrPlayer) {
		return false;
	}
	this->ptrPlayer = ptrPlayer;
	return true;
}
