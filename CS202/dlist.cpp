//Justin McKnight 11/2/21 CS202
//Lab8 DList
#include <iostream>
#include "dlist.hpp"

using namespace std;
//returns next node in list
Dnode *Dnode::Next(){
	return flink;
}
//returns node before this node in list
Dnode *Dnode::Prev(){
	return blink;
}
//constructor declares sentinel with new and sets blink and flink equal to sentinel.
Dlist::Dlist(){
	size = 0;
	sentinel = new Dnode;
	sentinel->blink = sentinel;
	sentinel->flink = sentinel;
}
//Copy Constructor uses pushback on new sentinel to create a copy
Dlist::Dlist(const Dlist &d){
	Dnode *tmp;
	sentinel = new Dnode;
	sentinel->blink = sentinel;
	sentinel->flink = sentinel;

	for(tmp = d.Begin(); tmp != d.End(); tmp=tmp->flink) Push_Back(tmp->s);
}
//Assignment operator clears list then pushes elements of list d onto new list
Dlist& Dlist::operator= (const Dlist &d){
	Dnode *tmp;
	Dlist newList;

	Clear();
	for(tmp = d.Begin(); tmp!=d.End(); tmp =tmp->flink) Push_Back(tmp->s);
	return *this;
}
//Destructor clears list then deletes sentinel node
Dlist::~Dlist(){
	Clear();
	delete sentinel;
}
//Clears list using pop back until size = 0, leaving only sentinel node
void Dlist::Clear(){
	while(size != 0){
		Pop_Back();
	}
	return;
}
//Checks if size is 0
bool Dlist::Empty() const{
	if(size == 0) return true;
	return false;
}
//returns size member
size_t Dlist::Size() const {
	return size;
}


//Puts new node on front of the list
void Dlist::Push_Front(const std::string &s){
	Dnode* node = new Dnode;
	Dnode* tmp= NULL;

	node->s = s;
	tmp = sentinel->flink;
	tmp->blink = node;
	sentinel->flink = node;
	node->flink = tmp;
	node->blink = sentinel;
	size++;
}
//Puts new node on the back of the list
void Dlist::Push_Back(const std::string &s){
	Dnode* node = new Dnode;
	Dnode* tmp = NULL;

	node->s = s;
	tmp = sentinel->blink;
	tmp->flink =  node;
	sentinel->blink = node;
	node->flink = sentinel;
	node-> blink = tmp;
	size++;
}


//Deletes the first element of the list
std::string Dlist::Pop_Front(){
	Dnode* node;
	string rv;

	node = sentinel->flink;
	sentinel->flink = node->flink;
	node->flink->blink = sentinel;
	rv = node->s;
	size--;
	delete node;
	return rv;
}
//deletes the last element of the list
std::string Dlist::Pop_Back(){
	Dnode* node;
	string rv;

	node =  sentinel->blink;
	sentinel->blink = node->blink;
	node->blink->flink = sentinel;
	rv = node->s;
	size--;
	delete node;
	return rv;
}
Dnode *Dlist::Begin() const{
	return sentinel->flink;
}         // Pointer to the first node on the list 
Dnode *Dlist::End() const{
	return sentinel;
}         // Pointer to "one past" the last node on the list.
Dnode *Dlist::Rbegin() const{
	return sentinel->blink;
}        // Pointer to the last node on the list
Dnode *Dlist::Rend() const{
	return sentinel;
}          // Pointer to "one before" the first node on the list.

//Inserts element before given node
void Dlist::Insert_Before(const std::string &s, Dnode *n){
	Dnode* node = new Dnode;
	Dnode* tmp = NULL;

	node->s = s;
	if(n->blink == sentinel){
		Push_Front(s);
		delete node;
		return;
	}
	tmp = n->blink;
	tmp->flink = node;
	n->blink = node;
	node->blink = tmp;
	node->flink = n;
	size++;
}
//Inserts element after given node
void Dlist::Insert_After(const std::string &s, Dnode *n){
	Dnode* node = new Dnode;
	Dnode* tmp;

	if(n->flink == sentinel){
		Push_Back(s);
		delete node;
		return;
	}
	node->s = s;
	tmp = n->flink;
	tmp->blink = node;
	n->flink = node;
	node->blink = n;
	node->flink = tmp;
	size++;
}
//Deletes given node
void Dlist::Erase(Dnode *n){
	Dnode *tmp1, *tmp2;

	tmp1 = n->flink;
	tmp2 = n->blink;

	tmp1->blink = tmp2;
	tmp2->flink = tmp1;
	size--;
	delete n;
}

