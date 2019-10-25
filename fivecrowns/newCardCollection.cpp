/************************************************************
* Name:  Ashmin Bhandari
* Project : Five Crowns (C++)
* Class : newCardCollection
* Date : 10/24/2019
************************************************************/

#include "newCardCollection.h"
#include <algorithm>
#include "gameRound.h"

/* *********************************************************************
Function Name: setCollection
Purpose: Sets the collection up according to a vector of cards provided, this is the constructor of the class
********************************************************************* */
void newCardCollection::setCollection(vector<card>collection) {
	
	//Setting the internal collection member as the collection provided as argument to this function
	this->collection = collection;

	//Setting the internal copyCollection memeber, which is just a copy to make changes upon as the collection provided as arguemnt to this function
	this->copyCollection = collection;

	//Initializing the jokerCount as 0, later the jokerCount will be calculated
	jokerCount = 0;

	//Initilzation the wildCardCount as 0, later the wildCardCount will be calculated
	wildCardCount = 0;

	//Initializing the specialCards count as 0, later the special cards will be calculated
	specialCards = 0;

	//Clearing the remaining cards vector 
	remainingCards.clear();

	//Clearing the books made vector
	booksMade.clear();

	//Clearing the runs made vector
	runsMade.clear();

	//Constructing a matrix out of the collection provided, integral to our strategy
	constructMatrix();

	//Duplicating the card collection as string 
	for (int i = 0; i < collection.size(); i++) {
		collectionInString.push_back(collection[i].getCardValue());
	}
}

/* *********************************************************************
Function Name: constructMatrix
Purpose: Constructs a matrix based on the collection that this instance was set up as. The horizontal values stand for the rank and the vertical values stand for the suit.
Local Variables: If any local variable is an array, structure or object, list its name and the purpose for which it is used.
Algorithm: Sets up the matrix according to the integer rank value and the integer suit value of the card
********************************************************************* */
void newCardCollection::constructMatrix() {

	//Getting the round instance, for to get the round number
	gameRound* r = gameRound::getRound();

	//The matrix initilzatied as all 0's
	theMatrix = { {0,0,0,0,0,0,0,0,0,0,0},
				  {0,0,0,0,0,0,0,0,0,0,0},
				  {0,0,0,0,0,0,0,0,0,0,0},
				  {0,0,0,0,0,0,0,0,0,0,0},
				  {0,0,0,0,0,0,0,0,0,0,0} };
	
	//Only adding cards that are not jokers or wildcards to the matrix. 
	for (auto it = copyCollection.begin(); it != copyCollection.end(); it++) {

		//If card is not joker or wildcard, then increment the matrix value at that index
		if (!it->isJoker() && it->getRankValue() != r->getRoundNo() + 2) {
			int suitIndex = it->getSuitValue();
			int rankIndex = it->getRankValue() - 3;
			theMatrix[suitIndex][rankIndex]++;
		}
	}

	//Getting the joker count and the wild card count from the collection provided
	for (auto it = copyCollection.begin(); it != copyCollection.end(); it++) {
		
		//If card is joker, then increment jokerCount
		if (it->isJoker()) {
			jokerCount++;
		}

		//If card has rank that is 2 sums greater than the round count then that is a wildCard so increment the wildCardCount
		if (r->getRoundNo() + 2 == it->getRankValue()) {
			wildCardCount++;
		}
	}		

	//Special cards sum is just the sum of the jokers and the wildcards in the collection
	specialCards = jokerCount + wildCardCount;
}

/* *********************************************************************
Function Name: updateMatrix
Purpose: This function will decrease the matrix value at the given index. 
Parameters: (a). meld, a vector of pair of integers and integers, which hold the co ordinates of the indexes to be updated or decreased
(b). isY, a bool. Since we need a different treatment for the indexes being updated along the vertical, i.e. for books rather than runs, this bool acts a flag
Algorithm: If the index to be updated is for a run that is successfully identified in the matrix, then we simply decrease the matrix value at that index by 1. 
However, if the index to be updated is for a book that is successfully identified in the matrix, then we set the matrix value at that index to be 0. This is because 
there can be two cards of the same rank and suit for a book.
********************************************************************* */
void newCardCollection::updateMatrix(vector<pair<int,int>> meld, bool isY) {	

	//Iterate through the coordinates, which are for a meld, provided as argument
	for (int i = 0; i < meld.size(); i++) {

		//If the matrix value at that index is greater than or equal to 1, that means a decrement can be done then proceed
		if(theMatrix[meld.at(i).first][meld.at(i).second] >= 1) {			

			//If the meld coordinates provided is for a book then proceed accordingly
			if (isY) {

				//Set the matrix value at that index to 0
				theMatrix[meld.at(i).first][meld.at(i).second] = 0;

				//Since this counts as a book that was made, convert the matrix index to actual card string value and push it back to the booksMade vector 
				for (int k = 0; k < theMatrix[meld.at(i).first][meld.at(i).second]; k++) {
					booksMade.push_back(matrixIndexToCardValue(meld.at(i).first, meld.at(i).second));
				}
			}

			//Otherwise, the coordinates are for a run
			else {

				//Decrease the matrix value at that index by 1 
				theMatrix[meld.at(i).first][meld.at(i).second]--;

				//Push the actual card values corresponding to the matrix indexes into the runsMade vector since a run was just made
				runsMade.push_back(matrixIndexToCardValue(meld.at(i).first, meld.at(i).second));
			}
		}
	}
}

