#pragma once
#include <string>
#include <unordered_set>
#include <regex>
#include "..\..\QueryTree.h"
#include "..\..\..\Entity.h"
#include "..\ValidationRegexLibrary\RegexValidators.h"

using namespace std;

class DeclarationValidator
{
    friend class FriendDeclarationValidator;

public:
    DeclarationValidator(QueryTree *qtPtrNew);
    ~DeclarationValidator();

    bool isValidDeclaration(string str);
    bool setQueryTree(QueryTree *qtPtrNew);

private:
    QueryTree *qtPtr;

    unordered_set<string> synonymBank;   //Contains list of used synonyms
    vector<string> unvalidatedQueryVector;  //Holds unvalidated stmts retreived from query tree

    bool isValidEntity(string str);
    bool isValidSynonym(string str);
    Entity getEntityIndexReference(string entity);
};
