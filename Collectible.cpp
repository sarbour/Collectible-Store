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

#include "Collectible.h"

//------------------------- Constructor ----------------------------------
Collectible::Collectible() {}

//-------------------------- Destructor ----------------------------------
Collectible::~Collectible() {}

//---------------------------- create ------------------------------------
// This method is intended to be overridden by subclasses.
// Preconditions: None
// Postconditions: Returns a pointer to instantiated empty Collectible item.
Collectible* Collectible::create() {
	Collectible* temp = new Collectible;
	return temp;
}

//----------------------------- clone -------------------------------------
// This method is intended to be overridden by subclasses.
// Preconditions: None
// Postconditions: Returns pointer to deep copy of Collectible.
Collectible* Collectible::clone() {
	Collectible* temp = new Collectible;
	return temp;
}

//----------------------------- fill -------------------------------------
// To be overriden by descendent classes.
// Preconditions: None
// Postconditions: None 
void Collectible::fill(vector<string>& v) {}

//-------------------------- toString -------------------------------------
// This method is intended to be overridden by subclasses.
// Preconditions: None
// Postconditions: Returns count of Collectible cast to string.
string Collectible::toString() const {
	return "-1";
}

//--------------------------- isDeleted -------------------------------------
// Getter for deleted value.
// Preconditions: None
// Postconditions: Returns boolean value for deleted.
bool Collectible::isDeleted() const{
	return deleted;
}

void Collectible::setDeleted(bool input) {
	deleted = input;
}

//-----------------------------  =  ---------------------------------------
// Overloaded assignment operator
// Preconditions:   None
// Postconditions:  *this is assigned the same stored variables values as right
Collectible& Collectible::operator=(const Collectible& right) {
	count = right.count;
	deleted = right.deleted;
	return *this;
}

//-----------------------------  ==  --------------------------------------
// Determine if two Collectibles are equal.
// Preconditions:   None
// Postconditions:  true is returned if the Collectibles have the same 
//          stored variable values and false is returned otherwise
bool Collectible::operator==(const Collectible& right) const {
	return false;
}

//-----------------------------  !=  --------------------------------------
// Determine if two Collectibles are not equal.
// Preconditions:   None
// Postconditions:  false is returned if Collectibles have the same stored 
//           varible values and true is returned otherwise
bool Collectible::operator!=(const Collectible& right) const {
	return false;
}

//-----------------------------  <   --------------------------------------
// Determine if left Collectible is less than right
// Preconditions:   None
// Postconditions:  true is returned if stored variable values are less than  
//           right; false is returned otherwise
bool Collectible::operator<(const Collectible& right) const {
	return false;
}

//-----------------------------  >   --------------------------------------
// Determine if left Collectible is greater than right
// Preconditions:   None
// Postconditions:  true is returned if stored variable values are less than  
//           right; false is returned otherwise
bool Collectible::operator>(const Collectible& right) const {
	return false;
}

//-----------------------------  <<  ----------------------------------------
// Overloaded output operator for class Collectible
// Preconditions:   a Collectible object is passed as input
// Postconditions:  toString method for subclass is printed to the output stream
ostream& operator<<(ostream& os, const Collectible& c) {
	os << c.toString();
	return os;
}

//*************************************************************************
//------- COINS -------- COINS -------- COINS ---------- COINS ------------
//*************************************************************************

//---------------------------- create ------------------------------------
// Preconditions: None
// Postconditions: Returns a Collectible pointer to instantiated
// subclass item.
Collectible* Coin::create() {
	Coin* myCoin = new Coin;
	Collectible* collectibleCoin = dynamic_cast<Collectible*>(myCoin);
	return collectibleCoin;
}

//----------------------------- clone -------------------------------------
// Preconditions: None
// Postconditions: Returns Collectible pointer to deep copy of Coin subclass.
Collectible* Coin::clone() {
	Coin* temp = new Coin;

	temp->count = this->count;
	temp->type = this->type;
	temp->year = this->year;
	temp->grade = this->grade;

	Collectible* collectibleTemp = dynamic_cast<Collectible*>(temp);
	return collectibleTemp;
}

//----------------------------- fill -------------------------------------
// Fills coin with values from inputTable.
// Preconditions: None
// Postconditions: storage variables filled by input vector. 
void Coin::fill(vector<string>& v) {
	count = atoi(v[1].c_str());
	year = atoi(v[2].c_str());
	grade = atoi(v[3].c_str());
	type = v[4];
}

