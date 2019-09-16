#include "gameround.h"
#include "deck.h"

//The constructor for the round
round::round() {
	this->nCards = 3; //Initialize the number of cards at 3, increases by 1 each round
}

void round::dealCards() {
	player p1;
	player p2;
	deck* a = deck::getDeck();

	for (int i = 0; i < nCards; i++) {
		p1.
	}

	for (int i = nCards; i < nCards * 2; i++) {
		p2.getHand()->addToHand(a->getCardAt(i));
	}

	p1.getHand()->printHand();
	p2.getHand()->printHand();
}