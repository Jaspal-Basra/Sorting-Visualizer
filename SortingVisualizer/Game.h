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

#define NUMBER_OF_BARS  200

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

enum selectionSortState
{
	SELECTION_CHECK_CONDITION_OUTER,
	SELECTION_CHECK_CONDITION_INNER,
    SELECTION_CHECK_CONDITION_MIN,
	SELECTION_INCREMENT_INNER_INDEX,
	SELECTION_CHECK_CONDITION_SWAP,
	SELECTION_SWAP,
	SELECTION_INCREMENT_OUTER_INDEX,
	SELECTION_SORT_FINISHED,
};

enum insertionSortState
{
	INSERTION_CHECK_CONDITION_OUTER,
	INSERTION_CHECK_CONDITION_INNER,
	INSERTION_SORT_FINISHED,
};

/*
    Class that acts as the game engine.
    Wrapper class.
*/

class Game
{
public:
    // Constructors / Destructors
    Game();
    virtual ~Game();

    // Public Methods
    void update();
    void render();

    // Accessors
    const bool isWindowOpen() const;
    const sf::Vector2u getWindowSize() const;

    // Variables

private:
    // Variables
    // Window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event event;

    sf::Vector2u windowBounds;

    // Sorting state machine variables
    bubbleSortState bubbleState;
    selectionSortState selectionState;
    insertionSortState insertionState;

    // Sorting swap variables
    sf::Vector2f aPos;
    sf::Vector2f bPos;
    sf::RectangleShape temp;

    // Bubble sort variables
    uint8_t bubbleSortOuterIndex;
    uint8_t bubbleSortInnerIndex;
    bool hasSwapOccurred; // Optimizes bubble sort by exiting early 

    // Selection sort variables
    uint8_t selectionSortOuterIndex;
    uint8_t selectionSortInnerIndex;
    uint8_t innerIndexMin;

    // Insertion sort variables
    uint8_t insertionSortOuterIndex;
    uint8_t insertionSortInnerIndex;

    // Merge sort vairbales
    bool renderM;
    bool last;

    // Quick sort variabled

    char c;

    std::vector<float> barPositions;
    std::vector<sf::RectangleShape> barsBuf;

	std::vector<float> barHeights;
	std::vector<float> barHeights2;

	int barIndex, index1, cnt2;

    sf::RectangleShape bar;
    std::vector<sf::RectangleShape> bars;

    unsigned int numberOfBars;
    float barSize;
    unsigned int barCount;

    bool sortFinished;

    // Private methods
    void initBars();
    void initializeVariables();
    void initWindow();
    int partition(std::vector<sf::RectangleShape>& A, int start, int end);
    void merge(std::vector<sf::RectangleShape>& A, std::vector<sf::RectangleShape>& left, std::vector<sf::RectangleShape>& right, int startLeft, int endLeft, int startRight, int endRight);
    void swap(std::vector<sf::RectangleShape>& A, int a, int b);

    void pollEvents();
    
    void updateBars();
    
    void renderBars(sf::RenderTarget& target);

    void quickSort(std::vector<sf::RectangleShape>& A, int start, int end);
    void mergeSort(std::vector<sf::RectangleShape>& A, int start, int end);
    void insertionSort(std::vector<sf::RectangleShape>& A, int n);
    void bubbleSort(std::vector<sf::RectangleShape>& A, int n);
    void selectionSort(std::vector<sf::RectangleShape>& A, int n);

    void renderMergeSort(sf::RenderTarget& target, std::vector<sf::RectangleShape>& A, int startLeft, int endRight);
    void renderColor(sf::RenderTarget& target);
};
