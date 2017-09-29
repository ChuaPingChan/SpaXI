#pragma once
#include<vector>
#include<string>

using namespace std;
const int MODIFIES = 0;
const int USES = 1;
const int PARENT = 2;
const int PARENTSTAR = 3;
const int FOLLOWS = 4;
const int FOLLOWSSTAR = 5;
const int CALLS = 6;
const int CALLSSTAR = 7;
const int NEXT = 8;
const int NEXTSTAR = 9;
const int AFFECTS = 10;
const int AFFECTSSTAR = 11;
const int PATTERN = 12;

typedef vector<int> ARGUMENT;

class Relationship
{
public:
    Relationship();
    Relationship(ARGUMENT arg1Type, ARGUMENT arg2Type);
    Relationship(ARGUMENT arg1Type, ARGUMENT arg2Type, ARGUMENT arg3Type);
    ARGUMENT getArg1Type();
    ARGUMENT getArg2Type();
    ARGUMENT getArg3Type();
    ~Relationship();

private:
    ARGUMENT arg1Type,arg2Type,arg3Type;
};

