#include "deck.h"

void deck::initializeDeck() {
	//Initialize 'spades' first, 0 through 10 in the array
	int rankValue = 3;
	for (int i = 0; i < 11; i++) {
		if (rankValue <= 10) {
			this->deck[i].setRank(to_string(rankValue));
		}
		else if (rankValue == 11) {
			this->deck[i].setRank("J");
		}
		else if (rankValue == 12) {
			this->deck[i].setRank("Q");
		}
		else if (rankValue == 13) {
			this->deck[i].setRank("K");
		}
		this->deck[i].setSuit("S"); //"S" for spades
		rankValue++;
	}

	//Initialize 'clubs' second, 11 through 21
	rankValue = 3;
	for (int i = 11; i < 22; i++) {
		if (rankValue <= 10) {
			this->deck[i].setRank(to_string(rankValue));
		}
		else if (rankValue == 11) {
			this->deck[i].setRank("J");
		}
		else if (rankValue == 12) {
			this->deck[i].setRank("Q");
		}
		else if (rankValue == 13) {
			this->deck[i].setRank("K");
		}
		this->deck[i].setSuit("C"); //"C" for clubs
		rankValue++;
	}

	//Initialize 'diamonds' third, 22 through 31
	rankValue = 3;
	for (int i = 22; i < 33; i++) {
		if (rankValue <= 10) {
			this->deck[i].setRank(to_string(rankValue));
		}
		else if (rankValue == 11) {
			this->deck[i].setRank("J");
		}
		else if (rankValue == 12) {
			this->deck[i].setRank("Q");
		}
		else if (rankValue == 13) {
			this->deck[i].setRank("K");
		}
		this->deck[i].setSuit("D"); //"D" for diamonds
		rankValue++;
	}

	//Initialize 'hearts' fourth, 31 through 41
	rankValue = 3;
	for (int i = 33; i < 44; i++) {
		if (rankValue <= 10) {
			this->deck[i].setRank(to_string(rankValue));
		}
		else if (rankValue == 11) {
			this->deck[i].setRank("J");
		}
		else if (rankValue == 12) {
			this->deck[i].setRank("Q");
		}
		else if (rankValue == 13) {
			this->deck[i].setRank("K");
		}
		this->deck[i].setSuit("H"); //"H" for diamonds
		rankValue++;
	}

	//Initialize 'tridents' fourth, 41 through 51
	rankValue = 3;
	for (int i = 44; i < 55; i++) {
		if (rankValue <= 10) {
			this->deck[i].setRank(to_string(rankValue));
		}
		else if (rankValue == 11) {
			this->deck[i].setRank("J");
		}
		else if (rankValue == 12) {
			this->deck[i].setRank("Q");
		}
		else if (rankValue == 13) {
			this->deck[i].setRank("K");
		}
		this->deck[i].setSuit("T"); //"T" for tridents
		rankValue++;
	}

	this->deck[55].isJoker(1);
	this->deck[56].isJoker(2);
	this->deck[57].isJoker(3);
}


void deck::printDeck() {
	for (int i = 0; i < 58; i++) {
		cout << this->deck[i].getCard() << endl;
	}
}