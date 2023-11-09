#ifndef C_MAP_LOADER_H
#define C_MAP_LOADER_H

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
 * @brief Contains map SpriteData struct, cLane class, and cMapLoader class
 *
 * This file contains map SpriteData struct, cLane class, and cMapLoader class for map loading and manipulation in game.
**/

/// @brief Sprite data for drawing and collision detection (block, danger, platform, etc.)
struct SpriteData
{
	char encode;                ///< Sprite encode chacters for map editor
	std::string sSpriteName;    ///< Sprite name (*.png), for sprite loading
	std::string sBackgroundName;///< Background name (*.png), for sprite's background
	std::string sCategory;      ///< Category, allow categorize configuration if needed
	bool isBlocked;             ///< If the player shouldn't be able to move here
	bool isDanger;              ///< If the player should be killed to move here
	float fPlatform;            ///< Platform dragging speed if the player land on them
	int32_t nSpritePosX;        ///< X initial position for drawing sprite
	int32_t nSpritePosY;        ///< Y initial position for drawing sprite
	int32_t nBackgroundPosX;    ///< X initial position for drawing background
	int32_t nBackgroundPosY;    ///< Y initial position for drawing background
	int32_t nID;                ///< The ID of the sprite, for player customization

	SpriteData* summon;			///< The chance of summoning another sprite with encoded = summon
	float fDuration;            ///< The duration (in seconds) of that sprite to be appeared
	float fCooldown;            ///< The cooldown durations for the two consecutive summoning
	float fChance;              ///< The probability of summoning in each second

	// Methods
	SpriteData();						///< Constructor
	~SpriteData();					 	///< Destructor
	void debug(char end = '\n') const;  ///< Debug
	bool SuccessSummon(int nCol, int nRow, float fCurrentTime, int fps) const;
};

/// @brief Class for lane object in game
class cLane
{
private:
	float fVelocity;   ///< velocity of the lane (> 0, moving right; < 0, moving left)
	std::string sLane; ///< character representation of the lane

public: // Constructors & Destructor
	cLane(float velocity, const std::string& sLane);
	cLane(const cLane& other);
	~cLane() = default;

public: // Getters
	float GetVelocity() const;
	std::string GetLane() const;

public:	// Setters
	void SetVelocity(float velocity);
	void SetLane(const std::string& sLane);
};

class cMapLoader
{
private:
	std::map<char, SpriteData> mapSprites; ///< Map of sprite data (key: encode, value: SpriteData)
	std::vector<cLane> vecLanes; ///< Vector of lanes in map
	std::vector<std::string> vecMapNames; ///< Vector of map names
	std::vector<std::string> vecMapDescriptions; ///< Vector of map descriptions

private:
	SpriteData currentSprite; ///< Current sprite data
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
	SpriteData GetSpriteData(char graphic) const;
	std::string GetDangerPattern();
	std::string GetBlockPattern();
	std::string GetMapName(int nLevel) const;
	std::string GetMapName() const;
	std::string GetMapDescription(int nLevel) const;
	std::string GetMapDescription() const;
	std::vector<cLane> GetLanes() const;
	cLane GetLane(int fPos) const;
	cLane GetLaneFloor(float fPos) const;
	cLane GetLaneRound(float fPos) const;
	cLane GetLaneCeil(float fPos) const;

public: // Info getters
	std::string ShowMapLevel() const;
	std::string ShowMapInfo() const;

public: // Setters
	bool SetSpriteData(const SpriteData& data);
	bool SetMapLevel(int MapLevel);

public: // Loaders
	bool LoadMapLane(const std::string& sLine, bool bDebug = false);
	bool LoadMapSprite(const std::string& sLine, bool bDebug = false);
	bool LoadMapName(const std::string& sFileName);
	bool LoadMapLevel(const int& nMapLevel);
	bool LoadMapLevel();
	float ExtractTime(const std::string& timeStr);
};

#endif // C_MAP_LOADER_H
