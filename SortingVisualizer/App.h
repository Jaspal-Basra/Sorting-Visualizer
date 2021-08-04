#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <vector>

#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   600

// Non-recursive sorting algorithms are implemented using state machines to
// prevent blocking the App's main loop

/**
* States for bubble sort state machine
*/
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

/**
* States for selection sort state machine
*/
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

/**
* States for insertion sort state machine
*/
enum insertionSortState
{
	INSERTION_CHECK_CONDITION_OUTER,
	INSERTION_CHECK_CONDITION_INNER,
	INSERTION_SORT_FINISHED,
};

/*
    Class that acts as the app engine.
    Wrapper class.
*/
class App
{
public:
    // Constructors / Destructors
    App();
    virtual ~App();

    // Public Methods
    void update();
    void render();

    // Accessors
    const bool isWindowOpen() const;
    const sf::Vector2u getWindowSize() const;

private:

    // Private variables

    // Window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event event;
    sf::Vector2u windowBounds;

    // Sorting select variable
    char sortingSelect;

    // Bar object
    sf::RectangleShape bar;

    // Bar vector
    std::vector<sf::RectangleShape> bars;

    // Bar properties
    unsigned int numberOfBars;
    float barSize;

    sf::Color initialColor;
    sf::Color comparisonColor;
    sf::Color scanColor;
    sf::Color partitionIndexColor;
    sf::Color mergeColor;
    sf::Color finalColor;

    // Bar height vector
	std::vector<float> barHeights;

    // Flag to indicate sorting has finished
    bool sortFinished;

private:

    // Private methods
    void initBars();
    void initializeVariables();
    void initWindow();

    void pollEvents();
    
    void updateBars();
    
    void renderBars(sf::RenderTarget& target);

    // Sorting functions
    void quickSort(std::vector<sf::RectangleShape>& A, int start, int end);
    void mergeSort(std::vector<sf::RectangleShape>& A, int start, int end);
    void insertionSort(std::vector<sf::RectangleShape>& A, int n);
    void bubbleSort(std::vector<sf::RectangleShape>& A, int n);
    void selectionSort(std::vector<sf::RectangleShape>& A, int n);

    // Sorting helper functions
    int partition(std::vector<sf::RectangleShape>& A, int start, int end);
    void merge(std::vector<sf::RectangleShape>& A, std::vector<sf::RectangleShape>& left, std::vector<sf::RectangleShape>& right, int startLeft, int endLeft, int startRight, int endRight);
    void swap(std::vector<sf::RectangleShape>& A, int a, int b);

    // Rendering functions (for recursive sorting algorithms that block the main loop)
    void renderMergeSort(sf::RenderTarget& target, std::vector<sf::RectangleShape>& A, int startLeft, int endRight);
};
