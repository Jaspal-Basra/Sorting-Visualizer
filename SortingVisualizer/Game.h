#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <vector>
#include <iostream>
#include <ctime>
#include <sstream>

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

    // Game objects
    sf::RectangleShape bar;
    std::vector<sf::RectangleShape> bars;

    unsigned int numberOfBars;
    float barSize;
    unsigned int barCount;

    // Private methods
    void initializeVariables();
    void initWindow();
    void initBars();

    void insertionSort(std::vector<sf::RectangleShape>& A, int n);

    void bubbleSort(std::vector<sf::RectangleShape>& A, int n);
    void swap(std::vector<sf::RectangleShape>& A, int a, int b);

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

    void spawnBar();

    // Accessors
    const bool isWindowOpen() const;
};
