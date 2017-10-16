#include "PatternTable.h"

list<string> infixToPostfix(string infix);
bool isOperator(string c);
int getPrecedence(string sign);

PatternTable::PatternTable() {
    
}

bool PatternTable::addWhile(int stmt, int varIdx) {
	if (varToWhileMap.find(varIdx) == varToWhileMap.end()) {
		varToWhileMap[varIdx].push_back(stmt);
	}
	else {
		varToWhileMap[varIdx].push_back(stmt);
		varToWhileMap[varIdx].sort();
		varToWhileMap[varIdx].unique();
	}
	whileToVarMap[stmt] = varIdx;
	whileVarList.push_back(varIdx);
	whileList.push_back(stmt);
	return true;
}

bool PatternTable::isWhileControlVar(int stmt, int varIdx) {
	if (varToWhileMap.find(varIdx) == varToWhileMap.end()) {
		return false;
	}

	return find(varToWhileMap[varIdx].begin(), varToWhileMap[varIdx].end(), stmt) != varToWhileMap[varIdx].end();
}

bool PatternTable::addIf(int stmt, int varIdx) {
	if (varToIfMap.find(varIdx) == varToIfMap.end()) {
		varToIfMap[varIdx].push_back(stmt);
	}
	else {
		varToIfMap[varIdx].push_back(stmt);
		varToIfMap[varIdx].sort();
		varToIfMap[varIdx].unique();
	}
	ifToVarMap[stmt] = varIdx;
	ifVarList.push_back(varIdx);
	ifList.push_back(stmt);
	return true;
}

bool PatternTable::isIfControlVar(int stmt, int varIdx) {
	if (varToIfMap.find(varIdx) == varToIfMap.end()) {
		return false;
	}

	return find(varToIfMap[varIdx].begin(), varToWhileMap[varIdx].end(), stmt) != varToWhileMap[varIdx].end();
}

pair<list<int>, list<int>> PatternTable::getControlVariablesInWhile() {
	return make_pair(whileList, whileVarList);
}

list<int> PatternTable::getControlVariablesInWhile(int stmt) {
	list<int> resultList;
	if (whileToVarMap.find(stmt) == whileToVarMap.end()) {
		return resultList;
	}

	resultList.push_back(whileToVarMap[stmt]);
	return resultList;
}

list<int> PatternTable::getWhileFromControlVar(int var) {
	if (varToWhileMap.find(var) == varToWhileMap.end()) {
		return list<int>();
	}

	return varToWhileMap[var];
}

list<int> PatternTable::getIfFromControlVar(int var) {
	if (varToIfMap.find(var) == varToIfMap.end()) {
		return list<int>();
	}

	return varToIfMap[var];
}

list<int> PatternTable::getControlVariablesInIf(int stmt) {
	list<int> resultList;
	if (ifToVarMap.find(stmt) == ifToVarMap.end()) {
		return resultList;
	}

	resultList.push_back(ifToVarMap[stmt]);
	return resultList;
}

pair<list<int>, list<int>> PatternTable::getControlVariablesInIf() {
	return make_pair(ifList, ifVarList);
}

list<int> PatternTable::getWhileWithControlVariable(int varIdx) {
	list<int> stmtList;
	if (varToWhileMap.find(varIdx) == varToWhileMap.end()) {
		return stmtList;
	}

	return varToWhileMap[varIdx];
}

list<int> PatternTable::getIfWithControlVariable(int varIdx) {
	if (varToIfMap.find(varIdx) == varToIfMap.end()) {
		return list<int>();
	}

	return varToIfMap[varIdx];
}

/*
    Pre-condition: expression must be a valid expression taking operands
    (0-9, a-z, A-Z) and operators(+,-,*,/) between operands
*/
bool PatternTable::addToPatternTable(int stmtNumber, int var, string expression) {
    // to convert infix to postfix expression
    list<string> postfixExpression = infixToPostfix(expression);
    // if stmt number does not exist as a key, insert data to hash map
    if (patternTableMap.find(stmtNumber) == patternTableMap.end()) {
        patternTableMap[stmtNumber] = make_pair(var, postfixExpression);
        return true;
    }
    return false;
}

