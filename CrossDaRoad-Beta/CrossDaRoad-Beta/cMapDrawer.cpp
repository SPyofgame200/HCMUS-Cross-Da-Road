#include "cMapDrawer.h"
#include "cApp.h"

cMapDrawer::cMapDrawer()
{
	app = nullptr;
}

cMapDrawer::cMapDrawer(cApp* app)
{
	SetTarget(app);
}

cMapDrawer::~cMapDrawer()
{
	app = nullptr;
	std::cerr << "cMapDrawer::~cMapDrawer(): Successfully destructed" << std::endl;
}

bool cMapDrawer::SetTarget(cApp* app)
{
	if (app == nullptr) {
		return false;
	}
	this->app = app;
	return true;
}

int cMapDrawer::GetStartPos(const cMapLane& lane) const
{
	int nStartPos = static_cast<int>(app->fTimeSinceStart * lane.GetVelocity()) % app_const::MAP_WIDTH_LIMIT;
	if (nStartPos < 0) nStartPos %= app_const::MAP_WIDTH_LIMIT;
	if (nStartPos < 0) nStartPos += app_const::MAP_WIDTH_LIMIT;
	return nStartPos;
}


int cMapDrawer::GetCellOffset(const cMapLane& lane) const
{
	float fCellOffset = static_cast<float>(app->nCellSize) * app->fTimeSinceStart * lane.GetVelocity();
	int nCellOffset = static_cast<int>(fCellOffset);
	nCellOffset %= app->nCellSize;
	return nCellOffset;
}

bool cMapDrawer::DrawLane(const cMapLane& lane)
{
	int nRow = lane.GetLaneID();
	int nStartPos = GetStartPos(lane);
	int nCellOffset = GetCellOffset(lane);
	app->fTimeSinceLastDrawn = app->fTimeSinceStart;
	for (int nCol = -1; nCol < app->nLaneWidth; nCol++) {
		const char cGraphic = lane.GetLaneGraphic(nStartPos + nCol);
		DrawCharacter(cGraphic, true, lane, nRow, nCol);
	}

	for (int nCol = -1; nCol < app->nLaneWidth; nCol++) {
		const char cGraphic = lane.GetLaneGraphic(nStartPos + nCol);
		DrawCharacter(cGraphic, false, lane, nRow, nCol);
	}

	for (int nCol = 0; nCol < app->nLaneWidth; nCol++) {
		const char cGraphic = lane.GetLaneGraphic(nStartPos + nCol);
		const int nTopLeftX = nCol * app->nCellSize - nCellOffset;
		const int nTopLeftY = nRow * app->nCellSize;
		const int nBottomRightX = (nCol + 1) * app->nCellSize - nCellOffset;
		const int nBottomRightY = (nRow + 1) * app->nCellSize;

		app->Zone.FillDanger(nTopLeftX, nTopLeftY, nBottomRightX, nBottomRightY, cGraphic, app->MapLoader.GetDangerPattern().c_str());
		app->Zone.FillBlocked(nTopLeftX, nTopLeftY, nBottomRightX, nBottomRightY, cGraphic, app->MapLoader.GetBlockPattern().c_str());
	}

	return true;
}

bool cMapDrawer::DrawAllLanes()
{
	int nRow = 0;
	const std::vector<cMapLane> vecLanes = app->MapLoader.GetLanes();
	for (const cMapLane& lane : vecLanes) {
		DrawLane(lane);
	}

	return true;
}

bool cMapDrawer::DrawCharacter(char graphic, bool drawBackground, const cMapLane& lane, int nRow, int nCol)
{
	int nCellOffset = GetCellOffset(lane);
	MapObject sprite = app->MapLoader.GetSpriteData(graphic);
	const int32_t nPosX = nCol * app->nCellSize - nCellOffset;
	const int32_t nPosY = nRow * app->nCellSize;
	constexpr int32_t nWidth = app_const::SPRITE_WIDTH;
	constexpr int32_t nHeight = app_const::SPRITE_HEIGHT;

	if (drawBackground) {
		const int32_t nDrawX = sprite.nBackgroundPosX * app_const::SPRITE_WIDTH;
		const int32_t nDrawY = sprite.nBackgroundPosY * app_const::SPRITE_HEIGHT;
		const std::string sName = sprite.sBackgroundName;
		if (sName.size()) {
			const app::Sprite* background = cAssetManager::GetInstance().GetSprite(sName);
			app->SetPixelMode(app::Pixel::NORMAL);
			app->DrawPartialSprite(nPosX + nCellOffset, nPosY, background, nDrawX, nDrawY, nWidth, nHeight);
			app->SetPixelMode(app::Pixel::NORMAL);
		}
	}
	else {
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
	}
	return true;
}
