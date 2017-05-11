/*
 * token.cpp
 *
 *  Created on: Jan 26, 2015
 *      Author: benjamin
 */

#include "token.h"
#include <sstream>
string token::print()
{
	string output;
	output = "(" + mapOfToks[type] + ",\"" + value + "\"," + lineToString() + ")";
	return output;
}

string token::lineToString()
{
	stringstream convert;
	convert << line;
	string lineNum = convert.str();
	return lineNum;
}
