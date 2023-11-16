#ifndef H_MAP_DRAWER_H
#define H_MAP_DRAWER_H

#include "cMapLane.h"
#include "cMapObject.h"
#include "cMapObject.h"

// Forward declaration
class cApp;

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

private: // Drawer helpers
	bool DrawLane(const cMapLane& Lane) const;
	bool DrawObject(const GraphicCell& Cell) const;
	bool DrawBackground(const GraphicCell& Cell) const;

public: // Drawers
	bool DrawAllLanes() const;

public: // Generators
	bool SuccessSummon(char graphic, int nID) const;
};

#endif // H_MAP_DRAWER_H
