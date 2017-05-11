/*
 * database.cpp
 *
 *  Created on: Mar 18, 2015
 *      Author: benjamin
 */

#include "database.h"


string database::toString()
	{
		string output;
		output = "DATABASE\n=========\n";
		for(std::map<string,relation>::iterator it = relations.begin(); it != relations.end(); ++it)
		{
			output += it->second.toString() + "\n";
		}
		return output;
	}

int database::getSize()
{
	int size = 0;

	for(map<string, relation>::iterator it = relations.begin(); it != relations.end(); ++it)
	{
		size += it->second.getSize();
	}

	return size;
}
