#include "functions.h"
#include "harvester.h"
#include "fire.h"
#include "thrower.h"
#include "snow_thrower.h"
#include "hungryant.h"
#include "wall.h"
#include "ninja.h"
#include "bodyguard.h"
using namespace std;



		//Adding Ants and Bees //

// Done
void add_bee(vector<vector<Tile*>> GB){
	/*********************************************************************
	** Function: Add bee
	** Description: Adds a bee to the beehive column of a random row
	** Parameters: Game board
	** Pre-Conditions: Game board is defined
	** Post-Conditions: Adds a bee to the board
	*********************************************************************/
	srand(time(NULL));
	Piece* new_bee = new Bee;
	int place = rand() % GB.size();
	// Place a new bee into the vector of the tile at the random space
	GB[place][9]->ent.push_back(new_bee);
}
// Done
void add_ant(vector<vector<Tile*>> GB){
	/*********************************************************************
	** Function: Add ant
	** Description: Prints the table of available ants then asks what type
	*  of ant the user wants to place. It then checks to see if the space
	*  the user wants is available (with bodyguard factored in). Can't place
	*  on beehive or queen
	** Parameters: The game board vector and the number of rows
	** Pre-Conditions: Game board is defined
	** Post-Conditions: Adds an ant to the board. If a bodyguard goes onto an ant
	*  it is on the last element.
	*********************************************************************/
	while(1){
		print_ant_types();
		// Print out options including na
		while(1){
			// Get what they entered
			int ant_type = get_positive_int(1, 9);
			Piece* desired_ant = make_ant(ant_type);
			// Food check
			// If sufficient food for desired ant
			if(Ant::food >= desired_ant->get_cost() && ant_type != 9){
				try_to_place_ant(GB, ant_type, desired_ant);
				display_board(GB);
				break;
			}
			else if(Ant::food < desired_ant->get_cost() && ant_type != 9){
				cout << "Not enough food for that ant. What would you like to place: ";
				delete desired_ant;
			}
			else if(ant_type == 9){
				// Remove dynamic ant
				delete desired_ant;
				return;
			}
		}
	}
}
// Done
void try_to_place_ant(vector<vector<Tile*>> GB, int ant_type, Piece* desired_ant){
	/*********************************************************************
	** Function: Try to place ant
	** Description: Asks for position and tried to place the ant there, if it can't
	*  it will ask for a new position
	** Parameters: Game board, type of any trying to be placed, and the new ant
	** Pre-Conditions: All are defined
	** Post-Conditions: Adds an ant to the game board
	*********************************************************************/
	while(1){
		// Get the place that the user wants to place it
		cout << "Where would you like to place it?" << endl;
		cout << "Rows go from 0 - n, Columns go from 0 - 9" << endl;
		cout << "Row: ";
		int x = get_positive_int(0, GB.size() - 1);
		cout << "Column: ";
		// Cant place on square 0 or square 9
		int y = get_positive_int(1, 8);


		// Check to see if square is occupied
		if(tile_empty(GB, x, y, ant_type)){
			// Now push that ant back
			GB[x][y]->ent.push_back(desired_ant);
			// Adjust food available
			Ant::food = Ant::food - desired_ant->get_cost();
			ant_order(GB[x][y]->ent);
			return;
		}
		else{
			cout << "Can't place the ant there. Enter new location." << endl;
		}
	}
}

