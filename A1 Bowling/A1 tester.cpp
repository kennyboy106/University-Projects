#include <iostream>
#include <string>
#include <time.h>

using namespace std;
void getplayers(int* i);
bool validint(string i);
string*** create3Dstrarr(int x, int y, int z);
int** create2Dintarr(int x, int y);
void delete3Darr(string ***a, int x, int y);
void delete2Darr(int ** a, int x);
void turn(string*** score, int** total, int i, int frame, int players);
void calctotal(string*** score, int** total, int players, int frame);
void printscore(string*** score, int** total, int players, int frame);
int scoreinterp(int knocked, int up, int j);
void basicscore(string*** score, int** total, int players, int frame);
void spacing(int total, int* sum);

/******************************************************
** Program: Bowling.cpp
** Author: Kenneth Tang
** Date: 03/30/2022
** Description: A game of bowling with x many players
** Input: Number of players and enter a whole bunch
** Output: The game and score of bowling.
** Extra Credit: Arrays are dynamically created during runtime.
*  No leaks when checked with valgrind
******************************************************/


int main(){
	srand(time(NULL));
	int players = 0;
	getplayers(&players);

	int** total = create2Dintarr(players, 10);
	string*** score = create3Dstrarr(players, 10, 2);

	for(int i = 0; i < 10; i++){ //ten frames
		for(int j = 0; j < players; j++){ //turn per player per frame
			turn(score, total, j, i, players);
		}
	}
	cout << "\n\nFinal Score!" << endl;
	calctotal(score, total, players, 10);
	printscore(score, total, players, 10);

	delete3Darr(score, players, 10);
	delete2Darr(total, players);
}

void getplayers(int* i){
	/*********************************************************************
	** Function: Gets players
	** Description: Gets a positive integer for number of players
	** Parameters: an integer address
	** Pre-Conditions: None
	** Post-Conditions: Returns true or false based on integer
	*********************************************************************/
	cout << "Enter the number of players: " << endl;
	string str;
	while(1){
		getline(cin, str);
		if(validint(str) && stoi(str) > 0){
			*i = stoi(str);
			break;
		}
		else{
			cout << "Enter a valid number of players: ";
		}
	}
}

