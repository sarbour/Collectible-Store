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

#include "CollectibleStore.h"

//----------------------- Constructor -----------------------------------
CollectibleStore::CollectibleStore() {
    initializeTransactionTable();
    initializeTypeTable();
}

//----------------------- letterToIndex ------------------------------------
// Converts letter input to correct Array index for access.
// A = 0 & Z = 25; Accepts upper and lowercase values.
// Preconditions: value passed is an alphabetical ASCII char.
// Postconditions: returns integer value.
int CollectibleStore::letterToIndex(char c) {
    int i = toupper(c) - 65;
    return i;
}

//------------------- InitializeTransactionTable  ------------------------------
// Stores Transaction objects in table for hashing.
// Preconditions: N/A
// Postconditions: Subclasses of Transaction stored as Transaction
//      pointers in transactionHashTable[].
void CollectibleStore::initializeTransactionTable() {
    int B = letterToIndex('B');
    Buy* dummyBuy = new Buy;
    Transaction* storeB = dynamic_cast<Transaction*>(dummyBuy);
    transactionHashTable[B] = storeB; // A-Z stored from 0-25 in HashTable.

    int S = letterToIndex('S');
    Sell* dummySell = new Sell;
    Transaction* storeS = dynamic_cast<Transaction*>(dummySell);
    transactionHashTable[S] = storeS;

    int D = letterToIndex('D');
    Display* dummyDisplay = new Display;
    Transaction* storeD = dynamic_cast<Transaction*>(dummyDisplay);
    transactionHashTable[D] = storeD;

    int C = letterToIndex('C');
    CustomerHistory* dummyCustomerHistory = new CustomerHistory;
    Transaction* storeC = dynamic_cast<Transaction*>(dummyCustomerHistory);
    transactionHashTable[C] = storeC;

    int H = letterToIndex('H');
    History* dummyHistory = new History;
    Transaction* storeH = dynamic_cast<Transaction*>(dummyHistory);
    transactionHashTable[H] = storeH;
}


//----------------------- InitializeTypeTable  ---------------------------------
// Stores dummy Type objects in table for hashing.
// Preconditions: N/A
// Postconditions: Subclasses of Collectible stored as Collectible
//      pointers in typeHashTable[].
void CollectibleStore::initializeTypeTable() {
    int M = letterToIndex('M');
    Coin* dummyCoin = new Coin;
    Collectible* storeCoin = dynamic_cast<Collectible*>(dummyCoin);
    typeHashTable[M] = storeCoin; // A-Z stored from 0-25 in HashTable.

    int C = letterToIndex('C');
    Comic* dummyComic = new Comic;
    Collectible* storeComic = dynamic_cast<Collectible*>(dummyComic);
    typeHashTable[C] = storeComic; // A-Z stored from 0-25 in HashTable.

    int S = letterToIndex('S');
    SportsCard* dummySportsCard = new SportsCard;
    Collectible* storeSportsCard = dynamic_cast<Collectible*>(dummySportsCard);
    typeHashTable[S] = storeSportsCard; // A-Z stored from 0-25 in HashTable.
}

//--------------------------- Destructor ---------------------------------------
// Traverses storeHashTable and calls destructor on all Collectible pointers
// stored. Also calls destroyTree on item SearchTree.
// Preconditions: None
// Postconditions: All dynamically allocated memory on the heap
//      is deallocated.
CollectibleStore::~CollectibleStore() {
    for (int i = 0; i < storeTableSize; i++){
        if(storeHashTable[i] != nullptr)
            delete storeHashTable[i];
    }

    for (int i = 0; i < typeTableSize; i++) {
        if (typeHashTable[i] != nullptr)
            delete typeHashTable[i];
    }

    for (int i = 0; i < transactionTableSize; i++) {
        if (transactionHashTable[i] != nullptr)
            delete transactionHashTable[i];
    }

    for (int i = 0; i < maxCustomers; i++) {
        if (customerHashTable[i] != nullptr)
            delete customerHashTable[i];
    }
}

