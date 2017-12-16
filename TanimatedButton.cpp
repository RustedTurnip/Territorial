#include "TanimatedButton.h"

#include <thread>
#include <chrono>

float TanimatedButton::animationSpeed = 50.f;
sf::Time TanimatedButton::timePerFrame = sf::seconds(1.f / 60.f);

/*
	Constructor -- Destructor
*/

TanimatedButton::TanimatedButton(sf::Vector2f size)
	: Tbutton(size) {

	initialiseCorners(25, 5);	//Manual default
}

TanimatedButton::TanimatedButton(sf::Font& font, sf::Vector2f size)
	: Tbutton(font, size){

	initialiseCorners(25, 5);	//Manual default
}

TanimatedButton::TanimatedButton(std::string fileLocation, sf::Vector2f size)
	: Tbutton(fileLocation, size) {

	initialiseCorners(25, 5);	//Manual default
}

TanimatedButton::~TanimatedButton() {

}




/*
	Other methods
*/

void TanimatedButton::initialiseCorners(int size, int thickness) {

	/* Set up corners */
	corners[0] = CornerShape(size, thickness, CornerShape::TopLeft);
	corners[1] = CornerShape(size, thickness, CornerShape::TopRight);
	corners[2] = CornerShape(size, thickness, CornerShape::BottomLeft);
	corners[3] = CornerShape(size, thickness, CornerShape::BottomRight);

	for (int i = 0; i < corners.size(); i++) {
		corners[i].setColour(this->getBackgroundColour());
	}

	setCornerPositions();
}

void TanimatedButton::setCornerPositions() {	/* Needs to be called every time the button is moved */
												//So will need to override all move and size methods

	sf::FloatRect buttonPosition = this->getButton()->getGlobalBounds();


	//Top left
	corners[0].setPosition(sf::Vector2f(buttonPosition.left, buttonPosition.top));
	//Top right
	corners[1].setPosition(sf::Vector2f(buttonPosition.left + buttonPosition.width, buttonPosition.top));
	//Bottom left
	corners[2].setPosition(sf::Vector2f(buttonPosition.left, buttonPosition.top + buttonPosition.height));
	//Bottom right
	corners[3].setPosition(sf::Vector2f(buttonPosition.left + buttonPosition.width,
											buttonPosition.top + buttonPosition.height));

}

/*
	Overrides from Tbutton
*/

void TanimatedButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	for (int i = 0; i < corners.size(); i++) {
		target.draw(corners[i]);
	}
	target.draw(getConstButton());

	if (drawTextFlag)
		target.draw(getConstText());
}

void TanimatedButton::setSize(sf::Vector2f size) {
	
	this->getButton()->setSize(size);
	drawText();

	setCornerPositions();
}


void TanimatedButton::setPosition(sf::Vector2f position) {

	this->getButton()->setPosition(position);
	drawText();

	setCornerPositions();
}

void TanimatedButton::setBackgroundColour(sf::Color colour) {

	Tbutton::setBackgroundColour(colour);

	for (int i = 0; i < corners.size(); i++) {
		corners[i].setColour(colour);
	}
}

void TanimatedButton::setCornerThickness(int thickness) {
	for (int i = 0; i < corners.size(); i++)
		corners[i].setThickness(thickness);
}

void TanimatedButton::setCornerSize(int size) {
	for (int i = 0; i < corners.size(); i++)
		corners[i].setSize(size);
}





/*
	Animation methods
*/

void TanimatedButton::calculateOpenDirection(sf::Time deltaTime) {	//Method is responsible for working out where to move the corner

	for (int i = 0; i < 4; i++) {	//For each corner

		sf::Vector2f movement(0.f, 0.f);

			//Move which way? All diagonals
			switch (i) {
			case 0: {
				movement.x -= animationSpeed;
				movement.y -= animationSpeed;
				break; }

			case 1: {
				movement.x += animationSpeed;
				movement.y -= animationSpeed;
				break; }

			case 2: {
				movement.x -= animationSpeed;
				movement.y += animationSpeed;
				break; }

			case 3: {
				movement.x += animationSpeed;
				movement.y += animationSpeed;
				break; }
			}

			//Move corner  --  Distance = Speed * Time
			corners[i].move(movement * deltaTime.asSeconds());
	}

}


void TanimatedButton::calculateCloseDirection(sf::Time deltaTime) {

	for (int i = 0; i < 4; i++) {	//For each corner

		sf::Vector2f movement(0.f, 0.f);

		//Move which way? All diagonals
		switch (i) {
		case 0: {
			movement.x += animationSpeed;
			movement.y += animationSpeed;
			break; }

		case 1: {
			movement.x -= animationSpeed;
			movement.y += animationSpeed;
			break; }

		case 2: {
			movement.x += animationSpeed;
			movement.y -= animationSpeed;
			break; }

		case 3: {
			movement.x -= animationSpeed;
			movement.y -= animationSpeed;
			break; }
		}

		//Move corner  --  Distance = Speed * Time
		corners[i].move(movement * deltaTime.asSeconds());
	}

}


void TanimatedButton::openAnimation() {

	//Smooth running stuff
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	//Bottom right of button
	sf::Vector2f startPosition(getButton()->getGlobalBounds().left,	getButton()->getGlobalBounds().top);
	//Position for corner to reach
	sf::Vector2f finalPosition(startPosition.x - animationDistance, startPosition.y -  animationDistance);


	/* Set new background & foreground colour */
	focusColour();

	while (corners[0].getPosition().y > finalPosition.y && isInFocus) {		//While not fully open

		timeSinceLastUpdate += clock.restart();
		//getButton()->setFillColor(getFocusBackgroundColour());

		while (timeSinceLastUpdate > timePerFrame) {

			timeSinceLastUpdate -= timePerFrame;
			calculateOpenDirection(timePerFrame);

		} 
	}

}


void TanimatedButton::closeAnimation() {

	//Smooth running stuff
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	//Position for corner to reach - the top left of button rectangle
	sf::Vector2f finalPosition(getButton()->getGlobalBounds().left,
									getButton()->getGlobalBounds().top);


	/* Set new background & foreground colour */
	focusColour();


	while (corners[0].getPosition().y < finalPosition.y && !isInFocus) {		//While not fully open

		timeSinceLastUpdate += clock.restart();

		while (timeSinceLastUpdate > timePerFrame) {

			timeSinceLastUpdate -= timePerFrame;
			calculateCloseDirection(timePerFrame);
		}
		
		closedCompleted = true; //Once closing has completed - animation is closed
	}
}


void TanimatedButton::animation() {
	isAlreadyRunning = true;

	openAnimation();
	closeAnimation();

	isAlreadyRunning = false;	//Allow for another thread to spawn
	closedCompleted = false;	//Reset for next thread spawned
}


void TanimatedButton::runAnimation() {

	std::thread animation(&TanimatedButton::animation, this);
	animation.detach();
}

void TanimatedButton::setInFocus(bool isFocus) {
	
	isInFocus = isFocus;

	if(!isAlreadyRunning)	//If safe to do so, launch new thread
		runAnimation();
}
