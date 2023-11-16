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

public: // Constructors & Destructor
	hMapDrawer();
	hMapDrawer(cApp* app);
	~hMapDrawer();

public: // Setters
	bool SetupTarget(cApp* app);

public: // Getters
	int GetStartPos(const cMapLane& lane) const;
	int GetCellOffset(const cMapLane& lane) const;

private: // Drawer helpers
	bool DrawLane(const cMapLane& lane) const;
	bool DrawObject(char graphic, int nCellOffset, int nRow, int nCol) const;
	bool DrawBackground(char graphic, int nCellOffset, int nRow, int nCol) const;

public: // Drawers
	bool DrawAllLanes() const;

public: // Generators
	bool SuccessSummon(const MapObject& sprite, int nCol, int nRow, float fCurrentTime, int fps, bool bCreateAllow) const;
};

#endif // H_MAP_DRAWER_H
