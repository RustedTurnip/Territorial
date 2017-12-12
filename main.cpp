/*! 
 * \file main.cpp : Defines the entry point for the console application.
 */
#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>

#include "territorial.h"

/* Globals */
sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Territorial", sf::Style::Fullscreen);

/* Function Prototypes */
void handleEvents();
void handleKeyboardEvents(sf::Event event);

/*!
 * \brief The main method from which the game is launched
 */
int main()
{
	std::cout << Territorial::getVersion() << std::endl;

	while (window.isOpen()) {
		handleEvents();

		window.clear(sf::Color::White);
		//Render method call here
		window.display();
	}

	return 0;
}

/*!
 *\brief This method handles global events
 */
void handleEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			window.close(); break;
		case sf::Event::KeyReleased:
		case sf::Event::KeyPressed:
			handleKeyboardEvents(event); break;
		}
	}
}

/*!
 * \brief This method handles keyboard events
 */
void handleKeyboardEvents(sf::Event event) {
	if (event.type == sf::Event::KeyReleased) {
		switch (event.key.code)
		{
		case sf::Keyboard::Escape:
			window.close();  break;
		}
	}
	else if(event.type == sf::Event::KeyPressed){
		return;	//Temp
	}
}
