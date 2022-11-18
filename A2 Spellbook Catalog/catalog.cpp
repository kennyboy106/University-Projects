#include "catalog.h"



//Done
void openfiles(char** argv, int argc, ifstream *users, ifstream *spellbook){
	/*********************************************************************
	** Function: Open Files
	** Description: Opens the two text files from terminal when running program
	** Parameters: The char pointer to the strings of the arguments, number of
	*  arguments, two file objects
	** Pre-Conditions: File names are included when program is started
	** Post-Conditions: Opens the files for use
	*********************************************************************/
	if(argc != 3){	//Exit the program if not correct number of arguments
		cout << "Enter the two required text files when running the program" << endl;
		exit(EXIT_FAILURE);
	}
	users->open(argv[1]);
	spellbook->open(argv[2]);
	if(!(users->is_open() || spellbook->is_open())){
		cout << "Failed to open text files" << endl;
		exit(EXIT_FAILURE);
	}
	else if(users->peek() == ifstream::traits_type::eof() || spellbook->peek() == ifstream::traits_type::eof()){
		cout << "Files open but one or more are empty" << endl;
		exit(EXIT_FAILURE);
	}
	else{
		cout << "Files open" << endl;																	//TEST FLAG//
	}
}

//Done
wizard* wizard_create_array(ifstream *users, int* number){
	/*********************************************************************
	** Function: Create wizard array
	** Description: Performs all the functions to create and populate an array
	*  of wizards with information from the users file
	** Parameters: Address of file object, address of number
	** Pre-Conditions: File is open and in correct format
	** Post-Conditions: Creates and populates a dynamic array of wizards
	*********************************************************************/
	string num_wizards;
	getline(*users, num_wizards);
	if(validint(num_wizards)){ 								//Check if the first line is an integer
		*number = stoi(num_wizards);						//save the number of wizards to main
		wizard* arr = new wizard[stoi(num_wizards)];		//create array of wizards
		wizard_populate(&users, arr, stoi(num_wizards));	//Fill it up
		return arr;											//Give it back to main
	}
	else{
		cout << "Number of wizards not at top of file. Program exit" << endl;
		exit(EXIT_FAILURE);
	}
}

//Done
void wizard_populate(ifstream **users, wizard* arr, int num_wizards){
	/*********************************************************************
	** Function: Populate from wiz (file)
	** Description: Copies data from wizard text file
	** Parameters: the address of file object, array, and number of wizards
	** Pre-Conditions: File object is open and in a specific format
	** Post-Conditions: Fills arr with information from the file
	*********************************************************************/
	for(int i = 0; i < num_wizards; i++){
		//De-reference to get to obj, then read from it
		**users >> arr[i].name >> arr[i].id >> arr[i].password >> arr[i].position_title >> arr[i].beard_length;
	}
}

//Done
wizard* wizard_login(ifstream *file_users, int* num_wizards){
	/*********************************************************************
	** Function: Login
	** Description: Takes the user through logging in and verifies status
	*  (student or teacher). Also returns the information of the user logged in
	** Parameters: file object and number of wizards in file
	** Pre-Conditions: File object is open
	** Post-Conditions: Returns the information of the user
	* *Why over 15 lines? I tried to compact this down without creating functions
	*  that take in all of the variables created in this function. Most of the
	*  lines are from if or for statements. The total lines for this function
	*  are 19, only 4 above the general limit.
	*********************************************************************/
	wizard* wizinfo = wizard_create_array(file_users, num_wizards);
	wizard* user = new wizard;
	string password, id;
	int loop = 0, tries = 0;
	while(loop == 0){
		cout << "Please enter your id: ";
		getline(cin, id);
		cout << "Please enter your password: ";
		getline(cin, password);


		//Check if id is a number
		if(validint(id)){
			for(int i = 0; i < *num_wizards && loop == 0; i++){
				//try to match it with existing id and pass
				if(stoi(id) == wizinfo[i].id && password.compare(wizinfo[i].password) == 0){
					//reassign a struct wiz variable to all elements of logging in user
					wizard_set_and_print(user, wizinfo, i);
					loop++;

				}
			}
			//If nothing matches then increment and check number of tries
			if(loop == 0){
				login_cap(&tries);
			}
		}
		else{
			cout << "Incorrect id or password" << endl;
		}

	}
	return user;
}

