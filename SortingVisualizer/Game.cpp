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
	std::cout << "Enter number of bars: ";
	std::cin >> numberOfBars;
	// this->numberOfBars = NUMBER_OF_BARS;
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

	// Merge sort
	renderM = false;
	last = false;

	// Quick sort

	std::cout << "Select a sorting algorithm from the following:\nSelection Sort (S)\nBubble Sort (B)\nInsertion Sort (I)\nMerge Sort (M)\nQuick Sort (Q)\nEnter here: ";
	std::cin >> c;
    // c = 'Q';

    barIndex = 0;

	index1 = 2;

	cnt2 = 0;

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

    for (int i = 0; i < numberOfBars; i++)
    {
    	barPositions.push_back(bars[i].getPosition().x);
		barHeights.push_back(bars[i].getSize().y);
		barHeights2.push_back(bars[i].getSize().y);
    }
}

void Game::updateBars()
{
	switch (c)
	{
	case 'S': selectionSort(bars, bars.size()); break;
	case 'B': bubbleSort(bars, bars.size()); break;
	case 'I': insertionSort(bars, bars.size()); break;
	case 'M': 
		if (!sortFinished) 
		{
			mergeSort(bars, 0, bars.size() - 1);
			sortFinished = true;
		}
		break;

	case 'Q': 
		if (!sortFinished)
		{
			quickSort(bars, 0, bars.size() - 1);
			sortFinished = true;
		}
		break;

	default: std::cout << "Invalid sorting algorithm selected." << std::endl; break;
	}
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

void Game::swap(std::vector<sf::RectangleShape>& A, int a, int b)
{
	A[a].setPosition(bPos.x, A[a].getPosition().y);
	A[b].setPosition(aPos.x, A[b].getPosition().y);

	temp = A[a];
	A[a] = A[b];
	A[b] = temp;
}

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

void Game::mergeSort(std::vector<sf::RectangleShape>& A, int start, int end)
{
	int n = end - start + 1;

    // Poll events
    pollEvents();

	if (n < 2) return; // Base case (recursion)

	int mid = n / 2 + start;

	std::vector<sf::RectangleShape> left;
	std::vector<sf::RectangleShape> right;

	for (int i = start; i < mid; i++)
		left.push_back(A[i-start]);

	for (int i = mid; i < n+start; i++)
		right.push_back(A[i-start]);

	mergeSort(left, start, mid - 1);
	mergeSort(right, mid, end);
	merge(A, left, right, start, mid, mid, end + 1);

	left.clear();
	right.clear();
}

void Game::merge(std::vector<sf::RectangleShape>& A, std::vector<sf::RectangleShape>& left, std::vector<sf::RectangleShape>& right, int startLeft, int endLeft, int startRight, int endRight)
{
	int j = 0;
	int k = 0;
	float xPos, yPos;

	int nLeft = endLeft - startLeft;
	int nRight = endRight - startRight;

	barIndex = startLeft;

	for (int i = 0; i < nLeft; i++)
	{
		left[i].setSize(sf::Vector2f(bars[i].getSize().x, bars[i + startLeft].getSize().y));
	}

	for (int i = 0; i < nRight; i++)
	{
		right[i].setSize(sf::Vector2f(bars[i].getSize().x, bars[i + startRight].getSize().y));
	}

	while (j < nLeft && k < nRight)
	{
		bars[startLeft + j].setFillColor(sf::Color::Red);
		bars[startRight + k].setFillColor(sf::Color::Red);
		renderColor(*this->window);
		if (left[j].getSize().y <= right[k].getSize().y)
		{
			bars[startLeft + j].setFillColor(sf::Color::Cyan);
			barHeights2[barIndex] = left[j].getSize().y;
			j++;
		}
		else if (right[k].getSize().y < left[j].getSize().y)
		{
			bars[startRight + k].setFillColor(sf::Color::Cyan);
			barHeights2[barIndex] = right[k].getSize().y;
			k++;
		}
		barIndex++;
	}
	while (j < nLeft)
	{
		bars[startLeft + j].setFillColor(sf::Color::Cyan);
		barHeights2[barIndex] = left[j].getSize().y;
		j++;
		renderColor(*this->window);
		barIndex++;
	}
	while (k < nRight)
	{
		bars[startRight + k].setFillColor(sf::Color::Cyan);
		barHeights2[barIndex] = right[k].getSize().y;
		k++;
		renderColor(*this->window);
		barIndex++;
	}
	renderM = true;
	renderMergeSort(*this->window, A, startLeft, endRight);
}

void Game::renderColor(sf::RenderTarget& target)
{
	this->window->clear(sf::Color(0, 0, 0, 255));

	// Rendering all the bars
	for (int i = 0; i < bars.size(); i++)
	{
		target.draw(bars[i]);
	}

	this->window->display();
}

void Game::renderMergeSort(sf::RenderTarget& target, std::vector<sf::RectangleShape>& A, int startLeft, int endRight)
{
	if ((endRight - startLeft) == bars.size())
		last = true;

	for (int j = startLeft; j < endRight; j++)
	{
		barHeights[j] = barHeights2[j];

		bars[j].setFillColor(sf::Color::Blue);

		for (int i = 0; i < bars.size(); i++)
		{
			pollEvents();
			bars[i].setSize(sf::Vector2f(bars[i].getSize().x, barHeights[i]));
			bars[i].setPosition(bars[i].getPosition().x, WINDOW_HEIGHT-bars[i].getSize().y);
		}

		renderColor(*this->window);

		if (!last)
		{
			bars[j].setFillColor(sf::Color::Cyan);
		}
		else
		{
			bars[j].setFillColor(sf::Color::Magenta);
		}
	}

	if (last)
		last = false;
}

void Game::quickSort(std::vector<sf::RectangleShape>& A, int start, int end)
{
	int partitionIndex;

	pollEvents();

	if (start < end)
	{
		partitionIndex = partition(A, start, end);
		bars[partitionIndex].setFillColor(sf::Color::Magenta);
		renderColor(*this->window);
		quickSort(A, start, partitionIndex - 1);
		quickSort(A, partitionIndex + 1, end);
	}
	else if (start == end)
	{
		bars[start].setFillColor(sf::Color::Magenta);
		renderColor(*this->window);
	}
}

int Game::partition(std::vector<sf::RectangleShape>& A, int start, int end)
{
	int pivot = A[end].getSize().y;
	A[end].setFillColor(sf::Color::Blue);
	renderColor(*this->window);
	int partitionIndex = start;

	for (int i = start; i < end; i++)
	{
		pollEvents();

		A[i].setFillColor(sf::Color::Red);
		A[partitionIndex].setFillColor(sf::Color::Red);
		renderColor(*this->window);

		A[i].setFillColor(sf::Color::Cyan);
		A[partitionIndex].setFillColor(sf::Color::Cyan);

		if (A[i].getSize().y <= pivot)
		{
			aPos = A[i].getPosition();
			bPos = A[partitionIndex].getPosition();
			swap(A, i, partitionIndex);
			partitionIndex++;
		}
	}
	aPos = A[end].getPosition();
	bPos = A[partitionIndex].getPosition();
	swap(A, end, partitionIndex);
	A[partitionIndex].setFillColor(sf::Color::Cyan);

	renderColor(*this->window);

	return partitionIndex;
}