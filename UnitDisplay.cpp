#include "UnitDisplay.h"
#include <iostream>
#include <string>
#include "Territorial.h"

/*
	Constructors
*/

UnitDisplay::UnitDisplay()
: font(Territorial::mainFont){

	initialise();
}


/*
	Initialisation functions
*/
void UnitDisplay::initialise() {
	float radius = 100.f;

	//Set circle
	this->circle = sf::CircleShape(radius);
	this->circle.setOrigin(sf::Vector2f(radius, radius));
	setColour(sf::Color(125,125,125)); //Default colour when game loads

	//Set text
	this->text = sf::Text("0", font, radius);
	this->text.setFillColor(sf::Color::Black);
}


/*
	Overrides
*/
void UnitDisplay::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	target.draw(circle);
	target.draw(text);
}


/* Other functions */
void UnitDisplay::setPosition(sf::Vector2f pos) {
	this->circle.setPosition(pos);

	/* Centrally align text in circle */
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin((bounds.left + bounds.width) / 2, (bounds.top + bounds.height) / 2);
	text.setPosition(pos);
}