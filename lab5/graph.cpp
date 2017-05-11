/*
 * graph.cpp
 *
 *  Created on: Apr 9, 2015
 *      Author: benbball
 */


#include "graph.h"



string graph::toString()
	{
		string output;
		for(std::map<int,node>::iterator it = nodes.begin(); it != nodes.end(); ++it)
		{
			output += it->second.toString() + "\n";
		}

		return output;
	}

string graph::intToString(int n)
{
	stringstream convert;
	convert << n;
	string out = convert.str();
	return out;
}

vector<node> graph::getPostOrder()
{
	vector<node> myStack;
	for(map<int,node>::iterator it = nodes.begin(); it != nodes.end(); ++it)
	{
		if(!it->second.visited)
		{
			vector<node> temp = dfs(it->second);
			myStack.insert(myStack.end(), temp.begin(), temp.end());
		}
	}
	return myStack;
}

vector<node> graph::dfs(node& x)
{
	vector<node> myStack;

	x.visited = true;
	for(int i = 0; i < x.adjacentNodes.size(); i++)
	{
		if(!nodes[x.adjacentNodes[i]].visited)
		{
			vector<node> temp = dfs(nodes[x.adjacentNodes[i]]);
			myStack.insert(myStack.end(), temp.begin(), temp.end());
		}
	}
	myStack.push_back(x);
	return myStack;
}
