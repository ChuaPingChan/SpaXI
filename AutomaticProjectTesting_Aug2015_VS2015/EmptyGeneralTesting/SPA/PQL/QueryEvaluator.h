#pragma once
#include <list>
#include <array>
#include <string>
#include <iostream>
#include "QueryTree.h"

using namespace std;

class QueryEvaluator
{
public:
	QueryEvaluator();
	~QueryEvaluator();

	void evaluate();

private:

	QueryTree* qtInstance;

    bool hasResult = true;
    list<string> finalResult;
    list<string> resultSelect;
	pair<list<string>, list<string>> resultSuchThat;
    pair<list<string>, list<string>> resultPattern;

    /*--------------- Evaluator clauses ---------------*/
    void evaluateSelect(array<string, 2> arr);
	void evaluateFollows(array<string, 4> arr);
	void evaluateFollowsT(array<string, 4> arr);
	void evaluateParent(array<string, 4> arr);
	void evaluateParentT(array<string, 4> arr);
	void evaluateUses(array<string, 4> arr);
	void evaluateModifies(array<string, 4> arr);
	void evaluatePattern(array<string, 6> arr);

    /*--------------- Evaluator helper methods ---------------*/
    /*--------------- Find set intersection between two lists---------------*/
    list<string> getIntersection(list<string> list1, list<string> list2);
};

