#pragma once
#include "../Utilities/SelectClause.h"
#include "../Utilities/ClauseResult.h"
#include "../../PKB/PKBMain.h"
#include <stdio.h>

class SelectionEvaluator
{
public:
	SelectionEvaluator();
	~SelectionEvaluator();

	bool evaluate(SelectClause clause); //To-Do: Integration Testing with ClauseResult

protected:
	list<int> evaluateSingleSynonymSelection(Entity argType, string synonym); //To-Do: Integration Testing with PKB
	PKBMain* pkbInstance;

private:
	list<int> singleSynonymSelectionResult;
	list<list<int>> tupleSelectionResults; //To-Do: Implement for Iteration 3
	bool hasResultForSelection;

};

