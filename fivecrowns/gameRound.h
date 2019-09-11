#pragma once

#include "player.h"

class gameRound {
private:
	int nCards; //Number of cards to be used in a round, starts at 3 

public:
	gameRound();
	void dealCards();
};
