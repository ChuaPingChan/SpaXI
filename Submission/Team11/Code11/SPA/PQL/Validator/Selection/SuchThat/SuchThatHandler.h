#pragma once
#include <string>
#include <regex>
#include "SuchThatValidator.h"
#include "ModifiesValidator.h"
#include "UsesValidator.h"
#include "ParentValidator.h"
#include "FollowsValidator.h"
#include "CallsValidator.h"
#include "NextValidator.h"
#include "AffectsValidator.h"
#include "..\..\..\QueryTree.h"
#include "..\..\..\Relationship.h"
#include "..\..\..\Utilities\SuchThatClause.h"
#include "..\..\..\Utilities\Formatter.h"
#include "..\..\..\..\Exceptions\RelationshipNotFoundException.h"

/**
* Checks the validation of suchthat clause
* Wrap into SuchThatClause
* Store SuchThatClause in QueryTree
*/
class SuchThatHandler
{
public:
    SuchThatHandler(QueryTree *qtPtrNew);
    ~SuchThatHandler();

    bool isValidSuchThat(string str);
        

private:
    QueryTree *qtPtr;

    string getSuchThatKeyWord(string str);

    Relationship getRelIndex(string rel);

    SuchThatClause makeSuchThatClause(SuchThatValidator stv);
    bool storeInQueryTree(SuchThatClause stc);
};
