#ifndef MENU_STATE_H
#define MENU_STATE_H

#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include "View.h"
#include "Tbutton.h"
#include "TanimatedButton.h"

class MenuView : public View {	/* May end up being parent for all in game menus */

	enum ButtonID {
		StartGame, Settings
	};

	private:
		const size_t BUTTON_NO = 4;		//Number of buttons on menu
		const size_t BUTTON_SPACING = 40;	//Spacing of buttons
		const sf::Vector2f BUTTON_SIZE = sf::Vector2f(350, 50);
		sf::FloatRect buttonBounds;	//Will need to be re-calculated  i.e. when window size changes

		sf::RenderTexture menuScreen;

		sf::Sprite logo;
		sf::Texture logoImage;
		std::vector<TanimatedButton> buttons;


		TanimatedButton test;
		TanimatedButton bug;

		sf::Font font;

	private: /* Initialise */
		void initialise();
		void initialiseScreen();
		void initialiseButtons();
		void initialiseButtonBounds();
		void initialiseImages();
		

	public:
		/* Constructor -- Destructor */
		MenuView(sf::RenderWindow*);
		~MenuView();


		/* Override methods */
		virtual void render();
		virtual Identifiers::StateChange handleEvents(sf::Event);

};

#endif // !MENU_STATE_H
