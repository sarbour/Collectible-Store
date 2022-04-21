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

int main() {
	// << "Begin Main" << "\n";

	// open 'HW4inventory.txt' file
	ifstream infile_inventory("HW4inventory.txt");
	if (!infile_inventory) {
		cerr << "File could not be opened." << endl;
		return 1;
	}

	CollectibleStore CS;

	// cout << "\n";

	CS.buildStore(infile_inventory);

	// open 'HW4customers.txt' file
	ifstream infile_customers("HW4customers.txt");
	if (!infile_customers) {
		cerr << "File could not be opened." << endl;
		return 1;
	}

	// cout << "BuildStore Complete" << "\n\n";

	cout << "Add Customers:\n";
	CS.addCustomers(infile_customers);

	// open 'HW4commands.txt' file
	ifstream infile_commands("HW4commands.txt");
	if (!infile_commands) {
		cerr << "File could not be opened." << endl;
		return 1;
	}

	// cout << "\nExecute Commands:\n";
	CS.executeCommands(infile_commands);
}