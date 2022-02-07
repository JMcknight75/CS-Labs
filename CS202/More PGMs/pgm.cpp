//Justin McKnight 9/14/21 CS202
//Lab3 more PGMS
#include "pgm.hpp"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

bool Pgm::Read(const std::string &file)
{
	ifstream fin;
	string s;
	size_t i, j, r, c, v;

	fin.open(file.c_str());
	if (fin.fail()) return false;

	if (!(fin >> s)) return false;
	if (s != "P2") return false;
	if (!(fin >> c) || c <= 0) return false;
	if (!(fin >> r) || r <= 0) return false;
	if (!(fin >> i) || i != 255) return false;

	Pixels.resize(r);
	for (i = 0; i < r; i++) {
		Pixels[i].clear();
		for (j = 0; j < c; j++) {
			if (!(fin >> v) || v > 255) return false;
			Pixels[i].push_back(v);
		}
	}
	if (fin >> s) return false;
	fin.close();
	return true;
}
//This program uses an output file stream to write a pgm file of size rows * cols based on the Pixels vector.
bool Pgm::Write(const std::string &file) const{
	int count, rows, cols;
	ofstream outputFile;

	if(Pixels.size() <= 0 || Pixels[0].size() <=0){
		return false;
	}
	cols =  Pixels[0].size();
	rows =  Pixels.size();

	count=1;

	outputFile.open(file.c_str());
//Prints Header for pgm file to output file
	outputFile << "P2" << endl << cols << " " << rows << endl << 255 << endl;
//Outputs the contents of Pixels[i][j] then prints a space or a newline if there are 20 pixels on the line
	for(int i = 0;i<rows;i++){
		for(int j = 0;j<cols;j++){
			outputFile << Pixels[i][j];
			if(count%20 == 0){
				outputFile<<endl;
			}else{
				if(count == rows*cols){
				}else{
					outputFile<< " ";
				}
			}
			count++;
		}
	}
//if end is reached but not 20 pixels on a line, outputs newline
	if((count-1)%20 != 0){
		outputFile << endl;
	}
	return true;
}
//Creates a pgm without the header of size r*c with all values equal to pv in the Pixels vector
bool Pgm::Create(size_t r, size_t c, size_t pv){
	vector< int > cols[c];
	if(pv > 255){
		return false;
	}
//Resizes Pixels vector to r*c
	Pixels.resize(r);
	for(size_t i = 0;i< r;i++){
		Pixels[i].resize (c);
	}
//Sets all values in vector to pv
	for(size_t i = 0;i<r;i++){
		for(size_t j = 0;j<c;j++){
			Pixels[i][j]=pv;
		}
	}

	return true;
}
//Rotates a PGM in the Pixels vector clockwise by 90 degrees, making the top row the rightmost column
bool Pgm::Clockwise(){
	size_t rows, cols;
//temporary vector cPixels that data is read into
	vector< vector < int > > cPixels;
	rows = Pixels.size();
	cols = Pixels[0].size();
//Resize cPixels to c*r
	cPixels.resize(cols);
	for(size_t i = 0; i<cols;i++){
		cPixels[i].resize(rows);
	}
//Reads in data from Pixels vector into place in cPixels vector
	for(size_t j = 0; j<cols; j++){
		for(size_t i=0;i<rows;i++){
			cPixels[j][i] =  Pixels[rows-1-i][j];
		}
	}
	Pixels =  cPixels;

	return true;
}
//Roatates a PGM in the Pixels vector counter-clockwise by 90 degrees, making top row the leftmost column reversed
bool Pgm::Cclockwise(){
	size_t rows, cols;
//temporary vector cCPixels
	vector< vector < int > > cCPixels;
	rows= Pixels.size();
	cols= Pixels[0].size();
//Resizes cCPixels to c*r
	cCPixels.resize(cols);
	for(size_t i = 0; i<cols;i++){
		cCPixels[i].resize(rows);
	}
//Reads data into cCPixels
	for(size_t j = 0; j<cols; j++){
		for(size_t i=0;i<rows;i++){
			cCPixels[j][i] =  Pixels[i][cols-1-j];
		}
	}
	Pixels =  cCPixels;

	return true;
}                   
//Adds a border of w pixels with the given value pv
bool Pgm::Pad(size_t w, size_t pv){
//temporary vector padPixels of size (2w+rows)(cols+2w)
	int rows, cols;
	vector< vector < int > > padPixels;

	if(pv > 255){
		return false;
	}
	rows = Pixels.size();
	cols = Pixels[0].size();
//Resizes padPixels
	padPixels.resize(rows+2*w);
	for(size_t i = 0; i < padPixels.size();i++){
		padPixels[i].resize(cols+ 2*w);
	}
//Checks bounds to see if pixel is part of original image or pad, then places appropriate pixel value
	for(size_t i = 0; i < padPixels.size(); i++){
		for(size_t j = 0; j<padPixels[0].size(); j++){
			if(i<w || i >= rows+w){
				padPixels[i][j] = pv;
			}else if(j<w || j>=cols+w){
				padPixels[i][j] = pv;
			}else{
				padPixels[i][j] = Pixels[i-w][j-w];
			}
		}
	}
	Pixels = padPixels;

	return true;
}
//makes r*c copies of the PGM in Pixels vector
bool Pgm::Panel(size_t r, size_t c){
//temporary vector panPixels of size rows*cols
	vector< vector< int > >panPixels;
	int rows, cols;
	if(r == 0 || c == 0){
		return false;
	}
	rows=Pixels.size();
	cols=Pixels[0].size();
//Resize panPixels
	panPixels.resize(rows*r);
	for(size_t i=0; i < panPixels.size();i++){
		panPixels[i].resize(cols*c);
	}
//Reads pixel data from Pixels into panPixels based on remainder of i%rows and j%cols
	for(size_t i=0;i < panPixels.size(); i++){
		for(size_t j=0;j<panPixels[0].size(); j++){
			panPixels[i][j] = Pixels[i%rows][j%cols];
		}
	}
	Pixels = panPixels;
	return true;
}
//Crops the image at (r,c) to (r+rows, c+cols)
bool Pgm::Crop(size_t r, size_t c, size_t rows, size_t cols){
//temporary vector cropPixels
	vector< vector< int > > cropPixels;
//Error checking to see if r+rows or c+cols exceedes acutual size
	if(rows+r > Pixels.size() || cols+c >= Pixels[0].size()){
		return false;
	}
//Resizes crop pixels
	cropPixels.resize(rows);
	for(size_t i=0;i<rows;i++){
		cropPixels[i].resize(cols);
	}
//Reads data from Pixels starting at (r,c) into cropPixels
	for(size_t i = 0; i < cropPixels.size(); i++){
		for(size_t j = 0; j < cropPixels[i].size(); j++){
			cropPixels[i][j] = Pixels[i+r][j+c];
		}
	}
	Pixels = cropPixels;
	return true;
}

