// cards.h

#ifndef CARDS_H
#define CARDS_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Cards {
	public:
		Cards() { suit = "X"; value = "X"; }
		Cards(string s, string v) { suit = s; value = v; }
		void setSuit(string s) { suit = s; }
		void setValue(string v) { value = v; }
		string getSuit() { return suit; }
		string getValue() { return value; }
		bool operator<(const Cards &a);
		bool operator>(const Cards &a);
		bool operator==(const Cards &a);
	private:	
		string suit;
		string value;
};

class BST {

 public:
	BST();                   // constructor
	~BST();                  // destructor
	bool insert(string suit, string value);     // insert value; return false if duplicate

	void returnLeastGreatest() const;       // print tree data in-order to cout
	void returnGreatestLeast() const;     // print tree data post-order to cout
	bool contains(string suit, string value) const;  // true if value is in tree

	Cards getPredecessor(string suit, string value) const;       // returns the predecessor value of the given value or 0 if there is none
	Cards getSuccessor(string suit, string value) const;         // returns the successor value of the given value or 0 if there is none
	bool remove(string suit, string value);                    // deletes the Node containing the given value from the tree
	vector<string> returnGreatestLeast(vector<string>& v); // returns a vector thats a string of the cards
	vector<string> returnLeastGreatest(vector<string>& v);
 private:

	struct Node {
	       Cards card;
	       Node *left, *right, *parent;
	      
	Node() : card(), left(0), right(0), parent(0) { }     
	};
	Node* root;

	vector<string> returnLeastGreatest(vector<string>& v, Node *n);
	vector<string> returnGreatestLeast(vector<string>& v, Node *n); // returns a vector thats a string of the cards
	Node* getNodeFor(string suit, string value, Node* n) const; // returns the node for a given value or NULL if none exists
	void clear(Node *n); // for destructor
	bool insert(Cards currCard, Node *n); // note overloading names for simplicity
	void returnLeastGreatest(Node *n) const;
	void returnGreatestLeast(Node *n) const;

	Node* getSuccessorNode(string suit, string value) const;   // returns the Node containing the successor of the given value
	Node* getPredecessorNode(string	suit, string value) const; // returns the Node containing the predecessor of the given value
};

#endif

