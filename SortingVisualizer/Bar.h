#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <vector>
#include <iostream>

#include "Sorting.h"

#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   600

#define NUMBER_OF_BARS  100

class Bar
{
private:
    // Variables

    // Game objects
    sf::RectangleShape bar;
    std::vector<sf::RectangleShape> bars;

    unsigned int numberOfBars;
    float barSize;
    unsigned int barCount;

    // Private methods
    void initializeVariables();
    void initBars();

    Sorting sorting;

public:
    // Constructors / Destructors
    Bar();
    virtual ~Bar();

    // Public Methods

    void update();
    void updateBars();

    void render(sf::RenderTarget& target);
    void renderBars(sf::RenderTarget& target);
};

