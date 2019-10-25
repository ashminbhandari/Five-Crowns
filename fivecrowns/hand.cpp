#include "cardCollection.h"


//Calculate information from the card collection
void cardCollection::calculateInformation() {
	//Iterate through the collection of cards provided and set up the map for book check
	for (int i = 0; i < this->collection.size(); i++) {
		this->mmForBookCheck.insert(make_pair(this->collection[i].getRankValue(), this->collection[i]));
	}

	//Calculate the run count
	calculateRunCount();

	//Set the number of jokers
	this->noJokers = this->mmForBookCheck.count(0);

	//Iterate through the collection of cards provided and set up the multimap for run check
	for (int i = 0; i < collection.size(); i++) {
		this->mmForRunCheck.insert(make_pair(this->collection[i].getSuit(), this->collection[i]));
	}

	//Calculate the book count 
	calculateBookCount();
}


//Gets the joker count
int cardCollection::getJokerCount() {
	return this->noOfJokers;
}


//Calculates the book count
void cardCollection::calculateBookCount() {

}
