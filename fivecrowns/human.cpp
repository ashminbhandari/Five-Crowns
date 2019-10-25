/************************************************************
* Name:  Ashmin Bhandari
* Project : Five Crowns (C++)
* Class : human
* Date : 10/24/2019
************************************************************/

#include "human.h"
#include "gameRound.h"
#include "brain.h"
#include <cstdlib>
#include "newCardCollection.h"

/* *********************************************************************
Function Name: pickCard
Purpose: Allows for the player to pick a card
Local Variables: (a). fromWhichToPick, the integer choice to be asked for from the user. It denotes from which pile to pick.
Algorithm: Simply, asks the user for input and does what it tells it. Pick from the draw pile or the discard pile?
********************************************************************* */
void human::pickCard() {

	//What is the user going to do? Pick from darw pile or discard pile? Ask for input.
	int fromWhichToPick = 0;

	//While the input given is not valid, keep looping
	while (fromWhichToPick != 1 && fromWhichToPick != 2) {

		//Prompt the user to pick
		cout << endl;
		cout << "Do you want to pick from the draw pile or the discard pile? \n\nChoose: [1 == from draw pile | 2 == from discard pile] : ";
		cin >> fromWhichToPick;
		cout << endl;

		//If an invalid input is given, output that to the screen and loop back again
		if (fromWhichToPick != 1 && fromWhichToPick != 2) {
			cout << "ERROR in input." << endl << endl;
		}
	}

	//Get the singleton round instance
	gameRound* r = gameRound::getRound(); 

	//If '1' was chosen, pick from the draw pile
	if (fromWhichToPick == 1) {

		//Get the draw pile from the round instance
		vector <card>* tempVec = r->getDrawPile();

		//Get the top card out of the draw pile
		card temp = tempVec->at(0).getCard();

		//Show which card was drawn by the player
		cout << "Player picked card : " << temp.getCardValue() << endl << endl;

		//Push the card picked to the player's hand
		this->getHand()->push_back(temp);

		//Erase the top of the draw pile 
		tempVec->erase(tempVec->begin());
	}

	//Else, '2' was chosen, so pick the discard pile card
	else {

		//Get the discard pile from the singleton round instance
		vector <card>* tempVec = r->getDiscardPile();

		//Show that the player picked the discard pile card
		cout << "Player picked card : " << tempVec->at(0).getCardValue() << endl << endl;

		//Push the discard pile card into the hand
		this->getHand()->push_back(tempVec->at(0).getCard());

		//Remove the top card of the discard pile 
		tempVec->erase(tempVec->begin());
	}
}

/* *********************************************************************
Function Name: dropCard
Purpose: Allows for the player to drop a card
Local Variables: (a). whichCardToDrop, the 'string' choice to be asked for from the user. It denotes from which card to drop
Algorithm: Simply, asks the user for the card to drop, checks whether that card exists in the hand, if so drops it, if not asks again
********************************************************************* */
void human::dropCard() {

	//Get the singleton round instance
	gameRound* r = gameRound::getRound();

	//Set a bool that the card is not yet removed
	bool notRemoved = true;
	do {

		//String to hold which card the user wants to drop
		string whichCardToDrop;

		//Prompt for the user
		cout << "Which card do you want to drop? \n\nChoose: ";
		cin >> whichCardToDrop;
		cout << endl;

		//Iterate through the hand of the user and if the said card exists then remove it, otherwise notRemoved is still true
		for (int i = 0; i < getHand()->size(); i++) {

			//If the current iteration matches which card the user wishes to drop, drop it 
			if (getHand()->at(i).getCardValue() == whichCardToDrop) {

				//Insert the card into the discard pile 
				r->getDiscardPile()->insert(r->getDiscardPile()->begin(),getHand()->at(i).getCard());

				//Let the user know that the card was dropped
				cout << "Player dropped card : " << getHand()->at(i).getCardValue() << endl << endl;

				//Erase the card from the player's hand as well
				getHand()->erase(getHand()->begin() + i);

				//Set not removed as false as we just removed the card
				notRemoved = false;
			}
		}

		//If not yet removed, that means the card was not in the user's hand. Let the user know that this is the case
		if (notRemoved) {
			cout << "ERROR in input. " << whichCardToDrop << " is not in your hand." << endl << endl;
		}

		//Loop until player drops a card
	} while (notRemoved);
}

