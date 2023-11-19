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
	/// Identity
	encode = 0;
	sCategory = "";
	/// Flag
	isBlocked = false;
	isDanger = false;
	/// Sprite
	sSpriteName = "";
	nSpritePosX = 0;
	nSpritePosY = 0;
	nID = 0;
	/// Background
	sBackgroundName = "";
	nBackgroundPosX = 0;
	nBackgroundPosY = 0;
	/// Lane
	fPlatform = 0.0;
	/// Summon
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

bool MapObject::ExtractToken(char &token, const std::string& sData)
{
	if (sData.empty()) {
		std::cerr << "MapObject::ExtractTime(NULL): ";
		std::cerr << "Invalid empty string, expected non-empty size" << std::endl;
		return false;
	}

	token = sData[0];
	return true;
}

/// @brief Extract time from string
/// @param sData Time string
/// @return Time in float format
bool MapObject::ExtractTime(float &fTime, const std::string& sData)
{
	if (sData.empty()) {
		std::cerr << "MapObject::ExtractTime(\"" << sData << "\"): ";
		std::cerr << "Invalid time string." << std::endl;
		return false;
	}

	float conversionFactor = 1.0;
	std::string numericPart;
	std::string timeType;

	// Find the position of the first non-numeric character
	size_t pos = 0;
	while (pos < sData.size() && (std::isdigit(sData[pos]) || sData[pos] == '.')) {
		numericPart += sData[pos];
		pos++;
	}

	if (pos < sData.size()) {
		timeType = sData.substr(pos);
	}
	else {
		std::cerr << "MapObject::ExtractTime(\"" << sData << "\"): ";
		std::cerr << "No time type specified in the time string." << std::endl;
		return false;
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
		std::cerr << "MapObject::ExtractTime(\"" << sData << "\"): ";
		std::cerr << "Unrecognized time type: " << timeType << std::endl;
		return false;
	}

	std::istringstream numericStream(numericPart);
	float numericValue;

	if (numericStream >> numericValue) {
		fTime = numericValue * conversionFactor;
		return true;
	}
	else {
		std::cerr << "MapObject::ExtractTime(\"" << sData << "\"): ";
		std::cerr << "Invalid numeric part in the time string." << std::endl;
		return false;
	}
}


bool MapObject::ExtractName(std::string& sName, const std::string& sData)
{
	if (sData.empty()) {
		std::cerr << "MapObject::ExtractName(\"" << sData << "\"): ";
		std::cerr << "Invalid data, expected non-empty string size" << std::endl;
		return false;
	}

	sName = sData;
	return true;
}

bool MapObject::ExtractFlag(bool &bFlag, const std::string& sData)
{
	if (sData.empty()) {
		std::cerr << "MapObject::ExtractFlag(\"" << sData << "\"): ";
		std::cerr << "Invalid data, expected non-empty string size." << std::endl;
		return false;
	}

	bFlag = (sData == "yes" || sData == "ok" || sData == "enable" || sData == "true" || sData == "1" || sData == "enabled");
	return true;
}

bool MapObject::ExtractPosition(int32_t& nPos, const std::string& sData)
{
	if (sData.empty()) {
		std::cerr << "MapObject::ExtractPosition(\"" << sData << "\"): ";
		std::cerr << "Invalid data, expected non-empty string size." << std::endl;
		return false;
	}

	nPos = std::stoi(sData);
	return true;
}

bool MapObject::ExtractFloat(float& fFloat, const std::string& sData)
{
	if (sData.empty()) {
		std::cerr << "MapObject::ExtractFloat(\"" << sData << "\"): ";
		std::cerr << "Invalid data, expected non-empty string size." << std::endl;
		return false;
	}

	fFloat = std::stof(sData);
	return true;
}

bool MapObject::ExtractPercentage(float& fPercentage, const std::string& sData)
{
	if (sData.size() <= 1) {
		std::cerr << "MapObject::ExtractPercentage(\"" << sData << "\"): ";
		std::cerr << "Invalid data, expected non-empty string size with suffix %." << std::endl;
		return false;
	}
	int nDataSize = static_cast<int>(sData.size());
	fPercentage = std::stof(sData.substr(0, static_cast<size_t>(nDataSize - 1)));
	return true;
}

bool ExtractAttributeValue(std::string& sAttribute, std::string& sValue, const std::string& sData)
{
	return true;
}

