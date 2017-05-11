/*
 * scanner.cpp
 *
 *  Created on: Jan 26, 2015
 *      Author: benjamin
 */

#include "scanner.h"
#include <fstream>
#include <cctype>
#include <iostream>

void scanner::scan(string fileName)
{
	inputFile.open(fileName.c_str());

	if(inputFile)		//check to make sure it opens
	{
		while(inputFile.get(curr))
		{
			scanToken();
		}
		makeToken(END, line);

		outputFile.open("output.txt");
		for(int i = 0; i < myVector.size(); i++)
		{
			outputFile << myVector[i].print() << endl;

		}
		outputFile << "Total Tokens = " << myVector.size();
		outputFile.close();
	}
	else
		cout << "File did not load"<< endl;


}

void scanner::scanToken()
{
	while(isspace(curr))
	{
		if(curr == '\n')
			line++;
		inputFile.get(curr);
		if(inputFile.eof())
			break;
	}
	switch (curr)
	{
	case ',':
		value = ",";
		makeToken(COMMA, line);
		break;
	case '.':
		value = ".";
		makeToken(PERIOD, line);
		break;
	case '?':
		value = "?";
		makeToken(Q_MARK, line);
		break;
	case '(':
		value = "(";
		makeToken(LEFT_PAREN, line);
		break;
	case ')':
		value = ")";
		makeToken(RIGHT_PAREN, line);
		break;
	case '*':
		value = "*";
		makeToken(MULTIPLY, line);
		break;
	case '+':
		value = "+";
		makeToken(ADD, line);
		break;
	case ':':
		value = ":";
		next = inputFile.peek();
		if(next == '-')
		{
			value = ":-";
			makeToken(COLON_DASH, line);
			inputFile.get(curr);
		}
		else
			makeToken(COLON, line);
		break;
	case '\'':
		scanStr();
		break;
	case '#':
		scanComm();
		break;
	default:
		if(isalpha(curr))
			scanID();
		else if(!inputFile.eof())
		{
			value += curr;
			makeToken(UNDEFINED, line);
		}
		break;
	}
}

void scanner::scanID()
{
	value += curr;
	inputFile.get(curr);
	while(isalnum(curr))
	{
		value += curr;
		inputFile.get(curr);
	}
	valueToUpper();
	if(valueUpper == "SCHEMES")
		makeToken(SCHEMES, line);
	else if(valueUpper == "FACTS")
		makeToken(FACTS, line);
	else if(valueUpper == "RULES")
		makeToken(RULES, line);
	else if(valueUpper == "QUERIES")
		makeToken(QUERIES, line);
	else
		makeToken(ID, line);
	scanToken();
}

void scanner::scanStr()
{
	bool endOfString = false;
	value += curr;
	lineStart = line;
	while(endOfString == false)
	{
		if(inputFile.peek() == -1)
		{
			makeToken(UNDEFINED, lineStart);
			endOfString = true;
		}
		else
		{
			inputFile.get(curr);
			switch(curr)
			{
			case '\n':
				line++;
				value += curr;
				break;
			case '\'':
				value += curr;
				next = inputFile.peek();
				if(next != '\'')
				{
					makeToken(STRING, lineStart);
					endOfString = true;
				}
				else
				{
					inputFile.get(curr);
					value += curr;
				}
				break;
			default:
				value += curr;
				break;
			}
		}
	}
}

void scanner::scanComm()
{
	value += curr;
	lineStart = line;
	next = inputFile.peek();
	if(next != '|')
	{
		inputFile.get(curr);
		while(curr != '\n')
		{
			value += curr;
			inputFile.get(curr);
		}
		if(curr == '\n')
			line++;
		makeToken(COMMENT, lineStart);

	}
	else
	{
		inputFile.get(curr);
		value += curr;
		inputFile.get(curr);
		next = inputFile.peek();
		while((curr != '|' || next != '#') && !inputFile.eof())
		{
			if(curr == '\n')
				line++;
			value += curr;
			inputFile.get(curr);
			next = inputFile.peek();
		}
		if(curr == '|' && next == '#')
		{
			value += curr;
			inputFile.get(curr);
			value += curr;
			makeToken(COMMENT, lineStart);
		}
		else if(inputFile.eof())
			makeToken(UNDEFINED, lineStart);
	}
}

void scanner::makeToken(tokType type, int lineNum)
{
	token newToken(type, value, lineNum);
	if(type != COMMENT)
	{
		myVector.push_back(newToken);
	}
	//cout << newToken.print() << endl;
	value = "";
	valueUpper = "";


}

void scanner::valueToUpper()
{
	for(int i = 0; i < value.length(); i++)
	{
		valueUpper += toupper(value[i]);
	}
}

vector<token> scanner::getVector()
{
	return myVector;
}

