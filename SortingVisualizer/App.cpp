#include "App.h"

// Constructors / Destructors
App::App()
{
	initWindow();
	initBars();
	initMenu();
}

App::~App()
{
	// Delete windows
	delete window;

	// Delete textboxes
	delete numberOfBarsTextbox;

	// Delete buttons
	delete selectionSortButton;
	delete bubbleSortButton;
	delete insertionSortButton;
	delete mergeSortButton;
	delete quickSortButton;
	delete startButton;
	delete restartButton;
}

/**
 * Initializes menu
 */
void App::initMenu()
{
	initFont();
	initText();
	initButtons();
}

/**
 * Initializes app window
 */
void App::initWindow()
{
#if !(FULLSCREEN_ON)
	videoMode.height = WINDOW_HEIGHT;
	videoMode.width = WINDOW_WIDTH;

	window = new sf::RenderWindow(videoMode, "Sorting Visualizer", sf::Style::Titlebar | sf::Style::Close);
#else // !(FULLSCREEN_ON)
	window = new sf::RenderWindow(videoMode, "Sorting Visualizer", sf::Style::Titlebar | sf::Style::Close | sf::Style::Fullscreen);
#endif // !(FULLSCREEN_ON)

	// Get window size for later use
	windowBounds = window->getSize();
}

/**
 * Updates window
 */
void App::update()
{
	pollEvents();

	switch (state)
	{
		case APP_SORTING:
			// Update bars
			updateBars();
			break;

		default:
			break;
	}
}

/**
 * Renders menu for display on window
 */
void App::renderMenu(sf::RenderTarget& target)
{
	numberOfBarsTextbox->draw(*window);
	window->draw(barsText);
	window->draw(title);
	selectionSortButton->draw(*window);
	bubbleSortButton->draw(*window);
	insertionSortButton->draw(*window);
	mergeSortButton->draw(*window);
	quickSortButton->draw(*window);
	startButton->draw(*window);

	// Display the relevant error text onto menu screen if necessary
	if (displayErrTextInvalidNum && displayErrTextSortingSelect)
	{
		window->draw(errTextInvalidNum);
		errTextSortingSelect.setPosition({windowBounds.x/2 - errTextSortingSelect.getLocalBounds().width/2, barsText.getPosition().y + errTextInvalidNum.getLocalBounds().height + errTextSortingSelect.getLocalBounds().height + windowBounds.y/40});
		window->draw(errTextSortingSelect);
	}
	else if (displayErrTextInvalidNum)
	{
		window->draw(errTextInvalidNum);
	}
	else if (displayErrTextSortingSelect)
	{
		errTextSortingSelect.setPosition({windowBounds.x/2 - errTextSortingSelect.getLocalBounds().width/2, barsText.getPosition().y + errTextSortingSelect.getLocalBounds().height + windowBounds.y/40});
		window->draw(errTextSortingSelect);
	}
}

/**
 * Initializes font
 *
 * @return  True if font initialized successfully, false if not 
 */
bool App::initFont()
{
	if (!font.loadFromFile("Fonts/arial_narrow_7.ttf"))
	{
		std::cout << "ERROR: Failed to load font!" << std::endl;
		return false;
	}

	return true;
}


/**
 * Initializes buttons
 */
