#include "Game.h"
#include "Territorial.h"
#include "HumanPlayer.h"

const size_t Game::initialAmounts[Territorial::PLAYER_MAXIMUM - 1] = {40, 35, 30, 25};

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

	setPlayers();
	map.setCurrentPlayer(players.at(0));
	return true;
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
	Map::MapEvents mapEvent = map.handleEvents(event);

	switch (mapEvent) {
	case Map::MapEvents::NextPlayer : {
		map.setCurrentPlayer(nextPlayer()); break;
	}
	}
}

void Game::setPlayers() {
	for (int i = 0; i < Territorial::PLAYER_MAXIMUM; i++) {
		if (Territorial::currentPlayers[i] == 2)
			return;
		else if (Territorial::currentPlayers[i] == 0) {
			players.push_back(new HumanPlayer());
		}
		else if (Territorial::currentPlayers[i] == 1) {
			players.push_back(new HumanPlayer()); //TODO Change to PCPlayer
		}
	}

	int playerNum = players.size();

	for (Player* player : players) {
		player->setInitialAllocationAmount(Game::initialAmounts[playerNum - 2]); //Set initial amounts
	}
}

Player* Game::nextPlayer() {
	
	//Move on to main game if allocation finished
	if (map.getCurrentState() == Map::MapState::UnitDistribution) {
		bool progress = true;
		for (Player* p : players) {
			if (p->getInitialAllocation() != 0)
				progress = false;
		}

		if (progress)
			map.setCurrentState(Map::MapState::Game);
	}

	//Get next player
	if (currentPlayer == (players.size() - 1))
		currentPlayer = 0;
	else
		currentPlayer++;
	return players.at(currentPlayer);
}