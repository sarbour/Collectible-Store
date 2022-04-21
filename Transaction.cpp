//---------------------------------------------------------------------------
// TRANSACTION.H
// Contains Transaction base class and derived subclasses
// for transaction options available in the CollectibleStore.
// Author: Arbour
//---------------------------------------------------------------------------
// Transaction Class: Parent class for transaction options to remove
// need for switch statement in calling transactions (e.g. Buy, Sell, etc.)
//
// Assumptions:
// Passed arguments begin with a letter idetentifier.
//---------------------------------------------------------------------------

#include "Transaction.h"

using namespace std;

Transaction::Transaction() {}

//----------------------- letterToIndex ------------------------------------
// Converts letter input to correct Array index for access.
// A = 0 & Z = 25; Accepts upper and lowercase values.
// Preconditions: value passed is an alphabetical ASCII char.
// Postconditions: returns integer value.
int Transaction::letterToIndex(char c) const {
    int i = toupper(c) - 65;
    return i;
}

//------------------ storeHashTableFunction ---------------------------------
// Creates and returns hash index based on input values.
// Preconditions: Valid input vector passed.
// Postconditions: returns index of item for storeHashTable.
int Transaction::storeHashTableFunction(vector<string>& v, int storeSize) const {
    int temp = 0;
    int addValue = 0;
    for (int i = 3; i < v.size(); i++) { // Skips type & quantity.
        addValue = pow(((int)v[i][0]), 3);
        temp += addValue;
    }
    temp %= storeSize;
    return temp;
}

//*************************************************************************
//----- BUY -------- BUY -------- BUY ---------- BUY ---------- BUY -------
//*************************************************************************

Buy::~Buy() {}

//----------------------- execute - Buy ------------------------------------
// Checks transaction string for validity.
// Increments count of Collectible in storeHashTable and items search tree.
// Updates transaction history for customer that initiated the order.
// Preconditions: None
// Postconditions: Adds item to CollectibleStore. Adds transaction to
//      customer history.
void Buy::execute(const vector<string>& v, Customer* c[], Collectible* type[],
	Collectible* store[], SearchTree* items, SearchTree& customers, int storeSize) const {
	vector<string> transaction = v;
	int customer = atoi(transaction[1].c_str());
	string transactionReceipt = transaction[0] + ", ";

	for (int i = 2; i < transaction.size(); i++) {
		transactionReceipt += transaction[i];
		transactionReceipt += ", ";
	}
	transactionReceipt.pop_back(); // removes ' '
	transactionReceipt.pop_back(); // removes ','

	c[customer]->addTransaction(transactionReceipt);

    vector<string> command = transaction;
    command.erase(command.begin()); // Removes 'B'
    command.erase(command.begin()); // Removes Customer ID
    command.insert(command.begin() + 1, "1");

    // Add Collectible to items SearchTree.
    // Takes first char from string stored in first cell.
    int typeIndex = letterToIndex((command[0])[0]);
    if (type[typeIndex] == nullptr){
        cout << "Invalid Input:" << endl;
        cout << transactionReceipt;
        return;
    }
    Collectible* newItem = type[typeIndex]->create();
    newItem->fill(command);
    items[typeIndex].insert(newItem);

    // Add Collectible to storeHashTable.
    int hashIndex = storeHashTableFunction(transaction, storeSize);
    int probe = 0;
    bool itemAdded = false;
    while (!itemAdded) {
        // Tests first location found to see if possible to insert.
        if (store[hashIndex] == nullptr) {
            store[hashIndex] = newItem;
            itemAdded = true;
        }
        // Tests if items is stored and a duplicate of existing item.
        // Increments count by # of new items if so.
        if (store[hashIndex] != nullptr
            && !store[hashIndex]->isDeleted()
            && *store[hashIndex] == *newItem) {
            store[hashIndex]->setCount(newItem->getCount() + 1);
            itemAdded = true;
        }
        // Tests if item is stored but previously deleted.
        else if (store[hashIndex] != nullptr
            && store[hashIndex]->isDeleted()) {
            delete store[hashIndex];
            store[hashIndex] = newItem;
            itemAdded = true;
        }
        probe++;
        hashIndex += (probe * probe); // Quadratic probing
        hashIndex %= storeSize;
    }
}

//*************************************************************************
//------ SELL ------- SELL ------- SELL -------- SELL -------- SELL -------
//*************************************************************************

Sell::~Sell() {}

