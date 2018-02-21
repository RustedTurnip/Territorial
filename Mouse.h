/*!
	\file this file houses the declaration of the Mouse class
	\author Samuel A. Wilcox
	\date 22/05/2017
*/
#ifndef MOUSE_H
#define MOUSE_H

#include <SFML\Graphics.hpp>

/*!
	\class Mouse class, uses static methods to make mouse details available at all times, i.e. mouse position
*/

/**/
class Mouse {

	private:
		static sf::RenderWindow* window;

	public:
		static void setWindow(sf::RenderWindow* windowParam) { window = windowParam; };
		static sf::Vector2i getMousePosition() { return sf::Mouse::getPosition(*window); };
		static sf::Vector2f mapPixelToCoords(sf::Vector2i mousePos, sf::View view) { return window->mapPixelToCoords(mousePos, view); };

};/**/

#endif // !MOUSE_H