//---------------------------- toString -------------------------------------
// Preconditions: Instance of Coin object called.
// Postconditions: Returns string of formatted Coin data.
string Coin::toString() const {
	string s = "M, " + to_string(count) + ", " + to_string(year) + ", " +
		to_string(grade) + ", " + type;
	return s;
}

//-----------------------------  =  -----------------------------------------
// Overloaded assignment operator
// Preconditions:   None
// Postconditions:  *this is assigned the same stored variables values as right
Collectible& Coin::operator=(const Collectible& right) {
	deleted = right.isDeleted();
	count = right.getCount();
	const Coin* rightCoin = dynamic_cast<const Coin*>(&right);
	type = rightCoin->type;
	year = rightCoin->year;
	grade = rightCoin->grade;
	return *this;
}

//-----------------------------  ==  ----------------------------------------
// Determine if two Coins are equal.
// Preconditions:   None
// Postconditions:  true is returned if the Coins have the same 
//          stored variable values and false is returned otherwise
bool Coin::operator==(const Collectible& right) const {
	bool isEqual = true;
	if (deleted != right.isDeleted())
		isEqual = false;
	const Coin* rightCoin = dynamic_cast<const Coin*>(&right);
	if (type != rightCoin->type ||
		year != rightCoin->year ||
		grade != rightCoin->grade)
		isEqual = false;
	return isEqual;
}

//-----------------------------  !=  --------------------------------------
// Determine if two Coins are not equal.
// Preconditions:   None
// Postconditions:  false is returned if the Coins have the same stored 
//           varible values and true is returned otherwise
bool Coin::operator!=(const Collectible& right) const {
	return !operator==(right);
}

//-----------------------------  <   ----------------------------------------
// Determine if left Coin is less than right
// Preconditions:   None
// Postconditions:  true is returned if stored variable values are less than  
//           right; false is returned otherwise
bool Coin::operator<(const Collectible& right) const {
	const Coin* rightCoin = dynamic_cast<const Coin*>(&right);
	if (_strcmpi(type.c_str(), rightCoin->type.c_str()) < 0)
		return true;
	if (_strcmpi(type.c_str(), rightCoin->type.c_str()) == 0){
		if (year < rightCoin->year)
			return true;
		if (year == rightCoin->year) {
			if (grade < rightCoin->grade)
				return true;
		}
	}
	return false;
}

//-----------------------------  >   ----------------------------------------
// Determine if left Coin is greater than right
// Preconditions:   None
// Postconditions:  true is returned if stored variable values are less than  
//           right; false is returned otherwise
bool Coin::operator>(const Collectible& right) const {
	const Coin* rightCoin = dynamic_cast<const Coin*>(&right);
	if (_strcmpi(type.c_str(), rightCoin->type.c_str()) > 0)
		return true;
	if (_strcmpi(type.c_str(), rightCoin->type.c_str()) == 0) {
		if (year > rightCoin->year)
			return true;
		if (year == rightCoin->year) {
			if (grade > rightCoin->grade)
				return true;
		}
	}
	return false;
}

//*************************************************************************
//------- COMICS -------- COMICS -------- COMICS ---------- COMICS --------
//*************************************************************************

//---------------------------- create ------------------------------------
// Preconditions: None
// Postconditions: Returns a Collectible pointer to instantiated
// subclass item.
Collectible* Comic::create() {
	Comic* myComic = new Comic;
	Collectible* collectibleComic = dynamic_cast<Collectible*>(myComic);
	return collectibleComic;
}

//----------------------------- clone -------------------------------------
// Preconditions: None
// Postconditions: Returns Collectible pointer to deep copy of Comic subclass.
Collectible* Comic::clone() {
	Comic* temp = new Comic;

	temp->count = this->count;
	temp->publisher = this->publisher;
	temp->title = this->title;
	temp->year = this->year;
	temp->grade = this->grade;

	Collectible* collectibleTemp = dynamic_cast<Collectible*>(temp);
	return collectibleTemp;
}

//----------------------------- fill -------------------------------------
// Fills comic with values from inputTable.
// Preconditions: None
// Postconditions: storage variables filled by input vector. 
void Comic::fill(vector<string>& v) {
	count = atoi(v[1].c_str());
	publisher = v[5];
	title = v[4];
	year = atoi(v[2].c_str());
	grade = v[3];
}

