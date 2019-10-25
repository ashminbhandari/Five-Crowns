#pragma once
#include "card.h"
#include <vector>

class player {
private:
	//Vector to store cards, the players hand
	vector <card> hand;

	//The name of the player
	string name;

	//Player score
	int score;
	
public:
	//Gets the players hand 
	vector <card>* getHand(); 

	//Take their turn, to be redefined in child classes
	virtual void takeTurn();

	//Prints out the players hand to screen
	void printHand();

	//Pick a card from the draw pile, to be redefined in child classes
	virtual void pickCard();

	//Drops a card to the discard pile, to be redefined in child classes
	virtual void dropCard();

	//Gets the name of the player
	string getName();

	//Sets the name of the player
	void setName(string);

	//Set score
	void setScore(int);

	//Get score
	int getScore();

	//Display current player details
	void printDetails();

};