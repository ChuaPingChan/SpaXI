#pragma once
#include"Relationship.h"
#include<unordered_map>
#include<assert.h>
#include "..\..\..\..\Entity.h"

typedef int RELATION_TYPE;
typedef int ARG_TYPE;

class RelationshipTable
{
public:
    RelationshipTable();
    ~RelationshipTable();
    bool isArgValid(RELATION_TYPE inputRel, ARG_TYPE one, ARG_TYPE two);
    bool isArgValid(RELATION_TYPE inputRel, ARG_TYPE one, ARG_TYPE two, ARG_TYPE three);
    Relationship rModify, rUses, rParent, rParentStar, rFollows, rFollowsStar, rCalls, rCallsStar, rNext, rNextStar, rAffects, rAffectsStar, rPattern;

private:
    unordered_map<RELATION_TYPE, Relationship> relTable;

    /****** Helper methods for Validity of Argument Type *******/
    bool isArg1Valid(Relationship rel, ARG_TYPE arg1);
    bool isArg2Valid(Relationship rel, ARG_TYPE arg);
    bool isArg3Valid(Relationship rel, ARG_TYPE arg);
};

