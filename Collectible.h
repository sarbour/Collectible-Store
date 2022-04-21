//---------------------------------------------------------------------------
// COLLECTIBLE.H
// Stores item count, and provides methods for create, buy, sell, and output
// of the stored item types.
// Author: Arbour
//---------------------------------------------------------------------------
// Collectible Class: Abstract factory that provides an interface
// for creating and storing objects of different types into the database.
//
// Assumptions:
// New object input includes all necessary data for addition to inventory.
//---------------------------------------------------------------------------
#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H

#include <iostream>
#include <string>

using namespace std;

class Collectible {
public:
    //------------------------- Constructor ----------------------------------
    Collectible();

    //---------------------------- create ------------------------------------
    // This method is intended to be overridden by subclasses.
    // Preconditions: None
    // Postconditions: Returns a pointer to instantiated empty Collectible item.
    virtual Collectible* create();

    //----------------------------- clone -------------------------------------
    // This method is intended to be overridden by subclasses.
    // Preconditions: None
    // Postconditions: Returns pointer to deep copy of Collectible.
    virtual Collectible* clone(Collectible* c);

    //----------------------------- output -------------------------------------
    // This method is intended to be overridden by subclasses.
    // Preconditions: None
    // Postconditions: Returns count of Collectible cast to string.
    virtual string output();

    //-----------------------------  =  ---------------------------------------
	// Overloaded assignment operator
	// Preconditions:   None
	// Postconditions:  *this is assigned the same stored variables values as right
	const Collectible& operator=(const Collectible& right);

	//-----------------------------  ==  --------------------------------------
	// Determine if two Collectibles are equal.
	// Preconditions:   None
	// Postconditions:  true is returned if the Collectibles have the same 
	//          stored variable values and false is returned otherwise
	bool operator==(const Collectible& right) const;

	//-----------------------------  !=  --------------------------------------
	// Determine if two Collectibles are not equal.
	// Preconditions:   None
	// Postconditions:  false is returned if Collectibles have the same stored 
	//           varible values and true is returned otherwise
	bool operator!=(const Collectible& right) const;

	//-----------------------------  <   --------------------------------------
	// Determine if left Collectible is less than right
	// Preconditions:   None
	// Postconditions:  true is returned if stored variable values are less than  
	//           right; false is returned otherwise
	bool operator<(const Collectible& right) const;

	//-----------------------------  >   --------------------------------------
	// Determine if left Collectible is greater than right
	// Preconditions:   None
	// Postconditions:  true is returned if stored variable values are greater  
	//           than right; false is returned otherwise
	bool operator>(const Collectible& right) const;

protected:
    bool deleted;   // Used for lazy deletion within storeHashMap
    int count;
};

class Coin : public Collectible{
public:
    string type;
    int year;
    int grade;
    
    //---------------------------- create ------------------------------------
    // Preconditions: None
    // Postconditions: Returns a Collectible pointer to instantiated
    // subclass item.
    void create(string typeIn, int yearIn, int gradeIn);

    //----------------------------- clone -------------------------------------
    // Preconditions: None
    // Postconditions: Returns Collectible pointer to deep copy of Coin subclass.
    Collectible* clone(Coin* c);

    //----------------------------- output -------------------------------------
    // Preconditions: Instance of Coin object called.
    // Postconditions: Returns string of formatted Coin data.
    string output() const;

    //-----------------------------  =  -----------------------------------------
	// Overloaded assignment operator
	// Preconditions:   None
	// Postconditions:  *this is assigned the same stored variables values as right
	const Coin& operator=(const Coin& right);

	//-----------------------------  ==  ----------------------------------------
	// Determine if two Coins are equal.
	// Preconditions:   None
	// Postconditions:  true is returned if the Coins have the same 
	//          stored variable values and false is returned otherwise
	bool operator==(const Coin& right) const;

	//-----------------------------  !=  ----------------------------------------
	// Determine if two Coins are not equal.
	// Preconditions:   None
	// Postconditions:  false is returned if Coins have the same stored 
	//           varible values and true is returned otherwise
	bool operator!=(const Coin& right) const;

	//-----------------------------  <   ----------------------------------------
	// Determine if left Coin is less than right
	// Preconditions:   None
	// Postconditions:  true is returned if stored variable values are less than  
	//           right; false is returned otherwise
	bool operator<(const Coin& right) const;

