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

	string toString();
	int getSize();


private:

};



#endif /* DATABASE_H_ */
