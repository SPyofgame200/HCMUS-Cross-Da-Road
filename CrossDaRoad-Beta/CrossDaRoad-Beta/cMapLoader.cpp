#include "cMapLoader.h"
#include <iostream>
#include <filesystem>

/**
 * @file cMapLoader.cpp
 *
 * @brief Contains SpriteData struct, cLane class, and cMapLoader class implementation
 *
 * This file implements SpriteData struct, cLane class, and cMapLoader class for map loading and manipulation in game.
**/

// ==================================================================================================
// ===================================== SpriteData =================================================
// ==================================================================================================

/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// CONSTRUCTORS & DESTRUCTOR ////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Default constructor 
SpriteData::SpriteData()
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
	summon = nullptr;
	fDuration = 0;
	fCooldown = 0;
	fChance = 0;
}

/// @brief Destructor (clears the strings)
SpriteData::~SpriteData()
{
	sSpriteName.clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// METHODS ///////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Function for debugging
/// @param end character to end the line
void SpriteData::debug(char end) const
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
		std::cerr << "summon=" << (summon == nullptr ? "NULL" : "\'" + std::string(1, summon->encode) + "\'");
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
#include <random>
#include <iomanip>
std::default_random_engine generator(std::random_device{}());
std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
std::map<int, float> mapLastSummon;
bool SpriteData::SuccessSummon(int nCol, int nRow, float fCurrentTime, int fps) const
{
	if (summon == nullptr || fChance <= 0) {
		return false; // Summon is not enabled or chance is zero or negative
	}

	const int id = static_cast<int>(nCol * 1e4 + nRow);
	if (mapLastSummon.count(id) == false) {
		std::uniform_real_distribution<float> initialDistribution(fDuration, 2 * fDuration + fCooldown);
		mapLastSummon[id] = initialDistribution(generator);
		//std::cerr << "map[" << id << "] = " << fDuration + fCooldown << std::endl;
	}
	float& fLastSummon = mapLastSummon[id];
	const float fDeltaTime = fCurrentTime - fLastSummon;

	//std::cerr << nCol << " " << nRow << " id=" << id << ": ";
	//std::cerr << "delta=" << fDeltaTime << " current=" << fCurrentTime << " " << "last=" << fLastSummon << " -> ";
	if (fDeltaTime >= 0) {
		if (fDeltaTime <= fDuration) {
			//std::cerr << "Continue" << std::endl;
			return true;
		}
		else if (fDeltaTime < fDuration + fCooldown) {
			//std::cerr << "Stoped" << std::endl;
			return false;
		}
	}

	const auto fProbability = static_cast<float>(fChance / 100.0 / (fps == 0 ? 1 : fps));
	const float fGenerated = distribution(generator);
	if (fGenerated < fProbability) {
		fLastSummon = fCurrentTime;
		//std::cerr << "Recreated" << std::endl;
		return true;
	}
	//std::cerr << "Failed" << std::endl;
	return false; // Summon is not successful
}

// ==================================================================================================
// ===================================== cLane ======================================================
// ==================================================================================================

/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// CONSTRUCTORS & DESTRUCTOR ////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Parameterized constructor
/// @param velocity velocity of the lane
/// @param lane character representation of the lane ()
cLane::cLane(const float velocity, const std::string& lane)
{
	fVelocity = velocity;
	sLane = lane;
}

/// @brief Copy constructor
/// @param other the other lane to copy from
cLane::cLane(const cLane& other)
{
	fVelocity = other.fVelocity;
	sLane = other.sLane;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// GETTERS ///////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Getter for velocity of the lane
float cLane::GetVelocity() const
{
	return fVelocity;
}

/// @brief Getter for character representation of the lane
std::string cLane::GetLane() const
{
	return sLane;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// SETTERS ///////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Setter for velocity of the lane
/// @param velocity velocity of the lane
void cLane::SetVelocity(const float velocity)
{
	fVelocity = velocity;
}

/// @brief Setter for character representation of the lane
/// @param lane character representation of the lane
void cLane::SetLane(const std::string& lane)
{
	sLane = lane;
}

// ==================================================================================================
// ===================================== cMapLoader =================================================
// ==================================================================================================

/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// CONSTRUCTORS & DESTRUCTOR ////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Default constructor
cMapLoader::cMapLoader()
{
	nMapLevel = app_const::GAME_LEVEL_INIT;
}
/// @brief Destructor
cMapLoader::~cMapLoader()
{
	Destruct();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////// CONSTRUCTOR & DESTRUCTOR FUNCTIONS ///////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Initialize properties of map loader
void cMapLoader::Init()
{
	nMapLevel = app_const::GAME_LEVEL_INIT;
	LoadMapName("data/maps/mapNames.txt");
}

/// @brief Destruct properties of map loader
void cMapLoader::Destruct()
{
	mapSprites.clear();
	vecLanes.clear();
	vecMapNames.clear();
	vecMapDescriptions.clear();
	dangerPattern.clear();
	blockPattern.clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// GAME UPDATE ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Clear all map data
void cMapLoader::MapClear()
{
	mapSprites.clear();
	vecLanes.clear();
}
/// @brief Load next map level
void cMapLoader::NextLevel()
{
	if (++nMapLevel == GetMapCount()) {
		nMapLevel = 0;
		std::cerr << "Reset to map zero (overflow)" << std::endl;
	}
}
/// @brief Load previous map level
void cMapLoader::PrevLevel()
{
	if (--nMapLevel == -1) {
		nMapLevel = 0;
		std::cerr << "Reset to map zero (underflow)" << std::endl;
	}
}
/// @brief Update pattern of danger and block
void cMapLoader::UpdatePattern()
{
	dangerPattern.clear();
	blockPattern.clear();
	for (auto [fst, snd] : mapSprites) {
		auto sprite = snd;
		if (sprite.isBlocked) {
			blockPattern += sprite.encode;
		}
		if (sprite.isDanger) {
			dangerPattern += sprite.encode;
		}
		sprite.debug();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// GETTERS ///////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Getter for map level
int cMapLoader::GetMapLevel() const
{
	return nMapLevel;
}
/// @brief Get number of maps
int cMapLoader::GetMapCount() const
{
	return static_cast<int>(vecMapNames.size());
}
/// @brief Getter for lanes of the map
std::vector<cLane> cMapLoader::GetLanes() const
{
	return vecLanes;
}
/// @brief Get map name by level
/// @param nLevel Level of the map
std::string cMapLoader::GetMapName(int nLevel) const
{
	if (nLevel < 0 || nLevel >= vecMapNames.size()) {
		std::cerr << "Attemping to GetMapName(nLevel=" << nLevel << ") is out of bounds";
		std::cerr << " - expected [0.." << static_cast<int>(vecMapNames.size()) - 1 << "]" << std::endl;
		return "Undefined";
	}
	return vecMapNames[nLevel];
}
/// @brief Get map name by current level
std::string cMapLoader::GetMapName() const
{
	return GetMapName(GetMapLevel());
}
/// @brief Get map description by level
/// @param nLevel Level of the map
std::string cMapLoader::GetMapDescription(int nLevel) const
{
	if (nLevel < 0 || nLevel >= vecMapDescriptions.size()) {
		std::cerr << "Attemping to GetMapDescription(nLevel=" << nLevel << ") is out of bounds";
		std::cerr << " - expected [0.." << static_cast<int>(vecMapDescriptions.size()) - 1 << "]" << std::endl;
		return "Undefined";
	}
	return vecMapDescriptions[nLevel];
}
/// @brief Get map description by current level
std::string cMapLoader::GetMapDescription() const
{
	return GetMapDescription(GetMapLevel());
}
/// @brief Getter for sprite data by graphic
/// @param graphic Graphic of the sprite
SpriteData cMapLoader::GetSpriteData(char graphic) const
{
	const auto spriteIter = mapSprites.find(graphic);
	if (spriteIter != mapSprites.end()) {
		return spriteIter->second;
	}
	else {
		return SpriteData();
	}
}
/// @brief Getter for danger pattern
std::string cMapLoader::GetDangerPattern()
{
	return dangerPattern;
}
/// @brief Getter for block pattern
std::string cMapLoader::GetBlockPattern()
{
	return blockPattern;
}
/// @brief Getter for lane by position
/// @param fPos Index of the lane in vector
cLane cMapLoader::GetLane(int fPos) const
{
	return vecLanes[fPos];
}
/// @brief Getter for lane by position (floor)
/// @param fPos Index of the lane in vector
cLane cMapLoader::GetLaneFloor(float fPos) const
{
	return GetLane(static_cast<int>(std::floor(fPos)));
}
/// @brief Getter for lane by position (round)
/// @param fPos Index of the lane in vector
cLane cMapLoader::GetLaneRound(float fPos) const
{
	return GetLane(static_cast<int>(std::round(fPos)));
}
/// @brief Getter for lane by position (ceil)
/// @param fPos Index of the lane in vector
cLane cMapLoader::GetLaneCeil(float fPos) const
{
	return GetLane(static_cast<int>(std::ceil(fPos)));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// INFO GETTERS //////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Getter for map level in string
std::string cMapLoader::ShowMapLevel() const
{
	return std::to_string(GetMapLevel());
}
/// @brief Getter for map info in string
std::string cMapLoader::ShowMapInfo() const
{
	const std::string info = "- Level<" + ShowMapLevel() + ">: " + GetMapName() + " | describe: " + GetMapDescription();
	return info;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// SETTERS ///////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Setter for sprite data
/// @param data Sprite data
/// @return True if sprite data was set successfully, false otherwise
bool cMapLoader::SetSpriteData(const SpriteData& data)
{
	const bool bOverwrite = mapSprites.count(data.encode);
	mapSprites[data.encode] = data;
	return bOverwrite;
}

/// @brief Setter for map level
/// @param MapLevel map level
/// @return Always return true by default
bool cMapLoader::SetMapLevel(int MapLevel)
{
	this->nMapLevel = MapLevel;
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// LOADERS ///////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Load map lane from file with debug mode (optional)
/// @param sLine Line of the map lane 
/// @param bDebug Whether to print debug message or not
/// @return True if map lane was loaded successfully, false otherwise
bool cMapLoader::LoadMapLane(const std::string& sLine, bool bDebug)
{
	std::cout << sLine << std::endl;
	const size_t spacePos = sLine.find(' ');
	if (spacePos == std::string::npos) {
		std::cout << "Error: Space not found in line: " << sLine << std::endl;
		return false;
	}

	try {
		const float velocity = std::stof(sLine.substr(spacePos + 1));
		const std::string laneString = sLine.substr(0, spacePos);
		const cLane lane(velocity, laneString);
		vecLanes.push_back(lane);
		return true;
	}
	catch ([[maybe_unused]] const std::invalid_argument& e) {
		std::cout << "Error: Invalid velocity value in line: " << sLine
			<< std::endl;
		return false;
	}
	catch ([[maybe_unused]] const std::out_of_range& e) {
		std::cout << "Error: Velocity value is out of range in line: " << sLine
			<< std::endl;
		return false;
	}
}
/// @brief Load map sprite from file
///	@param sLine 
/// @param bDebug
///	@return true if map sprite was loaded successfully, false otherwise
bool cMapLoader::LoadMapSprite(const std::string& sLine, bool bDebug)
{
	std::istringstream iss(sLine);
	char token;
	iss >> token;

	if (bDebug) {
		std::cout << "# Current Line = \"" << sLine << "\" -> token=" << token << std::endl;
	}

	if (token == '$') { // New Sprite
		currentSprite = SpriteData();
		iss >> currentSprite.encode;
		if (bDebug) {
			std::cerr << "Create new Sprite('" << currentSprite.encode << "')" << std::endl;
		}
	}
	{ // Continue Loading Last Sprite
		std::string attribute, value;
		std::string raw;
		while (iss >> raw) {
			// Find the position of '=' in the raw string
			const size_t equalPos = raw.find('=');

			// Check if the format is correct (contains '=' character)
			if (equalPos != std::string::npos) {
				// Split the raw string into attribute and value based on '='
				attribute = raw.substr(0, equalPos);
				value = raw.substr(equalPos + 1);
				if (bDebug) {
					std::cerr << attribute << " vs " << value << std::endl;
				}

				if (attribute == "sprite") {
					currentSprite.sSpriteName = value;
				}
				else if (attribute == "background") {
					currentSprite.sBackgroundName = value;
				}
				else if (attribute == "category") {
					currentSprite.sCategory = value;
				}
				else if (attribute == "block") {
					if (value == "true") {
						currentSprite.isBlocked = true;
					}
					else if (value == "false")
						currentSprite.isBlocked = false;
				}
				else if (attribute == "danger") {
					if (value == "true") {
						currentSprite.isDanger = true;
					}
					else if (value == "false")
						currentSprite.isDanger = false;
				}
				else if (attribute == "platformspeed") {
					currentSprite.fPlatform = std::stof(value);
				}
				else if (attribute == "spriteX") {
					currentSprite.nSpritePosX = std::stoi(value);
				}
				else if (attribute == "spriteY") {
					currentSprite.nSpritePosY = std::stoi(value);
				}
				else if (attribute == "backgroundX") {
					currentSprite.nBackgroundPosX = std::stoi(value);
				}
				else if (attribute == "backgroundY") {
					currentSprite.nBackgroundPosY = std::stoi(value);
				}
				else if (attribute == "id") {
					currentSprite.nID = std::stoi(value);
				}
				else if (attribute == "summon") {
					char target = value[0];
					currentSprite.summon = &mapSprites[target];
				}
				else if (attribute == "duration") {
					currentSprite.fDuration = ExtractTime(value);
				}
				else if (attribute == "cooldown") {
					currentSprite.fCooldown = ExtractTime(value);
				}
				else if (attribute == "chance") {
					value.pop_back();
					currentSprite.fChance = std::stof(value);
				}
				else {
					std::cerr << "Unknown attribute = \"" << attribute << "\" assigning value \"" << value << "\"";
					std::cerr << std::endl;
				}
			}
			if (bDebug) {
				std::cerr << "Assign attribute Sprite['" << currentSprite.encode
					<< "']";
				std::cerr << "->" << attribute << " := " << value << std::endl;
			}
		}
	}
	SetSpriteData(currentSprite);
	return true;
}
/// @brief Load map name from file
///	@param sFileName - File name (std::string)
///	@return true if map name was loaded successfully, false otherwise
bool cMapLoader::LoadMapName(const std::string& sFileName)
{
	std::ifstream ifs(sFileName);
	if (!ifs.is_open()) {
		std::cout << "Failed to open file: " << sFileName << std::endl;
		std::cerr << "Error state: " << ifs.rdstate() << std::endl;
		return false;
	}

	for (std::string sLine; std::getline(ifs, sLine);) {
		strutil::deduplicate(sLine, " ");
		strutil::trim(sLine);
		const size_t nPos = sLine.find(". ");
		if (nPos != std::string::npos) {
			const size_t startMapName = nPos + 2;
			size_t endMapName = sLine.find(' ', startMapName);
			if (endMapName == std::string::npos) {
				endMapName = sLine.length();
			}
			const std::string sMapName = sLine.substr(startMapName, endMapName - startMapName);
			vecMapNames.push_back(sMapName);

			const size_t startQuotePos = sLine.find('"');
			if (startQuotePos != std::string::npos) {
				const size_t endQuotePos = sLine.find('"', startQuotePos + 1);
				if (endQuotePos != std::string::npos) {
					std::string description = sLine.substr(startQuotePos + 1, endQuotePos - startQuotePos - 1);
					vecMapDescriptions.push_back(description);
				}
			}
		}
	}
	std::cout << "Map names are successfully loaded" << std::endl;
	ifs.close();
	return true;
}
/// @brief Load map level, map sprite, and map name from file
///	@param nMapLevel - Map level
///	@return true if map level, map sprite, and map name were loaded successfully,
bool cMapLoader::LoadMapLevel(const int& nMapLevel)
{
	MapClear();
	const std::string& sFileName = "data/maps/map" + std::to_string(nMapLevel) + ".txt";
	std::ifstream ifs(sFileName);
	if (!ifs.is_open()) {
		std::cout << "Failed to open file: " << sFileName << std::endl;
		std::cerr << "Error state: " << ifs.rdstate() << std::endl;
		std::cout << "Current Working Directory: " << std::filesystem::current_path() << std::endl;
		const std::string& sFileName = "data/maps/map" + std::to_string(nMapLevel) + ".txt";
		std::cout << "File Path: " << sFileName << std::endl;
		return false;
	}

	bool isLoadingSprite = false;
	for (std::string sLine; std::getline(ifs, sLine);) {
		strutil::deduplicate(sLine, " ");
		strutil::trim(sLine);
		if (sLine.empty())
			break;

		if (sLine.front() == '#') {
			if (isLoadingSprite) {
				break;
			}
			isLoadingSprite = true;
			continue;
		}

		if (isLoadingSprite) {
			LoadMapSprite(sLine);
		}
		else {
			LoadMapLane(sLine);
		}
	}
	UpdatePattern();
	ifs.close();
	return true;
}
/// @brief Load map level by current map level
/// @return True if map level, map sprite, and map name were loaded successfully, false otherwise
bool cMapLoader::LoadMapLevel()
{
	return LoadMapLevel(GetMapLevel());
}

/// @brief 
/// @param timeStr 
/// @return 
float cMapLoader::ExtractTime(const std::string& timeStr)
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
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// END OF FILE /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
