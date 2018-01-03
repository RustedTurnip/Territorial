/*!
 * \file Map.h : This file houses the class declaration of Map
 */
#ifndef MAP_H
#define MAP_H

#include <SFML\Graphics.hpp>

/*!
 * \brief this class represents a drawable map
 */
class Map : public sf::Drawable
{
private:
	/* Private Members */
	sf::Texture mapBackTexture;
	sf::Sprite mapBackSprite;

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
	bool load(std::string); /*!< Load selected map from file */
	void zeroView() { mapView.zoom(zeroZoom); }; /*!< Reset map zoom to '0'*/
};

#endif // !MAP_H
