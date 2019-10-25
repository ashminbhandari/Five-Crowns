/************************************************************
* Name:  Ashmin Bhandari
* Project : Five Crowns (C++)
* Class : gameRound
* Date : 10/24/2019
************************************************************/

#include "gameRound.h"
#include "deck.h"
#include "player.h"
#include "human.h"
#include "computer.h"
#include "newCardCollection.h"
#include <ctime>
#include <algorithm>
#include <map>
#include "serialization.h"

/* *********************************************************************
Variable Name: round
Purpose: This refers to the singleton instance of the round, which is first initialized to null or 0
********************************************************************* */
gameRound* gameRound::round = 0;

/* *********************************************************************
Function Name: gameRound
Purpose: Constructor for the game round, it sets up a round
Algorithm: Simply calls upon the setUpRound function to set up the round
********************************************************************* */
gameRound::gameRound() {
	setUpRound();
}

/* *********************************************************************
Function Name: getRound
Purpose: Gets the singleton instance of the round 
Return Value: The singleton instance of the round 
Algorithm: If a round instance has not been created then do so and return that otherwise just return the instance in use
********************************************************************* */
gameRound* gameRound::getRound() {
	if (round == 0) {
		round = new gameRound();
	}
	return round;	
}

/* *********************************************************************
Function Name: dealCards
Purpose: Deals cards to players
Return Value: The nature of the value returned by this function.
Algorithm: Shuffle the deck and then give out the number of cards in use in this specific round to both the players, i.e. deal the cards
********************************************************************* */
void gameRound::dealCards() {
	//Get the singleton deck isntance in use 
	deck* a = deck::getDeck();

	//Shuffle the deck
	a->shuffleDeck();

	//Deal the card to human player by removing the card from the deck and the pushing it back to the human hand
	for (int i = 0; i < nCards; i++) {

		//Get the card at the top and store it in a temporary location
		card temp = a->getCardAt(0); 

		//Push it back to the human hand
		human.getHand()->push_back(temp);

		//Remove that card from the deck
		a->removeCardAtTop();
	}

	//Deal the card to the computer player by removing the card from the deck and then pushing it back to the computer hand 
	for (int i = 0; i < nCards; i++) {

		//Get the card at the top and store it in a temporary location
		card temp = a->getCardAt(0);

		//Get the computer hand and push the card there
		computer.getHand()->push_back(temp);

		//Remove the card from the deck 
		a->removeCardAtTop();
	}
}

/* *********************************************************************
Function Name: instantiatePiles()
Purpose: Used during setting up the round, this function will set up the draw and discard piles
Local Variables: (a). topCard, it is a card object that holds the card currently on top of the draw pile, because the function sets up the draw pile first, the top of the draw pile 
is to put into the discard pile
(b). a, this is just he instance to the deck object which is a singleton
Algorithm: All the remaining cards in the deck after dealing will be put into the draw pile then the top of the draw pile will be put into the discard pile 
********************************************************************* */
void gameRound::instantiatePiles() {
	
	//Singleton isntance of the deck
	deck* a = deck::getDeck();

	//Iterate through the deck and then put the cards from it into the draw pile
	for (int i = 0; i < a->getDeckSize(); i++) {
		this->drawPile.push_back(a->getCardAt(i));
	}

	//This is the top card of the draw pile at this moment, to be put into the discard pile 
	card topCard = drawPile.at(0);

	//Remove the top card off drawPile
	this->drawPile.erase(this->drawPile.begin());

	//Put the top card out of draw pile into discard pile
	this->discardPile.push_back(topCard);
}

