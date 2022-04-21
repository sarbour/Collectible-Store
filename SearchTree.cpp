//---------------------------------------------------------------------------
// SEARCHTREE.CPP
// Member function definitions for class SearchTree
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

#include "SearchTree.h"

//-------------------------- Constructor ----------------------------------
// Default constructor for class SearchTree
// Preconditions:   None
// Postconditions:  root pointer points to nullptr.
SearchTree::SearchTree()
	: root(nullptr) {}


//----------------------------- Copy --------------------------------------
// Copy constructor for class SearchTree
// Preconditions:   oldTree points to a SearchTree.
// Postconditions:  if oldTree is empty, a tree is created with root equal
//		to nullptr. If tree contains values, these are copied into new Tree.
SearchTree::SearchTree(const SearchTree& oldTree) {
	if (this != &oldTree)
	{
		this->makeEmpty();
		root = copyTree(oldTree.root);
	}
	//root = copyTree(oldTree.root);
}


//--------------------------- destroyTree ----------------------------------
// Helper method for destructor
// Preconditions:   root for SearchTree passed.
// Postconditions:  deletes Nodes in Search Tree.
void SearchTree::destroyTree(Node* subTreePtr) {
	if (subTreePtr != nullptr) {
		destroyTree(subTreePtr->getLeftChildPtr());
		destroyTree(subTreePtr->getRightChildPtr());
		delete subTreePtr;
		subTreePtr = nullptr;
	} // end if
} // end destroyTree


//-------------------------- Destructor -----------------------------------
// Destructor for class SearchTree
// Preconditions:   pointer points to memory on the heap
// Postconditions:  Nodes stored in SearchTree are deallocated
SearchTree::~SearchTree() {
	if (root != nullptr) {
		if (root->leftChild == nullptr &&
			root->rightChild == nullptr) {
			delete root;
		}
	}
	else
		destroyTree(root);
}


//---------------------------- makeEmpty -----------------------------------
// Removes all values from the SearchTree
// Preconditions:   None
// Postconditions:  Values in SearchTree are removed, leaving the root pointer.
void SearchTree::makeEmpty() {
	if (root == nullptr)
		return;
	else {
		destroyTree(root->getLeftChildPtr());
		destroyTree(root->getRightChildPtr());
	}
}


//-------------------------- insertHelper ----------------------------------
// Helper method for insert operator.
// Preconditions:   oldTreeRootPtr points to a tree
// Postconditions:  returns True via test argument if successful in adding 
//		(or incrementing) passed Collectible to the SearchTree.
SearchTree::Node* SearchTree::insertHelper(Collectible* c, Node* &root) {
	if (root == nullptr) {
		Node* nn = new Node;
		nn->item = c;
		nn->count = c->getCount();
		nn->leftChild = nullptr;
		nn->rightChild = nullptr;
		root = nn;
	}
	else if (*c == *root->item) {
		root->item->setCount(root->item->getCount() + 1);
		return nullptr;
	}
	else if (*c < *root->item)
		root->leftChild = insertHelper(c, root->leftChild);
	else if (*c > *root->item)
		root->rightChild = insertHelper(c, root->rightChild);
	else {
		root->count++;
	}
	return root;
	
	//if (root == nullptr) {
	//	Node* nn = new Node;
	//	nn->item = item;
	//	nn->count = item->getCount();
	//	nn->leftChild = nullptr;
	//	nn->rightChild = nullptr;
	//	root = nn;
	//	test = true;
	//}
	//else if (*item == *root->item) {
	//	root->item->setCount(item->getCount() + 1);
	//}
	//else if (*item < *root->item) {
	//	insertHelper(root->leftChild, item, test);
	//}
	//else if (*item > *root->item) {
	//	insertHelper(root->rightChild, item, test);
	//}
	//else {
	//	root->count++;
	//	test = false;
	//}
}


//---------------------------- Insert --------------------------------------
// Insert instance of Collectible to SearchTree
// Preconditions:   Collectible value passed is valid
// Postconditions:  Collectible is stored in SearchTree. If value already
//		exists, the count is incremented.
void SearchTree::insert(Collectible* item) {
	insertHelper(item, this->root);
}


