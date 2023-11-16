#ifndef H_MAP_DRAWER_H
#define H_MAP_DRAWER_H

#include "cMapLane.h"
#include "cMapObject.h"

// Forward declaration
class cApp;

class hMapDrawer
{
private:
	cApp* app;

public:
	hMapDrawer();
	hMapDrawer(cApp* app);
	~hMapDrawer();

public: 
	bool SetupTarget(cApp* app);
	int GetStartPos(const cMapLane& lane) const;
	int GetCellOffset(const cMapLane& lane) const;
	bool DrawLane(const cMapLane& lane) const;
	bool DrawObject(char graphic, int nCellOffset, int nRow, int nCol) const;
	bool DrawBackground(char graphic, int nCellOffset, int nRow, int nCol) const;

public: // Drawers
	bool DrawAllLanes() const;
};

#endif // H_MAP_DRAWER_H
