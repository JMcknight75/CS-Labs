//Justin McKnight 9/7/21 CS202
//Lab2 Neg Lab
#include <iostream>
#include <cstdio>

using namespace std;
/*This program reads information from a PGM file and gives the negative of the image. */
int main(){
	int rows, cols, pixels, PGMCheck, count, num;
	string word,P2Check;
/*Error checking PGM file. Checks if it starts with P2, has proper rows and columns,
has 255 after rows and columns, and has exactly as many pixels as rows*cols.*/
	cin >> word;
	if(word != "P2"){
		cerr << "Bad PGM file -- first word is not P2" << endl;
		return 0;
	}
	if((!(cin >> cols))||(cols < 0)){
		cerr << "Bad PGM file -- No column specification" << endl;
		return 0;
	}
	if((!(cin >> rows))||(rows < 0)){
		cerr << "Bad PGM file -- No row specification" << endl;
		return 0;
	}
	if(!(cin>>PGMCheck) || PGMCheck != 255){
		cerr << "Bad PGM file -- No 255 following the rows and columns" << endl;
		return 0;
	}
	pixels = rows * cols;
//Outputs the header of a PGM file with proper rows and cols.
cout << "P2" << endl << cols << " " << rows << endl << 255 << endl;
//Goes through each pixel and subtracts each value from 255, outputs that value, and error checks.
	for(count = 0; count < pixels; count++){
		cin >> num;
		if(num < 0 || num > 255 || cin.fail()){
			cerr << "Bad PGM file -- pixel " << count << " is not a number between 0 and 255"<< endl;;
			return 0;
		}
		cout << 255-num << endl;

	}
	cin >> num;
	if(!(cin.fail())){
		cerr << "Bad PGM file -- Extra stuff after the pixels" << endl;
		return 0;
	}
	cin.clear();
	cin >> word;
	if(!(cin.fail())){
		cerr << "Bad PGM file -- Extra stuff after the pixels" << endl;
		return 0;
	}

	return 0;	
}
