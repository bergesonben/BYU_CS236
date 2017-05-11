/*
 * relation.h
 *
 *  Created on: Mar 1, 2015
 *      Author: benjamin
 */

#ifndef RELATION_H_
#define RELATION_H_

#include "Tuple.h"
//#include "scheme.h"
#include <iostream>
#include <set>

using namespace std;

class relation
{
public:
	relation(){}
	~relation(){}

//methods
	void setScheme(scheme s);
	void addTuple(Tuple t);
	string toString();
	relation select(int pos, string val);
	relation select(int pos1, int pos2);
	relation project(vector<int> pos);
	string printResult();

//variables
	set<Tuple> tupleList;
	scheme myScheme;
};



#endif /* RELATION_H_ */
