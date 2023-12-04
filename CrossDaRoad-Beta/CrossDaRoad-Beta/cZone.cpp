/**
 * @file cZone.cpp
 *
 * @brief Contains zone class implementation
 *
 * This file implements zone class for zone management.
**/

#include "cZone.h"
#include <cstring>
#include <iostream>

////////////////////////////////////////////////////////////////////////
////////////////////////// CONSTRUCTORS AND DESTRUCTOR /////////////////
////////////////////////////////////////////////////////////////////////

/// @brief Default constructor
cZone::cZone()
{
    Create();
}
/// @brief Parameterized constructor
/// @param nWidth width of the zone
/// @param nHeight height of the zone
cZone::cZone(const int nWidth, const int nHeight)
{
    CreateZone(nWidth, nHeight);
}
/// @brief Destructor
cZone::~cZone()
{
    if (Destroy()) {
        std::cerr << "cZone::~cZone(): Successfully destructed" << std::endl;
    }
}

template<class type>
bool cZone::CleanArray(type*& pArray)
{
    if (pArray) {
        delete[] pArray;
        pArray = nullptr;
        return true;
    }
    return false;
}

template<class type>
bool cZone::CleanObject(type*& pObject)
{
    if (pObject) {
        delete pObject;
        pObject = nullptr;
        return true;
    }
    return false;
}

bool cZone::Create()
{
    Destroy();
    nZoneWidth = 0;
    nZoneHeight = 0;
    bDangers = nullptr;
    nCellWidth = 0;
    nCellHeight = 0;
    sDefaultDangerPattern = nullptr;
    return true;
}

bool cZone::Destroy()
{
    CleanArray(bDangers);
    CleanArray(sDefaultDangerPattern);
    return true;
}

////////////////////////////////////////////////////////////////////////
/////////////////// CONSTRUCTOR FUNCTIONS //////////////////////////////
////////////////////////////////////////////////////////////////////////

/// @brief Create zone with size nWidth x nHeight, set danger and block pixels
/// @param nWidth width of the zone
/// @param nHeight height of the zone
/// @param bDanger value to set danger pixels (true: danger, false: safe)
/// @param bBlock value to set block pixels (true: block, false: unblock)
/// @return true if successfully created zone, false otherwise
bool cZone::CreateZone(const int nWidth, const int nHeight, const bool bDanger, const bool bBlock, const bool bPlatform)
{
    if (nWidth <= 0 || nHeight <= 0) {
        std::cerr << "cZone::CreateZone(width = " << nWidth << ", height = " << nHeight << "): ";
        std::cerr << "Invalid parameters, expected positive integer parameters";
        return false;
    }
    nZoneWidth = nWidth;
    nZoneHeight = nHeight;
    const int nZoneSize = nZoneWidth * nZoneHeight;
    bDangers = new bool[nZoneSize];
    memset(bDangers, bDanger, nZoneSize * sizeof(bool));
    return true;
}

/// @brief Create zone with size nWidth x nHeight, set danger and block pixels to safe and unblock
bool cZone::CreateZone(const int nWidth, const int nHeight)
{
    return CreateZone(nWidth, nHeight, false, false, false);
}

////////////////////////////////////////////////////////////////////////
////////////////////////////// CHECKERS ////////////////////////////////
////////////////////////////////////////////////////////////////////////

/// @brief Check if graphic is danger
/// @param graphic graphic to check 
/// @param sDangerPattern danger pattern to check 
/// @return true if graphic is danger, false otherwise
bool cZone::IsDanger(const char& graphic, const char* sDangerPattern)
{
    return strchr(sDangerPattern, graphic) != nullptr;
}
/// @brief Check if graphic is safe
/// @param graphic graphic to check
/// @param sDangerPattern danger pattern to check
/// @return true if graphic is safe, false otherwise
bool cZone::IsNotDanger(const char& graphic, const char* sDangerPattern)
{
    return !IsDanger(graphic, sDangerPattern);
}

bool cZone::IsDanger(const char& graphic)
{
    return IsDanger(graphic, sDefaultDangerPattern);
}

