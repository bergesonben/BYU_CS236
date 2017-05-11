/*
 * node.h
 *
 *  Created on: Apr 5, 2015
 *      Author: benjamin
 */

#ifndef NODE_H_
#define NODE_H_

using namespace std;

class node
{
public:
	node(){}
	~node(){}

	int name;
	vector<int> adjacentNodes;
	bool visited = false;
	int postOrderNum = -1;

	string toString()
	{
		string output;
		output += "R" + intToString(name) + ":";
		for(int i = 0; i < adjacentNodes.size(); i++)
		{
			if(i > 0)
				output += ",";
			output += "R" + intToString(adjacentNodes[i]);
		}
		return output;
	}

	string intToString(int n)
	{
		stringstream convert;
		convert << n;
		string out = convert.str();
		return out;
	}

	bool isCyclic()
	{
		for(int i = 0; i < adjacentNodes.size(); i++)
		{
			if(adjacentNodes[i] == name)
				return true;
		}
		return false;
	}

	bool operator<(const node& x) const
	{
		if(name < x.name)
			return true;
		else
			return false;
	}

	bool operator==(const node& x)
	{
		if(name == x.name)
			return true;
		else
			return false;
	}
};




#endif /* NODE_H_ */
