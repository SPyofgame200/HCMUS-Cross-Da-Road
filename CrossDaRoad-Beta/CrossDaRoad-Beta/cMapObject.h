/**
 * @file cMapObject.h
 * @brief Contains MapObject class
 *
 * This file contains prototype of MapObject class
 */


#ifndef C_MAP_OBJECT_H
#define C_MAP_OBJECT_H

#include <string>

 /// @brief Sprite data for drawing and collision detection (block, danger, platform, etc.)
class MapObject
{
private: // Identity attributes
	char code;                ///< Sprite code chacters for map editor
	std::string sCategory;      ///< Category, allow categorize configuration if needed

private: // Flag attributes
	bool isBlocked;             ///< If the player shouldn't be able to move here
	bool isDanger;              ///< If the player should be killed to move here

private: // Sprite attributes
	std::string sSpriteName;    ///< Sprite name (*.png), for sprite loading
	int32_t nSpritePosX;        ///< X initial position for drawing sprite
	int32_t nSpritePosY;        ///< Y initial position for drawing sprite
	int32_t nID;                ///< The ID of the sprite, for player customization
	
private: // Background attributes
	std::string sBackgroundName;///< Background name (*.png), for sprite's background
	int32_t nBackgroundPosX;    ///< X initial position for drawing background
	int32_t nBackgroundPosY;    ///< Y initial position for drawing background
	
private: // Lane attributes
	float fPlatform;            ///< Platform dragging speed if the player land on them

private: // Summon attributes
	char summon;			    ///< The chance of summoning another sprite with encoded = summon
	float fDuration;            ///< The duration (in seconds) of that sprite to be appeared
	float fCooldown;            ///< The cooldown durations for the two consecutive summoning
	float fChance;              ///< The probability of summoning in each second

public: // Constructors & Destructor
	MapObject();						///< Constructor
	MapObject(char code);				///< Constructor
	~MapObject();					 	///< Destructor

public: // Initializer & Cleanup
	bool Create();
	bool Destroy();

public: // Checkers
	bool IsBlocked() const;
	bool IsDanger() const;

public: // Getters
	char GetCode() const;
	std::string GetCategory() const;
	std::string GetSpriteName() const;
	int32_t GetSpritePosX() const;
	int32_t GetSpritePosY() const;
	int32_t GetSpriteFrameCount() const;
	std::string GetBackgroundName() const;
	int32_t GetBackgroundPosX() const;
	int32_t GetBackgroundPosY() const;
	float GetPlatformDragSpeed() const;
	char GetSummonTarget() const;
	float GetSummonDuration() const;
	float GetSummonCooldown() const;
	float GetSummonProbability() const;

public: // Output
	std::string ShowIdentityData() const;  ///< ShowData
	std::string ShowFlagData() const;  ///< ShowData
	std::string ShowSpriteData() const;  ///< ShowData
	std::string ShowBackgroundData() const;  ///< ShowData
	std::string ShowLaneData() const;  ///< ShowData
	std::string ShowSummonData() const;  ///< ShowData
	std::string ShowData() const;  ///< ShowData
	friend std::ostream& operator<<(std::ostream& output, const MapObject& obj);

public: // Extracters
	bool ExtractToken(char &token, const std::string& sData);
	bool ExtractTime(float &fTime, const std::string& sData);
	bool ExtractName(std::string &sName, const std::string& sData);
	bool ExtractFlag(bool &bFlag, const std::string& sData);
	bool ExtractPosition(int32_t &nPos, const std::string& sData);
	bool ExtractFloat(float &fFloat, const std::string& sData);
	bool ExtractPercentage(float &fPercentage, const std::string& sData);
	bool ExtractAttributeValue(std::string& sAttribute, std::string& sValue, const std::string& sData);

public: // Setters
	bool SetIdentityAttribute(const std::string& sAttribute, const std::string& sValue);
	bool SetFlagAttribute(const std::string& sAttribute, const std::string& sValue);
	bool SetSpriteAttribute(const std::string& sAttribute, const std::string& sValue);
	bool SetBackgroundAttribute(const std::string& sAttribute, const std::string& sValue);
	bool SetLaneAttribute(const std::string& sAttribute, const std::string& sValue);
	bool SetSummonAttribute(const std::string& sAttribute, const std::string& sValue);
	bool SetAttribute(const std::string& sAttribute, const std::string& sValue);
	bool SetAttributeFromData(const std::string& sData);
};

#endif // C_MAP_OBJECT_H