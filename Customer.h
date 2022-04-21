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

class Customer{
public:
    Customer();
    int id;
    string name;

private:
    struct Node{
        string transaction;
        Node* nextPtr;
    };
    Node* root;     // pointer to LinkedList of receipt of all transactions
};

#endif