//Justin McKnight 10/6/21 CS202
//Lab 5 Bitmatrix lab
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include "bitmatrix.hpp"
using namespace std;
//Bitmatrix constructor that makes a bitmatrix of size rows x cols with each value 0
Bitmatrix::Bitmatrix(int rows, int cols){
	vector<string> tmpVec;

	try{
		if(rows <= 0) throw ((string) "Bad rows");
		if(cols <=0) throw((string) "Bad cols");
	} catch (string s) {
		cout << s << endl;
		return;
	}
	M.resize(rows, "");
	for(int i = 0; i < rows; i++){
		M[i].resize(cols, '0');
	}
	return;
}
//Reads a bitmatrix in from a file and error checks
Bitmatrix::Bitmatrix(const string &fn){
	ifstream file;
	size_t i,j;
	string str;
	int numLines=0;

	try{
		M.resize(0);
		file.open(fn.c_str());
		if(!(file.is_open())) throw((string) "Can't open file");
		while(getline(file, str)){
			if(str != ""){
				numLines++;
			}
		}
		file.clear();
		file.seekg(0, file.beg);
		M.resize(numLines, "");
		j=0;
		while(getline(file, str)){
			for(size_t i =0; i < str.size(); i++){
				if(str != ""){
					if(str[i] != ' '){
						M[j].push_back(str[i]);
					}
				}
			}
			if(str != "") j++;
		}
		file.close();
		for(i = 0; i < M.size(); i++){
			if(M[i].size() != M[0].size()) throw ((string) "Bad file format");
			for( j = 0; j<M[0].size(); j++){
				if(M[i][j] != '0' && M[i][j] != '1' && M[i][j] != ' '){
					throw((string) "Bad file format");
				}
			}
		}
	}catch (string s){
		cout << s << endl;
		file.close();
		M.resize(1, "x");
		return;
	}
	return;
}
//Makes a copy of a bitmatrix and returns a pointer to it.
Bitmatrix *Bitmatrix::Copy() const
{
	Bitmatrix* p = new Bitmatrix(Rows(), Cols());

	p->M = M;
	return p;
}
//writes a bitmatrix to a file
bool Bitmatrix::Write(const string &fn) const{
	ofstream file;
	file.open(fn.c_str());
	if(!(file.is_open())){
		return false;		
	}
	for(int i = 0; i < Rows(); i++){
		file << M[i] << endl;
	}
	file.close();
	return true;
}
//Prints a bitmatrix to standard output
void Bitmatrix::Print(size_t w) const{	
	for(int i = 0; i < Rows(); i++){
		if(M[i].size() == 0) continue;
		for(int j = 0; j<Cols(); j++){
			cout << Val(i,j);
			if((w != 0 && ((j+1)%w)==0) && (j+1)!= Cols()){
				cout << " ";
			}
		}
		cout << endl;
		if(i!= Rows()-1 &&(w!=0 && (i+1)%w == 0)){
			cout << endl;
		}
	}
}
//Creates a PGM of a bitmatrix with 0 values being white (255) and 1 values being gray (100) with a black (0) border of size border and outputs bitmatrix values as pxp squares of respecive colors
bool Bitmatrix::PGM(const string &fn, int p, int border) const{
	ofstream file;
	int width,height;
//calculates rows and cols of PGM
	width = Rows() * p + (Rows()+1) * border;
	height  =  Cols() * p + (Cols()+1)*border;
	file.open(fn.c_str());
	if(!(file.is_open())){
		return false;
	}
	//outputs PGM header with calculated rows and cols
	file << "P2" << endl << height << " " << width << endl << 255 << endl;
	for(int i = 0; i < border; i++){
		for(int j = 0; j < height; j++){
			file << 0 << " ";
		}
		file << endl;
	}
//outputs PGM values 
	for(int n = 0; n < Rows(); n++){
		for(int m = 0; m < p; m++){
			for(int g = 0; g < border; g++){
				file << 0 << " ";
			}
			for(int j = 0; j<Cols(); j++){
				for(int i = 0; i < p; i++){
					if(M[n][j] == '1'){ file << 100 << " ";}
					if(M[n][j] == '0'){file << 255 << " ";}
					
				}
				for(int i = 0; i < border; i++){
					file << 0 << " ";
				}
			file << endl;
			}
			file << endl;
		}
		file << endl;
		for(int i =0; i < border; i++){
			for(int j = 0; j<height; j++){
				file << 0 << " ";
			}
			file << endl;
		}
		file << endl << endl;
	}


	file.close();
	return true;
}
//Returns amount of rows
int Bitmatrix::Rows() const{
	return M.size();
}
//Returns amount of cols
int Bitmatrix::Cols() const
{
	return M[0].size();
}
//Returns value at specified row and column
char Bitmatrix::Val(int row, int col) const
{
	if(row < Rows() && col < Cols()){
		return M[row][col];
	}else{
		return 'x';
	}
}
//Sets value at specified row and column to val
bool Bitmatrix::Set(int row, int col, char val){
	if(row >= Rows() || col >= Cols()|| row<0 || col<0) return false;
	if(val == '0' || val == '1'){
		M[row][col] = val;
		return true;
	}
	if(val == 0){
		M[row][col] = '0';
		return true;
	}
	if(val == 1){
		M[row][col] = '1';
		return true;
	}
	return false;
}
//Swaps two rows in a bitmatrix
bool Bitmatrix::Swap_Rows(int r1, int r2){
	if(r1 >= Rows() || r2 >= Rows()){
		return false;
	}
	if(r1 == r2){
		return true;
	}
	string tmpStr, secondTmpStr;
	tmpStr =  M[r1];
	secondTmpStr = M[r2];
	M[r1] = M[r2];
	M[r2] = tmpStr;
	if(M[r1] ==  secondTmpStr && M[r2] == tmpStr){
		return true;
	}


	return false;
}
//Adds two rows and sets the sum to r1
bool Bitmatrix::R1_Plus_Equals_R2(int r1, int r2){
	int tmp1, tmp2;
	string tmpStr;
	if(r1 >= Rows() || r2 >= Rows()||r2 < 0 || r1 < 0 || r1 == r2){
		return false;
	}
	for(int i = 0; i < Cols(); i++){
		tmp1 = M[r1][i] - '0';
		tmp2 = M[r2][i]- '0';
		tmp1 = tmp1^tmp2;
		if(tmp1 == 1){
			M[r1][i] = '1';
		}else{
			M[r1][i] = '0';
		}
	}

	return true;
}
//hash function
unsigned int djb_hash(const string &s){
	size_t i;
	unsigned int h;

	h = 5381;

	for (i = 0; i < s.size(); i++) {
		h = (h << 5) + h + s[i];
	}
	return h;
}
//Adds two matrices and returns pointer to sum
Bitmatrix *Sum(const Bitmatrix *a1, const Bitmatrix *a2){
	Bitmatrix* sumMatrix = new Bitmatrix(a1->Rows(), a1->Cols());

	if(a1->Rows() != a2->Rows() && a1->Cols() != a2->Cols()){
		delete sumMatrix;
		return NULL;
	}
	for(int i = 0; i < a1->Rows(); i++){
		for(int j = 0; j < a2->Cols(); j++){
			if(a1->Val(i,j) == a2->Val(i,j)){
				sumMatrix->Set(i,j, '0');
			}else{
				sumMatrix->Set(i,j, '1');
			}
		}
	}
	return sumMatrix;
}
//Multiplies two matrices and returns pointer to product
Bitmatrix *Product(const Bitmatrix *a1, const Bitmatrix *a2){
	Bitmatrix* prodMatrix = new Bitmatrix(a1->Rows(), a2->Cols());
	vector<int> r;
	vector<int> c;
	int sum;
	if(a1->Cols() != a2->Rows()){
		delete prodMatrix;
		return NULL;
	}
	r.resize(a1->Cols());
	c.resize(a2->Rows());
	for(int i = 0; i < prodMatrix->Rows(); i++){
		for(int j = 0; j < prodMatrix->Cols(); j++){
			for(size_t m = 0; m < r.size(); m++){
				r[m] = a1->Val(i, m) -'0';
			}
			for(size_t n = 0; n < c.size(); n++){
				c[n] = a2->Val(n, j) -'0';
			}
			sum = 0;
			for(size_t g = 0; g < r.size(); g++){
				sum ^= r[g] * c[g];
			}
			prodMatrix->Set(i,j, sum);
		}
	}
	return prodMatrix;
}
//Creates a new matrix out of rows specified in rows vector
Bitmatrix *Sub_Matrix(const Bitmatrix *a1, const vector <int> &rows){
	Bitmatrix* subMatrix = new Bitmatrix(rows.size(), a1->Cols());
	for(size_t i = 0; i < rows.size(); i++){
		if(rows[i] >= a1->Rows()|| rows.size() == 0) return NULL;
	}
	for(size_t i = 0; i < rows.size(); i++){
		for(int j = 0; j < a1->Cols(); j++){
			subMatrix->Set(i,j, a1->Val(rows[i], j)); 
		}
	}

	return subMatrix;
}
//Takes a gauss jordan elimination on a matrix to find the inverse and returns pointer to inverse
Bitmatrix *Inverse(const Bitmatrix *m){
	Bitmatrix* cpM = m->Copy();
	Bitmatrix* inv = new Bitmatrix(m->Rows(), m->Cols());
	if(m->Rows() != m->Cols()){
		delete inv;
		delete cpM;
		return NULL;
	}
	for(int i = 0; i < m->Rows(); i++){
		inv->Set(i, i, '1');
	}
	for(int i =0; i < m->Rows();  i++){
		if(cpM->Val(i,i) == '0'){
			if(i == cpM->Rows()-1){
				delete inv;
				delete cpM;
				return NULL;
			}
			for(int j = i; j < cpM->Rows(); j++){
				if(cpM->Val(j+1,i) == '1'){
					cpM->Swap_Rows(i,j+1);
					inv->Swap_Rows(i,j+1);
					break;
				}
			}
			if(cpM->Val(i,i) == '0'){	
				delete inv;
				delete cpM;
				return NULL;
			}
		}
		for(int j = i+1; j<cpM->Rows(); j++){
			if(cpM->Val(j,i) == '1'){
				cpM->R1_Plus_Equals_R2(j,i);
				inv->R1_Plus_Equals_R2(j,i);
			}
		}

	}
	for(int i = cpM->Rows()-1; i >0; i--){
		for(int j = i; j >= 0; j--){
			if(cpM->Val(j,i) == '1'){
				cpM->R1_Plus_Equals_R2(j,i);
				inv->R1_Plus_Equals_R2(j,i);
			}
		}
	} 
	return inv;
}


