/************************************************************
* Name:  Ashmin Bhandari
* Project : Five Crowns (C++)
* Class : Brain
* Date : 10/24/2019
************************************************************/

#pragma once
//For the cards in the game are held in a vector data structure 
#include <vector>

//Card objects upon which the game is built
#include "card.h"

/* *********************************************************************
Class Name: Brain
Purpose: Brain is the core of the computer's playing strategy. Given a vector of cards, i.e. a player's hand, and 
considering the draw pile and the discard pile, brain allows the computer to decide which card to pick and which card
to throw. It will try and make the most optimal choice.
********************************************************************* */
class brain {
public:
	pair<int,card> think(vector<card>, string);
};