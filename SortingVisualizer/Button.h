#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Button
{
public:
	// Constructors / Destructors
	Button() { }
	Button(int textSize, std::string buttonText, sf::Vector2f buttonSize, sf::Color buttonColor, sf::Color textColor);

	void setButtonColor(sf::Color color);
	void setPosition(sf::Vector2f pos);
	void setTextSize(int textSize);
	void setButtonSize(sf::Vector2f buttonSize);
	void setFont(sf::Font &font);
	void draw(sf::RenderWindow &window);
	bool isMouseOn(sf::RenderWindow &window);
	void setTextColor(sf::Color color);
	sf::FloatRect getBounds();

private:
	sf::RectangleShape button;
	sf::Text text;
};

