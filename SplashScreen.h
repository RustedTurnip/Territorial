/*!
 * \file SplashScreen.h : this file holds the class declaration of SplashScreen
 */
#ifndef SPLASH_SCREEN_H
#define SPLASH_SCREEN_H

#include <string>
#include <thread>
#include <SFML\Graphics.hpp>

/*!
 * \brief This class offers an easy implementation of a splash screen
 */
class SplashScreen {
	
	private:
		/* Graphics members*/
		sf::Texture iconTexture;
		sf::Sprite iconSprite;
		sf::RenderWindow& window;

		size_t duration;
		bool valid = false;
		size_t fadeTime;
		std::thread animationThread;

		/* Member methods */
		void centreIcon();
		void animation();
		void fade();

	public:
		/* Constructor */
		SplashScreen(std::string, size_t, sf::RenderWindow&);
		
		void run();
};

#endif // !SPLASH_SCREEN_H
