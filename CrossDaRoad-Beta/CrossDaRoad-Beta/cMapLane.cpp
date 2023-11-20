/**
 * @file cMapLane.cpp
 * @brief Contains map lane class implementation
 *
 *
**/

#include "cMapLane.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// CONSTRUCTORS & DESTRUCTOR ////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Parameterized constructor
/// @param velocity velocity of the lane
/// @param lane character representation of the lane ()
cMapLane::cMapLane(const float velocity, const std::string& lane, int ID, const std::string& underlay, int frame)
{
	fVelocity = velocity;
	sLane = lane;
	nID = ID;
	sUnderlay = underlay;
	nFrame = frame;
}

/// @brief Copy constructor
/// @param other the other lane to copy from
cMapLane::cMapLane(const cMapLane& other)
{
	fVelocity = other.fVelocity;
	sLane = other.sLane;
	nID = other.nID;
	sUnderlay = other.sUnderlay;
	nFrame = other.nFrame;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// GETTERS ///////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

bool cMapLane::HasUnderlay() const
{
	return !sUnderlay.empty();
}

std::string cMapLane::GetUnderlay() const
{
	return sUnderlay;
}

int cMapLane::GetUnderlayFrameCount() const
{
	if (!HasUnderlay()) {
		return -1;
	}
	return nFrame;
}

/// @brief Getter for velocity of the lane
float cMapLane::GetVelocity() const
{
	return fVelocity;
}
/// @brief Getter for character representation of the lane
std::string cMapLane::GetLane() const
{
	return sLane;
}
/// @brief Getter for ID of the lane
int cMapLane::GetLaneID() const
{
	return nID;
}
/// @brief Getter for size of the lane
size_t cMapLane::GetLaneSize() const
{
	return sLane.size();
}
/// @brief Getter for offset of the lane
/// @param fCurrentTime Current time of the game
/// @return Offset of the lane
float cMapLane::GetLaneOffset(float fCurrentTime) const
{
	return fCurrentTime * fVelocity;
}
/// @brief Getter for start position of the lane
/// @param fCurrentTime Current time of the game
/// @return Start position of the lane
int cMapLane::GetStartPos(float fCurrentTime) const
{
	int nStartPos = static_cast<int>(GetLaneOffset(fCurrentTime));
	return FixValue(nStartPos, GetLaneSize());
}
/// @brief Getter for cell offset of the lane
/// @param nCellSize Size of the cell
/// @param fCurrentTime Current time of the game
/// @return Cell offset of the lane
int cMapLane::GetCellOffset(int nCellSize, float fCurrentTime) const
{
	const float fCellOffset = nCellSize * GetLaneOffset(fCurrentTime);
	return static_cast<int>(fCellOffset) % nCellSize;
}
/// @brief Getter for character representation of the lane
/// @param nPos Position of the lane
/// @param bWrapAroundPosition Whether to wrap around the position or not
/// @return Character representation of the lane
char cMapLane::GetLaneGraphic(int nPos, bool bWrapAroundPosition) const
{
	if (bWrapAroundPosition) {
		FixValue(nPos, GetLaneSize());
	}
	const char cGraphic = sLane[nPos];
	return cGraphic;
}
/// @brief Fix value to be in range [0, nLimit)
/// @param nValue Value to be fixed
/// @param nLimit Maximum value
/// @return Fixed value
int cMapLane::FixValue(int& nValue, const size_t nLimit)
{
	return FixValue(nValue, static_cast<int>(nLimit));
}
/// @brief Fix value to be in range [0, nLimit)
/// @param nValue Value to be fixed
/// @param nLimit Maximum value
/// @return Fixed value
int cMapLane::FixValue(int& nValue, const int nLimit)
{
	if (abs(nValue) >= nLimit) {
		nValue %= nLimit;
	}
	if (nValue < 0) {
		nValue += nLimit;
	}
	return nValue;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// SETTERS ///////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Setter for velocity of the lane
/// @param velocity velocity of the lane
void cMapLane::SetVelocity(const float velocity)
{
	fVelocity = velocity;
}

/// @brief Setter for character representation of the lane
/// @param lane character representation of the lane
void cMapLane::SetLane(const std::string& lane)
{
	sLane = lane;
}

/// @brief Setter for ID of the lane
/// @param ID ID of the lane
void cMapLane::SetID(int ID)
{
	nID = ID;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// END OF FILE //////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////