bool MapObject::SetIdentityAttribute(const std::string& sAttribute, const std::string& sValue)
{
	if (sAttribute == "token") {
		return ExtractToken(encode, sValue);
	}
	if (sAttribute == "category") {
		return ExtractName(sCategory, sValue);
	}
	return false;
}
bool MapObject::SetFlagAttribute(const std::string& sAttribute, const std::string& sValue)
{
	if (sAttribute == "block") {
		return ExtractFlag(isBlocked, sValue);
	}
	if (sAttribute == "danger") {
		return ExtractFlag(isDanger, sValue);
	}
	return false;
}
bool MapObject::SetSpriteAttribute(const std::string& sAttribute, const std::string& sValue)
{
	if (sAttribute == "sprite") {
		return ExtractName(sSpriteName, sValue);
	}
	if (sAttribute == "spritex") {
		return ExtractPosition(nSpritePosX, sValue);
	}
	if (sAttribute == "spritey") {
		return ExtractPosition(nSpritePosY, sValue);
	}
	if (sAttribute == "id") {
		return ExtractPosition(nID, sValue);
	}
	return false;
}
bool MapObject::SetBackgroundAttribute(const std::string& sAttribute, const std::string& sValue)
{
	if (sAttribute == "background") {
		return ExtractName(sBackgroundName, sValue);
	}
	if (sAttribute == "backgroundx") {
		return ExtractPosition(nBackgroundPosX, sValue);
	}
	if (sAttribute == "backgroundy") {
		return ExtractPosition(nBackgroundPosY, sValue);
	}
	return false;
}
bool MapObject::SetLaneAttribute(const std::string& sAttribute, const std::string& sValue)
{
	if (sAttribute == "platformspeed") {
		return ExtractFloat(fPlatform, sValue);
	}
	return false;
}
bool MapObject::SetSummonAttribute(const std::string& sAttribute, const std::string& sValue)
{
	if (sAttribute == "summon") {
		return ExtractToken(summon, sValue);
	}
	if (sAttribute == "duration") {
		return ExtractTime(fDuration, sValue);
	}
	if (sAttribute == "cooldown") {
		return ExtractTime(fCooldown, sValue);
	}
	if (sAttribute == "chance") {
		return ExtractPercentage(fChance, sValue);
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

std::string MapObject::ShowIdentityData() const
{
	std::ostringstream oss;
	oss << "Identity: [ ";
	oss << "token=" << encode << ", ";
	oss << "category=\"" << sCategory << "\" ";
	oss << "]";
	return oss.str();
}

std::string MapObject::ShowFlagData() const
{
	std::ostringstream oss;
	oss << "Flag: [ ";
	oss << "is_blocked=" << std::boolalpha << isBlocked << ", ";
	oss << "is_danger=" << std::boolalpha << isDanger << ", ";
	oss << "]";
	return oss.str();
}

std::string MapObject::ShowSpriteData() const
{
	std::ostringstream oss;
	oss << "Sprite: [ ";
	oss << "name=\"" << sSpriteName << "\", ";
	oss << "draw_x=" << nSpritePosX << ", ";
	oss << "draw_y=" << nSpritePosY << " ";
	oss << "frames=" << nID << " ";
	oss << "]";
	return oss.str();
}

std::string MapObject::ShowBackgroundData() const
{
	std::ostringstream oss;
	oss << "Background: [ ";
	oss << "name=\"" << sBackgroundName << "\", ";
	oss << "draw_x=" << nBackgroundPosX << ", ";
	oss << "draw_y=" << nBackgroundPosY << " ";
	oss << "]";
	return oss.str();
}

std::string MapObject::ShowLaneData() const
{
	std::ostringstream oss;
	oss << "Lane: [ ";
	oss << "platform_drag=" << fPlatform << ", ";
	oss << "]";
	return oss.str();
}

std::string MapObject::ShowSummonData() const
{
	std::ostringstream oss;
	oss << "Summon: [ ";
	oss << "summon=" << summon << ", ";
	oss << "duration=" << fDuration << ", ";
	oss << "cooldown=" << fCooldown << ", ";
	oss << "chance=" << fChance << " ";
	oss << "]";
	return oss.str();
}

/// @brief Function for debugging
/// @param end character to end the line
std::string MapObject::ShowData() const
{
	std::ostringstream oss;
	oss << "Sprite[" << encode << "]= {\n";
	oss << "      " << ShowIdentityData() << "\n";
	oss << "          " << ShowFlagData() << "\n";
	oss << "        " << ShowSpriteData() << "\n";
	oss << "    " << ShowBackgroundData() << "\n";
	oss << "          " << ShowLaneData() << "\n";
	oss << "        " << ShowSummonData() << "\n";
	oss << "}";
	return oss.str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// END OF FILE ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////