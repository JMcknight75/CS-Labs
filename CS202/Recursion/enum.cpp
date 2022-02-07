#include <iostream>
#include <string>
#include <sstream>
using namespace std;
//Recursively calls itself to build string then as its returning sets first 0 it finds to 1 and calls itself recursively again
void do_enumeration(string &s, int index, int n_ones){
	if(index == s.size()){
		cout << s<< endl;;
		return;
	}
	if(s.size()-index > n_ones){
		s[index] = '0';
		do_enumeration(s, index+1, n_ones);
	}else{
		s[index] = '1';
		do_enumeration(s, index+1, n_ones-1);
	}
	if(s[index] == '1') s[index] = '-';
	if(s[index] == '0'){
		if(n_ones > 0){
			s[index] = '1';
			do_enumeration(s, index+1, n_ones-1);
		}
		if(n_ones == 0 && index+1 != s.size()){
			if(s[index] != '0'){
				s[index] = '0';
				do_enumeration(s, index+1, n_ones);
			}
		}
	}
	return;
}

//Error checks and calls first call of do-enumeration
int main(int argc, char* argv[]){
	string s;
	int size, n_ones;
	istringstream iss(argv[1]);
	istringstream iss2(argv[2]);

	if(argc != 3) return 0;
	if(!(iss >> size)){
		return 0;
	}
	iss2>>n_ones;

	s.resize(size, '-');
	do_enumeration(s, 0, n_ones);
	return 0;
}
