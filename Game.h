/*!
 * \file Game.h : this file contains the declaration for the class Game
 */
#ifndef GAME_H
#define GAME_H

#include "Reader.h"
#include "Map.h"
#include "Player.h"
#include "Tbutton.h"
#include "BattleOverlay.h"

/*!
 * \brief This class is responsible for holding the game itself and controlling the games flow
 */
class Game
{
	static const size_t initialAmounts[Territorial::PLAYER_MAXIMUM - 1];

private:
	/* Member variables */
	Map map; /*< Stores the map used for game */
	BattleOverlay battleOverlay = BattleOverlay();
	
	std::vector<Player*> players = std::vector<Player*>();

	void loadHeadsUp();
	void setPlayers();
	void setStatusString();
	void handleMapEvent(Map::MapEvents);
	Player* nextPlayer();
	size_t currentPlayer = 0;

	size_t allocationAmount = 0; //Number of units to place at the beginning of a turn

	std::vector<std::pair<sf::Text, Tbutton>> playerTracker;
	sf::Text gameStageDisplay = sf::Text("Selection", Territorial::mainFont, 75);

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