// Done
Piece* make_ant(int i){
	/*********************************************************************
	** Function: Make ant
	** Description: Generates an ant depending on the integer supplied
	** Parameters: Int
	** Pre-Conditions: None
	** Post-Conditions: Returns a Piece pointer to the new object
	*********************************************************************/
	switch(i){
		case 1: return new Harvester;
		case 2: return new Fire;
		case 3: return new Thrower;
		case 4: return new Snow_thrower;
		case 5: return new Hungryant;
		case 6: return new Wall;
		case 7: return new Ninja;
		case 8: return new Bodyguard;
	}

	return new Harvester;
}
// Done
bool tile_empty(vector<vector<Tile*>> GB, int x, int y, int ant_type){
	/*********************************************************************
	** Function: Tile_empty
	** Description: Checks to see if a tile is empty. If its not empty and the
	*  user wants to place a bodyguard, it checks to see if the other ant on the space
	*  is a bodyguard
	** Parameters: Game board, position coordinates, type of ant (refer to print_ant_types
	*  for values of ants)
	** Pre-Conditions: Coordinated must be within the limits of game board.
	** Post-Conditions: Returns true or false if a ant can or can't be placed in the
	*  space
	*********************************************************************/
	// Check to see if its the tile in question has an empty vector

	// If there is only one other ant there
	if(GB[x][y]->ent.size() == 1 && GB[x][y]->ent[0]->get_name().compare("bee") != 0){
		// If the space has something, check to see what it is if I'm placing
		// a bodyguard
		if(ant_type == 8){
			// If placing bodyguard, is the first ant a bodyguard?
			if(GB[x][y]->ent[0]->get_name().compare("bodyguard") != 0){
				return true;
			}
		}
		// If I'm not placing a bodyguard, check if the square is a bodyguard
		else if(GB[x][y]->ent[0]->get_name().compare("bodyguard") == 0){
			return true;

		}
		// If
		else{
			return false;
		}
	}
	// If space empty
	else if(GB[x][y]->ent.size() == 0){
		return true;
	}
	else if(GB[x][y]->ent.size() > 1){
		return false;
	}
	return false;
}

void ant_order(vector<Piece*> ent){
	/*********************************************************************
	** Function: Ant order
	** Description: If there are 2 ants on a tile and the bodyguard isn't on
	*  last position of the tile vector then move it to the end
	** Parameters: The vector of pieces for that tile
	** Pre-Conditions: None
	** Post-Conditions: Switches bodyguard to the end if its not already there
	*********************************************************************/
	if (ent.size() == 2 && ent[1]->get_name().compare("bodyguard") != 0)
	{
		// Check to see if bodyguard is on the last place
		// if it isn't then switch them
		// get the bodyguard pointer
		Piece* temp = ent[0];

		// Erase the bodyguard pointer from the vector
		ent.erase(ent.begin());
		// Push it to the end
		ent.push_back(temp);
	}
}

		// Going through the turns of ants and bees //
// Done
void ant_attack(vector<vector<Tile*>> GB){
	/*********************************************************************
	** Function: Ant attack
	** Description: Goes through the board looking for ants and letting them
	*  attack
	** Parameters: The game board
	** Pre-Conditions: All are defined
	** Post-Conditions: Ants attack
	*********************************************************************/
	// I need to go through the board and find all the ants

	// When i find an ant, execute its attack
	// Rows
	for (int i = 0; i < GB.size(); ++i)
	{
		// Columns
		for (int j = 0; j < GB[i].size(); ++j)
		{
			// Index of that vector
			for (int k = 0; k < GB[i][j]->ent.size(); ++k)
			{
				// If its not an ant in that spot, attack
				if(GB[i][j]->ent[k]->get_name().compare("bee") != 0){
					GB[i][j]->ent[k]->attack(GB, i, j, k);

					// Delete bees with 0 or less armor
					check_type_armor(GB, "bee");
				}
			}
		}
	}
}

// Done
void bee_attack(vector<vector<Tile*>> GB){
	/*********************************************************************
	** Function: Bee attack
	** Description: Goes through the board letting the bees attack
	** Parameters: The game board
	** Pre-Conditions: Board is defined
	** Post-Conditions: Bees go through their attacks
	*********************************************************************/
	// Rows
	for (int i = 0; i < GB.size(); ++i)
	{
		// Columns
		for (int j = 0; j < GB[i].size(); ++j)
		{
			// Index of that vector
			for (int k = GB[i][j]->ent.size() - 1; k >= 0; --k)
			{
				// if it is a bee
				if(GB[i][j]->ent[k]->get_name().compare("bee") == 0){
					// Bee attack
					GB[i][j]->ent[k]->attack(GB, i, j, k);

					// Delete dead ants
					check_type_armor(GB, "ant");
				}
			}
		}
	}
}

