/*!
	\file responsible for holding the class declaration of crossShape
	\author Samuel A. Wilcox
	\date 14/07/2017
*/
#ifndef CROSS_SHAPE_H
#define CROSS_SHAPE_H

#include <SFML\Graphics.hpp>

/*!
	\class defines a shape that is a cross (X), with the intended use within a close button
*/
class CrossShape : public sf::Drawable {
	
	private:
		/* Attributes */
		sf::RectangleShape backSlash;
		sf::RectangleShape forwardSlash;

		sf::Vector2f currentPosition;
		sf::Color currentColour;
		float shapeThickness;
		float shapeWidth;

		/* Methods */
		void setShape();
		void setAngles();
		int calculateRectLength();
		void setPosition();
		void setColour() { backSlash.setFillColor(currentColour); forwardSlash.setFillColor(currentColour); };


	public:
		/* Constructor -- Destructor */
		CrossShape(sf::Color = sf::Color::White, float width = 50, float thickness = 5, sf::Vector2f = sf::Vector2f());
		~CrossShape();

		/* Override */
		virtual void draw(sf::RenderTarget&, sf::RenderStates = sf::RenderStates()) const;

		/* Getters */
		sf::Vector2f getPosition() { return currentPosition; };
		sf::Color getColour() { return currentColour; };
		float getThickness() { return shapeThickness; };
		float getShapeWidth() { return shapeWidth; };

		/* Setters */
		void setOverallWidth(float width) { shapeWidth = width; setShape(); };
		void setShapeThickness(float thickness) { shapeThickness = thickness; setShape(); };
		void setColour(sf::Color colour) { currentColour = colour; setColour(); };
		void setPosition(sf::Vector2f);
};

#endif // !CROSS_SHAPE_H