//------------------------ buildStore ------------------------------------
// Adds items to inventory from infile line-by-line.
// Checks input items for validity. Skips item if invalid entry.
// Preconditions: Input items are valid.
// Postconditions: Item stored in CollectibleStore with correct count.
void CollectibleStore::buildStore(ifstream& infile) {
    vector<vector<string>> inputTable;
    inputTable = readInputFile(infile);

    for (int i = 0; i < inputTable.size(); i++) {
        // Takes first char from string stored in first cell.
        int typeIndex = letterToIndex( (inputTable[i][0])[0] );
        if (typeHashTable[typeIndex] == nullptr) {
            string transactionReceipt = "";
            for (int j = 0; j < inputTable[i].size(); j++){
                transactionReceipt += inputTable[i][j];
                transactionReceipt += ", ";
            }
            transactionReceipt.pop_back();
            transactionReceipt.pop_back();
            cout << "Invalid Input:" << endl;
            cout << transactionReceipt;
            continue;
        }
        Collectible* newItem = typeHashTable[typeIndex]->create();
        newItem->fill(inputTable[i]);
        items[typeIndex].insert(newItem);

        int hashIndex = storeHashTableFunction(inputTable[i]);
        int probe = 0;
        bool itemAdded = false;
        while (!itemAdded) {
            // Tests first location found to see if possible to insert.
            if (storeHashTable[hashIndex] == nullptr) {
                storeHashTable[hashIndex] = newItem;
                itemAdded = true;
                break;
            }
            // Tests if items is stored and a duplicate of existing item.
            // Increments count by # of new items if so.
            if (storeHashTable[hashIndex] != nullptr
                && !storeHashTable[hashIndex]->isDeleted()
                && storeHashTable[hashIndex] == newItem) {
                storeHashTable[hashIndex]->setCount(newItem->getCount());
                itemAdded = true;
            }
            // Tests if item is stored but previously deleted.
            else if(storeHashTable[hashIndex] != nullptr
                && storeHashTable[hashIndex]->isDeleted()) {
                delete storeHashTable[hashIndex];
                storeHashTable[hashIndex] = newItem;
                itemAdded = true;
            }
            probe++;
            hashIndex += (probe*probe); // Quadratic probing
            hashIndex %= storeTableSize;
        }
    }
}

//------------------ storeHashTableFunction ---------------------------------
// Creates and returns hash index based on input values.
// Preconditions: Valid input vector passed.
// Postconditions: returns index of item for storeHashTable.
int CollectibleStore::storeHashTableFunction(vector<string>& v) {
    int temp = 0;
    int addValue = 0;
    for (int i = 2; i < v.size(); i++) { // Skips type & quantity.
        addValue = pow(((int)v[i][0]), 3);
        temp += addValue;
    }
    temp %= storeTableSize;
    return temp;
}

//----------------------- readInputFile ------------------------------------
// Reads input file into inputTable, stores values
// comma-delimited until end of line and end of file consecutively.
// Preconditions: Valid input file stream provided.
// Postconditions: A vector of vectors storing separated input values returned.
vector<vector<string>> CollectibleStore::readInputFile(ifstream& infile) {
    vector<vector<string>> inputTable;
    vector<string> inputLine;
    string description;
    string s;

    while (infile.peek() != EOF) {
        if (infile.eof()) break;
        getline(infile, description, '\n'); //get line of info

        stringstream ss(description);
        while (ss.peek() != EOF) {
            getline(ss, s, ',');
            if (s[0] == ' ')
                s.erase(0, 1);
            inputLine.push_back(s);
        }
        inputTable.push_back(inputLine);
        inputLine.clear();
    }

    /*
    Uncomment to print input/commands to screen
    */
    //for (int i = 0; i < inputTable.size(); i++) {
    //    string test = "";
    //    for (int j = 0; j < inputTable[i].size(); j++) {
    //        test += inputTable[i][j];
    //        test += ", ";
    //    }
    //    test.pop_back();
    //    test.pop_back();
    //    cout << test << "\n";
    //}

    return inputTable;
}

//----------------------- addCustomers -----------------------------------
// Adds customers to customerHashTable by ID number in input data.
// Checks input items for validity. Skips item if invalid entry.
// Preconditions: Input items are valid.
// Postconditions: Customer(s) from input file stored in CollectibleStore.
void CollectibleStore::addCustomers(ifstream& infile) {
    vector<vector<string>> inputTable;
    inputTable = readInputFile(infile);

    for (int i = 0; i < inputTable.size(); i++) {
        int custID = atoi(inputTable[i][0].c_str());
        Customer* storeCustomer = new Customer;
        if(inputTable[i].size() == 2)
            storeCustomer->name = inputTable[i][1];
        customerHashTable[custID] = storeCustomer;
    }
}

//---------------------- executeCommands ---------------------------------
// Executes Sell, Buy, Display, Customer and History commands.
// Checks commands  for validity. Skips command if invalid entry.
// Preconditions: Input items are valid.
// Postconditions: Corresponding CollectibleStore manipulations are completed. 
//      Display values are output as requested by command file.
void CollectibleStore::executeCommands(ifstream& infile) {
    vector<vector<string>> inputTable;
    inputTable = readInputFile(infile);

    for (int i = 0; i < inputTable.size(); i++) {
        // Takes first char from string stored in first cell.
        int transactionIndex = letterToIndex((inputTable[i][0])[0]);
        if (transactionHashTable[transactionIndex] == nullptr){
            string transactionReceipt = "";
            for (int j = 0; j < inputTable[i].size(); j++) {
                transactionReceipt += inputTable[i][j];
                transactionReceipt += ", ";
            }
            transactionReceipt.pop_back();
            transactionReceipt.pop_back();
            cout << "Invalid Input:" << endl;
            cout << transactionReceipt << endl;
            continue;
        }
        transactionHashTable[transactionIndex]->execute(inputTable[i], 
            customerHashTable, typeHashTable, storeHashTable, items, customers, storeTableSize);
    }
}