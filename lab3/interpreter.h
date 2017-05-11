/*
 * interpreter.h
 *
 *  Created on: Mar 1, 2015
 *      Author: benjamin
 */

#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "parser.h"
#include "database.h"

using namespace std;

class interpreter
{
public:
	interpreter(){}
	~interpreter(){}

//functions
	void start(string inputFile);

//variables
	vector<scheme> schemesList;
	vector<scheme> factsList;
	vector<string> domain;
	vector<rule> rulesList;
	vector<predicate> queryList;
private:
	parser myParser;
	database db;

};




#endif /* INTERPRETER_H_ */
