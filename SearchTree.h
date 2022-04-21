//---------------------------------------------------------------------------
// SEARCHTREE.H
// Binary search tree class (for Collectible objects)
// Author: Arbour (Modified code provided by Professor Olson)
//---------------------------------------------------------------------------
// SearchTree Class: Stores input values as nodes in a binary search
//		tree, arranged according to order provided by overloaded
//		operator< & operator == methods. Values that already exist in the
//		tree increase the count of that Node by the value inserted.
// 
// Assumptions:
// Values provided for storage are Collectibles that have a char type
// and are comparable to one another via operator< & operator==
//---------------------------------------------------------------------------

#ifndef SEARCHTREE_H
#define SEARCHTREE_H
#include "Collectible.h"

using namespace std;

class SearchTree {

	//---------------------------- << --------------------------------------
	// Overloaded output operator for class SearchTree.
	// Preconditions: outputTree must point to a SearchTree
	// Postconditions: the values in tree are printed inorder (ASCII)
	//		ascending, proceeded by their number of occurrences in the tree.
	friend ostream& operator<<(ostream& os, const SearchTree& outputTree);

private:
	//--------------------------- Node -------------------------------------
	// Node Struct: storage object containing Collectible, left, and right
	//		pointer, and counter variable.
	struct Node {
		Collectible* item;
		Node* leftChild;
		Node* rightChild;
		int count = 1;
		char type;

		//-------------------- Constructors ---------------------------------
		Node() {}

		Node(const Collectible& rootItem)
			:leftChild(nullptr), rightChild(nullptr) {
			*item = rootItem;
		}
		Node(const Collectible& rootItem, Node* leftPtr, Node* rightPtr)
			:leftChild(leftPtr), rightChild(rightPtr) {
			//*item = rootItem;
			item = new Collectible;
			*item = rootItem;
		}

		//---------------------- setItem ------------------------------------
		// Precondition: None
		// Postcondition: Sets Collectible stored to the item passed.
		void setItem(const Collectible& rootItem) {
			*item = rootItem;
		}

		//---------------------- getItem ------------------------------------
		// Precondition: None
		// Postcondition: Returns the value stored in Collectible.
		Collectible getItem() const {
			return *item;
		}

		//------------------ getLeftChildPtr ------------------------------------
		// Precondition: None
		// Postcondition: Returns the stored leftChild pointer.
		Node* getLeftChildPtr() const {
			return leftChild;
		}

		//------------------ getRightChildPtr ------------------------------------
		// Precondition: None
		// Postcondition: Returns the stored rightChild pointer.
		Node* getRightChildPtr() const {
			return rightChild;
		}

		//------------------ setLeftChildPtr ------------------------------------
		// Mutator method
		// Precondition: None
		// Postcondition: Sets the stored leftChild pointer.
		void setLeftChildPtr(Node* leftPtr) {
			leftChild = leftPtr;
		}

		//------------------ setRightChildPtr ------------------------------------
		// Mutator method
		// Precondition: None
		// Postcondition: Sets the stored rightChild pointer.
		void setRightChildPtr(Node* rightPtr) {
			rightChild = rightPtr;
		}
	};
	// Declaration of the pointer to root of SearchTree.
	Node* root;

protected:
	//---------------------------- copyTree ------------------------------------
	// Helper method for assignment operator.
	// Copies the tree rooted at oldTreeRoot and returns a pointer to the root of
	// 	   the copy.
	// Preconditions:   oldTreeRootPtr points to a tree
	// Postconditions:  oldTreeRootPtr is copied into *this
	Node* copyTree(const Node* oldTreeRoot) const;

	//-------------------------- insertHelper ----------------------------------
	// Helper method for insert operator.
	// Preconditions:   oldTreeRootPtr points to a tree
	// Postconditions:  returns True via test argument if successful in adding 
	//		(or incrementing) passed Collectible to the SearchTree.
	Node* insertHelper(Collectible* c, Node* &root);

	//--------------------------- destroyTree ----------------------------------
	// Helper method for destructor
	// Preconditions:   root for SearchTree passed.
	// Postconditions:  deletes Nodes in Search Tree.
	void destroyTree(Node* subTreePtr);

	//------------------------- retrieveHelper ---------------------------------
	// Helper method for retrieve
	// Preconditions:   root for SearchTree passed.
	// Postconditions:  returns pointer to Collectible passed. Returns nullptr
	//		if not found within the SearchTree.
	const Collectible* retrieveHelper(const Node* root, const Collectible& key) const;

