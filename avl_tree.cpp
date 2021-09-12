#include <iostream>
#include "avl_tree.h"
using namespace std;
/*
  Name: void balanceFromRight(BinaryNode* &root);
  Return Type: NULL
  Functionality: Calls appropriate rotate function in order to maintain AVL status
  Uses: rotateToLeft(), rotateToRight()
*/
void AVLTree::balanceFromRight(BinaryNode* &root){
  //temp BinaryNode 
  BinaryNode* p;
  //temp Binary node
  BinaryNode* w;
  p = root->right;
  int b = p->bfactor;
  switch(p->bfactor){
    //line: 18-37: assumes the correct bfactor values for the nodes and call the appropriate rotation functions
    case -1:
      w = p->left;
      switch(w->bfactor){
        case -1:
          root->bfactor = 0;
          p->bfactor = 1;
          break;
        case 0:
          root->bfactor = 0;
          p->bfactor = 0;
          break;
        case 1:
          root->bfactor = -1;
          p->bfactor = 0;
      }
      w->bfactor = 0;
      rotateToRight(p);
      root->right = p;
      rotateToLeft(root);
      break;
    //line 39-41: if bfactor is equivalent to zero a logic error has occured and something went wrong with program
    case 0:
      rotateToLeft(root);
      p->bfactor = 1;
      root->bfactor = -1;
      break;
    //line 43-46: if bfactor is 1 the appropriate bfactors are assumed and the correct rotation functions are called
    case 1:
      root->bfactor = 0;
      p->bfactor = 0;
      rotateToLeft(root);
  }
}
 /*
  Name: void balanceFromLeft(BinaryNode* &root);
  Return Type: NULL
  Functionality: Calls the appropriate rotate functions in order to maintain AVL status
  Uses: rotateToLeft(), rotateToRight()
*/
void AVLTree::balanceFromLeft(BinaryNode* &root){
  //temp BinaryNode
  BinaryNode *p;
  //temp BinaryNode
  BinaryNode *w;
  p = root->left;
  switch(p->bfactor){
   
    //line 63-67: if the tree is already left heavy the right rotation is called to balance the tree
    case -1:
      root->bfactor = 0;
      p->bfactor = 0;
      rotateToRight(root);
      break;
    //line 69-71: if bfactor == 0 a logic error has occured and something wrong went with program
    case 0:
      rotateToRight(root);
      p->bfactor = -1;
      root->bfactor = 1;
      break;
    //line 73-93: if the tree is right heavy the binary tree needs to be reformatted for AVL to be true
    case 1:
      w = p->right;
      switch(w->bfactor){
        case -1:
          root->bfactor = 1;
          p->bfactor = 0;
          break;
        case 0:
          root->bfactor =0;
          p->bfactor = 0;
          break;
        case 1:
          root->bfactor = 0;
          p->bfactor = -1;
          break;
      }
      w->bfactor = 0;
      rotateToLeft(p);
      root->left = p;
      rotateToRight(root);
  }
}
/*
  Name: void rotateToLeft(BinaryNode* &root);
  Return Type: NULL
  Functionality: Adjust the nodes in the binary tree to fit the definition of AVL
*/
void AVLTree::rotateToLeft(BinaryNode* &root){
  //temp BinaryNode
  BinaryNode* p;
  //line 82-84: if the root is null there is a logic error and something went wrong
  if(root == NULL){
    cout << "Error in the tree" << endl;
  }
  //line 86-88: if there is no right tree a logic error has occured and something went wrong in the code
  else if(root->right == NULL){
    cout << "Error in the tree: No right subtree to rotate." << endl;
  }
  //line 90-94: Left rotation of nodes in order for the definition of AVL to still remain true 
  else{
    p = root->right;
    root->right = p->left;
    p->left = root;
    root = p;
  }
}
/*
  Name: void rotateToRight(BinaryNode* &root);
  Return Type: NULL
  Functionality: Adjusts the nodes in the binary tree to fit the definition of AVL
  */
