#include "Button.h"

// Constructors / Destructors
Button::Button(int textSize, std::string buttonText, sf::Vector2f buttonSize, sf::Color buttonColor, sf::Color textColor)
{
	text.setFillColor(textColor);
	text.setOutlineColor(textColor);
	text.setString(buttonText);
	text.setCharacterSize(textSize);

	button.setFillColor(buttonColor);
	button.setSize(buttonSize);
}

/**
* Sets the font for the button text
*
* @param font  The font to set for button text
*/
void Button::setFont(sf::Font &font)
{
	text.setFont(font);
}

/**
* Draws button on a window
*
* @param window  The window to draw the button onto
*/
void Button::draw(sf::RenderWindow &window)
{
	window.draw(button);
	window.draw(text);
}

/**
* Checks if mouse is on button
*
* @return True if mouse is on the the button, false if not
*/
bool Button::isMouseOn(sf::RenderWindow &window)
{
	// Get mouse x and y position
	float xPosMouse = sf::Mouse::getPosition(window).x;
	float yPosMouse = sf::Mouse::getPosition(window).y;

	// Get button x and y position
	float xPosButton = button.getPosition().x;
	float yPosButton = button.getPosition().y;

	// Get button width and height
	float buttonWidth = button.getPosition().x + button.getLocalBounds().width;
	float buttonHeight = button.getPosition().y + button.getLocalBounds().height;

	// Check if mouse is within bounds of button
	if (yPosMouse < buttonHeight && yPosMouse > yPosButton && xPosMouse < buttonWidth && xPosMouse > xPosButton)
		return true;

	return false;
}

/**
* Sets color of text on button
*/
void Button::setTextColor(sf::Color color)
{
	text.setFillColor(color);
	text.setOutlineColor(color);
}

/**
* Gets the bounds of the button
*
* @return Rectangle bounds of button
*/
sf::FloatRect Button::getBounds()
{
	return button.getLocalBounds();
}

/**
* Sets the color of the button
*/
void Button::setButtonColor(sf::Color color)
{
	button.setFillColor(color);
}

/**
* Sets the size of the text in the button
*/
void Button::setTextSize(int textSize)
{
	text.setCharacterSize(textSize);
}

/**
* Sets the size of the button
*/
void Button::setButtonSize(sf::Vector2f buttonSize)
{
	button.setSize(buttonSize);
}

/**
* Sets the psoition of the button
*/
void Button::setPosition(sf::Vector2f pos)
{
	button.setPosition(pos);

	// Calculate position of text relative to the button
	float x = (pos.x + button.getLocalBounds().width / 2) - (text.getLocalBounds().width / 2);
	float y = (pos.y + button.getLocalBounds().height / 2) - (text.getLocalBounds().height / 2);

	text.setPosition({x,y});
}

