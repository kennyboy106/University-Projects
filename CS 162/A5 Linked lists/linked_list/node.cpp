#include "node.h"
#include <iostream>
using namespace std;

// Default constructor
Node::Node(){
	// cout << "Node Default constructor" << endl;
	this->val = 0;
	this->next = NULL;

}

Node::Node(int i){
	// cout << "Node non Default constructor" << endl;
	this->val = i;
	this->next = NULL;
}
Node::~Node(){
	// cout << "Node destructor" << endl;
}