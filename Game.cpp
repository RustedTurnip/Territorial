#include "Game.h"
#include "Territorial.h"
#include "HumanPlayer.h"
#include "PCPlayer.h"
#include "Mouse.h"

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
	loadHeadsUp();
	map.setCurrentPlayer(players.at(0));
	return true;
}

void Game::update() {

	//TEMP - HANDLE PC PLAYER ACTIONS
	if (players.at(currentPlayer)->getPlayerType() == Player::PC) {

		PCPlayer* current = dynamic_cast<PCPlayer*>(players.at(currentPlayer));
		//if (map.getCurrentState() == Map::MapState::Selection) {
		//
		//	if(!pcTurnActive && !pcTurnActiveLast){ //If turn hasn't already started, start it
		//		current->selectTerritory();
		//		pcTurnActive = true;
		//		pcTurnActiveLast = true;
		//	}
		//	else if (pcTurnActiveLast == true && pcTurnActive == false) { //If turn was active last iteration but not anymore
		//		
		//		//Check that selection is finished
		//		bool flag = false;
		//		for (auto a : Territorial::map_global) {
		//			if (!a.second.isAllocated())
		//				flag = true;
		//		}
		//		if (!flag)
		//			map.setCurrentState(Map::MapState::UnitDistribution);
		//		
		//		nextPlayer();
		//		pcTurnActive = false;
		//		pcTurnActiveLast = false;
		//	}
		//	else if (current->isTurnOver()) {
		//		current->endTurn();
		//		pcTurnActive = false;
		//	}
		//}
		//else if (map.getCurrentState() == Map::MapState::UnitDistribution) {
		//	if (!pcTurnActive && !pcTurnActiveLast) { //If turn hasn't already started, start it
		//		current->placeUnit();
		//		pcTurnActive = true;
		//		pcTurnActiveLast = true;
		//	}
		//	else if (pcTurnActiveLast == true && pcTurnActive == false) { //If turn was active last iteration but not anymore

		//		//Check that selection is finished
		//		if (current->getPlayerNum() + 1 == players.size()) {
		//			if(current->getReserves() == 0)
		//				map.setCurrentState(Map::MapState::GamePlacement);
		//		}					

		//		nextPlayer();
		//		pcTurnActive = false;
		//		pcTurnActiveLast = false;
		//	}
		//	else if (current->isTurnOver()) {
		//		current->endTurn();
		//		pcTurnActive = false;
		//	}
		//}
		//else if (map.getCurrentState() == Map::MapState::GamePlacement) {
		//	if (!pcTurnActive && !pcTurnActiveLast) { //If turn hasn't already started, start it
		//		current->placeUnit();
		//		pcTurnActive = true;
		//		pcTurnActiveLast = true;
		//	}
		//	else if (pcTurnActiveLast == true && pcTurnActive == false) { //If turn was active last iteration but not anymore

		//		//Check that selection is finished
		//		if (current->getReserves() == 0 && map.getCurrentState() == Map::MapState::UnitDistribution){
		//			map.setCurrentState(Map::MapState::GamePlacement);
		//		}
		//		if(current->getReserves() <= 0)
		//			map.setCurrentState(Map::MapState::GameBattle);
		//		pcTurnActive = false;
		//		pcTurnActiveLast = false;
		//	}
		//	else if (current->isTurnOver()) {
		//		current->endTurn();
		//		pcTurnActive = false;
		//	}
		//}
		//else if (map.getCurrentState() == Map::MapState::GameBattle) {
		//	if (!pcTurnActive && !pcTurnActiveLast) { //If turn hasn't already started, start it
		//		current->battle();
		//		pcTurnActive = true;
		//		pcTurnActiveLast = true;
		//	}
		//	else if (pcTurnActiveLast == true && pcTurnActive == false) { //If turn was active last iteration but not anymore

		//		map.setCurrentState(Map::MapState::GamePlacement);
		//		nextPlayer();
		//		pcTurnActive = false;
		//		pcTurnActiveLast = false;
		//	}
		//	else if (current->isTurnOver()) {
		//		current->endTurn();
		//		pcTurnActive = false;
		//	}
		//}
		if (map.getCurrentState() == Map::MapState::Selection) {
			
			current->selectTerritory();
			
			//Check that selection is finished
			bool flag = false;
			for (auto a : Territorial::map_global) {
				if (!a.second.isAllocated())
					flag = true;
			}
			if (!flag)
				map.setCurrentState(Map::MapState::UnitDistribution);
			
			nextPlayer();
		}
		else if (map.getCurrentState() == Map::MapState::UnitDistribution) {
			current->placeUnit();

			if (current->getReserves() <= 0) {
				map.setCurrentState(Map::MapState::GamePlacement);
				allocationAmount = 3;
			}

			nextPlayer();
		}
		else if (map.getCurrentState() == Map::MapState::GamePlacement) {
			current->placeUnit();
			if (current->getReserves() == 0)
				map.setCurrentState(Map::MapState::GameBattle);
		}
		else if (map.getCurrentState() == Map::MapState::GameBattle){
			current->battle();
			
			//TEMP
			//std::vector<std::pair<int, bool>> out = std::vector<std::pair<int, bool>>();
			//std::cout << "PLAYER SIZE: " << players.size()  << std::endl;
			//for (int i = 0; i < players.size(); i++) {
			//	out.push_back(std::pair<int, bool>(i, true));
			//}
			//for (auto a : Territorial::map_global) {
			//	std::cout << "PLAYER NO: " << a.second.getPlayer() << std::endl;
			//	out.at(a.second.getPlayer()-1).second = false;
			//}
			//for (auto i : out) {
			//	if (i.second == false)
			//		players.at(i.first)->knockOutPlayer();
			//}
			//!TEMP
			map.setCurrentState(Map::MapState::GamePlacement);
			nextPlayer();
		}
	}
	//TEMP

	if (fortifyOverlay.isFortifyCommit()) {
		nextPlayer();
		fortifyOverlay.resetFortifyCommit();
	}
}

