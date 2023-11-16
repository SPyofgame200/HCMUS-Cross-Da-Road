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
	int nZoneWidth;  ///< width of the zone
	int nZoneHeight; ///< height of the zone
	bool* bDangers;  ///< array of danger pixels
	bool* bBlocks;   ///< array of block pixels
	int nCellWidth;
	int nCellHeight;
	char* sDefaultDangerPattern;
	char* sDefaultBlockPattern;

public: // Constructors & Destructor
	cZone();
	cZone(int nWidth, int nHeight);
	~cZone();

private: // Constructor functions
	bool CreateZone(int nWidth, int nHeight, bool bDanger, bool bBlock);
public: // Constructor functions
	bool CreateZone(int nWidth, int nHeight);

private: // Checkers
	static bool IsDanger(const char& graphic, const char* sDangerPattern);
	static bool IsSafe(const char& graphic, const char* sDangerPattern);
	static bool IsBlocked(const char& graphic, const char* sBlockPattern);
	static bool IsUnblocked(const char& graphic, const char* sBlockPattern);
	bool IsInside(int x, int y) const;

public: // Setters 
	bool SetDanger(int nPosX, int nPosY, bool bValue);
	bool SetBlock(int nPosX, int nPosY, bool bValue);
	bool SetCellSize(int nWidth, int nHeight);
	bool SetPattern(const char* sDangerPattern, const char* sBlockPattern);

public: // Fillers
	int FillDanger(const char& graphic, const char* sDangerPattern, int nTopLeftX, int nTopLeftY, int nBottomRightX, int nBottomRightY);
	int FillSafe(const char& graphic, const char* sDangerPattern, int nTopLeftX, int nTopLeftY, int nBottomRightX, int nBottomRightY);
	int FillBlocked(const char& graphic, const char* sBlockPattern, int nTopLeftX, int nTopLeftY, int nBottomRightX, int nBottomRightY);
	int FillUnblocked(const char& graphic, const char* sBlockPattern, int nTopLeftX, int nTopLeftY, int nBottomRightX, int nBottomRightY);
	int FillDanger(const char& graphic, int nTopLeftX, int nTopLeftY);
	int FillSafe(const char& graphic, int nTopLeftX, int nTopLeftY);
	int FillBlocked(const char& graphic, int nTopLeftX, int nTopLeftY);
	int FillUnblocked(const char& graphic, int nTopLeftX, int nTopLeftY);

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