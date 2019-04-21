/*! 
 * \file main.cpp : Defines the entry point for the console application.
 */
#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include <Windows.h>

#include "Territorial.h"
#include "Mouse.h"
#include "ViewManager.h"
#include "SplashScreen.h"

/* Globals */
sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Territorial", sf::Style::Fullscreen);
ViewManager manager(&window);

/* Function Prototypes */
void setup();
void handleEvents();
void handleKeyboardEvents(sf::Event event);
void splash();

/*!
 * \brief The main method from which the game is launched
 */
int main()
{
	std::cout << Territorial::version << std::endl;
	
	setup();

	//Frame-rate regulation initialisation
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	
	while (window.isOpen()) {
		handleEvents();
		
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > Territorial::TIME_PER_FRAME) {	/* Skip render until events caught up */
			timeSinceLastUpdate -= Territorial::TIME_PER_FRAME;
			handleEvents();
		}

		Territorial::updateStatistics(elapsedTime);
		manager.render();
		window.display();
	}

	return 0;
}

/*!
 * \brief Method to encompass any initialisations before beginning the game's execution
 */
void setup() {
	window.setFramerateLimit(Territorial::FRAMERATE_LIMIT); //Implement framerate limit
	Territorial::setWindowSize(sf::Vector2f(window.getSize()));//Set window size global
	Mouse::setWindow(&window);

	Territorial::initialiseResources();

	splash();
}

/*!
 *\brief This method handles global events
 */
void handleEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			window.close(); return;
		case sf::Event::KeyReleased:
		case sf::Event::KeyPressed:
			handleKeyboardEvents(event); return;
		}
		manager.handleEvents(event);
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
		case sf::Keyboard::LSystem:
			ShowWindow(window.getSystemHandle(), SW_MINIMIZE); break;
		}
	}
}

/*!
 * \brief Launches the splash screen
 * \TODO better integrate splash screen, seperate control loop seems excessive perhaps? But would it add to much to main loop?
 */
void splash() {
	SplashScreen splash("res/images/canalside_splash.png", 7000, window);
	splash.run();
}