/*!
 * \brief responsible for loading game data in from file
 */
void Game::drawGame(sf::RenderWindow& window) {
	window.draw(map);

	setStatusString(); //TEMP - Move to somewhere else
	window.draw(gameStageDisplay);

	for (int i = 0; i < playerTracker.size(); i++) {
		window.draw(playerTracker.at(i).second);
		if (currentPlayer + 1 == players.at(i)->getPlayerNum())
			window.draw(playerTracker.at(i).first);
	}

	if (nextButtonActive())
		window.draw(nextButton);

	if (battleOverlay.isOpen())
		window.draw(battleOverlay);
	if (fortifyOverlay.isOpen())
		window.draw(fortifyOverlay);
}

/*
* \brief responsible for handling game events
*/
void Game::handleEvents(sf::Event event){

	//TEMP
	if (players.at(currentPlayer)->getPlayerType() == Player::PC) {
		return;
	}
	//!TEMP

	if (battleOverlay.isOpen()) {
		battleOverlay.handleEvents(event);
		return;
	}
	if (fortifyOverlay.isOpen()) {
		fortifyOverlay.handleEvents(event);
		return;
	}

	if (handleGameEvents(event))
		return;

	Map::MapEvents mapEvent = map.handleEvents(event);
	if (mapEvent != Map::MapEvents::None) {
		handleMapEvent(mapEvent);
	}
}

bool Game::handleGameEvents(sf::Event event) {

	switch (event.type) {
	case sf::Event::MouseMoved: {
		return handleMouseMove();
	}
	case sf::Event::MouseButtonReleased: {
		return handleMouseClick();
	}
	}

	return false;
}

bool Game::handleMouseMove() {
	
	sf::Vector2i rawPos = Mouse::getMousePosition();
	sf::Vector2f mousePos = sf::Vector2f(rawPos.x, rawPos.y);

	if (nextButton.getGlobalBounds().contains(mousePos)) {
		nextButton.setInFocus(true);
		return true;
	}
	else
		nextButton.setInFocus(false);

	return false;
}

bool Game::handleMouseClick() {

	sf::Vector2i rawPos = Mouse::getMousePosition();
	sf::Vector2f mousePos = sf::Vector2f(rawPos.x, rawPos.y);

	if (nextButtonActive()) {
		if (nextButton.getGlobalBounds().contains(mousePos)) {
			if (map.getCurrentState() == Map::MapState::GameBattle) {
				map.setCurrentState(Map::MapState::GameFortification);
				return true;
			}
			else if (map.getCurrentState() == Map::MapState::GameFortification) {
				nextPlayer();
			}
		}
	}
}

bool Game::nextButtonActive() {
	if (map.getCurrentState() == Map::MapState::GameBattle ||
		map.getCurrentState() == Map::MapState::GameFortification) {
	
		if (!battleOverlay.isOpen()) {
			return true;
		}
	}

	return false;
}