//Done
void login_cap(int* tries){
	/*********************************************************************
	** Function: Login Cap
	** Description: Counts and exits if too many attempts
	** Parameters: Number of attempts
	** Pre-Conditions: None
	** Post-Conditions: Can exit program or increment tries
	*********************************************************************/
	if(*tries >= 2){
		cout << "Too many attempts. Program exit." << endl;
		exit(EXIT_FAILURE);
	}
	else{
		cout << "Incorrect id or password" << endl;
		(*tries)++;
	}
}
//Done
void wizard_set_and_print(wizard* user, wizard* wizinfo, int i){
	/*********************************************************************
	** Function: Set and print user
	** Description: Prints the login data and then sets user to all of the info
	*  of wizinfo before wizinfo is deleted
	** Parameters: User and wizinfo to be copied
	** Pre-Conditions: wizinfo is populated at the targeted place, i
	** Post-Conditions: Deletes wizinfo and copies to new wizard struct, user.
	*********************************************************************/
	user->name = wizinfo[i].name;
	user->id = wizinfo[i].id;
	user->password = wizinfo[i].password;
	user->position_title = wizinfo[i].position_title;
	user->beard_length = wizinfo[i].beard_length;

	cout << "\nWelcome " << wizinfo[i].name << endl;
	cout << "ID: " << wizinfo[i].id << endl;
	cout << "Status: " << wizinfo[i].position_title << endl;
	cout << "Beard Length: " << wizinfo[i].beard_length << endl;
	delete [] wizinfo;
	wizinfo = NULL;
}






//Done
spellbook* create_spellbooks(int num_spell_books){
	/*********************************************************************
	** Function: Create spell books
	** Description: Creates a dynamic array of spellbooks
	** Parameters: Number of books
	** Pre-Conditions: None
	** Post-Conditions: Returns the address to the start of dynamic array
	*********************************************************************/
	return new spellbook[num_spell_books];
}

//Done
void populate_spellbook_data(spellbook* sb, int num_spell_books, ifstream &spellbook){
	/*********************************************************************
	** Function: Populate Spell book data
	** Description: Copies all information after the first line of a text file
	*  Text file must be in specific format
	** Parameters: The array of structs, number of spell books, and the file
	** Pre-Conditions: Text file is open and array has been allocated
	** Post-Conditions: Fills array with data from the text file
	*********************************************************************/
	for(int i = 0; i < num_spell_books; i++){
		spellbook >> sb[i].title >> sb[i].author >> sb[i].num_pages >> sb[i].edition >> sb[i].num_spells;
		sb[i].s = create_spells(sb[i].num_spells);
		//Create an array of spells for the number of spells

		for(int j = 0; j < sb[i].num_spells; j++){
			//for each elements of the array of spells, read in the spell data
			populate_spell_data(sb[i].s, j, spellbook);
			// spellbook >> sb[i].s[j].name >> sb[i].s[j].success_rate >> sb[i].s[j].effect;
		}
	}
}

//Done
spell* create_spells(int num_spells){
	/*********************************************************************
	** Function: Create spells
	** Description: Creates a dynamic array sized to the number of spells in a book
	** Parameters: number of spells
	** Pre-Conditions: none
	** Post-Conditions: Returns address to a dynamic array
	*********************************************************************/
	return new spell[num_spells];
}

//Done
void populate_spell_data(spell* sp, int j, ifstream &spellbook){
	/*********************************************************************
	** Function: Populate spell data
	** Description: Required function to hold the line that reads in spell data
	*  from spellbook
	** Parameters: Array of spells, int for its place, file object
	** Pre-Conditions: All are defined
	** Post-Conditions: Copies info from file object to spell array and moves
	*  cursor along with it
	*********************************************************************/
	spellbook >> sp[j].name >> sp[j].success_rate >> sp[j].effect;
}




