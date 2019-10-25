#pragma once
#include "hand.h"

class player {
private:
	hand theHand;

public:
	//Gets a pointer to player's hand object
	hand* getHand();

	//Prints out the players hand to screen
	void print();
};