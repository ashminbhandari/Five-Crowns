#pragma once

#include <vector>
#include "card.h"

class newCardCollection {
private:
	vector <card> collection;
	vector<card> copyCollection;
	vector<string> collectionInString;
	vector<vector<int>> theMatrix;
	vector<string>remainingCards;
	vector<string> cardsUtilized;
	vector<string> booksMade;
	vector<string> runsMade;
	vector<string>specialCardsUsed;
	void updateMatrix(vector<pair<int,int>>, bool isY);
	int jokerCount;
	int wildCardCount;
	int specialCards; 
	void constructMatrix();
	void passI(int i , int j);
	void passII(int i, int j);
	void passIII();
public:	
	bool checkMatrix();
	int matrixSum();
	void setCollection(vector<card>);
	string matrixIndexToCardValue(int i, int j);
	vector<string>getRemainingCards();
	vector<string>getBooksMade();
	vector<string>getRunsMade();
	vector<string>getSpecialCardsUsed();
	int getJokerCount();
	int getWildCardCount();
	int getSpecialCardsCount();
};