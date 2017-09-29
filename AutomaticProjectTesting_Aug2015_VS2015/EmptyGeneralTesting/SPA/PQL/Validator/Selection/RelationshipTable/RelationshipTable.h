#pragma once
#include"Relationship.h"
#include<unordered_map>

const int STMT = 0;
const int ASSIGN = 1;
const int WHILE = 2;
const int IF = 3;
const int PROG_LINE = 4;
const int CALL = 5;
const int PROCEDURE = 6;
const int VARIABLE = 7;
const int INTEGER = 8;
const int UNDERSCORE = 9;
const int IDENT_WITHCOMMAS = 10;
const int EXPRESSION_SPEC = 11;
const int CONSTANT = 12;
const int STMTLIST = 13;

typedef int RELATION;
typedef int ARGTYPE;

class RelationshipTable
{
public:
    RelationshipTable();
    ~RelationshipTable();
    bool isArgValid(RELATION inputRel, ARGTYPE one, ARGTYPE two);
    bool isArgValid(RELATION inputRel, ARGTYPE one, ARGTYPE two, ARGTYPE three);
    Relationship rModify, rUses, rParent, rParentStar, rFollows, rFollowsStar, rCalls, rCallsStar, rNext, rNextStar, rAffects, rAffectsStar, rPattern;

private:
    unordered_map<RELATION, Relationship> relTable;

    /****** Helper methods for Validity of Argument Type *******/
    bool isArg1Valid(Relationship rel, ARGTYPE arg1);
    bool isArg2Valid(Relationship rel, ARGTYPE arg);
    bool isArg3Valid(Relationship rel, ARGTYPE arg);
};

