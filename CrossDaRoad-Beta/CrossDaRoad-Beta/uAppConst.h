/**
 * @file uAppConst.h
 *
 * @brief Contains application constants
 *
 * This file contains application constants. It is used to store constants that are used in multiple files.
 **/

#ifndef U_APP_CONST_H
#define U_APP_CONST_H

 /// @brief Namespace for application constants
namespace app_const
{
    constexpr int INIT_MENU_OPTION = 0; ///< Initial app option (new_game)
    constexpr const char* APP_OPTIONS[] = { "new_game", "continue", "setting", "about_us", "exit" }; ///< App options (new_game, continue, setting, about_us, exit)

    constexpr int INIT_PAUSE_OPTION = 0; ///< Initial pause option (resume)
    constexpr const char* PAUSE_OPTIONS[] = { "resume", "save", "exit" }; ///< Pause options (resume, save, exit)

    constexpr const char* APP_NAME = "Cross Da Road";          ///< Application name (Cross Da Road)
    constexpr const char* GAME_NAME = "Playing Cross Da Road"; ///< Game name (Playing Cross Da Road)
    constexpr int GAME_LEVEL_INIT = 5;                         ///< Initial game level (1)

    constexpr int MAP_WIDTH_LIMIT = 64; ///< Map width limit (64) (in pixels)

    constexpr int SCREEN_WIDTH = 352;  ///< Screen width (352) (in pixels)
    constexpr int SCREEN_HEIGHT = 160; ///< Screen height (160) (in pixels)

    constexpr int CELL_SIZE = 16;  ///< Cell size (16) (in pixels)
    constexpr int LANE_WIDTH = 18; ///< Lane width (18) (in pixels)

    constexpr int PIXEL_WIDTH = 4;  ///< Pixel width (4) (in pixels)
    constexpr int PIXEL_HEIGHT = 4; ///< Pixel height (4) (in pixels)

    constexpr int FONT_WIDTH = 8;  ///< Font width (8) (in pixels)
    constexpr int FONT_HEIGHT = 8; ///< Font height (8) (in pixels)

    constexpr int SPRITE_WIDTH = 16;  ///< Sprite width (16) (in pixels)
    constexpr int SPRITE_HEIGHT = 16; ///< Sprite height (16) (in pixels)

    constexpr float FROG_X_VELOCITY = 1.0; ///< Frog x velocity (1.0)
    constexpr float FROG_Y_VELOCITY = 1.0; ///< Frog y velocity (1.0)
    constexpr float FROG_X_RESET = 8.0f;   ///< Frog x reset position (8.0f)
    constexpr float FROG_Y_RESET = 9.0f;   ///< Frog y reset position (9.0f)

    constexpr float TOP_BORDER = 0.0f;    ///< Top border (0.0f)
    constexpr float BOTTOM_BORDER = 9.0f; ///< Bottom border (9.0f)
    constexpr float LEFT_BORDER = 0.0f;   ///< Left border (0.0f)
    constexpr float RIGHT_BORDER = 16.0f; ///< Right border (16.0f)
}

#endif // U_APP_CONST_H
