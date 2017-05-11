/*
 * database.h
 *
 *  Created on: Mar 1, 2015
 *      Author: benjamin
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include <map>
#include "relation.h"

using namespace std;

class database
{
public:
	database(){}
	~database(){}
	map<string, relation> relations;

	string toString()
	{
		string output;
		for(std::map<string,relation>::iterator it = relations.begin(); it != relations.end(); ++it)
		{
			output += it->second.toString() + "\n";
		}
		return output;
	}

private:

};



#endif /* DATABASE_H_ */