//---------------------------- copyTree ------------------------------------
// Helper method for assignment operator.
// Copies the tree rooted at treePtr and returns a pointer to the root of
// 	   the copy.
// Preconditions:   oldTreeRootPtr points to a tree
// Postconditions:  oldTreeRootPtr is copied into *this
SearchTree::Node* SearchTree::copyTree(const Node* oldTreeRoot) const {
	Node* newTreePtr = nullptr;
	// Copy tree nodes during a preorder traversal
	if (oldTreeRoot != nullptr) {
		// Copy node
		newTreePtr = new Node(oldTreeRoot->getItem(), nullptr, nullptr);
		//newTreePtr->item = (oldTreeRoot->getItem());
		newTreePtr->setLeftChildPtr(copyTree(oldTreeRoot->getLeftChildPtr()));
		newTreePtr->setRightChildPtr(copyTree(oldTreeRoot->getRightChildPtr()));
	} // end if
	// Else tree is empty (newTreePtr is nullptr)
	return newTreePtr;
} // end copyTree


//------------------------------   =   -------------------------------------
// overloaded assignment operator
// Preconditions:   right pointer points to the root of a SearchTree.
// Postconditions:  *this is assigned the same values rhs.
const SearchTree& SearchTree::operator=(const SearchTree& rhs) {
	if (this != &rhs)
	{
		this->makeEmpty();
		root = copyTree(rhs.root);
	}
	return *this;
}


//------------------------- retrieveHelper ---------------------------------
// Helper method for retrieve
// Preconditions:   root for SearchTree passed.
// Postconditions:  returns pointer to Collectible passed. Returns nullptr
//		if not found within the SearchTree.
const Collectible* SearchTree::retrieveHelper(const Node* root, const Collectible& key) const {
	if (root == nullptr)
		return nullptr;
	else if (key == *root->item)
		return root->item;
	else if (key < *root->item)
		return retrieveHelper(root->leftChild, key);
	else
		return retrieveHelper(root->rightChild, key);
}


//---------------------------- retrieve ------------------------------------
// Finds a Collectible in the SearchTree using a key stored in the parameter
// Preconditions:   Parameter value is valid.
// Postconditions:  Pointer to Collectible containing key is returned. If the
//		isn't found, a nullptr is returned.
const Collectible* SearchTree::retrieve(const Collectible& key) const {
	return retrieveHelper(root, key);
}

//------------------------ equalTreeHelper ---------------------------------
// Helper method for operator== (and operator !=)
// Preconditions:   None
// Postconditions:  returns True if the values in each SearchTree passed
//		are the same (including the number of occurrences in the Tree).
//*********************** METHOD NOT COMPLETE ******************************
bool SearchTree::equalTreeHelper(const Node* lhs, const Node* rhs) {
	if (lhs == nullptr && rhs == nullptr)
		return true;
	if ((lhs == nullptr && rhs != nullptr) ||
		(lhs != nullptr && rhs == nullptr)) {
		return false;
	}
	if ((lhs->getItem() != rhs->getItem()) ||
		(lhs->count != rhs->count)) {
		return false;
	}
	return equalTreeHelper(lhs->getLeftChildPtr(), rhs->getLeftChildPtr()) &&
		equalTreeHelper(lhs->getRightChildPtr(), rhs->getRightChildPtr());
}


//------------------------------   ==   ------------------------------------
// determine if two SearchTrees are equal
// Preconditions:   right pointer points to the root of a SearchTree.
// Postconditions:  returns true if the SearchTrees have the same values
//		with the same count, in the same configuration.
bool SearchTree::operator==(const SearchTree& rhs) {
	return equalTreeHelper(root, rhs.root);
}


//------------------------------   !=   ------------------------------------
// determine if two SearchTrees are not equal
// Preconditions:   right pointer points to the root of a SearchTree.
// Postconditions:  returns true if the SearchTrees do not have the same
//		values with the same count, in the same configuration.
bool SearchTree::operator!=(const SearchTree& rhs) {
	return !(equalTreeHelper(root, rhs.root));
}