/* *********************************************************************
Function Name: matrixSum
Purpose: It adds up all the values at all the indexes of the matrix 
Return Value: Integer value of the above genereated sum, the sum of all integer values within the matrix
Local Variables: matrixSum, integer that holds the sum of the matrix
Algorithm: Iterate through the matrix and add up the integer values at all indexes of the matrix, return the sum at the end
********************************************************************* */
int newCardCollection::matrixSum() {

	//Initialize the sum as 0
	int matrixSum = 0;

	//Iterate through the matrix and add up the value at matrix indexes to the matrix sum
	for (int i = 0; i < theMatrix.size(); i++) {
		for (int j = 0; j < theMatrix[i].size(); j++) {
			matrixSum = matrixSum + theMatrix[i][j];
		}
	}

	//Return the matrixSum as from the above calculation
	return matrixSum;
}

/* *********************************************************************
Function Name: passI
Purpose: This is the first pass to be made at a given coordinate in the matrix in order to check for books or runs along that index. 
Since one card can only be part of one book or a run, there is some prioritizing that needs to be done. This pass makes sure that the card goes to that run which is the most in need.
Parameters: (a) i, the index along the x-axis, (b) j, the index along the y-axis of the matrix
Algorithm: We gather the size of the run along the x-axis and the size of the book along the y-axis. The one that is the lesser size requires more attention. 
We update the matrix along the axis that requires more attention.
********************************************************************* */
void newCardCollection::passI(int i, int j) {
	//Check for horizontal meld, i.e. a run. This thus holds how many horizontal consecutive 1's there are from index i, j
	int xTotal = 0;

	//Vector that holds the indexes for a horizontal meld
	vector <pair<int, int>> xMeld;
	xMeld.clear();

	//Start at jIndex provided
	int jIndex = j;

	//Do while a 0 is not hit, moving towards the right. A 0 is hit means that the run ends there
	do {

		//If hit 0, break out of the loop, we hit the end of the run
		if (theMatrix[i][jIndex] == 0) {
			break;
		}
		
		//If not, add 1 to the size of the horizontal meld, or a run
		xTotal = xTotal + 1;

		//Push back the indexes of the horizontal meld we are currently finding
		xMeld.push_back(make_pair(i, jIndex));

		//Increase the jIndex so as to move more towards the right 
		jIndex++;

		//If we hit the end of the matrix, exit
	} while (jIndex < theMatrix[i].size());

	//We must also search towards the left from the index that was provided.
	//Only decrease jIndex for a search towards the left if the jIndex is greater than 0. Otherwise, we run into a nasty error
	if (j > 0) {
		jIndex = j - 1;
	}

	//Do while a 0 is not hit, moving towards the left
	do {
		if (theMatrix[i][jIndex] == 0) {
			break;
		}

		//Adding up to the size of the meld we are currently finding
		xTotal = xTotal + 1;

		//Pushing back to the index of the run we are currently finding 
		xMeld.push_back(make_pair(i, jIndex));

		//Decreasing the jIndex so as to move towards the left
		jIndex--;

		//If we hit the end of the matrix quit out 
	} while (jIndex >= 0);

	//At this point, we have figured out the horizontal run. Now we move into the vertical book. 

	//Check for a vertical meld, i.e. a book
	//Holds how many vertical 1's there are along the line of point i,j in the matrix
	int yTotal = 0;

	//Vector that holds the vertical meld
	vector<pair<int, int>>yMeld;
	yMeld.clear();

	//Start at iIndex of 0
	int iIndex = 0;

	//Move towards the vertical end of the matrix, add up the values of the matrix along the vertical 
	while (iIndex < theMatrix.size()) {
		if (theMatrix[iIndex][j] >= 1) {
			yTotal = yTotal + theMatrix[iIndex][j];
			yMeld.push_back(make_pair(iIndex, j));
		}
		iIndex++;
	}

	//This is where the prioritizing takes place.
	//If the xTotal is smaller than yTotal and it is a meld give it the priority, then remove that meld from the matrix
	if (xTotal < yTotal && xTotal >= 3) {
		updateMatrix(xMeld, false);
	}

	//Else, if the yTotal is smaller than xTotal (give it the priority) and it is a meld, then remove that meld from the matrix 
	else if (yTotal < xTotal && yTotal >= 3) {
		updateMatrix(yMeld, true);
	}
}

