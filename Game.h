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
#include "FortifyOverlay.h"

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
	FortifyOverlay fortifyOverlay = FortifyOverlay();
	std::vector<Player*> players = std::vector<Player*>();
	size_t currentPlayer = 0;
	
	/* Other variables */
	size_t allocationAmount = 0; //Number of units to place at the beginning of a turn

	/* Initialisation methods */
	void loadHeadsUp();
	void setPlayers();
	void setPlayerTracker();

	/* Other methods */
	void setStatusString();
	void nextPlayer();
	void handleMapEvent(Map::MapEvents);

	bool handleGameEvents(sf::Event);
	bool handleMouseMove();
	bool handleMouseClick();

	/* GUI Elements */
	std::vector<std::pair<sf::Text, Tbutton>> playerTracker;
	sf::Text gameStageDisplay = sf::Text("Selection", Territorial::mainFont, 75);
	TanimatedButton nextButton = TanimatedButton(Territorial::mainFont, sf::Vector2f(250, 50));

	bool nextButtonActive();
	
public:
	/* Constructor */
	Game();

	/* Core Mthods */
	void update();
	void handleEvents(sf::Event); /* Return type TBD */

	/* Other Methods */
	bool load();

	/* TEMP METHODS */
	void drawGame(sf::RenderWindow&); /*!< \todo Consider if Game should be sf::drawable*/
};

#endif // !GAME_H
