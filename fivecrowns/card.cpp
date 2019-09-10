#include "card.h"

card::card() {
	suit = "X"; //Default value for suit 
	rank = "X"; //Default value for rank 
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

//If the card is a joker, set the 
void card::isJoker(int jokerNo) {
	this->rank = "J";
	this->suit = to_string(jokerNo);
}