#include "Game.h"
#include <iostream>

using namespace std;

// Default Constructor
Game::Game(){
	/*********************************************************************
	** Function: Default constructor
	** Description: Creates the members, however since all members have their
	*  own default constructors, nothing needs to be done here
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Creates a game object with default member constructors
	*********************************************************************/
}

Game::Game(int argn, char** argv){
	/*********************************************************************
	** Function: Non default constructor
	** Description: Creates a game object and sets the command line argument
	*  to one of its variables
	** Parameters: Command line number of arguments and strings
	** Pre-Conditions: Command line has something in it
	** Post-Conditions: Sets argument to whatever the second argument was
	*********************************************************************/
	if(argn > 1){
		this->argument = argv[1];
	}
}



void Game::play_game(){
	/*********************************************************************
	** Function: Play game
	** Description: Takes the program through all the steps to play a game
	*  of go fish within the game object
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: None, but plays the game within itself
	*********************************************************************/
	srand(time(NULL));
	//Reset all object inside game to start new game//also shuffle deck
	cards.shuffle();
	//deal cards to all players
	deal();
	//sort players cards for each turn
	sort_hands();
	int play = 1;
	while(play){
		// Go through players
		for(int i = 0; i < 2; i++){
			if(cards.get_n_cards() == 0 && (players[0].num_cards() == 0 || players[1].num_cards() == 0)){
				// This will either reset the game or exit the program
				end_game(play);
				break;
			}
			if(!(cards.get_n_cards() == 0 && players[i].num_cards() == 0)){
				// Print who's turn it is
				cout << "\nPlayer " << i + 1 << "'s turn!" << endl;
				// Print that persons hands or books based on cheat mode
				print_hand_and_book(i);
				// Go through that players turn
				player_turn(i);
				// Check for any books in their hand and collect them
				// check_books(i);
				sort_hands();

			}
		}
	}
}


void Game::end_game(int &play){
	/*********************************************************************
	** Function: End of game
	** Description: Called when game should end, prints the players books
	*  and determines the winner. Also asks if the user wants to play again
	** Parameters: Looping variable so that if user wants to stop playing
	*  the program will exit normally and free memory
	** Pre-Conditions: None
	** Post-Conditions: Either resets or exits the program
	*********************************************************************/
	cout << "End of the game!\n" << endl;
	// Print both players books
	cout << "Player 1's books:" << endl;
	players[0].show_book();
	cout << "Player 2's books:" << endl;
	players[1].show_book();

	winner();
	play_again(play);
}

void Game::play_again(int &play){
	/*********************************************************************
	** Function: Play again
	** Description: asks the user if they want to play again
	** Parameters: Looping variable
	** Pre-Conditions: None
	** Post-Conditions: Changes looping variable depending on answer
	*********************************************************************/
	cout << "Would you like to play again? y/n: ";
	string line;
	while(1){
		getline(cin, line);
		if(line.size() == 1 && line[0] == 'y'){
			reset_game();
			break;
		}
		else if(line.size() == 1 && line[0] == 'n'){
			play = 0;
			break;
		}
		else{
			cout << "Please enter a y or n: ";
		}
	}
}

void Game::reset_game(){
	/*********************************************************************
	** Function: Reset game
	** Description: Resets the players and deck of cards. Shuffles the deck of
	*  cards again for new game
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Resets everything; players hands, deck of cards etc.
	*********************************************************************/
	cards.set_n_cards(52);
	cards.shuffle();
	players[0].reset();
	players[1].reset();
	deal();
	sort_hands();
}

void Game::winner(){
	/*********************************************************************
	** Function: Winner
	** Description: Determines the winner of the game based on number of books
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Prints text to console
	*********************************************************************/
	if(players[0].num_books() > players[1].num_books()){
		cout << "Player 1 wins!" << endl;
	}
	else if(players[0].num_books() < players[1].num_books()){
		cout << "Player 2 wins!" << endl;
	}
	else{
		cout << "Its a tie! Both players win or lose" << endl;
	}
}

