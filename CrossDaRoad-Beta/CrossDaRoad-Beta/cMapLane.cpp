#include "cMapLane.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// CONSTRUCTORS & DESTRUCTOR ////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Parameterized constructor
/// @param velocity velocity of the lane
/// @param lane character representation of the lane ()
cMapLane::cMapLane(const float velocity, const std::string& lane, int ID)
{
	fVelocity = velocity;
	sLane = lane;
	nID = ID;
}

/// @brief Copy constructor
/// @param other the other lane to copy from
cMapLane::cMapLane(const cMapLane& other)
{
	fVelocity = other.fVelocity;
	sLane = other.sLane;
	nID = other.nID;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// GETTERS ///////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

float cMapLane::GetVelocity() const
{
	return fVelocity;
}

std::string cMapLane::GetLane() const
{
	return sLane;
}

int cMapLane::GetLaneID() const
{
	return nID;
}

size_t cMapLane::GetLaneSize() const
{
	return sLane.size();
}

float cMapLane::GetLaneOffset(float fCurrentTime) const
{
	return fCurrentTime * fVelocity;
}

int cMapLane::GetStartPos(float fCurrentTime) const
{
	int nStartPos = static_cast<int>(GetLaneOffset(fCurrentTime));
	return FixValue(nStartPos, GetLaneSize());
}

int cMapLane::GetCellOffset(int nCellSize, float fCurrentTime) const
{
	const float fCellOffset = nCellSize * GetLaneOffset(fCurrentTime);
	return static_cast<int>(fCellOffset) % nCellSize;
}

char cMapLane::GetLaneGraphic(int nPos, bool bWrapAroundPosition) const
{
	if (bWrapAroundPosition) {
		FixValue(nPos, GetLaneSize());
	}
	const char cGraphic = sLane[nPos];
	return cGraphic;
}

int cMapLane::FixValue(int& nValue, const size_t nLimit)
{
	return FixValue(nValue, static_cast<int>(nLimit));
}

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

void cMapLane::SetID(int ID)
{
	nID = ID;
}