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
#include <string>
#include "Collectible.h"
#include "CollectibleStore.h"
#include "Customer.h"

using namespace std;

class CollectibleStore{
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

    //-------------------------- getItem ------------------------------------
	// Preconditions: None
	// Postconditions: Returns pointer to Collectible.
    Collectible* getItem();

    //---------------------------- buy --------------------------------------
	// Checks transaction string for validity.
    // Increments count of Collectible in storeHashTable and items search tree.
    // Updates transaction history for customer that initiated the order.
	// Preconditions: None
	// Postconditions: Adds item to CollectibleStore. Adds transaction to
    //      customer history.
    void buy(string transaction);

    //--------------------------- sell --------------------------------------
    // Checks transaction string for validity.
	// Decrements count of Collectible in storeHashTable and items search tree.
    // Removes item from both if count = 0.
    // Updates transaction history for customer that initiated the order.
	// Preconditions: None
	// Postconditions: Removes item from CollectibleStore. Adds transaction to 
    //      customer history.
    void sell(string transaction);

    //------------------------ buildStore ------------------------------------
    // Adds items to inventory from infile line-by-line.
    // Checks input items for validity. Skips item if invalid entry.
	// Preconditions: Input items are valid.
	// Postconditions: Item stored in CollectibleStore with correct count.
    void buildStore(ifstream &infile){
        for (each line of input){
            create new Collectible (using subclass)
            set count
            set stored variables

            set hashed pointer in storeHashTable to point to Collectible
            add Collectible to search tree
        }

    }

    //----------------------- addCustomers -----------------------------------
    // Adds customers to customerHashTable by ID number in input data.
    // Checks input items for validity. Skips item if invalid entry.
	// Preconditions: Input items are valid.
	// Postconditions: Customer(s) from input file stored in CollectibleStore.
    void addCustomers(ifstream &infile){
        for (each line of input){
            create new Customer
            store customer name
    };

    //---------------------- executeCommands ---------------------------------
    // Executes Sell, Buy, Display, Customer and History commands.
    // Checks commands  for validity. Skips command if invalid entry.
	// Preconditions: Input items are valid.
	// Postconditions: Corresponding CollectibleStore manipulations are completed. 
    //      Display values are output as requested by command file.
    void executeCommands(ifstream &infile){
        accesses command table based on input
        calls stored method based on input varible (e.g. S, B, D, C, H)
    };

    //----------------------- printCustomer ----------------------------------
    // Prints transaction history for customer entry.
	// Preconditions: Input items are valid.
	// Postconditions: Prints transaction history for customer from id passed
    //      as input.
    void printCustomer(int id) const{
        prints customer and id
        visits transactions LinkedList and prints iteratively until end
    };
    
    //----------------------- printHistory ----------------------------------
	// Preconditions: None
	// Postconditions: Prints transaction history for all customers, with
    // the customers in alphabetical order.
    void printHistory() const;

    //-------------------------- display -------------------------------------
	// Preconditions: None
	// Postconditions: Outputs the entire inventory of the store, including
    // the number of each item in inventory.
    void display() const{
        inorder traversal of items SearchTree;
        print item (ordered on insertion based on <, > , ==, != operators)
    }

    private:
    SearchTree items;   // Stores Collectible items for output 

    static const int commandTableSize = 26;
    string commandHashTable[commandTableSize];  // Stores dummy objects for quick access

    static const int typeTableSize = 26;
    string typeHashTable[typeTableSize];    // Stores dummy objects for quick access

    static const int storeTableSize = 223;       // Prime number storage value to assist in collisions
    Collectible* storeHashTable[storeTableSize]; // Approx. 100 value limit for O(1) efficiency.

    static const int maxCustomers = 1000;
    Customer* customerHashTable[maxCustomers]; // Stores customer names (using ID as key)
};

#endif /* COLLECTIBLESTORE_H */