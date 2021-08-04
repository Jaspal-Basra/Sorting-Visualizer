#include "App.h"

// Constructors / Destructors
App::App()
{
	initializeVariables();
	initWindow();

	initBars();
}

App::~App()
{
	delete window;
}

/**
* Initializes class variables
*/
void App::initializeVariables()
{
	// Bars
	std::cout << "Enter number of bars: ";
	std::cin >> numberOfBars;
	barSize = WINDOW_WIDTH / static_cast<float>(numberOfBars); // Size of each bar = window width/# of total bars

	// Sorting
	std::cout << "Select a sorting algorithm from the following:\nSelection Sort (S)\nBubble Sort (B)\nInsertion Sort (I)\nMerge Sort (M)\nQuick Sort (Q)\nEnter here: ";
	std::cin >> sortingSelect;

	// Bar colors for different scenarios during sorting
	initialColor = sf::Color::Cyan;
    comparisonColor = sf::Color::Red;
    scanColor = sf::Color::Green;
    partitionIndexColor = sf::Color::Blue;
    mergeColor = sf::Color::Blue;
    finalColor = sf::Color::Magenta;
}

/**
* Initializes app window
*/
void App::initWindow()
{
	videoMode.height = WINDOW_HEIGHT;
	videoMode.width = WINDOW_WIDTH;

	window = new sf::RenderWindow(videoMode, "Sorting Visualizer", sf::Style::Titlebar | sf::Style::Close);

	windowBounds = window->getSize(); // Get window size for later use

	window->setFramerateLimit(60);
}

/**
* Updates window
*/
void App::update()
{
	pollEvents();

	// Update bars
	updateBars();
}

/**
* Renders updates onto window
*/
void App::render()
{
	// Clear old frame
	window->clear(sf::Color(0, 0, 0, 255));

	// Draw bars
	renderBars(*window);

	// Update
	window->display();
}

/*
* Renders bars for display on window
*/
void App::renderBars(sf::RenderTarget& target)
{
	// Rendering all the bars
	for (unsigned int i = 0; i < bars.size(); i++)
	{
		target.draw(bars[i]);
	}
}

/**
* Checks if window is open
*
* @return  True if window is open, false if not
*/
const bool App::isWindowOpen() const
{
	return window->isOpen();
}

/**
* Retrieves window size
*
* @return  Size of window
*/
const sf::Vector2u App::getWindowSize() const
{
	return window->getSize();
}

/**
* Polls for events on window
*/
void App::pollEvents()
{
	// Event polling
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				window->close();
		}
	}
}

/**
* Initializes a new set of bars by generating their size/position and adding them to
* a data structure
*/
void App::initBars()
{
	unsigned int barCount = 0;
	float xPos, yPos;
	float barHeight;

	// Clear all bar vectors
	bars.clear();
	barHeights.clear();

	// Initialize Bars
	bar.setPosition(0.f, WINDOW_HEIGHT);
	bar.setSize(sf::Vector2f(2.f, 500.f));
	bar.setFillColor(initialColor);
	bar.setOutlineColor(sf::Color::Black);
	bar.setOutlineThickness(1.f);

	// Generate all bars
	while (bars.size() < numberOfBars)
	{
		// Generate a random height for the bar
		barHeight = static_cast<float>(rand() % static_cast<int>((WINDOW_HEIGHT)));

		// Set bar size
		bar.setSize(sf::Vector2f(barSize, barHeight));

		// Generate bar position based on current bar count and position
		xPos = barSize * static_cast<float>(barCount);
		yPos = WINDOW_HEIGHT - bar.getSize().y;

		// Set bar position
		bar.setPosition(xPos, yPos);

		// Add bar to vector
		bars.push_back(bar);

		barCount += 1;
	}

	// Record height of each bar
    for (unsigned int i = 0; i < numberOfBars; i++)
    {
		barHeights.push_back(bars[i].getSize().y);
    }
}

/**
* Update bars
*/
void App::updateBars()
{
	// Reset variables and bars for next run if sort has finished
	if (sortFinished)
	{
		initializeVariables();
		initBars();
		render();
		sortFinished = false;
	}

	// Run sorting algorithm based on user selection
	switch (sortingSelect)
	{
		case 'S': selectionSort(bars, bars.size()); break;
		case 'B': bubbleSort(bars, bars.size()); break;
		case 'I': insertionSort(bars, bars.size()); break;
		case 'M': 
			mergeSort(bars, 0, bars.size() - 1);
			sortFinished = true;
			break;

		case 'Q': 
			quickSort(bars, 0, bars.size() - 1);
			sortFinished = true;
			break;

		default: 
			std::cout << "Invalid sorting algorithm selected.\n";
			std::cout << "Select a sorting algorithm from the following : \nSelection Sort(S)\nBubble Sort(B)\nInsertion Sort(I)\nMerge Sort(M)\nQuick Sort(Q)\nEnter here : ";
			std::cin >> sortingSelect;
			break;
	}
}

