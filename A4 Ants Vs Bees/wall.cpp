#include "wall.h"
#include "entity_functions.h"

using namespace std;

// Default
Wall::Wall() : Ant(){
	// cout << "Wall constructor" << endl;
	this->armor = 4;
	this->cost = 4;
	this->name = "wall";
}

// Non Default
Wall::Wall(int a) : Ant(){
	// cout << "Wall nondefault constructor" << endl;
	this->armor = a;
}

// Destructor
Wall::~Wall(){
	// cout << "Wall destructor" << endl;
}

void Wall::attack(vector<vector<Tile*>> GB, int x, int y, int k){
	/*********************************************************************
	** Function: Attack
	** Description: Goes through the ant's attack
	** Parameters: Game board, position that the ant is at on the board, and
	*  the position in the tile vector of this ant
	** Pre-Conditions: Tries to attack if it is able to
	** Post-Conditions: Performs its attack
	*********************************************************************/

}

void Wall::take_dmg(int i){
	/*********************************************************************
	** Function: Take damage
	** Description: Takes i damage
	** Parameters: Amount of damage
	** Pre-Conditions: None
	** Post-Conditions: Reduces armor by the amount of damage
	*********************************************************************/
	this->armor = this->armor - i;
}