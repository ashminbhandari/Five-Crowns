#pragma once
#include "player.h"

class human : public player {
private:
	vector <card> hand;

protected:
	void pickCard();
	void dropCard();

public:
	void takeTurn();
};