// Done
void Game::deal(){
	/*********************************************************************
	** Function: Deal
	** Description: Deals 7 cards to the two players
	** Parameters: None
	** Pre-Conditions: Deck has at least 14 cards in it
	** Post-Conditions: Adds 7 cards to each players hand
	*********************************************************************/
	// int passing = 0;
	for(int i = 0; i < 7; i++){
		// Loop 7 times, hand out 7 cards
		// Pass each player a card from the deck of cards;
		for(int j = 0; j < 2; j++){
			// This is passing a card from cards at passing
			players[j].add_card(cards.return_card(cards.get_n_cards() - 1));
			// This then removes the card just given
			cards.remove_card();
		}
	}
}
// Done
void Game::draw_a_card(int p){
	/*********************************************************************
	** Function: Draw a card
	** Description: Draws a card from the deck and adds it to the players hand
	** Parameters: Which player it is that is drawing
	** Pre-Conditions: Deck has at least 1 card in it
	** Post-Conditions: Adds a card to player p's hand
	*********************************************************************/
	if(cards.get_n_cards() != 0){
		players[p].add_card(cards.return_card(cards.get_n_cards() - 1));
		cards.remove_card();
	}
	else{
		cout << "Error No more cards to draw" << endl;
	}
}
// Done
void Game::sort_hands(){
	/*********************************************************************
	** Function: Sort hands
	** Description: Sorts all players hands
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: All player's hands are sorted
	*********************************************************************/
	for(int i = 0; i < 2; i++){
		players[i].sort_cards();
	}
}

// Done
void Game::player_turn(int p){
	/*********************************************************************
	** Function: Player turn
	** Description: Goes through the turn for player p
	** Parameters: Which player's turn it is
	** Pre-Conditions: None
	** Post-Conditions: Adds, removes, draws, creates books, for a player.
	*  **Why over 15 lines? This function calls all the functions to go
	*    through a turn so reducing this down means I need to create more
	*    functions that hold just a few lines of code, making it more
	*    difficult to read the flow of a turn.
	*********************************************************************/
	int turn = 1;
	while(turn){
		turn = 0;
		if(players[p].num_cards() == 0 && cards.get_n_cards() != 0){
			// If player has no cards, they draw a card
			go_fish(p, "");
		}
		// If the deck is empty and player has no cards, then turn is over
		else if(players[p].num_cards() == 0){
			break;
		}
		// Find a card to ask for
		Card seeking_card = fishing_card(p);
		// If its the computer, ask for the card
		if(p == 0){
			cout << "Player " << p + 1 << ": Do you have any: " << seeking_card.map_rank() << "'s" << endl;

		}
		int match = 0;
		// Look for asked card through the other persons hand
		seek_and_swap(seeking_card, p, 1 - p, match, turn);

		// If no matches, draw a card and compare to what was asked
		if(match == 0 && cards.get_n_cards() != 0){
			go_fish(p, "fishing");
			if(players[p].card_at(players[p].num_cards() - p).get_rank() == seeking_card.get_rank()){
				cout << "Player " << p + 1 << " found a " << players[p].card_at(players[p].num_cards() - p).map_rank() << " while fishing!" << endl;
				turn = 1;
			}
		}
		sort_hands();
		check_books(p);
		print_hand_and_book(p);
	}
}

// Done
void Game::seek_and_swap(Card c, int recip, int giver, int &match, int &turn){
	/*********************************************************************
	** Function: Seek and swap
	** Description: Parse through opponents cards to find a match. If a match
	*  is found, transfer it to the recipients hand
	** Parameters: The card to look for, which player asked and which player is
	*  the opponent, matching variable and looping variable
	** Pre-Conditions: All were initialized
	** Post-Conditions: Transfers card from one persons hand to another
	*********************************************************************/
	// Search through the other persons cards
	for(int i = 0; i < players[giver].num_cards(); i++){
		// If find a matching card, take it
		if(c.get_rank() == players[giver].card_at(i).get_rank()){
			// Move all matches to the other hand hand
			card_transfer(recip, giver, i, match, turn);
		}
	}
	sort_hands();

	cout << endl;
}
// Done
Card Game::fishing_card(int p){
	/*********************************************************************
	** Function: Fishing card
	** Description: Chooses the appropriate function for which player it is
	** Parameters: Player number
	** Pre-Conditions: P is defined and between 0 - 1
	** Post-Conditions: Calls the correct function and returns the card chosen
	*********************************************************************/
	if(p == 0){
		return c_fishing_card();
	}
	else if(p == 1){
		return p_fishing_card();
	}
	else{
		cout << "Error in choosing function for fishing card" << endl;
	}
	Card temp;
	return temp;
}

// Done
Card Game::p_fishing_card(){
	/*********************************************************************
	** Function: Player fishing card
	** Description: Ask the player for what card they want to choose
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Returns a card they choose
	*********************************************************************/
	while(1){
		cout << "What card would you like to ask for? ";
		string line;
		getline(cin, line);
		// Compare the input to the ranks of the cards
		for(int i = 0; i < players[1].num_cards(); i++){
			// If a match is found
			if(line.compare(players[1].card_at(i).map_rank()) == 0){
				// Return the matched card
				return players[1].card_at(i);
			}
		}
		cout << "That card doesn't appear to be in your hand. This is case sensitive. Ex: Jack" << endl;
		cout << "Please try again: ";
	}
	// Need to return something so yeah
	Card uh;
	return uh;
}

