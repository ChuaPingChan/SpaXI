#pragma once
#include <list>
#include <array>
#include <string>
#include <iostream>


using namespace std;

class QueryEvaluator
{
public:
	QueryEvaluator();
	~QueryEvaluator();

	void evaluate();

private:
	bool hasResult = true;

	list<string> resultSelect;
	list<pair<string, string>> resultSuchThat;
	list<pair<string, string>> resultPattern;

	void evaluateFollows(array<string, 4> arr);
	void evaluateFollowsT(array<string, 4> arr);
	void evaluateParent(array<string, 4> arr);
	void evaluateParentT(array<string, 4> arr);
	void evaluateUses(array<string, 4> arr);
	void evaluateModifies(array<string, 4> arr);
	void evaluatePattern(array<string, 6> arr);


};