//Done
void spell_effect_sort(spell* sb, int num_total_spells){
	/*********************************************************************
	** Function: Spell effect sort
	** Description: sorts based on first char of effect name.
	** Parameters: spell array and total number of spells
	** Pre-Conditions: All are defined
	** Post-Conditions: Sorts the spells based on effect in alphabetical order
	*********************************************************************/
	int sort = 1;
	while(sort){
		sort = 0;
		for(int i = 1; i < num_total_spells; i++){
			char a = sb[i].effect[0], b = sb[i - 1].effect[0];
			if(int(a) < int(b)){
				spell temp = sb[i];
				sb[i] = sb[i - 1];
				sb[i - 1] = temp;
				sort = 1;
			}
		}
		num_total_spells--;
	}
}
//Done
spell* spell_combine(spellbook* sb, int* num_spell_books){
	/*********************************************************************
	** Function: Spell book spell combine
	** Description: Combines all spells within all spell books to a single
	*  spell array
	** Parameters: Spellbook array, number of spell books
	** Pre-Conditions: All are defined
	** Post-Conditions: Returns an array of all spells
	*********************************************************************/
	//Get total number of spells in all books
	int num_total_spells = 0, spellassign = 0;
	for(int i = 0; i < *num_spell_books; i++){
		num_total_spells += sb[i].num_spells;
	}
	//Combine all spells into one spell array
	spell* spellarr = new spell[num_total_spells];
	for(int i = 0; i < *num_spell_books; i++){
		for(int j = 0; j < sb[i].num_spells; j++){
			spellarr[spellassign].name = sb[i].s[j].name;
			spellarr[spellassign].effect = sb[i].s[j].effect;
			spellassign++;
		}
	}
	*num_spell_books = num_total_spells;
	return spellarr;
}





//Done
void menu_options(spellbook* spellinfo, wizard* wizinfo, int num_spell_books){
	/*********************************************************************
	** Function: Menu Options
	** Description: Prints out the options and allows the user to select the different
	*  sorting operations.
	** Parameters: Spellbooks, wizard information, number of spell books
	** Pre-Conditions: All are defined and populated
	** Post-Conditions: Prints to console or to file
	*  16 Lines, I needed to fit in one more line. I think this is better than
	*  if I were to put the entire switch statement into its own function. This
	*  way, the user can still see whats happening and its pretty straightforward
	*********************************************************************/
	int loop = 1;
	while(loop == 1){
		menu_print_options();
		string input;
		getline(cin, input);
		if(validint(input) && !(stoi(input) < 1 || stoi(input) > 4)){
			switch(stoi(input)){
				case 1: menu_spellbook_page_option(spellinfo, wizinfo, num_spell_books);
						//sort spell books by number of pages
						break;
				case 2: menu_spellbook_effect_option(spellinfo, wizinfo, num_spell_books);
						//group spells by their effect
						break;
				case 3: menu_spellbook_success_rate_option(spellinfo, wizinfo, num_spell_books);
						//sort spell books by average success rate
						break;
				case 4: loop++;
			}
		}
		else if(!validint(input) || (stoi(input) < 1 || stoi(input) > 4)){
			cout << "Please enter a number between 1-4";
		}
	}
}

//Done
void menu_spellbook_page_option(spellbook* sb, wizard* wizinfo, int num_spell_books){
	/*********************************************************************
	** Function: Menu Spell book page
	** Description: This is the function that is called from the menu when
	*  the user wishes to sort by number of pages. This function will censor
	*  books from output if student is using it and will clean its own memory
	*  after it is done
	** Parameters: Spell book array, user info, number of spell books
	** Pre-Conditions: All are defined
	** Post-Conditions: Prints to console
	*********************************************************************/
	spellbook* sb_cpy; //New dynamic memory allocated
	if(wizinfo->position_title == "Student"){
		sb_cpy = spellbook_copy_page_censor(sb, num_spell_books);
	}
	else{
		sb_cpy = spellbook_copy_page(sb, num_spell_books);
	}

	spellbook_page_sort(sb_cpy, num_spell_books);

	menu_options_print_sorted_spellbook(sb_cpy, num_spell_books);
	delete_spellbook_info(sb_cpy, num_spell_books);
}

