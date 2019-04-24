#include "stdafx.h"
#include "Dice.h"

Dice::Dice(int sides)
	: sides(sides) {

	srand(time(NULL));	/* set random seed */
}

Dice::~Dice() {

}



/*
Interaction
*/

int Dice::roll() {
	return rand() % sides + 1;	/* return a pseudo random number between 1 and the no. of sides */
}

std::vector<int> Dice::roll(int numOfRoles) {
	std::vector<int> rolls;
	for (int i = 0; i < numOfRoles; i++) {	/* roll the dice a number of times and return vector of results*/
		rolls.push_back(roll());
	}
	return rolls;
}