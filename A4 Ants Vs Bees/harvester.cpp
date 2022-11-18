#include "harvester.h"


using namespace std;

// Default
Harvester::Harvester() : Ant(){
	// cout << "Harvester constructor" << endl;
	this->armor = 1;
	this->cost = 2;
	this->name = "harvester";
}

// Non Default
Harvester::Harvester(int a) : Ant(){
	// cout << "Harvester nondefault constructor" << endl;
	this->armor = a;
}

// Destructor
Harvester::~Harvester(){
	// cout << "Harvester destructor" << endl;
}

void Harvester::attack(vector<vector<Tile*>> GB, int x, int y, int k){
	// Generate food at end of turn
	// cout << "Harvester attack" << endl;
	food++;
}

void Harvester::take_dmg(int i){
	/*********************************************************************
	** Function: Take damage
	** Description: Takes i damage
	** Parameters: Amount of damage
	** Pre-Conditions: None
	** Post-Conditions: Reduces armor by the amount of damage
	*********************************************************************/
	this->armor = this->armor - i;
}