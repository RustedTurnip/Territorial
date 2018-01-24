#include "SplashScreen.h"
#include "Territorial.h"
#include <thread>
#include <ctime>
#include <chrono>
#include <iostream>

/*
 * Constructor
 * \param duration: Length of splash screen in milliseconds
 */
SplashScreen::SplashScreen(std::string icon_loc, size_t duration, sf::RenderWindow& window)
: duration(duration)
, fadeTime(duration/2)
, window(window){
	if (iconTexture.loadFromFile(icon_loc)) {
		iconSprite.setTexture(iconTexture);
		centreIcon();
		valid = true;
	}
}

/*!
 * \brief Runs the splash screen for the specified duration using a thread to handle the animation
 */
void SplashScreen::run() {

	if (!valid)
		return;

	animation();
	size_t startTime = clock();
	
	while ((clock() - startTime) / (CLOCKS_PER_SEC / 1000) <= duration){
		window.clear(); //Clears to black
		window.draw(iconSprite);
		window.display();
	}
}

/*!
 * \brief centres icon to screen
 */
void SplashScreen::centreIcon(){
	sf::Vector2f windowSize = Territorial::getWindowSize();

	iconSprite.setOrigin(iconTexture.getSize().x / 2.f, iconTexture.getSize().y / 2.f);
	iconSprite.setPosition(Territorial::getWindowCentre().x, Territorial::getWindowCentre().y);
}

/*!
 * \brief handles the animation of the splash screen
 */
void SplashScreen::animation() {

	std::thread animation(&SplashScreen::fade, this);
	animation.detach();
}

/*!
 * \brief used in thread to fade in and out
 * \TODO - add sleep in between fading in and out - resolve whitewash bug this introduces
 *		 - fix white screen before splash screen loads
 *		 - determine whether splash screen should just be drawable
 *		 - add event handling to splash screen
 */
void SplashScreen::fade() {

	size_t startTime = clock();

	//Smooth running
	sf::Clock clockSF;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	float speed = 255.f / fadeTime;

	//Fade In
	float fade = 0;
	while ((clock() - startTime) / (CLOCKS_PER_SEC / 1000) <= fadeTime) {
		
		timeSinceLastUpdate += clockSF.restart();
		while (timeSinceLastUpdate > Territorial::TIME_PER_FRAME) {
			timeSinceLastUpdate -= Territorial::TIME_PER_FRAME;
			fade += speed * Territorial::TIME_PER_FRAME.asMilliseconds();
			iconSprite.setColor(sf::Color(255, 255, 255, fade));
		}
	}

	//Fade out
	startTime = clock(); //Reset clock
	while ((clock() - startTime) / (CLOCKS_PER_SEC / 1000) <= fadeTime) {
		timeSinceLastUpdate += clockSF.restart();
		while (timeSinceLastUpdate > Territorial::TIME_PER_FRAME) {
			timeSinceLastUpdate -= Territorial::TIME_PER_FRAME;
			fade -= speed * Territorial::TIME_PER_FRAME.asMilliseconds();
			iconSprite.setColor(sf::Color(255, 255, 255, fade));
		}
	}
}
