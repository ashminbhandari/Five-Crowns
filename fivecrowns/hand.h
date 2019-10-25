#pragma once

#include "card.h"
#include <vector>
#include <string>

class cardCollection {
private:
	vector <card> collection; //The cards in the collection
	vector <card> cardUtilized; //List of cards that have been a part of a book or run
	int runCount; //The run count of the card collection
	int bookCount; //The book count of the card collection
	int jokerCount; //The number of jokers in the card collection
	int jokersUtilized; //The number of jokers that have been utilized as part of a book or a run
 	multimap <int, card> mmForBookCheck;
	multimap <string, card> mmForRunCheck;
	void calculateRunCount();
	void calculateBookCount();

public:
	void calculateInformation();
	int getJokerCount();
	int getRunCount();
	int getBookCount();
	int getNoOfJokersUtilized();
};