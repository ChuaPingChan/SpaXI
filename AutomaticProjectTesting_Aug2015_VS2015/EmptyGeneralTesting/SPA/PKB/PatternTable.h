#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>
#include <stack>
#include <utility>

using namespace std;

class PatternTable {
public:
    PatternTable();
    bool addToPatternTable(int stmtNumber, string var, string expression);
    pair<string,string> getExpression(int stmtNumber);
    
    list<pair<int,string>> getLeftVariables();
    list<pair<int,string>> getLeftVariableThatMatchWithString(string expression);
    list<int> getExactMatchStmt(string expression);
    list<int> getPartialMatchStmt(string expression);

    //////////////////////////////////////
    bool hasExactMatch(int stmtNumber, string expression);
    bool hasPartialMatch(int stmtNumber, string expression);
private:
    unordered_map<int, pair<string,string>> patternTableMap;
    stack<char> infixToPostfixStack;
};