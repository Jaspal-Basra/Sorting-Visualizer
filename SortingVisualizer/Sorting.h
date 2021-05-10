#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <vector>
#include <iostream>

class Sorting
{
private:
    // Variables

    // Private methods

    int partition(std::vector<sf::RectangleShape>& A, int start, int end);

    void merge(std::vector<sf::RectangleShape>& A, std::vector<sf::RectangleShape>& left, std::vector<sf::RectangleShape>& right, int n, int nLeft, int nRight);

    void swap(std::vector<sf::RectangleShape>& A, int a, int b);

public:
    // Constructors / Destructors
    Sorting();
    virtual ~Sorting();

    // Public methods

    void quickSort(std::vector<sf::RectangleShape>& A, int start, int end);

    void mergeSort(std::vector<sf::RectangleShape>& A, int n);

    void insertionSort(std::vector<sf::RectangleShape>& A, int n);

    void bubbleSort(std::vector<sf::RectangleShape>& A, int n);

    void selectionSort(std::vector<sf::RectangleShape>& A, int n);
};

