#include <iostream>
#include <vector>
#include "linked_list.h"
using namespace std;


// Default constructor
Linked_List::Linked_List(){
	// cout << "linked_list constructor" << endl;
	this->length = 0;
	this->head = NULL;
}

// Destructor
Linked_List::~Linked_List(){
	// cout << "linked_list destructor" << endl;
	while(head != NULL){
		// save the next node
		Node* temp = head->next;
		// Delete the data of the node we are on
		delete head;
		// set to the next node in the list
		head = temp;
	}
}

int Linked_List::get_length(){
	/*********************************************************************
	** Function: Get length
	** Description: Gets the length of the list
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Returns the length of the list
	*********************************************************************/
	return this->length;

	/* This code actually computes the length
	Node* temp = head;
	// If the head node doesn't point to anything, return with 0
	if(head == NULL){
		return 0;
	}
	// Start counting at 1 since we know the list contains something
	int length = 1;
	while(head->next != NULL){
		// Move the list forward
		head = head->next;
		length++;
	}
	// Reset the head
	head = temp;

	return length;
	*/
}

Node* Linked_List::get_head(){
	/*********************************************************************
	** Function: Get head
	** Description: Returns the head of the list
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Returns the head of the list
	*********************************************************************/
	return head;
}


void Linked_List::print(){
	/*********************************************************************
	** Function: Print
	** Description: Print the linked list
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Prints the linked list
	*********************************************************************/
	Node* temp = head;
	for (int i = 0; i < this->length; ++i)
	{
		cout << head->val << " ";
		head = head->next;
	}
	cout << endl;
	head = temp;
}

void Linked_List::clear(){
	/*********************************************************************
	** Function: Clear
	** Description: Clears the linked list, freeing memory and resets the length
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Deletes the linked list
	*********************************************************************/
	cout << "linked_list clear" << endl;
	while(head != NULL){
		// save the next node
		Node* temp = head->next;
		// Delete the data of the node we are on
		delete head;
		// set to the next node in the list
		head = temp;
	}
	this->length = 0;
}

void Linked_List::push_front(int i){
	/*********************************************************************
	** Function: Push front
	** Description: Adds an item to the front of the list
	** Parameters: The value of the new item
	** Pre-Conditions: None
	** Post-Conditions: Adds an item to the front of the list
	*********************************************************************/
	Node* new_node = new Node;
	new_node->next = head;
	new_node->val = i;
	head = new_node;
	this->length++;
}

void Linked_List::push_back(int val){
	/*********************************************************************
	** Function: Push back
	** Description: Pushes an item to the end of the list
	** Parameters: Value of the new item
	** Pre-Conditions: None
	** Post-Conditions: Adds an item to the end of the list
	*********************************************************************/
	// Save head place
	Node* temp = head;
	// Get to the last node
	while(head->next != NULL){
		head = head->next;
	}
	// At the last node in the list, create a new node
	head->next = new Node(val);
	// // Move to that node
	// head = head->next;
	// // Set the value
	// head->val = i;
	// Return to the start of the list
	head = temp;
	this->length++;
}

void Linked_List::insert(int val, unsigned int index){
	/*********************************************************************
	** Function: Insert
	** Description: Inserts an element in the linked list. Doesn't insert item
	*  if the list is shorter than the index
	** Parameters: Value and the spot to insert the item
	** Pre-Conditions: None
	** Post-Conditions: Inserts item into the list
	*********************************************************************/
	// Return is index is larger than list length
	if (index > this->length)
	{
		return;
	}
	// Save the location of the first node
	Node* temp = head;
	if (index == 0)
	{
		head = new Node(val);
		head->next = temp;
	}
	else{
		// Get to the node right before insertion
		for (int i = 0; i < index - 1; ++i)
		{
			head = head->next;
		}
		// Save the address of the next node in the list to be shifted over
		Node* shifted_node = head->next;

		// Set head->next to the new node
		head->next = new Node(val);
		// Set the node after the new one to the next in line
		head->next->next = shifted_node;
		// Reset the head
		head = temp;
	}
	this->length++;
}



void Linked_List::sort_ascending(){
	/*********************************************************************
	** Function: Sort ascending
	** Description: Calls the merge sort function with descending mode
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Sorts the list in ascending order
	*********************************************************************/
	merge_sort(&head, 0);
}

void Linked_List::sort_descending(){
	/*********************************************************************
	** Function: Sort descending
	** Description: Calls the merge sort function with descending mode
	** Parameters: None
	** Pre-Conditions: None
	** Post-Conditions: Sorts the list in descending order
	*********************************************************************/
	merge_sort(&head, 1);
}

void merge_sort(Node** head, int i){
	/*********************************************************************
	** Function: Merge sort
	** Description: Uses merge sort to sort a linked list either descending or
	*  ascending order based on i
	** Parameters: Pointer to the head pointer and an integer to decide the mode
	** Pre-Conditions: None
	** Post-Conditions: Returns a sorted list based on i
	*********************************************************************/

	Node* temp = *head;
	Node* a;
	Node* b;
	if (temp == NULL || temp->next == NULL)
	{
		return;
	}

	partition(temp, &a, &b);

	merge_sort(&a, i);
	merge_sort(&b, i);
	// Enter 0 for ascending order
	if(i == 0){
		*head = merge_asc(a, b);
	}
	// Enter 1 for descending order
	else if(i == 1){
		*head = merge_desc(a, b);
	}

}

