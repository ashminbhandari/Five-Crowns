#pragma once

#include "player.h"
#include "card.h"

class gameRound {
private:
	//Number of cards to be used in a round, starts at 3 
	int nCards; 

	//Wild card
	card wildCard; 
	
	//The draw pile 
	vector <card> drawPile;

	//The discard pile, stored as a vector of cards
	vector <card> discardPile;
	
	player* p1; //First player
	
	player* p2; //Second player
	
	//Deals cards to the players
	void dealCards();

	//Instantiates the draw and discard pile
	void instantiatePiles();

	//Tosses the coin to see who plays first
	int coinToss();

	//Sets up the round
	void setUpRound();



public:
	gameRound();

	//Allow for players to take turns
	void start();
};
