#include "vinayak.h"
//USING ARRAYS = VERY IMPORTANT!

int main() {

	double g[4] = {0,0.3,0.4,0.42}; // 4 element array
	//g[1] = 0.3 here
	int i;

	cout << "Enter index: ";
	cin >> i;
	cout << g[i] << endl;
	
	//making array in loops
	int j[9];
	cout << "Element - Value" << endl;
	for (int i = 0; i < 9; i++) {
		j[i] = 12;
		cout << i << "-----------" << j[i] << endl;
	}

	//using array in calculations, dot product
	int x[5] = { 1,2,3,4,5 };
	float y[5] = { 0.1,0.2,0.3,0.4,0.5 };
	float sum = 0;
	for (int j = 0; j < 5; j++) {
		sum = x[j] + y[j];
	}

	cout << "Dot Product is: " << sum << endl;;
	//note: If I said int sum it will be 5 (not 5.5)
	//If I said int (y) and float sum, it will be....5



	//multi-dim arrays [ROWS] [COLUMNS] {matrices!!!}
	// here 2 rows 3 columns .. first row = 2 3 4, second row = 8 9 10 (i,j)
	// 2 3 4
	// 8 9 10
	int matrix[2][3] = { {2,3,4},{8,9,10} };

	cout << matrix[0][2] << endl; // zeroth row, 2nd column (i.e.) 4
	cout << matrix[1][2] << endl; // first row, 2rd element (i.e.) 10

	//printing multi-dim arrays
	cout << "Matrix" << endl;
	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 3; col++) {
			cout << matrix[row][col] << " ";
		}
		cout << endl;
	}


	return 0;
}