//Done
void menu_spellbook_effect_option(spellbook* sb, wizard* wizinfo, int num_spell_books){
	/*********************************************************************
	** Function: menu spellbook effect option
	** Description: Calls all functions for sorting based on effect
	** Parameters: Spellbook array, user info, and number of spell books
	** Pre-Conditions: All are defined
	** Post-Conditions: Prints sorted spells to console or file
	*********************************************************************/
	//Copy spells of each book over to a copy array
	spellbook* sb_cpy;
	if(wizinfo->position_title.compare("Student") == 0){
		sb_cpy = spellbook_copy_effect_censor(sb, num_spell_books);
	}
	else{
		sb_cpy = spellbook_copy_effect(sb, num_spell_books);
	}
	//Copy all spells from each book to one nice spell array
	int num_total_spells = num_spell_books;
	spell* spellarr = spell_combine(sb_cpy, &num_total_spells);


	//sort based on first char, in alphabetical order
	spell_effect_sort(spellarr, num_total_spells);
	//Print out sorted spells
	menu_options_print_sorted_spells(spellarr, num_total_spells);
	//delete spellbook and spells within
	delete_sorted_spells(sb_cpy, spellarr, num_spell_books);
}

//Done
void menu_spellbook_success_rate_option(spellbook* sb, wizard* wizinfo, int num_spell_books){
	/*********************************************************************
	** Function: Menu spellbook success rate option
	** Description: Calls all the functions needed to perform a sort based on
	*  success rate.
	** Parameters: The spellbook, user info, and number of spells
	** Pre-Conditions: All are populated and initialized
	** Post-Conditions:
	*********************************************************************/

	//Create a copy, censored or not
	spellbook* sb_cpy;
	if(wizinfo->position_title.compare("Student") == 0){
		sb_cpy = spellbook_copy_page_censor(sb, num_spell_books);
	}
	else{
		sb_cpy = spellbook_copy_page(sb, num_spell_books);
	}

	//Assign the values of average success based on spells in book
	menu_spellbook_success_assign(sb_cpy, num_spell_books);
	//Sort them based on success rate
	menu_spellbook_success_rate_sort(sb_cpy, num_spell_books);

	menu_options_print_sorted_success(sb_cpy, num_spell_books);
	delete_spellbook_info(sb_cpy, num_spell_books);
}

//Done
void menu_spellbook_success_assign(spellbook* sb, int num_spell_books){
	/*********************************************************************
	** Function: Menu spellbook success rate assign
	** Description: Assigns the average success rate for each book
	** Parameters: Spellbooks, number of spellbooks
	** Pre-Conditions: All are defined
	** Post-Conditions: Assigns a float to the avg_success_rate of each book
	*********************************************************************/
	for(int i = 0; i < num_spell_books; i++){
		float total_success = 0;
		for(int j = 0; j < sb[i].num_spells; j++){
			total_success += float (sb[i].s[j].success_rate);
		}
		sb[i].avg_success_rate = total_success / sb[i].num_spells;
	}
}

//Done
void menu_spellbook_success_rate_sort(spellbook* sb, int num_spell_books){
	/*********************************************************************
	** Function: menu spellbook success rate sort
	** Description: Sorts based on success rate, highest to lowest
	** Parameters: spellbooks and number of spellbooks
	** Pre-Conditions: All are initialized and defined
	** Post-Conditions: Changes order of spellbooks in array based on success
	*  rate
	*********************************************************************/
	int sort = 1;
	while(sort == 1){
		sort = 0;
		for(int i = 1; i < num_spell_books; i++){
			if(sb[i].avg_success_rate > sb[i - 1].avg_success_rate){
				spellbook temp = sb[i - 1];
				sb[i - 1] = sb[i];
				sb[i] = temp;
				sort = 1;
			}
		}
		num_spell_books--;
	}
}

