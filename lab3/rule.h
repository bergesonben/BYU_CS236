/*
 * rule.h
 *
 *  Created on: Feb 8, 2015
 *      Author: benjamin
 */

#ifndef RULE_H_
#define RULE_H_
#include "predicate.h"

using namespace std;

class rule
{
public:
	rule(){}
	~rule(){}
	predicate headPredicate;
	vector<predicate> predList;
	void addHead(predicate a)
	{
		headPredicate = a;
	}

	void addPred(predicate x)
	{
		predList.push_back(x);
	}

	void addPred(vector<predicate> v)
	{
		predList.insert(predList.end(), v.begin(), v.end());
	}

	string toString()
	{
		string output = headPredicate.toString() + " :- ";
		for(int i = 0; i < predList.size()-1; i++)
		{
			output += predList[i].toString() + ",";
		}
		output += predList[predList.size()-1].toString();

		return output;
	}

};



#endif /* RULE_H_ */