// Done
Card Game::c_fishing_card(){
	/*********************************************************************
	** Function: Computer fishing card
	** Description: Get a random card that the computer asks for
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Returns a matching card
	*********************************************************************/
	// Get me a matching card
	while(1){
		// Create a random card
		Card seeking_rank(rand() % 13, 0);
		for(int i = 0; i < players[0].num_cards(); i++){
			// Is created card a match?
			if(seeking_rank.get_rank() == players[0].card_at(i).get_rank()){
				return seeking_rank;
			}
		}
	}
	// Need to have return condition
	Card uh;
	return uh;
}

// Done
// Move card i from giver to recip
void Game::card_transfer(int recip, int giver, int &i, int &match, int &turn){
	/*********************************************************************
	** Function: Card transfer
	** Description: Transfers a matching card from the opponent to the recipient
	** Parameters: Which player is receiving, asking, location of card in opponents
	*  hand, the match variable, looping variable
	** Pre-Conditions: All are defined
	** Post-Conditions: Moves a card from giver's hand to recipient's hand
	*********************************************************************/
	players[recip].add_card(players[giver].card_at(i));

	// Announce what cards were taken
	cout << "Player " << recip + 1 << " got a " << players[giver].card_at(i).map_rank();
	cout << " of " << players[giver].card_at(i).map_suit();
	cout << " from Player " << giver + 1 << endl;
	// This will play for every card

	// Remove the card from giver
	players[giver].remove_card(players[giver].card_at(i));
	i--;
	match++;
	turn++;
}

// Done
// If a player needs to go fishing for any reason
void Game::go_fish(int p, string type){
	/*********************************************************************
	** Function: Go fish
	** Description: Draw a card from the deck
	** Parameters: Which player is drawing, the type of fishing
	** Pre-Conditions: p is between 0 - 1 and the deck isn't empty
	** Post-Conditions: Adds a card from the deck to the player
	*********************************************************************/
	if(type.compare("fishing") == 0){
		cout << "Player " << 2 - p << ": Go Fish!" << endl;
	}

	cout << "Player " << p + 1 << " went fishing" << endl;
	draw_a_card(p);
	if(type.compare("fishing") != 0){
		print_hand_and_book(1);
	}
}


void Game::check_books(int p){
	/*********************************************************************
	** Function: Check books
	** Description: Checks the players hand for books
	** Parameters: Which player is being checked
	** Pre-Conditions: None
	** Post-Conditions: Removes books from hand and copies the rank to
	*  book array
	*********************************************************************/
	// Get an array of number of ranks. See count_num_ranks for function
	int* book_locations = players[p].book_locate();

	// Go down backwards through the array of books locations
	for(int i = players[p].num_ranks() - 1; i >= 0; i--){
		if(book_locations[i] == 3){
			// Find the spot in the cards array
			int place = 0;
			for(int j = 0; j < i; j++){
				place += book_locations[j] + 1;
			}
			// Save what rank it is before deleting
			players[p].add_book(players[p].card_at(place).get_rank() + 2);
			cout << "Player " << p + 1 << " made a book!" << endl;
			for(int j = 0; j < 4; j++){
				// Remove the card in that place 4 times
				// We do this 4 times because every time we remove a card
				// From the array, the cards are moved down one place and
				// our indices are at the right place without changing it
				players[p].remove_card(players[p].card_at(place));

			}
		}

	}
	// Delete array because I'm done with it **throws it to the side**
	delete [] book_locations;
}

void Game::print_hand_and_book(int p){
	/*********************************************************************
	** Function: Print hand and book
	** Description: Prints the hand and book for player p
	** Parameters: Which player it is
	** Pre-Conditions: None
	** Post-Conditions: Prints to console
	*********************************************************************/
	if(p == 0 && argument.compare("true") == 0){
		cout << "Player " << p + 1 << "'s hand:" << endl;
		players[p].show_hand();
		cout << "Player " << p + 1 << "'s books:" << endl;
		players[p].show_book();
	}
	else if(p == 1){
		cout << "Player " << p + 1 << "'s hand:" << endl;
		players[p].show_hand();
		cout << "Player " << p + 1 << "'s books:" << endl;
		players[p].show_book();
	}
}