//Done
void spellbook_page_sort(spellbook* sb, int num_spell_books){
	/*********************************************************************
	** Function: Spell book page sort
	** Description: Sorts the books in the array based on page number. Lowest
	*  to highest
	** Parameters: Spell book array and number of elements in it
	** Pre-Conditions: Array is populated and defined
	** Post-Conditions: Sorts elements based on number of pages
	*********************************************************************/
	int s = 1;
	while(s){
		s = 0;
		for(int i = 1; i < num_spell_books; i++){
			if(sb[i].num_pages < sb[i - 1].num_pages){
				spellbook temp = sb[i];
				sb[i] = sb[i - 1];
				sb[i - 1] = temp;
				s = 1;
			}
		}
		num_spell_books--;
	}
}

//Done
void spellbook_copy_basic(spellbook* sb_cpy, int ba, spellbook* sb, int j){
	/*********************************************************************
	** Function: Spell book copy basic
	** Description: Nothing fancy, just copies the entirety of spell book, sb, to
	*  sb_cpy. The parameters are for different positions in the array if it is
	*  being censored or not. If not, both ints should be entered as the same
	** Parameters: spell books and locations inside the arrays of them
	** Pre-Conditions: They are defined and the ints are within bounds
	** Post-Conditions: Copies sb to sb_cpy with the spells
	*********************************************************************/
	//Here i have both books,
	sb_cpy[ba].title = sb[j].title;
	sb_cpy[ba].author = sb[j].author;
	sb_cpy[ba].num_pages = sb[j].num_pages;
	sb_cpy[ba].edition = sb[j].edition;
	sb_cpy[ba].num_spells = sb[j].num_spells;

	//Copy the spells over
	sb_cpy[ba].s = new spell[sb[j].num_spells];
	for(int i = 0; i < sb[j].num_spells; i++){
		sb_cpy[ba].s[i].name = sb[j].s[i].name;
		sb_cpy[ba].s[i].effect = sb[j].s[i].effect;
		sb_cpy[ba].s[i].success_rate = sb[j].s[i].success_rate;
	}
}

//Done
spellbook* spellbook_copy_page(spellbook* sb, int num_spell_books){
	/*********************************************************************
	** Function: Spell book copy
	** Description: Simply copies title and number of pages to another array
	*  of spell books
	** Parameters: the target array of spell books and number of books in it
	** Pre-Conditions: Target array is populated
	** Post-Conditions: Returns the copy
	*********************************************************************/

	spellbook* sb_cpy = new spellbook[num_spell_books];

	for(int i = 0; i < num_spell_books; i++){
		spellbook_copy_basic(sb_cpy, i, sb, i);
	}

	return sb_cpy;
}

//Done
spellbook* spellbook_copy_page_censor(spellbook* sb, int &num_spell_books){
	/*********************************************************************
	** Function: Spell book copy and censor
	** Description: Takes the array of spell books and trims it down to those
	*  appropriate for students
	** Parameters: Spell books and address of number of spells
	** Pre-Conditions: Spell books are populated
	** Post-Conditions: Returns a censored array of spell books
	*********************************************************************/
	spellbook *sb_cpy = new spellbook[spellbook_number_censored(sb, num_spell_books)];
	int book_assign = 0, badspell = 0;
	for(int i = 0; i < num_spell_books; i++){
		//Reset flag
		badspell = 0;

		//Going through each spell
		for(int j = 0; j < sb[i].num_spells; j++){
			if(sb[i].s[j].effect == "poison" || sb[i].s[j].effect == "death"){
				badspell++;
				break;
			}
		}
		//If flag hasn't been tripped, copy the spell book
		if(badspell == 0){
			spellbook_copy_basic(sb_cpy, book_assign, sb, i);
			book_assign++;
		}
	}
	num_spell_books = book_assign;

	return sb_cpy;
}

