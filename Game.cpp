#include "Game.h"

/*!
 * Constructor
 */
Game::Game(){

}

/*!
 * \brief responsible for loading game data in from file
 * \TODO : call load function in constructor
 */
bool Game::load() {

	Reader reader;
	std::string mapLoc = "res/maps/world/AdjacencyListCoords.txt";//Temp
	std::string coordsLoc = "res/maps/world/ContinentBounds.txt";//Temp
	
	if (!map.load("res/maps/world/world.png")) //Eventually there will be map selection
		return false;

	if (reader.readAll(mapLoc, coordsLoc)) {
		territories = reader.getVertices();
		continentBounds = reader.getContinentBounds();
		return true;
	}

	return false;
}

/*!
 * \brief responsible for loading game data in from file
 */
void Game::drawGame(sf::RenderWindow& window) {
	window.draw(map);
}
