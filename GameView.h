/*!
 * \file GameView.h : this class holds the class del=claration for GameView
 */
#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include "View.h"
#include "Identifiers.h"
#include "Game.h"

#include <SFML\Graphics.hpp>

/*!
 * \brief this class defines the 'view' which will hold the game itself
 */
class GameView : public View
{
	private:
		Game game;

	public:
		/* Constructor */
		GameView(sf::RenderWindow*);

		/* Overridden methods */
		virtual void render();
		virtual Identifiers::StateChange handleEvents(sf::Event);
};

#endif // !GAME_VIEW_H
