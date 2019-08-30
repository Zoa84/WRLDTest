#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
using namespace std;

bool bDebugText = false;							//Set true to show debug text when executing the program
vector<vector<unsigned long int>> vIFeatureData;	//Vector of vectors of the features positions (X and Y)
vector<string> vSFeatureName;						//Vector of the features names

//Function to find the euclidean distance between two features (Does not square root the answer as it is unnecessary and uses extra computationel cost
unsigned long long int GetEuclidDis(vector<unsigned long int> x, vector<unsigned long int> y) {
	return ((((unsigned long long int)x.at(0) - (unsigned long long int)y.at(0)) * ((unsigned long long int)x.at(0) - (unsigned long long int)y.at(0)))
		+ ((((unsigned long long int)x.at(1) - (unsigned long long int)y.at(1)) * ((unsigned long long int)x.at(1) - (unsigned long long int)y.at(1)))));
}

int main()
{
	//Get the text file to read data from
	string sFileLocation;
	cout << "Please enter the location of the text file: ";
	// ..\..\WRLD_programming_test\problem_small.txt  OR  ..\..\WRLD_programming_test\problem_big.txt
	cin >> sFileLocation;

	time_t tStartTime = time(NULL);
	if (bDebugText) {
		cout << "Start time is: " << tStartTime << endl;
	}

	fstream myFile;
	string sLine;
	vector<unsigned long int> vPos(2);		//Vector to hold a features X and Y position to add to vIFeaturePos

	myFile.open(sFileLocation);
	if (myFile.is_open()) {
		string sFeature;					//The feature name, to be added to vSFeatureName
		unsigned long int iFeaturePos[2];	//The features position, to be added to vPos then to vIFeaturePos

		//For each line, get the feature name and positions, and save them to vSFeatureName and vIFeaturePos
		while(!(myFile>>ws).eof() ) {	//While the next line in the file is not white space
			myFile >> sFeature;
			myFile >> iFeaturePos[0];
			myFile >> iFeaturePos[1];

			if (bDebugText) {
				cout << sFeature << " " << iFeaturePos[0] << " " << iFeaturePos[1] << endl;
			}

			vSFeatureName.push_back(sFeature);
			vPos.at(0) = iFeaturePos[0];
			vPos.at(1) = iFeaturePos[1];
			vIFeatureData.push_back(vPos);
		}
		myFile.close();
	}
	else {
		cout << "Unable to find and open file!" << endl;
		return 0;
	}

	int iFinalFeature = 0;						//The feature number with the longest, shortest distance to other features
	unsigned long long int iFinalDistance = 0;	//The distance from the most isolated feature to the closest feature
	unsigned long long int iDistance;			//Shortest distance for the current feature compared to all other feature

	//For loop to find the most isolated feature
	for (unsigned int i = 0; i < vSFeatureName.size(); i++) {
		iDistance = 0;
		for (unsigned int j = 0; j < vSFeatureName.size(); j++) {
			if (i != j) {
				unsigned long long int iCurDistance = GetEuclidDis(vIFeatureData.at(i), vIFeatureData.at(j));
				if (iCurDistance < iDistance || iDistance == 0) {
					iDistance = iCurDistance;
				}
			}
		}

		//If the shortest distance for this feature to others is longer than our currently saved feature (iFinalFeature & iFinalDistance),
		//set the current feature as the most isolated feature
		if (iDistance > iFinalDistance) {
			iFinalDistance = iDistance;
			iFinalFeature = i;
		}

		if (bDebugText) {
			cout << vSFeatureName.at(i) << " - Shortest distance to another feature: " << iDistance << endl;
		}
	}

	if (bDebugText) {
		time_t tEndTime = time(NULL);
		cout << "End time is: " << tEndTime << ", the process took " << tEndTime - tStartTime << endl;
		cout << "The longest, shortest distance is: " << vSFeatureName.at(iFinalFeature) << " " << iFinalDistance << endl;
	}

	//Print out the most isolated feature
	cout << vSFeatureName.at(iFinalFeature) << " " << vIFeatureData.at(iFinalFeature).at(0) << " " << vIFeatureData.at(iFinalFeature).at(1) << endl;

	system("pause");
}