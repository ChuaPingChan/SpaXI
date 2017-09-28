#pragma once
#include <string>
#include "SuchThatValidator.h"
#include "ModifiesValidator.h"
#include "UsesValidator.h"
#include "ParentValidator.h"
#include "FollowsValidator.h"
#include "CallsValidator.h"
#include "NextValidator.h"
#include "AffectsValidator.h"
#include "..\..\..\QueryTree.h"

class SuchThatHandler
{
public:
    SuchThatHandler(QueryTree *qtPtrNew);
    ~SuchThatHandler();

    bool isValidSuchThat(string str);
        

private:
    QueryTree *qtPtr;

    string removeAllSpaces(string str);
};
