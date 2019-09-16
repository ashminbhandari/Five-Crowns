#pragma once

#include "player.h"


class computer : public player {
private:
	vector <card> hand;

protected:
	void pickCard();
	void dropCard();

public:
	void takeTurn();
};