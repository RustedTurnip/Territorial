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
Territory::Territory(std::string name, int continent, int territoryID)
	: name(name)
	, units(100.f)
	, territoryID(territoryID){

	this->continent = static_cast<Identifiers::Continent>(continent);	//Set conntinent enum
}

/*!
	\brief constructor that additionally sets the Terrirories coordinates (for overlay)
*/
Territory::Territory(sf::Vector2f coords, std::string name, int continent, int territoryID)
	: name(name)
	, units(100.f)
	, territoryID(territoryID)
	, coords(coords) {

	overlaySet = true;
	this->continent = static_cast<Identifiers::Continent>(continent);	//Set conntinent enum
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
		std::string loc = "res/maps/CountryOverlays/";
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
		std::string loc = "res/maps/CountryImages/";
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
