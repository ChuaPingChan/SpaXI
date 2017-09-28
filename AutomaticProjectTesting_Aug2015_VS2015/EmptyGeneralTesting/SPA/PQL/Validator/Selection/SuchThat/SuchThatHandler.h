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
#include "..\..\..\QueryTreeStub.h"

class SuchThatHandler
{
public:
    SuchThatHandler(QueryTreeStub *qtPtrNew);
    ~SuchThatHandler();

    bool isValidSuchThat(string str);
        

private:
    QueryTreeStub *qtPtr;

    string removeAllSpaces(string str);
};
