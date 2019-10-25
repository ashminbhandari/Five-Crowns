#pragma once

#include "card.h"
#include <vector>
#include <string>
#include <map>

class cardCollection {
private:
	/*
	vector<card>cardsUtilized; //These cards are already part of a book or a run and cannot be used anymore period
	vector <card> cardsCanStillBeUsed;
	multimap <string, card> mmForRunCheck;

	//
	vector <card> collection; //The cards in the collection
	vector<string> aCopy;
	vector <int> rankUtilized; //Ranks of cards that have been a part of a book or run but still can be utilized for the other
	vector<int> booksMadeFor; //Cards for which books have been made
	int runCount; //The run count of the card collection
	int bookCount; //The book count of the card collection
	int jokerCount; //The number of jokers in the card collection
	int jokersLeft; //The number of jokers that have been utilized as part of a book or a run

	void calculateRunCount();
	void calculateBookCount();
	void solveCollisons();
	vector<int>runsMadeFor; //Cards for which runs have been made
	*/
	multimap <int, card> mmForBookCheck;
	multimap <string, card> mmForRunCheck;
	vector <card> collection;
	vector <string> asString;
	int jokersLeft;

public:
	/*
	void printOutPermutations();


	int getJokerCount();
	int getRunCount();
	int getBookCount();
	bool hasWon();
	*/
	void calculateInformation();
	void setCollection(vector<card>);
	void firstPassForBook();
	void firstPassForRun();
	string nextCardByString(string);
	string prevCardByString(string);
};