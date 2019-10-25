/************************************************************
* Name:  Ashmin Bhandari
* Project : Five Crowns (C++)
* Class : Deck
* Date : 10/24/2019
************************************************************/

#include "deck.h"
#include <algorithm>
#include <ctime>
#include <iterator>
#include <random>

//This is the singleton instance of the deck to be used throughout the game, first initialized as 0 
deck* deck::instance = 0;

/* *********************************************************************
Function Name: getDeck
Purpose: Gets the singleton deck instance to be used throughout the game. 
Return Value: Singleton instance of deck
Algorithm: If an instance has not yet been created, i.e. this is the first call to this class, then creates a new singleton instance and returns that
Otherwise, just returns the instance already created and in use as a singleton
********************************************************************* */
deck* deck::getDeck() {
	if (instance == 0) {
		instance = new deck();
	}
	return instance;
}

/* *********************************************************************
Function Name: deck
Purpose: Constructor for the deck
Local Variables: suit[], an array that holds the letter string values of suit: S, C, D, H and T
rank[], an array that holds the letter string values of the rank starting from 3 and ending at K
Algorithm: Simply pushes back into the deck, all the cards that are a part of it including three jokerse
********************************************************************* */
deck::deck() {
	
	//Array that holds the letter string values of the suits available for this game 
	string suit[] = { "S", "C", "D", "H", "T" }; //S - spades, C - clubs, D - diamonds, H - hearts, T - tridents

	//Array that holds the letter string values of the ranks available for this game 
	string rank[] = { "3", "4", "5", "6", "7", "8", "9","X", "J", "Q", "K" }; //Cards 3 through K - King

	//Iterate through string and rank to create the deck by pushing back into 'collection', the official vector of cards which holds the actual deck for this class
	for (int k = 0; k < 2; k++) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 11; j++) {
				card temp(rank[j], suit[i]);
				collection.push_back(temp);
			}
		}

		//Set up three jokers and push them back into the collection. Thus, we have a complete deck
		collection.push_back(card("J", "1"));
		collection.push_back(card("J", "2"));
		collection.push_back(card("J", "3"));
	}
}

/* *********************************************************************
Function Name: printDeck
Purpose: As is obvious, prints the deck out to the console
Algorithm: Simply, iterate through the collection and print each card in the deck out to the console 
********************************************************************* */
void deck::printDeck() {	
	for (int i = 0; i < collection.size(); i++) {
		cout << collection[i].getCardValue() << " ";
		//Formatting purposes, only 10 cards in one line
		if (i % 10 == 9) { 
			cout << endl;
		}
	}
	cout << endl;
} 

/* *********************************************************************
Function Name: shuffleDeck
Purpose: Simply, shuffles the deck
Algorithm: Uses, random_shuffle provided by the 'algorithm' to shuffle the deck
********************************************************************* */
void deck::shuffleDeck() {
	random_shuffle(collection.begin(), collection.end());
}

/* *********************************************************************
Function Name: removeCardAtTop
Purpose: Removes the card at the top of the deck
Algorithm: Uses the erase functionality provided by vectors to remove the top of the deck
********************************************************************* */
void deck::removeCardAtTop() {
	collection.erase(collection.begin());
}

/* *********************************************************************
Function Name: getDeckSize
Purpose: Gets the size of the deck
Algorithm: Simply, return the size of the collection (the vector that holds all the cards in the deck)
********************************************************************* */
int deck::getDeckSize() {
	return this->collection.size();
}

/* *********************************************************************
Function Name: getCardAt
Purpose: Gets the card at certain position in the deck, it gets the value not the reference
Return Value: The card object value rather than reference
********************************************************************* */
card deck::getCardAt(int index) {
	return this->collection[index];
}

