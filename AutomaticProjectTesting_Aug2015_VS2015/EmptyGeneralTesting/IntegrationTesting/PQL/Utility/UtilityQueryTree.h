#pragma once
#include <string>
#include <vector>
#include "..\..\..\SPA\PQL\QueryTreeStub.h"

using namespace std;

class UtilityQueryTree
{
public:
    UtilityQueryTree();
    ~UtilityQueryTree();

    static bool isGetAllAssignsSame(QueryTreeStub qt1, QueryTreeStub qt2);
};

