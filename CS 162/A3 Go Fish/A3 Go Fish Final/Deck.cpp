#include <iostream>
#include <time.h>
#include "Deck.h"
#include "Card.h"

using namespace std;

// Done
// Default Constructor
Deck::Deck(){
	/*********************************************************************
	** Function: Default constructor
	** Description: Sets n_card to 52 and initializes a deck of cards
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Initializes member variables and creates deck of cards
	*********************************************************************/
	this->n_cards = 52;
	int assign = 0;
	// Initialize a deck of cards
	for(int i = 0; i < 13; i++){
		for(int j = 0; j < 4; j++){
			cards[assign].set_rank(i);
			cards[assign++].set_suit(j);
		}
	}
}

// Done
void Deck::print_deck() const{
	/*********************************************************************
	** Function: Print deck
	** Description: Prints the deck of cards
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Prints the remaining cards in the stock
	*********************************************************************/
	for(int i = 0; i < this->n_cards; i++){
		cout << cards[i].map_rank() << " " << cards[i].map_suit() << endl;
	}
}

// Done
void Deck::set_n_cards(int i){
	/*********************************************************************
	** Function: Set number of cards
	** Description: Sets the number of remaining cards in the deck
	** Parameters: Integer
	** Pre-Conditions: Integer is between 0 and 52
	** Post-Conditions: Changes n_cards to int
	*********************************************************************/
	this->n_cards = i;
}
// Done
int Deck::get_n_cards() const{
	/*********************************************************************
	** Function: Get number of cards
	** Description: Gets the number of cards left in the deck
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Returns the number of cards left in the deck
	*********************************************************************/
	return this->n_cards;
}
// Done
Card Deck::return_card(int i){
	/*********************************************************************
	** Function: Return card
	** Description: Returns the card at place i in the deck
	** Parameters: Integer
	** Pre-Conditions: Integer is between 0 and 52 and is less than n_cards
	** Post-Conditions: Returns a card from the deck
	*********************************************************************/
	return cards[i];
}


// Done
void Deck::shuffle(){
	/*********************************************************************
	** Function: Shuffle
	** Description: Shuffles the deck of cards
	** Parameters: None
	** Pre-Conditions: deck of cards is defined
	** Post-Conditions: Shuffles the deck of cards
	*********************************************************************/
	srand(time(NULL));
	int limit = 400;
	for(int i = 0; i < limit; i++){
		int p1 = rand() % 52;
		Card temp = cards[p1];
		cards[p1] = cards[i % 52];
		cards[i % 52] = temp;
	}
}




// Done
void Deck::remove_card(){
	/*********************************************************************
	** Function: Remove a card
	** Description: Reduces n_cards by 1
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Reduces n_cards by 1
	*********************************************************************/
	this->n_cards--;
}
