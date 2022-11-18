#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include "Player.h"
#include "Game.h"

using namespace std;

/******************************************************
** Program: Go_Fish.cpp
** Author: Kenneth Tang
** Date: 05/18/2022
** Description: A game of go fish with a computer that is heavily
*  reliant on classes and class functions
** Input: Cards you want to ask for from your hand (Case sensitive)
** Output: The game in text
******************************************************/


int main(int argn, char** argv){


	Game G1(argn, argv);
	G1.play_game();
}
