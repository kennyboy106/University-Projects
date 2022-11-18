#include <iostream>
#include "Hand.h"

using namespace std;

// Constructor
Hand::Hand(){
	this->cards = NULL;
	this->n_cards = 0;
}

// Done
// Assignment Overload
const Hand& Hand::operator=(const Hand& h){
	/*********************************************************************
	** Function: Assignment overload
	** Description: Copies one hand to another
	** Parameters: Target object
	** Pre-Conditions: Both are defined
	** Post-Conditions: Deep copies members to hand
	*********************************************************************/
	// cout << "Test flag Hand.cpp: AOO called" << endl;
	if(this != &h){
		// Delete old array of cards
		if(this->cards != NULL){
			delete [] cards;
		}

		// Get new number of cards
		this->n_cards = h.n_cards;
		// Copy members of cards over
		this->cards = new Card[this->n_cards];
		for(int i = 0; i < this->n_cards; i++){
			this->cards[i] = h.cards[i];
		}
	}
	return *this;
}


// De-constructor
Hand::~Hand(){
	/*********************************************************************
	** Function: De-constructor
	** Description: Frees memory at end of its use
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Frees memory
	*********************************************************************/
	if(this->cards != NULL){
		delete [] this->cards;
		this->cards = NULL;
	}
}
// Access
int Hand::get_n_cards() const{return this->n_cards;}
Card* Hand::get_cards(){return this->cards;}

// Give card at certain spot
Card Hand::get_card(int i) const{
	/*********************************************************************
	** Function: Get Card
	** Description: Gives me a card at a certain spot in cards
	** Parameters: Integer
	** Pre-Conditions: Integer is equal to or less than n_cards
	** Post-Conditions: Returns a card
	*********************************************************************/
	return this->cards[i]; //Gives me a card
}


// Mutate
void Hand::set_n_cards(int i){this->n_cards = i;}
void Hand::set_cards(Card* c){this->cards = c;}

// Done
void Hand::add_card(Card c){
	/*********************************************************************
	** Function: Add a card
	** Description: Adds a card c to the array of cards
	** Parameters: Card object
	** Pre-Conditions: None
	** Post-Conditions: Increases array size and adds the card to it
	*********************************************************************/
	if(this->cards != NULL){
		Card* temp = this->cards; //Save the pointer to OG array
		// Create new array
		this->cards = new Card[++this->n_cards];
		for(int i = 0; i < n_cards - 1; i++){
			// Copy all old objects in array
			this->cards[i] = temp[i];
		}
		// Copy last item to array
		this->cards[this->n_cards - 1] = c;
		delete [] temp;
		temp = NULL;
	}
	else{
		this->cards = new Card[++this->n_cards];
		this->cards[0] = c;
	}
}
// Done
void Hand::remove_card(Card c){
	/*********************************************************************
	** Function: Remove card
	** Description: Removes a specific card from cards array
	** Parameters: Card object to remove
	** Pre-Conditions: All are defined
	** Post-Conditions: Returns new array with card of c rank removed
	*********************************************************************/
	// Create temp array of current size - 1
	Card* temp = new Card[--this->n_cards];
	for(int i = 0; i < this->n_cards + 1; i++){
		// When we find the match in the original cards
		if(cards[i].get_rank() == c.get_rank()){
			// Save the spot it was found
			int place = 0;
			for(int j = 0; j < this->n_cards + 1; j++){
				// If the copier spot isn't at the spot the card was found
				// copy the card over
				if(j != i){
					temp[place++] = cards[j];
				}
			}
			break;
		}
	}
	// Delete the old array of cards
	delete [] cards;
	// Save the new array
	cards = temp;
}


// Done
void Hand::show_cards() const{
	/*********************************************************************
	** Function: Show cards
	** Description: Shows the array of cards
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Prints text to console
	*********************************************************************/
	for(int i = 0; i < this->n_cards; i++){
		cout << cards[i].map_rank() << " " << cards[i].map_suit() << endl;
	}
}

