/*
 * parser.h
 *
 *  Created on: Feb 7, 2015
 *      Author: benjamin
 */

#ifndef PARSER_H_
#define PARSER_H_
#include "scanner.h"
#include "scheme.h"
#include "datalogProgram.h"

class parser
{
public:
	parser(){}
	~parser(){}

//functions
	void parse(string inputFile);
	token getToken();
	void match(tokType t);
	void error();
	void toString();
	void parseScheme();
	void parseSchemeList();
	void parseFactList();
	void parseFact();
	void parseRuleList();
	void parseRule();
	predicate headPredicate();
	predicate parsePredicate();
	vector<predicate> parsePredicateList();
	parameter parseParameter();
	vector<parameter> parseParameterList();
	string parseExpression();
	string parseOperator();
	void parseQuery();
	void parseQueryList();
	vector<string> idList();
	vector<string> stringList();

//variables
	token tok;
	vector<scheme> schemesList;
	vector<scheme> factsList;
	vector<string> domain;
	vector<rule> rulesList;
	vector<predicate> queryList;

private:
	vector<token> tokenList;
	datalogProgram program;
	scanner lexer;

};






#endif /* PARSER_H_ */
