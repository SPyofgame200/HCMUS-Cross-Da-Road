/**
 * @file cZone.h
 *
 * @brief Contains zone class
 *
 * This file contains zone class for zone management, collision detection, and rendering.
**/

#ifndef C_ZONE_H
#define C_ZONE_H


/// @brief Class for zone object in game (for collision detection)
class cZone
{
private:
    int nZoneWidth;   ///< width of the zone
    int nZoneHeight;  ///< height of the zone
    bool* bDangers;   ///< cache-friendly matrix of danger pixels
    int nCellWidth;   ///< width of the default filler zone
    int nCellHeight;  ///< height of the default filler zone
    char* sDefaultDangerPattern;

public: // Constructors & Destructor
    cZone();
    cZone(int nWidth, int nHeight);
    ~cZone();

private: /// Init-Clean Utilities
    template<class type>
    bool CleanArray(type*& pArray);
    template<class type>
    bool CleanObject(type*& pObject);

public: /// Initializer & Cleanup
    bool Create();
    bool Destroy();

public: // Constructor functions
    bool CreateZone(int nWidth, int nHeight, bool bDanger, bool bBlock, bool bPlatform);
    bool CreateZone(int nWidth, int nHeight);

public: // Checkers
    bool IsDanger(const char& graphic, const char* sDangerPattern);
    bool IsDanger(const char& graphic);
    
public: // Inverse Checkers
    bool IsNotDanger(const char& graphic, const char* sDangerPattern);
    bool IsNotDanger(const char& graphic);

private: /// Position Checkers
    bool IsInside(int x, int y) const;

public: // Setters 
    bool SetDanger(int nPosX, int nPosY, bool bValue);
    bool SetCellSize(int nWidth, int nHeight);
    bool SetPattern(const char* sDangerPattern);

public: // Fillers
    int FillDanger(const char& graphic, const char* sDangerPattern, int nTopLeftX, int nTopLeftY, int nBottomRightX, int nBottomRightY);
    int FillDanger(const char& graphic, int nTopLeftX, int nTopLeftY);
    int Fill(const char& graphic, int nTopLeftX, int nTopLeftY);

public: // Unfillers
    int UnfillDanger(const char& graphic, const char* sDangerPattern, int nTopLeftX, int nTopLeftY, int nBottomRightX, int nBottomRightY);
    int UnfillDanger(const char& graphic, int nTopLeftX, int nTopLeftY);
    int Unfill(const char& graphic, int nTopLeftX, int nTopLeftY);

public: // Danger Zone Checkers
    bool IsDangerPixel(float x, float y) const;
    bool IsDangerTopLeft(float x, float y, int size) const;
    bool IsDangerTopRight(float x, float y, int size) const;
    bool IsDangerBottomLeft(float x, float y, int size) const;
    bool IsDangerBottomRight(float x, float y, int size) const;
};

#endif // C_ZONE_H