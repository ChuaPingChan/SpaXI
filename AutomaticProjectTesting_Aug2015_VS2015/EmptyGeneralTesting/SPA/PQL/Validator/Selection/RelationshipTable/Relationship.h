#pragma once
#include<vector>
#include<string>

using namespace std;
typedef vector<int> ARGUMENT_TYPE_RULES;
typedef const int RELATION;
RELATION MODIFIES = 0;
RELATION USES = 1;
RELATION PARENT = 2;
RELATION PARENTSTAR = 3;
RELATION FOLLOWS = 4;
RELATION FOLLOWSSTAR = 5;
RELATION CALLS = 6;
RELATION CALLSSTAR = 7;
RELATION NEXT = 8;
RELATION NEXTSTAR = 9;
RELATION AFFECTS = 10;
RELATION AFFECTSSTAR = 11;
RELATION PATTERN = 12;

class Relationship
{
public:
    Relationship();
    Relationship(ARGUMENT_TYPE_RULES arg1Type, ARGUMENT_TYPE_RULES arg2Type);
    Relationship(ARGUMENT_TYPE_RULES arg1Type, ARGUMENT_TYPE_RULES arg2Type, ARGUMENT_TYPE_RULES arg3Type);
    ARGUMENT_TYPE_RULES getArg1Type();
    ARGUMENT_TYPE_RULES getArg2Type();
    ARGUMENT_TYPE_RULES getArg3Type();
    ~Relationship();

private:
    ARGUMENT_TYPE_RULES arg1Type,arg2Type,arg3Type;
};

