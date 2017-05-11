/*
 * interpreter.h
 *
 *  Created on: Mar 1, 2015
 *      Author: benjamin
 */

#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "parser.h"
#include "database.h"
#include "graph.h"
#include "node.h"

using namespace std;

class interpreter
{
public:
	interpreter(){}
	~interpreter(){}

//functions
	void start(string inputFile);

//variables
	vector<scheme> schemesList;
	vector<scheme> factsList;
	vector<string> domain;
	vector<rule> rulesList;
	vector<predicate> queryList;
private:
	parser myParser;
	database db;
	graph myGraph;
	graph revGraph;
	vector<vector<node> > sccs;
	void processRule(rule r);
	relation selects(predicate query);
	relation projectQuery(predicate query, relation rel);
	relation projectJoin(predicate query, relation rel);
	void rename(string name, vector<string> param, relation &renameRel);
	relation join(relation a, relation b);
	bool joinable(Tuple a, Tuple b, vector<string> aParam, vector<string> bParam);
	void evalRule();
	graph makeGraph();
	graph makeRevGraph();
};




#endif /* INTERPRETER_H_ */