/* *********************************************************************
Function Name: takeTurn
Purpose: Allows for the player's turn. It has a couple of things it can do. Namely, save the game, make a move, ask for help, try and go out or exit the game
Local Variables: (a). choice, stores the choice of the user as string
Algorithm: Simply, asks the user for input and do what it tells you. If asked for help, call upon a brain instance and think
********************************************************************* */
void human::takeTurn() {

	//A string that holds the choice of the user, initialized as an empty string
	string choice = "";

	//A do-while loop that keeps going until a valid input is entered
	do {

		//Prompt the user for input 
		cout << "What would you like to do? \n 1. Save the game \n 2. Make a move \n 3. Ask for help \n 4. Can I go out? \n 5. Exit the game \n Enter the appropriate number: ";
		cin >> choice;

		//If wrong choice is entered, then print out an error
		if (choice != "1" && choice != "2" && choice != "3" && choice != "4") {
			cout << "ERROR. Invalid input. Try again." << endl << endl;
		}

		//If user chose to save the game, then call upon the serialization class to serialize the state
		if (choice == "1") {

			//Get the singleton round instance
			gameRound* r = gameRound::getRound();

			//Set up a serialization instance
			serialization s;

			//Prompt user for the save file name 
			cout << "Enter the name of the save file: ";
			string saveFileName;
			cin >> saveFileName;

			//Save the game with all required states and let the user know of the success
			s.save(r->getRoundNo(), r->getComputerScore(), r->getHumanScore(), *r->getComputerHand(), *r->getHumanHand(), *r->getDrawPile(), *r->getDiscardPile(), r->getNextPlayer(), getName(), saveFileName);
			cout << "Game saved to file " << saveFileName << endl << endl;
		}

		//If user chose to take a turn then, call upon related functions to do so
		else if (choice == "2") {

			//Let it pick card
			pickCard();

			//Let it drop card
			dropCard();

			//Prin the details of the move out to the screen
			printDetails();
		}

		//If the user asked for help, call upon the brain to think
		else if (choice == "3") {
			//The choice stored as string. Needed for whether or not they want the regular or the extended help mode 
			string choice = "";

			//Creating a brain instance in order to think
			brain Brain;

			//A do while loop that makes sure that a correct input is entered
			do {

				//Prompt the user for what help mode they would like to use
				cout << "  Help modes: (1). Regular : Will not look at the draw pile card. (2). Extended: Will look at the draw pile card." << endl;
				cout << "  REGULAR or EXTENDED? [1 or 2]: ";
				cin >> choice;

				//If wrong input was entered, print out error 
				if (choice != "1" && choice != "2") {
					cout << "ERROR. Invalid input entered. Try again." << endl << endl;
				}
				
				//If choice is 1 then start on the regular help mode, get brain's thoughts 
				if (choice == "1") {
					pair<int, card> thought = Brain.think(*getHand(),"regular");
				}

				//If choice is 2 then start on the extended help mode, get brain's thoughts
				else if (choice == "2") {
					pair<int, card> thought = Brain.think(*getHand(), "extended");
				}

				//Go until valid input is entered
			} while (choice != "1" && choice != "2");
		}

		//If the user asked if it can go out or not? Let the user know if it can do so or not.
		else if (choice == "4") {

			//Call upon the newCardCollection's functionalities once again
			newCardCollection temp;

			//Set the newCardCollection isntance to the players hand 
			temp.setCollection(*getHand());

			//Check if the user can go out 
			bool canGoOut = temp.checkMatrix();
			
			//If yes, can go out then let the user know 
			if (canGoOut) {
				cout << endl << "Yes, you can go out. All of your cards have a book or a run." << endl;
			}

			//Otherwise, let the user know that they cannot go out yet and let them know of what needs to be done in order to do so
			else {
				
				//Letting the user know 
				cout << endl << "No, you can not go out yet." << endl;

				//Letting the user know of the stray cards in their hand
				cout << "These are the stray cards in your hand in need of a book or a run: ";

				//Getting the stray cards from the newCardCollection class instance created above
				vector<string>remCards = temp.getRemainingCards();

				//Printing the stray cards out for the user
				for (int i = 0; i < remCards.size(); i++) {
					cout << remCards[i] << " ";
				}
				cout << endl;

				//Letting thme know that the above remaining cards need to be matched
				cout << "In order to go out, you need to match the cards above first." << endl << endl;
			}
			
		}

		//If wishes to exit then simply exit
		else if (choice == "5") {
			cout << endl << "Game has been exited." << endl;
			exit(0);
		}
		
		//Keep looping until user makes the move
	} while (choice != "2");
}