/* *********************************************************************
Function Name: passII
Purpose: The first pass has cleared up all the prioritizing issues. Now we can just clear out all the books and runs in the matrix
Algorithm: We gather runs and books from the matrix and update the matrix.
********************************************************************* */
void newCardCollection::passII(int i, int j) {

	//Check for horizontal meld
	//Holds how many horizontal consecutive 1's there are from index i, j
	int xTotal = 0;

	//Vector that holds the indexes for a horizontal meld
	vector <pair<int, int>> xMeld;
	xMeld.clear();

	//Start at jIndex
	int jIndex = j;

	//Do while a 0 is not hit, moving towards the right
	do {
		if (theMatrix[i][jIndex] == 0) {
			break;
		}
		xTotal = xTotal + 1;
		xMeld.push_back(make_pair(i, jIndex));
		jIndex++;
	} while (jIndex < theMatrix[i].size());

	//Only decrease jIndex for a search towards the left, if the jIndex is greater than 0. Otherwise, we run into a nasty error
	if (j > 0) {
		jIndex = j - 1;
	}

	//Do while a 0 is not hit, moving towards the left
	do {
		if (theMatrix[i][jIndex] == 0) {
			break;
		}
		xTotal = xTotal + 1;
		xMeld.push_back(make_pair(i, jIndex));
		jIndex--;
	} while (jIndex >= 0);

	//Check for a vertical meld
	//Holds how many vertical 1's there are along the line of point i,j in the matrix
	int yTotal = 0;

	//Vector that holds the vertical meld
	vector<pair<int, int>>yMeld;
	yMeld.clear();

	//Start at iIndex of 0
	int iIndex = 0;

	//Move towards the vertical end of the matrix, add up all 1's
	while (iIndex < theMatrix.size()) {
		if (theMatrix[iIndex][j] >= 1) {
			yTotal = yTotal + theMatrix[iIndex][j];
			yMeld.push_back(make_pair(iIndex, j));
		}
		iIndex++;
	}

	//Clear in the matrix, if is a run
	if (xTotal >= 3) {
		updateMatrix(xMeld, false);
	}

	//Update the matrix, if is a book
	else if (yTotal >= 3) {
		updateMatrix(yMeld, true);
	}
}

