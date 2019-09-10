#include "card.h"

using namespace std;

class deck {
	
private:
	card deck[58]; //A deck consists of 58 cards, thus an array of 58 cards is created 

public:
	//Initializes the deck
	void initializeDeck();

	//Prints the deck out to console 
	void printDeck();
};