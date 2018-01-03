#include "GameView.h"

/*!
 * \brief GameView Constructor
 */
GameView::GameView(sf::RenderWindow* window)
: View(window){ //Call Super Constructor

	game.load();
}

/*!
 * \brief draws GameView to window
 */
void GameView::render() {
	getWindow()->clear(sf::Color::White);	//To test navigation from MenuView
	game.drawGame(*getWindow());
}

/*!
 * \brief Handles Events relavent to the GameView
 */
Identifiers::StateChange GameView::handleEvents(sf::Event event) {
	return Identifiers::DoNothing;
}
