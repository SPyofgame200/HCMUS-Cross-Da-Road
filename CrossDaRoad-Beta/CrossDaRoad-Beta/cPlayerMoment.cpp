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

// Implement Read and Write functions for cPlayerMoment
void cPlayerMoment::Read(std::istream& input) {
	// Read each property from the input stream
	input >> frame6_id_animation_safe;
	frame.Read(input);
}

void cPlayerMoment::Write(std::ostream& output) const {
	// Write each property to the output stream
	output << frame6_id_animation_safe << " ";
	frame.Write(output);
}

// Implement operator>> and operator<< for cPlayerMoment
std::istream& operator>>(std::istream& input, cPlayerMoment& playerMoment) {
	playerMoment.Read(input);
	return input;
}

std::ostream& operator<<(std::ostream& output, const cPlayerMoment& playerMoment) {
	playerMoment.Write(output);
	return output;
}