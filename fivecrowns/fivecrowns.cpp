/************************************************************
* Name:  Ashmin Bhandari
* Project : Five Crowns (C++)
* Class : fivecrowns
* Date : 10/24/2019
************************************************************/

#include <iostream>
#include "gameRound.h"
#include "newCardCollection.h"
#include "serialization.h"

/* *********************************************************************
Function Name: main
Purpose: This is the game driver. It starts a round, and goes until 11 rounds.
Local Variables: computerScore, it is the score of the computer at the end of all rounds
humanScore, it is the score of the human at the end of all rounds
Algorithm: Play rounds until round 11, at the end calculate scores and declare winner
********************************************************************* */
int main()
{
	//Get the singleton instance of the round
	gameRound* r = gameRound::getRound();

	//While loop until round 11, start each round
	while (r->getRoundNo() != 12) {
		r->start();
	}

	//Scores after all round ends
	int computerScore = r->getComputerScore();
	int humanScore = r->getHumanScore();

	//Neat print outs to the screen
	cout << endl << endl << "At the end of the game, the score tallys are: " << endl;
	cout << "Computer: " << computerScore << endl;
	cout << "Human: " << humanScore << endl;
	cout << endl;

	//If computer score was less, the human lost the game, say so
	if (computerScore < humanScore) {
		cout << "Sorry, you have lost this game." << endl;
	}
	
	//Otherwise, CONGRATULATIONS, the human has won the game 
	else cout << "Congratulations! You have won this game." << endl;
}
