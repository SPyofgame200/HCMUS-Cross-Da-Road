/**
 * @file cMapLoader.cpp
 *
 * @brief Contains cMapLoader class implementation
 *
 * This file implements cMapLoader class for map loading and manipulation in game.
**/

#include "cMapLoader.h"
#include <iostream>

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
	std::cerr << "cMapLoader::~cMapLoader(): Successfully destructed" << std::endl;
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
	platformPattern.clear();
	dangerPattern.clear();
	blockPattern.clear();
	for (const auto& pair : mapSprites) {
		const auto& sprite = pair.second;
		if (sprite.IsPlatform()) {
			platformPattern += sprite.GetCode();
		}
		if (sprite.IsBlocked()) {
			blockPattern += sprite.GetCode();
		}
		if (sprite.IsDanger()) {
			dangerPattern += sprite.GetCode();
		}
		std::cout << sprite.ShowData() << std::endl;
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
std::vector<cMapLane> cMapLoader::GetLanes() const
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
MapObject cMapLoader::GetSpriteData(char graphic) const
{
	const auto spriteIter = mapSprites.find(graphic);
	if (spriteIter != mapSprites.end()) {
		return spriteIter->second;
	}
	else {
		return MapObject();
	}
}
/// @brief Getter for danger pattern
std::string cMapLoader::GetPlatformPattern() const
{
	return platformPattern;
}
/// @brief Getter for danger pattern
std::string cMapLoader::GetDangerPattern() const
{
	return dangerPattern;
}
/// @brief Getter for block pattern
std::string cMapLoader::GetBlockPattern() const
{
	return blockPattern;
}
/// @brief Getter for lane by position
/// @param fPos Index of the lane in vector
cMapLane cMapLoader::GetLane(int fPos) const
{
	return vecLanes[fPos];
}
/// @brief Getter for lane by position (floor)
/// @param fPos Index of the lane in vector
cMapLane cMapLoader::GetLaneFloor(float fPos) const
{
	return GetLane(static_cast<int>(std::floor(fPos)));
}
/// @brief Getter for lane by position (round)
/// @param fPos Index of the lane in vector
cMapLane cMapLoader::GetLaneRound(float fPos) const
{
	return GetLane(static_cast<int>(std::round(fPos)));
}
/// @brief Getter for lane by position (ceil)
/// @param fPos Index of the lane in vector
cMapLane cMapLoader::GetLaneCeil(float fPos) const
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
bool cMapLoader::SetSpriteData(const MapObject& data)
{
	const bool bOverwrite = mapSprites.count(data.GetCode());
	mapSprites[data.GetCode()] = data;
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
bool cMapLoader::LoadMapLane(const std::string& sLine, int nLaneID)
{
	std::stringstream ss(sLine);
	std::string sLane;
	float fVelocity;

	// Read lane, velocity, and background from the line
	if (!(ss >> sLane >> fVelocity)) {
		std::cerr << "cMapLoader::LoadMapLane(\"" << sLine << "\", id=" << nLaneID << "): ";
		std::cerr << "Error: Failed to parse line, extracted content: ";
		std::cerr << "sLane[" << sLane.size() << "], fVelocity=" << fVelocity << std::endl;
		return false;
	}

	std::string sUnderlay = "";
	int nFrame = 0;
	ss >> sUnderlay >> nFrame;

	std::cout << "Line #" << nLaneID << ": sLane[" << sLane.size() << "] = \"" << sLane << "\", speed=" << fVelocity;
	if (sUnderlay.size()) {
		std::cout << " underlay = \"" << sUnderlay << "\"";
	}
	else {
		std::cout << " no-underlay";
	}
	std::cout << std::endl;
	const cMapLane lane(fVelocity, sLane, nLaneID, sUnderlay, nFrame);
	vecLanes.push_back(lane);
	return true;
}
/// @brief Load map sprite from file
///	@param sLine Line of the map sprite
/// @param bDebug Whether to print debug message or not
///	@return true if map sprite was loaded successfully, false otherwise
bool cMapLoader::LoadMapSprite(const std::string& sLine)
{
	std::istringstream iss(sLine);
	char token;
	iss >> token;
	// Create a new Sprite
	if (token == '$') { 
		char token;
		iss >> token;
		currentSprite = MapObject(token);
	}
	/// Alow sprite data to be read as multiple lines
	if (token == '$' || token == ':')
	{
		std::string sData;
		while (iss >> sData) {
			currentSprite.SetAttributeFromData(sData);
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
		utils::deduplicate(sLine, " ");
		utils::trim(sLine);
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
		const std::string& sFileName = "data/maps/map" + std::to_string(nMapLevel) + ".txt";
		std::cout << "File Path: " << sFileName << std::endl;
		return false;
	}

	int nLaneID = 0;
	bool bLoadingSprite = false;
	for (std::string sLine; std::getline(ifs, sLine);) {
		utils::deduplicate(sLine, " ");
		utils::trim(sLine);
		if (sLine.empty())
			break;

		if (sLine.front() == '#') {
			if (bLoadingSprite) {
				break;
			}
			bLoadingSprite = true;
			continue;
		}

		if (bLoadingSprite) {
			LoadMapSprite(sLine);
		}
		else {
			LoadMapLane(sLine, nLaneID++);
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

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// END OF FILE /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