	//-----------------------------  >   ----------------------------------------
	// Determine if left Coin is greater than right
	// Preconditions:   None
	// Postconditions:  true is returned if stored variable values are greater  
	//           than right; false is returned otherwise
	bool operator>(const Coin& right) const;
};

class Comic : public Collectible{
public:
    string publisher;
    string title;
    int year;
    string grade;

    //---------------------------- create ------------------------------------
    // Preconditions: None
    // Postconditions: Returns a Collectible pointer to instantiated
    // subclass item.
    void create(string publisherIn, string titleIn, int yearIn, string gradeIn);

    //----------------------------- clone -------------------------------------
    // Preconditions: None
    // Postconditions: Returns Collectible pointer to deep copy of Comic subclass.
    Collectible* clone(Comic* c);

    //----------------------------- output -------------------------------------
    // Preconditions: Instance of Comic object called.
    // Postconditions: Returns string of formatted Comic data.
    string output() const;

    //-----------------------------  =  -----------------------------------------
	// Overloaded assignment operator
	// Preconditions:   None
	// Postconditions:  *this is assigned the same stored variables values as right
	const Comic& operator=(const Comic& right);

	//-----------------------------  ==  ----------------------------------------
	// Determine if two Comics are equal.
	// Preconditions:   None
	// Postconditions:  true is returned if the Comics have the same 
	//          stored variable values and false is returned otherwise
	bool operator==(const Comic& right) const;

	//-----------------------------  !=  ----------------------------------------
	// Determine if two Comics are not equal.
	// Preconditions:   None
	// Postconditions:  false is returned if Comics have the same stored 
	//           varible values and true is returned otherwise
	bool operator!=(const Comic& right) const;

	//-----------------------------  <   ----------------------------------------
	// Determine if left Comic is less than right
	// Preconditions:   None
	// Postconditions:  true is returned if stored variable values are less than  
	//           right; false is returned otherwise
	bool operator<(const Comic& right) const;

	//-----------------------------  >   ----------------------------------------
	// Determine if left Comic is greater than right
	// Preconditions:   None
	// Postconditions:  true is returned if stored variable values are greater  
	//           than right; false is returned otherwise
	bool operator>(const Comic& right) const;
};

class SportsCard : public Collectible{
public:
    string player;
    int year;
    string mfr;
    
    //---------------------------- create ------------------------------------
    // Preconditions: None
    // Postconditions: Returns a Collectible pointer to instantiated
    // subclass item.
    void create(string playerIn, int yearIn, string mfrIn);

    //----------------------------- clone -------------------------------------
    // Preconditions: None
    // Postconditions: Returns Collectible pointer to deep copy of SportsCard subclass.
    Collectible* clone(SportsCard* c);
    
    //----------------------------- output -------------------------------------
    // Preconditions: Instance of SportsCard object called.
    // Postconditions: Returns string of formatted SportsCard data.
    string output() const;

    //-----------------------------  =  -----------------------------------------
	// Overloaded assignment operator
	// Preconditions:   None
	// Postconditions:  *this is assigned the same stored variables values as right
	const SportsCard& operator=(const SportsCard& right);

	//-----------------------------  ==  ----------------------------------------
	// Determine if two SportsCards are equal.
	// Preconditions:   None
	// Postconditions:  true is returned if the SportsCards have the same 
	//          stored variable values and false is returned otherwise
	bool operator==(const SportsCard& right) const;

	//-----------------------------  !=  ----------------------------------------
	// Determine if two SportsCards are not equal.
	// Preconditions:   None
	// Postconditions:  false is returned if SportsCards have the same stored 
	//           varible values and true is returned otherwise
	bool operator!=(const SportsCard& right) const;

	//-----------------------------  <   ----------------------------------------
	// Determine if left SportsCard is less than right
	// Preconditions:   None
	// Postconditions:  true is returned if stored variable values are less than  
	//           right; false is returned otherwise
	bool operator<(const SportsCard& right) const;

	//-----------------------------  >   ----------------------------------------
	// Determine if left SportsCard is greater than right
	// Preconditions:   None
	// Postconditions:  true is returned if stored variable values are greater  
	//           than right; false is returned otherwise
	bool operator>(const SportsCard& right) const;
};

#endif //COLLECTIBLE_H