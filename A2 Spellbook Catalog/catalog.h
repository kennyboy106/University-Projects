#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct wizard{
	string name;
	int id;
	string password;
	string position_title;
	float beard_length;
};

struct spell{
	string name;
	float success_rate;
	string effect;
};

struct spellbook{
	string title;
	string author;
	int num_pages;
	int edition;
	int num_spells;
	float avg_success_rate;
	struct spell *s;
};

void openfiles(char** argv, int argc, ifstream *users, ifstream *spellbook);

//Wizard functions//
wizard* wizard_create_array(ifstream*, int*);
void wizard_populate(ifstream**, wizard*, int);
wizard* wizard_login(ifstream *file_users, int*);
void login_cap(int*);
void wizard_set_and_print(wizard*, wizard*, int);

//Required Functions//
spellbook* create_spellbooks(int);
void populate_spellbook_data(spellbook*, int, ifstream&);
spell* create_spells(int);
void populate_spell_data(spell*, int, ifstream&);
void delete_info(wizard**, spellbook**, int);

//Spell functions//
void spell_effect_sort(spell*, int);
spell* spell_combine(spellbook*, int*);


//Spell book functions//
int spellbook_number_censored(spellbook*, int);
void menu_options_print_to_file(spellbook*, string);

//Menu functions//
void menu_options(spellbook*, wizard*, int);
void menu_spellbook_page_option(spellbook*, wizard*, int);
void menu_spellbook_effect_option(spellbook*, wizard*, int);
void menu_spellbook_success_rate_option(spellbook*, wizard*, int);
void menu_spellbook_success_assign(spellbook*, int);
void menu_spellbook_success_rate_sort(spellbook*, int);
void spellbook_page_sort(spellbook*, int);
void spellbook_copy_basic(spellbook*, int, spellbook*, int);
spellbook* spellbook_copy_page(spellbook*, int);
spellbook* spellbook_copy_page_censor(spellbook*, int&);
spellbook* spellbook_copy_effect(spellbook*, int);
spellbook* spellbook_copy_effect_censor(spellbook*, int&);
void menu_options_print_sorted_spellbook(spellbook*, int);
void menu_options_print_sorted_spells(spell*, int);
void menu_options_print_sorted_success(spellbook*, int);
void open_output_file(ofstream*);
void menu_options_spellbook_print_to_file(spellbook*, int, string);
void menu_options_spells_print_to_file(spell*, int);
void menu_print_options();
void menu_options_print_menu();

//Utility//
bool validint(string i);
void delete_spellbook_info(spellbook*, int);
void delete_sorted_spells(spellbook*, spell*, int);

