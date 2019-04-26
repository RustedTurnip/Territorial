#include "FortifyOverlay.h"
#include "Territorial.h"
#include "Mouse.h"

/* Constructor */
FortifyOverlay::FortifyOverlay() {
	initialise();
}

void FortifyOverlay::initialise() {

	background.setFillColor(sf::Color(50, 50, 50, 230));

	//Generic text initialise
	sourceTitle.setFillColor(sf::Color::White);
	destinationTitle.setFillColor(sf::Color::White);
	overlayTitle.setFillColor(sf::Color::White);
	sourceUnits.setFillColor(sf::Color::White);
	destinationUnits.setFillColor(sf::Color::White);

	//Generic button initialise
	confirmButton.setSize(sf::Vector2f(350, 50));
	confirmButton.setFont(Territorial::mainFont);
	confirmButton.setText("Confirm");
	confirmButton.setBackgroundColour(sf::Color::White);
	confirmButton.setForegroundColour(sf::Color::Black);
	confirmButton.setFocusBackgroundColour(sf::Color(155, 155, 155));
	confirmButton.setFocusForegroundColour(sf::Color::Black);

	addUnitButton.setBackgroundColour(sf::Color::White);
	addUnitButton.setForegroundColour(sf::Color::Black);
	addUnitButton.setFocusBackgroundColour(sf::Color(155, 155, 155));
	addUnitButton.setFocusForegroundColour(sf::Color::Black);
	addUnitButton.setText("+");
	removeUnitButton.setBackgroundColour(sf::Color::White);
	removeUnitButton.setForegroundColour(sf::Color::Black);
	removeUnitButton.setFocusBackgroundColour(sf::Color(155, 155, 155));
	removeUnitButton.setFocusForegroundColour(sf::Color::Black);
	removeUnitButton.setText("-");

	closeButton.setBackgroundColour(sf::Color::White);
	closeButton.setForegroundColour(sf::Color::Black);

}

void FortifyOverlay::initialiseElements() {

	//Ttiles
	sourceTitle.setString(source->getName());
	destinationTitle.setString(destination->getName());

	//Sprites
	sourceSprite.setTexture(*source->getShape().getTexture());
	destinationSprite.setTexture(*destination->getShape().getTexture());
	//Set sprite size
	//Set sprite scale
	float attackerScale;
	float defenderScale;
	if (sourceSprite.getTexture()->getSize().x > sourceSprite.getTexture()->getSize().y) {
		attackerScale = ICON_SIZE.x / sourceSprite.getTexture()->getSize().x;
	}
	else {
		attackerScale = ICON_SIZE.y / sourceSprite.getTexture()->getSize().y;
	}
	if (destinationSprite.getTexture()->getSize().x > destinationSprite.getTexture()->getSize().y) {
		defenderScale = ICON_SIZE.x / destinationSprite.getTexture()->getSize().x;
	}
	else {
		defenderScale = ICON_SIZE.y / destinationSprite.getTexture()->getSize().y;
	}
	sourceSprite.setScale(attackerScale, attackerScale);
	destinationSprite.setScale(defenderScale, defenderScale);

	//Unit numbers
	sourceUnits.setString(std::to_string(source->getUnits()));
	destinationUnits.setString(std::to_string(destination->getUnits()));
}

