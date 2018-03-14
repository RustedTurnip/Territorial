#include "LoadingScreen.h"

#include <ctime>
#include <iostream>

std::atomic<bool> LoadingScreen::isRunning = false;

/*
 * Constructor -- Destructor
 */

LoadingScreen::LoadingScreen(sf::RenderWindow* window)
	: window(window){

	initialise();
}

/*!
 * \brief sets up the loading screen
 */
void LoadingScreen::initialise() {

	font.loadFromFile("res/fonts/cinzel.otf");
	text.setFont(font);

	text.setColor(sf::Color::Black);
	text.setCharacterSize(40);
	text.setString("Loading...");
	
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin((bounds.left + bounds.width) / 2, (bounds.top + bounds.height) / 2);
	text.setPosition(window->getSize().x / 2, window->getSize().y/2);
}

/*!
 * \brief responsible for the animate elipses
 */
void LoadingScreen::animation() {
	
	std::string str = "Loading";
	size_t count = 0, startTime = clock();

	while (isRunning.load()) {

		if ((clock() - startTime) / (CLOCKS_PER_SEC / 1000) >= 500) {	//If half a second has passed
			startTime = clock();	//Reset timer
			str = "Loading";		//Reset text
			count++;

			for (int i = 0; i < (count % 4); i++) {	//Add correct amount of elipses, max 3
				str += ".";
			}
		}
		text.setString(str);	//Update text
		
		window->clear(sf::Color::White);
		window->draw(text);
		window->display();
	}
	window->setActive(false);
}

void LoadingScreen::run() {

	window->setActive(false);	//Switching over to new thread temporarily, switching back is automatic I think
	isRunning = true;
	screenThread = std::thread(&LoadingScreen::animation, this);
}

/*!
 * \brief used to safely terminate the loading screen preventing undefined behaviour and safe transfer 
 *		of the windows context
 */
void LoadingScreen::terminate() {
	isRunning = false;
	screenThread.join();
}