#include "thrower.h"
#include "entity_functions.h"

using namespace std;

// Default
Thrower::Thrower() : Ant(){
	// cout << "Thrower constructor" << endl;
	this->armor = 1;
	this->cost = 3;
	this->name = "thrower";
}

// Non Default
Thrower::Thrower(int a) : Ant(){
	// cout << "Thrower nondefault constructor" << endl;
	this->armor = a;
}

// Destructor
Thrower::~Thrower(){
	// cout << "Thrower destructor" << endl;
}

void Thrower::attack(vector<vector<Tile*>> GB, int x, int y, int k){
	/*********************************************************************
	** Function: Attack
	** Description: Goes through the ant's attack
	** Parameters: Game board, position that the ant is at on the board, and
	*  the position in the tile vector of this ant
	** Pre-Conditions: Tries to attack if it is able to
	** Post-Conditions: Performs its attack
	*********************************************************************/
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
				return;
			}
		}
	}
}

void Thrower::take_dmg(int i){
	/*********************************************************************
	** Function: Take damage
	** Description: Takes i damage
	** Parameters: Amount of damage
	** Pre-Conditions: None
	** Post-Conditions: Reduces armor by the amount of damage
	*********************************************************************/
	this->armor = this->armor - i;
}