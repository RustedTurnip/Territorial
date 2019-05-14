#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Territorial.h"
#include "Territory.h"
#include <set>

class Player {

	public:
		static enum PlayerType {Human, PC};

	protected:
		static size_t playerCount;

		PlayerType playerType;
		size_t playerNum;
		sf::Color playerColour;

		size_t reserves;
		bool out = false;
		
	public:
		enum PlayerAction {PlaceUnit, Attack, Fortify, EndTurn, DoNothing}; //For now units will be placed one at a time
		static const sf::Color COLOURS[Territorial::PLAYER_MAXIMUM];


	public:
		/* Constructor - Destructor */
		Player();
		~Player();

		size_t getPlayerNum() { return playerNum; };
		sf::Color getPlayerColour() { return playerColour; };
		void setReserves(size_t amount) { reserves = amount; };
		void allocateUnit() { reserves--; };
		size_t getReserves() { return reserves; };
		PlayerType getPlayerType() { return playerType; };

		//TEMP - to force polymorphism
		virtual void virtual_func() {};
		bool isPLayerOut() { return out; };
		bool knockOutPlayer() { out = true; };
};

#endif /* !PLAYER_H */