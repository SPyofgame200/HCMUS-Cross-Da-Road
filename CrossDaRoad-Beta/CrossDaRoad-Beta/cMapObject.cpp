/**
 * @file cMapObject.cpp
 * @brief Contains implementation of MapObject and GraphicCell structs
**/

#include "uStringUtils.h"
#include "cMapObject.h"
#include <iostream>
#include <sstream>
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

bool MapObject::SetIdentityAttribute(const std::string& sAttribute, const std::string& sValue)
{
	if (sAttribute == "token")
	{
		encode = sValue[0];
		return true;
	}
	if (sAttribute == "category") {
		sCategory = sValue;
		return true;
	}
	return false;
}
bool MapObject::SetFlagAttribute(const std::string& sAttribute, const std::string& sValue)
{
	bool bValue = (sValue == "true") || (sValue == "yes");
	if (sAttribute == "block") {
		isBlocked = bValue;
		return true;
	}
	if (sAttribute == "danger") {
		isDanger = bValue;
		return true;
	}
	return false;
}
bool MapObject::SetSpriteAttribute(const std::string& sAttribute, const std::string& sValue)
{
	if (sAttribute == "sprite") {
		sSpriteName = sValue;
		return true;
	}
	if (sAttribute == "spritex") {
		nSpritePosX = std::stoi(sValue);
		return true;
	}
	if (sAttribute == "spritey") {
		nSpritePosY = std::stoi(sValue);
		return true;
	}
	if (sAttribute == "id") {
		nID = std::stoi(sValue);
		return true;
	}
	return false;
}
bool MapObject::SetBackgroundAttribute(const std::string& sAttribute, const std::string& sValue)
{
	if (sAttribute == "background") {
		sBackgroundName = sValue;
		return true;
	}
	if (sAttribute == "backgroundx") {
		nBackgroundPosX = std::stoi(sValue);
		return true;
	}
	if (sAttribute == "backgroundy") {
		nBackgroundPosY = std::stoi(sValue);
		return true;
	}
	return false;
}
bool MapObject::SetLaneAttribute(const std::string& sAttribute, const std::string& sValue)
{
	if (sAttribute == "platformspeed") {
		fPlatform = std::stof(sValue);
		return true;
	}
	return false;
}
bool MapObject::SetSummonAttribute(const std::string& sAttribute, const std::string& sValue)
{
	if (sAttribute == "summon") {
		summon = sValue[0];
		return true;
	}
	if (sAttribute == "duration") {
		fDuration = ExtractTime(sValue);
		return true;
	}
	if (sAttribute == "cooldown") {
		fCooldown = ExtractTime(sValue);
		return true;
	}
	if (sAttribute == "chance") {
		std::string sFixed = sValue;
		sFixed.pop_back();
		fChance = std::stof(sFixed);
		return true;
	}
	return false;
}


/// @brief Extract time from string
/// @param timeStr Time string
/// @return Time in float format
float MapObject::ExtractTime(const std::string& timeStr)
{
	if (timeStr.empty()) {
		std::cerr << "Invalid time string." << std::endl;
		return 0.0;
	}

	float conversionFactor = 1.0;
	std::string numericPart;
	std::string timeType;

	// Find the position of the first non-numeric character
	size_t pos = 0;
	while (pos < timeStr.size() && (std::isdigit(timeStr[pos]) || timeStr[pos] == '.')) {
		numericPart += timeStr[pos];
		pos++;
	}

	if (pos < timeStr.size()) {
		timeType = timeStr.substr(pos);
	}
	else {
		std::cerr << "No time type specified in the time string." << std::endl;
		return 0.0;
	}

	if (timeType == "ms") {
		conversionFactor = static_cast<float>(1.0e-3);
	}
	else if (timeType == "us") {
		conversionFactor = static_cast <float>(1.0e-6);
	}
	else if (timeType == "ns") {
		conversionFactor = static_cast <float>(1.0e-9);
	}
	else if (timeType == "s") {
		conversionFactor = static_cast <float>(1.0); // Seconds
	}
	else {
		std::cerr << "Unrecognized time type: " << timeType << std::endl;
		return 0.0;
	}

	std::istringstream numericStream(numericPart);
	float numericValue;

	if (numericStream >> numericValue) {
		return numericValue * conversionFactor;
	}
	else {
		std::cerr << "Invalid numeric part in the time string." << std::endl;
		return 0.0;
	}
}

bool MapObject::SetAttribute(const std::string& sAttribute, const std::string& sValue)
{
	bool bSuccess = true;
	bSuccess &= SetIdentityAttribute(sAttribute, sValue);
	bSuccess &= SetFlagAttribute(sAttribute, sValue);
	bSuccess &= SetSpriteAttribute(sAttribute, sValue);
	bSuccess &= SetBackgroundAttribute(sAttribute, sValue);
	bSuccess &= SetLaneAttribute(sAttribute, sValue);
	bSuccess &= SetSummonAttribute(sAttribute, sValue);
	return bSuccess;
}

/// @brief Function for debugging
/// @param end character to end the line
void MapObject::Debug(char end) const
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