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

	//Constructor that takes in two string arguments 
	card(string, string);

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

	//Checks whether or not the card is a joker
	bool isJoker();
};