#include "Game.h"

// Constructors / Destructors
Game::Game()
{
	this->initializeVariables();
	this->initWindow();

	this->initBars();
}

Game::~Game()
{
	delete this->window;
}

// Private methods

void Game::initializeVariables()
{
	this->window = nullptr;

	// Bars

	//std::cout << "Enter number of bars: ";
	//std::cin >> numberOfBars;
	this->numberOfBars = NUMBER_OF_BARS;
	this->barSize = WINDOW_WIDTH / static_cast<float>(numberOfBars); // Size of each bar = window width/# of total bars
	this->barCount = 0;

	// Sorting
	bubbleState = BUBBLE_CHECK_CONDITION_OUTER;
	selectionState = SELECTION_CHECK_CONDITION_OUTER;
	insertionState = INSERTION_CHECK_CONDITION_OUTER;

	// Bubble sort
	bubbleSortOuterIndex = 1;
	bubbleSortInnerIndex = bubbleSortOuterIndex + 1;

	// Selection sort
	selectionSortOuterIndex = 0;
	selectionSortInnerIndex = 0;
	innerIndexMin = 0;

	// Insertion sort
	insertionSortOuterIndex = 1;
	insertionSortInnerIndex = 0;

	//std::cout << "Select a sorting algorithm from the following:\nSelection Sort (S)\nBubble Sort (B)\nInsertion Sort (I)\nMerge Sort (M)\nQuick Sort (Q)\nEnter here: ";
	//std::cin >> c;

	c = 'I';

	// Game logic
}

void Game::initWindow()
{
	this->videoMode.height = WINDOW_HEIGHT;
	this->videoMode.width = WINDOW_WIDTH;

	this->window = new sf::RenderWindow(this->videoMode, "Sorting Visualizer", sf::Style::Titlebar | sf::Style::Close);

	windowBounds = this->window->getSize(); // Get window size for later use

	this->window->setFramerateLimit(60);
}

// Public Methods

void Game::update()
{
	this->pollEvents();

	// Update bars
	this->updateBars();
}

void Game::render()
{
	// Clear old frame
	this->window->clear(sf::Color(0, 0, 0, 255));

	// Draw bars
	this->renderBars(*this->window);

	// Update
	this->window->display();
}

const bool Game::isWindowOpen() const
{
	return this->window->isOpen();
}

const sf::Vector2u Game::getWindowSize() const
{
	return this->window->getSize();
}

void Game::pollEvents()
{
	// Event polling
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape)
				this->window->close();
		}
	}
}

/**
* Initializes bars
*/
void Game::initBars()
{
	float xPos, yPos;

	// Initialize Bars
	this->bar.setPosition(0.f, WINDOW_HEIGHT);
	this->bar.setSize(sf::Vector2f(2.f, 500.f));
	this->bar.setFillColor(sf::Color::Cyan);
	this->bar.setOutlineColor(sf::Color::Black);
	this->bar.setOutlineThickness(1.f);

	// Generate all bars
	while (this->bars.size() < this->numberOfBars)
	{
		// Generate a random height for the bar
		float barHeight = static_cast<float>(rand() % static_cast<int>((WINDOW_HEIGHT)));

		this->bar.setSize(sf::Vector2f(this->barSize, barHeight));

		xPos = barSize * static_cast<float>(barCount);
		yPos = WINDOW_HEIGHT - bar.getSize().y;

		this->bar.setPosition(xPos, yPos);

		// Spawn the bar
		this->bars.push_back(this->bar);
		this->barCount += 1;
	}
}

void Game::updateBars()
{
	//bubbleSort(bars, bars.size());

	switch (c)
	{
	case 'S': selectionSort(bars, bars.size()); break;
	case 'B': bubbleSort(bars, bars.size()); break;
	case 'I': insertionSort(bars, bars.size()); break;
	case 'M': break;
	case 'Q': break;
	default: std::cout << "Invalid sorting algorithm selected." << std::endl; break;
	}

	//bubbleSort(bars, bars.size());
	//selectionSort(bars, bars.size());
}

/*
* Renders bars for display on window
*/
void Game::renderBars(sf::RenderTarget& target)
{
	// Rendering all the bars
	for (int i = 0; i < bars.size(); i++)
	{
		target.draw(bars[i]);
	}
}

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

