#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Textbox.h"
#include "Button.h"

#include <iostream>
#include <vector>

#define FULLSCREEN_ON   1

#if !(FULLSCREEN_ON)
 #define WINDOW_WIDTH   800
 #define WINDOW_HEIGHT  600
#endif // !(FULLSCREEN_ON)

#define MAX_NUMBER_OF_BARS 2000

// ASCII Number Definitions

#define ASCII_NUMBER_0 48
#define ASCII_NUMBER_9 57

// Order of appearance of buttons from left to right on window

#define BUTTON_SELECTION_SORT_NUM 1
#define BUTTON_BUBBLE_SORT_NUM 2
#define BUTTON_INSERTION_SORT_NUM 3
#define BUTTON_MERGE_SORT_NUM 4
#define BUTTON_QUICK_SORT_NUM 5

// Button positions as fraction of screen (0.5 means middle of screen)

#define START_BUTTON_X_POS (0.5f)
#define START_BUTTON_Y_POS (0.833f)

#define RESTART_BUTTON_X_POS (0.5f)
#define RESTART_BUTTON_Y_POS (0.5f)

#define SORTING_BUTTON_X_POS (0.167f)
#define SORTING_BUTTON_Y_POS (0.25f)

// Framerate Limit Definitions

#define FRAMERATE_LIMIT_MAX 100
#define FRAMERATE_LIMIT_MIN 10
#define FRAMERATE_LIMIT_NORMAL 60
#define FRAMERATE_LIMIT_BAR_DIVISOR 2

/**
* States for bubble sort state machine
*/
enum bubbleSortState
{
    BUBBLE_INVALID = 0,
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
    SELECTION_INVALID = 0,
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
    INSERTION_INVALID = 0,
	INSERTION_CHECK_CONDITION_OUTER,
	INSERTION_CHECK_CONDITION_INNER,
	INSERTION_SORT_FINISHED,
};

/**
* States for the overall application's state machine
*/
enum appState
{
    APP_INVALID = 0,
    APP_MENU,
    APP_SORTING,
    APP_RESTART_ICON,
};

/**
* Sorting algorithms
*/
enum sortingAlgorithms
{
    SORTING_NONE = 0,
    SORTING_SELECTION_SORT,
    SORTING_BUBBLE_SORT,
    SORTING_INSERTION_SORT,
    SORTING_MERGE_SORT,
    SORTING_QUICK_SORT,
};

/*
    App class
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

    // Private methods

    // Init functions
    void initMenu();
    bool initFont();
    void initBars();
    void initWindow();
    void initText();
    void initButtons();

    void pollEvents();

    // Update functions
    void updateBars();

    // Render functions
    void renderBars(sf::RenderTarget& target);
    void renderMenu(sf::RenderTarget& target);
    void renderRestartButton(sf::RenderTarget& target);

    // Sorting functions
    void quickSort(std::vector<sf::RectangleShape>& A, int start, int end);
    void mergeSort(std::vector<sf::RectangleShape>& A, int start, int end);
    bool insertionSort(std::vector<sf::RectangleShape>& A, int n);
    bool bubbleSort(std::vector<sf::RectangleShape>& A, int n);
    bool selectionSort(std::vector<sf::RectangleShape>& A, int n);

    // Sorting helper functions
    int partition(std::vector<sf::RectangleShape>& A, int start, int end);
    void merge(std::vector<sf::RectangleShape>& A, std::vector<sf::RectangleShape>& left, std::vector<sf::RectangleShape>& right, int startLeft, int endLeft, int startRight, int endRight);
    void swap(std::vector<sf::RectangleShape>& A, int a, int b);

    // Rendering functions (for recursive sorting algorithms)
    void renderMergeSort(sf::RenderTarget& target, std::vector<sf::RectangleShape>& A, int startLeft, int endRight);

    // Mouse event functions
    void mouseMovedEvent(bool isButtonPressed);
    void mouseButtonPressedEvent(bool &isButtonPressed);

    // Setup before sorting begins
    bool setupSorting();

private:

    // Private variables

    // Window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event event;
    sf::Vector2u windowBounds;

    // Bar object
    sf::RectangleShape bar;

    // Bar vector
    std::vector<sf::RectangleShape> bars;

    // Bar properties
    unsigned int numberOfBars;

    // Bar colors for different scenarios during sorting
    const sf::Color initialColor = sf::Color::Cyan;
    const sf::Color comparisonColor = sf::Color::Red;
    const sf::Color scanColor = sf::Color::Green;
    const sf::Color partitionIndexColor = sf::Color::Blue;
    const sf::Color mergeColor = sf::Color::Blue;
    const sf::Color finalColor = sf::Color::Magenta;

    // Button colors for different scenarious in menu
    const sf::Color unclickedColor = sf::Color::Green;
    const sf::Color clickedColor = sf::Color::Red;
    const sf::Color hoverColor = sf::Color::Red;

    // Bar height vector
	std::vector<float> barHeights;

    // Flag to indicate sorting has finished
    bool sortFinished = true;

    // Fonts
    sf::Font font;

    // Textboxes
    Textbox* numberOfBarsTextbox = new Textbox(30, sf::Color::White, true);

    // Buttons
    Button* selectionSortButton = new Button(15, "Selection Sort", {125, 50}, sf::Color::Green, sf::Color::Black);
    Button* bubbleSortButton = new Button(15, "Bubble Sort", {125, 50}, sf::Color::Green, sf::Color::Black);
    Button* insertionSortButton = new Button(15, "Insertion Sort", {125, 50}, sf::Color::Green, sf::Color::Black);
    Button* mergeSortButton = new Button(15, "Merge Sort", {125, 50}, sf::Color::Green, sf::Color::Black);
    Button* quickSortButton = new Button(15, "Quick Sort", {125, 50}, sf::Color::Green, sf::Color::Black);
    Button* startButton = new Button(15, "START", {125, 50}, sf::Color::Green, sf::Color::Black);
    Button* restartButton = new Button(15, "RESTART", {125, 50}, sf::Color::Green, sf::Color::Black);

    // App state
    appState state = APP_MENU;

    // Sorting select
    sortingAlgorithms sortingSelect = SORTING_NONE;

    // Menu texts
    sf::Text barsText;
    sf::Text errTextInvalidNum;
    sf::Text errTextSortingSelect;
    sf::Text title;

    // Flags to indicate which error text should be displayed on menu
    bool displayErrTextInvalidNum = false;
    bool displayErrTextSortingSelect = false;
};
