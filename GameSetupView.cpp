#include "GameSetupView.h"
#include "Territorial.h"

/*
Constructor -- Destructor
*/
GameSetupView::GameSetupView(sf::RenderWindow* window)
	: View(window)
	, font(Territorial::mainFont){

	//initialiseScreen();
	initialise();
}

GameSetupView::~GameSetupView() {

}

/*
Override methods
*/
Identifiers::StateChange GameSetupView::handleEvents(sf::Event event) {

	sf::Vector2f mousePos(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);

	//Click events (on release)
	if (event.type == sf::Event::MouseButtonReleased) {

		sf::Vector2f mousePos(sf::Mouse::getPosition(*getWindow()).x, sf::Mouse::getPosition(*getWindow()).y);

		for (int i = 0; i < buttons.size(); i++) {
			if (buttons.at(i).second.getGlobalBounds().contains(mousePos)) {
				/* Note to self -- Think about button struct - part StateIdentifier, part Button - return buttons[i].state */
				toggleHuman(i);
				return Identifiers::DoNothing;
			}
			else
				buttons.at(i).second.setInFocus(false);
		}

		//Add/Remove buttons
		if (addButton.getGlobalBounds().contains(mousePos))
			addPlayer();
		else
			addButton.setInFocus(false);

		if (removeButton.getGlobalBounds().contains(mousePos)) {
			removePlayer();
			return Identifiers::DoNothing;
		}
		else
			removeButton.setInFocus(false);

		//Play button
		if (playButton.getGlobalBounds().contains(mousePos))
			return Identifiers::StateChange::PlayGame;
		else
			playButton.setInFocus(false);

	}
	//Mouse over events
	if (event.type == sf::Event::MouseMoved) {
		sf::Vector2f mousePos(sf::Mouse::getPosition(*getWindow()).x, sf::Mouse::getPosition(*getWindow()).y);

		for (int i = 0; i < buttons.size(); i++) {

			if (buttons.at(i).second.getGlobalBounds().contains(mousePos)) {
				buttons.at(i).second.setInFocus(true);
				break;
			}
			else
				buttons.at(i).second.setInFocus(false);
		}

		//Add/Remove buttons
		if (addButton.getGlobalBounds().contains(mousePos))
			addButton.setInFocus(true);
		else
			addButton.setInFocus(false);

		if (removeButton.getGlobalBounds().contains(mousePos))
			removeButton.setInFocus(true);
		else
			removeButton.setInFocus(false);

		//Play button
		if (playButton.getGlobalBounds().contains(mousePos))
			playButton.setInFocus(true);
		else
			playButton.setInFocus(false);
	}

	return Identifiers::StateChange::DoNothing;
}

void GameSetupView::render() {

	getWindow()->clear(sf::Color::White);
	getWindow()->draw(title);

	for (int i = 0; i < buttons.size(); i++) {
		getWindow()->draw(buttons.at(i).first);
		getWindow()->draw(buttons.at(i).second);
	}

	getWindow()->draw(addButton);
	getWindow()->draw(removeButton);
	getWindow()->draw(playButton);
}

/*
Initialise Methods
*/

void GameSetupView::initialise() {

	//Add min. players
	addPlayer();
	addPlayer();

	initialiseText();
	initialiseFixedButtons();
	positionButtons();
}

void GameSetupView::initialiseText() {

	this->title = sf::Text("Game Setup", font, 72);
	this->title.setFillColor(sf::Color::Black);

	/* Align text */
	sf::FloatRect bounds = title.getLocalBounds();
	title.setOrigin((bounds.left + bounds.width) / 2, (bounds.top + bounds.height) / 2);
	title.setPosition(sf::Vector2f(Territorial::getWindowCentre().x, 350));

}

void GameSetupView::initialiseFixedButtons() {
	
	//Play button
	playButton = TanimatedButton(font, PLAYER_SIZE);
	playButton.setTextSize(28);
	playButton.setText("Play");
	playButton.setBackgroundColour(sf::Color::Black);
	playButton.setFocusBackgroundColour(sf::Color(155, 155, 155));
	playButton.setForegroundColour(sf::Color::White);
	playButton.setFocusForegroundColour(sf::Color::White);

	//Add/Remove
	addButton = Tbutton(font, BUTTON_ADD_REM_SIZE);
	removeButton = Tbutton(font, BUTTON_ADD_REM_SIZE);

	addButton.setText("+");
	removeButton.setText("-");

	addButton.setTextSize(36);
	removeButton.setTextSize(36);

	//Colours
	addButton.setBackgroundColour(sf::Color::Black);
	addButton.setFocusBackgroundColour(sf::Color(155, 155, 155));
	addButton.setForegroundColour(sf::Color::White);
	addButton.setFocusForegroundColour(sf::Color::White);
	removeButton.setBackgroundColour(sf::Color::Black);
	removeButton.setFocusBackgroundColour(sf::Color(155, 155, 155));
	removeButton.setForegroundColour(sf::Color::White);
	removeButton.setFocusForegroundColour(sf::Color::White);

}