/* *********************************************************************
Function Name: passIII
Purpose: The first pass cleared up all the books and runs that needed prioritizing i.e. since a card can only be part of a book or a run, there can be prioritizing issues.
The second pass cleared up all the books and runs.
The third pass, this pass will be for the cards that need jokers and wildcards.
Algorithm: We gather the books and runs that require a joker. We then let the books or runs that need the least amount of special cards have them.
********************************************************************* */
void newCardCollection::passIII() {
	
	//Only go through the mess, if there are special cards to expend
	if (specialCards > 0) {

		//How many special cards does this run need?
		int needJokerCount = 0;

		//At which indexes does this run need it's special cards
		vector<vector<pair<int, int>>> needJokers;

		//Pushing back an empty pair to start up things
		needJokers.push_back(vector<pair<int, int>>());

		//Iterate through all the horizontal lines of the matrix and gather all the indexes that need special cards
		//0 to 5 are coordinates along the vertical
		for (int i = 0; i < 5; i++) {

			//j is to be incremented, it is the index along the horizontal
			int j = 0;

			//While we don't hit the matrix's end
			while (j != theMatrix[i].size()) {

				//If a joker is needed, which means that the matrix spot is 0, push it back to the needJokers vectors at needJokerCount
				if (theMatrix[i][j] == 0) {
					needJokers[needJokerCount].push_back(make_pair(i, j));
				}

				//If along this line, we hit a 1, that means, we stopped needing jokers from here on out 
				else if (theMatrix[i][j] == 1) {
					//We start up another vector pair of integers to hold up all the jokers needed consecutively along the horizontal
					needJokers.push_back(vector<pair<int, int>>());

					//Increase the count of how many places need jokers
					needJokerCount++;
				}

				//Increment the index along horizontal
				j++;

				//If we hit the horizontal end of the matrix, a new pair of consecutive jokers need have to set up increment the needJokerCount and push back
				//a vector to hold the new pair
				if (j == theMatrix[i].size()) {
					needJokers.push_back(vector<pair<int, int>>());
					needJokerCount++;
				}
			}
		}

		//Sort the needJokers vector by size so that we can give jokers to the run that needs the least amount of jokers
		sort(needJokers.begin(), needJokers.end(), [](const vector<pair<int, int>>& a, const vector<pair<int, int>>& b) { return a.size() < b.size(); });
	
		//Iterate through the needJokers vector and give them jokers and wildCards until we run out 
		for (int i = 0; i < needJokers.size(); i++) {
			if (needJokers[i].size() <= specialCards) {
				for (int j = 0; j < needJokers[i].size(); j++) {

					//Increment the matrix value at the needJoker index, since we do have enough jokers to provide for
					theMatrix[needJokers[i][j].first][needJokers[i][j].second]++;

					//Decrease the count of the number of jokers we have
					specialCards = specialCards - needJokers[i].size();

					//Having given jokers, we can run a passII at this index so as to clear the run out
					passII(needJokers[i][j].first, needJokers[i][j].second);
				}
			}
		}

		//We first took a look at all the empty spaces, considering them as space that needed special cards. But the space right after
		//cards in consecution may be left out by the above run through. So we consider cards that are in consecution and the space 
		//after that as needing jokers\

		//Taking out cards in conseuction along the horizontal
		vector<vector<pair<int, int>>> cardsInConsecution;

		//Starting out a vector of pair of int and int to push back the conseuction
		cardsInConsecution.push_back(vector<pair<int, int>>());

		//Start at index 0 and move to the vertical end
		int index = 0;
		for (int i = 0; i < 5; i++) {
			int j = 0;
			while (j != theMatrix[i].size()) {
				
				//If there's a card, then we push back to the vector
				if (theMatrix[i][j] == 1) {
					cardsInConsecution[index].push_back(make_pair(i, j));
				}

				//Otherwise, dont push back but start a new vector of pairs to hold the next cards in consecution
				else if (theMatrix[i][j] == 0) {
					cardsInConsecution.push_back(vector<pair<int, int>>());
					index++;
				}

				//Increment the j index, to move along the horizontal
				j++;

				//If we hit the horizontal end, start a new vector of pairs to hold the next cards in consecution
				if (j == theMatrix[i].size()) {
					cardsInConsecution.push_back(vector<pair<int, int>>());
					index++;
				}
			}
		}

		//We give out special cards to those who need them if we have them
		for (int i = 0; i < cardsInConsecution.size(); i++) {
			if ((3 - cardsInConsecution[i].size()) <= specialCards) {
				for (int j = 0; j < cardsInConsecution[i].size(); j++) {
					theMatrix[cardsInConsecution[i][j].first][cardsInConsecution[i][j].second]--;
					specialCards = specialCards - (3 - cardsInConsecution[i].size());
				}
			}
		}
	}


	//Acting on the vertical cards that is the books that need jokers
	if (specialCards > 0) {

		//Getting all vertical book counts
		vector<int> bookCounts;

		//Get all the vertical books
		int theSum = 0;
		const int iTill = theMatrix[0].size();
		const int jTill = theMatrix.size();
		for (int i = 0; i < iTill; i++) {
			for (int j = 0; j < jTill; j++) {
				theSum = theSum + theMatrix[j][i];
			}
			bookCounts.push_back(theSum);
			theSum = 0;
		}

		//If a book needs joker, give it to them if we have them
		for (int i = 0; i < bookCounts.size(); i++) {
			if ((3-bookCounts[i]) <= specialCards) {
				theMatrix[0][i]++;
				passII(0,i);
			}
		}
	}
}

