/*
 * main.cpp
 *
 *  Created on: Jan 26, 2015
 *      Author: benjamin
 */


#include <iostream>

#include "scanner.h"


using namespace std;

int main(int argc, char* argv[])
{
	scanner myScanner;
	myScanner.scan(argv[1]);

	return 0;
}

