//Program written by Tristan Jordan
//Purpose is to demonstrate a hashing algorithm

#ifndef HASHSTRING_H
#define HASHSTRING_H

#include <iostream>
#include <vector>
#include <string>

std::string hashString(std::string msg) {
	//The list of characters which, in a more abstract form, is also the blocks
	std::vector<int> charStream;

	//Transform string into an appropriate stream
	for (int i = 0; i < msg.length(); i++) {
		if (msg[i] <= 'z' && msg[i] >= 'a') {
			charStream.push_back(msg[i] - 'a');
		}
		else if (msg[i] <= 'Z' && msg[i] >= 'A') {
			charStream.push_back(msg[i] - 'A');
		}
	}

	//Padding to ensure that all blocks are correctly sized
	int padding = 16 - (charStream.size() % 16);
	for (int i = 0; i < padding; i++) {
		charStream.push_back(0);
	}

	//running total, ultimate hash
	int runningT[] = { 0,0,0,0 };

	//the number of "blocks"
	int blocks = charStream.size() / 16;
	//The never changing size of a "block" which is 4 rows and 4 cols
	const int rowSize = 4;
	//location of a character in a "block"
	int location = 0;

	//hash begins
	for (int i = 0; i < blocks; i++) {
		int c = 0; int r = 0;

		//Phase 1
		for (int j = 0; j < rowSize; j++) {
			for (int k = 0; k < rowSize; k++) {
				location = (i * 16) + j + (k * 4);
				runningT[j] += charStream[location];
			}
		}

		//Hash
		for (int j = 0; j < rowSize; j++) {
			runningT[j] = runningT[j] % 26;
		}

		//shift dictates what part of the block is being accessed,cur iterates over the list
		int shift[] = { 1,2,3,0,6,7,4,5,11,8,9,10,15,14,13,12 };
		int cur = 0;

		//phase 2
		for (int j = 0; j < rowSize; j++) {
			for (int k = 0; k < rowSize; k++) {
				location = (i * 16) + shift[cur];
				runningT[cur % 4] += charStream[location];
				cur++;
			}
		}

		//Hash
		for (int j = 0; j < rowSize; j++) {
			runningT[j] = runningT[j] % 26;
		}
	}

	//this will be the string that is returned
	std::string temp = "";

	//Output of hash
	for (auto c : runningT) {
		temp += (char)(c + 65);
	}

	return temp;
}

#endif