void App::initButtons()
{
	const sf::Vector2f buttonSize = sf::Vector2f(windowBounds.x/12.8 + windowBounds.y/9.6, windowBounds.x/32 + windowBounds.y/24);
	const int textSize = windowBounds.x/106 + windowBounds.y/80;

	selectionSortButton->setFont(font);
	selectionSortButton->setTextSize(textSize);
	selectionSortButton->setButtonSize(buttonSize);
	selectionSortButton->setPosition(sf::Vector2f((BUTTON_SELECTION_SORT_NUM * (windowBounds.x * SORTING_BUTTON_X_POS)) - selectionSortButton->getBounds().width/2, windowBounds.y * SORTING_BUTTON_Y_POS));

	bubbleSortButton->setFont(font);
	bubbleSortButton->setTextSize(textSize);
	bubbleSortButton->setButtonSize(buttonSize);
	bubbleSortButton->setPosition(sf::Vector2f((BUTTON_BUBBLE_SORT_NUM * (windowBounds.x * SORTING_BUTTON_X_POS)) - bubbleSortButton->getBounds().width/2, windowBounds.y * SORTING_BUTTON_Y_POS));

	insertionSortButton->setFont(font);
	insertionSortButton->setTextSize(textSize);
	insertionSortButton->setButtonSize(buttonSize);
	insertionSortButton->setPosition(sf::Vector2f((BUTTON_INSERTION_SORT_NUM * (windowBounds.x * SORTING_BUTTON_X_POS)) - insertionSortButton->getBounds().width/2, windowBounds.y * SORTING_BUTTON_Y_POS));

	mergeSortButton->setFont(font);
	mergeSortButton->setTextSize(textSize);
	mergeSortButton->setButtonSize(buttonSize);
	mergeSortButton->setPosition(sf::Vector2f((BUTTON_MERGE_SORT_NUM * (windowBounds.x * SORTING_BUTTON_X_POS)) - mergeSortButton->getBounds().width/2, windowBounds.y * SORTING_BUTTON_Y_POS));

	quickSortButton->setFont(font);
	quickSortButton->setTextSize(textSize);
	quickSortButton->setButtonSize(buttonSize);
	quickSortButton->setPosition(sf::Vector2f((BUTTON_QUICK_SORT_NUM * (windowBounds.x * SORTING_BUTTON_X_POS)) - quickSortButton->getBounds().width/2, windowBounds.y * SORTING_BUTTON_Y_POS));

	startButton->setFont(font);
	startButton->setTextSize(textSize);
	startButton->setButtonSize(buttonSize);
	startButton->setPosition({(START_BUTTON_X_POS)*(windowBounds.x) - startButton->getBounds().width/2, (windowBounds.y*START_BUTTON_Y_POS) - startButton->getBounds().height/2});

	restartButton->setFont(font);
	restartButton->setTextSize(textSize);
	restartButton->setButtonSize(buttonSize);
	restartButton->setPosition({(RESTART_BUTTON_X_POS)*(windowBounds.x) - restartButton->getBounds().width/2, (windowBounds.y*RESTART_BUTTON_Y_POS) - restartButton->getBounds().height/2});
}

/**
 * Initializes textboxes and text
 */
void App::initText()
{
	std::stringstream strBuffer;
	const int textSize = windowBounds.x/106 + windowBounds.y/80;

	unsigned int upperLimit = (MAX_NUMBER_OF_BARS > static_cast<unsigned int>(windowBounds.x/2)) ? static_cast<unsigned int>(windowBounds.x/2) : MAX_NUMBER_OF_BARS;

	numberOfBarsTextbox->setFont(font);
	numberOfBarsTextbox->setPosition({windowBounds.x/2 - numberOfBarsTextbox->getBounds().width/2, windowBounds.y/2 - numberOfBarsTextbox->getBounds().height/2});
	numberOfBarsTextbox->setCharSize(textSize);
	numberOfBarsTextbox->setCharLimit(true, 5);

	barsText.setFont(font);
	barsText.setCharacterSize(textSize);
	barsText.setFillColor(sf::Color::White);
	barsText.setOutlineColor(sf::Color::White);
	
	strBuffer << "Enter number of bars (min: 5, max: " << upperLimit << "):  ";
	barsText.setString(strBuffer.str());
	strBuffer.str("");

	barsText.setPosition({windowBounds.x/2 - numberOfBarsTextbox->getBounds().width/2 - barsText.getLocalBounds().width, windowBounds.y/2 - numberOfBarsTextbox->getBounds().height/2});

	errTextInvalidNum.setFont(font);
	errTextInvalidNum.setCharacterSize(textSize);
	errTextInvalidNum.setFillColor(sf::Color::Red);
	errTextInvalidNum.setOutlineColor(sf::Color::Red);
	strBuffer << "Invalid number! Please enter a number between 5 and " << upperLimit; 
	errTextInvalidNum.setString(strBuffer.str());
	strBuffer.str("");

	errTextInvalidNum.setPosition({windowBounds.x/2 - errTextInvalidNum.getLocalBounds().width/2, barsText.getPosition().y + errTextInvalidNum.getLocalBounds().height + windowBounds.y/40});

	errTextSortingSelect.setFont(font);
	errTextSortingSelect.setCharacterSize(textSize);
	errTextSortingSelect.setFillColor(sf::Color::Red);
	errTextSortingSelect.setOutlineColor(sf::Color::Red);
	errTextSortingSelect.setString("No sorting algorithm selected!");

	errTextSortingSelect.setPosition({windowBounds.x/2 - errTextSortingSelect.getLocalBounds().width/2, barsText.getPosition().y + errTextInvalidNum.getLocalBounds().height + errTextSortingSelect.getLocalBounds().height + windowBounds.y/40});

	title.setFont(font);
	title.setCharacterSize(windowBounds.x/32 + windowBounds.y/24);
	title.setFillColor(sf::Color::Blue);
	title.setOutlineColor(sf::Color::Blue);
	title.setString("Sorting Visualizer");

	title.setPosition(sf::Vector2f(windowBounds.x/2 - title.getLocalBounds().width/2, windowBounds.y/160));
}

