/*
 * parser.cpp
 *
 *  Created on: Feb 7, 2015
 *      Author: benjamin
 */
#include "parser.h"
#include "rule.h"
#include "parameter.h"
#include <algorithm>
#include <iostream>

void parser::parse()
{
	match(SCHEMES);
	match(COLON);
	parseScheme();
	parseSchemeList();

	match(FACTS);
	match(COLON);
	parseFactList();
	program.makeDomain();

	match(RULES);
	match(COLON);
	parseRuleList();

	match(QUERIES);
	match(COLON);
	parseQuery();
	parseQueryList();

	cout << "Success!\n" << program.toString();
}

void parser::match(tokType t)
{
	if(tok.type == t)
	{
		tok = tokenList[0];
		tokenList.erase(tokenList.begin());
	}

	else
		error();
}

void parser::error()
{
	cout << "Failure!\n  "
		<< tok.print() << endl;
	exit(EXIT_SUCCESS);
}

void parser::toString()
{

}

void parser::parseScheme()
{
	//ID LEFT_PAREN ID idList RIGHT_PAREN
	scheme newScheme(tok.value);
	match(ID);
	match(LEFT_PAREN);
	newScheme.addParameter(tok.value);
	match(ID);
	newScheme.addParameter(idList());
	match(RIGHT_PAREN);


	program.addScheme(newScheme);

}

void parser::parseSchemeList()
{
	if(tok.type != FACTS)
	{
		parseScheme();
		parseSchemeList();
	}
}

void parser::parseFact()
{
	scheme newFact(tok.value);
	match(ID);
	match(LEFT_PAREN);
	newFact.addParameter(tok.value);
	match(STRING);
	newFact.addParameter(stringList());
	match(RIGHT_PAREN);
	match(PERIOD);

	program.addFact(newFact);
	//domain.insert(domain.end(),newFact.parameterList.begin(), newFact.parameterList.end());

}

void parser::parseFactList()
{
	if(tok.type != RULES)
	{
		parseFact();
		parseFactList();
	}


}

void parser::parseRuleList()
{
	if(tok.type != QUERIES)
	{
		parseRule();
		parseRuleList();
	}
}

void parser::parseRule()
{
	rule newRule;
	newRule.addHead(headPredicate());
	match(COLON_DASH);
	newRule.addPred(parsePredicate());
	newRule.addPred(parsePredicateList());
	match(PERIOD);

	program.addRule(newRule);

}

predicate parser::headPredicate()
{
	predicate newHead(tok.value);
	parameter initial;
	vector<parameter> pList;
	vector<string> temp;
	match(ID);
	match(LEFT_PAREN);
	initial.value = tok.value;
	newHead.addParameter(initial);
	match(ID);
	temp = idList();
	for(int i = 0; i < temp.size(); i++)
	{
		parameter a;
		a.value = temp[i];
		pList.push_back(a);
	}
	newHead.addParameter(pList);
	match(RIGHT_PAREN);

	return newHead;
}

predicate parser::parsePredicate()
{
	predicate newPred(tok.value);
	match(ID);
	match(LEFT_PAREN);
	newPred.addParameter(parseParameter());
	newPred.addParameter(parseParameterList());
	match(RIGHT_PAREN);

	return newPred;
}

vector<predicate> parser::parsePredicateList()
{
	vector<predicate> newPredList;
	if(tok.type != PERIOD && tok.type != QUERIES)
	{
		match(COMMA);
		newPredList.push_back(parsePredicate());
		vector<predicate> temp = parsePredicateList();
		newPredList.insert(newPredList.end(), temp.begin(), temp.end());
	}

	return newPredList;
}

parameter parser::parseParameter()
{
	parameter newParam;
	if(tok.type == STRING)
	{
		newParam.value = tok.value;
		match(STRING);
	}
	else if(tok.type == ID)
	{
		newParam.value = tok.value;
		match(ID);
	}
	else
	{

		newParam.value = parseExpression();
	}
	return newParam;
}

vector<parameter> parser::parseParameterList()
{
	vector<parameter> newParamList;
	if(tok.type != RIGHT_PAREN)
	{
		match(COMMA);
		newParamList.push_back(parseParameter());
		vector<parameter> temp = parseParameterList();
		newParamList.insert(newParamList.end(), temp.begin(), temp.end());
	}

	return newParamList;
}

string parser::parseExpression()
{
	string exp = "(";
	match(LEFT_PAREN);
	exp += parseParameter().value + " ";
	exp += parseOperator() + " ";
	exp += parseParameter().value;
	match(RIGHT_PAREN);
	exp += ")";

	return exp;
}

string parser::parseOperator()
{
	if(tok.type == ADD)
	{
		match(ADD);
		return "+";
	}
	else if(tok.type == MULTIPLY)
	{
		match(MULTIPLY);
		return "*";
	}
	else
		error();
}

void parser::parseQuery()
{
	program.addQuery(parsePredicate());
	match(Q_MARK);
}

void parser::parseQueryList()
{
	if(tok.type != END)
	{
		parseQuery();
		parseQueryList();
	}

}

vector<string> parser::idList()
{
	vector<string> myList;		//list of parameters to return

	//COMMA ID idList | lambda
	if(tok.type != RIGHT_PAREN)
	{
		match(COMMA);
		myList.push_back(tok.value);
		match(ID);
		vector<string> temp = idList();
		myList.insert(myList.end(), temp.begin(), temp.end());	//adds whatever returns from recursion
	}

	return myList;

}

vector<string> parser::stringList()
{
	vector<string> myList;		//list of parameters to return

	if(tok.type != RIGHT_PAREN)
	{
		match(COMMA);
		myList.push_back(tok.value);
		match(STRING);
		vector<string> temp = stringList();
		myList.insert(myList.end(), temp.begin(), temp.end());	//adds whatever returns from recursion
	}

	return myList;
}
