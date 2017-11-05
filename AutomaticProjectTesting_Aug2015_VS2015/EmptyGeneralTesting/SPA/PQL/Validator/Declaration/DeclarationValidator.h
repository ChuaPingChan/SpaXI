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

/**
 * Checks the validation of a given declaration
 */
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

    unordered_set<string> synonymBank;                  // Contains list of declared synonyms

    Entity getEntityIndexReference(string entity);      // Converts string form of entity into its enum form

    bool areValidSynonyms(Entity entity, string str);   // Checks if string contains valid synonyms and store them in the QueryTree

    bool hasValidEntityAndSynonym(string str);          // Checks if a given string contains a single valid entity followed by valid synonyms

    bool isDeclaredSynonym(string synonym);             // Check if a synonym has been declared before
};
