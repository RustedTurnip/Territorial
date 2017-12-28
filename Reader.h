/*!
	\file responsible for housing the Reader class
*/
#ifndef READER_H
#define READER_H

#include "Territory.h"
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <iostream>

/*!
	\brief responsible for reading data in from file
*/
class Reader
{
	private:
		const char DELIMITER = ';';

		std::vector<Territory> vertices;
		//std::vector<sf::FloatRect> continentBounds;
		std::map<int, sf::FloatRect> continentBounds;
		std::vector<std::string> splitString(std::string, const char);
		
		bool readMap(std::string);
		bool readContinents(std::string);

	public:
		bool readAll(std::string, std::string);/*!< \todo swap text files for map file */
		std::vector<Territory> getVertices() { return vertices; };
		std::map<int, sf::FloatRect> getContinentBounds() { return continentBounds; };

};


#endif // !READER_H