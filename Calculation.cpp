#include "vinayak.h"

int main() {

	// define variables
	string alpha, CD, CL, CY; //variables from file are here
	vector<float>AoA;
	vector<float>C_D;
	vector<float>C_L;
	vector<float>C_Y;

	//input filename
	string file;
	cout << "Enter the filename: ";
	cin >> file;

	//number of lines
	int i = 0;

	ifstream coeff(file); //opening the file.
	if (coeff.is_open()) //if the file is open
	{
		//ignore first line
		string line;
		getline(coeff, line);

		while (!coeff.eof()) //while the end of file is NOT reached
		{
			//I have 4 sets {alpha, CD, CL, CY} so use 4 getlines
			getline(coeff, alpha, ',');
			AoA.push_back(stof(alpha));
			getline(coeff, CD, ',');
			C_D.push_back(stof(CD));
			getline(coeff, CL, ',');
			C_L.push_back(stof(CL));
			getline(coeff, CY, '\n'); //new line after CY
			C_Y.push_back(stof(CY));
			
			i += 1; //increment number of lines
		}
		coeff.close(); //closing the file
		cout << "Number of entries: " << i-1 << endl;
	}
	else cout << "Unable to open file"; //if the file is not open output
	
	//output values
	cout << "AOA" << "\t" << "CD" << "\t" << "CL" << "\t" << "CY" << endl;
	for (int j = 0; j < i; j++) {
		cout << AoA[j] << "\t" << C_D[j] << "\t" << C_L[j] << "\t" << C_Y[j] << endl;
	}



	return 0;

}

