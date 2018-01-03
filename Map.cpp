#include "Map.h"
#include "territorial.h"

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
}

/*
/////////////////////// INITIALISATION ///////////////////////
*/

/*!
 * \brief loads in Map and initialises everything
 */
bool Map::load(std::string loc) {
	if (!mapBackTexture.loadFromFile(loc))
		return false;
	mapBackSprite.setTexture(mapBackTexture);
	setupMap();

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