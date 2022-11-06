// cards.cpp

#include "cards.h"

#include <iostream>
#include <string>
#include <vector>


// constructor sets up empty tree
BST::BST() {
    root = nullptr;
}

// destructor deletes all nodes
BST::~BST() {
    clear(root);
    root = nullptr;
}

// recursive helper for destructor
void BST::clear(Node *n) {
    if (!n) return;
    clear(n->left);
    clear(n->right);
    delete n;
}

// insert value in tree; return false if duplicate
bool BST::insert(string suit, string value) {
        if (!root) {
		Node *temp = new Node();
		temp->card.setSuit(suit);
		temp->card.setValue(value);
		root = temp;
		return true;
	}
        else {
	    Cards currCard(suit, value);
            return insert(currCard, root);
    }
}


// recursive helper for insert (assumes n is never 0)
bool BST::insert(Cards currCard, Node *n) {
    if (currCard > n->card) {
        if (!n->right) {
            Node *temp = new Node();
	    temp->card.setSuit(currCard.getSuit());
	    temp->card.setValue(currCard.getValue());
	    temp->parent = n;
            n->right = temp;
            return true;
        } else{
            return insert(currCard, n->right);
        }
    }
    else if (currCard < n->card) {
        if (!n->left) {
            Node *temp = new Node();
	    temp->card.setSuit(currCard.getSuit());
	    temp->card.setValue(currCard.getValue());
	    temp->parent = n;
            n->left = temp;
            return true;
        } else{
           return insert(currCard, n->left);
        }
    }
    else { // is equal
        return false;
    }
}

// print tree data pre-order
void BST::returnLeastGreatest() const {
    returnLeastGreatest(root);
}

// recursive helper for printPreOrder()
void BST::returnLeastGreatest(Node *n) const {
    if (!n) {
        return;
    }
    returnLeastGreatest(n->left);
    cout << n->card.getSuit() << " " << n->card.getValue() << endl;
    returnLeastGreatest(n->right);
}


// print tree data in-order, with helper
void BST::returnGreatestLeast() const {
    returnGreatestLeast(root);
}

void BST::returnGreatestLeast(Node *n) const {
    if (!n) {
        return;
    }
    returnGreatestLeast(n->right);
    cout << n->card.getSuit() << " " << n->card.getValue() << endl;
    returnGreatestLeast(n->left);
}

vector<string> BST::returnLeastGreatest(vector<string>& v) {
    return returnLeastGreatest(v, root);
}

vector<string> BST::returnLeastGreatest(vector<string>& v, Node *n) {
    if (!n) {
        return v;
    }
    returnLeastGreatest(v, n->left);
    
    v.push_back(n->card.getSuit() + " " + n->card.getValue()); // do i need to static cast suit because it is a char?
    
    returnLeastGreatest(v, n->right);

    return v;
}
vector<string> BST::returnGreatestLeast(vector<string>& v) {
    return returnGreatestLeast(v, root);
}

vector<string> BST::returnGreatestLeast(vector<string>& v, Node *n) {
    if (!n) {
        return v;
    }
    returnGreatestLeast(v, n->right);
    
    v.push_back(n->card.getSuit() + " " + n->card.getValue()); // do i need to static cast suit because it is a char?
    
    returnGreatestLeast(v, n->left);

    return v;
}

// Finds the node for a given value
BST:: Node* BST::getNodeFor(string suit, string value, Node* n) const{
    Cards currCard(suit, value);

    if (!n) {
        return nullptr;
    }
    if (currCard > n->card) {
	if (!n->right) {
		return nullptr;
	} else {
        	return  getNodeFor(suit, value, n->right);
	}
    }
    else if (currCard < n->card) {
    	if (!n->left) {
		return nullptr;
	} else {
		return getNodeFor(suit, value, n->left);
	}
    }
    else {
	    return n;
    }
}

// returns true if value is in the tree; false if not

// FIX
bool BST::contains(string suit, string value) const {
    if (getNodeFor(suit, value, root)) return true;
    else return false;
}

// returns the Node containing the predecessor of the given value
BST::Node* BST::getPredecessorNode(string suit, string value) const{
    Cards currCard(suit, value);

    if (!root) return 0;
    Node *currNode = getNodeFor(suit, value, root);
    if (!currNode) return 0;
    if (!currNode->left) {
        if (!currNode->parent) return 0;
        else {
            while (currNode->parent) {
                if (currNode->parent->card < currCard) {
                    return currNode->parent;
                }
                currNode = currNode->parent;
            }
            if (!currNode->parent) return 0;
        }
    } else {
        currNode = currNode->left;
        while (currNode->right) {
            currNode = currNode->right;
        }
    }
    return currNode;
}

// returns the predecessor value of the given value or 0 if there is none
Cards BST::getPredecessor(string suit, string value) const{
    Cards nullCard("X", "X");
    Cards currCard(suit, value);

    if (!root) return nullCard;
    Node *currNode = getNodeFor(suit, value, root);
    if (!currNode) return nullCard;
    if (!currNode->left) {
        if (!currNode->parent) return nullCard;
        else {
            while (currNode->parent) {
                if (currNode->parent->card < currCard) {
                    return currNode->parent->card;
                }
                currNode = currNode->parent;
            }
            if (!currNode->parent) return nullCard;
        }
    } else {
        currNode = currNode->left;
        while (currNode->right) {
            currNode = currNode->right;
        }
    }
    return currNode->card;
}

