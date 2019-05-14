#ifndef PC_PLAYER_H
#define PC_PLAYER_H

#include "Player.h"
#include <atomic>
#include <vector>

class PCPlayer : public Player {
private:
	const int DELAY = 100; //To simulate decision making time
	const int CONTINENT_HEURISTICS[6] = {2,1,2,3,3,1};
	const int CONTINENT_SIZE[6] = {9,4,6,7,12,4};
	int continentFill[6] = {0,0,0,0,0,0};
	
	std::atomic<bool> turnOver = false;
	std::atomic<bool> turnInProgress = false;

	std::vector<int> occupied = std::vector<int>();

	void selectTerritoryThreaded();
	void placeUnitThreaded();
	void battleThreaded();

	void battleRun(Territory&, Territory&);

public:
	/* Constructor */
	PCPlayer();

	void selectTerritory();
	void placeUnit();
	void battle();

	bool isTurnOver() { return turnOver.load(); };
	bool isTurnInProgress() { return turnInProgress.load(); };
	void endTurn() { turnOver = false; };

};

#endif // !PC_PLAYER_H