// Done
void check_type_armor(vector<vector<Tile*>> GB, string type){
	/*********************************************************************
	** Function: Check type armor
	** Description: Type is to be defined as ant or bee and then it checks the
	*  armor of all of those type. If the armor is 0 or less, it deletes that
	*  piece
	** Parameters: The game board and the type of piece to check
	** Pre-Conditions: All are defined
	** Post-Conditions: Deletes pieces with 0 or less hp
	*********************************************************************/
	// Rows
	for (int i = 0; i < GB.size(); ++i)
	{
		// Columns
		for (int j = 0; j < GB[i].size(); ++j)
		{
			for (int k = GB[i][j]->ent.size() - 1; k >= 0; --k)
			{

				if(type.compare("bee") == 0){
					// If there is a bee and it's armor is 0 or less, delete it and remove it from the list
					if(GB[i][j]->ent[k]->get_name().compare("bee") == 0 && GB[i][j]->ent[k]->get_armor() <= 0){
						delete GB[i][j]->ent[k];
						GB[i][j]->ent.erase(GB[i][j]->ent.begin() + k);
					}
				}
				else if(type.compare("ant") == 0){
					if(GB[i][j]->ent[k]->get_name().compare("bee") != 0 && GB[i][j]->ent[k]->get_armor() <= 0){
						delete GB[i][j]->ent[k];
						GB[i][j]->ent.erase(GB[i][j]->ent.begin() + k);
					}
				}
			}
		}
	}
}







		// Utility //
// Done
bool validint(string i){
	/*********************************************************************
	** Function: Valid integer
	** Description: Checks to see if string is a valid integer. Doesn't accept doubles
	** Parameters: String
	** Pre-Conditions: string is defined
	** Post-Conditions: returns true or false
	*********************************************************************/
	if(i.length() != 0){						//make sure string contains something
		for(int j = 0; j < i.length(); j++){	//Check every character in string to make sure its a digit
			if(!isdigit(i[j])){					//make sure negative sign is ignored once
				if(!(i[j] == '-' && j == 0)){
					return false;
				}
			}
		}
		return true;
	}
	else
		return false;
}

// Done
bool victory_condition(vector<vector<Tile*>> GB){
	/*********************************************************************
	** Function: Victory condition
	** Description: Checks to see if the game should end or not. Returns false
	*  if the game should be over
	** Parameters: The game board
	** Pre-Conditions: None
	** Post-Conditions: Returns true or false
	*********************************************************************/
	// I need to check to see if the board has any bees
	int num_bees = 0, bees_on_queen = 0;
	// Rows
	for (int i = 0; i < GB.size(); ++i)
	{
		// Columns
		for (int j = 0; j < GB[i].size(); ++j)
		{

			// Number of pieces on that tile
			for (int k = 0; k < GB[i][j]->ent.size(); ++k)
			{
				// For the column of queen ants, check to see if there is a bee
				if (j == 0 && GB[i][j]->ent[k]->get_name().compare("bee") == 0){
					bees_on_queen++;
				}
				// If there is any bee found
				if(GB[i][j]->ent[k]->get_name().compare("bee") == 0){
					num_bees++;
				}

			}
		}
	}
	if (bees_on_queen != 0 || num_bees == 0){
		return false;
	}

	// If bees are found and there are no bees on the queens
	return true;
}

