#pragma once

#include "player.h"

class computer : public player {
private:
	vector <card> hand;
	string name;
	int score;
public:
	void takeTurn();
};