void partition(Node* head, Node** front, Node** back){
	/*********************************************************************
	** Function: Partition
	** Description: Breaks a linked list in half. Extra elements in the middle get
	*  attached to the left list (front).
	** Parameters: Head node of the list to be broken and two pointers to accept
	*  the new heads of the broken lists
	** Pre-Conditions: None
	** Post-Conditions: Breaks the list in half and sets front and back to be the
	*  heads of the new list
	*********************************************************************/
	// Set the indexing nodes
	Node* fast = head->next;
	Node* slow = head;
	// Index until fast is null
	while(fast != NULL){
		fast = fast->next;
		// If fast isn't null yet, advance slow
		if(fast != NULL){
			slow = slow->next;
			fast = fast->next;
		}
	}
	// Slow is the midpoint of the list now
	// Split the list into 2 pieces, the front gets the regular head
	*front = head;
	// The back gets the second half of the list
	*back = slow->next;
	// Mark the end of the first part of the list
	slow->next = NULL;
}

Node* merge_asc(Node* a, Node* b){
	/*********************************************************************
	** Function: Merge ascending
	** Description: Uses merge sort with ascending sort. Uses two nodes and
	*  compares them with each other until either node doesn't have a next node after
	** Parameters: Two nodes
	** Pre-Conditions: None
	** Post-Conditions: Merges two linked lists together in ascending order and
	*  returns the head of the new list
	*********************************************************************/

	Node* temp = NULL;

	// If we are down to single elements return the non, null element
	// Check a first because single items will be split into the left list (aka a)
	if(a == NULL){
		return b;
	}
	if(b == NULL){
		return a;
	}
	// Recursively build the lists, taking out elements as we go
	if(a->val <= b->val){
		temp = a;
		temp->next = merge_asc(a->next, b);
	}
	else{
		temp = b;
		temp->next = merge_asc(a, b->next);
	}
	return temp;
}

Node* merge_desc(Node* a, Node* b){
	/*********************************************************************
	** Function: Merge descending
	** Description: Uses merge sort with descending sort. Uses two nodes and
	*  compares them with each other until either node doesn't have a next node after
	** Parameters: Two nodes
	** Pre-Conditions: None
	** Post-Conditions: Merges two linked lists together in descending order and
	*  returns the head of the new list
	*********************************************************************/

	Node* temp = NULL;

	// If we are down to single elements return the non, null element
	// Check a first because single items will be split into the left list (aka a)
	if(a == NULL){
		return b;
	}
	if(b == NULL){
		return a;
	}
	// Recursively build the lists, taking out elements as we go
	if(a->val >= b->val){
		temp = a;
		temp->next = merge_desc(a->next, b);
	}
	else{
		temp = b;
		temp->next = merge_desc(a, b->next);
	}
	return temp;
}

unsigned int count_prime(Linked_List& l){
	/*********************************************************************
	** Function: Count prime
	** Description: counts the number of prime numbers in a linked list
	** Parameters: The linked list itself
	** Pre-Conditions: None
	** Post-Conditions: Returns the number of prime numbers including 0 and 1
	*********************************************************************/
	unsigned int num_primes = 0;

	Node* head = l.get_head();
	while(head != NULL){
		if(head->val == 1 || head->val == 0){
			num_primes++;
		}
		else if(head->val > 0){
			for(int i = 2; i <= head->val / 2; i++){
				if(head->val % i == 0){
					num_primes++;
					break;
				}
			}
		}
		head = head->next;
	}



	return num_primes;
}



// int pow(int n, int exp){

// 	if(exp == 0){
// 		return 1;
// 	}
// 	else if(n == 0){
// 		return 0;
// 	}


// 	return n * pow(n, exp - 1);

// }

// Sorting
// Given a collection of data, sort in some order


// Selection sort
/**Divide the array into two parts
 * 		the elements that are already sorted on the left
 * 		unsorted elements on the right
 * Find the smallest element in the unsorted elements
 * Swap the smallest element with the leftmost element in the unsorted
 * Repeat
 *
 *
 */
/*
// Done
void select_sort(vector<int> &vec){
	for(int i = 0; i < vec.size() - 1; i++){
		int min = i;
		for(int j = i + 1; j < vec.size(); j++){
			if(vec[j] < vec[min]){
				min = j;
			}
		}
		if(min != i){
			swap(vec[i], vec[min]);
		}
	}
}

// Done
void insertion_sort(vector<int> &vec){
	for (int i = 0; i < vec.size(); ++i)
	{
		int j = i;
		while(j > 0 && vec[j] < vec[j-1]){
			swap(vec[j], vec[j - 1]);
			j--;
		}
	}
}

/*
void merge_sort(vector<int> &vec, int l, int r){
	// If left is less than right
	if(l < r){
		int m = l + (r - 1)/2;
		merge_sort(vec, l, m);
		merge_sort(vec, m + 1, r);
		merge(vec, l, m, r);
	}
}

void merge(vector<int> &vec, int l, int m, int r){
	// Needs to merge together the smaller vector
}

*/



