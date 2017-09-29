#include "RelationshipTable.h"

 ARGUMENT rule1 = { STMT, ASSIGN,WHILE,IF,PROG_LINE,CALL,PROCEDURE,IDENT_WITHCOMMAS,INTEGER};
 ARGUMENT rule2 = { VARIABLE, IDENT_WITHCOMMAS, UNDERSCORE};
 ARGUMENT rule3 = { STMT, WHILE,IF,PROG_LINE,INTEGER, UNDERSCORE};
 ARGUMENT rule4 = { STMT, ASSIGN,WHILE,IF,PROG_LINE,CALL,INTEGER, UNDERSCORE };
 ARGUMENT rule5 = { PROCEDURE, IDENT_WITHCOMMAS, UNDERSCORE };
 ARGUMENT rule6 = { ASSIGN, STMT, PROG_LINE, INTEGER, UNDERSCORE };
 ARGUMENT rule7 = { STMT, ASSIGN,WHILE,IF,PROG_LINE,CALL,PROCEDURE,IDENT_WITHCOMMAS,INTEGER };
 ARGUMENT rule_arg1_for_pattern = { ASSIGN, WHILE };
 ARGUMENT rule_arg2_for_pattern = { VARIABLE, IDENT_WITHCOMMAS, UNDERSCORE };
 ARGUMENT rule_arg3_for_pattern = { EXPRESSION_SPEC,UNDERSCORE };

 /*****************
 * Public methods *
 *****************/

RelationshipTable::RelationshipTable()
{
    ARGUMENT arg1, arg2;
    ARGUMENT arg3; //Extra argument for PATTERN
    
    //Modifies & Uses
    arg1 = rule1;
    arg2 = rule2;
    rModify = Relationship(arg1, arg2);
    rUses = Relationship(arg1, arg2);
    relTable[MODIFIES] = rModify;
    relTable[USES] = rUses;

    //Parent & Parent*
    arg1 = rule3;
    arg2 = rule4;
    rParent = Relationship(arg1, arg2);
    rParentStar = Relationship(arg1, arg2);
    relTable[PARENT] = rParent;
    relTable[PARENTSTAR] = rParentStar;

    //Follows & Follows*
    arg1 = rule4;
    arg2 = rule4;
    rFollows = Relationship(arg1, arg2);
    rFollowsStar = Relationship(arg1, arg2);
    relTable[FOLLOWS] = rParent;
    relTable[FOLLOWSSTAR] = rParentStar;
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

bool RelationshipTable::isArgValid(RELATION inputRel, ARGTYPE one, ARGTYPE two)
{
    Relationship rel = relTable[inputRel];
    return isArg1Valid(rel, one) && isArg2Valid(rel, two);
}

bool RelationshipTable::isArgValid(RELATION inputRel, ARGTYPE one, ARGTYPE two, ARGTYPE three)
{
    Relationship rel = relTable[inputRel];
    return isArg1Valid(rel, one) && isArg2Valid(rel, two) && isArg3Valid(rel, three);
}


/*****************
* Private helper methods *
*****************/
bool RelationshipTable::isArg1Valid(Relationship rel, ARGTYPE arg) 
{
    ARGUMENT arg1 = rel.getArg1Type();
    for (ARGUMENT::iterator it = arg1.begin(); it != arg1.end(); ++it)
    {
        if (*it == arg)
            return true;
    }
    return false;
}

bool RelationshipTable::isArg2Valid(Relationship rel, ARGTYPE arg)
{
    ARGUMENT arg2 = rel.getArg2Type();
    for (ARGUMENT::iterator it = arg2.begin(); it != arg2.end(); ++it)
    {
        if (*it == arg)
            return true;
    }
    return false;
}

bool RelationshipTable::isArg3Valid(Relationship rel, ARGTYPE arg)
{
    ARGUMENT arg3 = rel.getArg2Type();
    for (ARGUMENT::iterator it = arg3.begin(); it != arg3.end(); ++it)
    {
        if (*it == arg)
            return true;
    }
    return false;
}
