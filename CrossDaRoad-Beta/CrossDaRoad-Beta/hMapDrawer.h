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

/// @brief Class for drawing map on screen
class hMapDrawer
{
private:
	struct GraphicCell
	{
		char graphic; 			///< Character representing the graphic
		int nRowPos; 		    ///< Row of the cell
		int nColPos; 			///< Column of the cell

		// Constructors & Destructor
		GraphicCell();
		GraphicCell(char graphic, int nRowPos, int nColPos);
		~GraphicCell();
	};
	using GraphicLane = std::vector<GraphicCell>;

private:
	cApp* app;

public: // Constructors & Destructor
	hMapDrawer();
	hMapDrawer(cApp* app);
	~hMapDrawer();

public: // Setters
	bool SetupTarget(cApp* app);

private: /// Internality
	GraphicLane GetLaneBackgrounds(const cMapLane& Lane) const;
	GraphicLane GetLaneEntities(const cMapLane& Lane) const;

private: // Drawer helpers
	bool DrawLane(const cMapLane& Lane) const;
	bool DrawUnderlay(const cMapLane& Lane) const;
	bool DrawEntity(const GraphicCell& Cell) const;
	bool DrawBackground(const GraphicCell& Cell) const;
	bool DrawGraphic(const GraphicCell& Cell, const std::string& sName, int nDrawX = 0, int nDrawY = 0) const;
	void SetHitBox(const GraphicCell& Cell) const;

public: // Drawers
	bool DrawAllLanes() const;

public: // Generators
	bool SuccessSummon(char graphic, int nID) const;
};

#endif // H_MAP_DRAWER_H
