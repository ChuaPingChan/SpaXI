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
#include "Utilities\ClauseResult.h"

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
    void storeEvaluatorResult(ClauseResult result);
    
    unordered_set<string> getStmts();
    unordered_set<string> getAssigns();
    unordered_set<string> getWhiles();
    unordered_set<string> getVars();
    unordered_set<string> getConsts();
    unordered_set<string> getProgLines();

    SelectClause getSelect();
    vector<SuchThatClause> getSuchThatClauses();
    vector<PatternClause> getPatternClauses();
    ClauseResult getEvaluatorResult();

    bool isEntitySynonymExist(string synonym, Entity entityIdx);

private:

    unordered_set<string> _stmts;
    unordered_set<string> _assigns;
    unordered_set<string> _whiles;
    unordered_set<string> _vars;
    unordered_set<string> _consts;
    unordered_set<string> _progLines;

    SelectClause _selectStmt;
    vector<SuchThatClause> _suchThatClauses;
    vector<PatternClause> _patternClauses;

    ClauseResult _evaluatorResult;
};

