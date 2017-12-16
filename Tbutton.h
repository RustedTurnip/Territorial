/*!
*	\file Tbutton.h
*	\brief This file contains the declaration of the Tbutton class, an Interface component
*
*	\author Samuel A. Wilcox
*	\date 24/04/2017
*/
#ifndef TBUTTON_H
#define TBUTTON_H

#include <SFML\Graphics.hpp>
#include <string>

/*!
	\class Tbutton
	\brief This class defines a button that can be drawn to screen

	This class houses a "button", consisiting of a rectangle and text. The class provides all
	of the necessary functions, including changing colour and text

	\author Samuel A. Wilcox
	\date 24/04/2017
*/
class Tbutton : public sf::Drawable {

	

	private:
		sf::RectangleShape button;	/*!< Forms the base of button, defining its bounds */

		/* Colours - so can't be forgotton (TanimatedButton) */
		sf::Color backgroundColour;	/*!< The colour for the base rectangle */
		sf::Color foregroundColour;	/*!< The colour for the text within the button */

		sf::Color focusBackgroundColour;	/*!< Background colour when mouseOver */
		sf::Color focusForegroundColour;	/*!< Foreground colour when mouseOver */


		/* Button Text */
		sf::Font* font;
		sf::Text buttonText;

		bool isFontSet = false;
		

	private:
		/* Initialise methods */
		void initialiseButton(sf::Vector2f);
		void initialiseText();

		virtual void draw(sf::RenderTarget&, sf::RenderStates = sf::RenderStates()) const;


	protected:
		/* Methods for sub classes */
		bool drawText();
		bool drawTextFlag = false;	/*!< Used to determine whether to draw text (if within button bounds) */

		sf::RectangleShape* getButton();
		//sf::Text* getText();
		
		//const sf::RectangleShape& getConstButton() const;
		const sf::RectangleShape& getConstButton() const;
		const sf::Text& getConstText() const;

		/* Variables */
		bool isInFocus = false;
	
	public:
		/* Constructor -- Destructor */
		Tbutton(sf::Vector2f = sf::Vector2f(0, 0));	/* Default */
		Tbutton(sf::Font&, sf::Vector2f = sf::Vector2f(0, 0));	/* Set font from reference */
		Tbutton(std::string, sf::Vector2f = sf::Vector2f(0, 0));	/* Load font from file */
		~Tbutton();

		/* Override methods */
		
		
		void setFont(sf::Font&);
		bool loadFontFromFile(std::string);

		/* Text methods */
		void setText(std::string = "Button");
		void setTextSize(int);
		void setForegroundColour(sf::Color);
		void setFocusForegroundColour(sf::Color);

		/* sf::RectangleShape methods */
		void setSize(sf::Vector2f);
		void setPosition(sf::Vector2f);
		void setOrigin(sf::Vector2f);

		void setBackgroundColour(sf::Color);
		void setFocusBackgroundColour(sf::Color);

		sf::Vector2f getSize();
		sf::Vector2f getPosition();
		sf::FloatRect getGlobalBounds();

		sf::Color getBackgroundColour();
		sf::Color getForegroundColour();
		sf::Color getFocusBackgroundColour();
		sf::Color getFocusForegroundColour();
		
		//Possibly some more
		const std::string getText() const { return buttonText.getString(); };

		void setInFocus(bool);
		void focusColour();
};

#endif // !TBUTTON_H
