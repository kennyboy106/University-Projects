#include <iostream>
#include <string>
#include "Card.h"
#include "Deck.h"

using namespace std;

//default constructor
Card::Card(){
	/*********************************************************************
	** Function: Default constructor
	** Description: Initializes the rank and suit to 0 when a card it made
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Creates a 0 0 card object
	*********************************************************************/
	this->rank = 0; //goes from 0-12
	this->suit = 0; //goes from 0-3
}

//Copy Constructor
Card::Card(const Card &c){
	/*********************************************************************
	** Function: Copy card constructor
	** Description: Copies the data from c to new card
	** Parameters: A card object
	** Pre-Conditions: Card object is defined
	** Post-Conditions: Creates an identical card
	*********************************************************************/
	this->rank = c.rank;
	this->suit = c.suit;
}

//Non-default constructor
Card::Card(int r, int s){
	/*********************************************************************
	** Function: Non default card constructor
	** Description: Creates a card based on r and s
	** Parameters: rank and suit integers
	** Pre-Conditions: r is between 0 - 12 and s is between 0 - 3
	** Post-Conditions: Creates a card with r and s
	*********************************************************************/
	this->rank = r;
	this->suit = s;
}

// Assignment Overload
const Card& Card::operator=(const Card& c){
	/*********************************************************************
	** Function: Operator overload for Card
	** Description: Copies data from C to existing card object
	** Parameters: the target object
	** Pre-Conditions: Both are declared
	** Post-Conditions: Copies data from c to existing card
	*********************************************************************/
	if(this != &c){
		this->rank = c.rank;
		this->suit = c.suit;
	}
	return *this;
}

//Setters and getters
/*********************************************************************
** Function: Setters and getters
** Description: Each will either set or get rank or suit
** Parameters: For setters, the integer to set it to
** Pre-Conditions: setters have an int between 0-12 and 0-3 for rank or suit
** Post-Conditions: Changes rank or suit or return their value
*********************************************************************/
void Card::set_rank(int i){this->rank = i;}
void Card::set_suit(int i){this->suit = i;}
int Card::get_rank() const{return this->rank;}
int Card::get_suit() const{return this->suit;}

string Card::map_suit() const{
	/*********************************************************************
	** Function: Map suit
	** Description: Maps the suit of the card
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: returns a string
	*********************************************************************/
	switch(this->suit){
		case 0: return "Clubs";
		case 1: return "Spades";
		case 2: return "Diamonds";
		case 3: return "Hearts";
	}
	return "No suit";
}
string Card::map_rank() const{
	/*********************************************************************
	** Function: Map rank
	** Description: Maps the rank of the card
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Returns a string representation of the rank
	*********************************************************************/
	if(this->rank < 9){
		return to_string(this->rank + 2);
	}
	else{
		switch(this->rank){
			case 9: return "Jack";
			case 10: return "Queen";
			case 11: return "King";
			case 12: return "Ace";
			default: cout << "Rank of card is greater than 12. Inside map_rank function" << endl;
		}
	}
	return "No rank";
}

void Card::print_card() const{
	/*********************************************************************
	** Function: Print card
	** Description: Prints the card
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Prints the card
	*********************************************************************/
	switch(this->suit){
		case 0: cout << rank + 2 << " of Clubs" << endl;
				break;
		case 1: cout << rank + 2 << " of Spades" << endl;
				break;
		case 2: cout << rank + 2 << " of Diamonds" << endl;
				break;
		case 3: cout << rank + 2 << " of Hearts" << endl;
				break;
	}
}
