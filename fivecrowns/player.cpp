#include "player.h"

//Picks a card, to be overriden in child classes
void player::pickCard() {
}


//Drops a card, to be overriden in child classes
void player::dropCard() {
}

//Prints the hand out to the screen
void player::printHand() {
}

//Gets the hand of the player
vector <card>* player::getHand() {
	return &this->hand;
}

//Player takes their turn, to be overriden in child classes
void player::takeTurn() {
}

