#include <iostream>
#include "ant.h"


using namespace std;


// Default constructor
Ant::Ant() : Piece(){
	// cout << "Ant default constructor" << endl;
	this->armor = 0;
}
// Non default constructor
Ant::Ant(int a): Piece() {
	// cout << "Ant non default constructor" << endl;
	this->armor = a;
}
// Destructor
Ant::~Ant(){
	// cout << "Ant destructor" << endl;
}

// Getters
int Ant::get_armor(){
	return this->armor;
}

int Ant::get_cost(){
	return this->cost;
}

string Ant::get_name(){
	return this->name;
}


// Dummy function
void Ant::freeze(int a){}