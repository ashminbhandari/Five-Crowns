#include "card.h"
#include <vector>

using namespace std;

class deck {
	
private:
	vector<card> deck; //A deck for this game consists of 116 cards (58 in each)

public:
	//Initializes the deck
	void initialize();

	//Prints the deck out to console 
	void print();

	//Shuffle the deck
	void shuffle();
};