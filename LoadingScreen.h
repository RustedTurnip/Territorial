/*!
 * \file Loading.h charged with housing the Loading class declaration
 * \author Samuel A. Wilcox
 */
#ifndef LOADING_SCREEN_H
#define LOADING_SCREEN_H

#include <thread>
#include <SFML\Graphics.hpp>

/*!
	\brief this class provides a loading screen for transitional periods
*/
class LoadingScreen {

	private:
		sf::RenderWindow* window;
		static bool isRunning;// = false;

		void initialise();
		void animation();

		/* Attributes */
		sf::Font font;	//Will be changed when global resources implemented
		sf::Text text;

	public:
		/* Constructor -- Destructor */
		LoadingScreen(sf::RenderWindow*);

		void terminate() { isRunning = false; };
		void run();	/*!< runs the Loading Screen */

		static bool getIsRunning() { return isRunning; };
};

#endif // !LOADING_SCREEN_H
