/*!
 * \file Game.h : this file contains the declaration for the class Game
 */
#ifndef GAME_H
#define GAME_H

#include "Reader.h"

/*!
 * \brief This class is responsible for holding the game itself and controlling the games flow
 */
class Game
{
private:
	/* Member variables */
	std::vector<Territory> territories;
	std::map<int, sf::FloatRect> continentBounds;

public:
	/* Constructor */
	Game();

	/* Getters */
	std::vector<Territory>& getTerritories() { return territories; };

	/* Other Methods */
	bool load();
};

#endif // !GAME_H
