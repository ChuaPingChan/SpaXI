#pragma once
#include <string>
#include <vector>
#include "..\..\..\SPA\PQL\QueryTree.h"

using namespace std;

class UtilityQueryTree
{
public:
    UtilityQueryTree();
    ~UtilityQueryTree();

    static bool isSameContentAllStmts(unordered_set<string> expectedList, QueryTree qt);
    static bool isSameContentAllAssigns(unordered_set<string> expectedList, QueryTree qt);
    static bool isSameContentAllWhiles(unordered_set<string> expectedList, QueryTree qt);
    static bool isSameContentAllIfs(unordered_set<string> expectedList, QueryTree qt);
    static bool isSameContentAllProgLines(unordered_set<string> expectedList, QueryTree qt);
    static bool isSameContentAllCalls(unordered_set<string> expectedList, QueryTree qt);
    static bool isSameContentAllProcedures(unordered_set<string> expectedList, QueryTree qt);
    static bool isSameContentAllVariables(unordered_set<string> expectedList, QueryTree qt);
    
};