//Done
spellbook* spellbook_copy_effect(spellbook* sb, int num_spell_books){
	/*********************************************************************
	** Function: Spell book copy effect
	** Description: Copies all spells and effects in a spell book array
	** Parameters: Spell book array, number of spell books in array
	** Pre-Conditions: Spell book array is defined
	** Post-Conditions: Returns a copy of the array with only spell names &
	*  effects
	*********************************************************************/
	//Create copy array
	spellbook* sb_cpy = new spellbook[num_spell_books];
	for(int i = 0; i < num_spell_books; i++){
		//Create array of spells for each copy spell book
		sb_cpy[i].s = new spell[sb[i].num_spells];
		sb_cpy[i].num_spells = sb[i].num_spells;

		//Copy all spells and names over
		for(int j = 0; j < sb[i].num_spells; j++){
			sb_cpy[i].s[j].name = sb[i].s[j].name;
			sb_cpy[i].s[j].effect = sb[i].s[j].effect;
		}
	}
	//Return copy
	return sb_cpy;
}

//Done
spellbook* spellbook_copy_effect_censor(spellbook* sb, int &num_spell_books){
	/*********************************************************************
	** Function: Spell book copy effects, censored version
	** Description: Copies the effects and names of all spells that a student
	*  has access to
	** Parameters: Spell book array, number of spell books in array.
	** Pre-Conditions: Spell book array is defined
	** Post-Conditions: Returns a spell book array with censored spells
	*********************************************************************/
	spellbook *sb_cpy = new spellbook[num_spell_books];

	for(int i = 0; i < num_spell_books; i++){
		//Copy number of spells over
		sb_cpy[i].num_spells = sb[i].num_spells;

		//Parse through original book for bad spells and modify spells in book
		for(int j = 0; j < sb[i].num_spells; j++){
			//If bad spell found, decrement the number of spells by 1
			if(sb[i].s[j].effect == "poison" || sb[i].s[j].effect == "death"){
				sb_cpy[i].num_spells--;
			}
		}
		//Set new array of number of good spells
		sb_cpy[i].s = new spell[sb_cpy[i].num_spells];

		//As long as a spell doesn't have poison or death, copy it over, else
		//go to the next spell
		int spellassign = 0;
		for(int j = 0; j < sb[i].num_spells; j++){
			if(sb[i].s[j].effect != "poison" && sb[i].s[j].effect != "death"){
				sb_cpy[i].s[spellassign].effect = sb[i].s[j].effect;
				sb_cpy[i].s[spellassign].name = sb[i].s[j].name;
				spellassign++;
			}
		}
	}


	return sb_cpy;
}

//Done
void menu_options_print_sorted_spellbook(spellbook* sb, int num_spell_books){
	/*********************************************************************
	** Function: menu options print sorted spellbook
	** Description: Prints the sorted spell book based on page numbers
	** Parameters: Sorted spell book array, number of spell books
	** Pre-Conditions: All are defined
	** Post-Conditions: Prints to file or to console
	* 	17 lines. I can't compact this down more unless I make functions that do
	* 	2 lines of code. The switch function needs to be custom for each of the
	* 	different sort styles and moving stuff to functions would make reading this
	* 	more cumbersome
	*********************************************************************/
	string input;
	menu_options_print_menu();
	int loop = 0;
	while(loop == 0){
		cout << "Your Choice: ";
		getline(cin, input);
		if(validint(input) && (stoi(input) == 1 || stoi(input) == 2)){
			loop++;
			switch(stoi(input)){
				case 1:
					for(int i = 0; i < num_spell_books; i++){
						cout << sb[i].title << " " << sb[i].num_pages << endl;
					}
					break;
				case 2:
					menu_options_spellbook_print_to_file(sb, num_spell_books, "page_print");
					break;
			}
		}
		else{
			cout << "Please enter a number between 1 and 2" << endl;
		}
	}
}
//Done
void menu_options_print_sorted_spells(spell* sp, int num_total_spells){
	/*********************************************************************
	** Function: menu options print sorted spells
	** Description: Calls functions to print spells to console or to file
	** Parameters: Spell array, number of spells
	** Pre-Conditions: All are defined
	** Post-Conditions: Prints to file or console
	* 	17 lines. I can't compact this down more unless I make functions that do
	* 	2 lines of code. The switch function needs to be custom for each of the
	* 	different sort styles and moving stuff to functions would make reading this
	* 	more cumbersome
	*********************************************************************/
	string input;
	menu_options_print_menu();
	int loop = 0;
	while(loop == 0){
		cout << "Your Choice: ";
		getline(cin, input);
		if(validint(input) && (stoi(input) == 1 || stoi(input) == 2)){
			loop++;
			switch(stoi(input)){
				case 1:
					for(int i = 0; i < num_total_spells; i++){
						cout << sp[i].effect << " " << sp[i].name << endl;
					}
					break;
				case 2:
					menu_options_spells_print_to_file(sp, num_total_spells);
					break;
			}
		}
		else{
			cout << "Please enter a number between 1 and 2" << endl;
		}
	}
}