/* *********************************************************************
Function Name: coinToss
Purpose: As is evident, it tosses the coin, sees who is the winner so that the player can play first
Local Variables: call, an integer that holds the call to be made by the user i.e. heads or tails
flip, an integer that holds the result of a flip done using random number generation
Algorithm: Ask the user to call the toss, flip the coin (random number generation between 1 and 2), thus come to a result of the coin toss.
********************************************************************* */
void gameRound::coinToss() {

	//Integer that holds the call to be made by the user
	int call = 0;

	//While the call to be made is not appropirate that is the user doesnt enter 1 or a 2 then keep on asking the user for input and let them know that they are entering invalid inputs
	while (call != 1 && call != 2) {

		//Ask the user to call the toss
		cout << "Call the toss: [1 == heads | 2 == tails]: ";

		//Take in input
		cin >> call;
		cout << endl;

		//If call is not appropriate then print out an error to screen
		if (call != 1 && call != 2) {
			cout << "ERROR in input." << endl << endl;
		}
	}

	//Seed the random number generator
	srand(unsigned(time(0)));

	//Flip the coin using random number generation
	int flip = rand() % 2 + 1; 

	//Let know to user what was flipped
	cout << "Flipped ";
	if (flip == 1) {
		cout << "heads." << endl << endl;
	}
	else {
		cout << "tails. " << endl << endl;
	}

	//If the result of the flip matched the call made by the player then player 1 is human, otherwise the computer plays first
	if (flip == call) {

		//Player 1 is human
		this->p1 = &human; 

		//Player 2 is computer
		this->p2 = &computer; 

		//Set the next player as human, because they won the toss and are playing next
		this->nextPlayer = human.getName();

		//Let the user know that they won the coin toss
		cout << human.getName() <<" won the coin toss." << endl << endl;
	}

	//Otherwise, guess what, the computer is playing first
	else {

		//Set the computer up to play first
		this->p1 = &computer;

		//Set the human up to play first
		this->p2 = &human;

		//The next player obviously is the computer
		this->nextPlayer = computer.getName();

		//Let the user know that the computer won the coin toss
		cout << computer.getName() << " won the coin toss." << endl << endl;
	}

	//Let the user know that the coin has been tossed
	cout << endl << "Coin has been tossed." << endl << endl;
}

/* *********************************************************************
Function Name: setUpRound()
Purpose: It does all the setting up required at the start of the first round. 
Local Variables: (a). choice, an integer, at the start of the round to ask what the user wants to do, start from a saved position to set up the round or start a new one
(b). name, string, name of the player playing
Algorithm: Ask the user what it would like to do, start a new game or load a saved one. Proceed accordingly, if saved game is chosen, the serialization class is called upon to load the file
Otherwise, a new game is setup accordingly
********************************************************************* */
void gameRound::setUpRound() {

	//Set up the roundWinner member variable class as "This is the first round" because there have not been any roundwinners yet
	roundWinner = "This is the first round.";

	//Ask if the player wants to start a new game or load a saved game 
	string choice = "";

	//Go into a do-while loop for input validation, keep going and printing out errors until user enters a valid input
	do {
		
		//Taking in the choice of the user
		cout << "Would you like to start from a saved position or play a new game [ 1 or 2 ]:  ";
		cin >> choice;

		//If chose to start from saved position, then call upon serialization class to load the game 
		if (choice == "1") {

			//Let the user know that we are starting from a saved position
			cout << endl << "Starting from saved position.." << endl << endl;

			//Serialization isntance to load the game
			serialization savedGame;

			//Use the read functionality provided by the serialization class
			savedGame.read();

			//Current hand of the human set from the saved game 
			*this->human.getHand() = savedGame.humanHand;

			//The computer hand sent from the saved game
			*this->computer.getHand() = savedGame.computerHand;

			//Round count gotten from the saved game, this holds how many rounds there have been
			this->roundCount = savedGame.roundNo;

			//The number of cards in play in each players hand in this round which is equal to the hand of the computer or the player
			this->nCards = savedGame.computerHand.size();

			//Get the draw pile from the saved file
			this->drawPile = savedGame.drawPile;

			//Get the discard pile from the saved file
			this->discardPile = savedGame.discardPile;

			//Get the next player to paly from the saved file 
			this->nextPlayer = savedGame.nextPlayer;

			//Get the name of the human playing forom the saved file
			this->human.setName(savedGame.playerName);

			//Get the score of the human from the saved file 
			this->human.setScore(savedGame.humanScore);

			//Get the score of the computer from the saved file 
			this->computer.setScore(savedGame.computerScore);

			//Set the name of computer as "Computer". It is never going to be any different 
			this->computer.setName("Computer");

			//Set the name of the player from the saved game 
			this->human.setName(savedGame.playerName);

			//If nextPlayer gotten from the saved game is computer then player 1 is computer otherwise it is the human
			if (nextPlayer == "Computer") {
				this->p1 = &computer;
				this->p2 = &human;
			}

			//If nextPlayer gotten from the saved game is human then player 1 is human otherwise it is the computer
			else {
				this->p1 = &human;
				this->p2 = &computer;
			}
		}

		//If the user chose to start a new game, proceed accordingly
		else if (choice == "2") {

			//Letting the user know that a new game is being started 
			cout << "Starting a new game..." << endl << endl;

			//Holds the name of the player, to be entered by the user
			string name;
			
			//Prompt for the user to enter the name, and taking in the name 
			cout << "Enter player name:  ";
			cin >> name;

			//Setting the name of the human
			this->human.setName(name);

			//Setting the name of the computer, it is always going to be computer
			this->computer.setName("Computer");

			//The roundCount at the beginning is 1, the round number this is 
			this->roundCount = 1;

			//The number of cards to be played in the first round is 3
			this->nCards = 3; 

			//Having set some information up, toss the coin
			coinToss();

			//Deal the cards to the two players
			dealCards();

			//Instantiate the draw and discard piles 
			instantiatePiles();
		}

		//If the choice entered by the user was not 1 and it was not 2 then they entered a wrong input, let them know
		if (choice != "1" && choice != "2") {
			cout << "ERROR. Invalid input. Please try again." << endl << endl;
		}

		//Go until, a valid choice is entered
	} while (choice != "1" && choice != "2");
}

