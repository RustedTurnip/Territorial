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

	for (int i = 0; i < playerTracker.size(); i++) {
		window.draw(playerTracker.at(i).second);
		if (currentPlayer + 1 == players.at(i)->getPlayerNum())
			window.draw(playerTracker.at(i).first);
	}

	if (battleOverlay.isOpen())
		window.draw(battleOverlay);
}

/*
* \brief responsible for handling game events
*/
void Game::handleEvents(sf::Event event){

	if (battleOverlay.isOpen()) {
		battleOverlay.handleEvents(event);
		return;
	}

	Map::MapEvents mapEvent = map.handleEvents(event);
	if (mapEvent != Map::MapEvents::None) {
		handleMapEvent(mapEvent);
	}
}

void Game::setPlayers() {
	for (int i = 0; i < Territorial::PLAYER_MAXIMUM; i++) {
		if (Territorial::currentPlayers[i] == 2)
			break;
		else if (Territorial::currentPlayers[i] == 0) {
			players.push_back(new HumanPlayer());
		}
		else if (Territorial::currentPlayers[i] == 1) {
			players.push_back(new HumanPlayer()); //TODO Change to PCPlayer
		}
	
	}

	int playerNum = players.size();

	for (Player* player : players) {
		player->setReserves(Game::initialAmounts[playerNum - 2]); //Set initial amounts
	}

	setPlayerTracker();
}

void Game::setPlayerTracker() {

	sf::Vector2f startPos = sf::Vector2f(50, 50);
	const sf::Vector2f BUTTON_SIZE = sf::Vector2f(250, 50);
	
	playerTracker = std::vector<std::pair<sf::Text, Tbutton>>();

	for (Player* p : players) {

		sf::Vector2f pos = startPos;
		if (p->getPlayerNum() != 1) {
			pos.y = p->getPlayerNum() * startPos.y;
			pos.y += (p->getPlayerNum() - 1) * 25;
		}

		std::pair<sf::Text, Tbutton> pair = std::pair<sf::Text, Tbutton>();
		pair.first = sf::Text(">", Territorial::mainFont, 45);
		pair.first.setFillColor(sf::Color::Black);
		pair.first.setPosition(pos);

		pos.x += 40;

		pair.second = Tbutton();
		std::string str = "Player " + std::to_string(p->getPlayerNum());
		pair.second.setFont(Territorial::mainFont);
		pair.second.setTextSize(28);
		pair.second.setText(str);
		pair.second.setBackgroundColour(p->getPlayerColour());
		pair.second.setSize(BUTTON_SIZE);
		pair.second.setForegroundColour(sf::Color::Black);
		pair.second.setPosition(pos);

		playerTracker.push_back(pair);
	}
}

void Game::handleMapEvent(Map::MapEvents event) {
	
	switch (event) {
	//HANDLE PLACEMENT EVENT
	case Map::MapEvents::Placement: {
		Map::MapState state = map.getCurrentState();
		
		//Handle Selection
		if (state == Map::MapState::Selection) {
			map.setCurrentPlayer(nextPlayer());
		}

		//Check if UnitDistribution Complete
		if (state == Map::MapState::UnitDistribution) {
			bool progress = true;
			for (Player* p : players) {
				if (p->getReserves() != 0)
					progress = false;
			}
			if (progress) {
				allocationAmount = 3; //When game starts, players get three units each round
				map.setCurrentState(Map::MapState::GamePlacement);
			}
		map.setCurrentPlayer(nextPlayer());
		}

		if (state == Map::MapState::GamePlacement) {
			if (players.at(currentPlayer)->getReserves() == 0) {
				map.setCurrentState(Map::MapState::GameBattle);
			}
		}
		break;
	}

	case Map::MapEvents::Battle: {
		battleOverlay.openWindow(*map.selectionAttack, *map.selectionDefence);
		break;
	}

	case Map::MapEvents::Fortification: {
		map.setCurrentPlayer(nextPlayer());
		break;
	}
	}

	
}

Player* Game::nextPlayer() {

	//Get next player
	if (currentPlayer == (players.size() - 1))
		currentPlayer = 0;
	else
		currentPlayer++;

	size_t units = players.at(currentPlayer)->getReserves() + allocationAmount;
	players.at(currentPlayer)->setReserves(units);
	return players.at(currentPlayer);
}