#include "vinayak.h"

int main() {

	// define variables
	string alpha, CD, CL, CY; //variables from file are here
	vector<float>AoA;
	vector<float>C_D;
	vector<float>C_L;
	vector<float>C_Y;
	const float pi = 3.1415;

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
	
	//output values and find CD0, CY0, CL0
	cout << "AOA" << "\t" << "CD" << "\t" << "CL" << "\t" << "CY" << endl;
	float CDO, CLO, CYO;
	for (int j = 0; j < i; j++) {
		cout << AoA[j] << "\t" << C_D[j] << "\t" << C_L[j] << "\t" << C_Y[j] << endl;
		if (AoA[j] == 0) {
			CDO = C_D[j];
			CLO = C_L[j];
			CYO = C_Y[j];
		}
	}
	cout << endl;
	cout << "At zero AoA, CD = " << CDO << ", CL = " << CLO << ",and CY = " << CYO << endl;

	//user inputs AoA they want (-9.9 to 9.9, b/c step = 0.1)
	float al;
	cout << "Enter an AoA from -9.9 to 9.9 deg: ";
	cin >> al;
	if (al >= 9.9 || al <= -9.9)
		cout << "Out of range. Please re-run the program" << endl;

	//find location of AoA as k and the stability derivative
	int k = 0;
	while (k <= i-1) {
		if (al <= AoA[k + 1]) {
			break;
		}
		k += 1;
	}

	//find stability derivative (3 of them) - test CD only
	float x_1CD, x_2CD, x_1CL, x_2CL, x_1CY, x_2CY, CDREF, CLREF, CYREF; //x_1 = CD, CY, CL for (al-0.1) and x_2 = CD, CY, CL for (al+0.1) 
	float fw = ((AoA[k + 1] - (al + 0.1)) / (AoA[k + 1] - AoA[k]));
	float bk = ((AoA[k + 1] - (al - 0.1)) / (AoA[k + 1] - AoA[k]));
	float ref = ((AoA[k + 1] - (al)) / (AoA[k + 1] - AoA[k]));
	float run = 0.2;
	
	//FOR CD
	x_1CD = C_D[k + 1] - (C_D[k + 1] - C_D[k]) * bk;
	x_2CD = C_D[k + 1] - (C_D[k + 1] - C_D[k]) * fw;
	CDREF = C_D[k + 1] - (C_D[k + 1] - C_D[k]) * ref;
	float slop_CD = (x_2CD - x_1CD) / run;

	//FOR CL
	x_1CL = C_L[k + 1] - (C_L[k + 1] - C_L[k]) * bk;
	x_2CL = C_L[k + 1] - (C_L[k + 1] - C_L[k]) * fw;
	CLREF = C_L[k + 1] - (C_L[k + 1] - C_L[k]) * ref;
	float slop_CL = (x_2CL - x_1CL) / run;

	//FOR CY
	x_1CY = C_Y[k + 1] - (C_Y[k + 1] - C_Y[k]) * bk;
	x_2CY = C_Y[k + 1] - (C_Y[k + 1] - C_Y[k]) * fw;
	CYREF = C_Y[k + 1] - (C_Y[k + 1] - C_Y[k]) * ref;
	float slop_CY = (x_2CY - x_1CY) / run;

	//TOTAL COEFFICIENTS
	float C_DRAG = CDREF + slop_CD * 0.2;
	float C_LIFT = CLREF + slop_CL * 0.2;
	float C_SIDE = CYREF + slop_CY * 0.2;
	cout << "For your selected angle of attack: " << al << endl;
	cout << "CD" << "\t" << "CL" << "\t" << "CY" << endl;
	cout << C_DRAG << "\t" << C_LIFT << "\t" << C_SIDE << endl;
	cout << endl;

	//PUT THEM INTO MATRIX OF SIZE 3X1 "," is new row
	float COEFF[3][1] = { {-1*C_DRAG}, {C_SIDE}, {-1*C_LIFT} };
	
	//alpha into radians
	float a = al * (pi / 180);
	
	//the AoA matrix which is 3x3 in size
	float MAT[3][3] = { {cos(a),0,-sin(a)},{0,1,0},{sin(a),0,cos(a)} };
	
	// matrix multiplication (no need for loops)
	//COEFF_MAT = 3X1 here
	float COEFF_MAT[3][1];
	COEFF_MAT[0][0] = MAT[0][0] * COEFF[0][0] + MAT[0][1] * COEFF[1][0] + MAT[0][2] * COEFF[2][0];
	COEFF_MAT[1][0] = C_SIDE;
	COEFF_MAT[2][0] = MAT[2][0] * COEFF[0][0] + MAT[2][1] * COEFF[1][0] + MAT[2][2] * COEFF[2][0];

	//output all results
	cout << "X COEFFICIENT IS: " << COEFF_MAT[0][0] << endl;
	cout << "Y COEFFICIENT IS: " << COEFF_MAT[1][0] << endl;
	cout << "Z COEFFICIENT IS: " << COEFF_MAT[2][0] << endl;

	cout << "Thank you very much, goodbye!" << endl;


	return 0;

}

