//Justin McKnight 9/7/21 CS202
//Big White lab2
#include <iostream>
#include <stdlib.h>

using namespace std;
/*This program takes a nubmber of rows and columns from the command line and makes a white PGM file out of those */
int main(int argc, char** argv){ 
	int cols, rows, pixels;
//checks for exactly 3 arguments
	if(argc != 3){
		cerr << "usage: bigwhite rows cols" << endl;
	}
//converts command line arguments into integers
	rows = atoi(argv[1]);
	cols = atoi(argv[2]);
	if(rows <= 0 || cols <= 0){
		cerr << "usage: bigwhite rows cols" << endl;
	}
//Outputs header with rows and cols then rows*cols amount of pixels each at value 255
	cout << "P2" << endl << cols << " " << rows << endl << "255" << endl;
	pixels = rows * cols;
	for(int i = 0; i < pixels; i++){
		cout << "255"<<endl;
	}	
	return 0;
}
