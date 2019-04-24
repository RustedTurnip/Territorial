/*
 * \file territorial.h : contains class decleration of Territorial
 */
#ifndef TERRITORIAL_H
#define TERRITORIAL_H

#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

/*
 *\class Territorial : This class only contains static data. It acts as a host for global variables
 */
class Territorial
{
private:
	/* Frame rate variables */
	static size_t frameRateMonitor;
	static size_t frameRateActual;
	static sf::Time updateTime;

	/* Game's General Variables */
	static sf::Vector2f windowSize; //Default: (1920.f, 1080.f)
	static sf::Vector2f windowCentre; //Defualt ^/2


public:
	/* Constants */
	const static std::string version; /* The version number of Territorial itself */
	const static sf::Time TIME_PER_FRAME; /*!< Maximum frame RENDER time */
	const static float FRAMERATE_LIMIT; /*!< Constant defines global frame rate limit */


	static const size_t PLAYER_MINIMUM = 2;
	static const size_t PLAYER_MAXIMUM = 5;
	static int currentPlayers[PLAYER_MAXIMUM]; //0 = human, 1 = pc, <=2 = none
	
	/* Game's GLobal Resources */
	static sf::Font mainFont;
	
	/* Getters */
	static size_t getFrameRate() { return frameRateActual; };
	static sf::Time getUpdateTime() { return updateTime; };

	static sf::Vector2f getWindowSize() { return windowSize; };
	static sf::Vector2f getWindowCentre() { return windowCentre; };

	/* Setters */
	static void setWindowSize(sf::Vector2f);

	/* Other methods */
	static void updateStatistics(sf::Time);

	/* Game Initialisation */
	static void initialiseResources();
};

#endif /* !TERRITORIAL_H */