#include "ViewManager.h"

/*
	Constructor -- Destructor
*/
ViewManager::ViewManager(sf::RenderWindow* window) 
: window(window){

	loadView(Identifiers::MainMenu);	//Load Main Menu first
}

ViewManager::~ViewManager() {

}


/*
	Methods
*/
void ViewManager::render() {

	currentState->render();
}

void ViewManager::handleEvents(sf::Event event) {

	Identifiers::StateChange stateChange;
	stateChange = currentState->handleEvents(event);
	
	if (stateChange == Identifiers::StateChange::DoNothing)
		return;

	loadView(stateChange);
}


/*
	Load screens
*/
void ViewManager::loadView(Identifiers::StateChange state) {

	switch (state) {
	case Identifiers::StateChange::PlayGame: {
		game = new GameView(window);
		currentState = game; break;
	}
	case Identifiers::StateChange::MainMenu: {
		mainMenu = new MenuView(window);
		currentState = mainMenu; break;
	}
	}
}
