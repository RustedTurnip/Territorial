#include "BattleOverlay.h"
#include "Territorial.h"
#include "Mouse.h"
#include "Dice.h"
#include "Player.h"

#include <algorithm>

/* Constructor */
BattleOverlay::BattleOverlay() {
	initialise();
}

void BattleOverlay::initialise() {

	background.setFillColor(sf::Color(50, 50, 50, 230));

	//Generic text initialise
	attackerTitle.setFillColor(sf::Color::White);
	defenderTitle.setFillColor(sf::Color::White);
	overlayTitle.setFillColor(sf::Color::White);
	attackerUnits.setFillColor(sf::Color::White);
	defenderUnits.setFillColor(sf::Color::White);

	//Generic button initialise
	rollButton.setSize(sf::Vector2f(350, 50));
	rollButton.setFont(Territorial::mainFont);
	rollButton.setText("Roll");
	rollButton.setBackgroundColour(sf::Color::White);
	rollButton.setForegroundColour(sf::Color::Black);
	rollButton.setFocusBackgroundColour(sf::Color(155, 155, 155));
	rollButton.setFocusForegroundColour(sf::Color::Black);

	addDiceButton.setBackgroundColour(sf::Color::White);
	addDiceButton.setForegroundColour(sf::Color::Black);
	addDiceButton.setFocusBackgroundColour(sf::Color(155, 155, 155));
	addDiceButton.setFocusForegroundColour(sf::Color::Black);
	addDiceButton.setText("+");
	removeDiceButton.setBackgroundColour(sf::Color::White);
	removeDiceButton.setForegroundColour(sf::Color::Black);
	removeDiceButton.setFocusBackgroundColour(sf::Color(155, 155, 155));
	removeDiceButton.setFocusForegroundColour(sf::Color::Black);
	removeDiceButton.setText("-");

	closeButton.setBackgroundColour(sf::Color::White);
	closeButton.setForegroundColour(sf::Color::Black);

}

void BattleOverlay::initialiseElements() {

	currentDice = 1;
	diceNumber.setString(std::to_string(currentDice));

	//Ttiles
	attackerTitle.setString(attacker->getName());
	defenderTitle.setString(defender->getName());

	//Sprites
	attackerSprite.setTexture(*attacker->getShape().getTexture());
	defenderSprite.setTexture(*defender->getShape().getTexture());
	//Set sprite size
	//Set sprite scale
	float attackerScale;
	float defenderScale;
	if (attackerSprite.getTexture()->getSize().x > attackerSprite.getTexture()->getSize().y) {
		attackerScale = ICON_SIZE.x / attackerSprite.getTexture()->getSize().x;
	}
	else {
		attackerScale = ICON_SIZE.y / attackerSprite.getTexture()->getSize().y;
	}
	if (defenderSprite.getTexture()->getSize().x > defenderSprite.getTexture()->getSize().y) {
		defenderScale = ICON_SIZE.x / defenderSprite.getTexture()->getSize().x;
	}
	else {
		defenderScale = ICON_SIZE.y / defenderSprite.getTexture()->getSize().y;
	}
	attackerSprite.setScale(attackerScale, attackerScale);
	defenderSprite.setScale(defenderScale, defenderScale);

	//Unit numbers
	attackerUnits.setString(std::to_string(attacker->getUnits()));
	defenderUnits.setString(std::to_string(defender->getUnits()));
}

void BattleOverlay::positionElements() {

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
	bounds = attackerTitle.getLocalBounds();
	attackerTitle.setOrigin((bounds.left + bounds.width) / 2, 0);
	/* Align text */
	bounds = defenderTitle.getLocalBounds();
	defenderTitle.setOrigin((bounds.left + bounds.width) / 2, 0);
	
	attackerTitle.setPosition(attackerXAxis, yAxis);
	defenderTitle.setPosition(defenderXAxis, yAxis);

	yAxis += VERTICAL_SPACE + attackerTitle.getLocalBounds().height;

	// POSITION SPRITES 
	//Get sprite size
	sf::Vector2f attackerSize(attackerSprite.getTexture()->getSize().x * attackerSprite.getScale().x,
		attackerSprite.getTexture()->getSize().y * attackerSprite.getScale().y);
	sf::Vector2f defenderSize(defenderSprite.getTexture()->getSize().x * defenderSprite.getScale().x,
		defenderSprite.getTexture()->getSize().y * defenderSprite.getScale().y);
	attackerSprite.setPosition(sf::Vector2f(attackerXAxis - (attackerSize.x / 2), yAxis));
	defenderSprite.setPosition(sf::Vector2f(defenderXAxis - (defenderSize.x / 2), yAxis));

	yAxis += VERTICAL_SPACE + ICON_SIZE.y;

	// POSITION UNIT NUMBERS
	/* Align text */
	bounds = attackerUnits.getLocalBounds();
	attackerUnits.setOrigin((bounds.left + bounds.width) / 2, 0);
	attackerUnits.setPosition(sf::Vector2f(attackerXAxis, yAxis));

	/* Align text */
	bounds = defenderUnits.getLocalBounds();
	defenderUnits.setOrigin((bounds.left + bounds.width) / 2, 0);
	defenderUnits.setPosition(sf::Vector2f(defenderXAxis, yAxis));

	yAxis += VERTICAL_SPACE + bounds.height;

	//POSITION DICE ELEMENTS
	//Leaving 150px gap in middle
	removeDiceButton.setPosition(sf::Vector2f(centreXAxis - DICE_BUTTON_SIZE.x - 75, yAxis));
	addDiceButton.setPosition(sf::Vector2f(centreXAxis + 75, yAxis));
	/* Align text */
	bounds = diceNumber.getLocalBounds();
	diceNumber.setOrigin((bounds.left + bounds.width) / 2, 0);
	diceNumber.setPosition(sf::Vector2f(centreXAxis, yAxis));

	yAxis += VERTICAL_SPACE + DICE_BUTTON_SIZE.y;
	
	// POSITION ROLL BUTTON
	rollButton.setPosition(sf::Vector2f(centreXAxis - (rollButton.getSize().x / 2), yAxis));
}

