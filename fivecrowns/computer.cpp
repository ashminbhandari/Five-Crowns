/************************************************************
* Name:  Ashmin Bhandari
* Project : Five Crowns (C++)
* Class : Computer
* Date : 10/24/2019
************************************************************/

#include "computer.h"
#include <ctime>
#include "gameRound.h"
#include "newCardCollection.h"
#include <algorithm>
#include <time.h>
#include "brain.h"
#include <cstdlib>

/* *********************************************************************
Function Name: takeTurn
Purpose: Allows for the computer to take it's turn. The computer has a number of choices that it can 
make during it's turn and it allows for it to do that.
Local Variables: a. choice, string that holds what the computer wishes to do
Algorithm: Asks the user what it would like the computer to do. It may save the game, let the computer make it's move or exit the game.
If save the game is chosen, then ask for name of the save file and save the game.
If make the move is chosen, then the computer calls upon the brain class to think about which card to pick and which to drop.
********************************************************************* */
void computer::takeTurn() {
	//A string that holds the choice that the computer is to make
	string choice = "";

	//A do-while loop that makes sure that the correct input is entered. It keeps on asking for inputs until a valid input is entered. Lets the user know if invalid input is entered. 
	do {

		//Prompt for the user asking for what it wants to do
		cout << "What would you like the computer to do? \n 1. Save the game \n 2. Let the computer make a move \n 3. Quit the game \n Enter the appropriate number: ";
		cin >> choice;

		//Print out an ERROR if invalid input was entered
		if (choice != "1" && choice != "2" && choice != "3" && choice != "4") {
			cout << "ERROR. Invalid input. Try again." << endl << endl;
		}

		//Call upon the singleton round instance
		gameRound* r = gameRound::getRound();

		//If a correct input, in this case 1, which means to save the game was entered then go ahead and start the proceedings
		if (choice == "1") {

			//Set up a serialization instance
			serialization s;

			//Ask for the user to enter the name of the save file, a file with this name will be created and all the information saved upon
			cout << "Enter the name of the save file: ";
			string saveFileName;
			cin >> saveFileName;

			//Use the serialization instance to save the game using all the information gathered from the round instance.
			s.save(r->getRoundNo(), r->getComputerScore(), r->getHumanScore(), *r->getComputerHand(), *r->getHumanHand(), *r->getDrawPile(), *r->getDiscardPile(), r->getNextPlayer(), getName(), saveFileName);

			//Let the user know that the game was saved
			cout << "Game saved to file " << saveFileName << endl << endl;
		}

		//If a correct input, in this case 2, which means to 'make the move' is entered then go ahead and start the proceedings accordingly
		else if (choice == "2") {

			//Create a brain instance, so as to be able to think
			brain computerBrain;

			//Holds the card that is picked by the thinking done by the brain
			card picked;

			//Get what is to be done according to the thinking done by the brain, the mode selected for thinking here is extended
			pair<int, card> whatToDo = computerBrain.think(*getHand(), "extended");

			//If thinking says to pick the discard pile then pick from it 
			if (whatToDo.first == 0) {

				//Get the pointer to the discard pile from the singleton round instance. We are operating here on the actual discard pile 
				vector <card>* tempVec = r->getDiscardPile();

				//Since the discard pile is to be picked upon, the top of the discard pile is taken
				picked = tempVec->at(0).getCard();

				//Top of the discard pile is pushed back into the hand of the player
				getHand()->push_back(picked);

				//The top of the discard pile is erase
				tempVec->erase(tempVec->begin());
			}

			//If thinking says to pick from the draw pile then do so
			else {

				//Get the pointer to the actual draw pile being used in the round 
				vector <card>* tempVec = r->getDrawPile();

				//The picked card is the card at the top of the draw pile
				picked = tempVec->at(0).getCard();

				//Push the draw pile card into the player hand 
				this->getHand()->push_back(picked);

				//Erase the top draw pile card
				tempVec->erase(tempVec->begin());
			}

			//Drop the card that was suggested by the thinking done by iterating through the hand and finding the card suggested 
			for (int i = 0; i < getHand()->size(); i++) {

				//If the card at hand at this point in the iteration is the card suggested then remove it and insert it into the discard pile
				if (getHand()->at(i).getCardValue() == whatToDo.second.getCardValue()) {
					
					//Inserting the card removed to the discard pile 
					r->getDiscardPile()->insert(r->getDiscardPile()->begin(), getHand()->at(i).getCard());

					//Erasing the card from the hand
					getHand()->erase(getHand()->begin() + i);
				}
			}

			//Print out what was just done by the computer 
			cout << "The computer picked the card: " << picked.getCardValue() << " and dropped the card: " << whatToDo.second.getCardValue() << endl << endl;

			//Print out the current details of the player after the move happened
			printDetails();
		}

		//If the user chose to exit, do so
		else if (choice == "3") {
			exit(0);
		}

		//Keeps looping until a move was said to be made by the computer
	} while (choice != "2");
	
	
}

