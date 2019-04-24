#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Territorial.h"
#include "Territory.h"
#include <set>

class Player {

	protected:
		static size_t playerCount;

		size_t playerNum;
		sf::Color playerColour;

		size_t initialAllocation;

		//std::set<std::string, Territory&> territories = std::set<std::string, Territory&>();
		
	public:
		enum PlayerAction {PlaceUnit, Attack, Fortify, EndTurn, DoNothing}; //For now units will be placed one at a time
		static const sf::Color COLOURS[Territorial::PLAYER_MAXIMUM];


	public:
		/* Constructor - Destructor */
		Player();
		~Player();

		size_t getPlayerNum() { return playerNum; };
		sf::Color getPlayerColour() { return playerColour; };
		void setInitialAllocationAmount(size_t amount) { initialAllocation = amount; };
		void allocateUnit() { initialAllocation--; };
		size_t getInitialAllocation() { return initialAllocation; };
};

#endif /* !PLAYER_H */