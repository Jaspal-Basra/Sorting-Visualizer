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

#define NUMBER_OF_BARS  8

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
    bool mergeSortFinished;
    bool renderM;
    bool last;

    char c;

    std::vector<float> barPositions;
    std::vector<sf::RectangleShape> barsBuf;

	std::vector<float> barHeights;
	std::vector<float> barHeights2;

	int barIndex, index1, cnt2;

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

    //int partition(std::vector<sf::RectangleShape>& A, int start, int end);
    void merge(std::vector<sf::RectangleShape>& A, std::vector<sf::RectangleShape>& left, std::vector<sf::RectangleShape>& right, int startLeft, int endLeft, int startRight, int endRight);
    void swap(std::vector<sf::RectangleShape>& A, int a, int b);

public:

    // Public methods

    //void quickSort(std::vector<sf::RectangleShape>& A, int start, int end);
    void mergeSort(std::vector<sf::RectangleShape>& A, int start, int end);
    void insertionSort(std::vector<sf::RectangleShape>& A, int n);
    void bubbleSort(std::vector<sf::RectangleShape>& A, int n);
    void selectionSort(std::vector<sf::RectangleShape>& A, int n);

    void renderMergeSort(sf::RenderTarget& target, std::vector<sf::RectangleShape>& A, int startLeft, int endRight);
    void renderColor(sf::RenderTarget& target, std::vector<sf::RectangleShape>& A, int startLeft, int endRight);
};

/*
int Game::partition(std::vector<sf::RectangleShape>& A, int start, int end)
{
	int pivot = A[end].getSize().y;
	int partitionIndex = start;

	for (int i = start; i < end; i++)
	{
		if (A[i].getSize().y <= pivot)
		{
			swap(A, i, partitionIndex);
			partitionIndex++;
		}
	}
	swap(A, end, partitionIndex);

	return partitionIndex;
}
*/

/*
void Game::quickSort(std::vector<sf::RectangleShape>& A, int start, int end)
{
	int partitionIndex;

	if (start < end)
	{
		partitionIndex = partition(A, start, end);
		quickSort(A, start, partitionIndex - 1);
		quickSort(A, partitionIndex + 1, end);
	}
}
*/

/*
void Game::bubbleSort(std::vector<sf::RectangleShape>& A, int n)
{
	int hasSwapOccurred = false;
	for (int k = 1; k < n; k++)
	{
		hasSwapOccurred = false;
		for (int i = 0; i < n - k; i++)
		{
			if (A[i].getSize().y > A[i + 1].getSize().y)
			{
				hasSwapOccurred = true;
				swap(A, i, i + 1);
			}
		}

		if (!hasSwapOccurred)
			return;
	}
}
*/

/*
void Game::selectionSort(std::vector<sf::RectangleShape>& A, int n)
{
	int i_min = 0;

	for (int k = 0; k < n - 1; k++)
	{
		i_min = k;
		for (int i = k + 1; i < n; i++)
		{
			if (A[i].getSize().y < A[i_min].getSize().y)
				i_min = i;
		}
		if (A[i_min].getSize().y < A[k].getSize().y)
			swap(A, k, i_min);
	}
}
*/

/*
void InsertionSort(int* A, int n)
{
	int val;
	int hole;

	for (int i = 1; i < n; i++)
	{
		val = A[i];
		hole = i;

		while (hole > 0 && A[hole-1] > val)
		{
			A[hole] = A[hole-1];
			hole--;
		}

		A[hole] = val;
	}
}
*/

/*
void InsertionSort(int* A, int n)
{
	int temp;
	int j;
	for (int i = 1; i < n; i++)
	{
		j = i;
		while (j > 0 && A[j - 1] > A[j])
		{
			temp = A[j];
			A[j] = A[j - 1];
			A[j - 1] = temp;
			j--;
		}
	}
}
*/