//Done
void menu_options_print_sorted_success(spellbook* sb, int num_spell_books){
	/*********************************************************************
	** Function: Menu options print sorted success
	** Description: Prints out the spellbooks based on success rate. Prints to
	*  console or file
	** Parameters: Spellbook array and number of spell books
	** Pre-Conditions: All are initialized and defined
	** Post-Conditions: Prints to console or to file
	* 	17 lines. I can't compact this down more unless I make functions that do
	* 	2 lines of code. The switch function needs to be custom for each of the
	* 	different sort styles and moving stuff to functions would make reading this
	* 	more cumbersome
	*********************************************************************/
	string input;
	//Print the menu
	menu_options_print_menu();
	int loop = 0;
	while(loop == 0){
		cout << "Your Choice: ";
		getline(cin, input);
		if(validint(input) && (stoi(input) == 1 || stoi(input) == 2)){
			loop++;
			switch(stoi(input)){
				case 1:
					for(int i = 0; i < num_spell_books; i++){
						cout << sb[i].title << " " << sb[i].avg_success_rate << endl;
					}
					break;
				case 2:
					menu_options_spellbook_print_to_file(sb, num_spell_books, "success_print");
					break;
			}
		}
		else{
			cout << "Please enter a number between 1 and 2" << endl;
		}
	}
}

//Done
void open_output_file(ofstream* file){
	/*********************************************************************
	** Function: Open output file
	** Description: Opens a file for writing to specified by the user. Checks
	*  to make sure the file they want to print to is a text file
	** Parameters: output file object
	** Pre-Conditions: None
	** Post-Conditions: Opens file for use
	*********************************************************************/
	while(1){
		string input;
		cout << "Please provide desired filename: ";
		getline(cin, input);
		if(input.substr(input.length() - 4) == ".txt"){
			(*file).open(input, std::ios::app);
			break;
		}
		else{
			cout << "File name is not a text file" << endl;
		}
	}
}

//Done
void menu_options_spellbook_print_to_file(spellbook* sb, int num_spell_books, string str){
	/*********************************************************************
	** Function: menu options spellbook print to file
	** Description: Prints to file based on page sort or success rate sort
	** Parameters: Spellbook array, number of spell books, options string to
	*  say which thing to print, pages or success rate
	** Pre-Conditions: All are defined
	** Post-Conditions: Prints to the end of a file
	*********************************************************************/
	ofstream file_out;
	open_output_file(&file_out);
	//If sorted with page count
	if(str.compare("page_print") == 0){
		for(int i = 0; i < num_spell_books; i++){
			file_out << sb[i].title << " " << sb[i].num_pages << endl;
		}
	}
	//If sorted with success rate
	if(str.compare("success_print") == 0){
		for(int i = 0; i < num_spell_books; i++){
			file_out << sb[i].title << " " << sb[i].avg_success_rate << endl;
		}
	}


	file_out.close();
}
//Done
void menu_options_spells_print_to_file(spell* sp, int num_total_spells){
	/*********************************************************************
	** Function: menu options spell print to file
	** Description: Prints spells to file. Effect and name
	** Parameters: Spell array and number of spells
	** Pre-Conditions: All are defined
	** Post-Conditions: Prints to end of file
	*********************************************************************/
	ofstream file_out;
	open_output_file(&file_out);
	for(int i = 0; i < num_total_spells; i++){
		file_out << sp[i].effect << " " << sp[i].name << endl;
	}

	file_out.close();
}

