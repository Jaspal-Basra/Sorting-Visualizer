#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <vector>
#include <iostream>

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

public:
    // Constructors / Destructors
    Bar();
    virtual ~Bar();

    // Public Methods

    void update();
    void updateBars();

    void render(sf::RenderTarget& target);
    void renderBars(sf::RenderTarget& target);

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

