#include "computer.h"

void computer::pickCard() {
	cout << "I picked a card." << endl;
}

void computer::dropCard() {
	cout << "I dropped a card." << endl;
}

void computer::takeTurn() {
	pickCard();
	dropCard();
	cout << "I took a turn." << endl;
}
