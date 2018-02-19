#include "Map.h"
#include "Territorial.h"
#include "Reader.h"

/*!
 * Constructor
 */
Map::Map() {

}

/*!
 * \brief inherited from sf::Drawable, this method makes the class.. Drawable
 */
void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	
	target.setView(mapView);
	target.draw(mapBackSprite);

	for (int i = 0; i < territories.size(); i++) {
		target.draw(territories.at(i).getOverlay());
	}

	target.setView(target.getDefaultView());	//Change back (to draw other guis over top)
}

/*
 * /////////////////////// INITIALISATION ///////////////////////
 */

/*!
 * \brief loads in Map and initialises everything
 */
bool Map::load(std::string loc) {
	//Load map text data
	Reader reader;
	std::string mapLoc = "res/maps/world/AdjacencyListCoords.txt";//Temp - with line below will be single loc of map file
	std::string coordsLoc = "res/maps/world/ContinentBounds.txt";//Temp
	if (reader.readAll(mapLoc, coordsLoc)) {
		territories = reader.getVertices();
		continentBounds = reader.getContinentBounds();
	}
	else {
		return false; //TODO print ERR
	}
	
	//Load map image (whole)
	if (!mapBackTexture.loadFromFile(loc))
		return false;
	mapBackSprite.setTexture(mapBackTexture);

	setupMap();

	//Load territory overlays
	for (int i = 0; i < territories.size(); i++) {
		if (territories.at(i).getOverlaySet())
			territories.at(i).loadOverlay(mapBackSprite.getPosition());

		//Breaks up territories by continent	- create vector for each continent
		while (mapSplit.size() < territories.at(i).getContinent() + 1) { //Make mapSplit vector correct size (size == no. continents)
			mapSplit.push_back(std::vector<Territory*>());
		}
		mapSplit.at(territories.at(i).getContinent()).push_back(&territories.at(i));
	}

	return true;
}

/*!
 * \brief configures map
 */
void Map::setupMap() {
	//SetView
	sf::Vector2f windowSize = Territorial::getWindowSize();
	float multiplier = mapBackTexture.getSize().x / windowSize.x;	//Make it so width of map takes up entire width of screen
	
	if ((mapBackTexture.getSize().y / multiplier) > windowSize.y)	//If map off screen (on Y axis)
		multiplier = mapBackTexture.getSize().y / windowSize.y;	//Then to make it fit work out multiplier for y (will definitely fit if other didnt)

	mapView.reset(sf::FloatRect(0, 0, windowSize.x, windowSize.y));
	mapView.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

	zeroZoom = multiplier;
	mapView.zoom(zeroZoom);

	//SetMapSprite
	mapBackTexture.setSmooth(true);
	sf::Vector2f toSet(Territorial::getWindowCentre().x - (mapBackTexture.getSize().x / 2),
		Territorial::getWindowCentre().y - (mapBackTexture.getSize().y / 2));
	mapBackSprite.setPosition(toSet);
}