#pragma once
#include <string>
#include <unordered_set>
#include <regex>
#include "..\..\QueryTreeStub.h"

using namespace std;

class DeclarationValidator
{
    friend class FriendDeclarationValidator;

public:
    DeclarationValidator(QueryTreeStub *qtPtrNew);
    ~DeclarationValidator();

    bool isValidDeclaration(string str);
    bool setQueryTreeStub(QueryTreeStub *qtPtrNew);

private:
    QueryTreeStub *qtPtr;

    unordered_set<string> synonymBank;   //Contains list of used synonyms
    vector<string> unvalidatedQueryVector;  //Holds unvalidated stmts retreived from query tree

    bool isValidEntity(string str);
    bool isValidSynonym(string str);
};
