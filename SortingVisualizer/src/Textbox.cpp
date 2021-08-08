#include "Textbox.h"

// Constructors / Destructors
Textbox::Textbox(int charSize, sf::Color charColor, bool selected)
{
	textArea.setCharacterSize(charSize);
	textArea.setFillColor(charColor);
	textArea.setOutlineColor(charColor);
	isSelected = selected;

	if (selected)
		textArea.setString("_");
	else
		textArea.setString("");

	charLim = 0;
}

Textbox::~Textbox()
{
}

/**
 * Sets character size of the text box
 */
void Textbox::setCharSize(int charSize)
{
	textArea.setCharacterSize(charSize);
}

/**
 * Adds an inputted character to the textbox
 */
void Textbox::inputText(int inputChar)
{
	// Remove last character if backspace was entered
	if (inputChar == BACKSPACE_KEY)
	{
		if (textBuf.str().length() > 0)
		{
			eraseLastChar();
		}
	}
	else if (inputChar != ENTER_KEY)
	{
		textBuf << static_cast<char>(inputChar);
	}

	if (textBuf.str().length() < charLim)
	{
		textArea.setString(textBuf.str() + "_");
	}
	else
	{
		textArea.setString(textBuf.str());
	}
}

/**
 * Gets the bounds of the textbox
 *
 * @return Rectangle bounds of textbox
 */
sf::FloatRect Textbox::getBounds()
{
	return textArea.getLocalBounds();
}

/**
* Erases the last character in the textbox
*/
void Textbox::eraseLastChar()
{
	// Create new substring does not include the last character
	std::string newTextBuf = textBuf.str().substr(0, textBuf.str().length() - 1);

	// Clear text buffer
	textBuf.str("");

	// Add new substring to text buffer
	textBuf << newTextBuf;

	// Update text area
	textArea.setString(textBuf.str());
}

/**
 * Sets character limit for textbox
 *
 * @param hasLim  True if textbox will have a limit, false if not 
 * @param lim     Character limit for textbox (not used if hasLim is false)
 */
void Textbox::setCharLimit(bool hasLim, unsigned int lim)
{
	hasCharLim = hasLim;

	if (hasLim)
	{
		charLim = lim;
	}
}

/**
 * Sets if textbox appears as selected (underscore to indicate ready for user input)
 */
void Textbox::setSelected(bool sel)
{
	isSelected = sel;
	if (!sel)
	{
		// Create new substring does not include last character
		std::string newTextBuf = textBuf.str().substr(0, textBuf.str().length());

		// Clear text buffer
		textBuf.str("");

		// Add new substring to text buffer
		textBuf << newTextBuf;

		// Update text area
		textArea.setString(textBuf.str());
	}
}

/**
 * Gets the text in the textbox
 *
 * @return The text in the textbox
 */
std::string Textbox::getText()
{
	return textBuf.str();
}

/**
* Draws textbox onto the window
*
* @param window  The window to draw the textbox onto
*/
void Textbox::draw(sf::RenderWindow &window)
{
	window.draw(textArea);
}

/**
 * Sets the position of the textbox
 *
 * @param pos  The position to set the textbox to
 */
void Textbox::setPosition(sf::Vector2f pos)
{
	textArea.setPosition(pos);
}

/**
* Sets the font of the text in the textbox
*
* @param font  The font to set text in the textbox to
*/
void Textbox::setFont(sf::Font &font)
{
	textArea.setFont(font);
}

/**
 * Logic that decides whether a character is inputted to the textbox
 *
 * @param input  Inputted key event
 */
void Textbox::processTyping(sf::Event input)
{
	if (isSelected)
	{
		// Get the character code
		int inputChar = input.text.unicode;
		if (inputChar <= MAX_ASCII_VALUE)
		{
			if (hasCharLim)
			{
				if ((textBuf.str().length() < charLim) || ((textBuf.str().length() == charLim) && (inputChar == BACKSPACE_KEY)))
				{
					inputText(inputChar);
				}
			}
			else
			{
				inputText(inputChar);
			}
		}
	}
}

/**
 * Clears the textbox of all text
 */ 
void Textbox::clear()
{
	textBuf.str("");

	if (isSelected)
	{
		textArea.setString(textBuf.str() + "_");
	}
	else
	{
		textArea.setString(textBuf.str());
	}
	
}