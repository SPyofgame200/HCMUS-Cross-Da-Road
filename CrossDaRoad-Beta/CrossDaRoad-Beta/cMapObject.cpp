/**
 * @file cMapObject.cpp
 * @brief Contains implementation of MapObject and GraphicCell structs
**/

#include "cMapObject.h"
#include <iostream>
#include <chrono>
#include <map>

/////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// MAP OBJECTS ///////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Default constructor 
MapObject::MapObject()
{
	encode = 0;
	sSpriteName = "";
	sBackgroundName = "";
	sCategory = "";
	isBlocked = false;
	isDanger = false;
	fPlatform = 0.0;
	nSpritePosX = 0;
	nSpritePosY = 0;
	nBackgroundPosX = 0;
	nBackgroundPosY = 0;
	nID = 0;
	summon = 0;
	fDuration = 0;
	fCooldown = 0;
	fChance = 0;
}

/// @brief Destructor
MapObject::~MapObject()
{
	sSpriteName.clear();
	//std::cerr << "MapObject::~MapObject(): Successfully destructed" << std::endl;
}

/// @brief Function for debugging
/// @param end character to end the line
void MapObject::debug(char end) const
{
	std::cerr << "Sprite[" << encode << "]= {\n";
	{
		std::cerr << "    [";
		std::cerr << "name=" << (sSpriteName.empty() ? "NULL" : sSpriteName);
		std::cerr << ", ";
		std::cerr << "background="
			<< (sBackgroundName.empty() ? "NULL" : sBackgroundName);
		std::cerr << ", ";
		std::cerr << "category=" << (sCategory.empty() ? "NULL" : sCategory);
		std::cerr << "]\n";
	}
	{
		std::cerr << "    [";
		std::cerr << "isBlocked=" << std::boolalpha << isBlocked;
		std::cerr << ", ";
		std::cerr << "isDanger=" << std::boolalpha << isDanger;
		std::cerr << ", ";
		std::cerr << "platformSpeed=" << fPlatform;
		std::cerr << "]\n";
	}
	{
		std::cerr << "    [";
		std::cerr << "spriteX=" << nSpritePosX;
		std::cerr << ", ";
		std::cerr << "spriteY=" << nSpritePosY;
		std::cerr << ", ";
		std::cerr << "backgroundX=" << nBackgroundPosX;
		std::cerr << ", ";
		std::cerr << "backgroundY=" << nBackgroundPosY;
		std::cerr << ", ";
		std::cerr << "id=" << nID;
		std::cerr << "]\n";
	}
	{
		std::cerr << "    [";
		std::cerr << "summon=" << summon;
		std::cerr << ", ";
		std::cerr << "duration=" << fDuration << "s";
		std::cerr << ", ";
		std::cerr << "cooldown=" << fCooldown << "s";
		std::cerr << ", ";
		std::cerr << "chance=" << fChance << "%";
		std::cerr << "]\n";
	}
	std::cerr << "}" << end;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// END OF FILE ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////