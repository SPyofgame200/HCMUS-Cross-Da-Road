#include "cFrameManager.h"
#include "cPlayerMoment.h"

cPlayerMoment::cPlayerMoment()
{
	Reset();
}

void cPlayerMoment::Reset()
{
	frame6_id_animation_safe = 5;
}

int cPlayerMoment::GetSafeAnimationID() const
{
	return frame6_id_animation_safe;
}

/// @brief Check if player is landing
/// @return True if player is landing, false otherwise
bool cPlayerMoment::IsPlayerLanding() const
{
	return cFrameManager::GetFrame6().IsStopAnimation();
}