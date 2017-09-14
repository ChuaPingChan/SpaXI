#pragma once
#include <string>
#include <array>

using namespace std;

class QueryEvaluator
{
public:
	QueryEvaluator();
	~QueryEvaluator();

private:
	void evaluateFollows(array<string, 4> arr);
	void evaluateFollowsT(array<string, 4> arr);
	void evaluateParent(array<string, 4> arr);
	void evaluateParentT(array<string, 4> arr);
	void evaluateUses(array<string, 4> arr);
	void evaluateModifies(array<string, 4> arr);
	void evaluatePattern(array<string, 6> arr);
};

