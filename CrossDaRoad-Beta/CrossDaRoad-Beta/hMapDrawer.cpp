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
	std::cerr << "hMapDrawer::~hMapDrawer(): Successfully destructed" << std::endl;
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

bool hMapDrawer::DrawLane(const cMapLane& lane)
{
	int nRow = lane.GetLaneID();
	int nStartPos = GetStartPos(lane);
	int nCellOffset = GetCellOffset(lane);
	app->fTimeSinceLastDrawn = app->fTimeSinceStart;

	for (int nCol = -1; nCol < app->nLaneWidth; nCol++) {
		const char graphic = lane.GetLaneGraphic(nStartPos + nCol);
		DrawBackground(graphic, nCellOffset, nRow, nCol);
	}

	for (int nCol = -1; nCol < app->nLaneWidth; nCol++) {
		const char graphic = lane.GetLaneGraphic(nStartPos + nCol);
		DrawObject(graphic, nCellOffset, nRow, nCol);
	}

	for (int nCol = 0; nCol < app->nLaneWidth; nCol++) {
		const char graphic = lane.GetLaneGraphic(nStartPos + nCol);
		const int nTopLeftX = nCol * app->nCellSize - nCellOffset;
		const int nTopLeftY = nRow * app->nCellSize;
		const int nBottomRightX = (nCol + 1) * app->nCellSize - nCellOffset;
		const int nBottomRightY = (nRow + 1) * app->nCellSize;
		app->Zone.FillDanger(nTopLeftX, nTopLeftY, nBottomRightX, nBottomRightY, graphic, app->MapLoader.GetDangerPattern().c_str());
		app->Zone.FillBlocked(nTopLeftX, nTopLeftY, nBottomRightX, nBottomRightY, graphic, app->MapLoader.GetBlockPattern().c_str());
	}

	return true;
}

bool hMapDrawer::DrawAllLanes()
{
	int nRow = 0;
	const std::vector<cMapLane> vecLanes = app->MapLoader.GetLanes();
	for (const cMapLane& lane : vecLanes) {
		DrawLane(lane);
	}

	return true;
}

bool hMapDrawer::DrawObject(char graphic, int nCellOffset, int nRow, int nCol)
{
	MapObject sprite = app->MapLoader.GetSpriteData(graphic);
	const int32_t nPosX = nCol * app->nCellSize - nCellOffset;
	const int32_t nPosY = nRow * app->nCellSize;
	constexpr int32_t nWidth = app_const::SPRITE_WIDTH;
	constexpr int32_t nHeight = app_const::SPRITE_HEIGHT;
	const int32_t nDrawX = sprite.nSpritePosX * app_const::SPRITE_WIDTH;
	const int32_t nDrawY = sprite.nSpritePosY * app_const::SPRITE_HEIGHT;
	const std::string sName = sprite.sSpriteName + (sprite.nID <= 0 ? "" : app->Player.ShowFrameID(sprite.nID));
	if (sName.size()) {
		const app::Sprite* object = cAssetManager::GetInstance().GetSprite(sName);
		app->SetPixelMode(app::Pixel::MASK);
		app->DrawPartialSprite(nPosX, nPosY, object, nDrawX, nDrawY, nWidth, nHeight);
		app->SetPixelMode(app::Pixel::NORMAL);
	}

	if (sprite.SuccessSummon(nCol, nRow, app->fTimeSinceLastDrawn, app->GetAppFPS(), !app->IsEnginePause())) {
		const std::string sSummonName = sprite.summon->sSpriteName + (sprite.summon->nID <= 0 ? "" : app->Player.ShowFrameID(sprite.summon->nID));
		if (sSummonName.size()) {
			const app::Sprite* summoned_object = cAssetManager::GetInstance().GetSprite(sSummonName);
			app->SetPixelMode(app::Pixel::MASK);
			app->DrawPartialSprite(nPosX, nPosY, summoned_object, nDrawX, nDrawY, nWidth, nHeight);
			app->SetPixelMode(app::Pixel::NORMAL);
		}
	}
	return true;
}

bool hMapDrawer::DrawBackground(char graphic, int nCellOffset, int nRow, int nCol)
{
	MapObject sprite = app->MapLoader.GetSpriteData(graphic);
	const int32_t nPosX = nCol * app->nCellSize - nCellOffset;
	const int32_t nPosY = nRow * app->nCellSize;
	constexpr int32_t nWidth = app_const::SPRITE_WIDTH;
	constexpr int32_t nHeight = app_const::SPRITE_HEIGHT;
	const int32_t nDrawX = sprite.nBackgroundPosX * app_const::SPRITE_WIDTH;
	const int32_t nDrawY = sprite.nBackgroundPosY * app_const::SPRITE_HEIGHT;
	const std::string sName = sprite.sBackgroundName;
	if (sName.size()) {
		const app::Sprite* background = cAssetManager::GetInstance().GetSprite(sName);
		app->SetPixelMode(app::Pixel::NORMAL);
		app->DrawPartialSprite(nPosX + nCellOffset, nPosY, background, nDrawX, nDrawY, nWidth, nHeight);
		app->SetPixelMode(app::Pixel::NORMAL);
	}
	return true;
}
