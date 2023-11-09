#include "cAssetManager.h"

//////////////////////////////////////////////////////////////////////////
////////////////// CONSTRUCTORS and DESTRUCTORS //////////////////////////
//////////////////////////////////////////////////////////////////////////

/// @brief Default constructor
cAssetManager::cAssetManager()
{
    sDirectoryPath = ".";
    sFileExtension = "png";
}
/// @brief Destructor
cAssetManager::~cAssetManager()
{
    mapSprites.clear();
    sDirectoryPath.clear();
    sFileExtension.clear();
}

//////////////////////////////////////////////////////////////////////////
////////////////////////// GETTERS  //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/// @brief Getter for singleton instance
cAssetManager& cAssetManager::GetInstance()
{
    static cAssetManager instance;
    return instance;
}
/// @brief Getter for sprite with name
/// @param sName Name of sprite stored in mapSprites
app::Sprite* cAssetManager::GetSprite(const std::string& sName)
{
    if (mapSprites.find(sName) == mapSprites.end()) {
        std::cerr << "Failed to find sprite (\"" << sName << "\")" << std::endl;
        return nullptr;
    }
    else {
        return mapSprites[sName];
    }
}
/// @brief Getter for file location
/// @param sFileName Name of file
std::string cAssetManager::GetFileLocation(const std::string& sFileName) const
{
    return sDirectoryPath + "/" + sFileName + "." + sFileExtension;
}

//////////////////////////////////////////////////////////////////////////
////////////////////////// SETTERS  //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/// @brief Setter for directory path
/// @param sPath String of directory path
void cAssetManager::SetDirectoryPath(const std::string& sPath)
{
    sDirectoryPath = sPath;
}
/// @brief Setter for file extension
/// @param sExtension String of file extension
void cAssetManager::SetFileExtension(const std::string& sExtension)
{
    sFileExtension = sExtension;
}

//////////////////////////////////////////////////////////////////////////
////////////////////////// DEBUGGING /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/// @brief Print loading result to console
/// @param bSuccess Whether loading is successful or not
/// @param sSpriteCategory String of sprite category
/// @return True if loading is successful, false otherwise
bool cAssetManager::ReportLoadingResult(bool bSuccess, const std::string& sSpriteCategory)
{
    if (bSuccess) {
        std::cout << "Successfully loaded all " << sSpriteCategory << " sprites" << std::endl;
        return true;
    }
    else {
        std::cerr << "Failed to load some " << sSpriteCategory << " sprites" << std::endl;
        return false;
    }
}

//////////////////////////////////////////////////////////////////////////
////////////////////////// GAME LOADERS //////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/// @brief Load all menu sprites
/// @return True if loading is successful, false otherwise
bool cAssetManager::LoadMenuSprites()
{
    bool bSuccess = true;
    bSuccess &= LoadSprite("menu_background", "console_menu");
    bSuccess &= LoadSprite("new_game", "new_game");
    bSuccess &= LoadSprite("continue", "continue");
    bSuccess &= LoadSprite("setting", "setting");
    bSuccess &= LoadSprite("about_us", "about_us");
    bSuccess &= LoadSprite("exit", "exit");
    bSuccess &= LoadSprite("new_game_chosen", "new_game_chosen");
    bSuccess &= LoadSprite("continue_chosen", "continue_chosen");
    bSuccess &= LoadSprite("setting_chosen", "setting_chosen");
    bSuccess &= LoadSprite("about_us_chosen", "about_us_chosen");
    bSuccess &= LoadSprite("exit_chosen", "exit_chosen");

    return ReportLoadingResult(bSuccess, "menu");
}
/// @brief Load all setting sprites
/// @return True if loading is successful, false otherwise
bool cAssetManager::LoadSettingSprites()
{
    bool bSuccess = true;
    bSuccess &= LoadSprite("sound_on", "sound_on");
    bSuccess &= LoadSprite("sound_off", "sound_off");
    bSuccess &= LoadSprite("move_wsad", "move_wsad");
    bSuccess &= LoadSprite("move_arrow", "move_arrow");
    bSuccess &= LoadSprite("sound_on_chosen", "sound_on_chosen");
    bSuccess &= LoadSprite("sound_off_chosen", "sound_off_chosen");
    bSuccess &= LoadSprite("move_wsad_chosen", "move_wsad_chosen");
    bSuccess &= LoadSprite("move_arrow_chosen", "move_arrow_chosen");

    return ReportLoadingResult(bSuccess, "setting");
}
/// @brief Load all about us sprites
/// @return True if loading is successful, false otherwise
bool cAssetManager::LoadAboutUsSprites()
{
    bool bSuccess = true;
    bSuccess &= LoadAnimation("about_us_page", "about_us_page", 4);

    return ReportLoadingResult(bSuccess, "about us");
}
/// @brief Load all exit sprites
/// @return True if loading is successful, false otherwise
bool cAssetManager::LoadExitSprites()
{
    bool bSuccess = true;
    bSuccess &= LoadSprite("exit_no", "exit_no");
    bSuccess &= LoadSprite("exit_yes", "exit_yes");

    return ReportLoadingResult(bSuccess, "exit");
}
/// @brief Load all pause sprites
/// @return True if loading is successful, false otherwise
bool cAssetManager::LoadPauseSprites()
{
    bool bSuccess = true;
    bSuccess &= LoadSprite("black_alpha", "black_alpha170");
    bSuccess &= LoadSprite("pause_exit", "pause_exit");
    bSuccess &= LoadSprite("pause_resume", "pause_resume");
    bSuccess &= LoadSprite("pause_save", "pause_save");

    return ReportLoadingResult(bSuccess, "pause");
}
/// @brief Load all font sprites
/// @return True if loading is successful, false otherwise
bool cAssetManager::LoadFontSprites()
{
    bool bSuccess = true;
    bSuccess &= LoadSprite("font", "alphabet_black");

    return ReportLoadingResult(bSuccess, "font");
}
/// @brief Load all score bar sprites
/// @return True if loading is successful, false otherwise
bool cAssetManager::LoadScoreBarSprites()
{
    bool bSuccess = true;
    bSuccess &= LoadAnimation("score_bar", "score_bar", 4);

    return ReportLoadingResult(bSuccess, "score bar");
}

