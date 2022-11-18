#include "bodyguard.h"


using namespace std;

// Default
Bodyguard::Bodyguard() : Ant(){
	// cout << "Bodyguard constructor" << endl;
	this->armor = 2;
	this->cost = 4;
	this->name = "bodyguard";
}

// Non Default
Bodyguard::Bodyguard(int a) : Ant(){
	// cout << "Bodyguard nondefault constructor" << endl;
	this->armor = a;
}

// Destructor
Bodyguard::~Bodyguard(){
	// cout << "Bodyguard destructor" << endl;
}

void Bodyguard::attack(vector<vector<Tile*>> GB, int x, int y, int k){
	// Body guard doesn't attack
	// cout << "Bodyguard stood there menacingly" << endl;
}

void Bodyguard::take_dmg(int i){
	/*********************************************************************
	** Function: Take damage
	** Description: Takes i damage
	** Parameters: Amount of damage
	** Pre-Conditions: None
	** Post-Conditions: Reduces armor by the amount of damage
	*********************************************************************/
	this->armor = this->armor - i;
}