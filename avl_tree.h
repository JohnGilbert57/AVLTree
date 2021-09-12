#ifndef AVL_TREE_H
#define AVL_TREE_H

struct BinaryNode {
  /*
  Name: BinaryNode(const int key)
  Return Type: Constructor
  Functionality: Constructor used to set values for a new node within the 
                 AVL Tree. Used when declaring any BinaryNode object
  */
  BinaryNode(const int key) : key(key), left(NULL), right(NULL),bfactor(0) {}
  /*
  Name: ~BinaryNode()
  Return Type: Destructor
  Functionailty: Frees up used memory by the nodes used to build the binary nodes
  */
  ~BinaryNode() {
    delete left;
    delete right;
    left = right = NULL;
  }
  //used as a data field for each node
  int key;
  //declares left and right pointers for building the binary tree
  BinaryNode *left, *right;
  int bfactor;
};

class AVLTree {

public:
  /*
  Name: AVLTree
  Return Type: Constructor
  Functionality: used to instantiate an AVLTree variable and sets the root to NULL
  */
  AVLTree() : root(NULL) {}
  /*
  Name: ~AVLTree()
  Return Type: Destructor
  Functionality: is used to free up memory occupied by the AVL Tree
  */
  ~AVLTree() { 
    delete root;
  }

  void insert(const int key);
  /*
  Name: printInorder(BinaryNode* root)
  Return Type: void
  Functionality: recursive inorder traversal implementation for outputting
                 elements of the AVL Tree
  */
  void printInorder(BinaryNode* root);
  /*
  Name: heightInorder(BinaryNode* root)
  Return Type: void
  Functionality: Uses inorder traversal and prints out the key values
                 as well as the height that the node is situated at
  Uses: int findHeight(int x, int height, BinaryNode* root), BinaryNode* getRoot()
  */
  void heightInorder(BinaryNode* root);
  /*
  Name: int findHeight(int x, int height, BinaryNode* root)
  Return Type: int
  Functionality: finds the height of a node within a binary tree works similarly
                 to a recursive sequential search algorithm
  */
  int findHeight(BinaryNode* root);
  /*
  Name: BinaryNode* getRoot()
  Return Type: BinaryNode*
  Functionality: returns the root node of an AVLTree
  */
  BinaryNode* getRoot(){return root;}
  /*
  Name: void insertIntoAVL(BinaryNode* &root, BinaryNode *newNode, bool& isTaller)
  Return Type: NULL
  Functionality: Inserts new Binary nodes and maintains the binary tree as an AVLTree
  Uses: balanceFromRight(), balanceFromLeft()
  */
  void insertIntoAVL(BinaryNode* &root, BinaryNode *newNode, bool& isTaller);
  /*
  Name: void balanceFromRight(BinaryNode* &root);
  Return Type: NULL
  Functionality: Calls appropriate rotate function in order to maintain AVL status
  Uses: rotateToLeft(), rotateToRight()
  */
  void balanceFromRight(BinaryNode* &root);
  /*
  Name: void balanceFromLeft(BinaryNode* &root);
  Return Type: NULL
  Functionality: Calls the appropriate rotate functions in order to maintain AVL status
  Uses: rotateToLeft(), rotateToRight()
  */
  void balanceFromLeft(BinaryNode* &root);
  /*
  Name: void rotateToLeft(BinaryNode* &root);
  Return Type: NULL
  Functionality: Adjust the nodes in the binary tree to fit the definition of AVL
  */
  void rotateToLeft(BinaryNode* &root);
  /*
  Name: void rotateToRight(BinaryNode* &root);
  Return Type: NULL
  Functionality: Adjusts the nodes in the binary tree to fit the definition of AVL
  */
  void rotateToRight(BinaryNode* &root);
  /*
  Name: void removeFromAVL(BinaryNode* &root, int key, bool& isTaller);
  Return Type:NULL
  Functionality: removes a node from the binary tree while remaining at AVL status
  */
  void removeFromAVL(BinaryNode* &root, int key, bool& isTaller);
  /*
  Name: void remove(int key);
  Return Type: void
  Functionality: Calls the removeFrom AVL Function
  */
  void remove(int key);
  /*
  Name: int getBalance(BinaryNode* &root);
  Return Type: int
  Functionality: subtracts the height of the right tree by the left tree
  */
  int getBalance(BinaryNode* &root);
private:
  //pointer variable used to build the AVLTree
  BinaryNode* root;
};

#endif
