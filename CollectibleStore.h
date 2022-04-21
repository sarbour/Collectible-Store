//---------------------------------------------------------------------------
// COLLECTIBLESTORE.H
// Collectible store that creates, stores, displays, and manipulates,
// collectible items in a registry. The system is also capable of displaying
// overall inventory, and specific customer data (e.g. transaction history)
// Author: Arbour
//---------------------------------------------------------------------------
// Collectible Class: Abstract factory that provides an interface
// for creating and storing objects of different types into the database.
//
// Assumptions:
// New object input includes all necessary data for addition to inventory.
//---------------------------------------------------------------------------

#ifndef COLLECTIBLESTORE_H
#define COLLECTIBLESTORE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Collectible.h"
#include "Customer.h"
#include "SearchTree.h"
#include "Transaction.h"

using namespace std;

class CollectibleStore {
    friend class Transaction;
    friend class Buy;
    friend class Sell;
    friend class Display;
    friend class CustomerHistory;
    friend class History;

public:
    //----------------------- Constructor -----------------------------------
    CollectibleStore();

    //------------------------ Destructor -----------------------------------
    // Traverses storeHashTable and calls destructor on all Collectible pointers
    // stored. Also calls destroyTree on item SearchTree.
    // Preconditions: None
    // Postconditions: All dynamically allocated memory on the heap
    //      is deallocated.
    ~CollectibleStore();

    //------------------------ buildStore ------------------------------------
    // Adds items to inventory from infile line-by-line.
    // Checks input items for validity. Skips item if invalid entry.
    // Preconditions: Input items are valid.
    // Postconditions: Item stored in CollectibleStore with correct count.
    void buildStore(ifstream& infile);

    //----------------------- addCustomers -----------------------------------
    // Adds customers to customerHashTable by ID number in input data.
    // Checks input items for validity. Skips item if invalid entry.
    // Preconditions: Input items are valid.
    // Postconditions: Customer(s) from input file stored in CollectibleStore.
    void addCustomers(ifstream& infile);

    //---------------------- executeCommands ---------------------------------
    // Executes Sell, Buy, Display, Customer and History commands.
    // Checks commands  for validity. Skips command if invalid entry.
    // Preconditions: Input items are valid.
    // Postconditions: Corresponding CollectibleStore manipulations are completed. 
    //      Display values are output as requested by command file.
    void executeCommands(ifstream& infile);

    //----------------------- readInputFile ------------------------------------
    // Reads input file into inputTable, stores values
    // comma-delimited until end of line and end of file consecutively.
    // Preconditions: Valid input file stream provided.
    // Postconditions: A vector of vectors storing separated input values returned.
    vector<vector<string>> readInputFile(ifstream& infile);

    //----------------------- letterToIndex ------------------------------------
    // Converts letter input to correct Array index for access.
    // A = 0 & Z = 25; Accepts upper and lowercase values.
    // Preconditions: value passed is an alphabetical ASCII char.
    // Postconditions: returns integer value.
    int letterToIndex(char c);

    void initializeTransactionTable();

    void initializeTypeTable();

    int storeHashTableFunction(vector<string>& v);

private:
    static const int typeTableSize = 26;
    static const int transactionTableSize = 26;
    static const int storeTableSize = 20011;    // Prime number storage value to assist in collisions
    static const int maxCustomers = 1000;

    SearchTree items[typeTableSize];   // Stores Collectible items for output

    SearchTree customers;              // For alphabetical output of Customer history

    Collectible* typeHashTable[typeTableSize] = {nullptr};    // Stores dummy objects for quick access

    Transaction* transactionHashTable[transactionTableSize] = {nullptr};  // Stores dummy objects for quick access

    Collectible* storeHashTable[storeTableSize] = {nullptr}; // Approx. 10000 value limit for O(1) efficiency.

    Customer* customerHashTable[maxCustomers] = {nullptr}; // Stores customer names (using ID as key)
};

#endif /* COLLECTIBLESTORE_H */