//Lab7 Code Processing lab CS202 10/26/21 Justin McKnight
#include <set>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include "code_processor.hpp"

using namespace std;
//Hash function as defined in random_codes.cpp
unsigned int djb_hash(const string &s){
	size_t i;
	unsigned int h;

	h = 5381;

	for (i = 0; i < s.size(); i++) {
		h = (h << 5) + h + s[i];
	}
	return h;
}
//Adds a prize to the Prizes map and error checks
bool Code_Processor::New_Prize(const string &id, const string &description, int points, int quantity){
	Prize* newPrize;

	if(Prizes.find(id) != Prizes.end()){
		return false;
	}
	if(points <= 0 || quantity <= 0){
		return false;
	}
	newPrize = new Prize;
	newPrize->id = id;
	newPrize->description = description;
	newPrize->points = points;
	newPrize->quantity = quantity;
	if(Prizes.find(id) != Prizes.end()){
		return false;
	}
	Prizes.insert(pair<string, Prize*>(id, newPrize));
	return true;
}
//Adds a user to the Names map and error checks
bool Code_Processor::New_User(const string &username, const string &realname, int starting_points){
	User* user = new User;
	if(Names.find(username) != Names.end()){
		delete user;
		user = NULL;
		return false;
	}
	if(starting_points < 0){
		delete user;
		user = NULL;
		return false;
	}
	user->username = username;
	user->realname=realname;
	user->points = starting_points;
	Names.insert(pair<string, User*>(username, user));
	return true;
}
//Deletes User from Names map, deletes all phone numbers from the user in the Phones map, and clears users phone_numbers set. Also deletes pointers to clear memory
bool Code_Processor::Delete_User(const string &username){
	User* user;
	string phone;
	set<string>::const_iterator pit;

	if(Names.find(username) == Names.end()) return false;
	user = Names.find(username)->second;
//Erases from Phones map instead of calling Remove phone, as it is iterating through phone_numbers and Remove phone would resize phone_numbers
	for(pit = user->phone_numbers.begin(); pit != user->phone_numbers.end(); pit++){
		Phones.erase(*pit);
	}
	user->phone_numbers.clear();
	delete Names.find(username)->second;
	Names.erase(username);
	user = NULL;
	return true;
}
//Adds phone number to user by adding phone to Phones map with User* pointing to the user, and adds phone number to users phone_numbers set
bool Code_Processor::Add_Phone(const string &username, const string &phone){
	User* user;
	if(Names.find(username) == Names.end()){
		return false;
	}
	if(Phones.find(phone) != Phones.end()){
		return false;
	}
	user = Names.find(username)->second;
	user->phone_numbers.insert(phone);
	Phones.insert(pair<string, User*>(phone, user));
	return true;
}
//Removes Phone Number from Phones map and users phone_numbers set
bool Code_Processor::Remove_Phone(const string &username, const string &phone){
	User* user;
	if(Names.find(username) == Names.end()) return false;
	if(Phones.find(phone) == Phones.end()) return false;
	if(Phones.find(phone)->second->username != username) return false;
	user = Names.find(username)->second;
	user->phone_numbers.erase(phone);
	Phones.erase(phone);

	return true;
}
//returns string containing all of users phone numbers separated by newline and sorted. Goes through user's phone_numbers set to find numbers.
string Code_Processor::Show_Phones(const string &username) const{
	User* user;
	string tmpStr= "";
	set<string>::const_iterator pit;

	if(Names.find(username) == Names.end()) return "BAD USER";
	user=Names.find(username)->second;
	for(pit = user->phone_numbers.begin(); pit != user->phone_numbers.end(); pit++){
		tmpStr += (*pit + "\n");
	}

	return tmpStr;
}
//Checks if code has already been used and if not adds code to Codes set and adds points based on hash to User
int Code_Processor::Enter_Code(const string &username, const string &code){
	User* user;

	if(Names.find(username) == Names.end() || Codes.find(code) != Codes.end()) return -1;
	user = Names.find(username)->second;
	if(djb_hash(code)%17 == 0){
		Codes.insert(code);
		user->points += 10;
		return 10;
	}else if(djb_hash(code)%13 == 0){
		Codes.insert(code);
		user->points += 3;
		return 3;
	}
	
	return 0;
}
//Checks if code has already been used and if not, calls Enter_code with username associated with phone number
int Code_Processor::Text_Code(const string &phone, const string &code){
	string username;

	if(Phones.find(phone) == Phones.end() || Codes.find(code) != Codes.end()) return -1;
	username = Phones.find(phone)->second->username;
	return Enter_Code(username, code);
}
//Marks code as used by putting code into Codes set
bool Code_Processor::Mark_Code_Used(const string &code){
	if(djb_hash(code) % 17 != 0 && djb_hash(code)%13 != 0) return false;
	if(Codes.find(code) != Codes.end()) return false;
	
	Codes.insert(code);
	return true;
}
//returns the points value of a selected user
int Code_Processor::Balance(const string &username) const{
	int userPoints;

	if(Names.find(username) == Names.end()) return -1;
	userPoints = (Names.find(username))->second->points;
	return userPoints;
}
//Error checks then if the user has enough points, subtracts points and decreases quantity of prize by 1. If quantity is now 0, deletes prize
bool Code_Processor::Redeem_Prize(const string &username, const string &prize){
	User* user;
	Prize* redeemable;

	if(Names.find(username) == Names.end() || Prizes.find(prize) == Prizes.end()) return false;
	user = Names.find(username)->second;
	redeemable = Prizes.find(prize)->second;
	if(user->points < redeemable->points) return false;
	user->points -= redeemable->points;
	redeemable->quantity--;
	if(redeemable->quantity == 0) Prizes.erase(prize);
	return true;
}
//Code Processor destructor, deletes User and Prize pointers. Does not set pointers to NULL as program is exiting and iterators are const.
Code_Processor::~Code_Processor(){
	map<string, User *>::const_iterator nit;
	map<string, Prize *>::const_iterator pit;
	
	for(nit = Names.begin(); nit != Names.end(); nit++){
		delete nit->second;
	}
	for(pit = Prizes.begin(); pit != Prizes.end(); pit++){
		delete pit->second;
	}
}
//Writes commands to file in order to make server "fault-tolerant." Outputs contents of all maps and Code set.
bool Code_Processor::Write(const string &filename) const{
	ofstream file;
	map<string, Prize *>::const_iterator pit;
	map<string, User *>::const_iterator nit;
	map<string, User *>::const_iterator phit;
	set<string>::const_iterator cit;

	file.open(filename.c_str());
	if(file.is_open() != true){
		return false;
	}
	for(pit = Prizes.begin(); pit != Prizes.end(); pit++){
		file << "PRIZE " << pit->first << " " << pit->second->points << " " << pit->second->quantity << " " << pit->second->description << endl; 	
	}
	for(nit = Names.begin(); nit != Names.end(); nit++){
		file << "ADD_USER " << nit->first << " " << nit->second->points << " " << nit->second->realname << endl;
	}
	for(phit = Phones.begin(); phit != Phones.end(); phit++){
		file << "ADD_PHONE " << phit->second->username << " " << phit->first << endl;
	}
	for(cit = Codes.begin(); cit != Codes.end(); cit++){
		file  <<"MARK_USED " << *cit << endl;
	}


	return true;
}
