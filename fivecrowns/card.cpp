/************************************************************
* Name:  Ashmin Bhandari
* Project : Five Crowns (C++)
* Class : Card
* Date : 10/24/2019
************************************************************/

#include "card.h"
#include <iostream>

/* *********************************************************************
Function Name: card
Purpose: The constructor for the card class, it initializes the card to 'XX' value.
********************************************************************* */
card::card() {
	suit = "X"; //Default value for suit 
	rank = "X"; //Default value for rank 
}

/* *********************************************************************
Function Name: card
Purpose: Constructor for the card class that takes in two string arguments to initialize the card object as 
Parameters: a. rank, string value of the rank of the card
b. suit, string value of the suit of the card
********************************************************************* */
card::card(string rank, string suit) {
	this->rank = rank;
	this->suit = suit;
}

/* *********************************************************************
Function Name: getSuit
Purpose: A public getter of the suit of the card instance
Return Value: suit of the card, as a string value 
********************************************************************* */
string card::getSuit() {
	return suit;
}

/* *********************************************************************
Function Name: getRank
Purpose: A public getter of the rank of the card instance
Return Value: rank of the card, as a string value 
********************************************************************* */
string card::getRank() {
	return rank;
}

/* *********************************************************************
Function Name: setSuit
Purpose: A public setter of the suit of the card instance
********************************************************************* */
void card::setSuit(string suit) {
	this->suit = suit;
}

/* *********************************************************************
Function Name: setRank
Purpose: A public setter of the rank of the card instance
********************************************************************* */
void card::setRank(string rank) {
	this->rank = rank;
}

/* *********************************************************************
Function Name: getCard
Purpose: Getter of a copy of the card object
Return Value: A card object, a copy of 'this' instance 
********************************************************************* */
card card::getCard() {
	return *this;
}

/* *********************************************************************
Function Name: getCardValue
Purpose: Gets a string value of the card, for example JS is J of spades and so on
Return Value: A string representation of the card instance 
********************************************************************* */
string card::getCardValue() {
	return this->rank + this->suit;
}


/* *********************************************************************
Function Name: isJoker
Purpose: Checks whether or not the card is a joker
Return value: A bool which signifies whether the card is a joker or not 
********************************************************************* */
bool card::isJoker() {
	if (getCardValue() == "J1" || getCardValue () == "J2" || getCardValue() == "J3") {
		return true;
	}
	return false;
}

/* *********************************************************************
Function Name: getRankValue
Purpose: Gets the integer value of the rank of the card
Return Value: Integer value of the rank of the card
Algorithm: Run through a bunch of if's and return the value according to that 
********************************************************************* */
int card::getRankValue() {
	if (this->rank == "X") {
		return 10;
	}
	else if (getCardValue() == "JS" || getCardValue() == "JC" || getCardValue() == "JD" || getCardValue() == "JH" || getCardValue() == "JT") {
		return 11;
	}
	else if (this->rank == "Q") {
		return 12;
	}
	else if (this->rank == "K") {
		return 13;
	}
	else if (getCardValue() == "J1" || getCardValue() == "J2" || getCardValue() == "J3") {
		return 50;
	}
	else {
		return stoi(this->rank);
	}
}

/* *********************************************************************
Function Name: getSuitValue
Purpose: Gets the integer value of the suit of the card
Return Value: Integer value of the suit of the card
Algorithm: Run through a bunch of if's and return the value according to that
********************************************************************* */
int card::getSuitValue() {
	if(this->suit == "S") {
		return 0;
	}
	else if (this->suit == "C") {
		return 1;
	}
	else if (this->suit == "D") {
		return 2;
	}
	else if (this->suit == "H") {
		return 3;
	}
	else if (this->suit == "T") {
		return 4;
	}
}