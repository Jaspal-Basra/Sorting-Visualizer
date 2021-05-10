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

	// Game logic
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "Sorting Visualizer", sf::Style::Titlebar | sf::Style::Close);

	windowBounds = this->window->getSize(); // Get window size for later use

	this->window->setFramerateLimit(60);
}

void Game::initBars()
{
	this->bar.setPosition(0.f, windowBounds.y);
	this->bar.setSize(sf::Vector2f(2.f, 300.f));
	this->bar.setFillColor(sf::Color::Cyan);
	this->bar.setOutlineColor(sf::Color::Black);
	this->bar.setOutlineThickness(1.f);

	this->numberOfBars = 100;
	this->barSize = windowBounds.x / static_cast<float>(numberOfBars); // Size of each bar = window width/# of total bars
	this->barCount = 0;
}

void Game::insertionSort(std::vector<sf::RectangleShape>& A, int n)
{
	float val;
	int hole;

	for (int i = 1; i < n; i++)
	{
		val = A[i].getSize().y;
		hole = i;

		while (hole > 0 && A[hole-1].getSize().y > val)
		{
			A[hole] = A[hole-1];
			hole--;
		}
		A[hole].setSize(sf::Vector2f(A[hole].getSize().x, val));
	}
}

void Game::bubbleSort(std::vector<sf::RectangleShape>& A, int n)
{
	int hasSwapOccurred = false;
	for (int k = 1; k < n-1; k++)
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

void Game::swap(std::vector<sf::RectangleShape>& A, int a, int b)
{
	sf::RectangleShape temp = A[a];
	A[a] = A[b];
	A[b] = temp;
}

// Public Methods

void Game::update()
{
	this->pollEvents();

	// Update bars
	this->updateBars();
}

void Game::updateBars()
{
	float xPos, yPos;

	// Adds bars
	while (this->bars.size() < this->numberOfBars)
	{
		this->spawnBar();
	}

	//bubbleSort(bars, bars.size());
	insertionSort(bars, bars.size());

	for (int i = 0; i < bars.size(); i++)
	{
		xPos = barSize * static_cast<float>(i);
		yPos = windowBounds.y;
		this->bars[i].setPosition(
			xPos,
			yPos - bars[i].getSize().y
		);
	}
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

void Game::renderBars(sf::RenderTarget& target)
{
	// Rendering all the enemies
	for (int i = 0; i < bars.size(); i++)
	{
		target.draw(bars[i]);
	}
}

void Game::spawnBar()
{
	float xPos = barSize*static_cast<float>(barCount);
	float yPos = windowBounds.y;

	// Generate a random height for the bar
	float barHeight = static_cast<float>(rand() % static_cast<int>((this->window->getSize().y)));

	this->bar.setSize(sf::Vector2f(this->barSize, barHeight));

	this->bar.setPosition(
		xPos,
		yPos - bar.getSize().y
	);

	// Spawn the enemy
	this->bars.push_back(this->bar);
	this->barCount += 1;
}

const bool Game::isWindowOpen() const
{
	return this->window->isOpen();
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
