#pragma once
#include"Relationship.h"
#include<unordered_map>
#include<assert.h>

static const int STMT = 0;
static const int ASSIGN = 1;
static const int WHILE = 2;
static const int IF = 3;
static const int PROG_LINE = 4;
static const int CALL = 5;
static const int PROCEDURE = 6;
static const int VARIABLE = 7;
static const int INTEGER = 8;
static const int UNDERSCORE = 9;
static const int IDENT_WITHQUOTES = 10;
static const int EXPRESSION_SPEC = 11;
static const int CONSTANT = 12;
static const int STMTLIST = 13;

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