bool validint(string i){
	/*********************************************************************
	** Function: Valid integer
	** Description: Checks to see if string is a valid integer. Doesn't accept doubles
	** Parameters: String
	** Pre-Conditions: string is defined
	** Post-Conditions: returns true or false
	*********************************************************************/
	if(i.length() != 0){						//make sure string contains something
		for(int j = 0; j < i.length(); j++){
			if(!isdigit(i[j])){
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

string*** create3Dstrarr(int x, int y, int z){
	/*********************************************************************
	** Function:Create 3D string array
	** Description: Creates a 3D array in memory
	** Parameters: The size of the array
	** Pre-Conditions: None
	** Post-Conditions: Returns address to the start of array
	*********************************************************************/
	string*** a = new string**[x]; //Create an array that will carry double pointers.

	for(int i = 0; i < x; i++){
		//Here we set the elements in our array to hold pointers to regular arrays
		a[i] = new string*[y];

		for(int j = 0; j < y; j++){
			//Here we finally set each of the second level arrays to its own array
			a[i][j] = new string[z];
		}
	}
	return a; //return the double pointer (points to start of master array)
}

int** create2Dintarr(int x, int y){
	/*********************************************************************
	** Function: Create 2D integer array
	** Description: Creates a 2D array in memory
	** Parameters: The size of the array
	** Pre-Conditions: None
	** Post-Conditions: Returns address to the start of array
	*********************************************************************/
	//Create array holding arrays
	int** a = new int*[x];

	//assign elements of first array with more arrays
	for(int j = 0; j < x; j++){
		a[j] = new int[y];
	}

	//Initialize the array to 0;
	for(int i = 0; i < x; i++){
		for(int j = 0; j < y; j++){
			a[i][j] = 0;
		}
	}

	return a; //return address of 2D array.
}

void delete3Darr(string ***a, int x, int y){
	/*********************************************************************
	** Function: Delete 3D array
	** Description: Frees memory of a 3D string array
	** Parameters: the number of arrays and the rows in each array.
	*  Column number not needed
	** Pre-Conditions: None
	** Post-Conditions: Deletes array
	*********************************************************************/
	for(int i = 0; i < x; i++){
		for(int j = 0; j < y; j++){
			delete [] a[i][j];
		}
		delete [] a[i];
	}
	delete [] a;
}

void delete2Darr(int** a, int x){
	/*********************************************************************
	** Function: Delete 2D array
	** Description: Free memory of a 2D integer array
	** Parameters: The number of rows in array. Column number not needed
	** Pre-Conditions: None
	** Post-Conditions: Deletes array
	*********************************************************************/
	for(int i = 0; i < x; i++){
		delete [] a[i];
	}
	delete [] a;
}

void turn(string*** score, int** total, int pnum, int frame, int players){
	/*********************************************************************
	** Function: Turn
	** Description: Takes the player through their individual turn
	** Parameters: Needs the scoreboard, the player number, and the frame
	** Pre-Conditions: All variables are defined to be something
	** Post-Conditions: Changes score and total for each turn
	** **Why over 15 lines?
	**	Because a lot needs to happen in a turn and adding a function to
	**	print 2 lines or to make scoreinterp do the entire switch case will
	**	stretch the number of parameters even more which is confusing to read
	*********************************************************************/
	int runningpins = 10;
	int pinsknocked = 0;
	for(int j = 0; j < 2; j++){

		cout << "Frame: " << frame + 1 << endl;
		cout << "Player " << pnum + 1 << ", press enter to roll.";
		string str;
		getline(cin, str); //Make user press enter, discard input and proceed

		pinsknocked = rand() % (1 + runningpins);
		runningpins -= pinsknocked;
		//When repeated, this will roll between 0 and the number of pins left
		switch(scoreinterp(pinsknocked, runningpins, j)){
			case 1: score[pnum][frame][0] = "X";
					score[pnum][frame][1] = " ";
					j++;
					break;
			case 2: score[pnum][frame][1] = "-";
					break;
			case 3: score[pnum][frame][j] = to_string(pinsknocked);
					break;
		}
		calctotal(score, total, players, frame);
		printscore(score, total, players, frame);
	}
}

int scoreinterp(int knocked, int up, int j){
	/*********************************************************************
	** Function:Score interpret
	** Description: Interprets the score and returns 1-3 for the respective
	*  score
	** Parameters: Pins knocked down, pins still up, and the turn in the frame
	** Pre-Conditions: none
	** Post-Conditions: Returns an integer. 1 for strike. 2 for spare. 3 for
	*  regular
	*********************************************************************/
	if(knocked == 10 && j == 0){
		cout << "Strike! All pins knocked down" << endl;
		return 1;
	}
	else if(up == 0){
		cout << knocked << " knocked down. Spare!" << endl;
		return 2;
	}
	else{
		cout << knocked << " Pins knocked down, nice" << endl;
		return 3;
	}
}

void calctotal(string*** score, int** total, int players, int frame){
	/*********************************************************************
	** Function: Calculate total
	** Description: Uses score to calculate what total should be
	** Parameters: 3D array, 2D array, int players, int frame
	** Pre-Conditions: None
	** Post-Conditions: Changes total with respect to special scoring
	** **Why more than 15 lines?
	** 	Well, if I make the if strike, spare, or normal into its own function
	** 	then I'll have calctotal be only 2-5 lines so what is the point?
	*********************************************************************/
	basicscore(score, total, players, frame); //reset the board. Make calculations easy
	for(int i = 0; i < players; i++){
		for(int j = 0; j < frame; j++){


			if(score[i][j][0] == "X"){	//If its a strike
				if(j < 8){
					total[i][j] = 10 + total[i][j+1] + total[i][j+2];
				}
				else if(j < 9){
					total[i][j] = 10 + total[i][j+1];
				}
				else{
					total[i][j] = 10;
				}
			}
			else if(score[i][j][1] == "-"){	//If its a spare
				if(j < 9){
					total[i][j] = 10 + total[i][j+1];
					// cout << "Here";
				}
				else{
					total[i][j] = 10;
				}
			}
			else{	//If its a normal throw
				total[i][j] = stoi(score[i][j][0]) + stoi(score[i][j][1]);
			}

		}
	}
}

void basicscore(string*** score, int** total, int players, int frame){
	/*********************************************************************
	** Function: Basic Score
	** Description: Changes total to what the basic interpretation of scoring is
	*  i.e. no strike bonuses and no spare bonuses, just 10 or number of pins
	** Parameters: scores, total, players, current frame
	** Pre-Conditions: All are defined
	** Post-Conditions: Changes total to a basic scoreboard with no bonuses,
	*  either 10 or number of pins
	*********************************************************************/
	for(int i = 0; i < players; i++){
		for(int j = 0; j < frame; j++){
			if(score[i][j][0] == "X" || score[i][j][1] == "-"){
				total[i][j] = 10;
			}
			else{
				total[i][j] = stoi(score[i][j][0]) + stoi(score[i][j][1]);

			}
		}
	}
}

void printscore(string*** score, int** total, int players, int frame){
	/*********************************************************************
	** Function: Print scoreboard
	** Description: Prints the current scoreboard for all players
	** Parameters: the score, totals for each frame, number of players, the current frame
	** Pre-Conditions: All are defined
	** Post-Conditions: None, only prints
	*  **This is 16 lines, what? you want a function that does 2 lines?
	*********************************************************************/
	cout << "\nName\t |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10  | Total" << endl;
	for(int i = 0; i < players; i++){
		cout << "----------------------------------------------------------------------------------" << endl;
		cout << "Player" << i + 1 << "    ";
		//prints up to player score board


		for(int j = 0; j < 10; j++){
			for(int k = 0; k < 2; k++){
				cout << score[i][j][k] << " ";
			}
			cout << "  ";
		}

		cout << endl << "\t     "; //Set us up for printing the first total

		int sum = 0;
		for(int j = 0; j < frame; j++){
			spacing((int) total[i][j], &sum);
		}

		/* Before displaying the sum, we need to align it to the correct place
		 * in the board so we first add 62 spaces, then subtract 6 for each frame
		*/
		for(int j = 0; j < 62 - (6 * (frame)); j++)
			cout << " ";

		cout << sum << endl;
	}
	cout << endl;
}

void spacing(int total, int* sum){
	/*********************************************************************
	** Function: Spacing
	** Description: Takes some lines away from print scoreboard for that grade
	** Parameters: the integer of total at whatever frame and the sum from
	** printscore
	** Pre-Conditions: None
	** Post-Conditions: Adds total to sum and prints some spaces to align
	** everything correctly
	*********************************************************************/
	cout << total;
	*sum += total;
	if(total < 10){
		cout << "     ";  //print 5 spaces
	}
	else{
		cout << "    ";	 	  //print 4 spaces
	}
}

/*********************************************************************
	** Function:
	** Description:
	** Parameters:
	** Pre-Conditions:
	** Post-Conditions:
	*********************************************************************/