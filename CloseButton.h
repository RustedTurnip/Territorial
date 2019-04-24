/*!
	\file constains the delcaration for the close button class
	\author Samuel A. Wilcox
	\date 14/07/2017
*/
#ifndef CLOSE_BUTTON_H
#define CLOSE_BUTTON_H

#include <SFML\Graphics.hpp>
#include "CrossShape.h"

/*!
	\brief this class provides the shape(s) to display a 'close button', simply a rexctangle containing an X
*/
class CloseButton : public sf::Drawable {

	private:
		/* Attributes */
		CrossShape cross;
		sf::RectangleShape background;

		sf::Color foregroundColour;
		sf::Color backgroundColour;
		float size;
		size_t crossOffset = 4;	//Will be proportionate


		/* Methods */
		void initialise(float, sf::Vector2f);
		void reset();
		void centreCross();

	public:
		/* Constructor -- destructor */
		CloseButton(float size = 60, sf::Vector2f position = sf::Vector2f());
		~CloseButton();


		/* Override */
		virtual void draw(sf::RenderTarget&, sf::RenderStates = sf::RenderStates()) const;


		/* Setters */
		void setPosition(sf::Vector2f);
		void setForegroundColour(sf::Color);
		void setBackgroundColour(sf::Color);
		void setSize(float);

		/* Getters */
		sf::Color getForegroundColour() { return cross.getColour(); };
		sf::Color getBackgroundColour() { return background.getFillColor(); };
		sf::Vector2f getSize() { return background.getSize(); };
		sf::Vector2f getPosition() { return background.getPosition(); };
		sf::FloatRect getGlobalBounds() { return background.getGlobalBounds(); };
};

#endif // !CLOSE_BUTTON_H
