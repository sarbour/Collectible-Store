//---------------------------------------------------------------------------
// COLLECTIBLE.H
// Stores item count, and provides methods for create, buy, sell, and toString
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
#include <vector>
#include <string>

using namespace std;

class Collectible {
public:
	//------------------------- Constructor ----------------------------------
	Collectible();

	//-------------------------- Destructor ----------------------------------
	virtual ~Collectible();

	//---------------------------- create ------------------------------------
	// This method is intended to be overridden by subclasses.
	// Preconditions: None
	// Postconditions: Returns a pointer to instantiated empty Collectible item.
	virtual Collectible* create();

	//----------------------------- clone -------------------------------------
	// This method is intended to be overridden by subclasses.
	// Preconditions: None
	// Postconditions: Returns pointer to deep copy of Collectible.
	virtual Collectible* clone();

	//----------------------------- fill -------------------------------------
	// To be overriden by descendent classes.
	// Preconditions: None
	// Postconditions: storage variables filled by input vector. 
	virtual void fill(vector<string>& v);

	//--------------------------- toString ------------------------------------
	// This method is intended to be overridden by subclasses.
	// Preconditions: None
	// Postconditions: Returns count of Collectible cast to string.
	virtual string toString() const;

	//--------------------------- isDeleted -------------------------------------
	// Getter for deleted value.
	// Preconditions: None
	// Postconditions: Returns boolean value for deleted.
	bool isDeleted() const;

	void setDeleted(bool input);

	int getCount() const {return count;}

	void setCount(int i) {count = i;}

	//-----------------------------  =  ---------------------------------------
	// Overloaded assignment operator
	// Preconditions:   None
	// Postconditions:  *this is assigned the same stored variables values as right
	virtual Collectible& operator=(const Collectible& right);

	//-----------------------------  ==  --------------------------------------
	// Determine if two Collectibles are equal.
	// Preconditions:   None
	// Postconditions:  true is returned if the Collectibles have the same 
	//          stored variable values and false is returned otherwise
	virtual bool operator==(const Collectible& right) const;

	//-----------------------------  !=  --------------------------------------
	// Determine if two Collectibles are not equal.
	// Preconditions:   None
	// Postconditions:  false is returned if Collectibles have the same stored 
	//           varible values and true is returned otherwise
	virtual bool operator!=(const Collectible& right) const;

	//-----------------------------  <   --------------------------------------
	// Determine if left Collectible is less than right
	// Preconditions:   None
	// Postconditions:  true is returned if stored variable values are less than  
	//           right; false is returned otherwise
	virtual bool operator<(const Collectible& right) const;

	//-----------------------------  >   --------------------------------------
	// Determine if left Collectible is greater than right
	// Preconditions:   None
	// Postconditions:  true is returned if stored variable values are greater  
	//           than right; false is returned otherwise
	virtual bool operator>(const Collectible& right) const;

protected:
	bool deleted = false;   // Used for lazy deletion within storeHashMap
	int count;
};

class Coin : public Collectible {
public:
	string type;
	int year;
	int grade;

	//---------------------------- create ------------------------------------
	// Preconditions: None
	// Postconditions: Returns a Collectible pointer to instantiated
	// subclass item.
	Collectible* create();

	//----------------------------- clone -------------------------------------
	// Preconditions: None
	// Postconditions: Returns Collectible pointer to deep copy of Coin subclass.
	Collectible* clone();

	//----------------------------- fill -------------------------------------
	// Fills coin with values from inputTable.
	// Preconditions: None
	// Postconditions: storage variables filled by input vector. 
	void fill(vector<string>& v);

	//--------------------------- toString ------------------------------------
	// Preconditions: Instance of Coin object called.
	// Postconditions: Returns string of formatted Coin data.
	string toString() const;

	//-----------------------------  =  -----------------------------------------
	// Overloaded assignment operator
	// Preconditions:   None
	// Postconditions:  *this is assigned the same stored variables values as right
	Collectible& operator=(const Collectible& right);

	//-----------------------------  ==  ----------------------------------------
	// Determine if two Coins are equal.
	// Preconditions:   None
	// Postconditions:  true is returned if the Coins have the same 
	//          stored variable values and false is returned otherwise
	bool operator==(const Collectible& right) const;

	//-----------------------------  !=  ----------------------------------------
	// Determine if two Coins are not equal.
	// Preconditions:   None
	// Postconditions:  false is returned if Coins have the same stored 
	//           varible values and true is returned otherwise
	bool operator!=(const Collectible& right) const;

	//-----------------------------  <   ----------------------------------------
	// Determine if left Coin is less than right
	// Preconditions:   None
	// Postconditions:  true is returned if stored variable values are less than  
	//           right; false is returned otherwise
	bool operator<(const Collectible& right) const;

