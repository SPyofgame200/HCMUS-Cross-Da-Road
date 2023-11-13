#ifndef C_MAP_LOADER_H
#define C_MAP_LOADER_H

#include "cMapLane.h"
#include "cMapObject.h"
#include "uStringUtils.h"
#include "uAppConst.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <map>

/**
 * @file cMapLoader.h
 *
 * @brief Contains map MapObject struct, cMapLane class, and cMapLoader class
 *
 * This file contains cMapLane class, and cMapLoader class for map loading and manipulation in game.
**/

class cMapLoader
{
private:
	std::map<char, MapObject> mapSprites; ///< Map of sprite data (key: encode, value: MapObject)
	std::vector<cMapLane> vecLanes; ///< Vector of lanes in map
	std::vector<std::string> vecMapNames; ///< Vector of map names
	std::vector<std::string> vecMapDescriptions; ///< Vector of map descriptions

private:
	MapObject currentSprite; ///< Current sprite data
	std::string dangerPattern; ///< Danger pattern for map
	std::string blockPattern; ///< Block pattern for map
	int nMapLevel; ///< Current map level

public: // Constructors & Destructors
	cMapLoader();
	~cMapLoader();

public: // Constructor & Destruct functions
	void Init();
	void Destruct();

public: // Game Update
	void MapClear();
	void NextLevel();
	void PrevLevel();
	void UpdatePattern();

public: // Getters
	int GetMapLevel() const;
	int GetMapCount() const;
	MapObject GetSpriteData(char graphic) const;
	std::string GetDangerPattern();
	std::string GetBlockPattern();
	std::string GetMapName(int nLevel) const;
	std::string GetMapName() const;
	std::string GetMapDescription(int nLevel) const;
	std::string GetMapDescription() const;
	std::vector<cMapLane> GetLanes() const;
	cMapLane GetLane(int fPos) const;
	cMapLane GetLaneFloor(float fPos) const;
	cMapLane GetLaneRound(float fPos) const;
	cMapLane GetLaneCeil(float fPos) const;

public: // Info getters
	std::string ShowMapLevel() const;
	std::string ShowMapInfo() const;

public: // Setters
	bool SetSpriteData(const MapObject& data);
	bool SetMapLevel(int MapLevel);

public: // Loaders
	bool LoadMapLane(const std::string& sLine, int nLineID = 0, bool bDebug = false);
	bool LoadMapSprite(const std::string& sLine, bool bDebug = false);
	bool LoadMapName(const std::string& sFileName);
	bool LoadMapLevel(const int& nMapLevel);
	bool LoadMapLevel();

public: // Utilities
	static float ExtractTime(const std::string& timeStr);
};

#endif // C_MAP_LOADER_H