/**
 * Renders restart button for display on window
 */
void App::renderRestartButton(sf::RenderTarget& target)
{
	restartButton->draw(*window);
}

/**
 * Renders updates onto window
 */
void App::render()
{
	// Clear old frame
	window->clear(sf::Color(0, 0, 0, 255));

	switch (state)
	{
		case APP_MENU:
			// Draw menu
			renderMenu(*window);
			break;

		case APP_RESTART_ICON:
			// Draw bars and restart icon
			renderBars(*window);
			renderRestartButton(*window);
			break;

		case APP_SORTING:
			// Draw bars
			renderBars(*window);
			break;
	}

	// Update
	window->display();
}

/**
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
 * Gets window size
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
	static bool buttonPressed = false;

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
				break;

			case sf::Event::TextEntered:
				numberOfBarsTextbox->processTyping(event);
				break;

			case sf::Event::MouseMoved:
				mouseMovedEvent(buttonPressed);
				break;

			case sf::Event::MouseButtonPressed:
				mouseButtonPressedEvent(buttonPressed);
				break;
		}
	}
}

/**
 * Sets up sorting after start button is clicked
 *
 * @return  True if sorting was started successfully, false if not
 */
bool App::setupSorting()
{
	std::string text;
	bool invalidText = false;

	std::stringstream buffer;
	int val;

	text = numberOfBarsTextbox->getText();

	// Check if entry was a valid number
	for (unsigned int i = 0; i < text.length(); i++)
	{
		if (text[i] < ASCII_NUMBER_0 || text[i] > ASCII_NUMBER_9)
		{
			displayErrTextInvalidNum = true;
			invalidText = true;
			break;
		}
	}

	// Check if number is valid
	if (!invalidText)
	{
		buffer << text;
		buffer >> val;
		if (val < 5 || val > (windowBounds.x/2) || (val > MAX_NUMBER_OF_BARS))
		{
			displayErrTextInvalidNum = true;
			invalidText = true;
		}
		else
		{
			displayErrTextInvalidNum = false;
			numberOfBars = val;

			// Set framerate limit (sorting speed) based on number of bars
			unsigned int framerateLimit;
			unsigned int framerateLimitFromBars = numberOfBars/FRAMERATE_LIMIT_BAR_DIVISOR;

			if (FRAMERATE_LIMIT_MAX < framerateLimitFromBars)
			{
				framerateLimit = FRAMERATE_LIMIT_MAX;
			}
			else if (FRAMERATE_LIMIT_MIN > framerateLimitFromBars)
			{
				framerateLimit = FRAMERATE_LIMIT_MIN;
			}
			else
			{
				framerateLimit = framerateLimitFromBars;
			}

			window->setFramerateLimit(framerateLimit);
		}
	}

	// Set all buttons back to unclicked color if invalid number was not entered
	if (!displayErrTextInvalidNum)
	{
		bubbleSortButton->setButtonColor(unclickedColor);
		selectionSortButton->setButtonColor(unclickedColor);
		insertionSortButton->setButtonColor(unclickedColor);
		mergeSortButton->setButtonColor(unclickedColor);
		quickSortButton->setButtonColor(unclickedColor);
	}

	// Check if a sorting algorithm was selected
	if (sortingSelect == SORTING_NONE)
	{
		invalidText = true;
		displayErrTextSortingSelect = true;
	}
	else
	{
		displayErrTextSortingSelect = false;
	}

	// Clear textbox if invalid number was entered or if sorting was started successfully
	if ((displayErrTextInvalidNum && displayErrTextSortingSelect) || (!displayErrTextInvalidNum && !displayErrTextSortingSelect) || displayErrTextInvalidNum)
	{
		numberOfBarsTextbox->clear();
	}

	if (invalidText == true)
		return false;

	return true;
}

