#include <iostream>
#include "App.h"

int main()
{
    // Init srand
    std::srand(static_cast<unsigned>(time(NULL)));

    // Init game
    App app;

    // Main loop
    while (app.isWindowOpen())
    {
        // Update
        app.update();

        // Render
        app.render();
    }

    // End of application
    return 0;
}