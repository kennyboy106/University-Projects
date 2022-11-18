#include "hungryant.h"
#include "entity_functions.h"

using namespace std;

// Default
Hungryant::Hungryant() : Ant(){
	// cout << "Hungryant constructor" << endl;
	this->armor = 1;
	this->cost = 4;
	this->name = "hungryant";
	this->digesting = 0;
}

// Non Default
Hungryant::Hungryant(int a) : Ant(){
	// cout << "Hungryant nondefault constructor" << endl;
	this->armor = a;
}

// Destructor
Hungryant::~Hungryant(){
	// cout << "Hungryant destructor" << endl;
}

void Hungryant::attack(vector<vector<Tile*>> GB, int x, int y, int k){
	/*********************************************************************
	** Function: Attack
	** Description: Goes through the ant's attack
	** Parameters: Game board, position that the ant is at on the board, and
	*  the position in the tile vector of this ant
	** Pre-Conditions: Tries to attack if it is able to
	** Post-Conditions: Performs its attack
	*********************************************************************/
	// Eats bee in front of it
	if(this->digesting == 0){
		// I want to attack 2 squares in front of it to mimic PvZ
		// Check the range
		int range = 0;
		switch(y){
			case 8: range = -1; //Only check 1 square ahead
			default: range += 2; //Normal 2 square range
		}

		// Check its own square, and then the next 1 or 2 squares
		for (int i = y; i < y + range + 1; ++i)
		{
			// Check for the first bee
			for (int j = 0; j < GB[x][i]->ent.size(); ++j)
			{
				// If it is a bee, then eat it
				if(GB[x][i]->ent[j]->get_name().compare("bee") == 0){
					GB[x][i]->ent[j]->take_dmg(15);
					if(GB[x][i]->ent[j]->get_armor() <= 0){
						this->digesting = 2;
					}
					return;
				}
			}
		}
	}

	else{
		this->digesting--;
	}
}

void Hungryant::take_dmg(int i){
	/*********************************************************************
	** Function: Take damage
	** Description: Takes i damage
	** Parameters: Amount of damage
	** Pre-Conditions: None
	** Post-Conditions: Reduces armor by the amount of damage
	*********************************************************************/
	this->armor = this->armor - i;
}