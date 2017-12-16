#ifndef CORNER_H
#define CORNER_H

#include "SFML\Graphics.hpp"

//Class for a shape
class CornerShape : public sf::Drawable {


	public:
		static enum Rotation {
			TopLeft, TopRight, BottomLeft, BottomRight
		};



	private:
		/* Private variables */
		Rotation rotation;

		sf::RectangleShape horizontal;
		sf::RectangleShape vertical;


		/* Private methods */
		void setOrigin();
		void defaultConfig();


		/* Override */
		virtual void draw(sf::RenderTarget&, sf::RenderStates = sf::RenderStates()) const;

	public:
		/* Constructors -- Destructor */
		CornerShape(Rotation = TopLeft);
		CornerShape(int size, int thickness, Rotation rotation);
		~CornerShape();

		/* Override */
		void move(const sf::Vector2f&);


		/* Other methods */

		//Setters
		void setRotation(Rotation);
		void setPosition(sf::Vector2f);
		void setColour(sf::Color);
		void setThickness(int);
		void setSize(int);

		//Getters
		sf::Vector2f getPosition();

};

#endif // !CORNER_H
