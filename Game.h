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
	std::vector<Territory> territories;
	std::map<int, sf::FloatRect> continentBounds;
	Map map; /*< Stores the map used for game */

public:
	/* Constructor */
	Game();

	/* Getters */
	std::vector<Territory>& getTerritories() { return territories; };

	/* Other Methods */
	bool load();

	/* TEMP METHODS */
	void drawGame(sf::RenderWindow&); /*!< \todo Consider if Game should be sf::drawable*/
};

#endif // !GAME_H