void AVLTree::rotateToRight(BinaryNode* &root){
  //tmp BinaryNode
  BinaryNode *p;
  //line 97-99: if the root is null something went wrong and the program should have never gotten to this point
  if(root == NULL){
    cout << "Error in the tree" << endl;
  }
  //line 101-103: if there is no left tree it is impossible to balance and something went wrong
  else if(root->left == NULL){
    cout << "Error in the tree: No left subtree to rotate" << endl;
  }
  //line 105-109: Right rotation to balance the tree in order to fit the definition of AVL
  else{
    cout << "HERE" << endl;
    p = root->left;
    root->left = p->right;
    p->right = root;
    root = p;
  }
}
/*
  Name: void insertIntoAVL(BinaryNode* &root, BinaryNode *newNode, bool& isTaller)
  Return Type: NULL
  Functionality: Inserts new Binary nodes and maintains the binary tree as an AVLTree
  Uses: balanceFromRight(), balanceFromLeft()
  */
void AVLTree::insertIntoAVL(BinaryNode* &root, BinaryNode *newNode, bool& isTaller){
  //line 111-114: sets the root to newNode if the root == NULL also serves as base case
  if(root == NULL){
    root = newNode;
    isTaller = true;
  }
  //line 116-118: Checks to see if the newNode->key is already in the AVLTree also serves as base case
  else if(root->key == newNode->key){
    cout << "No duplicates are allowed" << endl;
  }
  //if the root->key is less than the newNode key value
  else if(root->key > newNode->key){
    //recursive call to insertIntoAVL
    insertIntoAVL(root->left, newNode, isTaller);
    //checks to see if the isTaller is true
    if(isTaller){

      switch (root->bfactor)
      {
        //line 129-132: if the bfactor is -1 the tree needs balanced
        case -1:
          balanceFromLeft(root);
          isTaller = false;
          break;
        //line 134-137: if the bfactor is 0 the node is inserted but documented
        case 0:
          root->bfactor = -1;
          isTaller = true;
          break;
        //line 139-142: if the bfactor is right heavy the tree is balanced by the left insert
        case 1:
          root->bfactor = 0;
          isTaller = false;
          break;
      }
    }
  }
  //if the root->key is greater than the newNode key value
  else{
    //recursive call to insertIntoAVL()
    insertIntoAVL(root->right, newNode, isTaller);
    //if a node is inserted above isTaller == true
    if(isTaller){
      switch(root->bfactor){
        //line 154-157: if tree is left heavy the right insert balances it out to maintain AVL and bfactor goes back to zero
        case -1:
          root->bfactor = 0;
          isTaller = false;
          break;
        //line 159-162: if tree was originally balanced the right insert makes the tree then right heavy
        case 0:
          root->bfactor = 1;
          isTaller = true;
          break;
        //line 164-167: if tree is right heavy the tree will now need balanced due to the right insert
        case 1:
          balanceFromRight(root);
          isTaller = false;
          break;
      }
    }
  }
}
/*
  Name: void removeFromAVL(BinaryNode* &root, int key, bool& isTaller);
  Return Type:NULL
  Functionality: removes a node from the binary tree while remaining at AVL status
*/
void AVLTree::removeFromAVL(BinaryNode* &root, int key, bool& isTaller){
    //line 225- 228: base case that ends the recursion if the root goes to NULL
    if(root == NULL){
      cout << "Item not found" << endl;
      return;
    }
    //line 230-248: comparison operator that function similarly to a recursive sequential search
    //then handles balancing after removing
    else if(root->key >key){

      removeFromAVL(root->left, key, isTaller);
      if(isTaller){
        switch(root->bfactor){
          case -1:
            root->bfactor = 0;
            isTaller = false;
            break;
          case 0:
            root->bfactor = 1;
            isTaller = true;
            break;
          case 1:
            balanceFromRight(root);
            isTaller = false;
            break;
        }
      }
    }
    //line 252-270: comparison operator that function similarly to a recursive sequential search
    //then handles balancing after removing
    else if(key > root->key){
      removeFromAVL(root->right, key, isTaller);
      if(isTaller){
        switch(root->bfactor){
          case -1:
            balanceFromLeft(root);
            isTaller = false;
            break;
          case 0:
            root->bfactor = -1;
            isTaller = true;
            break;
          case 1:
            root->bfactor = 0;
            isTaller = false;
            break;
        }
      }
    }
    //if the node is found
    else{
      //temp node that will be used to traverse the tree
       BinaryNode* temp;
       //case 1 when the node to be deleted has no children
        if(root->left == NULL && root->right == NULL){
          temp = root;
          root = NULL;
          delete temp;
          isTaller = true;
        }
        //case 2 when the node to be deleted has no right child but a left child
        else if(root->right == NULL){
          root->key = root->left->key;
          delete root->left;
          root->left = NULL;
          isTaller =true;
        }
        //case 3 when the node to be deleted has no left child but a right child 
        else if(root->left == NULL){
          root->key = root->right->key;
          delete root->right;
          root->right = NULL;
        
          isTaller = true;
        }
        //case 4 when there are 2 children
        else{
          BinaryNode* trail;
          trail = NULL;
          temp = root->left;
          while(temp->right != NULL){
            trail = temp;
            temp = temp->right;
          }
          root->key = temp->key;
          isTaller = true;
          removeFromAVL(root->left, temp->key, isTaller);
          //line 209-330 handles removal of nodes in the special case of the root that has two nodes
          if(isTaller){
            switch(root->bfactor){
            case -1:
              root->bfactor = 0;
              isTaller = false;
              break;
            case 0:
              root->bfactor = 1;
              isTaller = true;
              break;
            case 1:
              balanceFromRight(root);
              if(root->left != NULL && getBalance(root->left) <= -1){
                balanceFromLeft(root->left);
              }
              if (root->left !=NULL && getBalance(root->left) >= 1){
                balanceFromRight(root->left);
              }
              isTaller = false;
              break;
           }
          }
        }
    }
}
/*
  Name: int getBalance(BinaryNode* &root);
  Return Type: int
  Functionality: subtracts the height of the right tree by the left tree
  */
