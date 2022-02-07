#include "hash_202.hpp"
#include <sstream>
#include <iostream>
#include <stdio.h>
using namespace std;

int XOR(string);
int Last7(string);
//Sets up hash table of given size and sets hash function and collision type;
string Hash_202::Set_Up(size_t table_size, const std::string &fxn, const std::string &collision){
	if(Keys.size() > 0){
		return "Hash table already set up";
	}
	if(table_size == 0){
		return "Bad table size";
	}
	if(fxn != "Last7" && fxn != "XOR"){
		return "Bad hash function";
	}
	if(collision != "Linear" && collision != "Double"){
		return "Bad collision resolution strategy";
	}
	Nkeys = 0;
	Nprobes =0;
	Keys.resize(table_size);
	Vals.resize(table_size);
	if(fxn == "Last7"){
		Fxn = 'L';
	}else{
		Fxn = 'X';
	}
	if(collision == "Linear"){
		Coll = 'L';
	}else{
		Coll = 'D';
	}
	return "";
}
//Adds a value to the hash table based on the key given and the Hash functiona and collision type
string Hash_202::Add(const string &key, const string &val){
	int hash,index, firstHash;
	vector<string> xorHash;
	vector<int> hashVal;
//Error checking to see status of Hash table and key
	if(Keys.size() == 0){
		return "Hash table not set up";
	}
	if(key == ""){
		return "Empty key";
	}
	for(size_t i = 0; i < key.size(); i++){
		if(!(key[i] >= '0' && key[i] <= '9') && !(key[i] >= 'a' && key[i] <= 'f')){
			return "Bad key (not all hex digits)";
		}
	}
	if(val == ""){
		return "Empty val";
	}
	if(Nkeys == Keys.size()){
		return "Hash table full";
	}
//checks function and collision type and hashes the key and probes in case of collisions
	if(Fxn == 'L'){
		hash = Last7(key);
		for(size_t i = 0; i < Keys.size(); i++){
			if(Keys[i] == key){
				return "Key already in the table";
			}
		}
		index = hash%Keys.size();
		if(Keys[index] == ""){
			Keys[index] = key;
			Vals[index] = val;
			Nkeys++;
			return "";
		}else if(Coll == 'L'){
			for(size_t i=0;i<Keys.size();i++){
				index = (hash+i)%Keys.size();
				if(Keys[index]==""){
					Keys[index] = key;
					Vals[index]= val;
					Nkeys++;
					return "";
				}
			}
		}else if(Coll == 'D'){
			firstHash = hash;
			hash = 0;
			hash = XOR(key);
//if second increment is 0 sets hash to 1
			if(hash%Keys.size() == 0){
				hash = 1;
			}
			for(size_t i=0;i<Keys.size();i++){
				index = (firstHash+((hash%Keys.size())*i))%Keys.size();
				if(Keys[index]==""){
					Keys[index] = key;
					Vals[index]= val;
					Nkeys++;
					return "";
				}

			}
			return "Cannot insert key";
		}	
	}
	if(Fxn == 'X'){
		hash = XOR(key);
		for(size_t i = 0; i < Keys.size(); i++){
			if(Keys[i] == key){
				return "Key already in the table";
			}
		}
		index = hash % Keys.size();
		if(Keys[index] == ""){
			Keys[index] = key;
			Vals[index] = val;
			Nkeys++;
			return "";
		}else if(Coll == 'L'){
			for(size_t i = 0; i < Keys.size(); i++){
				index = (hash+i)%Keys.size();
				if(Keys[index]==""){
					Keys[index] = key;
					Vals[index]= val;
					Nkeys++;
					return "";
				}
			}
		}else if(Coll == 'D'){
			firstHash = hash;
			hash=Last7(key);
			if(hash%Keys.size() == 0){
				hash = 1;
			}
			for(size_t i=0;i<Keys.size();i++){
				index = (firstHash+((hash%Keys.size())*i))%Keys.size();
				if(Keys[index]==""){
					Keys[index] = key;
					Vals[index]= val;
					Nkeys++;
					return "";
				}
			}
			return "Cannot insert key";
		}
	}
//Checks in key is in the table
	for(size_t i = 0; i < Keys.size(); i++){
		if(Keys[i] == key){
			return "Key already in the table";
		}
	}
	return "";
}
//Finds a given key in the hash table then returns the value
string Hash_202::Find(const string &key){
	int hash,index, firstHash, probes;
	vector<string> xorHash;
	vector<int> hashVal;
	index = 0;
	probes = 0;
//Error cheking
	if(Keys.size() == 0){
		return "";
	}
	for(size_t i = 0; i < key.size(); i++){
		if(!(key[i] >= '0' && key[i] <= '9') && !(key[i] >= 'a' && key[i] <= 'f')){
			return "";
		}
	}
//Checks Hash function and collision type and then checks if the given key is in the location given by the hash function, and in case of collisions probes based on collision type and count amount of probes
	if(Fxn == 'L'){
		hash = Last7(key);
		index = hash%Keys.size();
		if(Keys[index] == key){
			//			Nprobes++;
			return Vals[index];
		}else if(Coll == 'L'){
			for(size_t i=1;i<Keys.size();i++){
				index = (hash+i)%Keys.size();
				if(Keys[index]==key&&Vals[index]!=""){
					Nprobes++;
					Nprobes += probes;
					return Vals[index];
				}else{
					probes++;
				}
			}
		}else if(Coll == 'D'){
			firstHash = hash;
			hash = XOR(key);
			if(hash%Keys.size() == 0){
				hash = 1;
			}
			for(size_t i=1;i<Keys.size();i++){
				index = (firstHash+((hash%Keys.size())*i))%Keys.size();
				if(Keys[index]==key && Vals[index] != ""){
					Nprobes++;
					Nprobes += probes;
					return Vals[index];
				}else{
					probes++;
				}
			}
		}	
	}
	if(Fxn == 'X'){
		hash = XOR(key);
		index = hash % Keys.size();
		if(Keys[index] == key){
			return Vals[index];
		}else if(Coll == 'L'){
			for(size_t i = 1; i < Keys.size(); i++){
				index = (hash+i)%Keys.size();
				if(Keys[index]==key &&Vals[index] != ""){
					Nprobes++;
					Nprobes += probes;
					return Vals[index];
				}else{
					probes++;
				}
			}
		}else if(Coll == 'D'){
			firstHash = hash;
			hash=Last7(key);
			if(hash%Keys.size() == 0){
				hash = 1;
			}
			for(size_t i=1;i<Keys.size();i++){
				index = (firstHash+((hash%Keys.size())*i))%Keys.size();
				if(Keys[index]==key && Vals[index]!=""){
					Nprobes++;
					Nprobes += probes;
					return Vals[index];
				}else{
					probes++;
				}
			}	
		}
	}
	return "";
}
//Prints the hash table sequentially
void Hash_202::Print() const{
	if(Keys.size() != 0){
		for(size_t i = 0; i < Keys.size(); i++){
			if(Keys[i] != ""){
				printf("%5lu %s %s\n",i, Keys[i].c_str(), Vals[i].c_str());
			}
		}
	}
}
//returns the total amount of probes required to find every key
size_t Hash_202::Total_Probes(){
	if(Keys.size()==0){
		return 0;
	}
	Nprobes = 0;
	for(size_t i = 0; i < Keys.size(); i++){
		Find(Keys[i]);
	}

	return Nprobes;
}
//splits the key up into 7 digit words and xors them as hex and returns this value as the hash
int XOR(string key){
	int hash = 0;
	int j;
	istringstream ss;
	vector<string> xorHash;
	vector<int> hashVal;
	if(key.size()%7==0){
		xorHash.resize(key.size()/7);
	}else{
		xorHash.resize((key.size()/7)+1);
	}
	hashVal.resize(xorHash.size()); 
	j=0;
	for(size_t i = 0; i < key.size(); i=i+7){
		if(i+7 >= key.size()){
			xorHash[j] = key.substr(i);
		}else{
			xorHash[j] = key.substr(i,7);
		}
		j++;
	}


	for(size_t i = 0; i < xorHash.size(); i++){
		ss.clear();
		ss.str(xorHash[i]);
		ss >> hex >> hashVal[i];
		hash = hash^ hashVal[i];
	}
	return hash;
}
//Takes the last 7 digits of the key and returns this value as the hash
int Last7(string key){	
	int strIndex, hash;
	string tmpString;
	istringstream ss;

	hash = 0;
	if(key.size() > 7){
		strIndex = key.size()-7;
	}else{
		strIndex = 0;
	}
	tmpString=key.substr(strIndex);
	ss.clear();
	ss.str(tmpString);
	ss >> hex >> hash;
	return hash;
}