void Game::loadHeadsUp() {
	setPlayerTracker();

	/* In game stage indicator */
	gameStageDisplay.setFillColor(sf::Color::Black);
	sf::Vector2f pos = sf::Vector2f(50, 0);
	pos.y = Territorial::getWindowSize().y - gameStageDisplay.getLocalBounds().height - 50;
	gameStageDisplay.setPosition(pos);

	/* Next button */
	nextButton.setText("Next");
	nextButton.setBackgroundColour(sf::Color::Black);
	nextButton.setForegroundColour(sf::Color::White);
	nextButton.setFocusBackgroundColour(sf::Color(155, 155, 155));
	nextButton.setFocusForegroundColour(sf::Color::White);
	nextButton.setOrigin(sf::Vector2f(nextButton.getSize().x / 2, nextButton.getSize().y));
	nextButton.setPosition(sf::Vector2f(Territorial::getWindowCentre().x, Territorial::getWindowSize().y - 50));
}

void Game::setPlayers() {
	for (int i = 0; i < Territorial::PLAYER_MAXIMUM; i++) {
		if (Territorial::currentPlayers[i] == 2)
			break;
		else if (Territorial::currentPlayers[i] == 0) {
			players.push_back(new HumanPlayer());
		}
		else if (Territorial::currentPlayers[i] == 1) {
			players.push_back(new PCPlayer());
		}
	
	}

	int playerNum = players.size();

	for (Player* player : players) {
		player->setReserves(Game::initialAmounts[playerNum - 2]); //Set initial amounts
	}
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

void Game::setStatusString() {
	Map::MapState state = map.getCurrentState();

	switch (state) {
	case Map::MapState::Selection: {
		gameStageDisplay.setString("Selection"); break;
	}
	case Map::MapState::UnitDistribution: {
		gameStageDisplay.setString("Distribution"); break;
	}
	case Map::MapState::GamePlacement: {
		gameStageDisplay.setString("Placement"); break;
	}
	case Map::MapState::GameBattle: {
		gameStageDisplay.setString("Battle"); break;
	}
	case Map::MapState::GameFortification: {
		gameStageDisplay.setString("Fortification"); break;
	}
	}
}

void Game::handleMapEvent(Map::MapEvents event) {
	
	switch (event) {
	//HANDLE PLACEMENT EVENT
	case Map::MapEvents::Placement: {
		Map::MapState state = map.getCurrentState();
		
		//Handle Selection
		if (state == Map::MapState::Selection) {
			nextPlayer();
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
		nextPlayer();
		}

		if (state == Map::MapState::GamePlacement) {
			if (players.at(currentPlayer)->getReserves() == 0) {
				map.setCurrentState(Map::MapState::GameBattle);
			}
		}
		break;
	}

	case Map::MapEvents::Battle: {
		battleOverlay.openWindow(*map.friendlySelectionOne, *map.enemySelectionOne);
		break;
	}

	case Map::MapEvents::Fortify: {
		fortifyOverlay.openWindow(*map.friendlySelectionOne, *map.friendlySelectionTwo);
		break;
	}
	}

}

void Game::nextPlayer() {

	//Get next player
	if (currentPlayer == (players.size() - 1))
		currentPlayer = 0;
	else
		currentPlayer++;

	if (players.at(currentPlayer)->isPLayerOut()) {
		nextPlayer();
		return;
	}

	int bonus = 0;

	//TEMP
	int fill[6] = {0,0,0,0,0,0};
	for (auto a : Territorial::map_global) {
		if (a.second.getPlayer() == currentPlayer) {
			fill[a.second.getContinent()] += 1;
		}
	}
	for (int i = 0; i < 6; i++) {
		if (fill[i] == CONTINENT_SIZE[i]) {
			bonus += CONTINENT_REWARD[i];
		}
	}
	//!TEMP

	size_t units = players.at(currentPlayer)->getReserves() + allocationAmount + bonus;
	players.at(currentPlayer)->setReserves(units);
	
	//Move to next player
	map.setCurrentPlayer(players.at(currentPlayer));

	//If we're in main game, move to next players placement
	if (map.getCurrentState() == Map::MapState::GameFortification) {
		map.setCurrentState(Map::MapState::GamePlacement);
		
		//Clear previous players selections
		map.friendlySelectionOne = nullptr;
		map.friendlySelectionTwo = nullptr;
		map.enemySelectionOne = nullptr;
	}
}