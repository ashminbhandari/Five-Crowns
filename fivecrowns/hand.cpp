#include "hand.h"

void hand::addToHand(card* card) {
	this->hand.push_back(card);
}

void hand::printHand() {
	for (int i = 0; i < hand.size(); i++) {
		cout << hand[i] << " " <<  hand[i]->getCardValue() << endl;
	}
}


