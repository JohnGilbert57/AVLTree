#include <iostream>
#include <string>
#include <cctype>
#include "avl_tree.h"
using namespace std;
/*
Name: bool isInt(const string &s)
ReturnType: boolean
Function: Checks to see if the key value that the user inputs is an integer
          for the insert and delete functions
*/
bool isInt(const string &s);

int main(int argc, char** argv) {
  bool isTaller = false;
  //declaration of an AVLTree object
  AVLTree tree;
  //user input will be assigned to this variable to decide which action will be performed
  char option;
  //will hold the value of the key value for insertion or deletion
  string key;
  //will use stoi() to convert string key to an int for key values
  int k;
  do {
    //takes in available option for action
    cin >> option;
    //switch case to call the appropriate function for the AVL Tree
    switch(option) {
      //if 'i' is inputted
      case 'i':
        //Line 38-43: takes in key value for insertion and makes sure it is an integer
        cin >> key;
        while(!isInt(key)){
          cout << "Not an Integer please enter a valid integer: ";
          cin >> key;
        }
        //converts key value to an integer
        k = stoi(key);
        tree.insert(k);
        //cout << tree.getRoot()->key << endl;
        break;
      //if 'r' is inputted
      case 'r':
        //line 52-60: takes in key value for removal and checks to see if it is an integer 
        cin >> key;
        while(!isInt(key)){
          cout << "Not an Integer please enter a valid integer: ";
          cin >> key;
        }
        //converts key to an integer for removal
        k = stoi(key);
        tree.remove(k);
        break;
      //if 'h' is inputted
      case 'h':
        //finds the height of every node
        tree.heightInorder(tree.getRoot());
        cout << endl;
        break;
      //if 'p' is inputted
      case 'p':
        //uses inorder travesal to print the AVLTree
        tree.printInorder(tree.getRoot());
        cout << endl;
        break;
      //if 'q' is inputted
      case 'q':
        cout << "Have a Nice Day!" << endl;
        break;
      //default statement if no equivalency is found
      default:
        cout << "Not a valid option" << endl;
        break;
    }
  } while(option != 'q');
}
/*
Name: bool isInt(const string &s)
ReturnType: boolean
Function: Checks to see if the key value that the user inputs is an integer
          for the insert and delete functions
*/
bool isInt(const string &s){
  for(size_t i = 0; i < s.length(); i++){
    //checks to see if individual character is a digit
    if(!isdigit(s[i])){
      //if a character is found to not be a digit return false
      return false;
    }
  }
  //if no characters are found to not be digits return true
  return true;
}