#include "cMapObject.h"
#include <iostream>
#include <chrono>
#include <map>

/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// CONSTRUCTORS & DESTRUCTOR ////////////////////////////////////
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
	summon = nullptr;
	fDuration = 0;
	fCooldown = 0;
	fChance = 0;
}

/// @brief Destructor (clears the strings)
MapObject::~MapObject()
{
	sSpriteName.clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// METHODS ///////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

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
bool MapObject::SuccessSummon(int nCol, int nRow, float fCurrentTime, int fps, bool bCreateAllow) const
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

	if (!bCreateAllow) {
		return false;
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