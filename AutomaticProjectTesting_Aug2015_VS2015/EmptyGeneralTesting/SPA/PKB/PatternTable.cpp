#include "PatternTable.h"

string infixToPostfix(string infix);
bool isOperator(char c);
int getPrecedence(char sign);

PatternTable::PatternTable() {
    
}

bool PatternTable::addToPatternTable(int stmtNumber, string expression) {
    // to convert infix to postfix expression
    string postfixExpression = infixToPostfix(expression);
    // if stmt number does not exist as a key, insert data to hash map
    if (patternTableMap.find(stmtNumber) == patternTableMap.end()) {
        patternTableMap[stmtNumber] = postfixExpression;
        return true;
    }
    return false;
}

string PatternTable::getExpression(int stmtNumber) {
    return patternTableMap[stmtNumber];
}

bool PatternTable::hasExactMatch(int stmtNumber, string expression) {
    // returns true if postfix of expression exactly matches with patternTableMap[stmtNumber]
    return patternTableMap[stmtNumber].compare(infixToPostfix(expression)) == 0;
}

bool PatternTable::hasPartialMatch(int stmtNumber, string expression) {
    size_t found = patternTableMap[stmtNumber].find(infixToPostfix(expression));
    // returns true if postfix of expression is the substring of patternTableMap[stmtNumber]
    return found != string::npos;
}

string infixToPostfix(string infix) {
    stack<char> signStack = stack<char>();
    string postfix = "";
    for (int i = 0; i < infix.length(); i++) {
        if (isalpha(infix[i]) || isdigit(infix[i])) {
            postfix += infix[i];
        }
        else if (isOperator(infix[i])) {
            while (!signStack.empty()
                && signStack.top() != '('
                && getPrecedence(infix[i]) <= getPrecedence(signStack.top())) {
                postfix += signStack.top();
                signStack.pop();
            }
            signStack.push(infix[i]);
        }
        else if (infix[i] == '(') {
            signStack.push(infix[i]);
        }
        else if (infix[i] == ')') {
            while (!signStack.empty() && signStack.top() != '(') {
                postfix += signStack.top();
                signStack.pop();
            }
            signStack.pop();
        }
    }
    while (!signStack.empty()) {
        if (signStack.top() != '(' || signStack.top() != ')') {
            postfix += signStack.top();
        }
        signStack.pop();
    }
    return postfix;
}

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int getPrecedence(char sign) {
    int weight;
    if (sign == '+' || sign == '-')
        weight = 1;
    else if (sign == '*' || sign == '/')
        weight = 2;
    return weight;
}