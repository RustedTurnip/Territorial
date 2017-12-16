#include "stdafx.h"
#include "CornerShape.h"
#include <iostream>


/*
	Constructor -- Destructor
*/

CornerShape::CornerShape(Rotation rotation) 
	: rotation(rotation) {

	horizontal = sf::RectangleShape(sf::Vector2f(100,100));
	defaultConfig();

}

CornerShape::CornerShape(int size, int thickness, Rotation rotation)
	: rotation(rotation) {

	setColour(sf::Color::Red);
	setSize(size);
	setThickness(thickness);
}

CornerShape::~CornerShape() {

}


/*
	Private other methods
*/

void CornerShape::defaultConfig() {

	setColour(sf::Color::Black);
	setThickness(5);
	setSize(25);
}


void CornerShape::setOrigin() {	//Needs to be called every time a size operation takes place

	switch (rotation) {

	case TopLeft :
		horizontal.setOrigin(sf::Vector2f(0, 0));
		vertical.setOrigin(sf::Vector2f(0, 0));
		break;

	case TopRight :
		horizontal.setOrigin(sf::Vector2f(horizontal.getSize().x, 0));
		vertical.setOrigin(sf::Vector2f(vertical.getSize().x, 0));
		break;

	case BottomLeft :
		horizontal.setOrigin(sf::Vector2f(0, horizontal.getSize().y));
		vertical.setOrigin(sf::Vector2f(0, vertical.getSize().y));
		break;

	case BottomRight :
		horizontal.setOrigin(sf::Vector2f(horizontal.getSize().x, horizontal.getSize().y));
		vertical.setOrigin(sf::Vector2f(vertical.getSize().x, vertical.getSize().y));
		break;
	}
}


void CornerShape::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	target.draw(horizontal);
	target.draw(vertical);
}


/*
	Public other methods
*/

//Setters

void CornerShape::setRotation(Rotation rotation) {

	this->rotation = rotation;
	setOrigin();
	
}

void CornerShape::setPosition(sf::Vector2f position) {

	horizontal.setPosition(position);
	vertical.setPosition(position);
}

void CornerShape::setColour(sf::Color colour) {

	horizontal.setFillColor(colour);
	vertical.setFillColor(colour);
}



void CornerShape::setThickness(int thickness) {

	//Length stays the same - thickness doesn't
	float horWidth = horizontal.getSize().x;
	float verHeight = vertical.getSize().y;

	horizontal.setSize(sf::Vector2f(horWidth, thickness));
	vertical.setSize(sf::Vector2f(thickness, verHeight));
	

	//Realign origin
	setOrigin();
}



void CornerShape::setSize(int size) {

	//Thickness stays the same - length doesn't
	float horHeight = horizontal.getSize().y;
	float verWidth = vertical.getSize().x;

	horizontal.setSize(sf::Vector2f(size, horHeight));
	vertical.setSize(sf::Vector2f(verWidth, size));


	//Realign origin
	setOrigin();

}


//Getters

sf::Vector2f CornerShape::getPosition() {

	return horizontal.getPosition();	//Could have just as easily returned verticle
										//Returns position in relation to origin
}



/*
	Overrides - sort of
*/

void CornerShape::move(const sf::Vector2f& offset) {

	horizontal.move(offset);
	vertical.move(offset);
}