void FortifyOverlay::positionElements() {

	background.setPosition(Territorial::getWindowCentre().x - OVERLAY_SIZE.x / 2, Territorial::getWindowCentre().y - OVERLAY_SIZE.y / 2);
	sf::Vector2f startPos = background.getPosition();


	float yAxis = startPos.y + VERTICAL_SPACE;

	float quarter = OVERLAY_SIZE.x / 4;
	float attackerXAxis = startPos.x + quarter;
	float defenderXAxis = startPos.x + (quarter * 3);
	float centreXAxis = startPos.x + (quarter * 2);

	// POSITION CLOSE BUTTON
	closeButton.setPosition(sf::Vector2f((startPos.x + OVERLAY_SIZE.x) - closeButton.getSize().x - 25, startPos.y + 25));

	// POSITION MAIN TITLE
	/* Align text */
	sf::FloatRect bounds = overlayTitle.getLocalBounds();
	overlayTitle.setOrigin((bounds.left + bounds.width) / 2, 0);

	overlayTitle.setPosition(sf::Vector2f(centreXAxis, yAxis));
	yAxis += VERTICAL_SPACE + overlayTitle.getLocalBounds().height;

	// POSITION TERRITORY TITLES
	/* Align text */
	bounds = sourceTitle.getLocalBounds();
	sourceTitle.setOrigin((bounds.left + bounds.width) / 2, 0);
	/* Align text */
	bounds = destinationTitle.getLocalBounds();
	destinationTitle.setOrigin((bounds.left + bounds.width) / 2, 0);

	sourceTitle.setPosition(attackerXAxis, yAxis);
	destinationTitle.setPosition(defenderXAxis, yAxis);

	yAxis += VERTICAL_SPACE + sourceTitle.getLocalBounds().height;

	// POSITION SPRITES 
	//Get sprite size
	sf::Vector2f attackerSize(sourceSprite.getTexture()->getSize().x * sourceSprite.getScale().x,
		sourceSprite.getTexture()->getSize().y * sourceSprite.getScale().y);
	sf::Vector2f defenderSize(destinationSprite.getTexture()->getSize().x * destinationSprite.getScale().x,
		destinationSprite.getTexture()->getSize().y * destinationSprite.getScale().y);
	sourceSprite.setPosition(sf::Vector2f(attackerXAxis - (attackerSize.x / 2), yAxis));
	destinationSprite.setPosition(sf::Vector2f(defenderXAxis - (defenderSize.x / 2), yAxis));

	yAxis += VERTICAL_SPACE + ICON_SIZE.y;

	// POSITION UNIT NUMBERS
	/* Align text */
	bounds = sourceUnits.getLocalBounds();
	sourceUnits.setOrigin((bounds.left + bounds.width) / 2, 0);
	sourceUnits.setPosition(sf::Vector2f(attackerXAxis, yAxis));

	/* Align text */
	bounds = destinationUnits.getLocalBounds();
	destinationUnits.setOrigin((bounds.left + bounds.width) / 2, 0);
	destinationUnits.setPosition(sf::Vector2f(defenderXAxis, yAxis));

	yAxis += VERTICAL_SPACE + bounds.height;

	//POSITION DICE ELEMENTS
	//Leaving 150px gap in middle
	removeUnitButton.setPosition(sf::Vector2f(centreXAxis - UNIT_BUTTON_SIZE.x - 75, yAxis));
	addUnitButton.setPosition(sf::Vector2f(centreXAxis + 75, yAxis));
	/* Align text */
	bounds = unitNumber.getLocalBounds();
	unitNumber.setOrigin((bounds.left + bounds.width) / 2, 0);
	unitNumber.setPosition(sf::Vector2f(centreXAxis, yAxis));

	yAxis += VERTICAL_SPACE + UNIT_BUTTON_SIZE.y;

	// POSITION ROLL BUTTON
	confirmButton.setPosition(sf::Vector2f(centreXAxis - (confirmButton.getSize().x / 2), yAxis));
}

void FortifyOverlay::openWindow(Territory& attacker, Territory& defender) {

	this->source = &attacker;
	this->destination = &defender;
	fortifyCommit = false;

	initialiseElements();
	positionElements();

	open = true;
}

void FortifyOverlay::handleEvents(sf::Event event) {

	switch (event.type) {
	case sf::Event::MouseMoved: {
		handleMouseMove(); break;
	}
	case sf::Event::MouseButtonReleased: {
		handleMouseClick(); break;
	}
	}
}

void FortifyOverlay::handleMouseMove() {

	sf::Vector2i rawMouse = Mouse::getMousePosition();
	sf::Vector2f mousePos = sf::Vector2f(rawMouse.x, rawMouse.y);

	if (addUnitButton.getGlobalBounds().contains(mousePos)) {
		addUnitButton.setInFocus(true);
	}
	else
		addUnitButton.setInFocus(false);

	if (removeUnitButton.getGlobalBounds().contains(mousePos)) {
		removeUnitButton.setInFocus(true);
	}
	else
		removeUnitButton.setInFocus(false);

	if (confirmButton.getGlobalBounds().contains(mousePos)) {
		confirmButton.setInFocus(true);
	}
	else
		confirmButton.setInFocus(false);
}

void FortifyOverlay::handleMouseClick() {
	sf::Vector2i rawMouse = Mouse::getMousePosition();
	sf::Vector2f mousePos = sf::Vector2f(rawMouse.x, rawMouse.y);

	if (addUnitButton.getGlobalBounds().contains(mousePos)) {
		addDice();
	}
	else if (removeUnitButton.getGlobalBounds().contains(mousePos)) {
		removeDice();
	}
	else if (confirmButton.getGlobalBounds().contains(mousePos)) {
		fortifyCommit = true;
		close();
	}
	else if (closeButton.getGlobalBounds().contains(mousePos)) {
		close();
	}

}

/* Overrides */
void FortifyOverlay::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	target.draw(background);
	target.draw(overlayTitle);
	target.draw(closeButton);
	target.draw(sourceSprite);
	target.draw(destinationSprite);
	target.draw(sourceTitle);
	target.draw(destinationTitle);
	target.draw(sourceUnits);
	target.draw(destinationUnits);
	target.draw(removeUnitButton);
	target.draw(unitNumber);
	target.draw(addUnitButton);
	target.draw(confirmButton);
}