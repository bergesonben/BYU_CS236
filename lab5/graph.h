/*
 * graph.h
 *
 *  Created on: Apr 5, 2015
 *      Author: benjamin
 */

#ifndef GRAPH_H_
#define GRAPH_H_
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include "node.h"

using namespace std;

class graph
{
public:
	graph(){}
	~graph(){}
	map<int,node> nodes;

	string toString();
	string intToString(int n);
	vector<node> getPostOrder();
	vector<node> dfs(node& x);
};



#endif /* GRAPH_H_ */
