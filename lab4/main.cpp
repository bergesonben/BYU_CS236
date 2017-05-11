/*
 * main.cpp
 *
 *  Created on: Mar 1, 2015
 *      Author: benjamin
 */

#include "interpreter.h"

int main(int argc, char* argv[])
{
	interpreter myInt;
	myInt.start(argv[1]);

	return 0;
}



