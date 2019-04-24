#ifndef DICE_H
#define DICE_H

#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>


class Dice {
private:
	int sides;

public:
	//Constructor -- destructor
	Dice(int = 6);
	~Dice();

	int roll();
	std::vector<int> roll(int);
};

#endif // !DICE_H
