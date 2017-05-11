/*
 * interpreter.cpp
 *
 *  Created on: Mar 1, 2015
 *      Author: benjamin
 */
#include "interpreter.h"
#include <iostream>
#include <algorithm>
#include "token.h"

void interpreter::start(string inputFile)
{
	myParser.parse(inputFile);
	schemesList = myParser.schemesList;
	factsList = myParser.factsList;
	domain = myParser.domain;
	rulesList = myParser.rulesList;
	queryList = myParser.queryList;


	//creating relations
	for(int i = 0; i < schemesList.size(); i++)
	{
		relation newRelation;
		newRelation.setScheme(schemesList[i]);
		db.relations.insert(pair<string, relation>(schemesList[i].name,newRelation));
	}

	//Adding tuples to relations
	for(int i = 0; i < factsList.size(); i++)
	{
		Tuple newTuple(factsList[i]);
		db.relations[factsList[i].name].addTuple(newTuple);

	}

	evalRule();


//Process Rules
	//processRules();

	//for testing prints out database after processing rules
		//cout << db.toString();

//Process Queries
	cout << "Query Evaluation\n";
//formatting according to queries
	for(int i = 0; i < queryList.size(); i++)
	{
		relation afterSelects;
		relation afterProjects;



	//Selects
		afterSelects = selects(queryList[i]);

	//Project(s) & Rename
		afterProjects = projectQuery(queryList[i], afterSelects);




	//print out results
		cout << queryList[i].toString() << "? ";
		if((afterSelects.tupleList).empty())
		{
			cout << "No\n";
		}
		else if((afterProjects.tupleList).empty())
		{
			cout << "Yes(1)\n";
		}
		else
		{

			cout << "Yes(" << afterProjects.tupleList.size() << ")\n";
			for(set<Tuple>::iterator it = afterProjects.tupleList.begin(); it != afterProjects.tupleList.end(); ++it)
			{
				cout << "  ";
				int count = 0;
				for(int x = 0; x < afterProjects.myScheme.parameterList.size(); x++)
				{

					if(count != 0)
						cout << ", ";
					cout  << afterProjects.myScheme.parameterList[x] << "="
							<< (*it)[count];
					count++;

				}
				cout << endl;
			}
		}




	}





}

void interpreter::processRule(rule r)
{
	predicate headPred = r.headPredicate;
	vector<predicate> predList = r.predList;
	relation afterPreds;

	afterPreds = selects(predList[0]);
	afterPreds = projectQuery(predList[0], afterPreds);

	for(int i = 1; i < predList.size(); i++)
	{
		afterPreds = join(afterPreds, projectQuery(predList[i], selects(predList[i])));
	}

	afterPreds = projectJoin(headPred, afterPreds);

	db.relations[headPred.name].addTuples(afterPreds);
}

relation interpreter::selects(predicate query)
{
	relation newRelation = db.relations[query.name];


	//selects based on strings
	for(int j = 0; j < query.parameterList.size(); j++)
	{
		parameter temp = query.parameterList[j];

		if(temp.type == STRING)
		{

			newRelation = newRelation.select(j, temp.value);
		}
	}

	//selects based on IDs
	for(int j = 0; j < query.parameterList.size(); j++)
	{
		for(int k = j+1; k < query.parameterList.size(); k++)
		{
			if(query.parameterList[j].value == query.parameterList[k].value)
			{
				newRelation = newRelation.select(j,k);
				break;
			}

		}
	}

	return newRelation;
}

relation interpreter::projectQuery(predicate query, relation rel)
{
	vector<int> projectsPos;
	vector<string> renameVals;
	relation newRelation;

	//creating vector of positions to project
	for(int k = 0; k < query.parameterList.size(); k++)
	{
		parameter temp = query.parameterList[k];
		if(temp.type == ID)
		{
			bool exists = false;
			for(int x = 0; x < projectsPos.size(); x++)
			{
				if(temp.value == renameVals[x])
					exists = true;
			}
			if(!exists)
			{
				projectsPos.push_back(k);
				renameVals.push_back(temp.value);
			}

		}
	}

	//Perform projections
	newRelation = rel.project(projectsPos);

	rename(query.name, renameVals, newRelation);


	return newRelation;
}

relation interpreter::projectJoin(predicate query, relation rel)
{
	vector<int> projectsPos;
	vector<string> renameVals;
	relation newRelation;

	//creating vector of positions to project
	for(int k = 0; k < query.parameterList.size(); k++)
	{
		parameter temp = query.parameterList[k];
		if(temp.type == ID)
		{
			bool exists = false;
			for(int x = 0; x < projectsPos.size(); x++)
			{
				if(temp.value == renameVals[x])
					exists = true;
			}
			if(!exists)
			{
				for(int l = 0; l < rel.myScheme.parameterList.size(); l++)
				{
					if(temp.value == rel.myScheme.parameterList[l])
					{

						projectsPos.push_back(l);
						renameVals.push_back(temp.value);
						break;
					}
				}

			}

		}
	}


	//Perform projections
	newRelation = rel.project(projectsPos);

	rename(query.name, renameVals, newRelation);


	return newRelation;
}

