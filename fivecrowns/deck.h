#include "card.h"
#include <vector>

using namespace std;

//Deck is a singleton class, for five crowns the deck consists of 116 cards
class deck {
	
private:
	//Single instance of deck to be accessed throughout the game
	static deck* instance;

	//A private constructor to prevent instancing
	deck();

	//The vector that holds the card objects
	vector <card> collection; //Collection of cards required for the game (58 in each, total 116 cards)

public:
	//Static accessor method 
	static deck* getDeck();

	//Prints the deck out to console 
	void printDeck();

	//Shuffles the deck
	void shuffleDeck();

	//Gets a card at certain location
	card getCardAt(int);

	//Removes the card at the top
	void removeCardAtTop();

	//Gets the size of the deck
	int getDeckSize();
};