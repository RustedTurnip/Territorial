/*!
 * \file Game.h : this file contains the declaration for the class Game
 */
#ifndef GAME_H
#define GAME_H

#include "Reader.h"
#include "Map.h"
#include "Player.h"
#include "Tbutton.h"

/*!
 * \brief This class is responsible for holding the game itself and controlling the games flow
 */
class Game
{
	static const size_t initialAmounts[Territorial::PLAYER_MAXIMUM - 1];

private:
	/* Member variables */
	Map map; /*< Stores the map used for game */
	std::vector<Player*> players = std::vector<Player*>();

	void setPlayers();
	Player* nextPlayer();
	size_t currentPlayer = 0;

	std::vector<std::pair<sf::Text, Tbutton>> playerTracker;

	void setPlayerTracker();
	
public:
	/* Constructor */
	Game();

	/* Core Mthods */
	void handleEvents(sf::Event); /* Return type TBD */

	/* Other Methods */
	bool load();

	/* TEMP METHODS */
	void drawGame(sf::RenderWindow&); /*!< \todo Consider if Game should be sf::drawable*/
};

#endif // !GAME_H