/**
 * Handles mouse moving events
 */
void App::mouseMovedEvent(bool isButtonPressed)
{
	switch (state)
	{
		case APP_MENU:
			if (selectionSortButton->isMouseOn(*window))
			{
				selectionSortButton->setButtonColor(hoverColor);
			}
			else
			{
				if (!isButtonPressed || sortingSelect != SORTING_SELECTION_SORT)
					selectionSortButton->setButtonColor(unclickedColor);
			}

			if (bubbleSortButton->isMouseOn(*window))
			{
				bubbleSortButton->setButtonColor(hoverColor);
			}
			else
			{
				if (!isButtonPressed || sortingSelect != SORTING_BUBBLE_SORT)
					bubbleSortButton->setButtonColor(unclickedColor);
			}

			if (insertionSortButton->isMouseOn(*window))
			{
				insertionSortButton->setButtonColor(hoverColor);
			}
			else
			{
				if (!isButtonPressed || sortingSelect != SORTING_INSERTION_SORT)
					insertionSortButton->setButtonColor(unclickedColor);
			}

			if (mergeSortButton->isMouseOn(*window))
			{
				mergeSortButton->setButtonColor(hoverColor);
			}
			else
			{
				if (!isButtonPressed || sortingSelect != SORTING_MERGE_SORT)
					mergeSortButton->setButtonColor(unclickedColor);
			}

			if (quickSortButton->isMouseOn(*window))
			{
				quickSortButton->setButtonColor(hoverColor);
			}
			else
			{
				if (!isButtonPressed || sortingSelect != SORTING_QUICK_SORT)
					quickSortButton->setButtonColor(unclickedColor);
			}

			if (startButton->isMouseOn(*window))
			{
				startButton->setButtonColor(hoverColor);
			}
			else
			{
				startButton->setButtonColor(unclickedColor);
			}
			break;

		case APP_RESTART_ICON:
			if (restartButton->isMouseOn(*window))
			{
				restartButton->setButtonColor(hoverColor);
			}
			else
			{
				restartButton->setButtonColor(unclickedColor);
			}
			break;
	}
}

/**
 * Handles mouse button pressing events
 */
