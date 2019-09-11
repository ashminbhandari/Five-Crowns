#include "deck.h"
#include <algorithm>

void deck::initialize() {
	string suit[] = { "S", "C", "D", "H", "T" }; //S - spades, C - clubs, D - diamonds, H - hearts, T - tridents
	string rank[] = { "3", "4", "5", "6", "7", "8", "9","X", "J", "Q", "K" }; //Cards 3 through K - King
	
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 11; j++) {
			card temp(rank[j], suit[i]);
			this->deck.push_back(temp);
		}
	}
	
	//Set up three jokers
	this->deck.push_back(card("J", "1"));
	this->deck.push_back(card("J", "2"));
	this->deck.push_back(card("J", "3"));
}

//Prints out the deck to the console
void deck::print() {
	for (int i = 0; i < 58; i++) {
		cout << this->deck[i].getCard() << endl;
	}
}

//Shuffles the deck randomly using random_shuffle provided by the algorithm library
void deck::shuffle() {
	random_shuffle(this->deck.begin(), this->deck.end());
}