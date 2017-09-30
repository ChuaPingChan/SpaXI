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
#include "..\..\..\Utilities\SuchThatClause.h"
#include "..\..\..\Utilities\Formatter.h"

class SuchThatHandler
{
    static const string MODIFIES;
    static const string USES;
    static const string PARENT;
    static const string PARENTSTAR;
    static const string FOLLOWS;
    static const string FOLLOWSSTAR;
    static const string CALLS;
    static const string CALLSSTAR;
    static const string NEXT;
    static const string NEXTSTAR;
    static const string AFFECTS;
    static const string AFFECTSSTAR;

    static const string STMT;
    static const string ASSIGN;
    static const string WHILE;
    static const string IF;
    static const string PROG_LINE;
    static const string CALL;
    static const string PROCEDURE;
    static const string VARIABLE;
    static const string INTEGER;
    static const string UNDERSCORE;
    static const string IDENT_WITH_QUOTES;
    static const string CONSTANT;

public:
    SuchThatHandler(QueryTree *qtPtrNew);
    ~SuchThatHandler();

    bool isValidSuchThat(string str);
        

private:
    QueryTree *qtPtr;

    string getSuchThatKeyWord(string str);

    int getRelIndex(string rel);
    int getArgTypeIndex(string arg);

    SuchThatClause makeSuchThatClause(SuchThatValidator stv);
    bool storeInQueryTree(SuchThatClause stc);
};
