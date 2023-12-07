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
    bMatrix = nullptr;
    nCellWidth = 0;
    nCellHeight = 0;
    sDefaultPattern = nullptr;
    return true;
}

bool cZone::Destroy()
{
    CleanArray(bMatrix);
    CleanArray(sDefaultPattern);
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
bool cZone::CreateZone(const int nWidth, const int nHeight, const bool bValue)
{
    if (nWidth <= 0 || nHeight <= 0) {
        std::cerr << "cZone::CreateZone(width = " << nWidth << ", height = " << nHeight << "): ";
        std::cerr << "Invalid parameters, expected positive integer parameters";
        return false;
    }
    nZoneWidth = nWidth;
    nZoneHeight = nHeight;
    const int nZoneSize = nZoneWidth * nZoneHeight;
    bMatrix = new bool[nZoneSize];
    Reset(bValue);
    return true;
}

bool cZone::Reset(bool bValue)
{
    if (nZoneWidth <= 0 || nZoneHeight <= 0) {
        std::cerr << "cZone::Reset(" << bValue << "): ";
        std::cerr << "Invalid zone size, expected positive integer size";
        return false;
    }
    const int nZoneSize = nZoneWidth * nZoneHeight;
    memset(bMatrix, bValue, nZoneSize * sizeof(bool));
    return true;
}

////////////////////////////////////////////////////////////////////////
////////////////////////////// CHECKERS ////////////////////////////////
////////////////////////////////////////////////////////////////////////

/// @brief Check if graphic is danger
/// @param graphic graphic to check 
/// @param sEnablePattern danger pattern to check 
/// @return true if graphic is danger, false otherwise
bool cZone::IsEnabled(const char& graphic, const char* sEnablePattern)
{
    return strchr(sEnablePattern, graphic) != nullptr;
}
/// @brief Check if graphic is safe
/// @param graphic graphic to check
/// @param sEnablePattern danger pattern to check
/// @return true if graphic is safe, false otherwise
bool cZone::IsDisabled(const char& graphic, const char* sEnablePattern)
{
    return !IsEnabled(graphic, sEnablePattern);
}

bool cZone::IsEnabled(const char& graphic)
{
    return IsEnabled(graphic, sDefaultPattern);
}

bool cZone::IsDisabled(const char& graphic)
{
    return !IsDisabled(graphic, sDefaultPattern);
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
    bMatrix[nPosY * nZoneWidth + nPosX] = bValue;
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
/// @param sEnablePattern Character array of danger pattern
/// @param sBlockPattern Character array of block pattern
/// @return True if successfully set danger and block pattern, false otherwise
bool cZone::SetPattern(const char* sEnablePattern)
{
    CleanArray(sDefaultPattern);
    sDefaultPattern = new char[strlen(sEnablePattern) + 1];
    strcpy_s(sDefaultPattern, strlen(sEnablePattern) + 1, sEnablePattern);
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
/// @param sEnablePattern danger pattern to check if graphic is danger or not
/// @return number of danger pixels filled
int cZone::Fill(const char& graphic, const char* sEnablePattern, const int nTopLeftX, const int nTopLeftY, const int nBottomRightX, const int nBottomRightY)
{

    int counter = 0;
    for (int x = nTopLeftX; x < nBottomRightX; x++) {
        for (int y = nTopLeftY; y < nBottomRightY; y++) {
            counter += SetDanger(x, y, IsEnabled(graphic, sEnablePattern));
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
/// @param sEnablePattern danger pattern to check if graphic is danger or not
/// @return number of safe pixels filled
int cZone::Unfill(const char& graphic, const char* sEnablePattern, const int nTopLeftX, const int nTopLeftY, const int nBottomRightX, const int nBottomRightY)
{
    int counter = 0;
    for (int x = nTopLeftX; x < nBottomRightX; x++) {
        for (int y = nTopLeftY; y < nBottomRightY; y++) {
            counter += SetDanger(x, y, IsDisabled(graphic, sEnablePattern));
        }
    }
    return counter;
}
/// @brief Fill danger pixels with graphic in the zone
/// @param graphic Graphic character to fill
/// @param nTopLeftX x coordinate of top left corner
/// @param nTopLeftY y coordinate of top left corner
/// @return Number of danger pixels filled
int cZone::Fill(const char& graphic, const int nTopLeftX, const int nTopLeftY)
{
    return Fill(graphic, sDefaultPattern, nTopLeftX, nTopLeftY, nTopLeftX + nCellWidth, nTopLeftY + nCellHeight);
}
/// @brief Fill safe pixels with graphic in the zone
/// @param graphic Graphic character to fill
/// @param nTopLeftX x coordinate of top left corner
/// @param nTopLeftY y coordinate of top left corner
/// @return Number of safe pixels filled
int cZone::Unfill(const char& graphic, const int nTopLeftX, const int nTopLeftY)
{
    return Unfill(graphic, sDefaultPattern, nTopLeftX, nTopLeftY, nTopLeftX + nCellWidth, nTopLeftY + nCellHeight);
}

////////////////////////////////////////////////////////////////////////
//////////////////////// DANGER ZONE CHECKERS //////////////////////////
////////////////////////////////////////////////////////////////////////

/// @brief Check if pixel at (x, y) is danger
/// @param x x coordinate
/// @param y y coordinate
/// @return true if pixel at (x, y) is danger, false otherwise
bool cZone::IsPixelEnabled(const float x, const float y) const
{
    const bool isDangerPixel = bMatrix[static_cast<int>(y) * nZoneWidth + static_cast<int>(x)];
    return isDangerPixel;
}

/// @brief Check if pixel at (x, y) is danger (top left) 
/// @param x x coordinate
/// @param y y coordinate
/// @param size size of the pixel
/// @return true if top left pixel at (x, y) is danger, false otherwise
bool cZone::IsTopLeftEnabled(const float x, const float y, const int size) const
{
    const bool isDangerTopLeft = IsPixelEnabled(x * static_cast<float>(size) + 1, y * static_cast<float>(size) + 1);
    return isDangerTopLeft;
}

/// @brief Check if pixel at (x, y) is danger (top right) 
/// @param x x coordinate
/// @param y y coordinate
/// @param size size of the pixel
/// @return true if top right pixel at (x, y) is danger, false otherwise
bool cZone::IsTopRightEnabled(const float x, const float y, const int size) const
{
    const bool isDangerTopRight = IsPixelEnabled((x + 1) * static_cast<float>(size) - 1, y * static_cast<float>(size) + 1);
    return isDangerTopRight;
}

/// @brief Check if pixel at (x, y) is danger (bottom left)
/// @param x x coordinate
/// @param y y coordinate
/// @param size size of the pixel
/// @return true if bottom left pixel at (x, y) is danger, false otherwise
bool cZone::IsBottomLeftEnabled(const float x, const float y, const int size) const
{
    const bool isDangerBottomLeft = IsPixelEnabled(x * static_cast<float>(size) + 1, (y + 1) * static_cast<float>(size) - 1);
    return isDangerBottomLeft;
}

/// @brief Check if pixel at (x, y) is danger (bottom right)
/// @param x x coordinate
/// @param y y coordinate
/// @param size size of the pixel
/// @return true if bottom right pixel at (x, y) is danger, false otherwise
bool cZone::IsBottomRightEnabled(const float x, const float y, const int size) const
{
    const bool isDangerBottomRight =
        IsPixelEnabled((x + 1) * static_cast<float>(size) - 1, (y + 1) * static_cast<float>(size) - 1);
    return isDangerBottomRight;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// END OF FILE ////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
