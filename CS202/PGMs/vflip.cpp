//Justin McKnight 9/7/21 CS202
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
/*This program reads information from a PGM file and flips the image vertically. */
int main(){
	int rows, cols, PGMCheck, count, num;
	string word,P2Check;
	vector< vector <int> > pixelVec;
	/*Error checking PGM file. Checks if it starts with P2, has proper rows and columns,
	  has 255 after rows and columns, and has exactly as many pixels as rows*cols.*/
	cin >> word;
	if(word != "P2"){
		cerr << "Bad PGM file -- first word is not P2" << endl;
		return 0;
	}
	if((!(cin >> cols))||(cols <= 0)){
		cerr << "Bad PGM file -- No column specification" << endl;
		return 0;
	}
	if((!(cin >> rows))||(rows <= 0)){
		cerr << "Bad PGM file -- No row specification" << endl;
		return 0;
	}
	if(!(cin>>PGMCheck) || PGMCheck != 255){
		cerr << "Bad PGM file -- No 255 following the rows and columns" << endl;
		return 0;
	}
	cout << "P2" << endl << cols << " " << rows << endl << 255 << endl;
	//Goes through each pixel and places each value in a 2d vector of rows and columns and error checks.
	pixelVec.resize(rows);
	for(int i = 0; i < rows; i++){
		pixelVec[i].resize(cols);
	}
	for(int i = 0; i < rows; i++){
		for(int j =0; j<cols;j++){
			cin >> num;
			pixelVec[i][j]=num;
			if(num < 0 || num > 255 || cin.fail()){
				cerr << "Bad PGM file -- pixel " << count << " is not a number between 0 and 255"<< endl;
				return 0;
			}

			count++;
		}
	}
	//Cycles through each row backwards and prints out the pixel value
	for(int i = rows; i > 0; i--){
		for(int j = 0; j<cols;j++){
			cout << pixelVec[i-1][j]<< " ";
		}
		cout << endl;
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
