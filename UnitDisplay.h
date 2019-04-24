#ifndef UNIT_DISPLAY_H
#define UNIT_DISPLAY_H

#include <SFML\Graphics.hpp>

class UnitDisplay : public sf::Drawable {

	private:
		sf::CircleShape circle; /*!< Forms the background circle in which the number will be displayed*/

		/*Text*/
		sf::Font& font;
		sf::Text text; /*!< Used to display number of units*/

		/*Private functions*/
		void initialise();

	public:
		/*Constructor*/
		UnitDisplay();

		void setColour(sf::Color colour) { circle.setFillColor(colour); };
		void setNumber(int units) { text.setString(std::to_string(units)); };
		void setNumber(std::string str) { text.setString(str); };
		void setPosition(sf::Vector2f);

		/* Getters */
		std::string getUnits() const { return text.getString(); };
		sf::Color getColour() const { return circle.getFillColor(); };
		sf::Vector2f getPosition() const { return circle.getPosition(); };

		/*Overrides*/
		virtual void draw(sf::RenderTarget&, sf::RenderStates = sf::RenderStates()) const;
};

#endif /*!UNIT_DISPLAY_H*/