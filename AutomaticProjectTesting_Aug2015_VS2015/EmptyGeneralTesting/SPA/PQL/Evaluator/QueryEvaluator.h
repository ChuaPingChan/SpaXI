#pragma once
#include <list>
#include <array>
#include <regex>
#include <string>
#include <iostream>
#include <algorithm>
#include "../QueryTree.h"
#include "../../PKB/PKBMain.h"
#include "ResultFactory.h"

using namespace std;

class QueryEvaluator
{
public:
	QueryEvaluator(QueryTree* qtPtr);
	~QueryEvaluator();

	void evaluate();

 //   /*--------------- Unit Testing ---------------*/
 //   bool getHasResult();
 //   pair<list<string>, list<string>> getResultSuchThat();
 //   list<string> getIntersectionTest(list<string> list1, list<string> list2);
 //   void evaluateSelectTest(array<string, 2> arr);
 //   void evaluateFollowsTest(array<string, 4> arr);
 //   void evaluateFollowsStarTest(array<string, 4> arr);
 //   void evaluateParentTest(array<string, 4> arr);
 //   void evaluateParentStarTest(array<string, 4> arr);
 //   void evaluateUsesTest(array<string, 4> arr);
 //   void evaluateModifiesTest(array<string, 4> arr);
 //   void evaluatePatternTest(array<string, 6> arr);

private:

	QueryTree* _qt;
	ResultFactory _rsFactory;
	//PKBMain PKB;//TODO: Set this to static

 //   bool hasResult = true;
 //   list<string> finalResult;
 //   list<string> resultSelect;
	//pair<list<string>, list<string>> resultSuchThat;
 //   pair<list<string>, list<string>> resultPattern;

 //   /*--------------- Evaluator clauses ---------------*/
 //   void evaluateSelect(array<string, 2> arr);
	//void evaluateFollows(array<string, 4> arr);
	//void evaluateFollowsStar(array<string, 4> arr);
	//void evaluateParent(array<string, 4> arr);
	//void evaluateParentStar(array<string, 4> arr);
	//void evaluateUses(array<string, 4> arr);
	//void evaluateModifies(array<string, 4> arr);
	//void evaluatePattern(array<string, 6> arr);


 //   /*--------------- Evaluator helper methods ---------------*/

 //   /*--------------- Get result from common synonym ---------------*/
 //   list<string> getCommonSynonymResult(list<string> select, pair<list<string>, list<string>> suchThat, pair<list<string>, list<string>> pattern);

 //   /*--------------- Find set intersection between two lists---------------*/
 //   list<string> getIntersection(list<string> list1, list<string> list2);

 //   /*--------------- Convert list of integers to list of strings ---------------*/
 //   list<string> getListStringFromListInt(list<int> listOfInt);
};

