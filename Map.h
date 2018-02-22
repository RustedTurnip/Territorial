/*!
 * \file Map.h : This file houses the class declaration of Map
 */
#ifndef MAP_H
#define MAP_H

#include <vector>
#include <SFML\Graphics.hpp>

#include "Territory.h"

/*!
 * \brief this class represents a drawable map
 */
class Map : public sf::Drawable
{
	enum MapEvents {
		Battle,
		None
	};
private:
	/* Private Members */
	sf::Texture mapBackTexture;
	sf::Sprite mapBackSprite;

	std::vector<Territory> territories;
	std::vector<std::vector<Territory*>> mapSplit;
	std::map<int, sf::FloatRect> continentBounds;

	Territory* inFocus = nullptr;

	float zeroZoom = 0.f;
	sf::View mapView;
	
	/* Setup methods */
	void setupMap();

	/* Overrides */
	virtual void draw(sf::RenderTarget&, sf::RenderStates = sf::RenderStates()) const;

public:
	/* Constructor */
	Map();

	/* Methods */
	bool load(std::string); /*!< \brief Load selected map from file */
	void zeroView() { mapView.zoom(zeroZoom); }; /*!< Reset map zoom to '0'*/

	/* Event methods */
	MapEvents handleEvents(sf::Event);
	void handleMouseMove();
	bool territoryColision(int, sf::Vector2f);
};

#endif // !MAP_H
