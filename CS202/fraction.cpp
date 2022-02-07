//Lab6 Justin McKnight Keno Lab 10/19/21
//CS202
#include <iostream>
#include <set>
#include "fraction.hpp"

using namespace std;
//Fraction class that allows you to multiply/divide number, factorial, and binomial coefficient
//Clears numerator and denominator
void Fraction::Clear(){
	numerator.clear();
	denominator.clear();
}
//Add a number to numerator
bool Fraction::Multiply_Number(int n){
	multiset <int>::iterator nit;

	if(n == 1){
		return true;
	}
	if(n<=0){
		return false;
	}
	if(!(denominator.empty())){
		nit = denominator.find(n);
		if(nit != denominator.end()){
			denominator.erase(nit);	
			return true;
		}
	}
	numerator.insert(n);
	return true;
}
//Add a number to the denominator
bool Fraction::Divide_Number(int n){
	multiset <int>::iterator dit;
	if(n <= 0) return false;
	if(n ==1) return true;
	if(!(numerator.empty())){
		dit = numerator.find(n);
		if(dit != numerator.end()){
			numerator.erase(dit);	
			return true;
		}
	}
	denominator.insert(n);
	return true;
}

// Add the numbers 2 through n to the numerator
bool Fraction::Multiply_Factorial(int n){
	if(n<=0) return false;
	if(n==1) return true;
	for(int i = n; i > 1; i--){
		Multiply_Number(i);
	}
	return true;
}
// Add the numbers 2 through n to the denominator
bool Fraction::Divide_Factorial(int n){
	if(n <= 0) return false;
	if(n == 1) return true;

	for(int i = n; i > 1; i--){
		Divide_Number(i);
	}
	return true;
}
//Multiply n-choose-k
bool Fraction::Multiply_Binom(int n, int k){	
	if(n <= 0 || k < 0) return false;
	if(k == 0) return true;

	Multiply_Factorial(n-k);
	Divide_Factorial(k);
	
	return true;
}
//Divide n-choose-k
bool Fraction::Divide_Binom(int n, int k){	
	if(n <= 0 || k < 0) return false;
	if(k == 0) return true;
	Divide_Factorial(n-k);
	Multiply_Factorial(k);
	
	return true;
}
//Swaps numerator and denominator
void Fraction::Invert(){
	multiset <int> tmp;

	tmp = numerator;
	numerator = denominator;
	denominator = tmp;
}
//Prints numerator and denominator
void Fraction::Print() const{
	multiset <int>::const_iterator nit;
	multiset <int>::const_iterator dit;
	
	if(!(numerator.empty())){
		for (nit =  numerator.begin(); nit != numerator.end(); nit++){
		if(nit != numerator.begin()){
			cout << " * ";
		}
		cout << *nit;
	}
	}else{
		cout << 1;
	}
	if(!(denominator.empty())){
		for (dit = denominator.begin(); dit != denominator.end(); dit++){
			cout << " / " << *dit;
		}
	}
	cout << endl;	
}
//multiplies numerator together and denominator together then divides numerator / denominator and returns value
double Fraction::Calculate_Product() const{
	double n,d, prod;
	multiset <int>::iterator nit, dit;

	n=1;
	d=1;
	for(nit = numerator.begin(); nit != numerator.end(); nit++){
		n *= *nit;
	}
	for(dit = denominator.begin(); dit != denominator.end(); dit++){
		d *= *dit;
	}
	prod = n/d;
	return prod;
}
