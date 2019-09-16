#include "deck.h"
#include <algorithm>
#include <ctime>
#include <iterator>

//The instance of the deck is initialized as null
deck* deck::instance = 0;

//If no instance has been created, created a new one otherwise refer back to that one instance
deck* deck::getDeck() {
	if (instance == 0) {
		instance = new deck();
	}
	return instance;
}

//Constructor for the deck, constructs a deck of 116 cards
deck::deck() {
	string suit[] = { "S", "C", "D", "H", "T" }; //S - spades, C - clubs, D - diamonds, H - hearts, T - tridents
	string rank[] = { "3", "4", "5", "6", "7", "8", "9","X", "J", "Q", "K" }; //Cards 3 through K - King
	for (int k = 0; k < 2; k++) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 11; j++) {
				card temp(rank[j], suit[i]);
				collection.push_back(temp);
			}
		}

		//Set up three jokers
		collection.push_back(card("J", "1"));
		collection.push_back(card("J", "2"));
		collection.push_back(card("J", "3"));
	}
}

//Prints out the deck to the console
void deck::printDeck() {
	cout << "Currently, the cards in the deck are : ";
}

//Shuffles the deck randomly using random_shuffle provided by the algorithm library
void deck::shuffleDeck() {
	srand(unsigned(time(0)));
	random_shuffle(collection.begin(), collection.end());
}

//Removes the card at the top
void deck::removeCardAtTop() {
	collection.erase(collection.begin());
}

//Gets the deck size
int deck::getDeckSize() {
	return this->collection.size();
}

card deck::getCardAt(int index) {
	return this->collection[index];
}