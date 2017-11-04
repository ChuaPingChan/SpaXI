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
#include "../Utilities/SuchThatClause.h"

using namespace std;

class QueryEvaluator
{
public:
    QueryEvaluator(QueryTree* qtPtr);
    ~QueryEvaluator();

    void evaluate();
    bool hasResult();

private:
    QueryTree* _qt;
    bool hasResultEvaluator;
};

