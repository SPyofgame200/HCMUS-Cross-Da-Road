/**
 * @file hMapDrawer.h
 * @brief Contains map drawer class for drawing map on screen
**/

#ifndef H_MAP_DRAWER_H
#define H_MAP_DRAWER_H

#include "cMapLane.h"
#include "cMapObject.h"
#include "cMapObject.h"
#include <vector>

// Forward declaration
class cApp;

/// @brief Structure for graphic cell 
struct GraphicCell
{
	char graphic; 			///< Character representing the graphic
	int nCellOffset; 		///< Offset of the cell
	int nRow; 				///< Row of the cell
	int nCol; 				///< Column of the cell
	float fLastDrawn; 		///< Last drawn time of the cell

	// Constructors & Destructor
	GraphicCell();
	GraphicCell(char graphic, int nCellOffset, int nRow, int nCol);
	~GraphicCell();
};

/// @brief Class for drawing map on screen
class hMapDrawer
{
private:
	cApp* app;

public: // Constructors & Destructor
	hMapDrawer();
	hMapDrawer(cApp* app);
	~hMapDrawer();

public: // Setters
	bool SetupTarget(cApp* app);

private: /// Internality
	std::vector<GraphicCell> GetLaneBackgrounds(const cMapLane& Lane) const;
	std::vector<GraphicCell> GetLaneObjects(const cMapLane& Lane) const;

private: // Drawer helpers
	bool DrawLane(const cMapLane& Lane) const;
	bool DrawUnderlay(const cMapLane& Lane) const;
	bool DrawObject(const GraphicCell& Cell) const;
	bool DrawBackground(const GraphicCell& Cell) const;

public: // Drawers
	bool DrawAllLanes() const;

public: // Generators
	bool SuccessSummon(char graphic, int nID) const;
};

#endif // H_MAP_DRAWER_H
