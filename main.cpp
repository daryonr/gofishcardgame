#include "cards.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(int argv, char** argc) {
  BST player1;
  BST player2;
  vector<string> player1Cards;
  vector<string> player2Cards;
  long unsigned int itr = 0;
  long unsigned int itr1 = 0;
  long unsigned int itr2 = 0;
  string suit;
  string value;
  bool cardFound1 = false;
  bool cardFound2 = false;

  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }

  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }

  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){
  	string suit1 = line.substr(0, line.find(" "));
  	string value1 = line.substr((line.find(" ") + 1), line.length());
	player1.insert(suit1, value1);
  }
  cardFile1.close();

  player1.returnLeastGreatest(player1Cards);
  
  while (getline (cardFile2, line) && (line.length() > 0)){
  	string suit2 = line.substr(0, line.find(" "));
  	string value2 = line.substr((line.find(" ") + 1), line.length());
	player2.insert(suit2, value2);
  }
  cardFile2.close();
  
  player2.returnGreatestLeast(player2Cards);

  while (itr < (player1Cards.size())) {
     while (!cardFound1 && itr1 < player1Cards.size()) {
	  for (unsigned int i = 0; i < player2Cards.size(); ++i) {
		if (player1Cards.at(itr1) == player2Cards.at(i)) {
  			suit = (player1Cards.at(itr1)).substr(0, (player1Cards.at(itr1)).find(" "));
  			value = player1Cards.at(itr1).substr(((player1Cards.at(itr1)).find(" ") + 1), (player1Cards.at(itr1)).length());
			if (player1.contains(suit, value)) {
				cout << "Alice picked matching card " << player1Cards.at(itr1) << endl;
				player1.remove(suit, value);
				player2.remove(suit, value);
				cardFound1 = true;
			}
			suit.clear();
			value.clear();
		}
	}
	itr1++;
     }
     while (!cardFound2 && itr2 < player2Cards.size()) {
        for (unsigned int j = 0; j < player1Cards.size(); ++j) {
		if (player2Cards.at(itr2) == player1Cards.at(j)) {
  			suit = (player2Cards.at(itr2)).substr(0, (player2Cards.at(itr2)).find(" "));
  			value = player2Cards.at(itr2).substr(((player2Cards.at(itr2)).find(" ") + 1), (player2Cards.at(itr2)).length());
		        if (player2.contains(suit, value)) {	
				cout << "Bob picked matching card " << player2Cards.at(itr2) << endl;
				player1.remove(suit, value);
				player2.remove(suit, value);
				cardFound2 = true;
			}
			suit.clear();
			value.clear();
		}
	}
	itr2++;
     }
     itr++;
     cardFound1 = cardFound2 = false;
  }
  
  cout << endl << "Alice's cards:" << endl;
  player1.returnLeastGreatest();
  cout << endl << "Bob's cards:" << endl;
  player2.returnLeastGreatest();
  
  return 0;
}
