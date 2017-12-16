/*
 * \file View.h : contains declaration of abstrace View base class
 */
#ifndef STATE_H
#define STATE_H

#include <SFML\Graphics.hpp>
#include "Identifiers.h"

class View {

	private:
		sf::RenderWindow* window;
	
	protected:
		sf::RenderWindow* getWindow() { return window; };

	public:
		/* Constructor */
		View(sf::RenderWindow* window) { this->window = window; };

		virtual void render() = 0;
		virtual Identifiers::StateChange handleEvents(sf::Event) = 0;

};

#endif // !STATE_H
