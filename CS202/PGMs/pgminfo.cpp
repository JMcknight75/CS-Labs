//Justin McKnight 9/7/21 CS202
//Lab2 PGM files
#include <iostream>
#include <cstdio>

using namespace std;
/*This program reads and prints basic informatin about a PGM file such as the amount of rows,
columns, pixels, and the average pixel value */
int main(){
	int rows, cols, pixels, PGMCheck, count, num;
	double avgPixel=0;
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
	cin >> PGMCheck;
	if(cin.fail() || PGMCheck != 255){
		cerr << "Bad PGM file -- No 255 following the rows and columns" << endl;
	}
	pixels = rows * cols;
//Goes through each pixel and adds to a total to find a value and error checks.
	for(count = 0; count < pixels; count++){
		cin >> num;
		if(num < 0 || num > 255 || cin.fail()){
			cerr << "Bad PGM file -- pixel " << count << " is not a number between 0 and 255"<< endl;;
			return 0;
		}
		avgPixel += num;
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
//Prints basic info about the PGM file.
	avgPixel = avgPixel/(pixels);
	printf("# Rows:%12d\n", rows);
	printf("# Columns:%9d\n", cols);
	printf("# Pixels:%10d\n", pixels);
	printf("Avg Pixel: %8.3f\n", avgPixel);
	return 0;	
}