pair<int, list<string>> PatternTable::getExpression(int stmtNumber) {
	//TODO 1 Check if this adds bug
	if (patternTableMap.find(stmtNumber) == patternTableMap.end()) {
		return make_pair(0, list<string>());
	}

    return patternTableMap[stmtNumber];
}

pair<list<int>,list<int>> PatternTable::getLeftVariables()
{
    pair<list<int>, list<int>> pairOfList;
    unordered_map<int, pair<int, list<string>>>::iterator it;
    for (it = patternTableMap.begin(); it != patternTableMap.end(); ++it)
    {
        //varList.push_back(make_pair(it->first,it->second.first));
        pairOfList.first.push_back(it->first);
        pairOfList.second.push_back(it->second.first);
    }
    return pairOfList;
}

pair<list<int>,list<int>> PatternTable::getLeftVariableThatPartialMatchWithString(string expression)
{
    pair<list<int>, list<int>> pairOfList;
    unordered_map<int, pair<int, list<string>>>::iterator it;
    for (it = patternTableMap.begin(); it != patternTableMap.end(); ++it)
    {
        if (hasPartialMatch(it->first, expression))
        {
            pairOfList.first.push_back(it->first);
            pairOfList.second.push_back(it->second.first);
        }
    }
    return pairOfList;
}

pair<list<int>, list<int>> PatternTable::getLeftVariableThatExactMatchWithString(string expression)
{
	pair<list<int>, list<int>> pairOfList;
	unordered_map<int, pair<int, list<string>>>::iterator it;
	for (it = patternTableMap.begin(); it != patternTableMap.end(); ++it)
	{
		if (hasExactMatch(it->first, expression))
		{
			pairOfList.first.push_back(it->first);
			pairOfList.second.push_back(it->second.first);
		}
	}
	return pairOfList;
}

list<int> PatternTable::getExactMatchStmt(string expression)
{
    list<int> assignList;
    unordered_map<int, pair<int, list<string>>>::iterator it;
    for (it = patternTableMap.begin(); it != patternTableMap.end(); ++it)
    {
        int stmt = it->first;
        if (hasExactMatch(stmt, expression)) {
            assignList.push_back(stmt);
        }
    }
    return assignList;
}

list<int> PatternTable::getPartialMatchStmt(string expression)
{
    list<int> assignList;
    unordered_map<int, pair<int, list<string>>>::iterator it;
    for (it = patternTableMap.begin(); it != patternTableMap.end(); ++it)
    {
        int stmt = it->first;
        if (hasPartialMatch(stmt, expression)) {
            assignList.push_back(stmt);
        }
    }
    return assignList;
}

list<int> PatternTable::getPartialMatchVar(int stmt, string expression) {
	list<int> varList;
	unordered_map<int, pair<int, list<string>>>::iterator it;
	for (it = patternTableMap.begin(); it != patternTableMap.end(); ++it) {
		if (it->first == stmt && hasPartialMatch(stmt, expression)) {
			varList.push_back(it->second.first);
		}
	}
	return varList;
}

list<int> PatternTable::getExactMatchVar(int stmt, string expression) {
	list<int> varList;
	unordered_map<int, pair<int, list<string>>>::iterator it;
	for (it = patternTableMap.begin(); it != patternTableMap.end(); ++it) {
		if (it->first == stmt && hasExactMatch(stmt, expression)) {
			varList.push_back(it->second.first);
		}
	}
	return varList;
}

list<int> PatternTable::getExactBothMatches(int var, string expression)
{
    list<int> assignList;
    unordered_map<int, pair<int, list<string>>>::iterator it;
    for (it = patternTableMap.begin(); it != patternTableMap.end(); ++it)
    {
        int stmt = it->first;
        int storedVar = it->second.first;
        //string storedExpression = it->second.second;
        if (storedVar == var && hasExactMatch(stmt, expression))
        {
            assignList.push_back(stmt);
        }
    }

    return assignList;
}

