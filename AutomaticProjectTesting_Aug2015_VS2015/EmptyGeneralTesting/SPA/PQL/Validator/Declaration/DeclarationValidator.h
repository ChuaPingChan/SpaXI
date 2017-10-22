#pragma once
#include <string>
#include <unordered_set>
#include <regex>
#include "..\..\QueryTree.h"
#include "..\..\..\Entity.h"
#include "..\ValidationRegexLibrary\RegexValidators.h"
#include "..\..\..\Exceptions\EntityNotFoundException.h"
#include "..\..\..\Exceptions\SynonymAlreadyExistException.h"

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

    unordered_set<string> synonymBank;   //Contains list of declared synonyms

    Entity getEntityIndexReference(string entity);

    bool areValidSynonyms(Entity entity, string str);

    bool hasValidEntityAndSynonym(string str);

    bool isDeclaredSynonym(string synonym);
};
