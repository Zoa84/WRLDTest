// WRLDTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <time.h>
using namespace std;

bool bDebugText = false;
string sFileLocation;
string sLine;
fstream myFile;
vector<unsigned long int> test(2);
vector<vector<unsigned long int>> vIFeatureData(0, vector<unsigned long int>(2));
vector<string> vSFeatures;

unsigned long long int GetEuclidDis(vector<unsigned long int> x, vector<unsigned long int> y) {
	return ((((unsigned long long int)x.at(0) - (unsigned long long int)y.at(0)) * ((unsigned long long int)x.at(0) - (unsigned long long int)y.at(0)))
		+ ((((unsigned long long int)x.at(1) - (unsigned long long int)y.at(1)) * ((unsigned long long int)x.at(1) - (unsigned long long int)y.at(1)))));
}

int main()
{
	//Get the text file to read data from
	cout << "Please enter the location of the text file: ";
	// ..\..\WRLD_programming_test\problem_small.txt  OR  ..\..\WRLD_programming_test\problem_big.txt
	cin >> sFileLocation;

	time_t tStartTime = time(NULL);
	if (bDebugText) {
		cout << "Start time is: " << tStartTime << endl;
	}

	myFile.open(sFileLocation);
	if (myFile.is_open()) {
		string sFeature;
		unsigned long int iFeaturePos[2];

		do {
			myFile >> sFeature;
			myFile >> iFeaturePos[0];
			myFile >> iFeaturePos[1];

			vSFeatures.push_back(sFeature);
			test.at(0) = iFeaturePos[0];
			test.at(1) = iFeaturePos[1];
			vIFeatureData.push_back(test);
		} while (getline(myFile, sLine));
		myFile.close();
	}
	else {
		cout << "Unable to find and open file!" << endl;
		return 0;
	}

	int iFinalFeature = 0;
	unsigned long long int iDistance;
	string sFinalDistance;
	unsigned long long int iFinalDistance = 0;
	for (unsigned int i = 0; i < vSFeatures.size(); i++) {
		iDistance = 0;
		for (unsigned int j = 0; j < vSFeatures.size(); j++) {
			if (i != j) {
				unsigned long long int dis = GetEuclidDis(vIFeatureData.at(i), vIFeatureData.at(j));
				if (dis < iDistance || iDistance == 0) {
					iDistance = dis;
				}
			}
		}

		if (iDistance > iFinalDistance || iFinalDistance == 0) {
			iFinalDistance = iDistance;
			sFinalDistance = vSFeatures.at(i);
			iFinalFeature = i;
		}

		if (bDebugText) {
			cout << i << " " << iDistance << endl;
		}
	}

	if (bDebugText) {
		time_t tEndTime = time(NULL);
		cout << "End time is: " << tEndTime << ", the process took " << tEndTime - tStartTime << endl;
		cout << "The longest shortest distance is: " << sFinalDistance << " " << iFinalDistance << endl;
	}

	cout << sFinalDistance << " " << vIFeatureData.at(iFinalFeature).at(0) << " " << vIFeatureData.at(iFinalFeature).at(1) << endl;

	system("pause");
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
