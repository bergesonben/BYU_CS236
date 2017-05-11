/*
 * datalogProgram.h
 *
 *  Created on: Feb 8, 2015
 *      Author: benjamin
 */

#ifndef DATALOGPROGRAM_H_
#define DATALOGPROGRAM_H_

#include <vector>
#include "scheme.h"
#include "rule.h"

using namespace std;

class datalogProgram
{
public:
	datalogProgram(){}
	~datalogProgram(){}
	void addScheme(scheme s);
	void addFact(scheme f);
	void addRule(rule r);
	void addQuery(predicate p);
	void makeDomain();
	string toString();


private:
	vector<scheme> schemesList;
	vector<scheme> factsList;
	vector<string> domain;
	vector<rule> rulesList;
	vector<predicate> queryList;
	string intToString(int);
};



#endif /* DATALOGPROGRAM_H_ */
