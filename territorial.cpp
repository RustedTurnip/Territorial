/*! 
 * \file Territorial.cpp : Defines the entry point for the console application.
 */
#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>

/* Globals */
sf::RenderWindow window(sf::VideoMode(800, 500), "Territorial");
extern std::string version; /* Called in from globals.cpp */

/* Function Prototypes */
void handleEvents();

/*!
 * \brief The main method from which the game is launched
 */
int main()
{
	std::cout << version << std::endl;

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
