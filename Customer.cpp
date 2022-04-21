#include "Customer.h"

using namespace std;

Customer::Customer() {}

Customer::~Customer() {

}

void Customer::addTransaction(string s) {
	Node* nn = new Node;
	nn->transaction = s;

	if (root == nullptr)
		root = nn;

	else if (root->nextPtr == nullptr)
		root->nextPtr = nn;

	else if (root->nextPtr != nullptr) {
		Node* curr;
		curr = root->nextPtr;
		while (curr != nullptr) {
			curr = curr->nextPtr;
		}
		curr->nextPtr = nn;
	}
}

void Customer::printTransactions() {
	if (root == nullptr){
		cout << "No Transaction History" << endl;
		return;
	}
	Node* curr = root;
	while (curr->nextPtr != nullptr){
		cout << curr->transaction;	// Prints intermediate list items.
		cout << "\n";
		curr = curr->nextPtr;
	}
	cout << curr->transaction << "\n";	// Prints last item in list.
}

//-----------------------------  <   --------------------------------------
// Determine if left Collectible is less than right
// Preconditions:   None
// Postconditions:  true is returned if stored variable values are less than  
//           right; false is returned otherwise
bool Customer::operator<(const Customer& right) const {
	if (_strcmpi(name.c_str(), right.name.c_str()) < 0)
		return true;
	return false;
}