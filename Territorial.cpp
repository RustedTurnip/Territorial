/*!
 * \file territorial.cpp : contains variable initialisations for the Territorial class
 */
#include "Territorial.h"
#include <iostream>

const std::string Territorial::version = "v0.6.0-dev";	/* At this point you change the games version number */
const sf::Time Territorial::TIME_PER_FRAME = sf::seconds(1.f / 60.f);
const float Territorial::FRAMERATE_LIMIT = 60.f;

/* Statistics static variables initialisation */
size_t Territorial::frameRateMonitor = 0;
size_t Territorial::frameRateActual = 0;
sf::Time Territorial::updateTime = sf::Time::Zero;

/* General Global variables */
sf::Vector2f Territorial::windowSize = sf::Vector2f(1920.f, 1080.f);
sf::Vector2f Territorial::windowCentre = sf::Vector2f(960.f, 540.f);

/*!
 * \brief This method updates statistics of the games exectution - e.g. FrameRate
 */
void Territorial::updateStatistics(sf::Time elapsedTime) {
	
	updateTime += elapsedTime;
	frameRateMonitor += 1;	/* Counts frames of last second */
	if (updateTime >= sf::seconds(1.0f))	{
		updateTime -= sf::seconds(1.0f);
		frameRateActual = frameRateMonitor; /* Frames rendered in last second*/
		frameRateMonitor = 0;
	}
}


/*
//////////////////// SETTERS ////////////////////
*/
void Territorial::setWindowSize(sf::Vector2f size) {
	if (size.x >= 800.f || size.y >= 600) {
		windowSize = size;
		windowCentre = sf::Vector2f(windowSize.x/2, windowSize.y/2);
	}
}