/// @brief Check if (x, y) is inside the zone
/// @param x x coordinate 
/// @param y y coordinate
/// @return true if (x, y) is inside the zone, false otherwise
bool cZone::IsInside(const int x, const int y) const
{
    return (x >= 0 && x < nZoneWidth) && (y >= 0 && y < nZoneHeight);
}

////////////////////////////////////////////////////////////////////////
////////////////////////////// SETTERS /////////////////////////////////
////////////////////////////////////////////////////////////////////////

/// @brief Set danger pixel at a position
/// @param nPosX x coordinate
/// @param nPosY y coordinate
/// @param bValue value to set (true: danger, false: safe)
/// @return true if successfully set danger pixel (if (nPosX, nPosY) is inside), false otherwise
bool cZone::SetDanger(const int nPosX, const int nPosY, const bool bValue)
{
    if (!IsInside(nPosX, nPosY)) {
        return false;
    }
    bDangers[nPosY * nZoneWidth + nPosX] = bValue;
    return true;
}

/// @brief Set cell size of the zone
/// @param nWidth Width of the cell
/// @param nHeight Height of the cell
/// @return True if successfully set cell size, false otherwise
bool cZone::SetCellSize(int nWidth, int nHeight)
{
    if (nWidth <= 0 || nHeight <= 0) {
        nCellWidth = 0;
        nCellHeight = 0;
        return false;
    }
    nCellWidth = nWidth;
    nCellHeight = nHeight;
    return true;
}
/// @brief Set danger and block pattern of the zone
/// @param sDangerPattern Character array of danger pattern
/// @param sBlockPattern Character array of block pattern
/// @return True if successfully set danger and block pattern, false otherwise
bool cZone::SetPattern(const char* sDangerPattern)
{
    CleanArray(sDefaultDangerPattern);
    sDefaultDangerPattern = new char[strlen(sDangerPattern) + 1];
    strcpy_s(sDefaultDangerPattern, strlen(sDangerPattern) + 1, sDangerPattern);
    return true;
}
////////////////////////////////////////////////////////////////////////
////////////////////////////// FILLERS /////////////////////////////////
////////////////////////////////////////////////////////////////////////

/// @brief Fill danger pixels with graphic in the zone
/// @param nTopLeftX top left x coordinate
/// @param nTopLeftY top left y coordinate
/// @param nBottomRightX bottom right x coordinate
/// @param nBottomRightY bottom right y coordinate
/// @param graphic graphic to fill
/// @param sDangerPattern danger pattern to check if graphic is danger or not
/// @return number of danger pixels filled
int cZone::FillDanger(const char& graphic, const char* sDangerPattern, const int nTopLeftX, const int nTopLeftY, const int nBottomRightX, const int nBottomRightY)
{

    int counter = 0;
    for (int x = nTopLeftX; x < nBottomRightX; x++) {
        for (int y = nTopLeftY; y < nBottomRightY; y++) {
            counter += SetDanger(x, y, IsDanger(graphic, sDangerPattern));
        }
    }
    return counter;
}
/// @brief  Fill safe pixels with graphic in the zone
/// @param nTopLeftX x coordinate of top left corner
/// @param nTopLeftY y coordinate of top left corner
/// @param nBottomRightX x coordinate of bottom right corner
/// @param nBottomRightY y coordinate of bottom right corner
/// @param graphic graphic to fill
/// @param sDangerPattern danger pattern to check if graphic is danger or not
/// @return number of safe pixels filled
int cZone::UnfillDanger(const char& graphic, const char* sDangerPattern, const int nTopLeftX, const int nTopLeftY, const int nBottomRightX, const int nBottomRightY)
{
    int counter = 0;
    for (int x = nTopLeftX; x < nBottomRightX; x++) {
        for (int y = nTopLeftY; y < nBottomRightY; y++) {
            counter += SetDanger(x, y, IsNotDanger(graphic, sDangerPattern));
        }
    }
    return counter;
}
/// @brief Fill danger pixels with graphic in the zone
/// @param graphic Graphic character to fill
/// @param nTopLeftX x coordinate of top left corner
/// @param nTopLeftY y coordinate of top left corner
/// @return Number of danger pixels filled
int cZone::FillDanger(const char& graphic, const int nTopLeftX, const int nTopLeftY)
{
    return FillDanger(graphic, sDefaultDangerPattern, nTopLeftX, nTopLeftY, nTopLeftX + nCellWidth, nTopLeftY + nCellHeight);
}
/// @brief Fill safe pixels with graphic in the zone
/// @param graphic Graphic character to fill
/// @param nTopLeftX x coordinate of top left corner
/// @param nTopLeftY y coordinate of top left corner
/// @return Number of safe pixels filled
int cZone::UnfillDanger(const char& graphic, const int nTopLeftX, const int nTopLeftY)
{
    return UnfillDanger(graphic, sDefaultDangerPattern, nTopLeftX, nTopLeftY, nTopLeftX + nCellWidth, nTopLeftY + nCellHeight);
}

