// WRLDTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool bDebugText = true;
string sFileLocation;
string sLine;
fstream myFile;

int main()
{
    cout << "Hello World!\n";

	cout << "Please enter the location of the text file: ";
	// ..\..\WRLD_programming_test\problem_small.txt  OR  ..\..\WRLD_programming_test\problem_big.txt
	cin >> sFileLocation;

	myFile.open(sFileLocation);
	if (myFile.is_open()) {
		while (getline(myFile, sLine)) {
			if (bDebugText) {
				cout << sLine << endl;
			}
		}

		//myFile << "Test";
		myFile.close();
	}
	else {
		cout << "Unable to find and open file!" << endl;
		return 0;
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