void Game::merge(std::vector<sf::RectangleShape>& A, std::vector<sf::RectangleShape>& left, std::vector<sf::RectangleShape>& right, int n, int nLeft, int nRight)
{
	int i = 0;
	int j = 0;
	int k = 0;
	while (j < nLeft && k < nRight)
	{
		if (left[j].getSize().y <= right[k].getSize().y)
		{
			A[i] = left[j];
			j++;
		}
		else if (right[k].getSize().y < left[j].getSize().y)
		{
			A[i] = right[k];
			k++;
		}
		i++;
	}
	while (j < nLeft)
	{
		A[i] = left[j];
		j++;
		i++;
	}
	while (k < nRight)
	{
		A[i] = right[k];
		k++;
		i++;
	}
}

void Game::swap(std::vector<sf::RectangleShape>& A, int a, int b)
{
	A[a].setPosition(bPos.x, A[a].getPosition().y);
	A[b].setPosition(aPos.x, A[b].getPosition().y);

	temp = A[a];
	A[a] = A[b];
	A[b] = temp;
}

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

void Game::mergeSort(std::vector<sf::RectangleShape>& A, int n)
{
	if (n < 2) return; // Base case (recursion)

	int mid = n / 2;

	std::vector<sf::RectangleShape> left;
	std::vector<sf::RectangleShape> right;

	for (int i = 0; i < mid; i++)
		left.push_back(A[i]);

	for (int i = mid; i < n; i++)
		right.push_back(A[i]);

	mergeSort(left, mid);
	mergeSort(right, n - mid);
	merge(A, left, right, n, mid, n - mid);
}

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

void Game::bubbleSort(std::vector<sf::RectangleShape>& A, int n)
{
	switch (bubbleState)
	{
	case BUBBLE_CHECK_CONDITION_OUTER:
		if (bubbleSortOuterIndex < n)
		{
			hasSwapOccurred = false;
			bubbleState = BUBBLE_CHECK_CONDITION_INNER;
		}
		else
		{
			A[0].setFillColor(sf::Color::Magenta);
			bubbleState = BUBBLE_SORT_FINISHED;
		}
		break;

	case BUBBLE_CHECK_CONDITION_INNER:
		if (bubbleSortInnerIndex < n - bubbleSortOuterIndex)
		{
			bubbleState = BUBBLE_CHECK_CONDITION_SWAP;
		}
		else
		{
			A[bubbleSortInnerIndex].setFillColor(sf::Color::Magenta);
			bubbleState = BUBBLE_INCREMENT_OUTER_INDEX;
			bubbleSortInnerIndex = 0;
		}
		break;

	case BUBBLE_CHECK_CONDITION_SWAP:
		if (A[bubbleSortInnerIndex].getSize().y > A[bubbleSortInnerIndex + 1].getSize().y)
		{
			hasSwapOccurred = true;
			aPos = A[bubbleSortInnerIndex].getPosition();
			bPos = A[bubbleSortInnerIndex + 1].getPosition();
			A[bubbleSortInnerIndex].setFillColor(sf::Color::Red);
			A[bubbleSortInnerIndex+1].setFillColor(sf::Color::Red);
			bubbleState = BUBBLE_SWAP;
		}
		else
		{
			A[bubbleSortInnerIndex].setFillColor(sf::Color::Green);
			A[bubbleSortInnerIndex+1].setFillColor(sf::Color::Green);
			bubbleState = BUBBLE_INCREMENT_INNER_INDEX;
		}
			
		break;

	case BUBBLE_SWAP:
		swap(A, bubbleSortInnerIndex, bubbleSortInnerIndex + 1);
		bubbleState = BUBBLE_INCREMENT_INNER_INDEX;
		break;

	case BUBBLE_INCREMENT_INNER_INDEX:
		A[bubbleSortInnerIndex].setFillColor(sf::Color::Cyan);
		A[bubbleSortInnerIndex+1].setFillColor(sf::Color::Green);
		bubbleSortInnerIndex++;
	    bubbleState = BUBBLE_CHECK_CONDITION_INNER;
		break;

	case BUBBLE_INCREMENT_OUTER_INDEX:
		if (!hasSwapOccurred) // Exit early if no swaps were made in last pass (optimizes the algorithm)
			bubbleState = BUBBLE_SORT_FINISHED;
		else
		{
			bubbleSortOuterIndex++;
			bubbleState = BUBBLE_CHECK_CONDITION_OUTER;
		}
		break;
		
	case BUBBLE_SORT_FINISHED:
		while (bubbleSortOuterIndex < n)
		{
			A[n-bubbleSortOuterIndex].setFillColor(sf::Color::Magenta);
			bubbleSortOuterIndex++;
		}
		A[0].setFillColor(sf::Color::Magenta);
		break;
	}
}

