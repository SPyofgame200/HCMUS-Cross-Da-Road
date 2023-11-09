#include "cApp.h"

int main()
{
	cApp app;
	if (app.Construct(app_const::SCREEN_WIDTH, app_const::SCREEN_HEIGHT, app_const::PIXEL_WIDTH, app_const::PIXEL_HEIGHT) == engine::SUCCESS) {
		app.Start();
	}
	return 0;
}