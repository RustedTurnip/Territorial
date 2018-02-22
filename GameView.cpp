#include "GameView.h"
#include "LoadingScreen.h"

/*!
 * \brief GameView Constructor
 */
GameView::GameView(sf::RenderWindow* window)
: View(window){ //Call Super Constructor

	LoadingScreen loading(window);
	loading.run();
	game.load();
	loading.terminate();
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
	game.handleEvents(event);
	return Identifiers::DoNothing;
}
