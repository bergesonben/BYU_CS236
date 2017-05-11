/*
 * predicate.h
 *
 *  Created on: Feb 8, 2015
 *      Author: benjamin
 */

#ifndef PREDICATE_H_
#define PREDICATE_H_
#include <string>
#include <vector>
#include "parameter.h"

using namespace std;

class predicate
{
public:
	predicate(string n)
	{
		name = n;
	}
	predicate(){}
	~predicate(){}
	string name;
	vector<parameter> parameterList;
	void addParameter(parameter param)
	{
		parameterList.push_back(param);
	}
	void addParameter(vector<parameter> params)
	{
		parameterList.insert(parameterList.end(),params.begin(), params.end());
	}

	string toString()
	{
		string output;
		output = name + "(";
		for(int i = 0; i < parameterList.size()-1; i++)
		{
			output = output + parameterList[i].value + ",";
		}
		output += parameterList[parameterList.size()-1].value + ")";

		return output;
	}
};



#endif /* PREDICATE_H_ */


/*
 * string name;
	vector<string> parameterList;
	void addParameter(string param)
	{
		parameterList.push_back(param);
	}
	void addParameter(vector<string> params)
	{
		parameterList.insert(parameterList.end(),params.begin(), params.end());
	}

	string toString()
	{
		string output;
		output = name + "(";
		for(int i = 0; i < parameterList.size()-1; i++)
		{
			output = output + parameterList[i] + ",";
		}
		output += parameterList[parameterList.size()-1] + ")";

		return output;
	}
 */
