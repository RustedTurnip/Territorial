#include "Reader.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

std::vector<std::string> Reader::splitString(std::string line, char delimiter)
{
	std::stringstream ss;
	ss << line;
	std::vector<std::string> sorted;
	std::string inFocus;

	while (getline(ss, inFocus, delimiter))
	{
		sorted.push_back(inFocus);
	}

	return sorted;
}

/*!
	\brief reads in the map, countries and neighbours and coords
	\TODO more accurate error message (i.e. which file hasn't been found)
	\TODO add const string for file name
*/
bool Reader::readMap(std::string mapLoc)
{
	
	try
	{
		std::ifstream mapReader(mapLoc);

		if (!mapReader)
		{
			throw std::logic_error("File not found");
		}

		std::string line;
		std::string inFocus;
		std::string name;
		int countryID;
		int continentID;
		int tempEdge;
		float x, y;
		std::vector<int> edges;
		std::vector<std::string> temp;
		std::stringstream ss;

		for (int i = 0; !mapReader.eof(); i++)
		{
			getline(mapReader, line);
			edges.clear();
			temp = splitString(line, DELIMITER);

			name = temp.at(0);

			ss << temp.at(1);
			ss >> continentID;
			ss.str(""); ss.clear();		//Clears stringstream
			
			ss << temp.at(2);
			ss >> countryID;
			ss.str(""); ss.clear();		//Clears stringstream
			
			//Read in coordinates
			ss << temp.at(3);
			ss >> x;
			ss.str(""); ss.clear();		//Clears stringstream
			ss << temp.at(4);
			ss >> y;
			ss.str(""); ss.clear();		//Clears stringstream

			for (int j = 5; j < temp.size(); j++)
			{
				ss << temp.at(j);
				ss >> tempEdge;
				edges.push_back(tempEdge);

				ss.str(""); ss.clear();		//Clears stringstream for next iteration
			}
			vertices.push_back(Territory(sf::Vector2f(x, y), name, continentID, countryID));
		}
	}
	catch(std::exception &e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
		std::cerr << "Exception Type: " << typeid(e).name() << std::endl;
	}
}


/*!
	\brief reads in each continents bounds from file
	\TODO more accurate error message (i.e. which file hasn't been found)
	\TODO add const string for file name
*/
bool Reader::readContinents(std::string coordsLoc) {

	try
	{
		std::ifstream mapReader(coordsLoc);

		if (!mapReader){
			throw std::logic_error("File not found");
		}

		std::string line;
		int continentID;
		float left, top, height, width;
		sf::FloatRect tempRect;
		std::vector<std::string> temp;
		std::stringstream ss;

		for (int i = 0; !mapReader.eof(); i++){
			
			getline(mapReader, line);
			temp = splitString(line, DELIMITER);

			ss << temp.at(0); ss >> continentID; ss.str(""); ss.clear();	//Read continentID
			ss << temp.at(1); ss >> left; ss.str(""); ss.clear();	//Read left
			ss << temp.at(2); ss >> top; ss.str(""); ss.clear();	//Read top
			ss << temp.at(3); ss >> width; ss.str(""); ss.clear();	//Read width
			ss << temp.at(4); ss >> height;	ss.str(""); ss.clear();	//Read height

			continentBounds.insert(std::make_pair(continentID, sf::FloatRect(left, top, width, height)));
		}
	}
	catch (std::exception &e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
		std::cerr << "Exception Type: " << typeid(e).name() << std::endl;
	}
}

bool Reader::readAll(std::string mapLoc, std::string coordsLoc) {

	if (!readMap(mapLoc))
		return false;
	if (!readContinents(coordsLoc))
		return false;

	return true;
}
