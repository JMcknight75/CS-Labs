//Justin McKnight 8/25/21 CS202
//Lab 0
#include <iostream>

using namespace std;

/*This program takes a text file as an input through the console and searches
character by character to find a letter and adds its value(starting from 'A' as 1) to
a running point total and prints it at the end.*/
int main() {
	char c;
	int points;

	points = 0;
/*Takes each character and checks if its value is between A and Z and assigns a point total to it based
on its distance from 'A' and adds that amount of points to the points int.*/
	while (cin >> c){
		if((c>='A') && (c<='Z')){
			points= points+ c-'A'+1;
		}
	}
	cout << points<<endl;
	return 0;
}
