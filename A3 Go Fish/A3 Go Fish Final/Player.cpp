#include <iostream>
#include "Hand.h"
#include "Player.h"

using namespace std;

// Default constructor
Player::Player(){
	/*********************************************************************
	** Function: Default constructor
	** Description: Create a player object with default values
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Create new player object
	*********************************************************************/
	this->books = NULL;
	this->n_books = 0;
}
// Copy constructor
Player::Player(const Player& p){
	/*********************************************************************
	** Function: Copy constructor
	** Description: Creates new player with data from another player
	** Parameters: Target object
	** Pre-Conditions: Target object is defined
	** Post-Conditions: Create copy object
	*********************************************************************/
	this->n_books = p.n_books;
	//Copy hand
	this->hand.set_n_cards(p.hand.get_n_cards()); //Copy number of cards
	this->hand.set_cards(new Card[this->hand.get_n_cards()]); //Create correctly sized array
	for(int i = 0; i < this->hand.get_n_cards(); i++){
		this->hand.add_card(p.hand.get_card(i)); //Copy each card to new array
	}
	//Copy array of int books
	this->books = new int[this->n_books];	//Create new array of same size
	for(int i = 0; i < this->n_books; i++){
		this->books[i] = p.books[i]; 		//Copy the integers in the array
	}

}
// Assignment Overload
const Player& Player::operator=(const Player& p){
	/*********************************************************************
	** Function: Assignment overload
	** Description: Copies data from one player to another
	** Parameters: Target player
	** Pre-Conditions: Both are defined
	** Post-Conditions: Copies data
	*********************************************************************/
	// cout << "Test flag Player.cpp: AOO called" << endl;
	if(this != &p){
		// Remove old array
		if(this->books != NULL){
			delete [] books;
		}

		this->hand = p.hand; // Operator overload to hand copy

		// Grab new size
		this->n_books = p.n_books;

		// Create new array of same size
		this->books = new int[this->n_books];
		for(int i = 0; i < this->n_books; i++){
			// Copy each element over
			books[i] = p.books[i];
		}
	}
	return *this;
}
// De-constructor
Player::~Player(){
	/*********************************************************************
	** Function: De-constructor
	** Description: Frees memory at end of use
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Free memory
	*********************************************************************/
	if(books != NULL){
		delete [] books;
		books = NULL;
	}
}



void Player::add_card(Card c){
	/*********************************************************************
	** Function: Add card
	** Description: Calls hand function to add a card and passes card into it
	** Parameters: Card object
	** Pre-Conditions: Card is defined
	** Post-Conditions: Adds a card to hand
	*********************************************************************/
	this->hand.add_card(c);
}

void Player::remove_card(Card c){
	/*********************************************************************
	** Function: Remove card
	** Description: Calls hand function to remove a specific card
	** Parameters: Card object
	** Pre-Conditions: Card is defined
	** Post-Conditions: Removes specific card from hand
	*********************************************************************/
	this->hand.remove_card(c);
}


void Player::add_book(int b){
	/*********************************************************************
	** Function: Add book
	** Description: Adds a rank to the book array and makes room for it
	** Parameters: Integer to be added
	** Pre-Conditions: None
	** Post-Conditions: Increases size of books and adds b to it
	*********************************************************************/
	if(books != NULL){
		int* temp = new int[++n_books];
		for(int i = 0; i < n_books - 1; i++){
			temp[i] = books[i];
		}
		temp[n_books - 1] = b;
		delete [] books;
		this->books = temp;
	}
	else if(books == NULL){
		books = new int[++n_books];
		this->books[0] = b;
	}
}



void Player::show_hand() const{
	/*********************************************************************
	** Function: Show hand
	** Description: Calls hand function to show cards
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Shows the cards in hand
	*********************************************************************/
	this->hand.show_cards();
}

void Player::show_book() const{
	/*********************************************************************
	** Function: Show book
	** Description: Prints the book elements
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Prints the books
	*********************************************************************/
	for(int i = 0; i < n_books; i++){
		if(books[i] < 11){
			cout << books[i] << " ";
		}
		else if(books[i] > 10){
			switch(books[i]){
				case 11: cout << "Jack ";
						 break;
				case 12: cout << "Queen ";
						 break;
				case 13: cout << "King ";
						 break;
				case 14: cout << "Ace ";
						 break;
				default: cout << "Rank of card is greater than 12. Inside show book function" << endl;
				}
		}
	}
	cout << endl;
}


// Done
// Get a card at certain point
Card Player::card_at(int i){
	/*********************************************************************
	** Function: Card at
	** Description: Returns a card at a specific point
	** Parameters: Integer location
	** Pre-Conditions: i is within the number of cards
	** Post-Conditions: Returns a card
	*********************************************************************/
	return this->hand.get_card(i);
}

// Done
void Player::sort_cards(){
	/*********************************************************************
	** Function: Sort cards
	** Description: Calls the sorting functions in correct order
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Sorts cards
	*********************************************************************/
	this->hand.sort_by_rank();
	this->hand.sort_by_suit();
}


int* Player::book_locate(){
	/*********************************************************************
	** Function: Book locate
	** Description: Calls the hand book locate function
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Returns integer array
	*********************************************************************/
	return this->hand.book_locate();
}
// Done
int Player::num_ranks(){
	/*********************************************************************
	** Function: Number of ranks
	** Description: Returns the number of ranks with the hand function
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Returns the number of ranks
	*********************************************************************/
	return this->hand.num_ranks();
}
// Done
int Player::num_cards(){
	/*********************************************************************
	** Function: Number of cards
	** Description: Returns the number of cards with the hand function
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Returns the number of cards
	*********************************************************************/
	return this->hand.get_n_cards();
}

int Player::num_books(){
	/*********************************************************************
	** Function: Number of books
	** Description: Returns the number of books
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Returns the number of books
	*********************************************************************/
	return this->n_books;
}


void Player::reset(){
	/*********************************************************************
	** Function: Reset
	** Description: Resets all member variables of player and calls reset on hand
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Resets players member variables
	*********************************************************************/
	this->hand.reset();
	delete [] this->books;
	this->books = NULL;
	this->n_books = 0;
}