/* *********************************************************************
Function Name: start
Purpose: It starts up the round based on the round infomration gathered or set up
Local Variables: player1Cards & player2Cards, a newCardCollection objects which are to be instantitaed with the cards in the hand of the players
player1HasWon, player2HasWon, keeps bool tallies of whether the players have won
Algorithm: Until one or both players have won, keeps letting them have turns. If a player has gone out starts up another round with updated round information
********************************************************************* */
void gameRound::start() {

	//Update the views at the beginning of the round
	updateViews();

	//newCardCollection objects that hold the player1 and player2 cards. newCardCollection class allows for to gather information about a player's hand like have they won? how many books are there? and so on...
	newCardCollection player1Cards, player2Cards;

	//A infinite while loop unless broken from
	while (true) {

		//Set the player1Card collection according to the player1 hand
		player1Cards.setCollection(*this->p1->getHand());

		//Set the player2Card collection according to the player2 hand 
		player2Cards.setCollection(*this->p2->getHand());

		//Bools that get the return value from the newCardCollection checkMatrix functionality which calculates information about the player hand and returns a bool of whether they have won or not
		bool player1HasWon = player1Cards.checkMatrix();
		bool player2HasWon = player2Cards.checkMatrix();

		//If a player number 1 has won then proceed accordingly
		if (player1HasWon) {

			//The roundwinner is now player 1, set its name up for the scoreboards
			roundWinner = p1->getName();

			//Next player is also player 1, set its name up for the scoreboards
			nextPlayer = p1->getName();

			//A temporary instance of newCardCollection class
			newCardCollection temp;

			//Setting temp as player 2's hand
			temp.setCollection(*this->p2->getHand());

			//If player 2 has also won then proceed accrodingly
			if (temp.checkMatrix()) {

				//Let the user know that both players went out and that there is no need for score calculation
				cout << "Both players went out, so no need for score calculation." << endl;

				//The round winner is really no one because both players went out 
				roundWinner = "Both players went out.";

				//Break from the while loop
				break;
			}

			//Calculate scores for player 2, if player 2 did not win as well
			calculateScores(p2);

			//Break from the while loop
			break;
		}

		//If player 2 has won
		else if (player2HasWon) {

			//The roundwinner name will be etched as player 2's name
			roundWinner = p2->getName();

			//The next player is player 2 too
			nextPlayer = p2->getName();

			//Player 1 is allowed it's turn that is due 
			this->p1->takeTurn();

			//Create a temporary isntance of the newCardCollection class
			newCardCollection temp;

			//Set the collection as player 1's hand so as to check whether it has won or not 
			temp.setCollection(*this->p1->getHand());
			
			//If yes, palyer 1 won too, then proceed accordingly
			if (temp.checkMatrix()) {

				//Let the user know that both players went out and there is no need for score calculation
				cout << "Both players went out, so no need for score calculation." << endl;

				//Round winner is no one because both players went out, this is not technical, technically one player did win first
				roundWinner = "Both players went out.";

				//Break from the loop
				break;
			}

			//Calcaulte scores for player 1 if it did not 1 
			calculateScores(p1);

			//Break from the while loop
			break;
		}

		//Next player to play is player 1
		nextPlayer = p1->getName();

		//Update the views
		updateViews();

		//Let player take turn
		this->p1->takeTurn();

		//Same as above
		nextPlayer = p2->getName();

		updateViews();

		this->p2->takeTurn();
	}

	//If we are here means the round has ended, someone has won. Let the user know of that
	cout << endl << "---------======The round has ended======---------" << endl << endl;
	
	//Clear both the player's current hands
	p1->getHand()->clear();
	p2->getHand()->clear();

	//If computer won the last round then they start first
	if (nextPlayer == "Computer") {
		this->p1 = &computer;
		this->p2 = &human;
	}

	//Else, the human starts first
	else {
		this->p1 = &human;
		this->p2 = &computer;
	}

	//Increase the count of the round
	roundCount++;

	//Increase the number of cards being played in this new round
	nCards++;

	//Clear the draw pile for the new round
	drawPile.clear();

	//Clear the discard pile for the new roudn
	discardPile.clear();

	//Deal cards again for the new round
	dealCards();

	//Instatntiate piles for the new round
	instantiatePiles();

}

