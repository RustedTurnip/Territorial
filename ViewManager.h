/*!
 * \file ViewManager.h : This file houses the class declaration for ViewManager
 */
#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <SFML\Graphics.hpp>
#include "View.h"
#include "MenuView.h"
#include "GameView.h"

/*!
 * \brief This class handles the changing between 'views'
 */
class ViewManager {

		sf::RenderWindow* window;

	private:
		View* currentState;

		MenuView* mainMenu;
		GameView* game;

		//Load Screens
		void loadView(Identifiers::StateChange);	//Responsible for loading the correct view, rather than load all  at same time

	public:
		/* Constructor -- Destructor */
		ViewManager(sf::RenderWindow* = nullptr);
		~ViewManager();

		void render();
		void handleEvents(sf::Event);

};

#endif // !STATE_MANAGER_H