int AVLTree::getBalance(BinaryNode* &root){
  //line 337-339: base case to end recursion
  if(root == NULL){
    return 0;
  }
  //line 341- 343: recursive call that finds the difference of the right tree and the left tree
  else{
    return findHeight(root->right) - findHeight(root->left);
  }

}
/*
  Name: void remove(int key);
  Return Type: void
  Functionality: Calls the removeFrom AVL Function
*/
void AVLTree::remove(int key){
  //sets isTaller to false to be fed into removeFromAVL
  bool isTaller = false;
  //removeFrom AVL call
  removeFromAVL(root, key, isTaller);
}
void AVLTree::insert(const int key) {
  //initiates isTaller to false since we have not inserted a node yet
  bool isTaller = false;
  //line 212-213: new BinaryNode that assumes the value of the key
  BinaryNode* tmp2;
  tmp2 = new BinaryNode(key);
  //call to insert
  insertIntoAVL(root, tmp2, isTaller);
}

/*
  Name: printInorder(BinaryNode* root)
  Return Type: void
  Functionality: recursive inorder traversal implementation for outputting
                 elements of the AVL Tree
  */
void AVLTree::printInorder(BinaryNode* root){
  //Line 40-42: Base case for recursive call
  if(root == NULL){
    return;
  }
  //recursive call for traversing the left of the tree and their subtrees
  printInorder(root->left);
  //outputs the value in order
  cout << root->key << " ";
 
  //recursive call for traversing the right of the tree and their subtrees
  printInorder(root->right);
}
/*
  Name: heightInorder(BinaryNode* root)
  Return Type: void
  Functionality: Uses inorder traversal and prints out the key values
                 as well as the height that the node is situated at
  Uses: int findHeight(int x, int height, BinaryNode* root), BinaryNode* getRoot()
*/
void AVLTree::heightInorder(BinaryNode* root){
  //initiates height to one inorder to start counting from the root of the AVLTree
  int height = 1;
  //Line 58-60: base case that stops the inorder traversal
  if(root == NULL){
    return;
  }
  //recursive call to traverse to the left
  heightInorder(root->left);
  //used to find the height of node about to be outputted
  height = findHeight(root);
  //outputs the key value of the node as well as the height it is situated at
  cout << height << " ";
  //recursive call to traverse to the right
  heightInorder(root->right);
}
/*
  Name: int findHeight(int x, int height, BinaryNode* root)
  Return Type: int
  Functionality: finds the height of a node within a binary tree works similarly
                 to a recursive sequential search algorithm
  */
int AVLTree::findHeight(BinaryNode* root){
  //Line 53-55: Base case for recursive call
  if(root == NULL){
    return 0;
  }
  //line 427-429: Basecase for if the links have reach a cve of NULL
  if(root->left == NULL && root->right == NULL){
    return 1;
  }
  //line 431-444: recursive calls that calculate the the height of a given tree
  else{
    if(root->right == NULL){
      return 1 + findHeight(root->left);
    }
    else if(root->left == NULL){
      return 1 + findHeight(root->right);
    }
    else if(findHeight(root->left) < findHeight(root->right)){
      return 1 + findHeight(root->right);
    }
    else{
      return 1 + findHeight(root->left);
    }
  }
}
