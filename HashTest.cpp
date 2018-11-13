//Testing driver for hashing header
//Written by Tristan Jordan

#include <iostream>
#include <vector>
#include <string>
#include "hashString.h"
using namespace std;

int main() {
	string msg;
	cout << "Enter message: \n";
	getline(cin, msg);
	

	cout << "Hashed: ";
	cout << hashString(msg);
	cin >> msg;
}
