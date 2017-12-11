/*! 
 * \file main.cpp : Defines the entry point for the console application.
 */
#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>

#include "territorial.h"

/* Globals */
sf::RenderWindow window(sf::VideoMode(800, 500), "Territorial");

/* Function Prototypes */
void handleEvents();

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
		}
	}
}