/*
* Swaps two bars in a vector and also swaps their positions
*
* @param  A Vector that contains bars
* @param  a First bar to swap
* @param  b Second bar to swap
*/
void App::swap(std::vector<sf::RectangleShape>& A, int a, int b)
{
	sf::RectangleShape temp;

	// Save positions of bars at index a and b
	sf::Vector2f aPos = A[a].getPosition();
	sf::Vector2f bPos = A[b].getPosition();

	// Swap positions of bars
	A[a].setPosition(bPos.x, aPos.y);
	A[b].setPosition(aPos.x, bPos.y);

	// Swap bars in vector
	temp = A[a];
	A[a] = A[b];
	A[b] = temp;
}

/*
* Runs bubble sort (implemented as state machine to prevent blocking App's main loop)
*
* @param  A Vector that contains bars
* @param  n Number of bars in vector
*/
void App::bubbleSort(std::vector<sf::RectangleShape>& A, int n)
{
	static bubbleSortState bubbleState = BUBBLE_CHECK_CONDITION_OUTER; 

	static uint8_t bubbleSortOuterIndex = 1;
    static uint8_t bubbleSortInnerIndex = bubbleSortOuterIndex + 1;
    static bool hasSwapOccurred; // Optimizes bubble sort by exiting early

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
				A[0].setFillColor(finalColor);
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
				A[bubbleSortInnerIndex].setFillColor(finalColor);
				bubbleState = BUBBLE_INCREMENT_OUTER_INDEX;
				bubbleSortInnerIndex = 0;
			}
			break;

		case BUBBLE_CHECK_CONDITION_SWAP:
			if (A[bubbleSortInnerIndex].getSize().y > A[bubbleSortInnerIndex + 1].getSize().y)
			{
				hasSwapOccurred = true;
				A[bubbleSortInnerIndex].setFillColor(comparisonColor);
				A[bubbleSortInnerIndex+1].setFillColor(comparisonColor);
				bubbleState = BUBBLE_SWAP;
			}
			else
			{
				A[bubbleSortInnerIndex].setFillColor(scanColor);
				A[bubbleSortInnerIndex+1].setFillColor(scanColor);
				bubbleState = BUBBLE_INCREMENT_INNER_INDEX;
			}
				
			break;

		case BUBBLE_SWAP:
			swap(A, bubbleSortInnerIndex, bubbleSortInnerIndex + 1);
			bubbleState = BUBBLE_INCREMENT_INNER_INDEX;
			break;

		case BUBBLE_INCREMENT_INNER_INDEX:
			A[bubbleSortInnerIndex].setFillColor(initialColor);
			A[bubbleSortInnerIndex+1].setFillColor(scanColor);
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
				A[n-bubbleSortOuterIndex].setFillColor(finalColor);
				bubbleSortOuterIndex++;
			}
			A[0].setFillColor(finalColor);
			bubbleSortOuterIndex = 1;
			bubbleSortInnerIndex = bubbleSortOuterIndex + 1;
			sortFinished = true;
			bubbleState = BUBBLE_CHECK_CONDITION_OUTER;
			break;
	}
}