// Done
bool bee_win(vector<vector<Tile*>> GB){
	/*********************************************************************
	** Function: Bee win
	** Description: Checks to see if a bee is on the first column
	** Parameters:
	** Pre-Conditions:
	** Post-Conditions:
	*********************************************************************/
	for (int i = 0; i < GB.size(); ++i)
	{
		if(GB[i][0]->ent.size() != 0 && GB[i][0]->ent[0]->get_name().compare("bee") == 0){
			return true;
		}
	}
	return false;
}

// Done
int get_positive_int(int min, int limit){
	/*********************************************************************
	** Function: Get positive int
	** Description: Inclusively gets an integer between min and limit
	** Parameters: Lower limit, higher limit
	** Pre-Conditions: None
	** Post-Conditions: Returns an inclusive integer
	*********************************************************************/
	// Gets a integer greater than 0
	string line;
	while(1){
		getline(cin, line);
		if(validint(line) && (stoi(line) >= min && stoi(line) <= limit)){
			return stoi(line);
			break;
		}
		else{
			cout << "Please enter a positive integer at least " << min;
			if(limit != 999){
				cout << " and less than " << limit + 1 << ": ";
			}
			else{
				cout << ": ";
			}
		}
	}

	// Never gets executed
	return 0;
}

// Done
void display_board(vector<vector<Tile*>> GB){
	/*********************************************************************
	** Function: Display board
	** Description: Displays the game board
	** Parameters: The board
	** Pre-Conditions: Defined
	** Post-Conditions: Prints out the state of the board
	*********************************************************************/
	// First display numbers of columns on top of each square
	// For the board i want to first draw the top bounds of each box
	// Then after the bounds i need to place a wall and

	//Parse through looking for the most number of pieces//
	int max_size = 0, cell_space = 15;
	print_col_names(GB[0].size(), cell_space);
	// Rows
	for (int i = 0; i < GB.size(); ++i)
	{
		// Columns
		for (int j = 0; j < GB[i].size(); ++j)
		{
			// Elements
			// Save the highest number encountered
			if(max_size < GB[i][j]->ent.size()){
				max_size = GB[i][j]->ent.size();
			}
		}
		print_top_header(GB[i].size(), cell_space);
		print_tiles(GB[i], max_size, cell_space);

		// Print out vertical spacers //
		for (int j = 0; j < 4 - max_size; ++j)
		{
			for (int k = 0; k < GB[i].size(); ++k)
			{
				cout << "| ";
				standard_spacing("", 0, cell_space);
				cout << "|";
			}
			cout << endl;
		}
	}
	print_top_header(GB[0].size(), cell_space);
}

// Done
void print_col_names(int col, int spaces){
	/*********************************************************************
	** Function: Print column names
	** Description: Prints the column labels
	** Parameters: Number of columns and spacing
	** Pre-Conditions: None
	** Post-Conditions: Prints labels
	*********************************************************************/
	cout << "  ";
	cout << "Queen Ants";
	standard_spacing("Queen A", 0, spaces);
	cout << " ";
	// Now I am right after the spacers
	for (int i = 1; i < col - 1; ++i)
	{
		cout << " ";
		for (int j = 0; j < spaces / 2; ++j)
		{
			cout << " ";
		}
		cout << i;
		for (int j = 0; j < spaces / 2; ++j)
		{
			cout << " ";
		}
		if((spaces / 2) * 2 < spaces){
			cout << " ";
		}
		cout << " ";
	}
	cout << " ";
	cout << "Beehives";
	standard_spacing("Beehive", 0, spaces);
	cout << endl;
}

// Done
void print_top_header(int col, int spaces){
	/*********************************************************************
	** Function: Print top header
	** Description: Prints the top header for the board
	** Parameters: Number of columns and the standard spaces
	** Pre-Conditions: None
	** Post-Conditions: Prints a nice header
	*********************************************************************/
	for (int i = 0; i < col; ++i)
	{
		cout << "+-";
		for (int j = 0; j < spaces; ++j)
		{
			cout << "-";
		}
		cout << "+";
	}
	cout << endl;
}

