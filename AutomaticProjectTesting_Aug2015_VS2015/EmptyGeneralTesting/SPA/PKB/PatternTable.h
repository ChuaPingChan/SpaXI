#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>
#include <stack>
#include <ctype.h>
#include <utility>
#include <algorithm>

using namespace std;

class PatternTable {
public:
    PatternTable();
    bool addToPatternTable(int stmtNumber, string var, string expression);
    pair<string,list<string>> getExpression(int stmtNumber);
    
    pair<list<int>,list<string>> getLeftVariables();
    pair<list<int>,list<string>> getLeftVariableThatMatchWithString(string expression);
    list<int> getExactMatchStmt(string expression);
    list<int> getPartialMatchStmt(string expression);
    list<int> getExactBothMatches(string var, string expression);
    list<int> getPartialBothMatches(string var, string expression);
    list<int> getLeftVariableMatchingStmts(string var);

    //////////////////////////////////////
    bool hasExactMatch(int stmtNumber, string expression);
    bool hasPartialMatch(int stmtNumber, string expression);
private:
    unordered_map<int, pair<string,list<string>>> patternTableMap;
    stack<char> infixToPostfixStack;
};