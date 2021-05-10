#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <vector>

#include "Bar.h"

/*
    Class that acts as the game engine.
    Wrapper class.
*/

class Game
{
private:
    // Variables
    // Window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event event;

    sf::Vector2u windowBounds;

    // Private methods
    void initializeVariables();
    void initWindow();

    Bar bar;

public:
    // Constructors / Destructors
    Game();
    virtual ~Game();

    // Public Methods

    void pollEvents();

    void update();
    void updateBars();

    void render();
    void renderBars(sf::RenderTarget& target);

    // Accessors
    const bool isWindowOpen() const;
    const sf::Vector2u getWindowSize() const;
};
