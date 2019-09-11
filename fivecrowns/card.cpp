#include "card.h"
#include <iostream>

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

//Gets the card address
card* card::getCard() {
	return this;
}

//Prints the card out to console 
string card::getCardValue() {
	return this->suit + this->rank;
}


//Returns false for a card object, true for a joker (derived from card)
bool card::isJoker() {
	if (getCardValue() == "J1" || getCardValue () == "J2" || getCardValue() == "J3") {
		return true;
	}
	return false;
}