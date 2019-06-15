#include "PCPlayer.h"
#include <thread>

#include <iostream>

/* Constructor */
PCPlayer::PCPlayer() {
	playerType = Player::PlayerType::PC;
}

void PCPlayer::selectTerritory() {
	turnInProgress = true;
	turnOver = false;

	std::thread t(&PCPlayer::selectTerritoryThreaded, this);
	t.detach();
	//t.join();
}

void PCPlayer::selectTerritoryThreaded() {
	
	std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
	std::pair<int, int> best = std::pair<int, int>(1000, 0); //First represents heuristic value, second ID

	for (auto a : Territorial::map_global) {
		if (a.second.isAllocated())
			continue;
		
		int value = a.second.getHeuristic();
		value *= CONTINENT_HEURISTICS[a.second.getContinent()];

		if (value < best.first)
			best = std::pair<int, int>(value, a.first);
	}

	//Implement selection
	Territory& territory = Territorial::map_global.at(best.second);
	territory.setPlayer(this->getPlayerNum());
	territory.setAllocated();
	territory.setUnitDisplayColour(this->getPlayerColour());
	territory.setUnits(territory.getUnits() + 1);
	this->allocateUnit();

	turnInProgress = false;
	turnOver = true;
}

void PCPlayer::placeUnit() {

	turnInProgress = true;
	turnOver = false;

	std::thread t(&PCPlayer::placeUnitThreaded, this);
	t.detach();
}

void PCPlayer::placeUnitThreaded() {

	std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));

	std::vector<int> occupied = std::vector<int>();
	int continentFill[6] = {};

	for (auto a : Territorial::map_global) {
		if (a.second.getPlayer() == this->getPlayerNum()) {
			occupied.push_back(a.first);
			continentFill[a.second.getContinent()] += 1;
		}
	}

	int value;
	std::pair<int, int> best = std::pair<int, int>(1000, 0);

	for (int i : occupied) {
		Territory& t = Territorial::map_global.at(i);
		int c = t.getContinent();
		value = t.getHeuristic();
		value += CONTINENT_HEURISTICS[c];
		value += CONTINENT_SIZE[c] - continentFill[c];
		value += t.getUnits() - 1; //Prevent tall stacking

		if (t.getUnits() > 4)
			value += (2 * (t.getUnits() - 4));
			

		if (value < best.first)
			best = std::pair<int, int>(value, i);
	}

	this->allocateUnit();
	Territory& t = Territorial::map_global.at(best.second);
	t.setUnits(t.getUnits() + 1);

	turnInProgress = false;
	turnOver = true;
}