//////////////////////////////////////////////////////////////////////////
////////////////////////// PLAYER LOADERS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/// @brief Load all player idle sprites
/// @return True if loading is successful, false otherwise
bool cAssetManager::LoadPlayerIdleSprites()
{
    bool bSuccess = true;
    bSuccess &= LoadSprite("froggy", "froggy");
    bSuccess &= LoadSprite("froggy_left", "froggy_left");

    return ReportLoadingResult(bSuccess, "player idle");
}
/// @brief Load all player jump sprites
/// @return True if loading is successful, false otherwise
bool cAssetManager::LoadPlayerJumpSprites()
{
    bool bSuccess = true;
    bSuccess &= LoadAnimation("froggy_jump", "froggy_jump", 6);
    bSuccess &= LoadAnimation("froggy_jump_left", "froggy_jump_left", 6);

    return ReportLoadingResult(bSuccess, "player jump");
}
/// @brief Load all player death sprites
/// @return True if loading is successful, false otherwise
bool cAssetManager::LoadPlayerDeathSprites()
{
    bool bSuccess = true;
    bSuccess &= LoadAnimation("froggy_death", "froggy_death", 6);

    return ReportLoadingResult(bSuccess, "player death");
}

//////////////////////////////////////////////////////////////////////////
////////////////////////// MAP LOADERS ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/// @brief Load all halloween map sprites
/// @return True if loading is successful, false otherwise
bool cAssetManager::LoadMapHalloweenSprites()
{
    bool bSuccess = true;
    bSuccess &= LoadSprite("black", "black");
    bSuccess &= LoadSprite("ghost", "ghost");
    bSuccess &= LoadSprite("reaper", "reaper");
    bSuccess &= LoadSprite("road3", "road3");
    bSuccess &= LoadSprite("road", "road");
    bSuccess &= LoadSprite("road2", "road2");
    bSuccess &= LoadSprite("pumpkin", "pumpkin");

    return ReportLoadingResult(bSuccess, "Halloween map");
}
/// @brief Load all river side map sprites
/// @return True if loading is successful, false otherwise
bool cAssetManager::LoadMapRiverSideSprites()
{
    bool bSuccess = true;
    bSuccess &= LoadSprite("alligator", "alligator");
    bSuccess &= LoadSprite("alligator_1", "alligator_1");
    bSuccess &= LoadSprite("kiwi", "kiwi_bird");
    bSuccess &= LoadSprite("wood1", "wood1");
    bSuccess &= LoadSprite("wood2", "wood2");
    bSuccess &= LoadSprite("wood3", "wood3");
    bSuccess &= LoadSprite("soil", "soil");
    bSuccess &= LoadSprite("lilypad", "lilypad");
    bSuccess &= LoadSprite("water", "water");
    bSuccess &= LoadSprite("tree", "tree");
    bSuccess &= LoadSprite("grass", "grass");

    return ReportLoadingResult(bSuccess, "River Side map");
}
/// @brief Load all ice age map sprites
/// @return True if loading is successful, false otherwise
bool cAssetManager::LoadMapIceAgeSprites()
{
    bool bSuccess = true;
    bSuccess &= LoadSprite("penguin", "penguin");
    bSuccess &= LoadSprite("snow_soil", "snow_soil");
    bSuccess &= LoadSprite("snowed_grass", "snowed_grass");
    bSuccess &= LoadSprite("ice", "ice");
    bSuccess &= LoadSprite("mamut", "mamut");

    return ReportLoadingResult(bSuccess, "Ice Age map");
}
/// @brief Load all volcano map sprites
/// @return True if loading is successful, false otherwise
bool cAssetManager::LoadMapVolcanoSprites()
{
    bool bSuccess = true;
    bSuccess &= LoadSprite("pavement", "wall");
    bSuccess &= LoadSprite("wall", "wall");
    bSuccess &= LoadSprite("volcano", "volcano");
    bSuccess &= LoadSprite("magma", "magma");
    bSuccess &= LoadSprite("pinetree", "pinetree");
    bSuccess &= LoadAnimation("fire", "fire", 4);

    return ReportLoadingResult(bSuccess, "Volcano map");
}
/// @brief Load all ocean map sprites
/// @return True if loading is successful, false otherwise
bool cAssetManager::LoadMapOceanSprites()
{
    bool bSuccess = true;
    bSuccess &= LoadSprite("sand", "sand");
    bSuccess &= LoadSprite("coconut", "coconut");
    bSuccess &= LoadSprite("ocean", "ocean");
    bSuccess &= LoadAnimation("crab", "crab", 4);

    return ReportLoadingResult(bSuccess, "Ocean map");
}

