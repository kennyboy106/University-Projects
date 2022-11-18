#include "Game.h"


// Default
Game::Game(){
	// cout << "Game constructor" << endl;
	this->num_rows = 1;
}
// Non default
Game::Game(int r){
	// cout << "Game non default constructor" << endl;
	// Create the 2D vector of Tile pointers that make up the game board
	for (int i = 0; i < r; ++i)
	{
		vector<Tile*> rows;
		for (int j = 0; j < 10; ++j)
		{
			rows.push_back(new Tile);
		}
		this->gameboard.push_back(rows);
	}
	this->num_rows = r;
}

// Destructor
Game::~Game(){
	/*********************************************************************
	** Function: Destructor
	** Description: Deletes all the objects within gameboard then deletes itself
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Deletes everything
	*********************************************************************/
	// cout << "Game destructor" << endl;
	for (int i = 0; i < gameboard.size(); ++i)
	{
		for (int j = 0; j < gameboard[i].size(); ++j)
		{
			for (int k = 0; k < gameboard[i][j]->ent.size(); ++k)
			{
				delete gameboard[i][j]->ent[k];
			}
			delete gameboard[i][j];
		}
	}
}

void Game::play(){
	/*********************************************************************
	** Function: Play
	** Description: This is the control function for the game. Calls all the
	*  functions necessary for playing the game
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Plays the game, modifies game board
	*********************************************************************/
	do{
		// Bee generated
		add_bee(gameboard);

		// Display the board
		display_board(gameboard);

		// Player adds an ant
		add_ant(gameboard);

		// Now i want the ants to attack
		ant_attack(gameboard);

		// Now i want bees to attack
		bee_attack(gameboard);


		} while(victory_condition(gameboard));


		
	display_board(gameboard);

	if(bee_win(gameboard)){
		cout << "Defeat, Bees got to the Queen ant" << endl;
	}
	else{
		cout << "Victory, all Bees were cleared!" << endl;
	}

}