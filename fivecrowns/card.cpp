#include "card.h"

//Constructor that takes in no arguments, initializes the card as "XX"
card::card() {
	suit = "X"; //Default value for suit 
	rank = "X"; //Default value for rank 
}

//Constructor that takes in two string arguments, intializes the card accordingly
card::card(string rank, string suit) {
	this->rank = rank;
	this->suit = suit;
}

//Gets the suit of the card
string card::getSuit() {
	return suit;
}

//Gets the rank of the card
string card::getRank() {
	return rank;
}

//Sets the suit of the card
void card::setSuit(string suit) {
	this->suit = suit;
}

//Sets the rank of the card
void card::setRank(string rank) {
	this->rank = rank;
}

//Gets the card value 
string card::getCard() {
	return rank + suit;
}

//Returns false for a card object, true for a joker (derived from card)
bool card::isJoker() {
	if (getCard() == "J1" || getCard() == "J2" || getCard() == "J3") {
		return true;
	}
	return false;
}