	//-----------------------------  >   ----------------------------------------
	// Determine if left Coin is greater than right
	// Preconditions:   None
	// Postconditions:  true is returned if stored variable values are greater  
	//           than right; false is returned otherwise
	bool operator>(const Collectible& right) const;
};

class Comic : public Collectible {
public:
	string publisher;
	string title;
	int year;
	string grade;

	string getPublisher() {return publisher;}

	string getTitle() {return title;}

	int getYear() {return year;}

	string getGrade() {return grade;}

	//---------------------------- create --------------------------------------
	// Preconditions: None
	// Postconditions: Returns a Collectible pointer to instantiated
	// subclass item.
	Collectible* create();

	//----------------------------- clone --------------------------------------
	// Preconditions: None
	// Postconditions: Returns Collectible pointer to deep copy of Comic subclass.
	Collectible* clone();

	//----------------------------- fill ---------------------------------------
	// Fills comic with values from inputTable.
	// Preconditions: None
	// Postconditions: storage variables filled by input vector. 
	void fill(vector<string>& v);

	//--------------------------- toString -------------------------------------
	// Preconditions: Instance of Comic object called.
	// Postconditions: Returns string of formatted Comic data.
	string toString() const;

	//-----------------------------  =  ----------------------------------------
	// Overloaded assignment operator
	// Preconditions:   None
	// Postconditions:  *this is assigned the same stored variables values as right
	Collectible& operator=(const Collectible& right);

	//-----------------------------  ==  ---------------------------------------
	// Determine if two Comics are equal.
	// Preconditions:   None
	// Postconditions:  true is returned if the Comics have the same 
	//          stored variable values and false is returned otherwise
	bool operator==(const Collectible& right) const;

	//-----------------------------  !=  ---------------------------------------
	// Determine if two Comics are not equal.
	// Preconditions:   None
	// Postconditions:  false is returned if Comics have the same stored 
	//           varible values and true is returned otherwise
	bool operator!=(const Collectible& right) const;

	//-----------------------------  <   ---------------------------------------
	// Determine if left Comic is less than right
	// Preconditions:   None
	// Postconditions:  true is returned if stored variable values are less than  
	//           right; false is returned otherwise
	bool operator<(const Collectible& right) const;

	//-----------------------------  >   ----------------------------------------
	// Determine if left Comic is greater than right
	// Preconditions:   None
	// Postconditions:  true is returned if stored variable values are greater  
	//           than right; false is returned otherwise
	bool operator>(const Collectible& right) const;
};

class SportsCard : public Collectible {
public:
	string player;
	int year;
	string mfr;
	string grade;

	//---------------------------- create ------------------------------------
	// Preconditions: None
	// Postconditions: Returns a Collectible pointer to instantiated
	// subclass item.
	Collectible* create();

	//----------------------------- clone -------------------------------------
	// Preconditions: None
	// Postconditions: Returns Collectible pointer to deep copy of SportsCard subclass.
	Collectible* clone();

	//----------------------------- fill ---------------------------------------
	// Fills SportsCard with values from inputTable.
	// Preconditions: None
	// Postconditions: storage variables filled by input vector. 
	void fill(vector<string>& v);

	//--------------------------- toString -------------------------------------
	// Preconditions: Instance of SportsCard object called.
	// Postconditions: Returns string of formatted SportsCard data.
	string toString() const;

	//-----------------------------  =  -----------------------------------------
	// Overloaded assignment operator
	// Preconditions:   None
	// Postconditions:  *this is assigned the same stored variables values as right
	Collectible& operator=(const Collectible& right);

	//-----------------------------  ==  ----------------------------------------
	// Determine if two SportsCards are equal.
	// Preconditions:   None
	// Postconditions:  true is returned if the SportsCards have the same 
	//          stored variable values and false is returned otherwise
	bool operator==(const Collectible& right) const;

	//-----------------------------  !=  ----------------------------------------
	// Determine if two SportsCards are not equal.
	// Preconditions:   None
	// Postconditions:  false is returned if SportsCards have the same stored 
	//           varible values and true is returned otherwise
	bool operator!=(const Collectible& right) const;

	//-----------------------------  <   ----------------------------------------
	// Determine if left SportsCard is less than right
	// Preconditions:   None
	// Postconditions:  true is returned if stored variable values are less than  
	//           right; false is returned otherwise
	bool operator<(const Collectible& right) const;

	//-----------------------------  >   ----------------------------------------
	// Determine if left SportsCard is greater than right
	// Preconditions:   None
	// Postconditions:  true is returned if stored variable values are greater  
	//           than right; false is returned otherwise
	bool operator>(const Collectible& right) const;
};

//-----------------------------  <<  ----------------------------------------
// Overloaded output operator for class Collectible
// Preconditions:   a Collectible object is passed as input
// Postconditions:  toString method for subclass is printed to the output stream
ostream& operator<<(ostream& os, const Collectible& c);

#endif //COLLECTIBLE_H