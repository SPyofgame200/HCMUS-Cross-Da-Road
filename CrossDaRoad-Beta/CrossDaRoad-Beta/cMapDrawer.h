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
	int GetStartPos(const cMapLane& lane) const;
	int GetCellOffset(const cMapLane& lane) const;
	bool DrawLane(const cMapLane& lane, int nRow);
	bool DrawCharacter(char graphic, bool drawBackground, const cMapLane& lane, int nRow, int nCol);

public: // Drawers
	bool DrawAllLanes();
};

#endif // C_MAP_DRAWER_H
