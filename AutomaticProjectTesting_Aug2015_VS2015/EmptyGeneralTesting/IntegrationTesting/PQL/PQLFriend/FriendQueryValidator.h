#pragma once
#include "..\SPA\PQL\Validator\QueryValidator.h"

class FriendQueryValidator
{
public:
    FriendQueryValidator(QueryTree *qtPtrNew);
    ~FriendQueryValidator();

    bool isValidQuery(string query);
    bool getValidDeclarationFlag();
    bool getValidSelectionFlag();

private:
    QueryValidator qv = QueryValidator(NULL);
};

