#include "joker.h"


//Joker constructor
joker::joker(string jokerNo) {
	setRank("J");
	setSuit(jokerNo);
}

//Returns TRUE since we are in the joker class
bool joker::isJoker() {
	return true;
}