// returns the Node containing the successor of the given value
BST::Node* BST::getSuccessorNode(string suit, string value) const{
    Cards currCard(suit, value);

    if (!root) return nullptr;
    Node *currNode = getNodeFor(suit, value, root);
    if (!currNode) return nullptr;
    if (!currNode->right) {
        if (!currNode->parent) return nullptr;
        else {
            while (currNode->parent) {
                if (currNode->parent->card > currCard) {
                    return currNode->parent;
                }
                currNode = currNode->parent;
            }
            if (!currNode->parent) return nullptr;
        }
    }
    else {
        currNode = currNode->right;
        while (currNode->left) {
            currNode = currNode->left;
        }
    }
    return currNode;
}


// returns the successor value of the given value or 0 if there is none
Cards BST::getSuccessor(string suit, string value) const{
    Cards nullCard("X", "X");
    Cards currCard(suit, value);

    if (!root) return nullCard;
    Node *currNode = getNodeFor(suit, value, root);
    if (!currNode) return nullCard;
    if (!currNode->right) {
        if (!currNode->parent) return nullCard;
        else {
            while (currNode->parent) {
                if (currNode->parent->card > currCard) {
                    return currNode->parent->card;
                }
                currNode = currNode->parent;
            }
            if (!currNode->parent) return nullCard;
        }
    }
    else {
        currNode = currNode->right;
        while (currNode->left) {
            currNode = currNode->left;
        }
    }
    return currNode->card;
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool BST::remove(string suit, string value){
    Cards currCard(suit, value);

    Node *currNode = getNodeFor(suit, value, root);
    if (!currNode) return false;
    if (currNode == root && !root->left && !root->right) {
        delete currNode;
        root = nullptr;
        return true;
    }
    else {
        if (!currNode->left && !currNode->right) { // no children
            if (currNode->parent->right == currNode) {
            	currNode->parent->right = nullptr;
            	delete currNode;
            	return true;
            }
	    else {
            	currNode->parent->left = nullptr;
            	delete currNode;
            	return true;
            }
        }
	else if (currNode->left && currNode->right) { // two children
		Node* newNode = getSuccessorNode(suit, value);
		string newSuit = newNode->card.getSuit();
		string newValue = newNode->card.getValue();
		remove(newNode->card.getSuit(), newNode->card.getValue());
		currNode->card.setSuit(newSuit);
		currNode->card.setValue(newValue);
		return true;
        }
	else { // only has one child
		if (!currNode->parent) { // checking if the currNode is a root node
			if (currNode->left) {
				currNode->left->parent = nullptr;
				root = currNode->left;
				delete currNode;
				return true; 
			}
			else {
				currNode->right->parent = nullptr;
				root = currNode->right;
				delete currNode;
				return true;
			}
		}
		else if (currNode->left) { // only has left child which is left
                	currNode->left->parent = currNode->parent;
                	if (currNode->parent->card > currCard) {
				currNode->parent->left = currNode->left;
               		}
			else {
				currNode->parent->right = currNode->left;
                	}
                	delete currNode;
                	return true;
            	}
		else { // only has right child
                	currNode->right->parent = currNode->parent;
                	if (currNode->parent->card > currCard) {
        	            	currNode->parent->left = currNode->right;
                	}
			else {
	                    	currNode->parent->right = currNode->right;
               		}
                	delete currNode;
                	return true;
           		}
        	}
    	}
}


bool Cards::operator==(const Cards& a) {
	int leftSuitVal = 0;
	int rightSuitVal = 0;
	int rightIntVal = 0;
	int leftIntVal = 0;
	
	
	if (value == "a") leftIntVal = 1;
	else if (value == "2") leftIntVal = 2;
	else if (value == "3") leftIntVal = 3;
	else if (value == "4") leftIntVal = 4;
	else if (value == "5") leftIntVal = 5;
	else if (value == "6") leftIntVal = 6;
	else if (value == "7") leftIntVal = 7;
	else if (value == "8") leftIntVal = 8;
	else if (value == "9") leftIntVal = 9;
	else if (value == "10") leftIntVal = 10;
	else if (value == "j") leftIntVal = 11;
	else if (value == "q") leftIntVal = 12;
	else if (value == "k") leftIntVal = 13;

	if (a.value == "a") rightIntVal = 1;
	else if (a.value == "2") rightIntVal = 2;
	else if (a.value == "3") rightIntVal = 3;
	else if (a.value == "4") rightIntVal = 4;
	else if (a.value == "5") rightIntVal = 5;
	else if (a.value == "6") rightIntVal = 6;
	else if (a.value == "7") rightIntVal = 7;
	else if (a.value == "8") rightIntVal = 8;
	else if (a.value == "9") rightIntVal = 9;
	else if (a.value == "10") rightIntVal = 10;
	else if (a.value == "j") rightIntVal = 11;
	else if (a.value == "q") rightIntVal = 12;
	else if (a.value == "k") rightIntVal = 13;
	
	if (suit == "c") leftSuitVal = 1;
	else if (suit == "d") leftSuitVal = 2;
	else if (suit == "s") leftSuitVal = 3;
	else if (suit == "h") leftSuitVal = 4;

	if (a.suit == "c") rightSuitVal = 1;
	else if (a.suit == "d") rightSuitVal = 2;
	else if (a.suit == "s") rightSuitVal = 3;
	else if (a.suit == "h") rightSuitVal = 4;

	if (leftSuitVal == rightSuitVal) {
		if (leftIntVal == rightIntVal) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}
bool Cards::operator<(const Cards& a) {
	int leftSuitVal = 0;
	int rightSuitVal = 0;
	int rightIntVal = 0;
	int leftIntVal = 0;
	
	
	if (value == "a") leftIntVal = 1;
	else if (value == "2") leftIntVal = 2;
	else if (value == "3") leftIntVal = 3;
	else if (value == "4") leftIntVal = 4;
	else if (value == "5") leftIntVal = 5;
	else if (value == "6") leftIntVal = 6;
	else if (value == "7") leftIntVal = 7;
	else if (value == "8") leftIntVal = 8;
	else if (value == "9") leftIntVal = 9;
	else if (value == "10") leftIntVal = 10;
	else if (value == "j") leftIntVal = 11;
	else if (value == "q") leftIntVal = 12;
	else if (value == "k") leftIntVal = 13;

	if (a.value == "a") rightIntVal = 1;
	else if (a.value == "2") rightIntVal = 2;
	else if (a.value == "3") rightIntVal = 3;
	else if (a.value == "4") rightIntVal = 4;
	else if (a.value == "5") rightIntVal = 5;
	else if (a.value == "6") rightIntVal = 6;
	else if (a.value == "7") rightIntVal = 7;
	else if (a.value == "8") rightIntVal = 8;
	else if (a.value == "9") rightIntVal = 9;
	else if (a.value == "10") rightIntVal = 10;
	else if (a.value == "j") rightIntVal = 11;
	else if (a.value == "q") rightIntVal = 12;
	else if (a.value == "k") rightIntVal = 13;
	
	if (suit == "c") leftSuitVal = 1;
	else if (suit == "d") leftSuitVal = 2;
	else if (suit == "s") leftSuitVal = 3;
	else if (suit == "h") leftSuitVal = 4;

	if (a.suit == "c") rightSuitVal = 1;
	else if (a.suit == "d") rightSuitVal = 2;
	else if (a.suit == "s") rightSuitVal = 3;
	else if (a.suit == "h") rightSuitVal = 4;
	
	if (leftSuitVal < rightSuitVal) {
		return true;
	}
	else if (leftSuitVal == rightSuitVal) {
		if (leftIntVal < rightIntVal) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}

}
bool Cards::operator>(const Cards& a) {
	int leftSuitVal = 0;
	int rightSuitVal = 0;
	int rightIntVal = 0;
	int leftIntVal = 0;
	
	
	if (value == "a") leftIntVal = 1;
	else if (value == "2") leftIntVal = 2;
	else if (value == "3") leftIntVal = 3;
	else if (value == "4") leftIntVal = 4;
	else if (value == "5") leftIntVal = 5;
	else if (value == "6") leftIntVal = 6;
	else if (value == "7") leftIntVal = 7;
	else if (value == "8") leftIntVal = 8;
	else if (value == "9") leftIntVal = 9;
	else if (value == "10") leftIntVal = 10;
	else if (value == "j") leftIntVal = 11;
	else if (value == "q") leftIntVal = 12;
	else if (value == "k") leftIntVal = 13;

	if (a.value == "a") rightIntVal = 1;
	else if (a.value == "2") rightIntVal = 2;
	else if (a.value == "3") rightIntVal = 3;
	else if (a.value == "4") rightIntVal = 4;
	else if (a.value == "5") rightIntVal = 5;
	else if (a.value == "6") rightIntVal = 6;
	else if (a.value == "7") rightIntVal = 7;
	else if (a.value == "8") rightIntVal = 8;
	else if (a.value == "9") rightIntVal = 9;
	else if (a.value == "10") rightIntVal = 10;
	else if (a.value == "j") rightIntVal = 11;
	else if (a.value == "q") rightIntVal = 12;
	else if (a.value == "k") rightIntVal = 13;
	
	if (suit == "c") leftSuitVal = 1;
	else if (suit == "d") leftSuitVal = 2;
	else if (suit == "s") leftSuitVal = 3;
	else if (suit == "h") leftSuitVal = 4;

	if (a.suit == "c") rightSuitVal = 1;
	else if (a.suit == "d") rightSuitVal = 2;
	else if (a.suit == "s") rightSuitVal = 3;
	else if (a.suit == "h") rightSuitVal = 4;
	
	if (leftSuitVal > rightSuitVal) {
		return true;
	}
	else if (leftSuitVal == rightSuitVal) {
		if (leftIntVal > rightIntVal) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}

}
