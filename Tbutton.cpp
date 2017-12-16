#include "stdafx.h"
#include "Tbutton.h"

#include <exception>
#include <iostream>

/*
	Constructors -- Destructor
*/

/*!
*	\brief Default constructor
*	\param size
*	\parblock
*		is used to set the size of the rectangle base (inherently, the size of the button)
*		with a default value of (0,0)
*/
Tbutton::Tbutton(sf::Vector2f size) {

	initialiseButton(size);
}


/*!
*	\brief Constructor allows user to set font and size
*	\param font
*	\parblock
*		is the font that will be used for the button's text. Passed by reference
*
*	\param size
*	\parblock
*		is used to set the size of the rectangle base (inherently, the size of the button)
*		with a default value of (0,0)
*/
Tbutton::Tbutton(sf::Font& font, sf::Vector2f size)
	: font(&font) {

	initialiseText();
	initialiseButton(size);

	isFontSet = true;
	drawText();
}


/*!
*	\brief Constructor allows user to set font and size
*	\param fileLocation
*	\parblock
*		the font is attempted to be loaded from this location
*
*	\param size
*	\parblock
*		is used to set the size of the rectangle base (inherently, the size of the button)
*		with a default value of (0,0)
*/
Tbutton::Tbutton(std::string fileLocation, sf::Vector2f size) {

	if (loadFontFromFile(fileLocation))
		initialiseText();

	initialiseButton(size);
	drawText();
}

Tbutton::~Tbutton() {
	
}




/*
	Initialise methods
*/

void Tbutton::initialiseText() {

	buttonText.setFont(*font);
	setText();
	//buttonText.setColor(sf::Color::White);
	drawText();
	
}

void Tbutton::initialiseButton(sf::Vector2f size) {

	button = sf::RectangleShape(size);
	backgroundColour = sf::Color::Black;
	foregroundColour = sf::Color::White;
	focusBackgroundColour = sf::Color::White;
	focusForegroundColour = sf::Color::Black;
	
	focusColour(); /* Set button initial colour */

}




/*
	Override methods
*/

/*!
*	\brief Required as class extends sf::Drawable, to allow the object to be drawn to RenderTarget
*/
void Tbutton::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	target.draw(button);

	if(drawTextFlag)
		target.draw(buttonText);
}


void Tbutton::setFont(sf::Font& font) {

	this->font = &font;	/* Reference to pointer */
	initialiseText();
}

bool Tbutton::loadFontFromFile(std::string fileLocation) {

	try {
		if (!font->loadFromFile(fileLocation))
			throw std::runtime_error("Failed to locate \"" + fileLocation + "\"");
		isFontSet = true;
		initialiseText();
	}
	catch (std::runtime_error e) {
		std::cerr << e.what() << std::endl;
	}
}



/*
	Public text methods
*/
void Tbutton::setText(std::string string) {
	
	buttonText.setString(string);
	drawText();
}

void Tbutton::setTextSize(int size) {

	buttonText.setCharacterSize(size);
	drawText();
}

void Tbutton::setForegroundColour(sf::Color colour) {

	foregroundColour = colour;

	if (!isInFocus)
		buttonText.setColor(foregroundColour);
}

void Tbutton::setFocusForegroundColour(sf::Color colour) {

	focusForegroundColour = colour;

	if (isInFocus)
		buttonText.setColor(focusForegroundColour);
}



/*
	Private methods
*/

bool Tbutton::drawText() {

	/**
	/
	if (!isFontSet)
		return false;
	/**/
	//If text is bigger than box - don't draw
	
	if ((buttonText.getLocalBounds().width + buttonText.getLocalBounds().left) > button.getSize().x) {
		drawTextFlag = false;
		return false;
	}
	if ((buttonText.getLocalBounds().height + buttonText.getLocalBounds().top) > button.getSize().y){
		drawTextFlag = false;
		return false;
	}

	/**
	/
	if ((buttonText.getLocalBounds().width) > button.getSize().x) {// + buttonText.getLocalBounds().left > button.getSize().x)
		std::cout << "false" << std::endl;
		return false;
	}
	if (buttonText.getLocalBounds().height > button.getSize().y) {// + buttonText.getLocalBounds().top > button.getSize().y)
		std::cout << "false" << std::endl;
		return false;
	}
	/**/

	sf::FloatRect textSize = buttonText.getLocalBounds();

	buttonText.setOrigin(textSize.left + textSize.width / 2,	/* Set origin as centre */
							textSize.top + textSize.height / 2);

	buttonText.setPosition((button.getPosition().x - button.getOrigin().x) + button.getSize().x / 2,
							(button.getPosition().y - button.getOrigin().y) + button.getSize().y / 2);

	drawTextFlag = true;
	return true;

}


/*
	Rectangle methods
*/
 //Setters
void Tbutton::setSize(sf::Vector2f size) {

	button.setSize(size);
	drawText();
}

void Tbutton::setBackgroundColour(sf::Color colour) {

	backgroundColour = colour;

	if(!isInFocus)
		button.setFillColor(backgroundColour);
}

void Tbutton::setPosition(sf::Vector2f position) {

	button.setPosition(position);
	drawText();
}

void Tbutton::setOrigin(sf::Vector2f origin) {

	button.setOrigin(origin);
	drawText();
}


void Tbutton::setFocusBackgroundColour(sf::Color colour) {

	focusBackgroundColour = colour;

	if (isInFocus)
		button.setFillColor(focusBackgroundColour);
}




//Getters
sf::Vector2f Tbutton::getSize() {

	return button.getSize();
}

sf::Vector2f Tbutton::getPosition() {

	return button.getPosition();
}

sf::FloatRect Tbutton::getGlobalBounds() {
	return button.getGlobalBounds();
}

sf::Color Tbutton::getBackgroundColour() {

	return button.getFillColor();
}

sf::Color Tbutton::getForegroundColour() {

	return buttonText.getColor();
}

sf::Color Tbutton::getFocusBackgroundColour() {

	return focusBackgroundColour;
}

sf::Color Tbutton::getFocusForegroundColour() {

	return focusForegroundColour;
}

//Protected getters
sf::RectangleShape* Tbutton::getButton() {

	return &button;
}

/**
/
sf::Text* Tbutton::getText() {

	return &buttonText;
}/**/

const sf::RectangleShape& Tbutton::getConstButton() const {

	return button;
}

const sf::Text& Tbutton::getConstText() const {

	return buttonText;
}


/*
	Infocus - Feedback that button is selected
*/

void Tbutton::setInFocus(bool focus) {

	isInFocus = focus;
	focusColour();
	
}

void Tbutton::focusColour() {

	if (isInFocus) {
		button.setFillColor(focusBackgroundColour);
		buttonText.setColor(focusForegroundColour);
	}
	else {
		button.setFillColor(backgroundColour);
		buttonText.setColor(foregroundColour);
	}

}
