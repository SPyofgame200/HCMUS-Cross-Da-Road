#ifndef C_MAP_DRAWER_H
#define C_MAP_DRAWER_H

#include "cMapLane.h"

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

public: // Drawers
	bool DrawLane(const cMapLane& lane, int nRow, int nCol);
	bool DrawAllLanes();
};

#endif // C_MAP_DRAWER_H