//---------------------------- toString -------------------------------------
// Preconditions: Instance of Comic object called.
// Postconditions: Returns string of formatted Comic data.
string Comic::toString() const {
	string s = "C, " + to_string(count) + ", " + to_string(year) + ", " +
		grade + ", " + title + ", " + publisher;
	return s;
}

//-----------------------------  =  -----------------------------------------
// Overloaded assignment operator
// Preconditions:   None
// Postconditions:  *this is assigned the same stored variables values as right
Collectible& Comic::operator=(const Collectible& right) {
	deleted = right.isDeleted();
	count = right.getCount();
	const Comic* rightComic = dynamic_cast<const Comic*>(&right);
	publisher = rightComic->publisher;
	title = rightComic->title;
	year = rightComic->year;
	grade = rightComic->grade;
	return *this;
}

//-----------------------------  ==  ----------------------------------------
// Determine if two Comics are equal.
// Preconditions:   None
// Postconditions:  true is returned if the Comics have the same 
//          stored variable values and false is returned otherwise
bool Comic::operator==(const Collectible& right) const {
	bool isEqual = true;
	if (deleted != right.isDeleted())
		isEqual = false;
	const Comic* rightComic = dynamic_cast<const Comic*>(&right);
	if (publisher != rightComic->publisher ||
		title != rightComic->title ||
		year != rightComic->year ||
		grade != rightComic->grade)
		isEqual = false;
	return isEqual;
}

//-----------------------------  !=  --------------------------------------
// Determine if two Comics are not equal.
// Preconditions:   None
// Postconditions:  false is returned if the Comics have the same stored 
//           varible values and true is returned otherwise
bool Comic::operator!=(const Collectible& right) const {
	return !operator==(right);
}

//-----------------------------  <   ----------------------------------------
// Determine if left Comic is less than right
// Preconditions:   None
// Postconditions:  true is returned if stored variable values are less than  
//           right; false is returned otherwise
bool Comic::operator<(const Collectible& right) const {
	const Comic* rightComic = dynamic_cast<const Comic*>(&right);
	if (_strcmpi(publisher.c_str(), rightComic->publisher.c_str()) < 0)
		return true;
	if (_strcmpi(publisher.c_str(), rightComic->publisher.c_str()) == 0) {
		if (_strcmpi(title.c_str(), rightComic->title.c_str()) < 0)
			return true;
		if (_strcmpi(title.c_str(), rightComic->title.c_str()) == 0) {
			if (year < rightComic->year)
				return true;
			if (year == rightComic->year) {
				if (_strcmpi(grade.c_str(), rightComic->grade.c_str()) < 0)
					return true;
			}
		}
	}
	return false;
}

//-----------------------------  >   ----------------------------------------
// Determine if left Comic is greater than right
// Preconditions:   None
// Postconditions:  true is returned if stored variable values are less than  
//           right; false is returned otherwise
bool Comic::operator>(const Collectible& right) const {
	const Comic* rightComic = dynamic_cast<const Comic*>(&right);
	if (_strcmpi(publisher.c_str(), rightComic->publisher.c_str()) > 0)
		return true;
	if (_strcmpi(publisher.c_str(), rightComic->publisher.c_str()) == 0) {
		if (_strcmpi(title.c_str(), rightComic->title.c_str()) > 0)
			return true;
		if (_strcmpi(title.c_str(), rightComic->title.c_str()) == 0) {
			if (year < rightComic->year)
				return true;
			if (year == rightComic->year) {
				if (_strcmpi(grade.c_str(), rightComic->grade.c_str()) > 0)
					return true;
			}
		}
	}
	return false;
}

//*************************************************************************
//------ SPORTSCARDS --- SPORTSCARDS --- SPORTSCARDS --- SPORTSCARDS ------
//*************************************************************************

//---------------------------- create ------------------------------------
// Preconditions: None
// Postconditions: Returns a Collectible pointer to instantiated
// subclass item.
Collectible* SportsCard::create() {
	SportsCard* mySportsCard = new SportsCard;
	Collectible* collectibleSportsCard = dynamic_cast<Collectible*>(mySportsCard);
	return collectibleSportsCard;
}

//----------------------------- clone -------------------------------------
// Preconditions: None
// Postconditions: Returns Collectible pointer to deep copy of SportsCard subclass.
Collectible* SportsCard::clone() {
	SportsCard* temp = new SportsCard;

	temp->count = this->count;
	temp->player = this->player;
	temp->year = this->year;
	temp->mfr = this->mfr;

	Collectible* collectibleTemp = dynamic_cast<Collectible*>(temp);
	return collectibleTemp;
}

