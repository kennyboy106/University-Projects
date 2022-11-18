#include <iostream>
#include <vector>

#include "functions.h"
#include "piece.h"
#include "ant.h"
#include "bee.h"
#include "harvester.h"
#include "Game.h"
using namespace std;
/******************************************************
** Program: AntsvsBees.cpp
** Author: Kenneth Tang
** Date: 05/18/2022
** Description: A game of Ants vs Bees inspired by Plants vs Zombies
** Input: Various integer inputs
** Output: Takes the user through a game of Ants Vs Bees
*  You win by clearing all bees on the board before a new one is generated
*  You lose by letting a bee get to the queen ant on any row
*  **Extra credit** Any number of rows possible
******************************************************/

// Starting food
int Ant::food = 10;

int main(){
	do{
		// Get the number of rows for the game
		cout << "How many rows do you want to play on?" << endl;
		cout << "Rows: ";
		int rows = get_positive_int(1);


		// Play the game
		Game g1(rows);
		g1.play();
	}while(play_again());
}