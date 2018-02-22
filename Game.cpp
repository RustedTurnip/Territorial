#include "Game.h"

/*!
 * Constructor
 */
Game::Game(){

}

/*!
 * \brief responsible for loading/setting up game- map related loading is handled within Map::load()
 * \TODO : call load function in constructor
		 : pass map location to map
 */
bool Game::load() {

	Reader reader;
	
	if (!map.load("res/maps/world/world.png")) //Eventually there will be map selection
		return false;

	return false;
}

/*!
 * \brief responsible for loading game data in from file
 */
void Game::drawGame(sf::RenderWindow& window) {
	window.draw(map);
}

/*
* \brief responsible for handling game events
*/
void Game::handleEvents(sf::Event event){
	map.handleEvents(event);
}