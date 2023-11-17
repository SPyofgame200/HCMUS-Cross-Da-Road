/**
 * @file cMapObject.h
 * @brief Contains MapObject struct for sprite data and GraphicCell struct for graphical cell
 *
 * This file contains prototype of MapObject struct and GraphicCell struct
 */


#ifndef C_MAP_OBJECT_H
#define C_MAP_OBJECT_H

#include <string>

 /// @brief Sprite data for drawing and collision detection (block, danger, platform, etc.)
struct MapObject
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

	char summon;			    ///< The chance of summoning another sprite with encoded = summon
	float fDuration;            ///< The duration (in seconds) of that sprite to be appeared
	float fCooldown;            ///< The cooldown durations for the two consecutive summoning
	float fChance;              ///< The probability of summoning in each second

	// Methods
	MapObject();						///< Constructor
	~MapObject();					 	///< Destructor
	void debug(char end = '\n') const;  ///< Debug
};

#endif // C_MAP_OBJECT_H