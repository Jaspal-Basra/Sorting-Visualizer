#include <iostream>
#include "Game.h"

int main()
{
    // Init srand
    std::srand(static_cast<unsigned>(time(NULL)));

    // Init game
    Game game;

    // Game loop
    while (game.isWindowOpen())
    {
        // Update
        game.update();

        // Render
        game.render();
    }

    // End of application
    return 0;
}