void GameSetupView::positionButtons() {

	calculateButtonBounds();

	sf::Vector2f buttonStartPos = sf::Vector2f(buttonBounds.left, buttonBounds.top);
	size_t tempY;
	
	tempY = buttonStartPos.y;

	/* Iterate through buttons to set invariable data */
	for (int i = 0; i < buttons.size(); i++) {

		if (i != 0)
			tempY += BUTTON_VERTICAL_SPACING + PLAYER_SIZE.y;

		buttons.at(i).first.setPosition(sf::Vector2f(buttonStartPos.x, tempY));
		buttons.at(i).second.setPosition(sf::Vector2f(buttonStartPos.x + PLAYER_SIZE.x + BUTTON_HORIZONTAL_SPACING, tempY));	
	}

	tempY += BUTTON_VERTICAL_SPACING + PLAYER_SIZE.y;
	addButton.setPosition(sf::Vector2f(buttonStartPos.x, tempY));
	removeButton.setPosition(sf::Vector2f(buttonStartPos.x + BUTTON_ADD_REM_SIZE.x + BUTTON_VERTICAL_SPACING, tempY));

	tempY += BUTTON_VERTICAL_SPACING + BUTTON_ADD_REM_SIZE.y;
	playButton.setPosition(sf::Vector2f(Territorial::getWindowCentre().x - PLAYER_SIZE.x / 2, tempY));

}

void GameSetupView::calculateButtonBounds() {

	float left, top, width, height;
	size_t buttonNo = buttons.size();

	height = (buttonNo * PLAYER_SIZE.y) + ((buttonNo - 1) * BUTTON_VERTICAL_SPACING);
	height += BUTTON_VERTICAL_SPACING + BUTTON_ADD_REM_SIZE.y + BUTTON_VERTICAL_SPACING + PLAYER_SIZE.y; //Accommodate extra buttons at bottom
	width = PLAYER_SIZE.x + BUTTON_HORIZONTAL_SPACING + HUMAN_TOGGLE_SIZE.x;
	left = (Territorial::getWindowCentre().x) - (width / 2);
	top = (Territorial::getWindowCentre().y) - (height / 2);

	buttonBounds = sf::FloatRect(left, top, width, height);
}



/*
Rest of methods
*/

void GameSetupView::addPlayer() {
	
	std::pair<Tbutton, Tbutton> pair = std::pair<Tbutton, Tbutton>();
	size_t playerNum = buttons.size() + 1;

	//Add Player Button
	pair.first = Tbutton(font, PLAYER_SIZE);
	pair.first.setText(PLAYER_STRING + " " + std::to_string(playerNum));
	pair.first.setTextSize(22);
	//Colours
	pair.first.setBackgroundColour(sf::Color::Black);
	pair.first.setForegroundColour(sf::Color::White);

	//Add corresponding toggle button
	pair.second = Tbutton(font, HUMAN_TOGGLE_SIZE);
	pair.second.setText(HUMAN_STRING);
	pair.second.setTextSize(28);
	//Colours
	pair.second.setBackgroundColour(sf::Color::Black);
	pair.second.setFocusBackgroundColour(sf::Color(155, 155, 155));
	pair.second.setForegroundColour(sf::Color::White);
	pair.second.setFocusForegroundColour(sf::Color::White);

	buttons.push_back(pair);
	positionButtons();
}

void GameSetupView::removePlayer() {

	if (buttons.size() <= 2)
		return;

	buttons.pop_back();
	positionButtons();
}

void GameSetupView::toggleHuman(size_t num) {

	if (buttons.at(num).second.getText() == HUMAN_STRING)
		buttons.at(num).second.setText(PC_STRING);
	else
		buttons.at(num).second.setText(HUMAN_STRING);
}
