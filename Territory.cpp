#include "Territory.h"
#include <iostream>

/*
Constructor -- Destructor
*/

/*!
\brief Default constructor
\param name
\parblock
should be set when class is created, if otherwise, then error has occured
default value = "Error"
*/
Territory::Territory(std::string name, int continent, int territoryID, int heuristic, std::vector<int> edges)
	: name(name)
	, units(0)
	, territoryID(territoryID)
	, heuristic(heuristic){

	this->continent = static_cast<Identifiers::Continent>(continent);	//Set conntinent enum
	setNeighbours(edges);
}

/*!
	\brief constructor that additionally sets the Terrirories coordinates (for overlay)
*/
Territory::Territory(sf::Vector2f coords, std::string name, int continent, int territoryID, int heuristic, std::vector<int> edges)
	: name(name)
	, units(0)
	, territoryID(territoryID)
	, coords(coords) 
	, heuristic(heuristic){

	overlaySet = true;
	this->continent = static_cast<Identifiers::Continent>(continent);	//Set conntinent enum
	setNeighbours(edges);
	//loadOverlay();
}


/*!
	\brief copy constructor
	\TODO add overlay sprite loading (if overlaySet == true)
*/
Territory::Territory(const Territory& obj) {
	units = obj.getUnits();
	name = obj.getName();
	continent = obj.getContinent();
	territoryID = obj.getTerritoryID();
	overlaySet = obj.getOverlaySet();
	neighbours = obj.getNeighbours();
	heuristic = obj.getHeuristic();

	/* TEMP - replcae with copying of object (add copy constructor to UnitDisplay class) */
	unitDisplay.setColour(obj.getUnitDisplay().getColour());
	unitDisplay.setNumber(obj.getUnitDisplay().getUnits());
	unitDisplay.setPosition(obj.getUnitDisplay().getPosition());

	if (overlaySet)
		coords = obj.getCoords();
}


/**/
Territory::~Territory() {

}/**/


/*!
	\brief used in battle to remove units
*/
bool Territory::dealDamage(float damage) {

	units -= damage;

	if (this->units <= 0)	//While units left to defend
		return false;

	return true;
}


/*!
	\brief used to load overlay image from file
*/
bool Territory::loadOverlay(sf::Vector2f offSet) {

	try {
		std::string loc = "res/maps/world/CountryOverlays/";
		loc += std::to_string(continent) + "/";
		loc += std::to_string(territoryID) + ".png";

		if (!overlayText.loadFromFile(loc))
			throw std::runtime_error("Failed to load file \"" + territoryID);// + '.png');

		overlayImage = overlayText.copyToImage();	//For pixel perfect collision
		overlaySprite.setTexture(overlayText);
		overlaySprite.setPosition(coords.x + offSet.x, coords.y + offSet.y);
		
		loadShape(offSet);

		return true;
	}
	catch (std::runtime_error exception) {
		std::cerr << exception.what() << std::endl;
		return false;
	}
}

/*!
	\brief 
*/
bool Territory::loadShape(sf::Vector2f offSet) {
	
	try {
		std::string loc = "res/maps/world/CountryImages/";
		loc += std::to_string(continent) + "/";
		loc += std::to_string(territoryID) + ".png";

		if (!territoryShapeText.loadFromFile(loc))
			throw std::runtime_error("Failed to load file \"" + territoryID);// + '.png');

		territoryShapeImage = territoryShapeText.copyToImage();	//For pixel perfect collision
		territoryShapeSprite.setTexture(territoryShapeText);
		territoryShapeSprite.setPosition(coords.x + offSet.x, coords.y + offSet.y);

		return true;
	}
	catch (std::runtime_error exception) {
		std::cerr << exception.what() << std::endl;
		return false;
	}
}

bool Territory::isOver(sf::Vector2f worldPos) {

	sf::Vector2f mousePos;

	//Work out local position by getting difference
	mousePos.x = worldPos.x - overlaySprite.getPosition().x;
	mousePos.y = worldPos.y - overlaySprite.getPosition().y;

	if (overlayImage.getPixel(mousePos.x, mousePos.y).a > 0)
		return true;

	return false;
}

void Territory::positionUnitCounter(sf::Vector2f offset) {

	sf::Vector2f position = sf::Vector2f(coords.x + offset.x, coords.y + offset.y);
	position.x += overlayText.getSize().x / 2;
	position.y += overlayText.getSize().y / 2;

	unitDisplay.setPosition(position);
}

void Territory::setNeighbours(std::vector<int> edges) {
	for (int i : edges) {
		neighbours.insert(i);
	}
}

bool Territory::isNeigbour(int id) {

	if (neighbours.find(id) != neighbours.end())
		return true;
	return false;
}