//Done
void menu_print_options(){
	/*********************************************************************
	** Function: Menu print options
	** Description: Simply prints menu to console to save space in other function
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: None
	*********************************************************************/
	cout << "\nWhich option would you like to choose?" << endl;
	cout << "1. Sort spellbooks by number of pages" << endl;
	cout << "2. Group spells by their effect" << endl;
	cout << "3. Sort spellbooks by average success rate" << endl;
	cout << "4. Quit" << endl;
	cout << "Your Choice: ";
}

//Done
void menu_options_print_menu(){
	/*********************************************************************
	** Function: Menu options, print menu
	** Description: Prints the print menu to console
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: None
	*********************************************************************/
	cout << "How would you like the information displayed" << endl;
	cout << "1. Print to screen (Press 1)" << endl;
	cout << "2. Print to file   (Press 2)" << endl;
}

//Done
int spellbook_number_censored(spellbook* sb, int num_spell_books){
	/*********************************************************************
	** Function: Spell book function, return number censored
	** Description: Returns the number of books that shouldn't be included
	** Parameters: Spellbook, number of spell books
	** Pre-Conditions: sb is populated
	** Post-Conditions: Returns the number of books that shouldn't be censored
	*********************************************************************/
	int count = num_spell_books;
	for(int i = 0; i < num_spell_books; i++){
		for(int j = 0; j < sb[i].num_spells; j++){
			if((sb[i].s[j].effect.compare("poison") == 0 || sb[i].s[j].effect.compare("death") == 0)){
				count--;
				break;
			}
		}
	}
	return count;
}


//Utility//

//Done
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

//Done
void delete_info(wizard** wizarr, spellbook** sbarr, int num_spell_books){
	/*********************************************************************
	** Function: Delete info
	** Description: Deletes the dynamic arrays used
	** Parameters: the array locations
	** Pre-Conditions: The arrays are at some length or defined
	** Post-Conditions: Frees memory and sets pointers to null
	*********************************************************************/
	delete *wizarr;
	wizarr = NULL;


	for(int i = 0; i < num_spell_books; i++){
		delete [] (*sbarr)[i].s;
		(*sbarr)[i].s = NULL;
	}
	delete [] *sbarr;
	sbarr = NULL;
}

//Done
void delete_spellbook_info(spellbook* sb, int num_spell_books){
	/*********************************************************************
	** Function: Delete spell book info
	** Description: Deletes a spell book array IF AND ONLY IF the array doesn't
	*  have a defined array of spells inside it
	** Parameters: Spell book array
	** Pre-Conditions: Spell book array doesn't have spell array inside
	** Post-Conditions: Deletes it and sets pointer to null
	*********************************************************************/
	for(int i = 0; i < num_spell_books; i++){
		delete [] sb[i].s;
		sb[i].s = NULL;
	}
	delete [] sb;
	sb = NULL;
}
//Done
void delete_sorted_spells(spellbook* sb, spell* spell, int num_spell_books){
	/*********************************************************************
	** Function: Delete sorted spells
	** Description: Deletes an array of spellbooks and all spells within
	** Parameters: spellbook array, spell array, number of spell books
	** Pre-Conditions: All are defined
	** Post-Conditions: All are deleted
	*********************************************************************/
	for(int i = 0; i < num_spell_books; i++){
		delete [] sb[i].s;
		sb[i].s = NULL;
	}
	delete [] sb;
	delete [] spell;
	sb = NULL;
	spell = NULL;
}






/*********************************************************************
	** Function:
	** Description:
	** Parameters:
	** Pre-Conditions:
	** Post-Conditions:
	*********************************************************************/


