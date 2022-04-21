//---------------------------------------------------------------------------
// HW4.CPP
// Driver code for testing CollectibleStore.
// Authors:  Arbour
//---------------------------------------------------------------------------
// This code tests all of the basic functionality of the CollectibleStore
//  class for CSS 502 HW 4.
//
// Assumptions:
//   -- a text file named "HW4_Initialize.txt" exists in the same directory
//      as the code
//   -- a text file named "HW4_Customer.txt" exists in the same directory
//      as the code
//   -- a text file named "HW4_Commands.txt" exists in the same directory
//      as the code
//---------------------------------------------------------------------------

#include <fstream>
#include <string>
#include <sstream>
#include "CollectibleStore.h"
using namespace std;

int main() {
    // open '_Initialize' file
	ifstream infile("HW4_Initialize.txt");
	if (!infile) {
		cerr << "File could not be opened." << endl;
		return 1;
	}

    CollectibleStore CS;

    CS.buildStore(infile);

    // open '_Customer' file
	ifstream infile("HW4_Customer.txt");
	if (!infile) {
		cerr << "File could not be opened." << endl;
		return 1;
	}

    CS.addCustomers(infile);

    // open '_Commands' file
	ifstream infile("HW4_Commands.txt");
	if (!infile) {
		cerr << "File could not be opened." << endl;
		return 1;
	}

    CS.executeCommands(infile);
}