	//------------------------ equalTreeHelper ---------------------------------
	// Helper method for operator== (and operator !=)
	// Preconditions:   None
	// Postconditions:  returns True if the values in each SearchTree passed
	//		are the same (including the number of occurrences in the Tree).
	bool equalTreeHelper(const Node* lhs, const Node* rhs);

	//-------------------------- outputHelper ----------------------------------
	// Helper method for operator<<
	// Preconditions:   None
	// Postconditions:  prints values to the screen from SearchTree
	//		as "value" "ocurrences"; sorted in ASCII order.
	ostream& outputHelper(ostream& os, const Node* root) const;

	//--------------------------- deleteNode -----------------------------------
	// Deletes node in Search Tree
	// Preconditions:   None
	// Postconditions:  decrements occurence of value passed from SearchTree
	//		if this is the last remaining in the SearchTree the value is deleted.
	Node* deleteNode(Collectible& c, Node* &root);

	Node* findMin(Node* root);

	Node* find(Collectible& c, Node* root);

	//--------------------------- deleteRoot -----------------------------------
	// Deletes root in Search Tree
	// Preconditions:   None
	// Postconditions:  Deletes root value.
	void deleteRoot(Node*& root);

	//---------------------- findAndDeleteMostLeft -----------------------------
	// Helper method for deleteNode
	// Preconditions:   None
	// Postconditions:  Deletes leftmost value from tree passed.
	Collectible* findAndDeleteMostLeft(Node*& root);

public:
	//-------------------------- Constructor ----------------------------------
	// Default constructor for class SearchTree
	// Preconditions:   None
	// Postconditions:  root pointer points to nullptr.
	SearchTree();

	//----------------------------- Copy --------------------------------------
	// Copy constructor for class SearchTree
	// Preconditions:   oldTree points to a SearchTree.
	// Postconditions:  if oldTree is empty, a tree is created with root equal
	//		to nullptr. If tree contains values, these are copied into new Tree.
	SearchTree(const SearchTree& oldTree);

	//-------------------------- Destructor -----------------------------------
	// Destructor for class SearchTree
	// Preconditions:   pointer points to memory on the heap
	// Postconditions:  Nodes stored in SearchTree are deallocated
	virtual ~SearchTree();

	//---------------------------- Insert --------------------------------------
	// Insert instance of Collectible to SearchTree
	// Preconditions:   Collectible value passed is valid
	// Postconditions:  Collectible is stored in SearchTree. If value already
	//		exists, the count is incremented.
	void insert(Collectible* item);

	//---------------------------- Remove --------------------------------------
	// Removes instance of Collectible from SearchTree
	// Preconditions:   Collectible value passed is valid
	// Postconditions:  Collectible is removed from SearchTree. If the count is
	//		greater than 1, the value is decremented. If the values is 1, the
	//		Node is deleted.
	bool remove(Collectible& key);

	//---------------------------- makeEmpty -----------------------------------
	// Removes all values from the SearchTree
	// Preconditions:   None
	// Postconditions:  Values in SearchTree are removed, leaving the root pointer.
	void makeEmpty();

	//---------------------------- retrieve ------------------------------------
	// Finds a Collectible in the SearchTree using a key stored in the parameter
	// Preconditions:   Parameter value is valid.
	// Postconditions:  Pointer to Collectible containing key is returned. If the
	//		isn't found, a nullptr is returned.
	const Collectible* retrieve(const Collectible& key) const;

	//------------------------------   =   -------------------------------------
	// overloaded assignment operator
	// Preconditions:   right pointer points to the root of a SearchTree.
	// Postconditions:  *this is assigned the same values rhs.
	const SearchTree& operator=(const SearchTree& rhs);

	//------------------------------   ==   ------------------------------------
	// determine if two SearchTrees are equal
	// Preconditions:   right pointer points to the root of a SearchTree.
	// Postconditions:  returns true if the SearchTrees have the same values
	//		with the same count, in the same configuration.
	//*********************** METHOD NOT COMPLETE ******************************
	bool operator==(const SearchTree& rhs);

	//------------------------------   !=   ------------------------------------
	// determine if two SearchTrees are not equal
	// Preconditions:   right pointer points to the root of a SearchTree.
	// Postconditions:  returns true if the SearchTrees do not have the same
	//		values with the same count, in the same configuration.
	//*********************** METHOD NOT COMPLETE ******************************
	//				  (Logic is dependent on operator==)
	bool operator!=(const SearchTree& rhs);
};

#endif