// Done
void Hand::sort_by_rank(){
	/*********************************************************************
	** Function: Sort by rank
	** Description: Sorts cards by rank
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Sorts cards by rank
	*********************************************************************/
	// Sort by rank
	int sort = 1, j = this->n_cards;
	while(sort){
		sort = 0;
		for(int i = 0; i < j - 1; i++){
			if(cards[i].get_rank() > cards[i + 1].get_rank()){
				Card temp = cards[i];
				cards[i] = cards[i + 1];
				cards[i + 1] = temp;
				sort = 1;
			}
		}
		j--;
	}
}

// Done
void Hand::sort_by_suit(){
	/*********************************************************************
	** Function: Sort by suit
	** Description: Sorts by suit
	** Parameters: None
	** Pre-Conditions: Cards is sorted by rank first
	** Post-Conditions: Sorts cards by suit within each rank, keeps all ranks
	*  of the same type together
	*********************************************************************/
	// Count how many different ranks there are
	int n_ranks = num_ranks();


	// Create an array of ints for that many ranks
	int* num_rank_arr = new int[n_ranks];
	for(int i = 0; i < n_ranks; i++){
		num_rank_arr[i] = 0;
	}


	// Now I need to count how many of each rank
	if(this->n_cards > 0)
		count_num_ranks(num_rank_arr);


	int place = 0; // Reset place
	for(int i = 0; i < n_cards; i++){
		// This will go through each number of ranks for n ranks
		for(int k = 0; k < num_rank_arr[place]; k++){
			// Sort them by suit in sub-divisions
			if(cards[i].get_suit() > cards[i + 1].get_suit()){
				Card temp = cards[i];
				cards[i] = cards[i + 1];
				cards[i + 1] = temp;
			}
			i++; // Move up in the list and get out of current number
		}
		place++;
	}

	delete [] num_rank_arr;
	num_rank_arr = NULL;
}

// Done
int Hand::num_ranks() const{
	/*********************************************************************
	** Function: Number of ranks
	** Description: Counts the number of different ranks in the cards array
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Returns the number of unique ranks
	*********************************************************************/
	// Check if hand isn't empty
	if(this->n_cards != 0){
		int n_ranks = 1;
		for(int i = 0; i < this->n_cards - 1; i++){
			int temp = cards[i].get_rank();
			if(temp != cards[i + 1].get_rank()){
				n_ranks++;
			}
		}
		return n_ranks;
	}
	// If hand it empty then return 0
	return 0;
}

// Done
void Hand::count_num_ranks(int* num_rank_arr){
	/*********************************************************************
	** Function: Count number of ranks
	** Description: Counts the number of a each type of rank
	** Parameters: Array of unique ranks
	** Pre-Conditions: Array of unique ranks is defined
	** Post-Conditions: Adds the number of each rank to a spot in num_rank_arr
	*********************************************************************/
	int place = 0;
	for(int i = 0; i < this->n_cards - 1; i++){
		if(cards[i].get_rank() == cards[i + 1].get_rank()){
			num_rank_arr[place]++;
		}
		else{
			place++;
		}
	}
}

int* Hand::book_locate(){
	/*********************************************************************
	** Function: Book locate
	** Description: Gets the number of times a unique rank shows up
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Returns an array of number of frequency of ranks
	*********************************************************************/
	int* num_rank_arr = new int[num_ranks()];
	for(int i = 0; i < num_ranks(); i++){
		num_rank_arr[i] = 0;
	}



	if(this->n_cards > 0){
		count_num_ranks(num_rank_arr);
	}
	return num_rank_arr;
}

void Hand::reset(){
	/*********************************************************************
	** Function: Reset
	** Description: Resets hand
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Resets hand
	*********************************************************************/
	this->n_cards = 0;
	delete [] this->cards;
	this->cards = NULL;
}