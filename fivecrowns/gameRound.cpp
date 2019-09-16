#include "gameRound.h"
#include "deck.h"
#include "player.h"
#include "human.h"
#include "computer.h"
#include <ctime>
#include <iterator>

//The constructor for the round
gameRound::gameRound() {
	this->nCards = 3; //Initialize the number of cards at 3, increases by 1 each round
	this->wildCard = card(to_string(nCards), "X"); //For each round, the wild card is the card with the value of n
}

void gameRound::dealCards() {
	//Get the deck
	deck* a = deck::getDeck();

	//Shuffle the deck
	a->shuffleDeck();

	//Deal the cards to the two players
	for (int i = 0; i < nCards; i++) {
		a->removeCardAtTop();
	}

	for (int i = 0; i < nCards; i++) {
		card tempCard = a->getCardAt(i);
		a->removeCardAtTop();
	}
}

void gameRound::instantiatePiles() {
	deck* a = deck::getDeck();
	for (int i = 0; i < a->getDeckSize(); i++) {
		this->drawPile.push_back(a->getCardAt(i));
	}


	card topCard = drawPile.at(0);

	//Remove the top card off drawPile
	this->drawPile.erase(this->drawPile.begin());

	//Put the top card out of draw pile into discard pile
	this->discardPile.push_back(topCard);
}

//Tosses the coin to see who plays first
int gameRound::coinToss() {
	cout << "Coin has been tossed." << endl;
	int call = 0;

	while (call != 1 && call != 2) {
		cout << "Call the toss: [1 == heads | 2 == tails]: ";
		cin >> call;
		if (call != 1 && call != 2) {
			cout << "ERROR in input." << endl;
		}
	}


	srand(unsigned(time(0)));
	int flip = rand() % 2 + 1;

	cout << "Flipped ";
	if (flip == 1) {
		cout << "heads." << endl;
	}
	else {
		cout << "tails. " << endl;
	}


	if (flip == call) {
		cout << "You won the coin toss. You go first." << endl;
		this->p1 = &human(); //Player 1 is human
		this->p2 = &computer(); //Player 2 is computer
		return 1;
	}
	else {
		this->p1 = &computer();
		this->p2 = &human();
		cout << "You lost the coin toss. It is computer's turn first." << endl;
		return 2;
	}
}

//Sets up the round
void gameRound::setUpRound() {
	dealCards();
	instantiatePiles();
}

//Start the round
void gameRound::start() {
	setUpRound();
	coinToss();
	this->p1->takeTurn();
	this->p2->takeTurn();
}

