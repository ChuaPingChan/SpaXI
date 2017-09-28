#pragma once
#include<vector>
#include<string>

using namespace std;

const string FOLLOWS = "Follows";
const string FOLLOWSSTAR = "Follows*";
const string PARENT = "Parent";
const string PARENTSTAR = "Parent*";
const string USES = "Uses";
const string MODIFIES = "Modifies";
const string PATTERN = "pattern";

typedef vector<string> ARGUMENT;

class Relationship
{
public:
    Relationship();
    Relationship(ARGUMENT argType1, ARGUMENT argType2);
    Relationship(ARGUMENT argType1, ARGUMENT argType2, ARGUMENT argType3);
    ~Relationship();

private:
    ARGUMENT argType1,argType2,argType3;
};

