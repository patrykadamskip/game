// START OF INCLUDES
#include <iostream>
#include "game.hpp"
#include <crtdbg.h>

// END OF INCLUDES

int main(int argc, char *argv[])
{

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    Game GameInstance;
    GameInstance.Init();

    // GAME LOOP START

    while (GameInstance.GetState())
    {
        GameInstance.EventHandler(&GameInstance.GetEvent());
        GameInstance.Update();
        GameInstance.Render();
    }

    // GAME LOOP END

    return 0;
}