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

    static bool isGetAllStmtsSame(QueryTree qt1, QueryTree qt2);
    static bool isGetAllAssignsSame(QueryTree qt1, QueryTree qt2);
    static bool isGetAllVariablesSame(QueryTree qt1, QueryTree qt2);
    static bool isGetAllWhilesSame(QueryTree qt1, QueryTree qt2);
};
