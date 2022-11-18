#include <iostream>
#include "catalog.h"
using namespace std;

/******************************************************
** Program: wizard_catalog.cpp
** Author: Kenneth Tang
** Date: 04/20/2022
** Description: A sorting program that censors harmful spells
*  from students
** Input: Two text files with user information and spell data
** Output: Text to console or a specific file
******************************************************/

int main(int argc, char** argv){

	/*
	1st Step;
		Edit parameters of main to accept to text files
		check those files to see if they can be opened, if not, exit()
		If able to open, collect data
	*/
	//Open files
	ifstream file_users, file_spellbook;
	openfiles(argv, argc, &file_users, &file_spellbook);

	//Copy all the data from files
	int num_wizards, num_spell_books;
	file_spellbook >> num_spell_books;
	spellbook* spellinfo = create_spellbooks(num_spell_books);
	populate_spellbook_data(spellinfo, num_spell_books, file_spellbook);

	/*
	2nd Step;
		Ask for user id & password
		check against the wizards.txt file (1st file)
	*/
	wizard* wizinfo = wizard_login(&file_users, &num_wizards);
	//wizinfo now only has info on logged in user




	/*
	3rd Step;
		Ask for what user wants to do:
		sort spell books by number of pages
		sort spells by effect
		sort by average success rate of spells
		quit

		Inside this function I get input for option
		Then call a function for each option and pass in whats needed

	*/
	menu_options(spellinfo, wizinfo, num_spell_books);



	//dont forget to delete the array of spells within each book
	// delete [] spellinfo;
	// spellinfo = NULL;
	// delete [] wizinfo;
	// wizinfo = NULL;
	delete_info(&wizinfo, &spellinfo, num_spell_books);
}