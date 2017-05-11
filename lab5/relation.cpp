/*
 * relation.cpp
 *
 *  Created on: Mar 1, 2015
 *      Author: benjamin
 */

#include "relation.h"
#include "token.h"
#include "parameter.h"

void relation::setScheme(scheme s)
{
	myScheme = s;
}

void relation::addTuple(Tuple t)
{
	tupleList.insert(t);
}

void relation::addTuples(relation tups)
{
	for(set<Tuple>::iterator it = tups.tupleList.begin(); it != tups.tupleList.end(); ++it)
	{
		addTuple(*it);
	}
}

string relation::toString()
{
	string output;
	output = myScheme.toString() + "\n";
	for(set<Tuple>::iterator it = tupleList.begin(); it != tupleList.end(); ++it)
	{
		output += (*it).toString() + "\n";
	}
	output += "\n";

	return output;
}

relation relation::select(int pos, string val)
{
	relation temp;
	temp.setScheme(myScheme);
	for(set<Tuple>::iterator it = tupleList.begin(); it != tupleList.end(); ++it)
	{

		if((*it)[pos] == val)
		{

			temp.addTuple(*it);
		}
	}
	return temp;
}

relation relation::select(int pos1, int pos2)
{
	relation temp;
	temp.setScheme(myScheme);
	for(set<Tuple>::iterator it = tupleList.begin(); it != tupleList.end(); ++it)
	{
		if((*it)[pos1] == (*it)[pos2])
		{
			temp.addTuple(*it);
		}
	}
	return temp;
}

relation relation::project(vector<int> pos)
{
	relation newRel;
	newRel.setScheme(myScheme);
	if(!pos.empty())
	{
		for(set<Tuple>::iterator it = tupleList.begin(); it != tupleList.end(); ++it)
		{
			Tuple temp;
			for(int i = 0; i < pos.size(); i++)
			{
				temp.push_back((*it)[pos[i]]);
			}
			newRel.addTuple(temp);

		}
	}

	return newRel;
}

int relation::getSize()
{
	return tupleList.size();
}

/*string relation::printResult()
{
	string output;
	for(set<tuple>::iterator it = tupleList.begin(); it != tupleList.end(); ++it)
	{
		output += "  ";
		for(int i = 0; i < myScheme.parameterList.size(); i++)
		{
			if(myScheme.parameterList[i] == ID)
			{

			}
		}
	}
}*/
