#include "hMapDrawer.h"
#include "cApp.h"
#include <vector>

hMapDrawer::hMapDrawer()
{
	app = nullptr;
}

hMapDrawer::hMapDrawer(cApp* app)
{
	SetupTarget(app);
}

hMapDrawer::~hMapDrawer()
{
	app = nullptr;
	//std::cerr << "hMapDrawer::~hMapDrawer(): Successfully destructed" << std::endl;
}

bool hMapDrawer::SetupTarget(cApp* app)
{
	if (app == nullptr) {
		return false;
	}
	this->app = app;
	return true;
}

bool hMapDrawer::DrawLane(const cMapLane& lane) const
{
	const int nRow = lane.GetLaneID();
	const int nStartPos = lane.GetStartPos(app->fTimeSinceStart);
	const int nCellOffset = lane.GetCellOffset(app->nCellSize, app->fTimeSinceStart);

	std::vector<GraphicCell> Backgrounds;
	for (int nCol = -1; nCol < app->nLaneWidth; nCol++) {
		const char graphic = lane.GetLaneGraphic(nStartPos + nCol);
		Backgrounds.push_back(GraphicCell(graphic, nCellOffset, nRow, nCol));
	}

	std::vector<GraphicCell> Objects;
	for (int nCol = -1; nCol < app->nLaneWidth; nCol++) {
		const char graphic = lane.GetLaneGraphic(nStartPos + nCol);
		Objects.push_back(GraphicCell(graphic, nCellOffset, nRow, nCol));
	}

	for (int id = 0; id < Objects.size(); ++id)
	{
		const GraphicCell& Cell = Objects[id];
		const int nID = static_cast<int>(nRow * 1e4 + id);
		if (SuccessSummon(Cell.graphic, nID)) {
			const MapObject& sprite = app->MapLoader.GetSpriteData(Cell.graphic);
			Objects.push_back(GraphicCell(sprite.summon, nCellOffset, nRow, Cell.nCol));
		}
	}

	for (const GraphicCell& BackgroundCell : Backgrounds) {
		DrawBackground(BackgroundCell);
	}
	for (const GraphicCell& ObjectCell : Objects) {
		DrawObject(ObjectCell);
	}
	return true;
}

bool hMapDrawer::DrawAllLanes() const
{
	const std::vector<cMapLane> vecLanes = app->MapLoader.GetLanes();
	for (const cMapLane& lane : vecLanes) {
		DrawLane(lane);
	}

	return true;
}

bool hMapDrawer::DrawObject(const GraphicCell &Cell) const
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

#include <random>
#include <iomanip>
std::default_random_engine generator(std::random_device{}());
std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
std::map<int, float> mapLastSummon;
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
		//std::cerr << "map[" << nID << "] = " << sprite.fDuration + sprite.fCooldown << std::endl;
	}
	float& fLastSummon = mapLastSummon[nID];
	const float fDeltaTime = fCurrentTime - fLastSummon;

	//std::cerr << nCol << " " << nRow << " id=" << id << ": ";
	//std::cerr << "delta=" << fDeltaTime << " current=" << fCurrentTime << " " << "last=" << fLastSummon << " -> ";
	if (fDeltaTime >= 0) {
		if (fDeltaTime <= sprite.fDuration) {
			//std::cerr << "Continue" << std::endl;
			return true;
		}
		else if (fDeltaTime < sprite.fDuration + sprite.fCooldown) {
			//std::cerr << "Stoped" << std::endl;
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
		//std::cerr << "Recreated" << std::endl;
		return true;
	}
	//std::cerr << "Failed" << std::endl;
	return false; // Summon is not successful
}