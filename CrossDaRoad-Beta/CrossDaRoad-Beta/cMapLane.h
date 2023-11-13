#ifndef C_MAP_LANE_H
#define C_MAP_LANE_H

#include <string>

/// @brief Class for lane object in game
class cMapLane
{
private:
	float fVelocity;   ///< velocity of the lane (> 0, moving right; < 0, moving left)
	std::string sLane; ///< character representation of the lane
	int nID;

public: // Constructors & Destructor
	cMapLane(float velocity, const std::string& sLane, int ID);
	cMapLane(const cMapLane& other);
	~cMapLane() = default;

public: // Getters
	float GetVelocity() const;
	std::string GetLane() const;
	int GetID() const;
	size_t GetLaneSize() const;
	char GetLaneGraphic(int nPos, bool bWrapAroundPosition = true) const;

public:	// Setters
	void SetVelocity(float velocity);
	void SetLane(const std::string& sLane);
	void SetID(int ID);
};

#endif // C_MAP_LANE_H