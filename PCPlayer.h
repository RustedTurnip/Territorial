#ifndef PC_PLAYER_H
#define PC_PLAYER_H

#include "Player.h"
#include <atomic>

class PCPlayer : public Player {
private:
	const int DELAY = 0; //To simulate decision making time
	const int CONTINENT_HEURISTICS[6] = {2,1,2,3,3,1};
	const int CONTINENT_SIZE[6] = {9,4,6,7,12,4};
	
	std::atomic<bool> turnOver = false;
	std::atomic<bool> turnInProgress = false;

	void selectTerritoryThreaded();
	void placeUnitThreaded();

public:
	/* Constructor */
	PCPlayer();

	void selectTerritory();
	void placeUnit();

	bool isTurnOver() { return turnOver.load(); };
	bool isTurnInProgress() { return turnInProgress.load(); };
	void endTurn() { turnOver = false; };

};

#endif // !PC_PLAYER_H