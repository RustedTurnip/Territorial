#include "Player.h"

size_t Player::playerCount = 0;
const sf::Color Player::COLOURS[Territorial::PLAYER_MAXIMUM] = {	

	sf::Color(237, 163, 56),	//Orange
	sf::Color(16, 152, 86),		//Green
	sf::Color(104, 163, 229),	//Blue
	sf::Color(230, 241, 61),	//Yellow
	sf::Color(128, 60, 161)		//Purple
};

/* Constructor */
Player::Player() {

	playerColour = COLOURS[playerCount];
	
	Player::playerCount++;
	playerNum = Player::playerCount;
	
}

Player::~Player() {
	Player::playerCount--;
}