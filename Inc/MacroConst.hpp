#ifndef __MACROCONST_HPP__
#define __MACROCONST_HPP__

namespace Constants
{

    // General constants
    namespace General
    {
        // Main window resolution
        constexpr int MainWinWidth = 1280;
        constexpr int MainWinHeight = 720;

        // Name of the game
        constexpr const char *GAMENAME = "gra";

        // Frame rate of the game FPS = 1s / FRAME_RATE (in ms)
        constexpr int FRAME_RATE = 16; // 16ms for 60fps

        constexpr const char *TEST_FONT_PATH = "Assets/Fonts/ByteBounce.ttf";

    }

    // Player constants
    namespace PlayerMacro
    {
        namespace Paths
        {
            constexpr const char *TEST_PLAYER_SPRITE_PATH = "Assets/Img/PlayerSprites/test_player_sprite.png";
        }

        namespace SpriteSheetMacro
        {
            constexpr int TEST_PLAYER_SPRITE_WIDTH = 150;
            constexpr int TEST_PLAYER_SPRITE_HEIGHT = 200;
            constexpr int TEST_PLAYER_START_FRAME = 0;
            constexpr int TEST_PLAYER_WALKING_ANIMATION = 0;
            constexpr int TEST_PLAYER_TOTAL_FRAMES = 2;
            constexpr int TEST_PLAYER_SHEET_WIDTH = 2;
            constexpr int TEST_PLAYER_SHEET_HEIGHT = 1;
        }
    }

    // Menu constants
    namespace MenuMacro
    {
        namespace Paths
        {
            constexpr const char *START_BUTTON_IDLE_PATH = "Assets/Img/start_button_idle.bmp";
            constexpr const char *START_BUTTON_ACTIVE_PATH = "Assets/Img/start_button_active.bmp";
            constexpr const char *PROGRESS_BUTTON_IDLE_PATH = "Assets/Img/progress_button_idle.bmp";
            constexpr const char *PROGRESS_BUTTON_ACTIVE_PATH = "Assets/Img/progress_button_active.bmp";
            constexpr const char *OPTIONS_BUTTON_IDLE_PATH = "Assets/Img/options_button_idle.bmp";
            constexpr const char *OPTIONS_BUTTON_ACTIVE_PATH = "Assets/Img/options_button_active.bmp";
            constexpr const char *EXIT_BUTTON_IDLE_PATH = "Assets/Img/exit_button_idle.bmp";
            constexpr const char *EXIT_BUTTON_ACTIVE_PATH = "Assets/Img/exit_button_active.bmp";
        }

        namespace UI
        {
            constexpr int BUTTON_X_POSITION = 835;
            constexpr int BUTTON_WIDTH = 260;
            constexpr int BUTTON_HEIGHT = 70;

            constexpr int START_BUTTON_Y_POSITION = 100;
            constexpr int PROGRESS_BUTTON_Y_POSITION = 200;
            constexpr int OPTIONS_BUTTON_Y_POSITION = 300;
            constexpr int EXIT_BUTTON_Y_POSITION = 400;
        }
    }

    namespace ArenaMacro
    {
        namespace Paths
        {
            constexpr const char *TEST_BACKGROUND_PATH = "Assets/Img/Backgrounds/bcgtest.png";
        }

    }

    // Options constants
    namespace OptionsMenuMacro
    {
        namespace Paths
        {
            constexpr const char *TEST_BACKGROUND_PATH_OPTIONS = "Assets/Img/Backgrounds/settings_background.png";
            constexpr const char *RESOLUTION_BUTTON_IDLE_PATH = "Assets/Img/Buttons/resolution_button_idle.bmp";
        }

        namespace UI
        {
            constexpr int BUTTON_WIDTH = 250;
            constexpr int BUTTON_HEIGHT = 60;
        }
    }
    namespace ConfigMacro
    {
        namespace Paths
        {
            constexpr const char *CONFIG_FILE_PATH = "config.txt";
        }
    }

}

#endif // __MACROCONST_HPP__
