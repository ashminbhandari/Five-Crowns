#pragma once

#include <vector>
#include "card.h"

class hand {
private:
	vector<card*> hand; //Store the hand in a vector 

public:
	void addToHand(card*);
	void printHand();
};