//Justin McKnight CS202 8/31/21
//Checkerboard lab1
#include <iostream>
#include <cstdio>

using namespace std;

/*This program takes 5 parameters, a row R, a column C, a starting character SC, a cycle size CS, and a width W. 
	With these the program make a checkerboard pattern of the size RxC starting with the starting character and incrementing until the cycle size is hit.
	Each row and letter in a row in multiplied by the width */

int main(){
	int R, C, CS, W;
	char SC, pChar;
	string line;
	
	cin >> R;
	cin >> C;
	cin >> SC;
	cin >> CS;
	cin >> W;
	line = "";
//Checks the input to see if it can make a checkerboard
	if(cin.eof()){
		cerr << "usage: checkerboard  - stdin should contain R, C, SC, CS and W"<<endl;
		return 0;
	}
	if((R<=0) || (C<=0) || (CS <=0) || (W<=0)){
		return 0;
	}
	if(SC+CS > 127){
		return 0;
	}
//creates each row by creating a string and adding the correct letter found by SC+(i+j)%CS W times then printing that row W times and starting a new line, creating an ixj matrix aka checkerboard.
	for(int i = 0; i<R;i++){
		for(int j = 0; j<C; j++){
			pChar = SC+(i+j)%CS;
			for(int n =0;n<W;n++) {line += pChar;}
		}
	for(int m=0;m<W;m++) {cout <<line<< endl;}
	line = "";
	}
	return 0;	
}
