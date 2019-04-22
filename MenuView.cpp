#include "MenuView.h"

/*
	Constructor -- Destructor
*/
MenuView::MenuView(sf::RenderWindow* window)
	: View(window) {

	//initialiseScreen();
	font.loadFromFile("res/fonts/cinzel.otf");
	initialise();
}

MenuView::~MenuView() {

}

/*
	Override methods
*/
Identifiers::StateChange MenuView::handleEvents(sf::Event event) {

	sf::Vector2f mousePos(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);

	//Click events (on release)
	if (event.type == sf::Event::MouseButtonReleased) {
		
		sf::Vector2f mousePos(sf::Mouse::getPosition(*getWindow()).x, sf::Mouse::getPosition(*getWindow()).y);

		for (int i = 0; i < buttons.size(); i++) {
			if (buttons.at(i).getGlobalBounds().contains(mousePos)) {
				/* Note to self -- Think about button struct - part StateIdentifier, part Button - return buttons[i].state */
				return Identifiers::SetupGame;
			}
			else
				buttons.at(i).setInFocus(false);
		}

			//return Identifiers::StateChange::StartGame;
	}
	//Mouse over events
	if (event.type == sf::Event::MouseMoved) {
		sf::Vector2f mousePos(sf::Mouse::getPosition(*getWindow()).x, sf::Mouse::getPosition(*getWindow()).y);

		for (int i = 0; i < buttons.size(); i++) {

			if (buttons.at(i).getGlobalBounds().contains(mousePos)) {
				buttons.at(i).setInFocus(true);
				break;
			}
			else
				buttons.at(i).setInFocus(false);
		}
	}

	return Identifiers::StateChange::DoNothing;
}

void MenuView::render() {
	
	getWindow()->clear(sf::Color::White);
	getWindow()->draw(logo);

	for (int i = 0; i < buttons.size(); i++)
		getWindow()->draw(buttons.at(i));
}

/*
	Initialise Methods
*/

void MenuView::initialise() {

	initialiseImages();
	initialiseScreen();
	initialiseButtons();
}

void MenuView::initialiseImages() {

	if (!logoImage.loadFromFile("res/images/territorial_logo.png"))
		std::cerr << "Failed to locate \"territorial_logo.png\"" << std::endl;

	logo.setTexture(logoImage);
	logo.setOrigin(logoImage.getSize().x / 2, logoImage.getSize().y / 2);
	logo.setPosition(getWindow()->getSize().x / 2, 200);
}

void MenuView::initialiseScreen() {
	
	
}


void MenuView::initialiseButtons() {

	initialiseButtonBounds();

	sf::Vector2f buttonStartPos;
	size_t tempY;
	size_t buttonBoxHeight = ((BUTTON_NO * BUTTON_SIZE.y) + ((BUTTON_NO - 1) * BUTTON_SPACING));

	buttonStartPos.x = getWindow()->getSize().x / 2;	//Centre of screen
	buttonStartPos.y = (getWindow()->getSize().y / 2) - (buttonBoxHeight / 2);

	tempY = buttonStartPos.y;

	/* Iterate through buttons to set invariable data */
	for (int i = 0; i < BUTTON_NO; i++) {

		if(i != 0)
			tempY += BUTTON_SPACING + BUTTON_SIZE.y;

		buttons.push_back(TanimatedButton(BUTTON_SIZE));
		buttons.at(i).setFont(font);
		buttons.at(i).setOrigin(sf::Vector2f(buttons.at(i).getSize().x / 2, buttons.at(i).getSize().y / 2));
		buttons.at(i).setPosition(sf::Vector2f(buttonStartPos.x, tempY));
		buttons.at(i).setTextSize(28);
		buttons.at(i).setBackgroundColour(sf::Color::Black);
		buttons.at(i).setFocusBackgroundColour(sf::Color(155, 155, 155));
		buttons.at(i).setForegroundColour(sf::Color::White);
		buttons.at(i).setFocusForegroundColour(sf::Color::White);
	}

	buttons.at(0).setText("Play Game");
	buttons.at(1).setText("Settings");
	buttons.at(2).setText("Instructions");
	buttons.at(3).setText("Credits");
}

void MenuView::initialiseButtonBounds() {

	float left, top, width, height;

	height = (BUTTON_NO * BUTTON_SIZE.y) + ((BUTTON_NO - 1) * BUTTON_SPACING);
	width = BUTTON_SIZE.x;
	left = (getWindow()->getSize().x / 2) - (width / 2);
	top = (getWindow()->getSize().y / 2) - (height / 2);
	
	buttonBounds = sf::FloatRect(left, top, width, height);
}



/*
	Rest of methods
*/

