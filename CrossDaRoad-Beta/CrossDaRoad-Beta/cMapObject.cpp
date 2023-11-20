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
	code = token;
}

/// @brief Destructor
MapObject::~MapObject()
{
	Destroy();
}

bool MapObject::Create()
{
	/// Identity
	code = 0;
	sCategory = "";
	/// Flag
	isBlocked = false;
	isDanger = false;
	/// Sprite
	sSpriteName = "";
	nSpritePosX = 0;
	nSpritePosY = 0;
	nSpriteFrame = 0;
	/// Background
	sBackgroundName = "";
	nBackgroundPosX = 0;
	nBackgroundPosY = 0;
	nBackgroundFrame = 0;
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

bool MapObject::IsBlocked() const
{
	return isBlocked;
}

bool MapObject::IsDanger() const
{
	return isDanger;
}

bool MapObject::IsPlatform() const
{
	return GetPlatformDragSpeed() != 0;
}

char MapObject::GetCode() const
{
	return code;
}

std::string MapObject::GetCategory() const
{
	return sCategory;
}

std::string MapObject::GetSpriteName() const
{
	return sSpriteName;
}

int32_t MapObject::GetSpritePosX() const
{
	return nSpritePosX;
}

int32_t MapObject::GetSpritePosY() const
{
	return nSpritePosY;
}

int32_t MapObject::GetSpriteFrameCount() const
{
	return nSpriteFrame;
}

std::string MapObject::GetBackgroundName() const 
{
	return sBackgroundName;
}

int32_t MapObject::GetBackgroundPosX() const 
{
	return nBackgroundPosX;
}

int32_t MapObject::GetBackgroundPosY() const 
{
	return nBackgroundPosY;
}

int32_t MapObject::GetBackgroundFrameCount() const
{
	return nBackgroundFrame;
}

float MapObject::GetPlatformDragSpeed() const 
{
	return fPlatform;
}

char MapObject::GetSummonTarget() const 
{
	return summon;
}

float MapObject::GetSummonDuration() const 
{
	return fDuration;
}

float MapObject::GetSummonCooldown() const 
{
	return fCooldown;
}

float MapObject::GetSummonProbability() const 
{
	return fChance;
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

bool MapObject::ExtractPositions(int32_t& nPosX, int32_t& nPosY, const std::string& sData)
{
	if (sData.empty()) {
		std::cerr << "MapObject::ExtractPosition(\"" << sData << "\"): ";
		std::cerr << "Invalid data, expected non-empty string size." << std::endl;
		return false;
	}

	if (sData == "default") {
		nPosX = nPosY = 0;
		return true;
	}

	int x, y;
	std::istringstream iss(sData);
	if (!(iss >> x >> y)) {
		std::cerr << "MapObject::ExtractPosition(\"" << sData << "\"): ";
		std::cerr << "Failed to extract positions." << std::endl;
		return false;
	}

	nPosX = x;
	nPosY = y;
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

bool MapObject::ExtractAttributeValue(std::string& sAttribute, std::string& sValue, const std::string& sData)
{
	const size_t uDelimiter = sData.find('=');
	if (uDelimiter == std::string::npos) {
		std::cerr << "MapObject::ExtractAttributeValue(&,&,\"" << sData << "\"): ";
		std::cerr << "Can not extract \"attributes = value\" format from data \"" << sData << "\"" << std::endl;
		return false;
	}

	// Split the raw string into the form `attribute=value`
	sAttribute = sData.substr(0, uDelimiter);
	sValue = sData.substr(uDelimiter + 1);

	// Standardize the value, so it doesnt be case sentitive
	utils::trim(sAttribute);
	utils::trim(sValue);
	utils::lowerize(sAttribute);
	utils::lowerize(sValue);
	return true;
}

bool MapObject::SetIdentityAttribute(const std::string& sAttribute, const std::string& sValue)
{
	if (sAttribute == "token") {
		return ExtractToken(code, sValue);
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
	if (sAttribute == "spritepos") {
		return ExtractPositions(nSpritePosX, nSpritePosY, sValue);
	}
	if (sAttribute == "spriteframe") {
		return ExtractPosition(nSpriteFrame, sValue);
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
	if (sAttribute == "backgroundpos") {
		return ExtractPositions(nBackgroundPosX, nBackgroundPosY, sValue);
	}
	if (sAttribute == "backgroundframe") {
		return ExtractPosition(nSpriteFrame, sValue);
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
	std::string sAttribute, sValue;
	if (!ExtractAttributeValue(sAttribute, sValue, sData)) {
		return false;
	}
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
	oss << "token=" << code << ", ";
	oss << "category=\"" << sCategory << "\" ";
	oss << "]";
	return oss.str();
}

std::string MapObject::ShowFlagData() const
{
	std::ostringstream oss;
	oss << "Flag: [ ";
	oss << "is_blocked=" << std::boolalpha << IsBlocked() << ", ";
	oss << "is_danger=" << std::boolalpha << IsDanger() << ", ";
	oss << "is_platform=" << std::boolalpha << IsPlatform() << " ";
	oss << "]";
	return oss.str();
}

std::string MapObject::ShowSpriteData() const
{
	std::ostringstream oss;
	oss << "Sprite: [ ";
	oss << "name=\"" << sSpriteName << "\", ";
	oss << "draw_position=(" << nSpritePosX << ":" << nSpritePosY << "), ";
	oss << "frames=" << nSpriteFrame << " ";
	oss << "]";
	return oss.str();
}

std::string MapObject::ShowBackgroundData() const
{
	std::ostringstream oss;
	oss << "Background: [ ";
	oss << "name=\"" << sBackgroundName << "\", ";
	oss << "draw_position=(" << nBackgroundPosX << ":" << nBackgroundPosY << "), ";
	oss << "frames=" << nBackgroundFrame << " ";
	oss << "]";
	return oss.str();
}

std::string MapObject::ShowLaneData() const
{
	std::ostringstream oss;
	oss << "Lane: [ ";
	oss << "platform_drag=" << fPlatform << " ";
	oss << "]";
	return oss.str();
}

std::string MapObject::ShowSummonData() const
{
	std::ostringstream oss;
	oss << "Summon: [ ";
	oss << "summon=" << (summon == 0 ? "NULL" : std::string(1, summon)) << ", ";
	oss << "duration=" << fDuration << "s, ";
	oss << "cooldown=" << fCooldown << "s, ";
	oss << "chance=" << fChance << "% ";
	oss << "]";
	return oss.str();
}

/// @brief Function for debugging
/// @param end character to end the line
std::string MapObject::ShowData() const
{
	std::ostringstream oss;
	oss << "Sprite[" << code << "]<" << (sCategory.empty() ? "Uncategorized" : sCategory) << "> = {\n";
	oss << "          " << ShowFlagData() << "\n";
	oss << "        " << ShowSpriteData() << "\n";
	oss << "    " << ShowBackgroundData() << "\n";
	oss << "          " << ShowLaneData() << "\n";
	oss << "        " << ShowSummonData() << "\n";
	oss << "}";
	return oss.str();
}

std::ostream& operator<<(std::ostream& output, const MapObject& obj) {
	output << obj.ShowData();
	return output;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// END OF FILE ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////