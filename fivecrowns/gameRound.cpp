#include "gameRound.h"
#include "deck.h"

//The constructor for the round
gameRound::gameRound() {
	this->nCards = 3; //Initialize the number of cards at 3, increases by 1 each round
}

void gameRound::dealCards() {
	//Create two players
	player p1;
	player p2;

	//Get the deck
	deck* a = deck::getDeck();

	//Shuffle the deck
	a->shuffle();

	//Deal the cards to the two players
	for (int i = 0; i < nCards; i++) {
		p1.getHand()->addToHand(a->getCardAt(i));
	}

	for (int i = nCards; i < nCards * 2; i++) {
		p2.getHand()->addToHand(a->getCardAt(i));
	}

	//For debugging purposes, print out the hands
	p1.getHand()->printHand();
	p2.getHand()->printHand();
}