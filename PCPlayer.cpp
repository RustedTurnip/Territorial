#include "PCPlayer.h"
#include <thread>

#include <iostream>
#include "Dice.h"

/* Constructor */
PCPlayer::PCPlayer() {
	playerType = Player::PlayerType::PC;
}

void PCPlayer::selectTerritory() {
	turnInProgress = true;
	turnOver = false;

	std::thread t(&PCPlayer::selectTerritoryThreaded, this);
	//t.detach();
	t.join();
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
	//t.detach();
	t.join();
}

void PCPlayer::placeUnitThreaded() {

	std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));

	occupied = std::vector<int>();

	for (int i = 0; i < 6; i++)
		continentFill[i] = 0;

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
			

		for (int j : Territorial::map_global.at(i).getNeighbours()) {
			if (Territorial::map_global.at(j).getPlayer() != this->playerNum) {
				if (value < best.first) {
					best = std::pair<int, int>(value, i);
					break;
				}
			}
		}
	}

	this->allocateUnit();
	Territory& t = Territorial::map_global.at(best.second);
	t.setUnits(t.getUnits() + 1);

	turnInProgress = false;
	turnOver = true;
}

void PCPlayer::battle() {

	turnInProgress = true;
	turnOver = false;

	std::thread t(&PCPlayer::battleThreaded, this);
	//t.detach();
	t.join();
}

void PCPlayer::battleThreaded() {
	
	std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));

	typedef std::pair<Territory&, Territory&> battle;
	std::vector<int> sources = std::vector<int>();

	for (std::map<int, Territory&>::iterator it = Territorial::map_global.begin(); it != Territorial::map_global.end(); ++it) {
		if (it->second.getPlayer() == this->getPlayerNum()) {
			if (it->second.getUnits() >= 3) {
				sources.push_back(it->first);
			}
		}
	}

	std::vector<battle> battles = std::vector<battle>();

	for (int t : sources) {
		for (int j : Territorial::map_global.at(t).getNeighbours()) {
			if (Territorial::map_global.at(j).getUnits() < Territorial::map_global.at(t).getUnits() - 1) {
				battles.push_back(battle(Territorial::map_global.at(t), Territorial::map_global.at(j)));
			}
		}
	}

	std::map<int, int> best = std::map<int, int>();

	for (int i = 0; i < battles.size(); i++) {
		int value = 1;
		value += battles.at(i).first.getUnits() - battles.at(i).second.getUnits();
		value += (continentFill[battles.at(i).second.getContinent()] - CONTINENT_SIZE[battles.at(i).second.getContinent()]) / 2;
		//Dice d = Dice(3);
		//value -= d.roll();

		best.insert(std::pair<int, int>(value, i));
	}

	Dice d = Dice(4);
	int times = d.roll();
	int count = 0;

	for (auto iter = best.rbegin(); iter != best.rend(); iter++) {
		count++;
		if (count == times)
			break;

		battleRun(battles.at(iter->second).first, battles.at(iter->second).second);
	}

	if (battles.size() > 0) {
		for (int i = 0; i < times; i++) {
			
		}
	}

	turnInProgress = false;
	turnOver = true;
}

void PCPlayer::battleRun(Territory& source, Territory& destination) {

	while (destination.getUnits() > 0 && source.getUnits() > 1) {

		int attacking = source.getUnits() - 1;
		if (attacking > 3)
			attacking = 3;

		if (attacking <= 0)
			break;

		int defending = 1;
		if (destination.getUnits() > 1)
			defending++;

		//Roll dice
		Dice dice = Dice(6); //Six sided dice
		std::vector<int> attackRolls = std::vector<int>();
		std::vector<int> defenceRolls = std::vector<int>();

		for (int i = 0; i < attacking; i++)
			attackRolls.push_back(dice.roll());
		for (int i = 0; i < defending; i++)
			defenceRolls.push_back(dice.roll());

		//Order rolls (ascending)
		std::sort(attackRolls.begin(), attackRolls.end(), std::greater<int>());
		std::sort(defenceRolls.begin(), defenceRolls.end(), std::greater<int>());

		//Comparison no. (lesser of the two)
		size_t comparisonNum = (attacking < defending) ? attacking : defending;

		//Compare highest two rolls for each - draw favours defence
		for (int i = 0; i < comparisonNum; i++) {
			if (attackRolls.at(i) > defenceRolls.at(i)) {
				destination.setUnits(destination.getUnits() - 1);
				std::cout << "UNIT DOWN" << std::endl;
			}
			else {
				source.setUnits(source.getUnits() - 1);
			}
		}
	}

	//If battle won
	if (destination.getUnits() == 0) {

		
		//Set to new player
		destination.setPlayer(this->getPlayerNum());
		destination.setUnitDisplayColour(Player::COLOURS[this->getPlayerNum() - 1]); //TEMP

		int total = source.getUnits() - 1;
		int half = total / 2;
		if (total == 1)
			destination.setUnits(1);
		else
			destination.setUnits(total - half);
		source.setUnits(half + 1);
	}

	std::cout << destination.getName() << std::endl;
	std::cout << source.getName() << std::endl;

}