#include "GameView.h"

/*
 * \brief GameView Constructor
 */
GameView::GameView(sf::RenderWindow* window)
: View(window){ //Call Super Constructor

}

/*
 * \brief draws GameView to window
 */
void GameView::render() {
	getWindow()->clear(sf::Color::Black);	//To test navigation from MenuView
}

/*
 * \brief Handles Events relavent to the GameView
 */
Identifiers::StateChange GameView::handleEvents(sf::Event event) {
	return Identifiers::DoNothing;
}
