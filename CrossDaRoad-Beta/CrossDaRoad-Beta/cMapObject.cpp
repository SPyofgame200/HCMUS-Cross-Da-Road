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
	Create();
}

MapObject::MapObject(char token)
{
	Create();
	encode = token;
}

/// @brief Destructor
MapObject::~MapObject()
{
	Destroy();
}

bool MapObject::Create()
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
	return true;
}

bool MapObject::Destroy()
{
	sSpriteName.clear();
	sBackgroundName.clear();
	sCategory.clear();
	return true;
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

bool MapObject::SetAttribute(const std::string& sAttribute, const std::string& sValue)
{
	if (SetIdentityAttribute(sAttribute, sValue)) return true;
	if (SetFlagAttribute(sAttribute, sValue)) return true;
	if (SetSpriteAttribute(sAttribute, sValue)) return true;
	if (SetBackgroundAttribute(sAttribute, sValue)) return true;
	if (SetLaneAttribute(sAttribute, sValue)) return true;
	if (SetSummonAttribute(sAttribute, sValue)) return true;
	return false;
}

bool MapObject::SetAttributeFromData(const std::string& sData)
{
	const size_t uDelimiter = sData.find('=');
	if (uDelimiter == std::string::npos) {
		std::cerr << "Unknown properties from data [\"" << sData << "\"]" << std::endl;
		return false;
	}
	
	// Split the raw string into the form `attribute=value`
	std::string sAttribute, sValue;
	sAttribute = sData.substr(0, uDelimiter);
	sValue = sData.substr(uDelimiter + 1);

	// Standardize the value, so it doesnt be case sentitive
	utils::trim(sAttribute);
	utils::trim(sValue);
	utils::lowerize(sAttribute);
	utils::lowerize(sValue);
	
	// Trying to set the attribute if it is possible
	if (!SetAttribute(sAttribute, sValue)) {
		std::cerr << "Can not set attribute [" << sAttribute << "] with value " << sValue << std::endl;
		return false;
	}
	return true;
}

void MapObject::ShowIdentityData() const
{
	std::cerr << "Identity: [ ";
	std::cerr << "token=" << encode << ", ";
	std::cerr << "category=\"" << sCategory << "\" ";
	std::cerr << "]";
}

void MapObject::ShowFlagData() const
{
	std::cerr << "Flag: [ ";
	std::cerr << "is_blocked=" << std::boolalpha << encode << ", ";
	std::cerr << "is_danger=" << std::boolalpha << sCategory << ", ";
	std::cerr << "]";
}

void MapObject::ShowSpriteData() const
{
	std::cerr << "Sprite: [ ";
	std::cerr << "name=\"" << sSpriteName << "\", ";
	std::cerr << "draw_x=" << nSpritePosX << ", ";
	std::cerr << "draw_y=" << nSpritePosY << " ";
	std::cerr << "frames=" << nID << " ";
	std::cerr << "]";
}

void MapObject::ShowBackgroundData() const
{
	std::cerr << "Background: [ ";
	std::cerr << "name=\"" << sBackgroundName << "\", ";
	std::cerr << "draw_x=" << nBackgroundPosX << ", ";
	std::cerr << "draw_y=" << nBackgroundPosY << " ";
	std::cerr << "]";
}

void MapObject::ShowLaneData() const
{
	std::cerr << "Lane: [ ";
	std::cerr << "platform_drag=" << fPlatform << ", ";
	std::cerr << "]";
}

void MapObject::ShowSummonData() const
{
	std::cerr << "Summon: [ ";
	std::cerr << "summon=" << summon << ", ";
	std::cerr << "duration=" << fDuration << ", ";
	std::cerr << "cooldown=" << fCooldown << ", ";
	std::cerr << "chance=" << fChance << " ";
	std::cerr << "]";
}

/// @brief Function for debugging
/// @param end character to end the line
void MapObject::ShowData() const
{
	std::cerr << "Sprite[" << encode << "]= {\n";
	std::cerr << "      "; ShowIdentityData(); std::cerr << "\n";
	std::cerr << "          "; ShowFlagData(); std::cerr << "\n";
	std::cerr << "        "; ShowSpriteData(); std::cerr << "\n";
	std::cerr << "    "; ShowBackgroundData(); std::cerr << "\n";
	std::cerr << "          "; ShowLaneData(); std::cerr << "\n";
	std::cerr << "        "; ShowSummonData(); std::cerr << "\n";
	std::cerr << "}";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// END OF FILE ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////