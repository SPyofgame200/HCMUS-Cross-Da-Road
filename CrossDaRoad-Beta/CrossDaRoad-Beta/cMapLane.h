/**
 * @file cMapLane.h
 * @brief Contains map lane class prototype
 *
 *
**/

#ifndef C_MAP_LANE_H
#define C_MAP_LANE_H

#include <string>

/// @brief Class for lane object in game
class cMapLane
{
private: // Properties
	float fVelocity;   ///< velocity of the lane (> 0, moving right; < 0, moving left)
	std::string sLane; ///< character representation of the lane
	std::string sUnderlay; 
	int nID;
	int nFrame;

public: // Constructors & Destructor
	cMapLane(float velocity, const std::string& lane, int ID, const std::string &background = "", int nFrame = 0);
	cMapLane(const cMapLane& other);
	~cMapLane() = default;

public: // Getters
	bool HasUnderlay() const;
	std::string GetUnderlay() const;
	int GetUnderlayFrameCount() const;
	float GetVelocity() const;
	std::string GetLane() const;
	int GetLaneID() const;
	size_t GetLaneSize() const;
	float GetLaneOffset(float fCurrentTime) const;
	int GetStartPos(float fCurrentTime) const;
	int GetCellOffset(int nCellSize, float fCurrentTime) const;
	char GetLaneGraphic(int nPos, bool bWrapAroundPosition = true) const;

private: // Utilities
	static int FixValue(int& nValue, const size_t nLimit);
	static int FixValue(int& nValue, const int nLimit);

public:	// Setters
	void SetVelocity(float velocity);
	void SetLane(const std::string& sLane);
	void SetID(int ID);
};

#endif // C_MAP_LANE_H