/*
* Runs selection sort (implemented as state machine to prevent blocking App's main loop)
*
* @param  A Vector that contains bars
* @param  n Number of bars in vector
*/
void App::selectionSort(std::vector<sf::RectangleShape>& A, int n)
{
	static selectionSortState selectionState = SELECTION_CHECK_CONDITION_OUTER;

	static uint8_t selectionSortOuterIndex = 0;
	static uint8_t selectionSortInnerIndex = 0;
	static uint8_t innerIndexMin = 0;

	switch (selectionState)
	{
		case SELECTION_CHECK_CONDITION_OUTER:
			if (selectionSortOuterIndex < n - 1)
			{
				innerIndexMin = selectionSortOuterIndex;
				selectionSortInnerIndex = selectionSortOuterIndex + 1;
				A[selectionSortOuterIndex].setFillColor(comparisonColor);
				selectionState = SELECTION_CHECK_CONDITION_INNER;
			}
			else
				selectionState = SELECTION_SORT_FINISHED;
			break;

		case SELECTION_CHECK_CONDITION_INNER:
			if (selectionSortInnerIndex < n)
			{
				A[selectionSortInnerIndex].setFillColor(scanColor);
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
					A[innerIndexMin].setFillColor(initialColor);
				innerIndexMin = selectionSortInnerIndex;
				A[innerIndexMin].setFillColor(comparisonColor);
			}
			selectionState = SELECTION_INCREMENT_INNER_INDEX;
			break;

		case SELECTION_INCREMENT_INNER_INDEX:
			if (selectionSortInnerIndex != innerIndexMin)
				A[selectionSortInnerIndex].setFillColor(initialColor);
			selectionSortInnerIndex++;
			selectionState = SELECTION_CHECK_CONDITION_INNER;
			break;

		case SELECTION_CHECK_CONDITION_SWAP:
			if (A[innerIndexMin].getSize().y < A[selectionSortOuterIndex].getSize().y)
			{
				selectionState = SELECTION_SWAP;
			}
			else
			{
				A[selectionSortOuterIndex].setFillColor(finalColor);
				selectionState = SELECTION_INCREMENT_OUTER_INDEX;
			}
			break;

		case SELECTION_SWAP:
			swap(A, selectionSortOuterIndex, innerIndexMin);
			A[selectionSortOuterIndex].setFillColor(finalColor);
			A[innerIndexMin].setFillColor(initialColor);
			selectionState = SELECTION_INCREMENT_OUTER_INDEX;
			break;

		case SELECTION_INCREMENT_OUTER_INDEX:
			selectionSortOuterIndex++;
			selectionState = SELECTION_CHECK_CONDITION_OUTER;
			break;

		case SELECTION_SORT_FINISHED:
			A[A.size()-1].setFillColor(finalColor);
			selectionSortOuterIndex = 0;
			selectionSortInnerIndex = 0;
			innerIndexMin = 0;
			sortFinished = true;
			selectionState = SELECTION_CHECK_CONDITION_OUTER;
			break;
	}
}

/*
* Runs insertion sort (implemented as state machine to prevent blocking App's main loop)
*
* @param  A Vector that contains bars
* @param  n Number of bars in vector
*/
void App::insertionSort(std::vector<sf::RectangleShape>& A, int n)
{
	static insertionSortState insertionState = INSERTION_CHECK_CONDITION_OUTER;
	static uint8_t insertionSortOuterIndex = 1;
	static uint8_t insertionSortInnerIndex = 0;

	switch (insertionState)
	{
		case INSERTION_CHECK_CONDITION_OUTER:
			if (insertionSortOuterIndex < n)
			{
				insertionSortInnerIndex = insertionSortOuterIndex;
				A[0].setFillColor(finalColor);
				A[insertionSortInnerIndex].setFillColor(comparisonColor);
				insertionState = INSERTION_CHECK_CONDITION_INNER;
			}
			else
				insertionState = INSERTION_SORT_FINISHED;
			break;

		case INSERTION_CHECK_CONDITION_INNER:
			if (insertionSortInnerIndex > 0 && A[insertionSortInnerIndex-1].getSize().y > A[insertionSortInnerIndex].getSize().y)
			{
				swap(A, insertionSortInnerIndex, insertionSortInnerIndex - 1);
				A[insertionSortInnerIndex].setFillColor(finalColor);
				insertionSortInnerIndex--;
			}
			else
			{
				A[insertionSortInnerIndex].setFillColor(finalColor);
				insertionSortOuterIndex++;
				insertionState = INSERTION_CHECK_CONDITION_OUTER;
			}
			break;

		case INSERTION_SORT_FINISHED:
			insertionSortOuterIndex = 1;
			insertionSortInnerIndex = 0;
			sortFinished = true;
			insertionState = INSERTION_CHECK_CONDITION_OUTER;
			break;
	}
}

/*
* Runs merge sort
*
* @param A      Vector that contains bars
* @param start  First index in vector
* @param end    Final index in vector
*/
void App::mergeSort(std::vector<sf::RectangleShape>& A, int start, int end)
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

	// Clear auxiliary vectors
	left.clear();
	right.clear();
}

