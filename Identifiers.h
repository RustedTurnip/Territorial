/*!
*	\file Identifiers.h
*	\brief This file contains "Identifiers" e.g. enumerations, that are used across the program
*
*	\author Samuel A. Wilcox
*	\date 16/12/2017
*/
#ifndef IDENTIFIERS_H
#define IDENTIFIERS_H

namespace Identifiers {

	enum Continent {
		NorthAmerica,
		SouthAmerica,
		Africa,
		Europe,
		Asia,
		Australia,
		ContinentError
	};


	/*!
	*	Each enumeration, with the exception of DoNothing represents a state (or screen)
	*	which will be used by the ViewManager to navigate to the correct screen, or enter
	*	certain states
	*/
	enum StateChange {
		DoNothing,
		MainMenu,
		SetupGame,
		PlayGame,
		Settings,
		Instructions,
		Credits,
		EndGame
	};
}

#endif // !IDENTIFIERS_H
