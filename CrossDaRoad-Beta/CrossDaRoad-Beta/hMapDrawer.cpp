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
GraphicCell::GraphicCell(char graphic, int nCellOffset, int nRow, int nCol)
{
	this->graphic = graphic;
	this->nCellOffset = nCellOffset;
	this->nRow = nRow;
	this->nCol = nCol;
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
		if (SuccessSummon(Cell.graphic, id)) {
			const MapObject& sprite = app->MapLoader.GetSpriteData(Cell.graphic);
			Objects.push_back(GraphicCell(sprite.GetSummonTarget(), nCellOffset, nRow, Cell.nCol));
		}
	}

	return Objects;
}

bool hMapDrawer::DrawUnderlay(const cMapLane& Lane) const
{
	if (Lane.HasUnderlay()) {
		const int32_t nPosX = 0;
		const int32_t nPosY = Lane.GetLaneID() * app->nCellSize;
		const int nFrameCount = Lane.GetUnderlayFrameCount();
		const std::string sUnderlay = Lane.GetUnderlay() + (nFrameCount <= 0 ? "" : app->ShowFrameID(nFrameCount, 0.001));
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
	std::vector<GraphicCell> Backgrounds = GetLaneBackgrounds(Lane);
	for (const GraphicCell& BackgroundCell : Backgrounds) {
		DrawBackground(BackgroundCell);
	}

	std::vector<GraphicCell> Objects = GetLaneObjects(Lane);
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
		DrawUnderlay(lane);
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
	const int32_t nDrawX = sprite.GetSpritePosX() * app_const::SPRITE_WIDTH;
	const int32_t nDrawY = sprite.GetSpritePosY() * app_const::SPRITE_HEIGHT;
	int nFrameCount = sprite.GetSpriteFrameCount();
	const std::string sName = sprite.GetSpriteName() + (nFrameCount <= 0 ? "" : app->ShowFrameID(nFrameCount));
	if (sName.size()) {
		const app::Sprite* object = cAssetManager::GetInstance().GetSprite(sName);
		app->SetPixelMode(app::Pixel::MASK);
		app->DrawPartialSprite(nPosX, nPosY, object, nDrawX, nDrawY);
		app->SetPixelMode(app::Pixel::NORMAL);

		app->Zone.Fill(Cell.graphic, nPosX, nPosY);
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
	const int32_t nDrawX = sprite.GetBackgroundPosX() * app_const::SPRITE_WIDTH;
	const int32_t nDrawY = sprite.GetBackgroundPosY() * app_const::SPRITE_HEIGHT;
	const std::string sName = sprite.GetBackgroundName();
	if (sName.size()) {
		const app::Sprite* background = cAssetManager::GetInstance().GetSprite(sName);
		app->SetPixelMode(app::Pixel::NORMAL);
		app->DrawPartialSprite(nPosX + Cell.nCellOffset, nPosY, background, nDrawX, nDrawY);
		app->SetPixelMode(app::Pixel::NORMAL);

		app->Zone.Fill(Cell.graphic, nPosX, nPosY);
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
	if (sprite.GetSummonTarget() == 0 || sprite.GetSummonProbability() <= 0) {
		return false; // Summon is not enabled or chance is zero or negative
	}

	float fCurrentTime = app->fTimeSinceStart;
	int fps = app->GetAppFPS();
	if (mapLastSummon.count(nID) == false) {
		std::uniform_real_distribution<float> initialDistribution(0, sprite.GetSummonDuration());
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

	const auto fProbability = static_cast<float>(sprite.GetSummonProbability() / 100.0 / (fps == 0 ? 1 : fps));
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