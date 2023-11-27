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
bool cPlayerMoment::StartAnimation()
{
	return frame.GetSharedInstance().StartAnimation();
}
bool cPlayerMoment::NextAnimation(bool bUpdate)
{
	bool result = frame.GetSharedInstance().NextAnimation(bUpdate);
	return result;
}

bool cPlayerMoment::UpdateFrame(const float fTickTime, const int nFrameDelay, const float fTickRate)
{
	return frame.GetSharedInstance().UpdateFrame(fTickTime, nFrameDelay, fTickRate);
}

int cPlayerMoment::GetLimit() const
{
	return frame.GetLimit();
}

bool cPlayerMoment::IsStopAnimation() const
{
	return frame.GetSharedInstance().IsStopAnimation();
}

/// @brief Check if player is landing
/// @return True if player is landing, false otherwise
bool cPlayerMoment::IsJumpingStop() const
{
	return frame.GetSharedInstance().IsStopAnimation();
}
/// @brief Check if player is safe when having collision
/// @return True if player is safe, false otherwise
bool cPlayerMoment::IsJumpingSafe() const
{
	return frame.GetSharedInstance().GetAnimationID() <= GetSafeAnimationID();
}
int cPlayerMoment::GetAnimationID() const
{
	return frame.GetSharedInstance().GetAnimationID();
}
bool cPlayerMoment::IsValidID(int nID) const
{
	return frame.IsValidID(nID);
}