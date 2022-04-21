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

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#include "Customer.h"
#include "Collectible.h"
#include "SearchTree.h"

using namespace std;

class Transaction {
public:
    Transaction();

    virtual ~Transaction() = default;

    virtual void execute(const vector<string>& v, Customer* c[], Collectible* type[],
        Collectible* store[], SearchTree* items, SearchTree& customers, int storeSize) const = 0;

    //----------------------- letterToIndex ------------------------------------
    // Converts letter input to correct Array index for access.
    // A = 0 & Z = 25; Accepts upper and lowercase values.
    // Preconditions: value passed is an alphabetical ASCII char.
    // Postconditions: returns integer value.
    int letterToIndex(char c) const;

    int storeHashTableFunction(vector<string>& v, int storeSize) const;
};


class Buy : public Transaction {
public:
    ~Buy();

    //----------------------- execute - Buy ------------------------------------
    // Checks transaction string for validity.
    // Increments count of Collectible in storeHashTable and items search tree.
    // Updates transaction history for customer that initiated the order.
    // Preconditions: None
    // Postconditions: Adds item to CollectibleStore. Adds transaction to
    //      customer history.
    void execute(const vector<string>& v, Customer* c[], Collectible* type[],
        Collectible* store[], SearchTree* items, SearchTree& customers, int storeSize) const;
};

class Sell : public Transaction {
public:
    ~Sell();

    //----------------------- execute - Sell -----------------------------------
    // Checks transaction string for validity.
    // Decrements count of Collectible in storeHashTable and items search tree.
    // Removes item from both if count = 0.
    // Updates transaction history for customer that initiated the order.
    // Preconditions: None
    // Postconditions: Removes item from CollectibleStore. Adds transaction to 
    //      customer history.
    void execute(const vector<string>& v, Customer* c[], Collectible* type[],
        Collectible* store[], SearchTree* items, SearchTree& customers, int storeSize) const;
};

class Display : public Transaction {
public:
    ~Display();

    //----------------------- execute - Display --------------------------------
    // Preconditions: None
    // Postconditions: Outputs the entire inventory of the store, including
    // the number of each item in inventory.
    void execute(const vector<string>& v, Customer* c[], Collectible* type[],
        Collectible* store[], SearchTree* items, SearchTree& customers, int storeSize) const;
};

class CustomerHistory : public Transaction {
public:
    ~CustomerHistory();

    //---------------------- execute - Customer --------------------------------
    // Prints transaction history for customer entry.
    // Preconditions: Input items are valid.
    // Postconditions: Prints transaction history for customer from id passed
    //      as input.
    void execute(const vector<string>& v, Customer* c[], Collectible* type[],
        Collectible* store[], SearchTree* items, SearchTree& customers, int storeSize) const;
};

class History : public Transaction {
public:
    ~History();

    //---------------------- execute - History ---------------------------------
    // Preconditions: None
    // Postconditions: Prints transaction history for all customers, with
    // the customers in alphabetical order.
    void execute(const vector<string>& v, Customer* c[], Collectible* type[],
        Collectible* store[], SearchTree* items, SearchTree& customers, int storeSize) const;
};

#endif /* TRANSACTION_H */