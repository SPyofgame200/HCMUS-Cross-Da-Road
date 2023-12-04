/**
 * @file cZone.h
 *
 * @brief Contains zone class
 *
 * This file contains zone class for zone management, collision detection.
**/

#ifndef C_ZONE_H
#define C_ZONE_H


/// @brief Class for zone object in game (for collision detection)
class cZone
{
private:
    int nZoneWidth;         ///< width of the zone
    int nZoneHeight;        ///< height of the zone
    bool* bMatrix;          ///< cache-friendly matrix of pixel states
    int nCellWidth;         ///< width of the default filler zone
    int nCellHeight;        ///< height of the default filler zone
    char* sDefaultPattern;  ///< default enable patterns

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
    bool IsEnabled(const char& graphic, const char* sEnablePattern);
    bool IsDisabled(const char& graphic, const char* sEnablePattern);
    bool IsEnabled(const char& graphic);
    bool IsDisabled(const char& graphic);
    bool IsInside(int x, int y) const;

public: // Setters 
    bool SetDanger(int nPosX, int nPosY, bool bValue);
    bool SetCellSize(int nWidth, int nHeight);
    bool SetPattern(const char* sEnablePattern);

public: // Fillers
    int Fill(const char& graphic, const char* sEnablePattern, int nTopLeftX, int nTopLeftY, int nBottomRightX, int nBottomRightY);
    int Unfill(const char& graphic, const char* sEnablePattern, int nTopLeftX, int nTopLeftY, int nBottomRightX, int nBottomRightY);
    int Fill(const char& graphic, int nTopLeftX, int nTopLeftY);
    int Unfill(const char& graphic, int nTopLeftX, int nTopLeftY);

public: // Danger Zone Checkers
    bool IsPixelEnabled(float x, float y) const;
    bool IsTopLeftEnabled(float x, float y, int size = 1) const;
    bool IsTopRightEnabled(float x, float y, int size = 1) const;
    bool IsBottomLeftEnabled(float x, float y, int size = 1) const;
    bool IsBottomRightEnabled(float x, float y, int size = 1) const;
};

#endif // C_ZONE_H