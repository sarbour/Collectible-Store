//---------------------------------------------------------------------------
// CUSTOMER.H
// Customer class that tracks customer name, ID, and receipt of transaction
// history.
// Author: Arbour
//---------------------------------------------------------------------------
// Assumptions:
// New transaction input includes all necessary data for addition to history.
//---------------------------------------------------------------------------

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <iostream>
#include "SearchTree.h"

using namespace std;

class Customer {
public:
    int id;
    string name;

    Customer();

    ~Customer();

    void addTransaction(string s);

    void printTransactions();

    //-----------------------------  <   --------------------------------------
    // Determine if left Customer is less than right
    // Preconditions:   None
    // Postconditions:  true is returned if stored variable values are less than  
    //           right; false is returned otherwise.
    bool operator<(const Customer& right) const;

private:
    struct Node {
        string transaction = "";
        Node* nextPtr = nullptr;
    };
    Node* root;     // pointer to LinkedList of receipt of all transactions
};

#endif