void App::mouseButtonPressedEvent(bool &isButtonPressed)
{
	switch (state)
	{
		case APP_MENU:
			if (selectionSortButton->isMouseOn(*window))
			{
				isButtonPressed = true;
				selectionSortButton->setButtonColor(clickedColor);

				bubbleSortButton->setButtonColor(unclickedColor);
				insertionSortButton->setButtonColor(unclickedColor);
				mergeSortButton->setButtonColor(unclickedColor);
				quickSortButton->setButtonColor(unclickedColor);

				sortingSelect = SORTING_SELECTION_SORT;
			}

			else if (bubbleSortButton->isMouseOn(*window))
			{
				isButtonPressed = true;
				bubbleSortButton->setButtonColor(clickedColor);

				selectionSortButton->setButtonColor(unclickedColor);
				insertionSortButton->setButtonColor(unclickedColor);
				mergeSortButton->setButtonColor(unclickedColor);
				quickSortButton->setButtonColor(unclickedColor);

				sortingSelect = SORTING_BUBBLE_SORT;
			}

			else if (insertionSortButton->isMouseOn(*window))
			{
				isButtonPressed = true;
				insertionSortButton->setButtonColor(clickedColor);

				selectionSortButton->setButtonColor(unclickedColor);
				bubbleSortButton->setButtonColor(unclickedColor);
				mergeSortButton->setButtonColor(unclickedColor);
				quickSortButton->setButtonColor(unclickedColor);

				sortingSelect = SORTING_INSERTION_SORT;
			}

			else if (mergeSortButton->isMouseOn(*window))
			{
				isButtonPressed = true;
				mergeSortButton->setButtonColor(clickedColor);

				selectionSortButton->setButtonColor(unclickedColor);
				bubbleSortButton->setButtonColor(unclickedColor);
				insertionSortButton->setButtonColor(unclickedColor);
				quickSortButton->setButtonColor(unclickedColor);

				sortingSelect = SORTING_MERGE_SORT;
			}

			else if (quickSortButton->isMouseOn(*window))
			{
				isButtonPressed = true;
				quickSortButton->setButtonColor(clickedColor);

				selectionSortButton->setButtonColor(unclickedColor);
				bubbleSortButton->setButtonColor(unclickedColor);
				insertionSortButton->setButtonColor(unclickedColor);
				mergeSortButton->setButtonColor(unclickedColor);

				sortingSelect = SORTING_QUICK_SORT;
			}

			else if (startButton->isMouseOn(*window))
			{
				if (setupSorting())
				{
					startButton->setButtonColor(unclickedColor);
					state = APP_SORTING;
				}
			}
			break;

		case APP_RESTART_ICON:
			if (restartButton->isMouseOn(*window))
			{
				state = APP_MENU;
				restartButton->setButtonColor(unclickedColor);
			}
			break;
	}
	
}

/**
 * Initializes a new set of bars by generating their size/position and adding them to
 * a data structure
 */
void App::initBars()
{
	float barSize;
	unsigned int barCount = 0;
	float xPos, yPos;
	float barHeight;

	// Clear all bar vectors
	bars.clear();
	barHeights.clear();

	// Initialize Bars
	bar.setPosition(0.f, windowBounds.y);
	bar.setSize(sf::Vector2f(2.f, 500.f));
	bar.setFillColor(initialColor);
	bar.setOutlineColor(sf::Color::Black);
	bar.setOutlineThickness(1.f);

	// Calculate bar size
	barSize = windowBounds.x / static_cast<float>(numberOfBars); // Size of each bar = window width/# of total bars

	// Generate all bars
	while (bars.size() < numberOfBars)
	{
		// Generate a random height for the bar
		barHeight = static_cast<float>(rand() % static_cast<int>((windowBounds.y)));

		// Set bar size
		bar.setSize(sf::Vector2f(barSize, barHeight));

		// Generate bar position based on current bar count and position
		xPos = barSize * static_cast<float>(barCount);
		yPos = windowBounds.y - bar.getSize().y;

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
		sortFinished = false;
		initBars();
		render();
	}

	if (!sortFinished)
	{
		// Run sorting algorithm based on user selection
		switch (sortingSelect)
		{
			case SORTING_SELECTION_SORT: 
				if (selectionSort(bars, bars.size()))
					sortFinished = true;
				break;

			case SORTING_BUBBLE_SORT: 
				if (bubbleSort(bars, bars.size()))
					sortFinished = true;
				break;

			case SORTING_INSERTION_SORT: 
				if (insertionSort(bars, bars.size()))
					sortFinished = true;
				break;
				
			case SORTING_MERGE_SORT: 
				mergeSort(bars, 0, bars.size() - 1);
				sortFinished = true;
				break;

			case SORTING_QUICK_SORT: 
				quickSort(bars, 0, bars.size() - 1);
				sortFinished = true;
				break;

			default: 
				break;
		}
	}

	// Display restart button after sort has finished
	if (sortFinished)
	{
		// Restore framerate limit
		window->setFramerateLimit(FRAMERATE_LIMIT_NORMAL);
		state = APP_RESTART_ICON;
		sortingSelect = SORTING_NONE;
	}
}

