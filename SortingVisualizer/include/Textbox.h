#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>

#define BACKSPACE_KEY 8
#define ENTER_KEY 13

#define MAX_ASCII_VALUE 127

class Textbox
{
public:
	// Constructors / Destructors
	Textbox() { }
    Textbox(int charSize, sf::Color charColor, bool selected);
    virtual ~Textbox();

    std::string getText();

    void draw(sf::RenderWindow &window);
    void setPosition(sf::Vector2f pos);
    void setFont(sf::Font &font);
    void setCharLimit(bool hasLim, unsigned int lim = 0);
    void setSelected(bool sel);
    void setCharSize(int charSize);
    void processTyping(sf::Event input);
    void clear();
    sf::FloatRect getBounds();
    
private:
	sf::Text textArea;
	std::ostringstream textBuf;
	unsigned int charLim;
	bool hasCharLim = false;
	bool isSelected = false;

	void inputText(int inputChar);
	void eraseLastChar();
};

