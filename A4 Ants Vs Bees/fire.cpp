#include "fire.h"
#include "entity_functions.h"

using namespace std;

// Default
Fire::Fire() : Ant(){
	// cout << "Fire constructor" << endl;
	this->armor = 1;
	this->cost = 4;
	this->name = "fire";
}

// Non Default
Fire::Fire(int a) : Ant(){
	// cout << "Fire nondefault constructor" << endl;
	this->armor = a;
}

// Destructor
Fire::~Fire(){
	// cout << "Fire destructor" << endl;
}

// Done
void Fire::attack(vector<vector<Tile*>> GB, int x, int y, int k){
	/*********************************************************************
	** Function: Attack
	** Description: Goes through the ant's attack
	** Parameters: Game board, position that the ant is at on the board, and
	*  the position in the tile vector of this ant
	** Pre-Conditions: Tries to attack if it is able to
	** Post-Conditions: Performs its attack
	*********************************************************************/
	// Doesn't attack unless there is a bee on it
	if(tile_has_bee(GB[x][y]->ent)){
		// cout << "Fire ant explosion" << endl;
		// Make all the bees in the same tile take 15 damage
		for (int i = 0; i < GB[x][y]->ent.size(); ++i)
		{
			if(GB[x][y]->ent[i]->get_name().compare("bee") == 0){
				GB[x][y]->ent[i]->take_dmg(15);
			}
		}
		// After dealing damage, delete itself
		delete GB[x][y]->ent[k];
		GB[x][y]->ent.erase(GB[x][y]->ent.begin() + k);
	}
}

void Fire::take_dmg(int i){
	/*********************************************************************
	** Function: Take damage
	** Description: Takes i damage
	** Parameters: Amount of damage
	** Pre-Conditions: None
	** Post-Conditions: Reduces armor by the amount of damage
	*********************************************************************/
	this->armor = this->armor - i;
}