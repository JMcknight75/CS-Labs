//Lab 9 Shifter ss_solver.cpp Justin McKnight
//11/9/21 CS202
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

class Shifter {
	public:
		bool Read_Grid_And_Shapes(int argc, const char **argv);
		void Apply_Shape(int index, int r, int c);
		bool Find_Solution(int index);
		void Print_Solution() const;
	protected:
		vector <string> Grid;                   
		vector < vector <string> > Shapes;     
		vector <int> Solution_Rows;            
		vector <int> Solution_Cols;            
};

int main(int argc, const char **argv){
	Shifter game;

	game.Read_Grid_And_Shapes(argc, argv);
	game.Find_Solution(0);
	game.Print_Solution();
	return 0;
}
//Reads in Grid from command line and Shapes from standard input and puts them in vectors
bool Shifter::Read_Grid_And_Shapes(int argc, const char **argv){
	istringstream ss;
	string row;
	int i;
	size_t size;
	vector<string> shape;

	for(i = 1; i < argc; i++){
		ss.clear();
		ss.str(argv[i]);
		ss >> row;
		if(i == 1) size = row.size();
		if(row.size() != size) return false;
		Grid.push_back(row);
	}
	/*Get shape from std. input then splits into words with stringstream and pushes into shape vector,
	  then pushes shape vector into Shapes vector*/
	while(getline(cin, row)){
		ss.clear();
		shape.clear();
		ss.str(row);
		while(ss >> row){
			if(row != " "){
			shape.push_back(row);
			}
		}
		Shapes.push_back(shape);
	}
	Solution_Rows.resize(Shapes.size(), -1);
	Solution_Cols.resize(Shapes.size(), -1);
	return true;
}
//Applies shape to grid at row and column indexes given and inverts the 1s and 0s
void Shifter::Apply_Shape(int index, int r, int c){
	string row;
	size_t i,j;
	for(i = 0; i < Shapes[index].size(); i++){
		row = Shapes[index][i];
		for(j = 0; j < row.size(); j++){
			if(row[j] == '1'){
				if(Grid[r+i][c+j] == '0'){
					Grid[r+i][c+j] = '1';
				}else{
					Grid[r+i][c+j] = '0';
				}
			}
		}
	}
}
//Recursivley calls itself to find the positions each shape must be placed in for the solution
bool Shifter::Find_Solution(int index){
	size_t i, j, r;
	string test;
//Tests grid to see if it is composed of all 0s
	if(index == Shapes.size()){
		test.resize(Grid[0].size(), '1');
		for(r = 0; r < Grid.size(); r++){
			if(Grid[r] != test){
				return false;
			}
		}
		return true;
	}
//Tests each shape at each viable location recursively and sets the index of the rows and columns to the Solution_Rows and Solution_Cols vectors
	for(i = 0; i < Grid.size(); i++){
		for(j = 0; j < Grid[0].size(); j++){
			if(j + Shapes[index][0].size() <= Grid[0].size()){
				if(i + Shapes[index].size() <= Grid.size()){
					Apply_Shape(index, i, j);
					Solution_Rows[index] = i;
					Solution_Cols[index] = j;
					if(!Find_Solution(index+1)){
						Apply_Shape(index,i,j);
						Solution_Rows[index] = -1;
						Solution_Cols[index] = -1;
					}else{
						return true;
					}
				}
			}
		}

	}
	return false;	
}
//Prints Shape and where it must be placed to complete solution
void Shifter::Print_Solution() const{
	for(size_t i = 0; i < Shapes.size(); i++){
		for(size_t j = 0; j < Shapes[i].size(); j++){
			if(Solution_Rows[0] == -1) return;
			cout << Shapes[i][j] << " ";
		}
		cout << Solution_Rows[i] << " " << Solution_Cols[i] << endl;
	}

	return;	
}

