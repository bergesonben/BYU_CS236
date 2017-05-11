/*
 * tuple.h
 *
 *  Created on: Mar 1, 2015
 *      Author: benjamin
 */

#ifndef TUPLE_H_
#define TUPLE_H_

#include <string>
#include "scheme.h"

using namespace std;


class Tuple : public vector<string>
{
public:
	Tuple(scheme s)
	{
		push_back(s.name);
		for(int i = 0; i < s.parameterList.size(); i++)
		{
			push_back(s.parameterList[i]);
		}
	}
	Tuple(){}
	~Tuple(){}

	string toString() const
	{
		string output;
		for(vector<string>::const_iterator it = this->begin(); it != this->end(); ++it)
		{
			output +=  *it + "  ";
		}
		return output;
	}


};




#endif /* TUPLE_H_ */
