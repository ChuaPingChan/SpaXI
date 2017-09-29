#pragma once
#include<vector>
#include<string>

using namespace std;
static const int MODIFIES = 0;
static const int USES = 1;
static const int PARENT = 2;
static const int PARENTSTAR = 3;
static const int FOLLOWS = 4;
static const int FOLLOWSSTAR = 5;
static const int CALLS = 6;
static const int CALLSSTAR = 7;
static const int NEXT = 8;
static const int NEXTSTAR = 9;
static const int AFFECTS = 10;
static const int AFFECTSSTAR = 11;
static const int PATTERN = 12;

typedef vector<int> ARGUMENT_TYPE;

class Relationship
{
public:
    Relationship();
    Relationship(ARGUMENT_TYPE arg1Type, ARGUMENT_TYPE arg2Type);
    Relationship(ARGUMENT_TYPE arg1Type, ARGUMENT_TYPE arg2Type, ARGUMENT_TYPE arg3Type);
    ARGUMENT_TYPE getArg1Type();
    ARGUMENT_TYPE getArg2Type();
    ARGUMENT_TYPE getArg3Type();
    ~Relationship();

private:
    ARGUMENT_TYPE arg1Type,arg2Type,arg3Type;
};

