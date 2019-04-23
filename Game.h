/*!
 * \file Game.h : this file contains the declaration for the class Game
 */
#ifndef GAME_H
#define GAME_H

#include "Reader.h"
#include "Map.h"

/*!
 * \brief This class is responsible for holding the game itself and controlling the games flow
 */
class Game
{
private:
	/* Member variables */
	Map map; /*< Stores the map used for game */

/* Game Constants */
public:
	static const size_t PLAYER_MINIMUM = 2;
	static const size_t PLAYER_MAXIMUM = 5;

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