//////////////////////////////////////////////////////////////////////////
////////////////////////// LOADERS ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/// @brief Load particular sprite
/// @param sName Name of sprite that will be stored in map of sprites
/// @param sFileName Name of file that contains sprite
/// @return True if loading is successful, false otherwise
bool cAssetManager::LoadSprite(const std::string& sName, const std::string& sFileName)
{
    auto* spr = new app::Sprite(GetFileLocation(sFileName));
    if (spr == nullptr || spr->GetData() == nullptr) {
        std::cerr << "cAssetManager::LoadSprite(name=\"" << sName << "\", filename=\"" << sFileName << "\"): ";
        std::cerr << "Can not found with file \"" << GetFileLocation(sFileName) << "\"" << std::endl;
        return false;
    }
    mapSprites[sName] = spr;
    return true;
}
/// @brief Load particular animation of sprites
/// @param sName Name of animation that will be stored in map of sprites
/// @param sFileName Name of file that contains animation of sprites
/// @param nMaxFrame Maximum frame of animation
/// @return True if loading is successful, false otherwise
bool cAssetManager::LoadAnimation(const std::string& sName, const std::string& sFileName, const int nMaxFrame)
{
    bool bSuccess = true;
    for (int nFrame = 1; nFrame <= nMaxFrame; ++nFrame) {
        const std::string sFrame = std::to_string(nFrame);
        bSuccess &= LoadSprite(sName + sFrame, sFileName + sFrame);
    }
    return bSuccess;
}
/// @brief Load all sprites in game
/// @return True if loading is successful, false otherwise
bool cAssetManager::LoadAllSprites()
{
    SetDirectoryPath("./data/assets");
    SetFileExtension("png");

    bool bSuccess = true;
    bSuccess &= LoadMenuSprites();
    bSuccess &= LoadSettingSprites();
    bSuccess &= LoadAboutUsSprites();
    bSuccess &= LoadExitSprites();
    bSuccess &= LoadPauseSprites();
    bSuccess &= LoadFontSprites();
    bSuccess &= LoadScoreBarSprites();
    bSuccess &= LoadPlayerIdleSprites();
    bSuccess &= LoadPlayerJumpSprites();
    bSuccess &= LoadPlayerDeathSprites();
    bSuccess &= LoadMapHalloweenSprites();
    bSuccess &= LoadMapRiverSideSprites();
    bSuccess &= LoadMapIceAgeSprites();
    bSuccess &= LoadMapVolcanoSprites();
    bSuccess &= LoadMapOceanSprites();

    return ReportLoadingResult(bSuccess, "all");
}

//////////////////////////////////////////////////////////////////////////
////////////////////////// END OF FILE ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////