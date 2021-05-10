#include "Bar.h"

void Bar::initializeVariables()
{
	std::cout << "Enter number of bars: ";
	std::cin >> numberOfBars;
	//this->numberOfBars = NUMBER_OF_BARS;
	this->barSize = WINDOW_WIDTH / static_cast<float>(numberOfBars); // Size of each bar = window width/# of total bars
	this->barCount = 0;
}

/**
* Initializes bars
*/
void Bar::initBars()
{
	float xPos, yPos;

	// Initialize Bars
	this->bar.setPosition(0.f, WINDOW_HEIGHT);
	this->bar.setSize(sf::Vector2f(2.f, 300.f));
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

Bar::Bar()
{
	this->initializeVariables();
	this->initBars();
}

Bar::~Bar()
{
}

void Bar::update()
{
	this->updateBars();
}

void Bar::updateBars()
{
	float xPos, yPos;

	char c;
	std::cout << "Select a sorting algorithm from the following:\nSelection Sort (S)\nBubble Sort (B)\nInsertion Sort (I)\nMerge Sort (M)\nEnter here: ";
	std::cin >> c;

	switch (c)
	{
	case 'S': sorting.selectionSort(bars, bars.size()); break;
	case 'B': sorting.bubbleSort(bars, bars.size()); break;
	case 'I': sorting.insertionSort(bars, bars.size()); break;
	case 'M': sorting.mergeSort(bars, bars.size()); break;
	case 'Q': sorting.quickSort(bars, 0, bars.size() - 1); break;
	default: std::cout << "Invalid sorting algorithm selected." << std::endl; break;
	}

	// Update positions of all bars after sort
	for (int i = 0; i < bars.size(); i++)
	{
		xPos = barSize * static_cast<float>(i);
		yPos = WINDOW_HEIGHT - bars[i].getSize().y;
		this->bars[i].setPosition(xPos, yPos);
	}
}

/**
* Renders game objects for display on winow
*/
void Bar::render(sf::RenderTarget& target)
{
	this->renderBars(target);
}

/*
* Renders bars for display on window
*/
void Bar::renderBars(sf::RenderTarget& target)
{
	// Rendering all the bars
	for (int i = 0; i < bars.size(); i++)
	{
		target.draw(bars[i]);
	}
}
