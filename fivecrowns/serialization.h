#pragma once
#include <vector>
#include "card.h"
#include  <string>

class serialization {
public:
	int roundNo;
	int computerScore;
	int humanScore;
	vector <card> computerHand;
	vector <card> humanHand;
	vector<card> drawPile;
	vector<card>discardPile;
	string nextPlayer;
	string playerName;
	void read();
	void save(int roundNo, int computerScore, int humanScore, vector <card> computerHand, vector <card> humanHand, vector<card> drawPile, vector<card>discardPile, string nextPlayer, string playerName, string saveFileName);
};