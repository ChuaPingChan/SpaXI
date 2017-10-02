#pragma once
#include <unordered_set>
#include <string>
#include <iostream>
#include <array>
#include <list>
#include <unordered_set>
#include "Utilities\SuchThatClause.h"
#include "Utilities\PatternClause.h"
#include "Utilities\SelectClause.h"
#include "..\Entity.h"

using namespace std;

class QueryTree
{
public:
    QueryTree();
    ~QueryTree();

    void insertVariable(int type, string var);
        void insertSelect(SelectClause select);
    void insertSuchThat(SuchThatClause relClause);
    void insertPattern(PatternClause patternClause);
    void storeEvaluatorResult(list<string> list);
    
    unordered_set<string> getStmts();
    unordered_set<string> getAssigns();
    unordered_set<string> getWhiles();
    unordered_set<string> getVars();
    unordered_set<string> getConsts();
    unordered_set<string> getProgLines();

    SelectClause getSelect();
    vector<SuchThatClause> getSuchThatClauses();
    vector<PatternClause> getPatternClauses();
    list<string> getEvaluatorResult();

    bool isEntitySynonymExist(string synonym, Entity entityIdx);

private:

    unordered_set<string> stmts;
    unordered_set<string> assigns;
    unordered_set<string> whiles;
    unordered_set<string> vars;
    unordered_set<string> consts;
    unordered_set<string> progLines;

    SelectClause selectStmt;
    vector<SuchThatClause> suchThatClauses;
    vector<PatternClause> patternClauses;

    list<string> evaluatorResult;
};

