#pragma once
#include <unordered_set>
#include <string>
#include <iostream>
#include <array>
#include <list>
#include <unordered_set>
#include "..\Entity.h"
#include "Utilities\SuchThatClause.h"
#include "Utilities\PatternClause.h"
#include "Utilities\WithClause.h"
#include "Utilities\SelectClause.h"
#include "Utilities\ClauseResult.h"

using namespace std;

class QueryTree
{
public:
    QueryTree();
    ~QueryTree();

    void insertSynonym(Entity type, string synonym);
    void insertSelect(SelectClause select);
    void insertSuchThat(SuchThatClause relClause);
    void insertPattern(PatternClause patternClause);
    void insertWith(WithClause withClause);
    void storeEvaluatorResult(ClauseResult result);
    
    unordered_set<string> getStmts();
    unordered_set<string> getAssigns();
    unordered_set<string> getWhiles();
    unordered_set<string> getIfs();
    unordered_set<string> getCalls();
    unordered_set<string> getProcedures();
    unordered_set<string> getVars();
    unordered_set<string> getConsts();
    unordered_set<string> getProgLines();

    SelectClause getSelectClause();
    vector<SuchThatClause> getSuchThatClauses();
    vector<PatternClause> getPatternClauses();
    vector<WithClause> getWithClauses();
    ClauseResult getEvaluatorResult();

    bool isEntitySynonymExist(string synonym, Entity entityIdx);

private:

    unordered_set<string> _stmts;
    unordered_set<string> _assigns;
    unordered_set<string> _whiles;
    unordered_set<string> _ifs;
    unordered_set<string> _calls;
    unordered_set<string> _procedures;
    unordered_set<string> _vars;
    unordered_set<string> _consts;
    unordered_set<string> _progLines;

    SelectClause _selectClause;
    vector<SuchThatClause> _suchThatClauses;
    vector<PatternClause> _patternClauses;
    vector<WithClause> _withClauses;

    ClauseResult _evaluatorResult;
};