/* *********************************************************************
Function Name: printDrawPile
Purpose: Prints the draw pile 
Algorithm: Iterate through and print the draw pile using the getCardValue functionality of the card class
********************************************************************* */
void gameRound::printDrawPile() {
	for (unsigned int i = 0; i < this->drawPile.size(); i++) {
		cout << this->drawPile[i].getCardValue() << " ";
	}
	cout << endl;
}

/* *********************************************************************
Function Name: printDiscardPile
Purpose: Prints the discard pile 
Algorithm: Iterate through and print the discard pile using the getCardValue functionality of the card class
********************************************************************* */
void gameRound::printDiscardPile() {
	for (unsigned int i = 0; i < this->discardPile.size(); i++) {
		cout << this->discardPile[i].getCardValue() << " ";
	}
	cout << endl;
}

/* *********************************************************************
Function Name: updateViews
Purpose: Update the views to the screen following a certain format. This prints out most of the current state of the round to the screen.
********************************************************************* */
void gameRound::updateViews() {
	
	//The round count is printed 
	cout << "Round: " << this->roundCount << endl;
	cout << endl;

	//This is the state of the computer currently
	cout << "Computer: " << endl;

	//The score of the computer
	cout << "Score: " << computer.getScore() << endl;

	//The hand of the computer
	cout << "Hand: ";
	computer.printHand();

	//To print out the reamining cards in the computer's hand, we once again call upon newCardCollection's fucntionalities
	newCardCollection temp;

	//Setting the collection as computer's hand
	temp.setCollection(*computer.getHand());

	//Check through the hand to gather information
	temp.checkMatrix();

	//Vector of strings to hold the reamining cards yet to be matched by the player
	vector<string> remCardsInString = temp.getRemainingCards();

	//Vector of strings to hold the runs that have been made till now by the player, gather thanks to newCardCollection class
	vector<string> runsMade = temp.getRunsMade();

	//Vector of strings to hold the books made that have been made till now by the palyer, gathered thanks to newCardCollection class
	vector<string> booksMade = temp.getBooksMade();

	//The strays, i.e. the remaining cards, printing it out the screen
	cout << "Strays: ";
	for (int i = 0; i < remCardsInString.size(); i++) {
		cout << remCardsInString[i] << " ";
	}
	cout << endl;


	//Printing the books out to the screen
	cout << "Books: ";
	for (int i = 0; i < booksMade.size(); i++) {
		cout << booksMade[i] << " ";
	}
	cout << endl;

	//Printing the runs made out to the screen
	cout << "Runs: ";
	for (int i = 0; i < runsMade.size(); i++) {
		cout << runsMade[i] << " ";
	}
	cout << endl;
	cout << endl;

	//Now, printing out the human's information. We follow the same format as above
	cout << "Human: " << endl;

	//Human's score
	cout << "Score: " << human.getScore() << endl;

	//Current human's hand, printing it out to the screen
	cout << "Hand: ";
	human.printHand();

	//Setting up a newCardCollection class isntance again to gather infomration about human's hand
	newCardCollection temp1;

	//Setting the collection as human's hand 
	temp1.setCollection(*human.getHand());

	//Checking the matrix, i.e. calculating to gather the infomration about the hand of the palyer
	temp1.checkMatrix();

	//Vector of strings to store the remaining cards in the player's hand yet to be matched
	vector<string> remCardsInString1 = temp1.getRemainingCards();

	//Vector of strings, to stroe the books made by the player till now 
	vector<string> booksMade1 = temp1.getBooksMade();

	//Vector of strings, to store the runs made by the palyer till now 
	vector<string> runsMade1 = temp1.getRunsMade();

	//Printing remaining cards out to the screen
	cout << "Strays: ";
	for (int i = 0; i < remCardsInString1.size(); i++) {
		cout << remCardsInString1[i] << " ";
	}
	cout << endl;

	//Printing books out to the screen
	cout << "Books: ";
	for (int i = 0; i < booksMade1.size(); i++) {
		cout << booksMade1[i] << " ";
	}
	cout << endl;

	//Printing runs out to the screen
	cout << "Runs: ";
	for (int i = 0; i < runsMade1.size(); i++) {
		cout << runsMade1[i] << " ";
	}
	cout << endl << endl;

	//Printing out the draw pile to the screen
	cout << "Draw Pile: ";
	printDrawPile();
	cout << endl;

	//Printing out the discard pile to the screen
	cout << "Discard Pile: ";
	printDiscardPile();
	cout << endl;

	//The next player to play is also printed
	cout << "Next Player: " << this->nextPlayer;
	cout << endl << endl;

	//Printing out what happened last round 
	cout << "What happened last round?: " << roundWinner << endl << endl;
}

