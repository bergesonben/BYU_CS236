/*
 * main.cpp
 *
 *  Created on: Feb 7, 2015
 *      Author: benjamin
 */
#include "parser.h"

int main(int argc, char* argv[])
{
	parser myParser(argv[1]);
	myParser.parse();

	return 0;
}



