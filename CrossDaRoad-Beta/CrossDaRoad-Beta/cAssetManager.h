/**
 * @file cAssetManager.h
 * @brief Contains asset manager class
 *
 * This file contains asset manager class that manages assets (sprites, sounds, etc.).
**/

#ifndef C_ASSET_MANAGER_H
#define C_ASSET_MANAGER_H

#include <map>
#include "gSprite.h"

/// @brief Singleton class for asset management
class cAssetManager
{
private: // Properties
	std::map<std::string, app::Sprite*> mapSprites; ///< map of sprites that converts string to sprite
	std::string sDirectoryPath;
	std::string sFileExtension;

private: // Constructor & Destructor
	cAssetManager();
	~cAssetManager();

private: // Debugging purposes
	static bool ReportLoadingResult(bool bSuccess, const std::string& sSpriteCategory);

public: // Avoid conflicts
	cAssetManager(cAssetManager const&) = delete;
	void operator=(cAssetManager const&) = delete;

public: // Getters
	static cAssetManager& GetInstance();
	app::Sprite* GetSprite(const std::string& sName);
	std::string GetFileLocation(const std::string& sFileName) const;

public: // Setters
	void SetDirectoryPath(const std::string& sPath);
	void SetFileExtension(const std::string& sExtension);

public: // Game Loaders
	bool LoadNameBoxSprites();
	bool LoadMenuSprites();
	bool LoadContinueSprites();
	bool LoadSettingSprites();
	bool LoadAboutUsSprites();
	bool LoadExitSprites();
	bool LoadPauseSprites();
	bool LoadGameOverSprites();
	bool LoadFontSprites();
	bool LoadFont1Sprites();
	bool LoadScoreBarSprites();

private: // Player Loaders
	bool LoadPlayerIdleSprites();
	bool LoadPlayerJumpSprites();
	bool LoadPlayerSwimSprites();
	bool LoadPlayerDeathSprites();

private: // Map Loaders
	bool LoadMapHalloweenSprites();
	bool LoadMapRiverSideSprites();
	bool LoadMapIceAgeSprites();
	bool LoadMapVolcanoSprites();
	bool LoadMapBeachSprites();
	bool LoadMapOceanSprites();

private: // Loaders
	bool LoadSprite(const std::string& sName, const std::string& sFileName);
	bool LoadAnimation(const std::string& sName, const std::string& sFileName, int nMaxFrame);

public: // Loaders
	bool LoadAllSprites();
};

#endif // C_ASSET_MANAGER_H
