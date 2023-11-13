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

int cMapLane::GetID() const
{
	return nID;
}

int cMapLane::GetLaneSize() const
{
	return sLane.size();
}

char cMapLane::GetLaneGraphic(int nPos, bool bWrapAroundPosition) const
{
	if (bWrapAroundPosition && abs(nPos) >= GetLaneSize()) {
		nPos %= GetLaneSize(); /// (-size, +size)
		if (nPos < 0) {
			nPos += GetLaneSize(); /// [0, +size)
		}
	}
	char cGraphic = sLane[nPos];
	return cGraphic;
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