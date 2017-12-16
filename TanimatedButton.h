#ifndef TANIMATED_BUTTON_H
#define TANIMATED_BUTTON_H

#include "Tbutton.h"
#include "CornerShape.h"
#include <array>
#include <iostream>

class TanimatedButton : public Tbutton {

	static float animationSpeed;
	static sf::Time timePerFrame;

	private:
		std::array<CornerShape, 4> corners;

		bool isAnimated;
		//bool isInFocus = false;
		bool closedCompleted = true;
		bool isAlreadyRunning = false;	//To stop more than one thread spawning

		int animationDistance = 10;


	private:
		/* Private methods */
		void initialiseCorners(int, int);
		void setCornerPositions();

		/* Private animation methods */
		void calculateOpenDirection(sf::Time);
		void calculateCloseDirection(sf::Time);
		void openAnimation();
		void closeAnimation();
		void animation();
		void runAnimation();

		//Drawable
		virtual void draw(sf::RenderTarget&, sf::RenderStates = sf::RenderStates()) const;

	public:
		/* Constructor -- Destructor */
		TanimatedButton(sf::Vector2f = sf::Vector2f(0, 0));
		TanimatedButton(sf::Font&, sf::Vector2f = sf::Vector2f(0, 0));
		TanimatedButton(std::string, sf::Vector2f = sf::Vector2f(0, 0));
		~TanimatedButton();


		/* Public animation methods */
		virtual void setInFocus(bool);	/* Override */
		


		/* Overrides */
		void setSize(sf::Vector2f);
		void setPosition(sf::Vector2f);
		void setBackgroundColour(sf::Color);


		/* Corner methods */
		void setCornerSize(int);
		void setCornerThickness(int);

};







#endif // !TANIMATED_BUTTON_H