int cZone::Fill(const char& graphic, int nTopLeftX, int nTopLeftY)
{
    int nChange = 0;
    nChange += FillDanger(graphic, nTopLeftX, nTopLeftY);
    return nChange;
}

int cZone::Unfill(const char& graphic, int nTopLeftX, int nTopLeftY)
{
    int nChange = 0;
    nChange += UnfillDanger(graphic, nTopLeftX, nTopLeftY);
    return nChange;
}

////////////////////////////////////////////////////////////////////////
//////////////////////// DANGER ZONE CHECKERS //////////////////////////
////////////////////////////////////////////////////////////////////////

/// @brief Check if pixel at (x, y) is danger
/// @param x x coordinate
/// @param y y coordinate
/// @return true if pixel at (x, y) is danger, false otherwise
bool cZone::IsDangerPixel(const float x, const float y) const
{
    const bool isDangerPixel = bDangers[static_cast<int>(y) * nZoneWidth + static_cast<int>(x)];
    return isDangerPixel;
}

/// @brief Check if pixel at (x, y) is danger (top left) 
/// @param x x coordinate
/// @param y y coordinate
/// @param size size of the pixel
/// @return true if top left pixel at (x, y) is danger, false otherwise
bool cZone::IsDangerTopLeft(const float x, const float y, const int size) const
{
    const bool isDangerTopLeft = IsDangerPixel(x * static_cast<float>(size) + 1, y * static_cast<float>(size) + 1);
    return isDangerTopLeft;
}

/// @brief Check if pixel at (x, y) is danger (top right) 
/// @param x x coordinate
/// @param y y coordinate
/// @param size size of the pixel
/// @return true if top right pixel at (x, y) is danger, false otherwise
bool cZone::IsDangerTopRight(const float x, const float y, const int size) const
{
    const bool isDangerTopRight = IsDangerPixel((x + 1) * static_cast<float>(size) - 1, y * static_cast<float>(size) + 1);
    return isDangerTopRight;
}

/// @brief Check if pixel at (x, y) is danger (bottom left)
/// @param x x coordinate
/// @param y y coordinate
/// @param size size of the pixel
/// @return true if bottom left pixel at (x, y) is danger, false otherwise
bool cZone::IsDangerBottomLeft(const float x, const float y, const int size) const
{
    const bool isDangerBottomLeft = IsDangerPixel(x * static_cast<float>(size) + 1, (y + 1) * static_cast<float>(size) - 1);
    return isDangerBottomLeft;
}

/// @brief Check if pixel at (x, y) is danger (bottom right)
/// @param x x coordinate
/// @param y y coordinate
/// @param size size of the pixel
/// @return true if bottom right pixel at (x, y) is danger, false otherwise
bool cZone::IsDangerBottomRight(const float x, const float y, const int size) const
{
    const bool isDangerBottomRight =
        IsDangerPixel((x + 1) * static_cast<float>(size) - 1, (y + 1) * static_cast<float>(size) - 1);
    return isDangerBottomRight;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// END OF FILE ////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
