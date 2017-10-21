#include "FriendQueryValidator.h"

FriendQueryValidator::FriendQueryValidator(QueryTree * qtPtrNew)
{
    qv = QueryValidator(qtPtrNew);
}

FriendQueryValidator::~FriendQueryValidator()
{
}

bool FriendQueryValidator::isValidQuery(string query)
{
    return qv.isValidQuery(query);
}

bool FriendQueryValidator::getValidDeclarationFlag()
{
    return qv.isValidDeclarationFlag;
}

bool FriendQueryValidator::getValidSelectionFlag()
{
    return qv.isValidSelectionFlag;
}
