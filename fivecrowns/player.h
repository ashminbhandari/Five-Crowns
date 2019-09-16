#pragma once
#include "card.h"
#include <vector>

class player {
private:
	vector <card> hand;

protected:
	//Pick a card from the draw pile, to be redefined in child classes
	virtual void pickCard();

	//Drops a card to the discard pile, to be redefined in child classes
	virtual void dropCard();

public:
	//Gets the players hand 
	vector <card>* getHand(); 

	//Take their turn, to be redefined in child classes
	virtual void takeTurn();

	//Prints out the players hand to screen
	void printHand();
};