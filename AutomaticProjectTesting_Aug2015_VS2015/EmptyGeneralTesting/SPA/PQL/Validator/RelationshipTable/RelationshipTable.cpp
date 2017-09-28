#include "RelationshipTable.h"


//Rule 1: SYNONYM (stmt|assign|while|if|prog_line|call|procedure)|STRING|INTEGER
//Rule 2: SYNONYM (variable)|STRING|_
//Rule 3: and so on....

 ARGUMENT rule1 = { "stmt","assign","while","if","prog_line","call","procedure","STRING","INTEGER" };
 ARGUMENT rule2 = { "variable","STRING","_" };

RelationshipTable::RelationshipTable()
{
    ARGUMENT arg1, arg2, arg3;
    
    //Modifies & Uses
    arg1 = rule1;
    arg2 = rule2;
    Relationship rModify(arg1, arg2);
    Relationship rUses(arg1, arg2);
    relTable[MODIFIES] = rModify;
    relTable[USES] = rUses;
    
}


RelationshipTable::~RelationshipTable()
{
}

bool RelationshipTable::hasRelationship(RELATION inputRel)
{
   auto iterator = relTable.find(inputRel);
   if(iterator==relTable.end())
     return false;
   
   return true;
}

bool RelationshipTable::isArgValid(RELATION, ARGTYPE one, ARGTYPE two)
{
    return false;
}

bool RelationshipTable::isArgValid(RELATION, ARGTYPE one, ARGTYPE two, ARGTYPE three)
{
    return false;
}
