#include "cardCollection.h"
#include <algorithm>

//Set the collection, construct the collection object
void cardCollection::setCollection(vector<card>collection) {
	this->collection = collection;

	//Pushing back the string values of cards into the string vector
	for (int i = 0; i < collection.size(); i++) {
		asString.push_back(collection.at(i).getCardValue());
	}
}

//Calculate information from the card collection
void cardCollection::calculateInformation() {
	//Iterate through the collection of cards provided and set up the map for book check
	for (int i = 0; i < collection.size(); i++) {
		mmForBookCheck.insert(make_pair(collection[i].getRankValue(), collection[i]));
	}

	jokersLeft = mmForBookCheck.count(0);

	for (int i = 0; i < collection.size(); i++) {
		mmForRunCheck.insert(make_pair(collection[i].getSuit(), collection[i]));
	}
}
//First pass for book
void cardCollection::firstPassForBook() {
	for (int i = 3; i <= 13; i++) {
		if (mmForBookCheck.count(i) == 3) {
			auto forRank = mmForBookCheck.equal_range(i);
			for (auto k = forRank.first; k != forRank.second; ++k) {
				asString.erase(remove(asString.begin(), asString.end(), k->second.getCardValue()), asString.end());
			}
		}
		else if (jokersLeft >= 1) {
			if (mmForBookCheck.count(i) == 2) {
				auto forRank = mmForBookCheck.equal_range(i);
				for (auto k = forRank.first; k != forRank.second; ++k) {
					asString.erase(remove(asString.begin(), asString.end(), k->second.getCardValue()), asString.end());
				}
				jokersLeft--;
			}
		}
	}

	for (int i = 0; i < asString.size(); i++) {
		cout << asString[i] << " ";
	}
	cout << endl;
}

//First pass for run
void cardCollection::firstPassForRun() {
	string theSuit[5] = { "S", "C", "D", "H", "T" };

	vector <string> cardsInSuitString;
	
	vector <int> rankArray;
	
	vector<string> currentRun;

	for (int i = 0; i < 5; i++) {
		cardsInSuitString.clear();
		currentRun.clear();
		auto forSuit = mmForRunCheck.equal_range(theSuit[i]);

		for (auto k = forSuit.first; k != forSuit.second; ++k) {
			cardsInSuitString.push_back(k->second.getCardValue());
		}

		for (int s = 0; s < cardsInSuitString.size(); s++) {
			cout << cardsInSuitString[s] << " ";
		}
		cout << endl;

		for (int j = 0; j < cardsInSuitString.size(); j++) {
			cout << "Card to + 1 " << cardsInSuitString.at(j) << endl;
			string nextCard = nextCardByString(cardsInSuitString.at(j));
			string prevCard = prevCardByString(cardsInSuitString.at(j));
			cout << "To search " << nextCard << endl;
			cout << "To search " << prevCard << endl;
			

			if (find(asString.begin(), asString.end(), nextCard) != asString.end()) {
				currentRun.push_back(cardsInSuitString.at(j));
			}	
			else if (find(asString.begin(), asString.end(), nextCard) == asString.end() && find(asString.begin(), asString.end(), prevCard) != asString.end()) {
				cout << "HERE" << endl;
				currentRun.push_back(cardsInSuitString.at(j));
				if (currentRun.size() >= 3) {
					for (int g = 0; g < currentRun.size(); g++) {
						asString.erase(remove(asString.begin(), asString.end(), currentRun[g]), asString.end());
						cardsInSuitString.erase(remove(cardsInSuitString.begin(), cardsInSuitString.end(), currentRun[g]), cardsInSuitString.end());
					}
					
				}
				else if (currentRun.size() == 2) {
					if (jokersLeft >= 1) {
						for (int h = 0; h < currentRun.size(); h++) {
							asString.erase(remove(asString.begin(), asString.end(), currentRun[h]), asString.end());
							cardsInSuitString.erase(remove(cardsInSuitString.begin(), cardsInSuitString.end(), currentRun[h]), cardsInSuitString.end());
						}
						jokersLeft--;
					}
				}
			}
		}
	}
	cout << "The string " << endl;
	for (int i = 0; i < asString.size(); i++) {
		cout << asString[i] << " ";
	}
	cout << endl;
}

//Gets next card by string
string cardCollection::nextCardByString(string card) {
	char rank = card[0];
	char nextRank = ' ';
	if (rank >= 51 && rank <= 56) {
		nextRank = rank + 1;
	}
	else if (rank == '9') {
		nextRank = 'X';
	}
	else if (rank == 'X') {
		nextRank = 'J';
	}
	else if (rank == 'J') {
		nextRank = 'Q';
	}
	else if (rank == 'Q') {
		nextRank = 'K';
	}
	else if (rank == 'K') {
		nextRank = 'L';
	}
	
	
	string s = string(1, card[1]);
	string r = string(1, nextRank);

	return r + s;

}

//Get prev card by string
string cardCollection::prevCardByString(string card) {
	string suit = string(card.at(1), 1);
	char rank = card[0];
	char prevRank = ' ';
	if (rank >= 51 && rank <= 57) {
		prevRank = rank - 1;
	}
	else if (rank == 'K') {
		prevRank = 'Q';
	}
	else if (rank == 'Q') {
		prevRank = 'J';
	}
	else if (rank == 'J') {
		prevRank = 'X';
	}
	else if (rank == 'X') {
		prevRank = '9';
	}
	
	string s = string(1, card[1]);
	string r = string(1, prevRank);

	return r + s;
}