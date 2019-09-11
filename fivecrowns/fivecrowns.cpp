#include <iostream>
#include "deck.h"

int main()
{
	deck myDeck;
	myDeck.initialize();
	myDeck.print();
	myDeck.shuffle();
	myDeck.print();
	return 0;
}
