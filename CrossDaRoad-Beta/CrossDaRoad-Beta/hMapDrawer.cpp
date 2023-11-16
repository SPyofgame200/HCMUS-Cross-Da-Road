#include "hMapDrawer.h"
#include "cApp.h"

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

int hMapDrawer::GetStartPos(const cMapLane& lane) const
{
	return lane.GetStartPos(app->fTimeSinceStart);
}


int hMapDrawer::GetCellOffset(const cMapLane& lane) const
{
	return lane.GetCellOffset(app->nCellSize, app->fTimeSinceStart);
}

bool hMapDrawer::DrawLane(const cMapLane& lane) const
{
	const int nRow = lane.GetLaneID();
	const int nStartPos = GetStartPos(lane);
	const int nCellOffset = GetCellOffset(lane);
	app->fTimeSinceLastDrawn = app->fTimeSinceStart;

	for (int nCol = -1; nCol < app->nLaneWidth; nCol++) {
		const char graphic = lane.GetLaneGraphic(nStartPos + nCol);
		DrawBackground(graphic, nCellOffset, nRow, nCol);
	}

	app->Zone.SetPattern(app->MapLoader.GetDangerPattern().c_str(), app->MapLoader.GetBlockPattern().c_str());
	for (int nCol = -1; nCol < app->nLaneWidth; nCol++) {
		const char graphic = lane.GetLaneGraphic(nStartPos + nCol);
		DrawObject(graphic, nCellOffset, nRow, nCol);
	}

	return true;
}

bool hMapDrawer::DrawAllLanes() const
{
	int nRow = 0;
	const std::vector<cMapLane> vecLanes = app->MapLoader.GetLanes();
	for (const cMapLane& lane : vecLanes) {
		DrawLane(lane);
	}

	return true;
}

bool hMapDrawer::DrawObject(char graphic, int nCellOffset, int nRow, int nCol) const
{
	const MapObject sprite = app->MapLoader.GetSpriteData(graphic);
	const int32_t nPosX = nCol * app->nCellSize - nCellOffset;
	const int32_t nPosY = nRow * app->nCellSize;
	app->Zone.FillDanger(graphic, nPosX, nPosY);
	app->Zone.FillBlocked(graphic, nPosX, nPosY);
	const int32_t nDrawX = sprite.nSpritePosX * app_const::SPRITE_WIDTH;
	const int32_t nDrawY = sprite.nSpritePosY * app_const::SPRITE_HEIGHT;
	const std::string sName = sprite.sSpriteName + (sprite.nID <= 0 ? "" : app->Player.ShowFrameID(sprite.nID));
	if (sName.size()) {
		const app::Sprite* object = cAssetManager::GetInstance().GetSprite(sName);
		app->SetPixelMode(app::Pixel::MASK);
		app->DrawPartialSprite(nPosX, nPosY, object, nDrawX, nDrawY);
		app->SetPixelMode(app::Pixel::NORMAL);
	}

	if (SuccessSummon(sprite, nCol, nRow, app->fTimeSinceLastDrawn, app->GetAppFPS(), !app->IsEnginePause())) {
		const MapObject summon = app->MapLoader.GetSpriteData(sprite.summon);
		const std::string sSummonName = summon.sSpriteName + app->Player.ShowFrameID(summon.nID);
		const app::Sprite* summoned_object = cAssetManager::GetInstance().GetSprite(sSummonName);
		app->SetPixelMode(app::Pixel::MASK);
		app->DrawPartialSprite(nPosX, nPosY, summoned_object, nDrawX, nDrawY);
		app->Zone.FillDanger(sprite.summon, nPosX, nPosY);
		app->Zone.FillBlocked(sprite.summon, nPosX, nPosY);
		app->SetPixelMode(app::Pixel::NORMAL);
	}
	return true;
}

bool hMapDrawer::DrawBackground(char graphic, int nCellOffset, int nRow, int nCol) const
{
	const MapObject sprite = app->MapLoader.GetSpriteData(graphic);
	const int32_t nPosX = nCol * app->nCellSize - nCellOffset;
	const int32_t nPosY = nRow * app->nCellSize;
	const int32_t nDrawX = sprite.nBackgroundPosX * app_const::SPRITE_WIDTH;
	const int32_t nDrawY = sprite.nBackgroundPosY * app_const::SPRITE_HEIGHT;
	const std::string sName = sprite.sBackgroundName;
	if (sName.size()) {
		const app::Sprite* background = cAssetManager::GetInstance().GetSprite(sName);
		app->SetPixelMode(app::Pixel::NORMAL);
		app->DrawPartialSprite(nPosX + nCellOffset, nPosY, background, nDrawX, nDrawY);
		app->SetPixelMode(app::Pixel::NORMAL);
	}
	return true;
}

#include <random>
#include <iomanip>
std::default_random_engine generator(std::random_device{}());
std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
std::map<int, float> mapLastSummon;
bool hMapDrawer::SuccessSummon(const MapObject& sprite, int nCol, int nRow, float fCurrentTime, int fps, bool bCreateAllow) const
{
	if (sprite.summon == 0 || sprite.fChance <= 0) {
		return false; // Summon is not enabled or chance is zero or negative
	}

	const int id = static_cast<int>(nCol * 1e4 + nRow);
	if (mapLastSummon.count(id) == false) {
		std::uniform_real_distribution<float> initialDistribution(0, sprite.fDuration);
		mapLastSummon[id] = initialDistribution(generator);
		//std::cerr << "map[" << id << "] = " << sprite.fDuration + sprite.fCooldown << std::endl;
	}
	float& fLastSummon = mapLastSummon[id];
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

	if (!bCreateAllow) {
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