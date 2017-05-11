/*
 * interpreter.cpp
 *
 *  Created on: Mar 1, 2015
 *      Author: benjamin
 */
#include "interpreter.h"
#include <iostream>
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

//formatting according to queries
	for(int i = 0; i < queryList.size(); i++)
	{
		relation selects = db.relations[queryList[i].name];
		relation projects;
		vector<int> projectsPos;
		vector<string> renameVals;


	//select(s)
		//selects based on strings
		for(int j = 0; j < queryList[i].parameterList.size(); j++)
		{
			parameter temp = queryList[i].parameterList[j];
			if(temp.type == STRING)
				selects = selects.select(j+1, temp.value);
		}
		//selects based on IDs
		for(int j = 0; j < queryList[i].parameterList.size(); j++)
		{
			for(int k = j+1; k < queryList[i].parameterList.size(); k++)
			{
				if(queryList[i].parameterList[j].value == queryList[i].parameterList[k].value)
				{
					selects = selects.select(j,k);
					break;
				}

			}
		}

	//Project(s)
		//creating vector of positions to project
		for(int k = 0; k < queryList[i].parameterList.size(); k++)
		{
			parameter temp = queryList[i].parameterList[k];
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
		projects = selects.project(projectsPos);


	//Renaming
		/*for(int j = 0; j < queryList[i].parameterList.size(); j++)
		{
			projects.myScheme.editParameter(j, queryList[i].parameterList[j].value);
		}*/
		scheme tempScheme(queryList[i].name);
		tempScheme.addParameter(renameVals);
		projects.setScheme(tempScheme);

	//print out results
		cout << queryList[i].toString() << "? ";
		if((selects.tupleList).empty())
		{
			cout << "No\n";
		}
		else if((projects.tupleList).empty())
		{
			cout << "Yes(1)\n";
		}
		else
		{

			cout << "Yes(" << projects.tupleList.size() << ")\n";
			for(set<Tuple>::iterator it = projects.tupleList.begin(); it != projects.tupleList.end(); ++it)
			{
				cout << "  ";
				int count = 0;
				for(int x = 0; x < projects.myScheme.parameterList.size(); x++)
				{

					if(count != 0)
						cout << ", ";
					cout  << projects.myScheme.parameterList[x] << "="
							<< (*it)[count];
					count++;

				}
				cout << endl;
			}
		}
		/*cout << "selects:\n" << selects.toString();
		if(!renameVals.empty())
			cout << "projects:\n" << projects.toString();*/

	}





}



