#include "human.h"

void human::pickCard() {
	//What is the user going to do? Pick from darw pile or discard pile? Ask for input.
	int fromWhichToPick = 0;
	while (fromWhichToPick != 1 && fromWhichToPick != 2) {
		cout << "Do you want to pick from the draw pile or the discard pile? \n Choose: [1 == from draw pile | 2 == from discard pile] : ";
		cin >> fromWhichToPick;
		if (fromWhichToPick != 1 && fromWhichToPick != 2) {
			cout << "ERROR in input." << endl;
		}
	}

	//Draw from the chosen pile
	if (fromWhichToPick == 1) {
		cout << "I picked from the draw pile." << endl;
	}
	else {
		cout << "I picked from the discard pile." << endl;
	}
}

void human::dropCard() {
	string whichCardToDrop;
	cout << "Which card do you want to drop? \n Choose: ";
	cin >> whichCardToDrop;
	cout << whichCardToDrop << "was dropped." << endl;
}


void human::takeTurn() {
	pickCard();
	dropCard();
}
