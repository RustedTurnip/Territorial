/*!
	\file Territory.h
	\author Samuel A. Wilcox
	\brief This file houses the declaration of the Territory class
	\date 27/04/2017
*/
#ifndef TERRITORY_H
#define TERRITORY_H

#include <SFML\Graphics.hpp>
#include <string>
#include <set>
#include "Identifiers.h"
#include <math.h>
#include "UnitDisplay.h"

/*!
	\brief This class is the equivalent of a country in the game RISK

*/
class Territory {

	private:
		/* Attributes */
		std::string name;	/*!< Each Territory has a unique name */
		int territoryID;
		Identifiers::Continent continent;

		sf::Texture overlayText;
		sf::Sprite overlaySprite;
		sf::Image overlayImage;

		sf::Texture territoryShapeText;
		sf::Sprite territoryShapeSprite;
		sf::Image territoryShapeImage;

		UnitDisplay unitDisplay;

		sf::Vector2f coords;
		bool overlaySet = false;

		size_t currentPlayer;

		std::set<int> neighbours; /*!< Effectively makes this class Adjacency List for Graph, using Territory IDs  */

		/* In Game Attributes */
		size_t units;	/*!< Each Territory has a number of units, for battle */
		bool allocated = false; //For unit placement
		
		void setNeighbours(std::vector<int>); //TEMP
		int heuristic;

	public:
		/* Methods */
		bool loadOverlay(sf::Vector2f offset);
		bool loadShape(sf::Vector2f offset);
		

	public:
		/* Constructor -- Destructor */
		//Territory(std::string = "Error");
		Territory(std::string = "Error", int = 6, int = -1, int = 1, std::vector<int> = std::vector<int>());	//6 = ContinentError
		Territory(sf::Vector2f, std::string = "Error", int = 6, int = -1, int = 1, std::vector<int> = std::vector<int>());	//6 = ContinentError
		Territory(const Territory&);	//Copy constructor
		~Territory();

		/* Getters */
		std::string getName() const { return name; };
		Identifiers::Continent getContinent() const { return continent; };
		float getUnits() const { return std::ceil(units); };
		int getTerritoryID() const { return territoryID; };
		bool getOverlaySet() const { return overlaySet; };
		sf::Vector2f getCoords() const { return coords; };
		const UnitDisplay& getUnitDisplay() const { return unitDisplay; };
		const sf::Sprite& getOverlay() const { return overlaySprite; };
		std::set<int> getNeighbours() const { return neighbours; };
		int getHeuristic() const { return heuristic; };

		const sf::Sprite& getShape() const { return territoryShapeSprite; };

		bool isOver(sf::Vector2f);
		bool isAllocated() { return allocated; };
		size_t getPlayer() { return currentPlayer; };

		/* Setters */
		void setUnits(size_t units) { this->units = units; unitDisplay.setNumber(units); };
		//void addUnits(float units) { this->units += units; };
		bool dealDamage(float);
		void setAllocated() { allocated = true; };
		void setUnitDisplayColour(sf::Color colour) { unitDisplay.setColour(colour); };

		void positionUnitCounter(sf::Vector2f);
		void setPlayer(size_t playerNum) { currentPlayer = playerNum; };

		bool isNeigbour(int);
		
};

#endif // !TERRITORY_H