bool PatternTable::isExactMatch(int stmt, int var, string expression) {
	if (patternTableMap.find(stmt) == patternTableMap.end()) {
		return false;
	}

	return (patternTableMap[stmt].first == var && hasExactMatch(stmt, expression));
}

bool PatternTable::isPartialMatch(int stmt, int var, string expression) {
	if (patternTableMap.find(stmt) == patternTableMap.end()) {
		return false;
	}

	return (patternTableMap[stmt].first == var && hasPartialMatch(stmt, expression));
}

list<int> PatternTable::getPartialBothMatches(int var, string expression)
{
    list<int> assignList;
    unordered_map<int, pair<int, list<string>>>::iterator it;
    for (it = patternTableMap.begin(); it != patternTableMap.end(); ++it)
    {
        int stmt = it->first;
        int storedVar = it->second.first;
        //string storedExpression = it->second.second;
        if (storedVar == var && hasPartialMatch(stmt, expression))
        {
            assignList.push_back(stmt);
        }
    }

    return assignList;
}

list<int> PatternTable::getLeftVariableMatchingStmts(int var)
{
    list<int> stmtList;
    unordered_map<int, pair<int, list<string>>>::iterator it;
    for (it = patternTableMap.begin(); it != patternTableMap.end(); ++it)
    {
        if (var == it->second.first)
        {
            stmtList.push_back(it->first);
        }
    }
    return stmtList;
}



//////////////////////////////////////////////////////////
bool PatternTable::hasExactMatch(int stmtNumber, string expression) {
    // returns true if postfix of expression exactly matches with patternTableMap[stmtNumber]
	if (patternTableMap.find(stmtNumber) == patternTableMap.end()) {
		return false;
	}
    return patternTableMap[stmtNumber].second == infixToPostfix(expression);
}

bool PatternTable::hasPartialMatch(int stmtNumber, string expression) {
    // returns true if postfix of expression is the sublist of patternTableMap[stmtNumber]
    list<string> exp = patternTableMap[stmtNumber].second;
    list<string> subexp = infixToPostfix(expression);
    list<string>::iterator listitr = std::search(
        exp.begin(), exp.end(),
        subexp.begin(), subexp.end()
    );
    return listitr != exp.end();
}

/*
    Pre-cond: infix is a valid expression
*/
list<string> infixToPostfix(string infix) {
    stack<string> signStack = stack<string>();
    list<string> postfix = list<string>();
    string var = "";
    for (int i = 0; i < infix.length(); i++) {
        string current = "";
        current += infix[i];
        if (isalpha(infix[i]) || isdigit(infix[i])) {
            var += infix[i];
        }
        else {
            if (!var.empty()) {
                postfix.push_back(var);
                var = "";
            }
            if (isOperator(current)) {
                while (!signStack.empty()
                    && signStack.top().compare("(") != 0
                    && getPrecedence(current) <= getPrecedence(signStack.top())) {
                    postfix.push_back(signStack.top());
                    signStack.pop();
                }
                signStack.push(current);
            }
            else if (infix[i] == '(') {
                signStack.push(current);
            }
            else if (infix[i] == ')') {
                while (!signStack.empty() && signStack.top().compare("(") != 0) {
                    postfix.push_back(signStack.top());
                    signStack.pop();
                }
                signStack.pop();
            }
        }
    }
    postfix.push_back(var);
    while (!signStack.empty()) {
        if (signStack.top().compare("(") != 0 || signStack.top().compare(")") != 0) {
            postfix.push_back(signStack.top());
        }
        signStack.pop();
    }
    return postfix;
}

bool isOperator(string c) {
    return (c.compare("+") == 0 ||
        c.compare("-") == 0 ||
        c.compare("*") == 0 ||
        c.compare("/") == 0);
}

/*
    Pre-cond: sign takes only operators(+, -, *, /)
*/
int getPrecedence(string sign) {
    int weight;
    if (sign.compare("+") == 0 || sign.compare("-") == 0)
        weight = 1;
    else if (sign.compare("*") == 0 || sign.compare("/") == 0)
        weight = 2;
    return weight;
}