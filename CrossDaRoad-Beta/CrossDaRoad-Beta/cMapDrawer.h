#ifndef C_MAP_DRAWER_H
#define C_MAP_DRAWER_H

#include "cMapLane.h"
#include "cMapObject.h"

// Forward declaration
class cApp;

class cMapDrawer
{
private:
	cApp* app;

public:
	cMapDrawer();
	cMapDrawer(cApp* app);
	~cMapDrawer();

public: 
	bool SetTarget(cApp* app);

	bool DrawLane(const cMapLane& lane, int nRow, int nCol = 0);
	bool DrawCharacter(int nLaneIndex, const MapObject& sprite, bool drawBackground, const cMapLane& lane, int nRow, int nCol, int nCellOffset);

public: // Drawers
	bool DrawAllLanes();
};

#endif // C_MAP_DRAWER_H
