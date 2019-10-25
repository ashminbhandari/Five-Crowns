/************************************************************
* Name:  Ashmin Bhandari
* Project : Five Crowns (C++)
* Class : serialization
* Date : 10/24/2019
************************************************************/

#include "serialization.h"
#include <fstream>
#include <sstream>
#include <vector>

/* *********************************************************************
Function Name: read
Purpose: For serialization purposes, reads from a given file
********************************************************************* */
void serialization::read() {

	//Set the fail flag as true at first
	bool fail = true;

	//Have we not parsed the score for computer yet?
	bool scoreForComputer = true;

	//Have we not parsed the score for computer yet?
	bool handForComputer = true;

	//Do-while loop until valid input is entered
	do {

		//Get the file name
		string fileName;
		cout << "Enter a filename to read from: ";
		cin >> fileName;

		//Read in the file 
		ifstream inFile(fileName);

		//If failed give out error 
		if (inFile.fail()) {
			cout << "ERROR. The given file name does not exist." << endl << endl;
		}

		//Else, read in each line and extract the information
		else {

			//Iterate through all lines
			for (string line; getline(inFile, line);) {

				//Taking out the round number out of the file
				if (line.find("Round") != string::npos) {
					string numberString = "";
					for (int i = 7; i < line.size(); i++) {
						numberString = numberString + line.at(i);
					}
					roundNo = stoi(numberString);
				}

				//Taking out the computer and player scores out of the file
				if (line.find("Score") != string::npos) {
					if (scoreForComputer) {
						string compScore = "";
						for (int i = 10; i < line.size(); i++) {
							compScore = compScore + line.at(i);
						}
						computerScore = stoi(compScore);
						scoreForComputer = false;
					}
					else {
						string humScore = "";
						for (int i = 10; i < line.size(); i++) {
							humScore = humScore + line.at(i);
						}
						humanScore = stoi(humScore);
					}
				}

				//Taking out the computer hand out of the pile
				if (line.find("Hand") != string::npos) {
					if (handForComputer) {
						for (string::iterator it = line.begin() + 9; it != line.end(); ++it) {
							if (*it != ' ') {
								string rank = string(1, *it);
								string suit = string(1, *++it);
								computerHand.push_back(card(rank, suit));
							}
						}
						handForComputer = false;
					}
					else {
						for (string::iterator it = line.begin() + 9; it != line.end(); ++it) {
							if (*it != ' ') {
								string rank = string(1, *it);
								string suit = string(1, *++it);
								humanHand.push_back(card(rank, suit));
							}
						}
					}
				}

				//Taking out the draw pile 
				if (line.find("Draw") != string::npos) {
					for (string::iterator it = line.begin() + 11; it != line.end(); ++it) {
						if (*it != ' ') {
							string rank = string(1, *it);
							string suit = string(1, *++it);
							drawPile.push_back(card(rank, suit));
						}
					}
				}

				//Taking out the discard pile 
				if (line.find("Discard") != string::npos) {
					for (string::iterator it = line.begin() + 14; it != line.end(); ++it) {
						if (*it != ' ') {
							string rank = string(1, *it);
							string suit = string(1, *++it);
							discardPile.push_back(card(rank, suit));
						}
					}
				}

				//Taking out the next player
				if (line.find("Next") != string::npos) {
					for (string::iterator it = line.begin() + 13; it != line.end(); ++it) {
						nextPlayer = nextPlayer + *it;
					}
				}

				//Taking out the player name
				if (line.find("Name") != string::npos) {
					for (string::iterator it = line.begin() + 13; it != line.end(); ++it) {
						playerName = playerName + *it;
					}
				}
			}
			fail = false;
		}
	} while (fail);
}


/* *********************************************************************
Function Name: save
Purpose: For serialization purposes, saves to a given file 
********************************************************************* */
void serialization::save(int roundNo, int computerScore, int humanScore, vector <card> computerHand, vector <card> humanHand, vector<card> drawPile, vector<card>discardPile, string nextPlayer, string playerName, string saveFileName) {
	ofstream saveFile;
	saveFile.open(saveFileName);
	saveFile << "Round: " << roundNo << "\n";
	saveFile << "Computer: \n";
	saveFile << "   Score: " << computerScore << "\n";
	saveFile << "   Hand: ";
	for (int i = 0; i < computerHand.size(); i++) {
		saveFile << computerHand.at(i).getCardValue() << " ";
	}
	saveFile << "\n";
	saveFile << "Human: \n";
	saveFile << "   Score: " << humanScore << "\n";
	saveFile << "   Hand: ";
	for (int i = 0; i < humanHand.size(); i++) {
		saveFile << humanHand.at(i).getCardValue() << " ";
	}
	saveFile << "\n";
	saveFile << "Draw Pile: ";
	for (int i = 0; i < drawPile.size(); i++) {
		saveFile << drawPile.at(i).getCardValue() << " ";
	}
	saveFile << "\n";
	saveFile << "Discard Pile: ";
	for (int i = 0; i < discardPile.size(); i++) {
		saveFile << discardPile.at(i).getCardValue() << " ";
	}
	saveFile << "\n";
	saveFile << "Next Player: " << nextPlayer << "\n";
	saveFile << "Player Name: " << playerName << "\n";
}