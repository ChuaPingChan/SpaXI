#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>
#include <stack>

using namespace std;

class PatternTable {
public:
    PatternTable();
    bool addToPatternTable(int stmtNumber, string expression);
    string getExpression(int stmtNumber);
    bool hasExactMatch(int stmtNumber, string expression);
    bool hasPartialMatch(int stmtNumber, string expression);
private:
    unordered_map<int, string> patternTableMap;
    stack<char> infixToPostfixStack;
};