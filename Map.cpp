#include "Map.h"
#include "Territorial.h"
#include "Reader.h"
#include "Mouse.h"

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

	if (inFocus != nullptr)
		target.draw(inFocus->getOverlay());

	for (Territory t : territories) {
		target.draw(t.getUnitDisplay());
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

		std::map<int, sf::FloatRect>::iterator it;
		for (it = continentBounds.begin(); it != continentBounds.end(); it++) {
			it->second.left += mapBackSprite.getPosition().x;
			it->second.top += mapBackSprite.getPosition().y;
		}
	}
	else {
		return false; //TODO print ERR
	}
	
	//Load map image (whole)
	if (!mapBackTexture.loadFromFile(loc))
		return false;
	mapBackSprite.setTexture(mapBackTexture);

	setupMap();

	//Load territory overlays and set counter
	for (int i = 0; i < territories.size(); i++) {
		if (territories.at(i).getOverlaySet())
			territories.at(i).loadOverlay(mapBackSprite.getPosition());

		//Breaks up territories by continent	- create vector for each continent
		while (mapSplit.size() < territories.at(i).getContinent() + 1) { //Make mapSplit vector correct size (size == no. continents)
			mapSplit.push_back(std::vector<Territory*>());
		}
		mapSplit.at(territories.at(i).getContinent()).push_back(&territories.at(i));
		territories.at(i).positionUnitCounter(mapBackSprite.getPosition());
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

	std::map<int, sf::FloatRect>::iterator it;
	for (it = continentBounds.begin(); it != continentBounds.end(); it++) {
		it->second.left += mapBackSprite.getPosition().x;
		it->second.top += mapBackSprite.getPosition().y;
	}
}


/*
* /////////////////////// EVENT METHODS ///////////////////////
*/


/*!
 * \brief standard method, handles any events of concern to the Map
 */
Map::MapEvents Map::handleEvents(sf::Event event) {
	sf::Vector2f mousePos(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);

	MapEvents mapEvent = MapEvents::None;	//Reset event

	switch (event.type) {
	case sf::Event::MouseMoved: {

		sf::Vector2i mousePos = Mouse::getMousePosition();
		sf::Vector2f worldPos = Mouse::mapPixelToCoords(mousePos, mapView);
		handleMouseMove(); break;
	}
	}

	return mapEvent;
}


/*!
 * \brief this method is responsible for identifying events triggered by mouse movement over the map
 */
void Map::handleMouseMove() {
	/* Get relevant mouse data */
	sf::Vector2i mousePos = Mouse::getMousePosition();
	sf::Vector2f worldPos = Mouse::mapPixelToCoords(mousePos, mapView);

	/* If mouse is over a continent, check for territory collision in that continent */
	std::map<int, sf::FloatRect>::iterator it;
	for (it = continentBounds.begin(); it != continentBounds.end(); it++) {
		if (it->second.contains(worldPos)) {
			if (territoryColision(it->first, worldPos))
				return;
		}
	}
}


/*!
 * \brief This method is used to check if mouse is over a terriotry IN A GIVEN CONTINENT
 * \param continentID : used to restrict search to a single continent
 */
bool Map::territoryColision(int continentID, sf::Vector2f worldPos) {

	/* Check mouse is within bounds of current territory */
	for (Territory* t : mapSplit.at(continentID)){

		/* Pixel perfect detection */
		if (t->getOverlay().getGlobalBounds().contains(worldPos)) {
			if (t->isOver(worldPos)) {
				this->inFocus = t;
				return true;
			}
		}
	}
	this->inFocus = nullptr;
	return false;
}
