#include "RelationshipTable.h"

 ARGUMENT_TYPE_RULES rule1 = { STMT, ASSIGN,WHILE,IF,PROG_LINE,CALL,PROCEDURE,IDENT_WITHQUOTES,INTEGER};
 ARGUMENT_TYPE_RULES rule2 = { VARIABLE, IDENT_WITHQUOTES, UNDERSCORE};
 ARGUMENT_TYPE_RULES rule3 = { STMT, WHILE,IF,PROG_LINE,INTEGER, UNDERSCORE};
 ARGUMENT_TYPE_RULES rule4 = { STMT, ASSIGN,WHILE,IF,PROG_LINE,CALL,INTEGER, UNDERSCORE };
 ARGUMENT_TYPE_RULES rule5 = { PROCEDURE, IDENT_WITHQUOTES, UNDERSCORE };
 ARGUMENT_TYPE_RULES rule6 = { ASSIGN, STMT, PROG_LINE, INTEGER, UNDERSCORE };
 ARGUMENT_TYPE_RULES rule7 = { STMT, ASSIGN,WHILE,IF,PROG_LINE,CALL,PROCEDURE,IDENT_WITHQUOTES,INTEGER };
 ARGUMENT_TYPE_RULES rule_arg1_for_pattern = { ASSIGN, WHILE };
 ARGUMENT_TYPE_RULES rule_arg2_for_pattern = { VARIABLE, IDENT_WITHQUOTES, UNDERSCORE };
 ARGUMENT_TYPE_RULES rule_arg3_for_pattern = { EXPRESSION_SPEC_PARTIAL,UNDERSCORE };

 /*****************
 * Public methods *
 *****************/

RelationshipTable::RelationshipTable()
{
    ARGUMENT_TYPE_RULES arg1, arg2;
    ARGUMENT_TYPE_RULES arg3; //Extra argument for PATTERN
    
    //Modifies & Uses
    arg1 = rule1;
    arg2 = rule2;
    rModify = Relationship(arg1, arg2);
    rUses = Relationship(arg1, arg2);
    relTable[MODIFIES] = rModify;
    relTable[USES] = rUses;
    arg1.clear();
    arg2.clear();

    //Parent & Parent*
    arg1 = rule3;
    arg2 = rule4;
    rParent = Relationship(arg1, arg2);
    rParentStar = Relationship(arg1, arg2);
    relTable[PARENT] = rParent;
    relTable[PARENTSTAR] = rParentStar;
    arg1.clear();
    arg2.clear();

    //Follows & Follows*
    arg1 = rule4;
    arg2 = rule4;
    rFollows = Relationship(arg1, arg2);
    rFollowsStar = Relationship(arg1, arg2);
    relTable[FOLLOWS] = rFollows;
    relTable[FOLLOWSSTAR] = rFollowsStar;
    arg1.clear();
    arg2.clear();
/*
    //Calls and Calls*
    arg1 = rule5;
    arg2 = rule5;
     rCalls=Relationship(arg1, arg2);
     rCallsStar=Relationship(arg1, arg2);
    relTable[CALLS] = rCalls;
    relTable[CALLSSTAR] = rCallsStar;

    //Next and Next*
    arg1 = rule4;
    arg2 = rule4;
     rNext=Relationship(arg1, arg2);
     rNextStar=Relationship(arg1, arg2);
    relTable[NEXT] = rNext;
    relTable[NEXTSTAR] = rNextStar;

    //Affects and Affects*
    arg1 = rule6;
    arg2 = rule6;
     rAffects=Relationship(arg1, arg2);
     rAffectsStar=Relationship(arg1, arg2);
    relTable[AFFECTS] = rCalls;
    relTable[AFFECTSSTAR] = rCallsStar;
*/
    //Pattern
    arg1 = rule_arg1_for_pattern;
    arg2 = rule_arg2_for_pattern;
    arg3 = rule_arg3_for_pattern;
    rPattern =  Relationship(arg1, arg2, arg3);
    relTable[PATTERN] = rPattern;
    arg1.clear();
    arg2.clear();
    arg3.clear();
    
}


RelationshipTable::~RelationshipTable()
{
}

/*
bool RelationshipTable::hasRelationship(RELATION inputRel)
{
   auto iterator = relTable.find(inputRel);
   if(iterator==relTable.end())
     return false;
   
   return true;
} */

bool RelationshipTable::isArgValid(RELATION_TYPE inputRel, ARG_TYPE one, ARG_TYPE two)
{
    assert(inputRel <= 12);
    Relationship rel = relTable.find(inputRel)->second;
    return isArg1Valid(rel, one) && isArg2Valid(rel, two);
}

bool RelationshipTable::isArgValid(RELATION_TYPE inputRel, ARG_TYPE one, ARG_TYPE two, ARG_TYPE three)
{
    Relationship rel = relTable.find(inputRel)->second;
    return isArg1Valid(rel, one) && isArg2Valid(rel, two) && isArg3Valid(rel, three);
}


/*****************
* Private helper methods *
*****************/
bool RelationshipTable::isArg1Valid(Relationship rel, ARG_TYPE arg) 
{
    ARGUMENT_TYPE_RULES arg1 = rel.getArg1Type();
    for (ARGUMENT_TYPE_RULES::iterator it = arg1.begin(); it != arg1.end(); ++it)
    {
        if (*it == arg)
            return true;
    }
    return false;
}

bool RelationshipTable::isArg2Valid(Relationship rel, ARG_TYPE arg)
{
    ARGUMENT_TYPE_RULES arg2 = rel.getArg2Type();
    for (ARGUMENT_TYPE_RULES::iterator it = arg2.begin(); it != arg2.end(); ++it)
    {
        if (*it == arg)
            return true;
    }
    return false;
}

bool RelationshipTable::isArg3Valid(Relationship rel, ARG_TYPE arg)
{
    ARGUMENT_TYPE_RULES arg3 = rel.getArg3Type();
    for (ARGUMENT_TYPE_RULES::iterator it = arg3.begin(); it != arg3.end(); ++it)
    {
        if (*it == arg)
            return true;
    }
    return false;
}
