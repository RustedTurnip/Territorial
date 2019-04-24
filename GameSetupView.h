#ifndef GAME_SETUP_VIEW_H
#define GAME_SETUP_VIEW_H

#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include "View.h"
#include "Tbutton.h"
#include "TanimatedButton.h"

class GameSetupView : public View {	/* May end up being parent for all in game menus */

	enum ButtonID {
		AddPlayer, RemovePlayer, HumanToggle
	};

private:
	//Spacing of buttons
	const size_t BUTTON_VERTICAL_SPACING = 15;
	const size_t BUTTON_HORIZONTAL_SPACING = 40;
	
	const sf::Vector2f PLAYER_SIZE = sf::Vector2f(350, 50);
	const sf::Vector2f HUMAN_TOGGLE_SIZE = sf::Vector2f(150, 50);
	const sf::Vector2f BUTTON_ADD_REM_SIZE = sf::Vector2f(50, 50);

	const std::string PLAYER_STRING = "Player";
	const std::string HUMAN_STRING = "Human";
	const std::string PC_STRING = "PC";

	sf::FloatRect buttonBounds;	//Will need to be re-calculated  i.e. when window size changes

	sf::Text title;
	std::vector<std::pair<Tbutton, Tbutton>> buttons;
	Tbutton addButton;
	Tbutton removeButton;
	TanimatedButton playButton;

	sf::Font& font;

private: /* Initialise */
	void initialise();
	void initialiseText();
	void initialiseFixedButtons();
	void calculateButtonBounds();
	void positionButtons();

	void addPlayer();
	void removePlayer();
	void toggleHuman(size_t);
	Identifiers::StateChange playGame();

public:
	/* Constructor -- Destructor */
	GameSetupView(sf::RenderWindow*);
	~GameSetupView();


	/* Override methods */
	virtual void render();
	virtual Identifiers::StateChange handleEvents(sf::Event);

};

#endif /* !GAME_SETUP_VIEW_H */