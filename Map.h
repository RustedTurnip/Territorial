/*!
 * \file Map.h : This file houses the class declaration of Map
 */
#ifndef MAP_H
#define MAP_H

#include <vector>
#include <SFML\Graphics.hpp>

#include "Territory.h"
#include "Player.h"

/*!
 * \brief this class represents a drawable map
 */
class Map : public sf::Drawable
{

public:
	enum MapEvents {
		NextPlayer,
		None
	};
	
	enum MapState { Selection, UnitDistribution, Game };

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

	Player* currentPlayer = nullptr;
	MapState currentState = MapState::Selection;
	
	/* Setup methods */
	void setupMap();

	/* Overrides */
	virtual void draw(sf::RenderTarget&, sf::RenderStates = sf::RenderStates()) const;

private:
	/* General methods */
	bool allocate(Territory&);

public:
	/* Constructor */
	Map();

	/* Methods */
	bool load(std::string); /*!< \brief Load selected map from file */
	void zeroView() { mapView.zoom(zeroZoom); }; /*!< Reset map zoom to '0'*/

	/* Event methods */
	MapEvents handleEvents(sf::Event);
	void handleMouseMove();
	MapEvents handleMouseClick();
	bool territoryColision(int, sf::Vector2f);

	void setCurrentPlayer(Player* player) { currentPlayer = player; };
	MapState getCurrentState() { return currentState; };
	void setCurrentState(MapState ms) { currentState = ms; };
};

#endif // !MAP_H
