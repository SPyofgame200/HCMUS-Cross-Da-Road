#ifndef C_ASSET_MANAGER_H
#define C_ASSET_MANAGER_H

#include "uAppConst.h"
#include <map>
#include "gSprite.h"

/**
 * @file cAssetManager.h
 * @brief Contains asset manager class
 *
 * This file contains asset manager class that manages assets (sprites, sounds, etc.).
**/

/// @brief Singleton class for asset management
class cAssetManager
{
private:
	std::map<std::string, app::Sprite*> mapSprites; ///< map of sprites that converts string to sprite
	std::string sDirectoryPath;
	std::string sFileExtension;

public: // Constructor & Destructor
	cAssetManager();
	~cAssetManager();

private: // Debugging purposes
	bool ReportLoadingResult(bool bSuccess, const std::string& sSpriteCategory);

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
	bool LoadMenuSprites();
	bool LoadSettingSprites();
	bool LoadAboutUsSprites();
	bool LoadExitSprites();
	bool LoadPauseSprites();
	bool LoadFontSprites();
	bool LoadScoreBarSprites();

public: // Player Loaders
	bool LoadPlayerIdleSprites();
	bool LoadPlayerJumpSprites();
	bool LoadPlayerDeathSprites();

public: // Map Loaders
	bool LoadMapHalloweenSprites();
	bool LoadMapRiverSideSprites();
	bool LoadMapIceAgeSprites();
	bool LoadMapVolcanoSprites();
	bool LoadMapOceanSprites();

public: // Loaders
	bool LoadSprite(const std::string& sName, const std::string& sFileName);
	bool LoadAnimation(const std::string& sName, const std::string& sFileName, int nMaxFrame);
	bool LoadAllSprites();
};

#endif // C_ASSET_MANAGER_H