void Game::selectionSort(std::vector<sf::RectangleShape>& A, int n)
{
	switch (selectionState)
	{
	case SELECTION_CHECK_CONDITION_OUTER:
		if (selectionSortOuterIndex < n - 1)
		{
			innerIndexMin = selectionSortOuterIndex;
			selectionSortInnerIndex = selectionSortOuterIndex + 1;
			A[selectionSortOuterIndex].setFillColor(sf::Color::Red);
			selectionState = SELECTION_CHECK_CONDITION_INNER;
		}
		else
			selectionState = SELECTION_SORT_FINISHED;
		break;

	case SELECTION_CHECK_CONDITION_INNER:
		if (selectionSortInnerIndex < n)
		{
			A[selectionSortInnerIndex].setFillColor(sf::Color::Green);
			selectionState = SELECTION_CHECK_CONDITION_MIN;
		}
		else
		{
			selectionState = SELECTION_CHECK_CONDITION_SWAP;
			selectionSortInnerIndex = 0;
		}
		break;

	case SELECTION_CHECK_CONDITION_MIN:
		if (A[selectionSortInnerIndex].getSize().y < A[innerIndexMin].getSize().y)
		{
			if (innerIndexMin != selectionSortOuterIndex)
				A[innerIndexMin].setFillColor(sf::Color::Cyan);
			innerIndexMin = selectionSortInnerIndex;
			A[innerIndexMin].setFillColor(sf::Color::Red);
		}
		selectionState = SELECTION_INCREMENT_INNER_INDEX;
		break;

	case SELECTION_INCREMENT_INNER_INDEX:
		if (selectionSortInnerIndex != innerIndexMin)
			A[selectionSortInnerIndex].setFillColor(sf::Color::Cyan);
		selectionSortInnerIndex++;
		selectionState = SELECTION_CHECK_CONDITION_INNER;
		break;

	case SELECTION_CHECK_CONDITION_SWAP:
		if (A[innerIndexMin].getSize().y < A[selectionSortOuterIndex].getSize().y)
		{
			aPos = A[selectionSortOuterIndex].getPosition();
			bPos = A[innerIndexMin].getPosition();
			selectionState = SELECTION_SWAP;
		}
		else
		{
			A[selectionSortOuterIndex].setFillColor(sf::Color::Magenta);
			selectionState = SELECTION_INCREMENT_OUTER_INDEX;
		}

		break;

	case SELECTION_SWAP:
		swap(A, selectionSortOuterIndex, innerIndexMin);
		A[selectionSortOuterIndex].setFillColor(sf::Color::Magenta);
		A[innerIndexMin].setFillColor(sf::Color::Cyan);
		selectionState = SELECTION_INCREMENT_OUTER_INDEX;
		break;

	case SELECTION_INCREMENT_OUTER_INDEX:
		selectionSortOuterIndex++;
		selectionState = SELECTION_CHECK_CONDITION_OUTER;
		break;

	case SELECTION_SORT_FINISHED:
		A[A.size()-1].setFillColor(sf::Color::Magenta);
		break;
	}
}

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

void Game::insertionSort(std::vector<sf::RectangleShape>& A, int n)
{
	switch (insertionState)
	{
	case INSERTION_CHECK_CONDITION_OUTER:
		if (insertionSortOuterIndex < n)
		{
			insertionSortInnerIndex = insertionSortOuterIndex;
			A[0].setFillColor(sf::Color::Magenta);
			A[insertionSortInnerIndex].setFillColor(sf::Color::Red);
			insertionState = INSERTION_CHECK_CONDITION_INNER;
		}
		else
			insertionState = INSERTION_SORT_FINISHED;
		break;

	case INSERTION_CHECK_CONDITION_INNER:
		if (insertionSortInnerIndex > 0 && A[insertionSortInnerIndex-1].getSize().y > A[insertionSortInnerIndex].getSize().y)
		{
			aPos = A[insertionSortInnerIndex].getPosition();
			bPos = A[insertionSortInnerIndex - 1].getPosition();
			swap(A, insertionSortInnerIndex, insertionSortInnerIndex - 1);
			A[insertionSortInnerIndex].setFillColor(sf::Color::Magenta);
			insertionSortInnerIndex--;
		}
		else
		{
			A[insertionSortInnerIndex].setFillColor(sf::Color::Magenta);
			insertionSortOuterIndex++;
			insertionState = INSERTION_CHECK_CONDITION_OUTER;
		}
		break;

	case INSERTION_SORT_FINISHED:
		break;
	}
}