/************************************************************
* Name:  Ashmin Bhandari
* Project : Five Crowns (C++)
* Class : Brain
* Date : 10/24/2019
************************************************************/

//Simply importing the header for the brain class
#include "brain.h"

//Brain will need to get in touch with the round to get the state of the game
#include "gameRound.h"

//Brain contacts the card collection class in order to get critical information about the user's hand needed to make a decision
#include "newCardCollection.h"

//For use of the sort function
#include <algorithm>

/* *********************************************************************
Function Name: 'think'
Purpose: 'think' takes the card passed into it into consideration along with the draw pile
and the discard pile (whose information it gets from the round class), to make a decision
on which pile to pick from and which card to drop. 
Parameters: (a). 'theCollection', a vector of cards passed by value. It holds the collection of cards that make up 
a player's hand, that the function is to consider in making it's decision. 
(b). 'mode', a string which signifies the two modes of thinking made available by this function, namely regular and extended.
Regular mode will not look at the draw pile in making it's decision about which card to pick and which to drop, extended mode will.
Return Value: A pair of integer and a card. The integer value can be 0 or 1. 0 means it is best to pick from the discard pile, 1 means
it's best to pick from the draw pile. Meanwhile, the latter of the pair, the card returned, is the card to be dropped by the player.
Local Variables: (a). 'r', the singleton instance of the round class. Through this instance, 'think' can gather information (the state) about the 
what is happening in the round being played. 
(b). 'discardPileCard', it is a card object. Simply, the card on top of the discard pile.
(c). 'drawPileCard', it is a card object. Simply, the card on top of the draw pile.
(d). 'copyCollection' & 'tempCopy', a vector of card objects, copy of the collection of cards sent as a parameter to the function, any changes 'think' needs to make whilst
in the process of making it's decision is made to the copy instead of the original. If the collection needs to be reset back to the original,
we have the original collection intact. 
(e). 'cardMatrixSum' & 'matrixSum', they are vectors of a pair of integer and card. Having tried out the card from discard or draw pile at each hand position,
it 'cardMatrixSum' holds the matrix sum value (can be thought of as the score corresponding to putting the card at that specific hand position), 
and the card itself.
(f). 'smallest', it is again a vector of a pair of integer and card. It is the 'cardMatrixSum' that generated the lowest score (or matrix sum). 
So it is the best choice to make.
(g). 'temp', it is an object of 'newCardCollection' type. The newCardCollection class helps gather information on what cards in the hand are books, what are runs, how many cards remain, 
and what the matrix sum (score) is.
(h). 'cardToDrop', holds the card that is to be dropped by the player. The selection as a result of thought.
(i). 'remCards', vector of strings, the cards that remain without a book or a run match in the user's hand  
(j). 'remCardsAsCards', the remaining cards from above as card objects instead of strings
Algorithm: (1). Get the card from the discard pile
(2). Put the discard pile card at each hand position and store the matrix sums (or the scores) of doing so in each hand position
(3). Sort the scores in ascending order
(4). Iterate through the sorted scores, if a score is found such that the score is lesser than the score of the hand as it was originally without adding the discard pile card and removing a card,
then return these values i.e. a pair of integer and card, the integer is 0, which means pick from the discard pile, and the card is the card which is the best to drop
(5). If nothing positive came out of taking the discard pile card and putting it at each hand position by replacing the card at that hand position then it is clear that 
one needs to draw from the draw pile.
(6). If extended mode was chosen, then the above algorithm as done with the discard pile card is also done with the draw pile card and the appropriate values returned
(7). If not, then the strategy simply tells you to remove the card with the highest score penalty.
********************************************************************* */
pair<int, card> brain::think(vector<card> theCollection, string mode) {
	//Calls upon the singleton instance of the game round so as to gather information about the round being played, important in making the decision
	gameRound* r = gameRound::getRound();

	//Simply getting the top card of the discard pile 
	card discardPileCard = r->getDiscardPile()->at(0);

	//Copy theCollection, the collection passed as a parameter for this function to think upon
	vector <card> copyCollection = theCollection;

	//This vector will hold the card that was replaced for to make space for the discard pile card and the integer score that came off of doing so
	vector<pair<int, card>> cardMatrixSum;

	//Iterate through the collection of cards, put the discard pile card in for each hand position by replacing the card already there. Check the score, store the score as a result of doing afore said replacement.
	for (int i = 0; i < theCollection.size(); i++) {
		//The card that is going to be removed to make space for the discard pile card
		card theCard = copyCollection.at(i);

		//Actually erasing the card
		copyCollection.erase(copyCollection.begin() + i);

		//Having erase the card, adding the discard pile card to the collection
		copyCollection.push_back(discardPileCard);

		//Instantiating a card collection object, this allows for to check the score among other important functionalities
		newCardCollection temp;

		//Setting the collection with the discard pile i.e. constructing the newCardCollection object
		temp.setCollection(copyCollection);

		//Gathering information about the collection, i.e. how many books has it got, how many runs, how many cards remain, the score, and other critical information
		temp.checkMatrix();

		//Pushing back the score as a result of above calculation and the card that was replaced in order to get that score
		cardMatrixSum.push_back(make_pair(temp.matrixSum(), theCard));

		//Setting back the collection to it's original state
		copyCollection = theCollection;
	}

	//Sorting 'cardMatrixSum' in ascending order so as to be able to start iterating from the lowest score
	sort(cardMatrixSum.begin(), cardMatrixSum.end(), [](auto& left, auto& right) { return left.first < right.first; });

	//This variable is intended to hold the card that generated the lowest score of doing all the above replacements with discard pile card 
	pair<int, card> smallest = make_pair(INT_MAX, card("X", "X"));

	//Index, the index will be incremented as we iterate through the cardMatrixSum vector 
	int index = 0;

	//We do-while loop through the cardMatrixSum, making sure that we are not planning on removing a joker or a wildcard in the process
	do {
		if (!cardMatrixSum[index].second.isJoker() && cardMatrixSum[index].second.getRankValue() != r->getRoundNo() + 2) {
			smallest = cardMatrixSum[index];
			break;
		}
		index++;
	} while (index != cardMatrixSum.size());

	//The matrix sum with the cards just as it is, without adding the card from the discard pile 
	newCardCollection temp;

	//Constructing the 'newCardCollection' object as the original collection passed to this function
	temp.setCollection(theCollection);

	//Cacluating the information for the original collection
	temp.checkMatrix();

	//Compare the score of the original hand or the collection without any modification with the one with the modification made, i.e. the one with the discard pile added.
	//If a positive difference was seen that is the score decrease, then that is the decision to make. Return that the discard pile needs to picked from, and the card
	//that generated the lowest score needs to dropped
	if (smallest.first < temp.matrixSum())  {
		cout << endl << "Having tried the card from the discard pile on each hand positions, picking the discard pile card and removing '" << smallest.second.getCardValue() << "' yields the best result in terms of going out." << endl << endl;
		return make_pair(0, smallest.second);
	}

	//Otherwise, if a positive difference was not seen, then the discard pile will have to picked from
	else {

		//The regular mode doesn't allow for to actuall peek at the draw pile card before making decision on which card to drop
		if (mode == "regular") {

			//Some neat outputs for the screen
			cout << endl << endl << "Regular strategy:" << endl;
			cout << endl << "There is no way of knowing which card is going to come out of the draw pile, but since picking the discard pile makes no positive difference, (having tried that card at each hand positions), it is best to pick the draw pile card. " << endl;
			
			//Vector the hold the cards that remain without a book or a run match in the hand, information gathered from functionalities provided by newCardCollection
			vector<string> remCards = temp.getRemainingCards();

			//Remaining cards as card objects so as to make use of card object fucntionaities
			vector<card> remCardsAsCards;

			//Some neat outputs for the screen
			cout << "These cards aren't a part of a book or a run as of yet. You may want to choose from these cards to drop: ";

			//Create and push back cards to the remCardsAsCards vector form remCards as strings
			for (int i = 0; i < remCards.size(); i++) {
				remCardsAsCards.push_back(card(string(1, remCards[i][0]), string(1, remCards[i][1])));
				cout << remCards[i] << " ";
			}
			cout << endl;

			//Card object that will hold the card to drop, this will be returned as a result of the thinking that is being done here
			card cardToDrop;

			//Minimum value of an integer, to be compared with to get the card with the highest score penalty 
			int min = INT_MIN;
			for (int i = 0; i < remCardsAsCards.size(); i++) {
				if (remCardsAsCards.at(i).getRankValue() > min) {
					cardToDrop = remCardsAsCards[i];
					min = cardToDrop.getRankValue();
				}
			}
			
			//Some neat output for the screen
			cout << "Considering, score penalities of higher ranked cards, just letting you know that, as of yet," << cardToDrop.getCardValue() << " is going to cost you the most points." << endl << endl;

			//Return the pair of integer, 1 means pick from draw pile and the card to drop
			return make_pair(1, cardToDrop);
		}

		//If extended mode is chosen, then one can peek at the draw pile card which is technically allowed in a game
		else if (mode == "extended") {

			//The card at the top of the draw pile, information gathered from the singleton instance of the round class
			card drawPileCard = r->getDrawPile()->at(0);

			//Copying collection of cards sent into this function in order to be thought upon
			vector<card> tempCopy = theCollection;

			//This vector will hold the card that was replaced for to make space for the discard pile card and the integer score that came off of doing so
			vector<pair<int, card>>matrixSums;

			//Same as what was done with the discard pile above, iterating through the collection, replacing the draw pile card into each hand position and calculating corresponding scores
			for (int i = 0; i < theCollection.size(); i++) {
				
				//The card to be replaced
				card theCard = tempCopy.at(i);

				//Erasing the card from the vector 
				tempCopy.erase(tempCopy.begin() + i);

				//Pushing back the draw pile card
				tempCopy.push_back(drawPileCard);

				//Creating an instance of newCardCollection object so as to make use of it's wonderful functionalities
				newCardCollection temp;

				//Setting up the newCardCollection instance with the collection that holds the draw pile card
				temp.setCollection(tempCopy);

				//Calculating infromation based on the collection provided
				temp.checkMatrix();

				//Pushing back the information gathered into the matrixSums vector, the card and the corresponding score it generated
				matrixSums.push_back(make_pair(temp.matrixSum(), theCard));

				//Setting back the collection to it's original state
				tempCopy = theCollection;
			}

			//Sorting 'matrixSums' in ascending order so as to be able to start iterating from the lowest score
			sort(matrixSums.begin(), matrixSums.end(), [](auto& left, auto& right) { return left.first < right.first; });

			//This variable is intended to hold the card that generated the lowest score of doing all the above replacements with draw pile card 
			pair<int, card> smallest_ = make_pair(INT_MAX, card("X", "X"));

			//Integer to hold the index, will be increased in order to iterate through the matrixSums vector 
			index = 0;

			//Checking if the card being replaced is not a joker or a wildcard
			do {
				if (!matrixSums[index].second.isJoker() && matrixSums[index].second.getRankValue() != r->getRoundNo() + 2) {
					smallest_ = matrixSums[index];
					break;
				}
				index++;
			} while (index != matrixSums.size());

			//Some neat outputs for the screen
			cout << endl << endl << "Extended strategy:" << endl;
			cout << "Picking from the discard pile makes not positive difference, so I picked " << drawPileCard.getCardValue() << " from the draw pile and tried it at each hand position. Removing, " << smallest_.second.getCardValue() << " yields the best result." << endl << endl;
			
			//Return the pair of integer, 1 means pick from draw pile and the card to drop
			return make_pair(1, smallest_.second);
		}
	}	
}
