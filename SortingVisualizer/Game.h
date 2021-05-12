#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <vector>
#include <chrono>

//#include "Bar.h"

#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   600

#define NUMBER_OF_BARS  100

#define ANIMATION_TIME  20

enum bubbleSortState
{
	BUBBLE_CHECK_CONDITION_OUTER,
	BUBBLE_CHECK_CONDITION_INNER,
	BUBBLE_CHECK_CONDITION_SWAP,
	BUBBLE_SWAP,
	BUBBLE_INCREMENT_INNER_INDEX,
	BUBBLE_INCREMENT_OUTER_INDEX,
	BUBBLE_SORT_FINISHED,
};

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

    // Sorting
    uint8_t bubbleSortOuterIndex;
    uint8_t bubbleSortInnerIndex;

	// Sorting swap
    sf::Vector2f aPos;
    sf::Vector2f bPos;
    sf::RectangleShape temp;
    bool moveFinished;
    bool hasSwapOccurred;

    bubbleSortState bubbleState;

    std::chrono::steady_clock::time_point currTime, startTime;
    std::chrono::microseconds waitTime;

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

    // Variables

// Game objects
    sf::RectangleShape bar;
    std::vector<sf::RectangleShape> bars;

    unsigned int numberOfBars;
    float barSize;
    unsigned int barCount;

    // Private methods
    void initBars();

public:
    // Public Methods

private:
    // Variables

    // Private methods

    int partition(std::vector<sf::RectangleShape>& A, int start, int end);
    void merge(std::vector<sf::RectangleShape>& A, std::vector<sf::RectangleShape>& left, std::vector<sf::RectangleShape>& right, int n, int nLeft, int nRight);
    void swap(std::vector<sf::RectangleShape>& A, int a, int b);

public:

    // Public methods

    void quickSort(std::vector<sf::RectangleShape>& A, int start, int end);
    void mergeSort(std::vector<sf::RectangleShape>& A, int n);
    void insertionSort(std::vector<sf::RectangleShape>& A, int n);
    void bubbleSort(std::vector<sf::RectangleShape>& A, int n);
    void selectionSort(std::vector<sf::RectangleShape>& A, int n);
};
