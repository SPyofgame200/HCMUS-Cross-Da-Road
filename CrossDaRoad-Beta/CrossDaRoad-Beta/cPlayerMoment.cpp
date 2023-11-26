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
	return frame.StartAnimation();
}
bool cPlayerMoment::NextAnimation(bool bUpdate)
{
	bool result = frame.NextAnimation(bUpdate);
	return result;
}
bool cPlayerMoment::IsStopAnimation() const
{
	return frame.IsStopAnimation();
}

int cPlayerMoment::GetLimit() const
{
	return frame.GetLimit();
}

/// @brief Check if player is landing
/// @return True if player is landing, false otherwise
bool cPlayerMoment::IsJumpingStop() const
{
	return frame.IsStopAnimation();
}
/// @brief Check if player is safe when having collision
/// @return True if player is safe, false otherwise
bool cPlayerMoment::IsJumpingSafe() const
{
	return frame.GetAnimationID() <= GetSafeAnimationID();
}
int cPlayerMoment::GetAnimationID() const
{
	return frame.GetAnimationID();
}
bool cPlayerMoment::IsValidID(int nID) const
{
	return frame.IsValidID(nID);
}