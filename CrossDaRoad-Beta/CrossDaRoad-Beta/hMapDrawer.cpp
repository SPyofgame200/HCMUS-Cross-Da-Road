/**
 * @file hMapDrawer.cpp
 * @brief Implements map drawer class for drawing map on screen
 *
**/

#include "cFrameManager.h"
#include "cApp.h"

//=================================================================================================
// Include new header files here

//=================================================================================================

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// CONSTRUCTORS & DESTRUCTOR /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Default constructor
hMapDrawer::GraphicCell::GraphicCell()
{
    graphic = 0;
    nRowPos = 0;
    nColPos = 0;
}

/// @brief Parameterized constructor
hMapDrawer::GraphicCell::GraphicCell(char graphic, int nRowPos, int nColPos)
{
    this->graphic = graphic;
    this->nRowPos = nRowPos;
    this->nColPos = nColPos;
}

/// @brief Destructor
hMapDrawer::GraphicCell::~GraphicCell() = default;

/// @brief Default constructor
hMapDrawer::hMapDrawer() : app(nullptr)
{
}

/// @brief Parameterized constructor
/// @param app Pointer to the application
hMapDrawer::hMapDrawer(cApp* app) : app(nullptr)
{
    SetupTarget(app);
}

/// @brief Destructor
hMapDrawer::~hMapDrawer()
{
    app = nullptr;
    //std::cerr << "hMapDrawer::~hMapDrawer(): Successfully destructed" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// SETTERS /////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Sets the target application
/// @param app Pointer to the application
/// @return True if successful, false otherwise
bool hMapDrawer::SetupTarget(cApp* app)
{
    if (app == nullptr) {
        return false;
    }
    this->app = app;
    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// DRAWERS /////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Get lane backgrounds on screen
/// @param Lane Lane to be drawn
/// @return Vector of graphic cells representing the lane backgrounds
hMapDrawer::GraphicLane hMapDrawer::GetLaneBackgrounds(const cMapLane& Lane) const
{
    const int nRow = Lane.GetLaneID();
    const int nStartPos = Lane.GetStartPos(app->fTimeSinceStart);

    GraphicLane Backgrounds;
    for (int nCol = -1; nCol < app_const::LANE_WIDTH; nCol++) {
        const char graphic = Lane.GetLaneGraphic(nStartPos + nCol);
        Backgrounds.push_back(GraphicCell(graphic, nRow * app_const::CELL_SIZE, nCol * app_const::CELL_SIZE));
    }

    return Backgrounds;
}

/// @brief Get lane objects on screen
/// @param Lane Lane to be drawn
/// @return Vector of graphic cells representing the lane objects
hMapDrawer::GraphicLane hMapDrawer::GetLaneEntities(const cMapLane& Lane) const
{
    const int nRow = Lane.GetLaneID();
    const int nStartPos = Lane.GetStartPos(app->fTimeSinceStart);
    const int nCellOffset = Lane.GetCellOffset(app_const::CELL_SIZE, app->fTimeSinceStart);

    GraphicLane Objects;
    for (int nCol = -1; nCol < app_const::LANE_WIDTH; nCol++) {
        const char graphic = Lane.GetLaneGraphic(nStartPos + nCol);
        const int nPosX = nRow * app_const::CELL_SIZE;
        const int nPosY = nCol * app_const::CELL_SIZE - nCellOffset;
        Objects.push_back(GraphicCell(graphic, nPosX, nPosY));
    }

    for (int id = 0; id < Objects.size(); ++id) {
        const GraphicCell& Cell = Objects[id];
        if (SuccessSummon(Cell.graphic, id)) {
            const MapObject& sprite = app->MapLoader.GetSpriteData(Cell.graphic);
            Objects.push_back(GraphicCell(sprite.GetSummon(), Cell.nRowPos, Cell.nColPos));
        }
    }

    return Objects;
}

bool hMapDrawer::DrawUnderlay(const cMapLane& Lane) const
{
    if (Lane.HasUnderlay()) {
        constexpr int32_t nPosX = 0;
        const int32_t nPosY = Lane.GetLaneID() * app_const::CELL_SIZE;
        const int nFrameCount = Lane.GetUnderlayFrameCount();
        const std::string sUnderlay = Lane.GetUnderlay() + cFrameManager::GetInstance().ShowFrameID(nFrameCount, 0.001f);
        const app::Sprite* pUnderlay = cAssetManager::GetInstance().GetSprite(sUnderlay);
        app->SetPixelMode(app::Pixel::MASK);
        app->DrawSprite(nPosX, nPosY, pUnderlay);
        app->SetPixelMode(app::Pixel::NORMAL);
        return true;
    }
    return false;
}

/// @brief Draw lane on screen
/// @param lane Lane to be drawn
/// @return True if successful, false otherwise
bool hMapDrawer::DrawLane(const cMapLane& Lane) const
{
    const GraphicLane Backgrounds = GetLaneBackgrounds(Lane);
    for (const GraphicCell& BackgroundCell : Backgrounds) {
        DrawBackground(BackgroundCell);
        SetHitBox(BackgroundCell);
    }

    const GraphicLane Objects = GetLaneEntities(Lane);
    for (const GraphicCell& ObjectCell : Objects) {
        DrawEntity(ObjectCell);
        SetHitBox(ObjectCell);
    }

    return true;
}

/// @brief Draw all lanes on screen
/// @return Always true by default
bool hMapDrawer::DrawAllLanes() const
{
    const std::vector<cMapLane> vecLanes = app->MapLoader.GetLanes();
    for (const cMapLane& lane : vecLanes) {
        DrawUnderlay(lane);
        DrawLane(lane);
    }

    return true;
}

/// @brief Draw object on screen
/// @param Cell Cell to be drawn
/// @return Always true by default
bool hMapDrawer::DrawEntity(const GraphicCell& Cell) const
{
    const MapObject sprite = app->MapLoader.GetSpriteData(Cell.graphic);
    const int32_t nDrawX = sprite.GetSpritePosX();
    const int32_t nDrawY = sprite.GetSpritePosY();
    const std::string sName = sprite.GetSpriteName();
    const std::string sFrameID = cFrameManager::GetInstance().ShowFrameID(sprite.GetSpriteFrameCount());
    if (sName.empty()) {
        return false;
    }
    app->SetPixelMode(app::Pixel::MASK);
    return DrawGraphic(Cell, sName + sFrameID, nDrawX, nDrawY);
}

/// @brief Draw background on screen
/// @param Cell Graphic cell to be drawn
/// @return Always true by default
bool hMapDrawer::DrawBackground(const GraphicCell& Cell) const
{
    const MapObject sprite = app->MapLoader.GetSpriteData(Cell.graphic);
    const int32_t nDrawX = sprite.GetBackgroundPosX();
    const int32_t nDrawY = sprite.GetBackgroundPosY();
    const std::string sName = sprite.GetBackgroundName();
    const std::string sFrameID = cFrameManager::GetInstance().ShowFrameID(sprite.GetBackgroundFrameCount());
    if (sName.empty()) {
        return false;
    }
    app->SetPixelMode(app::Pixel::NORMAL);
    return DrawGraphic(Cell, sName + sFrameID, nDrawX, nDrawY);
}

bool hMapDrawer::DrawGraphic(const GraphicCell &Cell, const std::string& sName, int nDrawX, int nDrawY) const
{
    const app::Sprite* background = cAssetManager::GetInstance().GetSprite(sName);
    app->DrawPartialSprite(Cell.nColPos, Cell.nRowPos, background, nDrawX * app_const::SPRITE_WIDTH, nDrawY * app_const::SPRITE_HEIGHT);
    app->SetPixelMode(app::Pixel::NORMAL);
    return true;
}

void hMapDrawer::SetHitBox(const GraphicCell& Cell) const
{
    app->cDangerZone.Fill(Cell.graphic, Cell.nColPos, Cell.nRowPos);
    app->cBlockedZone.Fill(Cell.graphic, Cell.nColPos, Cell.nRowPos);
    app->cWinningZone.Fill(Cell.graphic, Cell.nColPos, Cell.nRowPos);
    app->cPlatformZone.Fill(Cell.graphic, Cell.nColPos, Cell.nRowPos);
}
//=================================================================================================

#include <random>
#include <iomanip>
std::default_random_engine generator(std::random_device{}());
std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
std::map<int, float> mapLastSummon;

//=================================================================================================

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// GENERATORS //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Summon object on screen randomly
/// @param graphic Character representing the object
/// @param nID ID of the object
/// @return True if successful, false otherwise
bool hMapDrawer::SuccessSummon(char graphic, int nID) const
{
    const MapObject& sprite = app->MapLoader.GetSpriteData(graphic);
    if (sprite.GetSummon() == 0 || sprite.GetSummonChance() <= 0) {
        return false; // Summon is not enabled or chance is zero or negative
    }

    const float fCurrentTime = app->fTimeSinceStart;
    const int fps = app->GetAppFPS();
    if (mapLastSummon.count(nID) == false) {
        const float fMinTime = fCurrentTime + sprite.GetSummonPredelay();
        const float fMaxTime = fCurrentTime + sprite.GetSummonPredelay() + sprite.GetSummonDuration();
        std::uniform_real_distribution<float> initialDistribution(fMinTime, fMaxTime);
        mapLastSummon[nID] = initialDistribution(generator);
    }
    float& fLastSummon = mapLastSummon[nID];
    const float fDeltaTime = fCurrentTime - fLastSummon;

    if (fDeltaTime >= 0) {
        if (fDeltaTime <= sprite.GetSummonDuration()) {
            return true;
        }
        else if (fDeltaTime < sprite.GetSummonDuration() + sprite.GetSummonCooldown()) {
            return false;
        }
    }

    if (app->IsEnginePause()) {
        return false;
    }

    const auto fProbability = static_cast<float>(sprite.GetSummonChance() / 100.0 / (fps == 0 ? 1 : fps));
    const float fGenerated = distribution(generator);
    if (fGenerated < fProbability) {
        fLastSummon = fCurrentTime;
        return true;
    }
    return false; // Summon is not successful
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// END OF FILE /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////