/* *********************************************************************
Function Name: getDrawPile
Purpose: Gets a reference to the draw pile being used in the round
Return Value: Reference to the vector of cards being used as the draw pile  
********************************************************************* */
vector <card>* gameRound::getDrawPile() {
	return &this->drawPile;
}

/* *********************************************************************
Function Name: getDiscardPile
Purpose: Gets a reference to the discard pile being used in the round
Return Value: Reference to the vector of cards being used as the discard pile 
********************************************************************* */
vector <card>* gameRound::getDiscardPile() {
	return &this->discardPile;
}

/* *********************************************************************
Function Name: getRoundNo
Purpose: Gets the current number of the round being played
Return Value: An integer of the current round count by value 
********************************************************************* */
int gameRound::getRoundNo() {
	return this->roundCount;
}

/* *********************************************************************
Function Name: calculateScores
Purpose: Calculates scores of the player provided as argument
Parameters: A pointer to the player for whose the score is to be calcaulted
Algorithm: Simply adds up the point values of cards that remain without book or run matches the given player's hand
********************************************************************* */
void gameRound::calculateScores(player* p) {

	//A neat print out to the screen
	cout << "Score calculation logic: ";

	//Getting the score of the player
	int playerScore = p->getScore();

	//Getting the hand of the player
	vector<card>* playerHand = p->getHand();

	//Create an instance of the newCardCollection class
	newCardCollection temp;

	//Set it as the player's hand
	temp.setCollection(*playerHand);

	//Gather information about the hand by checking it for books, runs, cards that remain etc.
	temp.checkMatrix();

	//The remaining cards gotten via the newCardCollection instance temp
	vector<string> remCardsAsString = temp.getRemainingCards();

	//The remaining cards to be store as vector of cards instead of vector of strings
	vector<card> remCards;

	//Iterate through the reaminig cards as string and create remaing cards as card objects
	for (int i = 0; i < remCardsAsString.size(); i++) {
		string theCard = remCardsAsString.at(i);
		string rank(1, theCard[0]);
		string suit(1, theCard[1]);
		remCards.push_back(card(rank, suit));
	}

	//Iterate through the remaining cards and calculate the score, adding it to the player's tally that already exists
	for (int i = 0; i < remCards.size(); i++) {

		//Neat print outs about how the score calculation was done printed out to the screen
		cout << "[" << remCards.at(i).getCardValue() << "=" << remCards.at(i).getRankValue() << "] ";

		//The player score being added
		playerScore = playerScore + remCards.at(i).getRankValue();
	}

	//The count of the special cards that remain in the player's hand, special cards are jokers and wildcards.  
	int specialCardsRemaining = temp.getSpecialCardsCount();

	//The count of the wild cards that was orignially in the player's hand
	int wildCardCount = temp.getWildCardCount();

	//If wildcards remain without a run or a book match then penalties will be added to the score
	for (int i = 0; i < specialCardsRemaining; i++) {
		if (wildCardCount > 0) {
			cout << "[WILDCARD=20] ";
			playerScore = playerScore + 20;
			wildCardCount--;
		}
		else {
			cout << "[JOKER=20] ";
			playerScore = playerScore + 50;
		}
	}

	//Set the new score of the play8er
	p->setScore(playerScore);

	//Neat print out of the player score at the end
	cout << " = " << playerScore << endl;
}

