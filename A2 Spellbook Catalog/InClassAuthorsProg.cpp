//IN CLASS//
//Reading from spell books
ifstream fin;

int num_books = 0;
//read integer at start of file
fin >> num_books;

book* create_book(int num){
	return book[num]
}

book* arr_books = create_book(num_books);

string* create_authors(int num_aut){
	return new string[num_aut];
}

void populate_authors(string* authors, int num_aut, ifstream* fin){
	for(int i = 0; i < num_aut; i++){
		fin >> authors[i];
	}
}


void populate_bookarr(book* b, int num, ifstream* fin){ //passing ifstream by reference saves the cursor location
	for(int i = 0; i < num; i++){
		fin >> b[i].title >> b[i].pages >> b[i].num_authors;
		b[i].authors = create_authors(b[i].num_authors);
		for(int j = 0; j < b[i].num_authors; j++){
			b[i].authors[j] = "Some author";
		}
		populate_authors(b[i].authors, b[i].num_authors, &fin);
	}


}