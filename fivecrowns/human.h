#pragma once
#include "player.h"

class human : public player {
private:
	vector <card> hand;
	string name;
	int score;
public:
	void pickCard();
	void dropCard();
	void takeTurn();
};