// Done
void standard_spacing(string name, int armor, int spaces){
	/*********************************************************************
	** Function: Standard spacing
	** Description: Prints enough spaces to neatly draw the cells
	** Parameters: The name of the object being printed earlier and the armor
	** Pre-Conditions: All are defined
	** Post-Conditions: Prints a nice amount of spaces to make a neat cell
	*********************************************************************/
	if (name.size() > 0)
	{
		spaces = spaces - 2 - name.size() - to_string(armor).size();
	}

	for (int i = 0; i < spaces; ++i)
	{
		cout << " ";
	}
}

// Done
void print_tiles(vector<Tile*> GB, int max_size, int spaces){
	/*********************************************************************
	** Function: Print tiles
	** Description: Prints the cells with names of objects in them with proper
	*  spacing. Accounts for more than 3 objects on a tile by expanding that
	*  row vertically
	** Parameters: Game board and the highest number of pieces on the row of tiles
	** Pre-Conditions: All are defined
	** Post-Conditions: Prints the pieces
	*********************************************************************/
	//Prints the cells//
	int place = 0;
	// Rows
	// for (int i = 0; i < GB.size(); ++i)
	// {
		for (int q = 0; q < max_size; ++q)
		{

			// Columns
			for (int j = 0; j < GB.size(); ++j)
			{

				// Elements

				// If we have at least 1 element, print it
				// For this, I want to print the ant first if its there
				// Then i want to print the bees on it after.
				if (GB[j]->ent.size() > place){
					cout << "| " << GB[j]->ent[place]->get_name() << ": " << GB[j]->ent[place]->get_armor();
					standard_spacing(GB[j]->ent[place]->get_name(), GB[j]->ent[place]->get_armor(), spaces);
					cout << "|";
				}
				// If no elements, print a regular space
				else {//(GB[i][j]->ent.size() == 0){
					cout << "| ";
					standard_spacing("", 0, spaces);
					cout << "|";
				}
			}
			place++;
			cout << endl;
		}
	// }
}

// Done
void print_ant_types(){
	/*********************************************************************
	** Function: Print and types
	** Description: Prints the table of available ants
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: None
	*********************************************************************/
	cout << "What kind of ant do you want to add?" << endl;
	cout << "Food Stored: " << Ant::food << endl;
	cout << "1. Harvester    : 2 Food : 1 Armor : Makes one food per turn" << endl;
	cout << "2. Fire         : 4 Food : 1 Armor : Violently detonates when a Bee is on it" << endl;
	cout << "3. Thrower      : 3 Food : 1 Armor : Shoots a 1 dmg leaf at the closest bee" << endl;
	cout << "4. Snow Thrower : 3 Food : 1 Armor : Shoots a 1 dmg frozen leaf at the closest bee" << endl;
	cout << "5. Hungry Ant   : 4 Food : 1 Armor : Eats a bee in front of it, recharges for 2 turns" << endl;
	cout << "6. Wall         : 4 Food : 4 Armor : Blocks bees" << endl;
	cout << "7. Ninja        : 6 Food : 1 Armor : Sits behind the bees, stabbing them each turn" << endl;
	cout << "8. Bodyguard    : 4 Food : 2 Armor : Can be placed on an ant. Protects that ant" << endl;
	cout << "9. End Turn" << endl;
	cout << "What would you like to place: ";
}
// Done
bool play_again(){
	/*********************************************************************
	** Function: Play again
	** Description: Ask if the user wants to play again
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Returns true or false
	*********************************************************************/
	cout << "Would you like to play again? 0-no 1-yes" << endl;
	cout << ": ";
	int answer = get_positive_int(0, 1);
	switch(answer){
		case 0: return false;
		case 1: return true;
	}
	return false;
}


/*********************************************************************
	** Function:
	** Description:
	** Parameters:
	** Pre-Conditions:
	** Post-Conditions:
	*********************************************************************/