//---------------------------- Remove --------------------------------------
// Removes instance of Collectible from SearchTree
// Preconditions:   Collectible value passed is valid
// Postconditions:  Collectible is removed from SearchTree. If the count is
//		greater than 1, the value is decremented. If the values is 1, the
//		Node is deleted.
bool SearchTree::remove(Collectible& key) {
	Node* item = find(key, root);
	if (item->count > 2) {
		item->count--;
		return true;
	}
	if (item->count == 1) {
		deleteNode(key, root);
		return true;
	}
	return false;
}

//-------------------------- outputHelper ----------------------------------
// Helper method for operator<<
// Preconditions:   None
// Postconditions:  prints values to the screen from SearchTree
//		as "value" "ocurrences"; sorted in ASCII order.
ostream& SearchTree::outputHelper(ostream& os, const Node* root) const {
	if (root != nullptr) {
		outputHelper(os, root->leftChild);
		os << root->item->toString() << endl;
		outputHelper(os, root->rightChild);
	}
	return os;
}

//---------------------------- << --------------------------------------
// Overloaded output operator for class SearchTree.
// Preconditions: outputTree must point to a SearchTree
// Postconditions: the values in tree are printed inorder (ASCII)
//		ascending, proceeded by their number of occurrences in the tree.
ostream& operator<<(ostream& os, const SearchTree& outputTree) {
	outputTree.outputHelper(os, outputTree.root);
	return os;
}


//--------------------------- deleteNode -----------------------------------
// Deletes node in Search Tree
// Preconditions:   None
// Postconditions:  decrements occurence of value passed from SearchTree
//		if this is the last remaining in the SearchTree the value is deleted.
SearchTree::Node* SearchTree::deleteNode(Collectible& c, Node* &root)
{
	Node* temp;
	if (root == nullptr)
		return nullptr;
	else if (c < *root->item)
		root->leftChild = deleteNode(c, root->leftChild);
	else if (c > *root->item)
		root->rightChild = deleteNode(c, root->rightChild);
	else if (root->leftChild && root->rightChild)
	{
		temp = findMin(root->rightChild);
		root->item = temp->item;
		root->rightChild = deleteNode(*root->item, root->rightChild);
	}
	else
	{
		temp = root;
		if (root->leftChild == nullptr)
			root = root->rightChild;
		else if (root->rightChild == nullptr)
			root = root->leftChild;
		delete temp;
	}

	return root;
}

SearchTree::Node* SearchTree::findMin(Node* root)
{
	if (root == nullptr)
		return nullptr;
	else if (root->leftChild == nullptr)
		return root;
	else
		return findMin(root->leftChild);
}

SearchTree::Node* SearchTree::find(Collectible& c, Node* root) {
	if (root == nullptr)
		return nullptr;
	else if (c < *root->item)
		return find(c, root->leftChild);
	else if (c > *root->item)
		return find(c, root->rightChild);
	else
		return root;
}


//--------------------------- deleteRoot -----------------------------------
// Deletes root in Search Tree
// Preconditions:   None
// Postconditions:  Deletes root value.
void SearchTree::deleteRoot(Node*& root)
{
	delete root->item;

	if (root->leftChild == nullptr && root->rightChild == nullptr) {    // Not actually necessary
		delete root;
		root = nullptr;
	}
	else if (root->leftChild == nullptr || root->rightChild == nullptr) {
		Node* tmp = root;
		root = root->leftChild == nullptr ? root->rightChild : root->leftChild;
		delete tmp;
	}
	else {
		root->item = findAndDeleteMostLeft(root->rightChild);
	}
}

//---------------------- findAndDeleteMostLeft -----------------------------
// Helper method for deleteNode
// Preconditions:   None
// Postconditions:  Deletes leftmost value from tree passed.
Collectible* SearchTree::findAndDeleteMostLeft(Node*& root)
{
	if (root->leftChild == nullptr) {
		Collectible* item = root->item;
		Node* junk = root;
		root = root->rightChild;
		delete junk;
		return item;
	}
	else
		return findAndDeleteMostLeft(root->leftChild);
}