void interpreter::rename(string name, vector<string> param, relation &renameRel)
{
	scheme tempScheme(name);
	tempScheme.addParameter(param);
	renameRel.setScheme(tempScheme);
}

relation interpreter::join(relation a, relation b)
{
	relation product;
	predicate joinProj;
	scheme productScheme = a.myScheme;

	productScheme.addParameter(b.myScheme.parameterList);
	product.setScheme(productScheme);

	for(set<Tuple>::iterator it = a.tupleList.begin(); it != a.tupleList.end(); ++it)
	{
		for(set<Tuple>::iterator jt = b.tupleList.begin(); jt != b.tupleList.end(); ++jt)
		{
			if(joinable((*it),(*jt),a.myScheme.parameterList, b.myScheme.parameterList))
			{
				Tuple newTuple = (*it);
				newTuple.insert(newTuple.end(), (*jt).begin(), (*jt).end());
				product.addTuple(newTuple);

			}
		}
	}

	vector<string>::iterator it = unique(productScheme.parameterList.begin(), productScheme.parameterList.end());
	productScheme.parameterList.resize(distance(productScheme.parameterList.begin(),it));
	joinProj = productScheme.toPred();


	product = projectJoin(joinProj, product);

	return product;
}

bool interpreter::joinable(Tuple a, Tuple b, vector<string> aParam, vector<string> bParam)
{
	for(int i = 0; i < a.size(); i++)
	{
		for(int j=0; j < b.size(); j++)
		{
			if(aParam[i] == bParam[j] && a[i] != b[j])
				return false;
		}
	}

	return true;
}

void interpreter::evalRule()
{
	myGraph = makeGraph();
	revGraph = makeRevGraph();

	cout << "Dependency Graph\n";
	cout << myGraph.toString() << endl;

	vector<node> postOrder = revGraph.getPostOrder();

	while(!postOrder.empty())
	{
		int i = postOrder.size() - 1;
		if(!myGraph.nodes[postOrder[i].name].visited)
		{
			vector<node> temp = myGraph.dfs(myGraph.nodes[postOrder[i].name]);
			sort(temp.begin(), temp.end());
			temp.erase(unique(temp.begin(),temp.end()), temp.end());
			sccs.push_back(temp);
		}
		postOrder.pop_back();
	}

	cout << "Rule Evaluation\n";

	for(int i = 0;  i < sccs.size(); i++)
	{
		int numPasses = 0;
		if(sccs[i].size() == 1 && !sccs[i][0].isCyclic())
		{
			processRule(rulesList[sccs[i][0].name]);
			cout << "1 passes: R" << sccs[i][0].name << endl;
		}
		else
		{
			int sizeBefore = 0;
			int sizeAfter = 0;

			do
			{
				sizeBefore = db.getSize();
				for(int j = 0; j < sccs[i].size(); j++)
				{
					processRule(rulesList[sccs[i][j].name]);
				}

				sizeAfter = db.getSize();

				numPasses++;
			}while(sizeBefore != sizeAfter);

			cout << numPasses << " passes: R" << sccs[i][0].name;
			for(int j = 1; j < sccs[i].size(); j++)
			{
				cout << ",R" << sccs[i][j].name;
			}
			cout << endl;
		}


	}
	cout << endl;

}

graph interpreter::makeGraph()
{
	graph thisGraph;

	for(int i =0; i < rulesList.size(); i++)
	{
		rule thisRule = rulesList[i];
		node thisNode;
		thisNode.name = i;
		for(int j = 0; j < thisRule.predList.size(); j++)
		{
			predicate thisPred = thisRule.predList[j];
			for(int k = 0; k < rulesList.size(); k++)
			{
				if(thisPred.name == rulesList[k].headPredicate.name)
				{
					thisNode.adjacentNodes.push_back(k);
				}
			}
		}
		sort(thisNode.adjacentNodes.begin(), thisNode.adjacentNodes.end());
		thisNode.adjacentNodes.erase(unique(thisNode.adjacentNodes.begin(), thisNode.adjacentNodes.end()), thisNode.adjacentNodes.end());
		thisGraph.nodes.insert(pair<int, node>(i, thisNode));
	}

	return thisGraph;
}

graph interpreter::makeRevGraph()
{
	graph thisGraph;

	for(int i = 0; i < rulesList.size(); i++)
	{
		rule thisRule = rulesList[i];
		node thisNode;
		thisNode.name = i;
		for(int j = 0; j < rulesList.size(); j++)
		{
			for(int k = 0; k < rulesList[j].predList.size(); k++)
			{
				if(rulesList[j].predList[k].name == thisRule.headPredicate.name)
				{
					thisNode.adjacentNodes.push_back(j);
				}
			}
		}
		sort(thisNode.adjacentNodes.begin(), thisNode.adjacentNodes.end());
		thisNode.adjacentNodes.erase(unique(thisNode.adjacentNodes.begin(), thisNode.adjacentNodes.end()), thisNode.adjacentNodes.end());
		thisGraph.nodes.insert(pair<int,node>(i,thisNode));
	}

	return thisGraph;


}