void BattleOverlay::openWindow(Territory& attacker, Territory& defender) {

	this->attacker = &attacker;
	this->defender = &defender;

	initialiseElements();
	positionElements();

	open = true;
}

void BattleOverlay::handleEvents(sf::Event event) {
	
	switch (event.type) {
	case sf::Event::MouseMoved: {
		handleMouseMove(); break;
	}
	case sf::Event::MouseButtonReleased: {
		handleMouseClick(); break;
	}
	}
}

void BattleOverlay::handleMouseMove() {
	
	sf::Vector2i rawMouse = Mouse::getMousePosition();
	sf::Vector2f mousePos = sf::Vector2f(rawMouse.x, rawMouse.y);

	if (addDiceButton.getGlobalBounds().contains(mousePos)) {
		addDiceButton.setInFocus(true);
	}
	else
		addDiceButton.setInFocus(false);

	if (removeDiceButton.getGlobalBounds().contains(mousePos)) {
		removeDiceButton.setInFocus(true);
	}
	else
		removeDiceButton.setInFocus(false);

	if (rollButton.getGlobalBounds().contains(mousePos)) {
		rollButton.setInFocus(true);
	}
	else
		rollButton.setInFocus(false);
}

void BattleOverlay::handleMouseClick() {
	sf::Vector2i rawMouse = Mouse::getMousePosition();
	sf::Vector2f mousePos = sf::Vector2f(rawMouse.x, rawMouse.y);

	if (addDiceButton.getGlobalBounds().contains(mousePos)) {
		addDice();
	}
	else if (removeDiceButton.getGlobalBounds().contains(mousePos)) {
		removeDice();
	}
	else if (rollButton.getGlobalBounds().contains(mousePos)) {
		attack();
	}
	else if (closeButton.getGlobalBounds().contains(mousePos)) {
		close();
	}

}

void BattleOverlay::addDice() {
	if (attacker->getUnits() - 1 > currentDice) { //Enough units to attack with
		if (currentDice < 3) { //Use up to three dice
			currentDice++;
			diceNumber.setString(std::to_string(currentDice));
		}
	}
}

void BattleOverlay::removeDice() {
	if (currentDice > 1) {
		currentDice--;
		diceNumber.setString(std::to_string(currentDice));
	}
}

void BattleOverlay::attack() {
	
	int attacking = currentDice;
	int defending = 1;
	if (defender->getUnits() > 1)
		defending++;

	//Roll dice
	Dice dice = Dice(6); //Six sided dice
	std::vector<int> attackRolls = std::vector<int>();
	std::vector<int> defenceRolls = std::vector<int>();

	for (int i = 0; i < attacking; i++)
		attackRolls.push_back(dice.roll());
	for (int i = 0; i < defending; i++)
		defenceRolls.push_back(dice.roll());

	//Order rolls (ascending)
	std::sort(attackRolls.begin(), attackRolls.end(), std::greater<int>());
	std::sort(defenceRolls.begin(), defenceRolls.end(), std::greater<int>());

	//Comparison no. (lesser of the two)
	size_t comparisonNum = (attacking < defending) ? attacking : defending;

	//Compare highest two rolls for each - draw favours defence
	for (int i = 0; i < comparisonNum; i++) {
		if (attackRolls.at(i) > defenceRolls.at(i)) {
			defender->setUnits(defender->getUnits() - 1);
		}
		else {
			attacker->setUnits(attacker->getUnits() - 1);
		}
	}

	//If battle won
	if (defender->getUnits() == 0) {
		//Set to new player
		defender->setPlayer(attacker->getPlayer());
		defender->setUnitDisplayColour(Player::COLOURS[attacker->getPlayer()-1]); //TEMP

		//Temporary only transfer 1 unit in win
		defender->setUnits(1);
		attacker->setUnits(attacker->getUnits() - 1);
		close();
	}
	else if (attacker->getUnits() == 1) { //If battle lost
		close();
	}
	else { //Refresh and go again
		//TEMP
		size_t lastDice = currentDice;
		initialiseElements();
		positionElements();

		if (attacker->getUnits() - 1 < lastDice) {
			currentDice = attacker->getUnits() - 1;
		}
		else {
			currentDice = lastDice;
		}
		diceNumber.setString(std::to_string(currentDice));
	}
}

/* Overrides */
void BattleOverlay::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	target.draw(background);
	target.draw(overlayTitle);
	target.draw(closeButton);
	target.draw(attackerSprite);
	target.draw(defenderSprite);
	target.draw(attackerTitle);
	target.draw(defenderTitle);
	target.draw(attackerUnits);
	target.draw(defenderUnits);
	target.draw(removeDiceButton);
	target.draw(diceNumber);
	target.draw(addDiceButton);
	target.draw(rollButton);
}