/* *********************************************************************
Function Name: getComputerScore
Purpose: Gets the computer score
Return Value: Integer value of the score of computer
Algorithm: Return score for that player which is computer
********************************************************************* */
int gameRound::getComputerScore() {
	//The player 1 score
	int player1Score = p1->getScore();

	//Player 2 score
	int player2Score = p2->getScore();

	//If player 1 is computer then return this  score
	if (p1->getName() == "Computer") {
		return player1Score;
	}

	//Else if player 2 is computer then return this score
	else if (p2->getName() == "Computer") {
		return player2Score;
	}
}

/* *********************************************************************
Function Name: getHumanScore
Purpose: Gets the human player score
Return Value: Integer value of the score of human
Algorithm: Return score for that player which is human
********************************************************************* */
int gameRound::getHumanScore() {
	//The player 1 score
	int player1Score = p1->getScore();


	//The player 2 score
	int player2Score = p2->getScore();

	//If player 1 is computer the return player 2's score
	if (p1->getName() == "Computer") {
		return player2Score;
	}

	//If player 2 is computer then return palyer 1 score
	else if (p2->getName() == "Computer") {
		return player1Score;
	}
}

/* *********************************************************************
Function Name: getComputerHand
Purpose: Gets a reference to the computer's hand
Return Value: A reference to vector of card objects, referring to the computer's hand
********************************************************************* */
vector<card>* gameRound::getComputerHand() {
	if (p1->getName() == "Computer") return p1->getHand();
	else return p2->getHand();
}

/* *********************************************************************
Function Name: getHumanHand
Purpose: Gets a reference to the human's hand
Return Value: A reference to vector of card objects, referring to the human's hand
********************************************************************* */
vector<card>* gameRound::getHumanHand() {
	if (p1->getName() == "Computer") return p2->getHand();
	else return p1->getHand();
}