/**
 * @file hMapDrawer.cpp
 * @brief Implements map drawer class for drawing map on screen
 *
**/

#include "hMapDrawer.h"
#include "cApp.h"
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// CONSTRUCTORS & DESTRUCTOR /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Default constructor
GraphicCell::GraphicCell()
{
	graphic = 0;
	nCellOffset = 0;
	nRow = 0;
	nCol = 0;
}

/// @brief Parameterized constructor
GraphicCell::GraphicCell(char graphic, int nCellOffset, int nRow, int nCol, float fLastDrawn)
{
	this->graphic = graphic;
	this->nCellOffset = nCellOffset;
	this->nRow = nRow;
	this->nCol = nCol;
	this->fLastDrawn = fLastDrawn;
}

/// @brief Destructor
GraphicCell::~GraphicCell() = default;

/// @brief Default constructor
hMapDrawer::hMapDrawer()
{
	app = nullptr;
}

/// @brief Parameterized constructor
/// @param app Pointer to the application
hMapDrawer::hMapDrawer(cApp* app)
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
std::vector<GraphicCell> hMapDrawer::GetLaneBackgrounds(const cMapLane& Lane) const
{
	const int nRow = Lane.GetLaneID();
	const int nStartPos = Lane.GetStartPos(app->fTimeSinceStart);
	const int nCellOffset = Lane.GetCellOffset(app->nCellSize, app->fTimeSinceStart);

	std::vector<GraphicCell> Backgrounds;
	for (int nCol = -1; nCol < app->nLaneWidth; nCol++) {
		const char graphic = Lane.GetLaneGraphic(nStartPos + nCol);
		Backgrounds.push_back(GraphicCell(graphic, nCellOffset, nRow, nCol));
	}

	return Backgrounds;
}

/// @brief Get lane objects on screen
/// @param Lane Lane to be drawn
/// @return Vector of graphic cells representing the lane objects
std::vector<GraphicCell> hMapDrawer::GetLaneObjects(const cMapLane& Lane) const
{
	const int nRow = Lane.GetLaneID();
	const int nStartPos = Lane.GetStartPos(app->fTimeSinceStart);
	const int nCellOffset = Lane.GetCellOffset(app->nCellSize, app->fTimeSinceStart);

	std::vector<GraphicCell> Objects;
	for (int nCol = -1; nCol < app->nLaneWidth; nCol++) {
		const char graphic = Lane.GetLaneGraphic(nStartPos + nCol);
		Objects.push_back(GraphicCell(graphic, nCellOffset, nRow, nCol));
	}

	for (int id = 0; id < Objects.size(); ++id) {
		const GraphicCell& Cell = Objects[id];
		const int nID = static_cast<int>(Cell.nRow * 1e6 + Cell.nCol * 1e3 + nStartPos);
		if (SuccessSummon(Cell.graphic, nID)) {
			const MapObject& sprite = app->MapLoader.GetSpriteData(Cell.graphic);
			Objects.push_back(GraphicCell(sprite.summon, nCellOffset, nRow, Cell.nCol));
		}
	}

	return Objects;
}
/// @brief Draw lane on screen
/// @param lane Lane to be drawn
/// @return True if successful, false otherwise
bool hMapDrawer::DrawLane(const cMapLane& Lane) const
{
	std::vector<GraphicCell> Backgrounds = GetLaneBackgrounds(Lane);
	std::vector<GraphicCell> Objects = GetLaneObjects(Lane);

	for (const GraphicCell& BackgroundCell : Backgrounds) {
		DrawBackground(BackgroundCell);
	}

	for (const GraphicCell& ObjectCell : Objects) {
		DrawObject(ObjectCell);
	}

	return true;
}

/// @brief Draw all lanes on screen
/// @return Always true by default
bool hMapDrawer::DrawAllLanes() const
{
	const std::vector<cMapLane> vecLanes = app->MapLoader.GetLanes();
	for (const cMapLane& lane : vecLanes) {
		DrawLane(lane);
	}

	return true;
}
/// @brief Draw object on screen
/// @param Cell Cell to be drawn
/// @return Always true by default
bool hMapDrawer::DrawObject(const GraphicCell& Cell) const
{
	const MapObject sprite = app->MapLoader.GetSpriteData(Cell.graphic);
	const int32_t nPosX = Cell.nCol * app->nCellSize - Cell.nCellOffset;
	const int32_t nPosY = Cell.nRow * app->nCellSize;
	const int32_t nDrawX = sprite.nSpritePosX * app_const::SPRITE_WIDTH;
	const int32_t nDrawY = sprite.nSpritePosY * app_const::SPRITE_HEIGHT;
	const std::string sName = sprite.sSpriteName + (sprite.nID <= 0 ? "" : app->Player.ShowFrameID(sprite.nID));
	if (sName.size()) {
		const app::Sprite* object = cAssetManager::GetInstance().GetSprite(sName);
		app->SetPixelMode(app::Pixel::MASK);
		app->DrawPartialSprite(nPosX, nPosY, object, nDrawX, nDrawY);
		app->SetPixelMode(app::Pixel::NORMAL);

		app->Zone.FillDanger(Cell.graphic, nPosX, nPosY);
		app->Zone.FillBlocked(Cell.graphic, nPosX, nPosY);
	}
	return true;
}

/// @brief Draw background on screen
/// @param Cell Graphic cell to be drawn
/// @return Always true by default
bool hMapDrawer::DrawBackground(const GraphicCell& Cell) const
{
	const MapObject sprite = app->MapLoader.GetSpriteData(Cell.graphic);
	const int32_t nPosX = Cell.nCol * app->nCellSize - Cell.nCellOffset;
	const int32_t nPosY = Cell.nRow * app->nCellSize;
	const int32_t nDrawX = sprite.nBackgroundPosX * app_const::SPRITE_WIDTH;
	const int32_t nDrawY = sprite.nBackgroundPosY * app_const::SPRITE_HEIGHT;
	const std::string sName = sprite.sBackgroundName;
	if (sName.size()) {
		const app::Sprite* background = cAssetManager::GetInstance().GetSprite(sName);
		app->SetPixelMode(app::Pixel::NORMAL);
		app->DrawPartialSprite(nPosX + Cell.nCellOffset, nPosY, background, nDrawX, nDrawY);
		app->SetPixelMode(app::Pixel::NORMAL);

		app->Zone.FillDanger(Cell.graphic, nPosX, nPosY);
		app->Zone.FillBlocked(Cell.graphic, nPosX, nPosY);
	}
	return true;
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
	if (sprite.summon == 0 || sprite.fChance <= 0) {
		return false; // Summon is not enabled or chance is zero or negative
	}

	float fCurrentTime = app->fTimeSinceStart;
	int fps = app->GetAppFPS();
	if (mapLastSummon.count(nID) == false) {
		std::uniform_real_distribution<float> initialDistribution(0, sprite.fDuration);
		mapLastSummon[nID] = initialDistribution(generator);
	}
	float& fLastSummon = mapLastSummon[nID];
	const float fDeltaTime = fCurrentTime - fLastSummon;

	if (fDeltaTime >= 0) {
		if (fDeltaTime <= sprite.fDuration) {
			return true;
		}
		else if (fDeltaTime < sprite.fDuration + sprite.fCooldown) {
			return false;
		}
	}

	if (app->IsEnginePause()) {
		return false;
	}

	const auto fProbability = static_cast<float>(sprite.fChance / 100.0 / (fps == 0 ? 1 : fps));
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