//----------------------- execute - Sell -----------------------------------
// Checks transaction string for validity.
// Decrements count of Collectible in storeHashTable and items search tree.
// Removes item from both if count = 0.
// Updates transaction history for customer that initiated the order.
// Preconditions: None
// Postconditions: Removes item from CollectibleStore. Adds transaction to 
//      customer history.
void Sell::execute(const vector<string>& v, Customer* c[], Collectible* type[],
	Collectible* store[], SearchTree* items, SearchTree& customers, int storeSize) const {
    vector<string> transaction = v;
    int customer = atoi(transaction[1].c_str());
    string transactionReceipt = transaction[0] + ", ";

    for (int i = 2; i < transaction.size(); i++) {
        transactionReceipt += transaction[i];
        transactionReceipt += ", ";
    }
    transactionReceipt.pop_back(); // removes ' '
    transactionReceipt.pop_back(); // removes ','
    
    if (c[customer] == nullptr)
        return;

    c[customer]->addTransaction(transactionReceipt);

    vector<string> command = transaction;
    command.erase(command.begin()); // Removes 'S'
    command.erase(command.begin()); // Removes Customer ID
    command.insert(command.begin() + 1, "1");

    // Removes Collectible from items SearchTree.
    // Takes first char from string stored in first cell.
    int typeIndex = letterToIndex((transaction[0])[0]);
    if (type[typeIndex] == nullptr)
        return;
    Collectible* newItem = type[typeIndex]->create();
    newItem->fill(command);
    items[typeIndex].remove(*newItem);

    // Decrement/delete Collectible in storeHashTable.
    int hashIndex = storeHashTableFunction(transaction, storeSize);
    int probe = 0;
    bool itemRemoved = false;
    while (!itemRemoved) {
        // Tests first location found to see if possible to insert.
        if (store[hashIndex] == nullptr) {
            break;
        }
        // Tests if items is stored.
        // If so, decrements count and/or marks as deleted.
        if (store[hashIndex] != nullptr
            && !store[hashIndex]->isDeleted()
            && *store[hashIndex] == *newItem) {
            store[hashIndex]->setCount(store[hashIndex]->getCount() - 1);
            if (store[hashIndex]->getCount() == 0)
                store[hashIndex]->setDeleted(true);
            itemRemoved = true;
        }
        probe++;
        hashIndex += (probe * probe); // Quadratic probing
        hashIndex %= storeSize;
    }
}

//*************************************************************************
//-- DISPLAY ----- DISPLAY ----- DISPLAY ------ DISPLAY ----- DISPLAY -----
//*************************************************************************

Display::~Display() {}

//----------------------- execute - Display --------------------------------
// Preconditions: None
// Postconditions: Outputs the entire inventory of the store, including
// the number of each item in inventory.
void Display::execute(const vector<string>& v, Customer* c[], Collectible* type[],
	Collectible* store[], SearchTree* items, SearchTree& customers, int storeSize) const {

    // Display Coins, then Comics, then SportsCards.
    int M = letterToIndex('M');
    int C = letterToIndex('C');
    int S = letterToIndex('S');
    cout << "Coins:\n" << items[M] << endl;
    cout << "Comics:\n" << items[C] << endl;
    cout << "Sports Cards:\n" << items[S]<< endl;
}

//*************************************************************************
//---- CUST HISTORY ---------- CUST HISTORY ------------- CUST HISTORY ----
//*************************************************************************

CustomerHistory::~CustomerHistory() {}

//---------------------- execute - Customer --------------------------------
// Prints transaction history for customer entry.
// Preconditions: Input items are valid.
// Postconditions: Prints transaction history for customer from id passed
//      as input.
void CustomerHistory::execute(const vector<string>& v, Customer* c[], Collectible* type[],
	Collectible* store[], SearchTree* items, SearchTree& customers, int storeSize) const {

    vector<string> command = v;
    int customerID = atoi(command[1].c_str());

    if (c[customerID] != nullptr) {
        cout << "\n" << c[customerID]->name << ":" << endl;
        c[customerID]->printTransactions();
    }
}

//*************************************************************************
//-- HISTORY ----- HISTORY ----- HISTORY ------ HISTORY ----- HISTORY -----
//*************************************************************************

History::~History() {}

//---------------------- execute - History ---------------------------------
// Preconditions: None
// Postconditions: Prints transaction history for all customers, with
// the customers in alphabetical order.
void History::execute(const vector<string>& v, Customer* c[], Collectible* type[],
	Collectible* store[], SearchTree* items, SearchTree& customers, int storeSize) const {

    vector<Customer> customerList;
    for (int i = 0; i < 1000; i++) {
        if (c[i] != nullptr)
            customerList.push_back(*c[i]);
    }

    sort(customerList.begin(), customerList.end());

    cout << "\nCustomer History List:" << endl;

    for (int i = 0; i < customerList.size(); i++) {
        cout << customerList[i].name << ":" << endl;
        customerList[i].printTransactions();
        cout << "\n";
    }
}