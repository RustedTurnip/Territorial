#ifndef BATTLE_OVERLAY_H
#define BATTLE_OVERLAY_H

#include <SFML/Graphics.hpp>
#include "Territory.h"
#include "Territorial.h"
#include "CloseButton.h"
#include "TanimatedButton.h"

class BattleOverlay : public sf::Drawable {

private:
	const sf::Vector2f OVERLAY_SIZE = sf::Vector2f(700, 900);
	const float VERTICAL_SPACE = 50.f;
	const sf::Vector2f ICON_SIZE = sf::Vector2f(150, 150);
	const sf::Vector2f DICE_BUTTON_SIZE = sf::Vector2f(50, 50);

	/* Genral Attributes */
	sf::RectangleShape background = sf::RectangleShape(OVERLAY_SIZE);
	sf::Text overlayTitle = sf::Text("Attack", Territorial::mainFont, 45);
	CloseButton closeButton = CloseButton(40);
	TanimatedButton rollButton = TanimatedButton();
	Tbutton addDiceButton = Tbutton(Territorial::mainFont, DICE_BUTTON_SIZE);
	Tbutton removeDiceButton = Tbutton(Territorial::mainFont, DICE_BUTTON_SIZE);
	sf::Text diceNumber = sf::Text("1", Territorial::mainFont, 50);
	bool open = false;

	/* Attacker attributes */
	Territory* attacker;
	sf::Text attackerTitle = sf::Text("", Territorial::mainFont, 26);
	sf::Sprite attackerSprite = sf::Sprite();
	sf::Text attackerUnits = sf::Text("", Territorial::mainFont, 36);

	/* Defender attributes */
	Territory* defender;
	sf::Text defenderTitle = sf::Text("", Territorial::mainFont,26);
	sf::Sprite defenderSprite = sf::Sprite();
	sf::Text defenderUnits = sf::Text("", Territorial::mainFont, 36);

	/* General Functions */
	void initialise();
	void positionElements();
	void initialiseElements();

	void handleMouseMove();
	void handleMouseClick();

	void addDice() {};
	void removeDice() {};
	void attack() {};

public:
	/* Constructor */
	BattleOverlay();

	void close() { open = false; };
	void openWindow(Territory&, Territory&);
	bool isOpen() { return open; };
	
	void handleEvents(sf::Event);

	void setAttacker(Territory&);
	void setDefender(Territory&);

	/* Overrides */
	virtual void draw(sf::RenderTarget&, sf::RenderStates = sf::RenderStates()) const;
};

#endif // !BATTLE_OVERLAY_H
