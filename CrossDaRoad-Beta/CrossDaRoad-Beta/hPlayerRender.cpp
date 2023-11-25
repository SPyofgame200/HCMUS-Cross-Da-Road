#include "hPlayerRender.h"
#include "cAssetManager.h"
#include "cFrameManager.h"
#include "hPlayer.h"

//=================================================================================================
// Include new header files here

//=================================================================================================

hPlayerRender::hPlayerRender() : ptrPlayer(nullptr)
{

}

hPlayerRender::hPlayerRender(hPlayer* ptrPlayer) : ptrPlayer(nullptr)
{
	SetupTarget(ptrPlayer);
}

hPlayerRender::~hPlayerRender()
{
	ptrPlayer = nullptr;
	std::cerr << "hPlayerRender::~hPlayerRender(): Successfully destructed" << std::endl;
}

bool hPlayerRender::SetupTarget(hPlayer* ptrPlayer)
{
	if (!ptrPlayer) {
		return false;
	}
	this->ptrPlayer = ptrPlayer;
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// PLAYER RENDERER ///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool hPlayerRender::OnRenderPlayerIdle() const
{
	OnRenderPlayer();
	return true;
}

bool hPlayerRender::OnRenderPlayerJumpStart() const
{
	OnRenderPlayer();
	return true;
}

bool hPlayerRender::OnRenderPlayerJumpContinue() const
{
	OnRenderPlayer();
	return true;
}

bool hPlayerRender::OnRenderPlayerJumpStop() const
{
	OnRenderPlayer();
	return true;
}

/// @brief Render player animation to screen
/// @return Always true by default
bool hPlayerRender::OnRenderPlayer() const
{
	const int nID = cFrameManager::GetFrame6().GetAnimationID();
	const bool isValidID = cFrameManager::GetFrame6().IsValidID(nID);
	const bool isLeft = (ptrPlayer->Status().IsLeftDirection());
	const bool isJump = (ptrPlayer->Status().IsJumpAnimation()) && (isValidID);
	const std::string sPlayerState = std::string(isJump ? "_jump" : "");
	const std::string sPlayerDirection = std::string(isLeft ? "_left" : "");
	const std::string sPlayerID = (isJump ? std::to_string(nID) : "");
	const std::string sPlayerName = "froggy" + sPlayerState + sPlayerDirection + sPlayerID;
	ptrPlayer->Draw(sPlayerName);
	return true;
}

/// @brief Render player death animation to screen
/// @return Always true by default
bool hPlayerRender::OnRenderPlayerDeath()
{
	for (int id = 1; id <= 6; ++id) {
		const std::string sPlayerName = "froggy_death" + std::to_string(id);;
		const auto froggy = cAssetManager::GetInstance().GetSprite(sPlayerName);
		ptrPlayer->Draw(sPlayerName, true, true);
		ptrPlayer->Sleep(100);
	}
	ptrPlayer->Reset();
	return true;
}

bool hPlayerRender::OnRender()
{
	if (ptrPlayer->Status().IsPlayerIdling()) {
		return OnRenderPlayerIdle();
	}
	if (ptrPlayer->Status().IsPlayerStartingJump()) {
		return OnRenderPlayerJumpStart();
	}
	if (!ptrPlayer->IsPlayerLanding()) {
		return OnRenderPlayerJumpContinue();
	}
	else { /// Jump completed
		return OnRenderPlayerJumpStop();
	}
	return false;
}

/// @brief Check if player is safe when having collision
/// @return True if player is safe, false otherwise
bool hPlayerRender::IsCollisionSafe() const
{
	return cFrameManager::GetFrame6().GetAnimationID() <= ptrPlayer->Record().GetSafeAnimationID();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// LOGIC-RENDER CONTROL /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