/* *********************************************************************
Function Name: checkMatrix
Purpose: It applies passI, passII, passII in that order to each index of the matrix
Return: bool value of whether the user won or not. Based on if the matrix is all 0's OR not.
Algorithm: Handles prioritizing issues first with passI, clears out all complete books and runs with passII, clears out cards that need jokers
with passIII
********************************************************************* */
bool newCardCollection::checkMatrix() {

	//Set a variable to hold the matrix sum at the beginning
	int prevMatrixSum = 0;

	//Do-while loop until we don't get any changes in the matrix sum having passed through all indexes of the matrix with a for loop
	do {

		//Storing the matrix sum at the beginning of the run through
		prevMatrixSum = matrixSum();

		//Running through all indexes and applying passI to them through the matrix completely
		for (int i = 0; i < theMatrix.size(); i++) {
			for (int j = 0; j < theMatrix[i].size(); j++) {
				passI(i, j);
			}
		}

		//Checking if sum reamined the same, if it didn't, maybe there is more clearing to do so do another run. If sum didn't change after another pass
		//just move out of the loop
	} while (prevMatrixSum != matrixSum());

	//Do-while loop until we don't get any changes in the matrix sum having passed through all indexes of the matrix with a for loop
	do {

		//Storing the matrix sum at the beginning of the run through
		prevMatrixSum = matrixSum();

		//Running through all indexes and applying passII to them through the matrix completely
		for (int i = 0; i < theMatrix.size(); i++) {
			for (int j = 0; j < theMatrix[i].size(); j++) {
				passII(i, j);
			}
		}

		//Checking if sum reamined the same, if it didn't, maybe there is more clearing to do so do another run. If sum didn't change after another pass
		//just move out of the loop
	} while (prevMatrixSum != matrixSum());

	//Make a pass for jokers
	passIII();

	//If matrixSum is now 0, the user can go out, or has no card without a run or a book match in their hand
	if (matrixSum() == 0) {
		return true;
	}

	//If they didn't win, store the cards that remain into remaining cards vector
	for (int i = 0; i < theMatrix.size(); i++) {
		for (int j = 0; j < theMatrix[i].size(); j++) {
			for (int k = 0; k < theMatrix[i][j]; k++) {
				remainingCards.push_back(matrixIndexToCardValue(i, j));
			}
		}
	}

	//They didn't win, so return false
	return false;
}

/* *********************************************************************
Function Name: matrixIndexToCardValue
Purpose: Converts index of the matrix to a string representing the value of the card
Parameters: i and j that represent the index
Return Value: string representation of the card
Algorithm: Adds 3 to the index along x-axis to get the rank value, and just appropriates the suit value according to the index along y-axis
********************************************************************* */
string newCardCollection::matrixIndexToCardValue(int i, int j) {
	//The string to be returned, initially empty
	string s = "";

	//Add 3 and add appropriate string representation of the rank to the empty string 
	if (j + 3 == 10) {
		s = s + "X";
	}
	else if (j + 3 == 11) {
		s = s + "J";
	}
	else if (j + 3 == 12) {
		s = s + "Q";
	}
	else if (j + 3 == 13) {
		s = s + "K";
	}
	else {
		s = s + to_string(j + 3);
	}

	//Add appropriate string representation according to the y-coordinate
	if (i == 0) {
		s = s + "S";
	}
	else if (i == 1) {
		s = s + "C";
	}
	else if (i == 2) {
		s = s + "D";
	}
	else if (i == 3) {
		s = s + "H";
	}
	else if (i == 4) {
		s = s + "T";
	}

	return s;
}

/* *********************************************************************
Function Name: getRemainingCards
Purpose: Gets the card that remain in player's hand witout match
Return Value: Vector of strings that hold the cards that reamin in palyer's hand without a match
********************************************************************* */
vector<string> newCardCollection::getRemainingCards() {
	return remainingCards;
}

/* *********************************************************************
Function Name: getJokerCount
Purpose: Gets the count of the joker in the player's hand
Return Value: Integer of the joker count
********************************************************************* */
int newCardCollection::getJokerCount() {
	return jokerCount;
}

/* *********************************************************************
Function Name: getWildCardCount
Purpose: Gets the count of the wildcard in the player's hand
Return Value: Integer of the wildcard count
********************************************************************* */
int newCardCollection::getWildCardCount() {
	return wildCardCount;
}

/* *********************************************************************
Function Name: getSpecialCardCount
Purpose: Gets the count of the special cards in the player's hand
Return Value: Integer of the special cards count
********************************************************************* */
int newCardCollection::getSpecialCardsCount() {
	return specialCards;
}

/* *********************************************************************
Function Name: getBooksMade
Purpose: Gets the books that were made by the player
Return Value: Vector of strings holding the books that the player is able to make
********************************************************************* */
vector<string> newCardCollection::getBooksMade() {
	return booksMade;
}


/* *********************************************************************
Function Name: getRunsMade
Purpose: Gets the runs that the player is able to make
Return Value: Vector of strings holding the runs that the player is able to make
********************************************************************* */
vector<string> newCardCollection::getRunsMade() {
	return runsMade;
}

/* *********************************************************************
Function Name: getSpecialCardsUsed
Purpose: Gets the special cards that the player used
Return Value: Vector of strings holding the special cards that the player used
********************************************************************* */
vector<string> newCardCollection::getSpecialCardsUsed() {
	return specialCardsUsed;
}