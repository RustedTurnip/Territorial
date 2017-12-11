/*
 * \file territorial.h : contains class decleration of Territorial
 */
#ifndef TERRITORIAL_H
#define TERRITORIAL_H

#include <string>

/*
 *\class Territorial : This class only contains static data. It acts as a host for global variables
 */
class Territorial
{
private:
	const static std::string version; /* The version number of Territorial itself */
public:
	/* Getters */
	static const std::string getVersion() { return version; }
};

#endif /* !TERRITORIAL_H */