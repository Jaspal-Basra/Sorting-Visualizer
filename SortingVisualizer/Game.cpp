#include "Game.h"

// Constructors / Destructors
Game::Game()
{
	this->initializeVariables();
	this->initWindow();
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

void Game::updateBars()
{
	bar.update();
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
	bar.render(target);
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
