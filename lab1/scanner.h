/*
 * scanner.h
 *
 *  Created on: Jan 26, 2015
 *      Author: benjamin
 */

#ifndef SCANNER_H_
#define SCANNER_H_
#include "token.h"
#include <fstream>
#include <vector>

class scanner
{
public:
	scanner(){}
	~scanner(){}
	void scan(string fileName);
	void scanToken();
	void scanID();
	void scanStr();
	void scanComm();
	void makeToken(tokType type, int lineNum);
	//void valueToUpper(); For case-insensitivity

private:
	ifstream inputFile;
	ofstream outputFile;
	int line = 1;
	char curr;
	char next;
	string value = "";
	//string valueUpper = ""; For case-insensitivity
	int lineStart = 0;
	vector<token> myVector;
};



#endif /* SCANNER_H_ */
