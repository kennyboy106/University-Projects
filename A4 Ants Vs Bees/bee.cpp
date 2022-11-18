#include <iostream>
#include "bee.h"



using namespace std;

// Default
Bee::Bee() : Piece(){
	// cout << "Bee constructor" << endl;
	this->armor = 3;
	this->frozen = 0;
}

// Non Default
Bee::Bee(int a) : Piece(){
	this->armor = a;
}

// Destructor
Bee::~Bee(){
	// cout << "Bee destructor" << endl;
}
// Getters
int Bee::get_armor(){
	return this->armor;
}

string Bee::get_name(){
	return this->name;
}



void Bee::attack(vector<vector<Tile*>> GB, int x, int y, int k){
	/*********************************************************************
	** Function: Attack
	** Description: Takes the bee through its attack
	** Parameters: Game board, position on the board and position of the vector its in
	** Pre-Conditions: All are defined
	** Post-Conditions: The bee attacks depending on frozen
	*********************************************************************/
	/**For the bees to attack they need to deal 1 damage to the ant in front of it or move forward
	 * First
	 * 		detect if an ant is in front of it
	 * 			check the tile in front of it to see if vector length is not 0
	 * 			if its not zero, then deal 1 damage to the last element in that vector
	 * 		if no ant, then move to the next tile's vector
	 * information i need for that: i need the position that the bee is at
	 * I need the to derive the space next to it from the position
	 */

	// Check to see if tile in front is empty
	// cout << "Bee attack" << endl;
	if(this->frozen == 0){
		if(tile_available(GB, x, y - 1)){
			// Move forwards
			// Set the pointer of this bee to the next vector
			GB[x][y-1]->ent.push_back(GB[x][y]->ent[k]);

			// Remove it from the space its in
			GB[x][y]->ent.erase(GB[x][y]->ent.begin() + k);
			// cout << "Bee moved" << endl;

		}
		// If the tile has an ant that isn't a ninja, attack it
		else{
			// cout << "Bee attacked" << endl;
			// attack the bodyguard in vector first
			for (int i = 0; i < GB[x][y-1]->ent.size(); ++i)
			{
				if(GB[x][y-1]->ent[i]->get_name().compare("bodyguard") == 0){
					// attack the bodyguard
					GB[x][y-1]->ent[i]->take_dmg(1);
					// This should be the end of the attack
					return;
				}
			}
			// If couldn't find the bodyguard, attack the last ant in the array
			GB[x][y-1]->ent[GB[x][y-1]->ent.size() - 1]->take_dmg(1);


			// Testing
			// cout << "Armor of the ant that took damage: ";
			// cout << GB[x][y-1]->ent[GB[x][y-1]->ent.size() - 1]->get_armor() << endl;

		}
	}
	else{
		this->frozen--;
	}
}

void Bee::take_dmg(int i){
	/*********************************************************************
	** Function: Take damage
	** Description: Takes i damage
	** Parameters: Amount of damage
	** Pre-Conditions: None
	** Post-Conditions: Reduces armor by the amount of damage
	*********************************************************************/
	this->armor = this->armor - i;
}


// Does nothing because it's never called for a bee. Needed for virtual function
int Bee::get_cost(){return 0;}


bool Bee::tile_available(vector<vector<Tile*>> GB, int x, int y){
	/*********************************************************************
	** Function: Tile available
	** Description: Tells the bee if they should be able to move onto a tile
	** Parameters: The position in the game board that they are interested in
	** Pre-Conditions: All are defined
	** Post-Conditions: Returns true or false
	*********************************************************************/
	if(GB[x][y]->ent.size() == 0){
		return true;
	}
	else{
		// check through all the elements of the vector
		// If i find an all bees or a ninja, then return true
		for (int i = 0; i < GB[x][y]->ent.size(); ++i)
		{
			// If you something that isn't a bee or a ninja, it must be an ant
			if(GB[x][y]->ent[i]->get_name().compare("bee") != 0 && GB[x][y]->ent[i]->get_name().compare("ninja") != 0 && GB[x][y]->ent[i]->get_name().compare("fire") != 0){
				return false;
			}
		}
		// If you don't find any non bee or ninja matches, return true
		return true;
	}
	return false;
}

void Bee::freeze(int i){
	/*********************************************************************
	** Function: Freeze
	** Description: Called and inflicts a freeze onto the bee
	** Parameters: Strength of the freeze as an integer
	** Pre-Conditions: None
	** Post-Conditions: Applies frozen to the bee
	*********************************************************************/
	this->frozen = i;
}