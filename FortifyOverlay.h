#ifndef FORTIFY_OVERLAY_H
#define FORTIFY_OVERLAY_H

#include <SFML/Graphics.hpp>
#include "CloseButton.h"
#include "TanimatedButton.h"
#include "Tbutton.h"
#include "Territory.h"
#include "Territorial.h"

class FortifyOverlay : public sf::Drawable {

private:
	const sf::Vector2f OVERLAY_SIZE = sf::Vector2f(700, 900);
	const float VERTICAL_SPACE = 50.f;
	const sf::Vector2f ICON_SIZE = sf::Vector2f(150, 150);
	const sf::Vector2f UNIT_BUTTON_SIZE = sf::Vector2f(50, 50);

	/* Genral Attributes */
	sf::RectangleShape background = sf::RectangleShape(OVERLAY_SIZE);
	sf::Text overlayTitle = sf::Text("Fortify", Territorial::mainFont, 45);
	CloseButton closeButton = CloseButton(40);
	TanimatedButton confirmButton = TanimatedButton();
	Tbutton addUnitButton = Tbutton(Territorial::mainFont, UNIT_BUTTON_SIZE);
	Tbutton removeUnitButton = Tbutton(Territorial::mainFont, UNIT_BUTTON_SIZE);
	sf::Text unitNumber = sf::Text("1", Territorial::mainFont, 50);
	bool open = false;
	bool fortifyCommit = false;
	size_t unitsToMove = 1;

	/* Attacker attributes */
	Territory* source;
	sf::Text sourceTitle = sf::Text("", Territorial::mainFont, 26);
	sf::Sprite sourceSprite = sf::Sprite();
	sf::Text sourceUnits = sf::Text("", Territorial::mainFont, 36);

	/* Defender attributes */
	Territory* destination;
	sf::Text destinationTitle = sf::Text("", Territorial::mainFont, 26);
	sf::Sprite destinationSprite = sf::Sprite();
	sf::Text destinationUnits = sf::Text("", Territorial::mainFont, 36);

	/* General Functions */
	void initialise();
	void positionElements();
	void initialiseElements();

	void handleMouseMove();
	void handleMouseClick();

	void addUnit();
	void removeUnit();
	void confirm();

public:
	/* Constructor */
	FortifyOverlay();

	void close() { open = false; };
	void openWindow(Territory&, Territory&);
	bool isOpen() { return open; };
	bool isFortifyCommit() { return fortifyCommit; };

	void handleEvents(sf::Event);

	void setSource(Territory&);
	void setDestination(Territory&);
	void resetFortifyCommit() { fortifyCommit = false; };

	/* Overrides */
	virtual void draw(sf::RenderTarget&, sf::RenderStates = sf::RenderStates()) const;
};

#endif // !FORTIFY_OVERLAY_H
