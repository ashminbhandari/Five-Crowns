#pragma once
#include "card.h"

class joker : public card {
public:
	
	//Initializes a joker with given joker number
	joker(string jokerNo);

	//Whether or not the card is a joker
	bool isJoker();
};