#pragma once

#include <iostream>
#include <string>

using namespace std;

class card {

private:
	string suit;
	string rank;

public:
	//Constructor 
	card();

	//Get the suit of the card
	string getSuit();

	//Get the rank of the card
	string getRank();

	//Set the suit of the card
	void setSuit(string suit);

	//Set the rank of the card
	void setRank(string rank);

	//Gets the card value
	string getCard();

	//Takes an integer value and defines a joker accordingly. For example, if 1 is supplied the joker is defined as "J1"
	void isJoker(int);
};