#include "ninja.h"
#include "entity_functions.h"

using namespace std;

// Default
Ninja::Ninja() : Ant(){
	// cout << "Ninja constructor" << endl;
	this->armor = 1;
	this->cost = 6;
	this->name = "ninja";
}

// Non Default
Ninja::Ninja(int a) : Ant(){
	// cout << "Ninja nondefault constructor" << endl;
	this->armor = a;
}

// Destructor
Ninja::~Ninja(){
	// cout << "Ninja destructor" << endl;
}

void Ninja::attack(vector<vector<Tile*>> GB, int x, int y, int k){
	/*********************************************************************
	** Function: Attack
	** Description: Goes through the ant's attack
	** Parameters: Game board, position that the ant is at on the board, and
	*  the position in the tile vector of this ant
	** Pre-Conditions: Tries to attack if it is able to
	** Post-Conditions: Performs its attack
	*********************************************************************/
	// Attack all bees in its vector
	// cout << "Ninja attack" << endl;
	/**For the ninja, it does 1 damage to any bee on its square
	 */
	if(tile_has_bee(GB[x][y]->ent)){
		// Go through all pieces on that tile
		for (int i = 0; i < GB[x][y]->ent.size(); ++i)
		{
			// Deal damage to bees in that tile
			if(GB[x][y]->ent[i]->get_name().compare("bee") == 0){
				GB[x][y]->ent[i]->take_dmg(1);
			}
		}
	}

}

void Ninja::take_dmg(int i){
	/*********************************************************************
	** Function: Take damage
	** Description: Takes i damage
	** Parameters: Amount of damage
	** Pre-Conditions: None
	** Post-Conditions: Reduces armor by the amount of damage
	*********************************************************************/
	this->armor = this->armor - i;
}