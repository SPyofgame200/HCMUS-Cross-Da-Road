#ifndef C_ZONE_H
#define C_ZONE_H

/**
 * @file cZone.h
 *
 * @brief Contains zone class
 *
 * This file contains zone class for zone management, collision detection, and rendering.
**/

/// @brief Class for zone object in game (for collision detection)
class cZone
{
private:
	int nZoneHeight; ///< height of the zone
	int nZoneWidth;  ///< width of the zone
	bool* bDangers;  ///< array of danger pixels
	bool* bBlocks;   ///< array of block pixels

public: // Constructors & Destructor
	cZone();
	cZone(int nWidth, int nHeight);
	~cZone();

private: // Constructor functions
	bool CreateZone(int nWidth, int nHeight, bool bDanger, bool bBlock);
public: // Constructor functions
	bool CreateZone(int nWidth, int nHeight);

private: // Checkers
	static bool IsDanger(const char& graphic, const char* danger_pattern);
	static bool IsSafe(const char& graphic, const char* danger_pattern);
	static bool IsBlocked(const char& graphic, const char* block_pattern);
	static bool IsUnblocked(const char& graphic, const char* block_pattern);
	bool IsInside(int x, int y) const;

public: // Setters 
	bool SetDanger(int nPosX, int nPosY, bool bValue) const;
	bool SetBlock(int nPosX, int nPosY, bool bValue) const;

public: // Fillers
	int FillDanger(int nTopLeftX, int nTopLeftY, int nBottomRightX, int nBottomRightY, const char& graphic, const char* danger_pattern) const;
	int FillSafe(int nTopLeftX, int nTopLeftY, int nBottomRightX, int nBottomRightY, const char& graphic, const char* danger_pattern) const;
	int FillBlocked(int nTopLeftX, int nTopLeftY, int nBottomRightX, int nBottomRightY, const char& graphic, const char* danger_pattern) const;
	int FillUnblocked(int nTopLeftX, int nTopLeftY, int nBottomRightX, int nBottomRightY, const char& graphic, const char* danger_pattern) const;

public: // Danger Zone Checkers
	bool IsDangerPixel(float x, float y) const;

	bool IsDangerTopLeft(float x, float y, int size) const;
	bool IsDangerTopRight(float x, float y, int size) const;
	bool IsDangerBottomLeft(float x, float y, int size) const;
	bool IsDangerBottomRight(float x, float y, int size) const;

public: // Block Zone Checkers
	bool IsBlockedPixel(float x, float y) const;

	bool IsBlockedTopLeft(float x, float y, int size) const;
	bool IsBlockedTopRight(float x, float y, int size) const;
	bool IsBlockedBottomLeft(float x, float y, int size) const;
	bool IsBlockedBottomRight(float x, float y, int size) const;
};

#endif // C_ZONE_H