#pragma once

#include "player.h"
#include "card.h"
#include "human.h"
#include "computer.h"
#include "serialization.h"

class gameRound {
private:
	//Singleton instance of the round 
	static gameRound* round;

	//Keeps track of which round is currently playing 
	int roundCount; 

	//Number of cards to be used in a round, starts at 3 
	int nCards; 

	//Wild card
	card wildCard; 
	
	//The draw pile 
	vector <card> drawPile;

	//The discard pile, stored as a vector of cards
	vector <card> discardPile;
	
	//Who's playing?
	string nextPlayer;

	human human; //Human player
	
	computer computer; //Computer player

	player* p1;
	
	player* p2; 
	
	//Deals cards to the players
	void dealCards();

	//Instantiates the draw and discard pile
	void instantiatePiles();

	//Tosses the coin to see who plays first
	void coinToss();

	//Print the draw pile
	void printDrawPile();

	//Print the discard pile
	void printDiscardPile();
	
	//Update the views
	void updateViews();

	//Private constructor for round
	gameRound();

	//Calculate the player scores
	void calculateScores(player*);

	string roundWinner;

public:
	//Get round
	static gameRound* getRound();

	//Sets up the round
	void setUpRound();

	//Allow for players to take turns
	void start();

	//Get draw pile 
	vector <card>* getDrawPile();

	//Get discard pile
	vector <card>* getDiscardPile();

	//Gets the round number
	int getRoundNo();

	//Gets human score
	int getHumanScore();

	//Get computer score
	int getComputerScore();

	//Get computer hand 
	vector<card>* getComputerHand();

	//Get human hand 
	vector <card>* getHumanHand();

	//Get next player
	string getNextPlayer() {
		return nextPlayer;
	}
};
