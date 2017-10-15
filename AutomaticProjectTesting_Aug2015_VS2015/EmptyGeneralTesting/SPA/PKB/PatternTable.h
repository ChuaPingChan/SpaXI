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
	bool addWhile(int stmt, int varIdx);
	bool addIf(int stmt, int varIdx);
    bool addToPatternTable(int stmtNumber, int varIdx, string expression);
    pair<int,list<string>> getExpression(int stmtNumber);
    pair<list<int>,list<int>> getLeftVariables();
    pair<list<int>,list<int>> getLeftVariableThatPartialMatchWithString(string expression);
	pair<list<int>, list<int>> getLeftVariableThatExactMatchWithString(string expression);
    list<int> getExactMatchStmt(string expression);
    list<int> getPartialMatchStmt(string expression);
	list<int> getPartialMatchVar(int stmt, string expression);
	list<int> getExactMatchVar(int stmt, string expression);
    list<int> getExactBothMatches(int var, string expression);
	bool isExactMatch(int stmt, int var, string expression);
	bool isPartialMatch(int stmt, int var, string expression);
	list<int> getPartialBothMatches(int var, string expression);
    list<int> getLeftVariableMatchingStmts(int var);
	list<int> getIfWithControlVariable(int varIdx);
	list<int> getWhileWithControlVariable(int varIdx);

    //////////////////////////////////////
    bool hasExactMatch(int stmtNumber, string expression);
    bool hasPartialMatch(int stmtNumber, string expression);
private:
    unordered_map<int, pair<int,list<string>>> patternTableMap;
    stack<char> infixToPostfixStack;
	unordered_map<int, list<int>> varToWhileMap;
	unordered_map<int, list<int>> varToIfMap;
};