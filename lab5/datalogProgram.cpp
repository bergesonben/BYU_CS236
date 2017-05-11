/*
 * datalogProgram.cpp
 *
 *  Created on: Feb 8, 2015
 *      Author: benjamin
 */
#include "datalogProgram.h"
#include <sstream>
#include <algorithm>

void datalogProgram::addScheme(scheme s)
{
	schemesList.push_back(s);
}

void datalogProgram::addFact(scheme f)
{
	factsList.push_back(f);
	domain.insert(domain.end(), f.parameterList.begin(), f.parameterList.end());
}

void datalogProgram::addRule(rule r)
{
	rulesList.push_back(r);
}

void datalogProgram::addQuery(predicate p)
{
	queryList.push_back(p);
}

void datalogProgram::makeDomain()
{

	sort(domain.begin(), domain.end());
	domain.erase(unique(domain.begin(), domain.end()), domain.end());
}

string datalogProgram::toString()
{
	string output;
	output = "Schemes(" + intToString(schemesList.size()) + "):\n";
	for(int i = 0; i < schemesList.size(); i++)
	{
		output += "  " + schemesList[i].toString() + "\n";
	}
	output += "Facts(" + intToString(factsList.size()) +  "):\n";
	for(int i = 0; i < factsList.size(); i++)
	{
		output += "  " + factsList[i].toString() + ".\n";
	}
	output += "Rules(" + intToString(rulesList.size()) + "):\n";
	for(int i = 0; i < rulesList.size(); i++)
	{
		output += "  " + rulesList[i].toString() + ".\n";
	}

	output += "Queries(" + intToString(queryList.size()) + "):\n";
	for(int i = 0; i < queryList.size(); i++)
	{
		output += "  " + queryList[i].toString() + "?\n";
	}

	output += "Domain(" + intToString(domain.size()) + "):\n";
	for(int i = 0; i < domain.size(); i++)
	{
		output += "  " + domain[i] + "\n";
	}
	return output;

}



string datalogProgram::intToString(int x)
{
	stringstream convert;
	convert << x;
	string output = convert.str();
	return output;
}