//Creates hash table of specified size
BM_Hash::BM_Hash(int size)
{
	try{
		if(size <=0) throw ((string) "Bad size");
	}
	catch (string s){	
		cout << s << endl;
		return;
	}
	Table.resize(size);
}
//Stores bitmatrix in hash table based on hashed key
bool BM_Hash::Store(const string &key, Bitmatrix *bm){
	unsigned int hash, index;
	HTE newHTE;
	hash = djb_hash(key);
	index = hash%Table.size();
	if(bm->Rows() == 0 || bm->Cols() == 0) return false;
	if(Table[index].size() != 0){
		for(size_t i = 0; i < Table[index].size(); i++){
			if(Table[index][i].key == key){
				return false;
			}
		}
	}else{
		if(Table[index].size() == 0){
			newHTE.key = key;
			newHTE.bm = bm;
			Table[index].push_back(newHTE);
			return true;
		}
	}
	newHTE.key = key;
	newHTE.bm = bm;
	Table[index].push_back(newHTE);
	return true;
	//	if(Table[index][Table.size()-1].key == key){ 
	//		return true;
	//	} 
	//	return false;
}
//Returns pointer to bitmatrix from hash table
Bitmatrix *BM_Hash::Recall(const string &key) const{
	unsigned int hash, index;	

	hash = djb_hash(key);
	index = hash%Table.size();
	if(Table[index].size() == 0) return NULL;
	for(size_t i = 0; i < Table[index].size(); i++){
		if(Table[index][i].key == key) return Table[index][i].bm;
	}


	return NULL;
}
//Outputs vector of all objects in hash table
vector <HTE> BM_Hash::All() const{
	vector <HTE> rv;
	for(size_t i = 0; i < Table.size(); i++){
		for(size_t j = 0; j < Table[i].size(); j++){
			rv.push_back(Table[i][j]);
		}
	}

	return rv;
}