//----------------------------- fill -------------------------------------
// Fills comic with values from inputTable.
// Preconditions: None
// Postconditions: storage variables filled by input vector. 
void SportsCard::fill(vector<string>& v) {
	count = atoi(v[1].c_str());
	player = v[4];
	year = atoi(v[2].c_str());
	mfr = v[5];
	grade = v[3];
}

//----------------------------- toString -------------------------------------
// Preconditions: Instance of SportsCard object called.
// Postconditions: Returns string of formatted SportsCard data.
string SportsCard::toString() const {
	string s = "S, " + to_string(count) + ", " + to_string(year) + ", " +
		grade + ", " + player + ", " + mfr;
	return s;
}

//-----------------------------  =  -----------------------------------------
// Overloaded assignment operator
// Preconditions:   None
// Postconditions:  *this is assigned the same stored variables values as right
Collectible& SportsCard::operator=(const Collectible& right) {
	deleted = right.isDeleted();
	count = right.getCount();
	const SportsCard* rightSportsCard = dynamic_cast<const SportsCard*>(&right);
	player = rightSportsCard->player;
	year = rightSportsCard->year;
	mfr = rightSportsCard->mfr;
	grade = rightSportsCard->grade;
	return *this;
}

//-----------------------------  ==  ----------------------------------------
// Determine if two SportsCards are equal.
// Preconditions:   None
// Postconditions:  true is returned if the SportsCards have the same 
//          stored variable values and false is returned otherwise
bool SportsCard::operator==(const Collectible& right) const {
	bool isEqual = true;
	if (deleted != right.isDeleted())
		isEqual = false;
	const SportsCard* rightSportsCard = dynamic_cast<const SportsCard*>(&right);
	if (player != rightSportsCard->player ||
		year != rightSportsCard->year ||
		mfr != rightSportsCard->mfr ||
		grade != rightSportsCard->grade)
		isEqual = false;
	return isEqual;
}

//-----------------------------  !=  --------------------------------------
// Determine if two SportsCards are not equal.
// Preconditions:   None
// Postconditions:  false is returned if the SportsCards have the same stored 
//           varible values and true is returned otherwise
bool SportsCard::operator!=(const Collectible& right) const {
	return !operator==(right);
}

//-----------------------------  <   ----------------------------------------
// Determine if left SportsCard is less than right
// Preconditions:   None
// Postconditions:  true is returned if stored variable values are less than  
//           right; false is returned otherwise
bool SportsCard::operator<(const Collectible& right) const {
	const SportsCard* rightSportsCard = dynamic_cast<const SportsCard*>(&right);
	if (_strcmpi(player.c_str(), rightSportsCard->player.c_str()) < 0)
		return true;
	if (_strcmpi(player.c_str(), rightSportsCard->player.c_str()) == 0) {
		if (year < rightSportsCard->year)
			return true;
		if (year == rightSportsCard->year) {
			if (_strcmpi(mfr.c_str(), rightSportsCard->mfr.c_str()) < 0)
				return true;
			if (_strcmpi(player.c_str(), rightSportsCard->player.c_str()) == 0) {
				if (_strcmpi(grade.c_str(), rightSportsCard->grade.c_str()) < 0)
					return true;
			}
		}
	}
	return false;
}

//-----------------------------  >   ----------------------------------------
// Determine if left SportsCard is greater than right
// Preconditions:   None
// Postconditions:  true is returned if stored variable values are less than  
//           right; false is returned otherwise
bool SportsCard::operator>(const Collectible& right) const {
	const SportsCard* rightSportsCard = dynamic_cast<const SportsCard*>(&right);
	if (_strcmpi(player.c_str(), rightSportsCard->player.c_str()) > 0)
		return true;
	if (_strcmpi(player.c_str(), rightSportsCard->player.c_str()) == 0) {
		if (year > rightSportsCard->year)
			return true;
		if (year == rightSportsCard->year) {
			if (_strcmpi(mfr.c_str(), rightSportsCard->mfr.c_str()) > 0)
				return true;
			if (_strcmpi(player.c_str(), rightSportsCard->player.c_str()) == 0) {
				if (_strcmpi(grade.c_str(), rightSportsCard->grade.c_str()) > 0)
					return true;
			}
		}
	}
	return false;
}