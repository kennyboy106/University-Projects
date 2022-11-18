#include "snow_thrower.h"
#include "entity_functions.h"

using namespace std;

// Default
Snow_thrower::Snow_thrower() : Ant(){
	// cout << "Snow_thrower constructor" << endl;
	this->armor = 1;
	this->cost = 3;
	this->name = "snow_thrower";
}

// Non Default
Snow_thrower::Snow_thrower(int a) : Ant(){
	// cout << "Snow_thrower nondefault constructor" << endl;
	this->armor = a;
}

// Destructor
Snow_thrower::~Snow_thrower(){
	// cout << "Snow_thrower destructor" << endl;
}

void Snow_thrower::attack(vector<vector<Tile*>> GB, int x, int y, int k){
	/*********************************************************************
	** Function: Attack
	** Description: Goes through the ant's attack
	** Parameters: Game board, position that the ant is at on the board, and
	*  the position in the tile vector of this ant
	** Pre-Conditions: Tries to attack if it is able to
	** Post-Conditions: Performs its attack
	*********************************************************************/
	// deals 1 damage to top bee in array and freeze it
	// cout << "snow attack" << endl;
	// I need to go through only the row its on and look for the first be at the
	// end of the vector


	// Number of columns
	for (int i = 0; i < GB[x].size(); ++i)
	{
		// Go from the top of the list of entities down
		for (int j = GB[x][i]->ent.size() - 1; j >= 0; --j)
		{
			// If its a bee
			if (GB[x][i]->ent[j]->get_name().compare("bee") == 0)
			{
				// Attack and apply freeze
				GB[x][i]->ent[j]->take_dmg(1);
				GB[x][i]->ent[j]->freeze(2);
				return;
			}
		}
	}
}

void Snow_thrower::take_dmg(int i){
	/*********************************************************************
	** Function: Take damage
	** Description: Takes i damage
	** Parameters: Amount of damage
	** Pre-Conditions: None
	** Post-Conditions: Reduces armor by the amount of damage
	*********************************************************************/
	this->armor = this->armor - i;
}