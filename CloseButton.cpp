#include "stdafx.h"
#include "CloseButton.h"

/* Constructor -- Destructor */
CloseButton::CloseButton(float size, sf::Vector2f position)
:size(size){
	
	//background.setSize(sf::Vector2f(size, size));
	//background.setPosition(position);
	initialise(size, position);
}

CloseButton::~CloseButton() {

}


/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/* Initialisation */
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

void CloseButton::initialise(float size, sf::Vector2f position) {

	background.setSize(sf::Vector2f(size, size));
	background.setPosition(position);
	cross.setOverallWidth(size - (crossOffset * 2));
	sf::Vector2f offset(background.getSize().x / 2, background.getSize().y / 2);
	cross.setPosition(position + offset);
	cross.setShapeThickness(2);

	background.setFillColor(sf::Color::Black);	//For now
	cross.setColour(sf::Color::White);
}

void CloseButton::reset() {
	
}



/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/* Setters */
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

void CloseButton::setSize(float width) {
	
	background.setSize(sf::Vector2f(width, width));
	cross.setOverallWidth(width - crossOffset);
}


void CloseButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	target.draw(background);
	target.draw(cross);
}

void CloseButton::setPosition(sf::Vector2f position) {

	background.setPosition(position);
	sf::Vector2f offset(background.getSize().x / 2, background.getSize().y / 2);
	cross.setPosition(position + offset);
}

void CloseButton::setForegroundColour(sf::Color colour) {

	cross.setColour(colour);
}

void CloseButton::setBackgroundColour(sf::Color colour) {

	background.setFillColor(colour);
}