/**
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

/**
 * Runs bubble sort (implemented as state machine to prevent blocking other tasks in the main loop)
 *
 * @param    A Vector that contains bars
 * @param    n Number of bars in vector
 *
 * @return   True if sort is finished, false if not
 */
bool App::bubbleSort(std::vector<sf::RectangleShape>& A, int n)
{
	bool retVal = false;
	static bubbleSortState bubbleState = BUBBLE_CHECK_CONDITION_OUTER; 
	static unsigned int bubbleSortOuterIndex = 1;
    static unsigned int bubbleSortInnerIndex = 0;
    static bool hasSwapOccurred;

	switch (bubbleState)
	{
		case BUBBLE_CHECK_CONDITION_OUTER:
			if (bubbleSortOuterIndex < n - 1)
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
			bubbleSortInnerIndex = 0;
			bubbleState = BUBBLE_CHECK_CONDITION_OUTER;
			retVal = true;
			break;
	}

	return retVal;
}

/**
 * Runs selection sort (implemented as state machine to prevent blocking other tasks in the main loop)
 *
 * @param  A Vector that contains bars
 * @param  n Number of bars in vector
 *
 * @return   True if sort is finished, false if not
 */
bool App::selectionSort(std::vector<sf::RectangleShape>& A, int n)
{
	bool retVal = false;
	static selectionSortState selectionState = SELECTION_CHECK_CONDITION_OUTER;
	static unsigned int selectionSortOuterIndex = 0;
	static unsigned int selectionSortInnerIndex = 0;
	static unsigned int innerIndexMin = 0;

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
			selectionState = SELECTION_CHECK_CONDITION_OUTER;
			retVal = true;
			break;
	}

	return retVal;
}

/**
 * Runs insertion sort (implemented as state machine to prevent blocking other tasks in the main loop)
 *
 * @param  A Vector that contains bars
 * @param  n Number of bars in vector
 *
 * @return   True if sort is finished, false if not
 */
bool App::insertionSort(std::vector<sf::RectangleShape>& A, int n)
{
	bool retVal = false;

	static insertionSortState insertionState = INSERTION_CHECK_CONDITION_OUTER;
	static unsigned int insertionSortOuterIndex = 1;
	static unsigned int insertionSortInnerIndex = 0;

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
			insertionState = INSERTION_CHECK_CONDITION_OUTER;
			retVal = true;
			break;
	}

	return retVal;
}

/**
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

/**
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
		pollEvents();
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
		pollEvents();
		bars[startLeft + j].setFillColor(initialColor);
		barHeights[barIndex] = left[j].getSize().y;
		j++;
		render();
		barIndex++;
	}
	while (k < nRight)
	{
		pollEvents();
		bars[startRight + k].setFillColor(initialColor);
		barHeights[barIndex] = right[k].getSize().y;
		k++;
		render();
		barIndex++;
	}

	// Render changes
	renderMergeSort(*window, A, startLeft, endRight);
}

/**
 * Renders merging of left and right vectors
 *
 * @param A           Vector that contains bars
 * @param startLeft   First index of left vector
 * @param endRight    Final index of right vector
 */
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
		bars[i].setPosition(bars[i].getPosition().x, windowBounds.y-bars[i].getSize().y);

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

/**
 * Runs quick sort
 *
 * @param A      Vector that contains bars
 * @param start  First index in vector
 * @param end    Final index in vector
 */
void App::quickSort(std::vector<sf::RectangleShape>& A, int start, int end)
{
	int partitionIndex;

	// Poll events
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
 * Partitions the bar vector (used in quick sort)
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
		// Poll events
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