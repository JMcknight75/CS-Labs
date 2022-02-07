//Justin Mcknight 8/31/21 CS202
//Moonglow lab lab1
#include <iostream>
#include <vector>

using namespace std;
/*This program takes a test file and outputs an easy to read format of the useful information. It prints the name of the student followed by the overall score.
 * To get a score the program adds the different numbers in the file to the total score unless the numbers follow the word "AVERAGE", in which the program will average the numbers until
 * it is given a non-number or end of file.
 */
int main(){
	string name;
	string word;
	double score=0;
	double num;
	double average=0;
	double count;
//Reads in number first, if fails checks for string, if succedes adds to score
	while(true){
		cin >> num;
//When end of file is reached, prints the name and score and ends the program.
		if(cin.eof()){
			cout << name <<" "<< score<< endl;
			return 0;
		}
		if(!(cin.fail())){
			score += num;

		}
//If word read is NAME, reads following word as the name of student
		if(cin.fail()){
			cin.clear();
			cin >> word;
			if(word =="NAME"){
				cin >> name;
			}
//If word read is Average, reads following entries as numbers and averages them out until it reaches a non-number or eof.
			if(word =="AVERAGE"){
				count = 0;
				average = 0;
				while(true){
					cin >> num;
					if(cin.eof()){
						score += average/count;
						break;
					}
					if(cin.fail()) {
						if(count> 0){
							score = score + average/count;
						}
						cin.clear();
						break;
					}
					average = average + num;
					count++;
				}
			}
		}
	}
	return 0;
}
