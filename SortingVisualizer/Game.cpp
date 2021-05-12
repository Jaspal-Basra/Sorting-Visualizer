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
	//this->numberOfBars = NUMBER_OF_BARS;
	this->barSize = WINDOW_WIDTH / static_cast<float>(numberOfBars); // Size of each bar = window width/# of total bars
	this->barCount = 0;

	// Sorting
	bubbleSortOuterIndex = 1;
	bubbleSortInnerIndex = 0;

	moveFinished = false;
	hasSwapOccurred = false;

	waitTime = static_cast<std::chrono::microseconds>(500000);

	bubbleState = BUBBLE_CHECK_CONDITION_OUTER;

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
	//float xPos, yPos;

	//quickSort(bars, 0, bars.size() - 1);
	bubbleSort(bars, bars.size());

	/*
	// Update positions of all bars after sort
	for (int i = 0; i < bars.size(); i++)
	{
		xPos = barSize * static_cast<float>(i);
		yPos = WINDOW_HEIGHT - bars[i].getSize().y;
		this->bars[i].setPosition(xPos, yPos);
	}
	*/
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
	//A[a].setFillColor(sf::Color::Green);
	//A[b].setFillColor(sf::Color::Green);
	//for (int i = 0; i < 100000; i++)
	//{
	//if ((A[a].getPosition().x < bPos.x || A[b].getPosition().x > aPos.x))
	//{
		//A[a].move(1.f, 0.f);
		//A[b].move(-1.f, 0.f);
	//}
	//else if ((A[a].getPosition().x > bPos.x || A[b].getPosition().x < aPos.x))
	//{
		//A[a].move(-1.f, 0.f);
		//A[b].move(1.f, 0.f);
	//}
	//else
	//{
		//A[a].move(0.f, 0.f);
		//A[b].move(0.f, 0.f);

	A[a].setPosition(bPos.x, A[a].getPosition().y);
	A[b].setPosition(aPos.x, A[b].getPosition().y);

		temp = A[a];
		A[a] = A[b];
		A[b] = temp;

		

		//if (b == A.size()-1)
			//A[b].setFillColor(sf::Color::Magenta);
		//else
		//A[b].setFillColor(sf::Color::Green);

		//A[a].setFillColor(sf::Color::Cyan);
	    //A[b].setFillColor(sf::Color::Cyan);

		moveFinished = true;
		//break;
	//}
	//}
	
	
	// A[a].setPosition(aPos.x, A[a].getPosition().y);
	// A[b].setPosition(bPos.x, A[b].getPosition().y);
	// A[a] = A[b];
	// A[b] = temp;
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

void Game::insertionSort(std::vector<sf::RectangleShape>& A, int n)
{
	float val;
	int hole;

	for (int i = 1; i < n; i++)
	{
		val = A[i].getSize().y;
		hole = i;

		while (hole > 0 && A[hole - 1].getSize().y > val)
		{
			A[hole] = A[hole - 1];
			hole--;
		}
		A[hole].setSize(sf::Vector2f(A[hole].getSize().x, val));
	}
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
			//startTime = std::chrono::high_resolution_clock::now();
			bubbleState = BUBBLE_CHECK_CONDITION_SWAP;
		}
		else
		{
			//if (bubbleSortInnerIndex == n - bubbleSortOuterIndex - 1)
			A[bubbleSortInnerIndex].setFillColor(sf::Color::Magenta);
			bubbleState = BUBBLE_INCREMENT_OUTER_INDEX;
			bubbleSortInnerIndex = 0;
		}
		break;

	case BUBBLE_CHECK_CONDITION_SWAP:
		if (A[bubbleSortInnerIndex].getSize().y > A[bubbleSortInnerIndex + 1].getSize().y)
		{
			//temp = A[bubbleSortInnerIndex];
			hasSwapOccurred = true;
			aPos = A[bubbleSortInnerIndex].getPosition();
			bPos = A[bubbleSortInnerIndex + 1].getPosition();
			bubbleState = BUBBLE_SWAP;
			A[bubbleSortInnerIndex].setFillColor(sf::Color::Red);
			A[bubbleSortInnerIndex+1].setFillColor(sf::Color::Red);
		}
		else
		{
			// Check timer here to allow to stay green for some time
			//std::chrono::steady_clock
			A[bubbleSortInnerIndex].setFillColor(sf::Color::Green);
			A[bubbleSortInnerIndex+1].setFillColor(sf::Color::Green);
			currTime = std::chrono::high_resolution_clock::now();
			//if (std::chrono::duration_cast<std::chrono::microseconds>(currTime - startTime) >= waitTime)
			{
				//A[bubbleSortInnerIndex].setFillColor(sf::Color::Cyan);
				bubbleState = BUBBLE_INCREMENT_INNER_INDEX;
			}
		}
			
		break;

	case BUBBLE_SWAP:
		if (moveFinished)
		{
			//if (bubbleSortInnerIndex == n - bubbleSortOuterIndex - 1)
				//A[bubbleSortInnerIndex+1].setFillColor(sf::Color::Magenta);
			bubbleState = BUBBLE_INCREMENT_INNER_INDEX;
			moveFinished = 0;
		}
		else
		{
			//A[bubbleSortInnerIndex].setFillColor(sf::Color::Green);
			//A[bubbleSortInnerIndex+1].setFillColor(sf::Color::Green);
			swap(A, bubbleSortInnerIndex, bubbleSortInnerIndex + 1);
		}
			
		break;

	case BUBBLE_INCREMENT_INNER_INDEX:
		//if (bubbleSortInnerIndex == n - bubbleSortOuterIndex - 1)
			//A[bubbleSortInnerIndex+1].setFillColor(sf::Color::Magenta);
		A[bubbleSortInnerIndex].setFillColor(sf::Color::Cyan);
		A[bubbleSortInnerIndex+1].setFillColor(sf::Color::Green);
		bubbleSortInnerIndex++;
	    bubbleState = BUBBLE_CHECK_CONDITION_INNER;
		break;

	case BUBBLE_INCREMENT_OUTER_INDEX:
		if (!hasSwapOccurred)
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
