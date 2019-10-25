/************************************************************
* Name:  Ashmin Bhandari
* Project : Five Crowns (C++)
* Class : player
* Date : 10/24/2019
************************************************************/

#include "player.h"
#include "gameRound.h"
#include "newCardCollection.h"
#include <algorithm>

/* *********************************************************************
Function Name: pickCard
Purpose: Overriden by it's children: human and computer.
********************************************************************* */
void player::pickCard() {
}

/* *********************************************************************
Function Name: dropCard
Purpose: Overriden by it's children: human and computer.
********************************************************************* */
void player::dropCard() {
}

/* *********************************************************************
Function Name: printHand
Purpose: Prints the hand out to the screen
********************************************************************* */
void player::printHand() {
	for (int i = 0; i < hand.size(); i++) {
		cout << hand[i].getCardValue() << " ";
	}
	cout << endl;
}

/* *********************************************************************
Function Name: getHand
Purpose: Gets a reference to the player's hand
Return value: Reference to a vector of card object i.e. the player's hand
********************************************************************* */
vector <card>* player::getHand() {
	return &this->hand;
}

/* *********************************************************************
Function Name: takeTurn
Purpose: To be overriden in child classes
********************************************************************* */
void player::takeTurn() {
}

/* *********************************************************************
Function Name: getName
Purpose: Gets the player name
Return Value: The player name as a string
********************************************************************* */
string player::getName() {
	return name;
}

/* *********************************************************************
Function Name: setName
Purpose: Sets the player name
********************************************************************* */
void player::setName(string name) {
	this->name = name;
}

/* *********************************************************************
Function Name: getScore
Purpose: Gets the player score
Return Value: The player score as a integer
********************************************************************* */
int player::getScore() {
	return score;
}

/* *********************************************************************
Function Name: setScore
Purpose: Sets the player score
********************************************************************* */
void player::setScore(int score) {
	this->score = score;
}

/* *********************************************************************
Function Name: printDetails
Purpose: Print the details of the player out to the screen
********************************************************************* */
void player::printDetails() {
	
	//Instantiate a newCardCollection object and set it to the player's hand
	newCardCollection temp;
	temp.setCollection(*getHand());
	
	//Check if player has won
	bool hasWon = temp.checkMatrix();

	//Get the remaining cards in hand, the runs made and the books made
	vector<string> remainingCards = temp.getRemainingCards();
	vector<string> runsMade = temp.getRunsMade();
	vector<string> booksMade = temp.getBooksMade();

	//Neatly print out the information to the screen
	cout << "Here's what happened during this move: " << endl;
	cout << "The hand: ";
	printHand();

	//Print out remaining cards
	cout << "Remaining cards: ";
	for (int i = 0; i < remainingCards.size(); i++) {
		cout << remainingCards[i] << " ";
	}
	cout << endl;

	//Print out runs made
	cout << "Runs made: ";
	for (int i = 0; i < runsMade.size(); i++) {
		cout << runsMade[i] << " ";
	}
	cout << endl;

	//Print out books made
	cout << "Books made: ";
	for (int i = 0; i < booksMade.size(); i++) {
		cout << booksMade[i] << " ";
	}
	cout << endl;

	//If the user won, then show that they went out 
	if (hasWon) {
		cout << this->getName() << " thus has successfully gone out." << endl;
	}
	cout << endl << endl;
}