/*
* Merges left and right vector into parent vector (used in merge sort)
*
* @param A           Vector that contains bars
* @param startLeft   First index of left vector
* @param endLeft     Final index of left vector
* @param startRight  First index of right vector
* @param endRight    Final index of right vector
*/
void App::merge(std::vector<sf::RectangleShape>& A, std::vector<sf::RectangleShape>& left, std::vector<sf::RectangleShape>& right, int startLeft, int endLeft, int startRight, int endRight)
{
	int j = 0;
	int k = 0;

	int barIndex;

	int nLeft = endLeft - startLeft;
	int nRight = endRight - startRight;

	barIndex = startLeft;

	// Update heights of bars in left and right auxiliary vectors
	for (int i = 0; i < nLeft; i++)
	{
		left[i].setSize(sf::Vector2f(bars[i].getSize().x, bars[i + startLeft].getSize().y));
	}
	for (int i = 0; i < nRight; i++)
	{
		right[i].setSize(sf::Vector2f(bars[i].getSize().x, bars[i + startRight].getSize().y));
	}

	// Merge left and right auxiliary vectors into parent vector
	while (j < nLeft && k < nRight)
	{
		bars[startLeft + j].setFillColor(comparisonColor);
		bars[startRight + k].setFillColor(comparisonColor);
		render();

		if (left[j].getSize().y <= right[k].getSize().y)
		{
			bars[startLeft + j].setFillColor(initialColor);
			barHeights[barIndex] = left[j].getSize().y;
			j++;
		}
		else if (right[k].getSize().y < left[j].getSize().y)
		{
			bars[startRight + k].setFillColor(initialColor);
			barHeights[barIndex] = right[k].getSize().y;
			k++;
		}

		barIndex++;
	}

	// Finish merging in case one auxiliary vector was exhausted before the other
	while (j < nLeft)
	{
		bars[startLeft + j].setFillColor(initialColor);
		barHeights[barIndex] = left[j].getSize().y;
		j++;
		render();
		barIndex++;
	}
	while (k < nRight)
	{
		bars[startRight + k].setFillColor(initialColor);
		barHeights[barIndex] = right[k].getSize().y;
		k++;
		render();
		barIndex++;
	}

	// Render changes
	renderMergeSort(*window, A, startLeft, endRight);
}

void App::renderMergeSort(sf::RenderTarget& target, std::vector<sf::RectangleShape>& A, int startLeft, int endRight)
{
	// Flag to indicate whether this is the final run of merge before the vector is sorted
	static bool finalRun = false;

	// If segment of vector equals total vector size, mark this as final run of merge
	if ((endRight - startLeft) == bars.size())
		finalRun = true;

	// Update heights of bars for current segment of vector
	for (int i = startLeft; i < endRight; i++)
	{
		// Poll events
		pollEvents();

		// Set leading bar to blue colour
		bars[i].setFillColor(mergeColor);

		bars[i].setSize(sf::Vector2f(bars[i].getSize().x, barHeights[i]));
		bars[i].setPosition(bars[i].getPosition().x, WINDOW_HEIGHT-bars[i].getSize().y);

		render();

		// If final run of merge, then set final color, otherwise set default colour
		if (finalRun)
			bars[i].setFillColor(finalColor);
		else
			bars[i].setFillColor(initialColor);
	}

	// Reset final run flag
	if (finalRun)
		finalRun = false;
}

/*
* Runs quick sort
*
* @param A      Vector that contains bars
* @param start  First index in vector
* @param end    Final index in vector
*/
void App::quickSort(std::vector<sf::RectangleShape>& A, int start, int end)
{
	int partitionIndex;

	pollEvents();

	if (start < end)
	{
		partitionIndex = partition(A, start, end);
		bars[partitionIndex].setFillColor(finalColor);
		render();
		quickSort(A, start, partitionIndex - 1);
		quickSort(A, partitionIndex + 1, end);
	}
	else if (start == end)
	{
		// If there is one element in the segment, it has been sorted
		bars[start].setFillColor(finalColor);
		render();
	}
}

/*
* Paritions the bar vector (used in quick sort)
*
* @param A      Vector that contains bars
* @param start  First index in current partition
* @param end    Final index in current partition
*/
int App::partition(std::vector<sf::RectangleShape>& A, int start, int end)
{
	float pivot = A[end].getSize().y;
	A[end].setFillColor(partitionIndexColor);
	render();
	int partitionIndex = start;

	for (int i = start; i < end; i++)
	{
		pollEvents();

		A[i].setFillColor(comparisonColor);
		A[partitionIndex].setFillColor(comparisonColor);
		render();

		A[i].setFillColor(initialColor);
		A[partitionIndex].setFillColor(initialColor);

		if (A[i].getSize().y <= pivot)
		{
			swap(A, i, partitionIndex);
			partitionIndex++;
		}
	}
	swap(A, end, partitionIndex);
	A[partitionIndex].setFillColor(initialColor);

	render();

	return partitionIndex;
}