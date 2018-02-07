/*!
 * \file Loading.h charged with housing the Loading class declaration
 * \author Samuel A. Wilcox
 */
#ifndef LOADING_SCREEN_H
#define LOADING_SCREEN_H

#include <thread>
#include <atomic>
#include <SFML\Graphics.hpp>

/*!
	\brief this class provides a loading screen for transitional periods
*/
class LoadingScreen {

	private:
		sf::RenderWindow* window;
		static std::atomic<bool> isRunning;// = false;

		void initialise();
		void animation();

		/* Attributes */
		sf::Font font;	//Will be changed when global resources implemented
		sf::Text text;
		std::thread screenThread;

	public:
		/* Constructor -- Destructor */
		LoadingScreen(sf::RenderWindow*);

		void terminate() { isRunning = false; };
		void run();	/*!< runs the Loading Screen */

		static bool getIsRunning() { return isRunning.load(); };
};

#endif // !LOADING_SCREEN_H
