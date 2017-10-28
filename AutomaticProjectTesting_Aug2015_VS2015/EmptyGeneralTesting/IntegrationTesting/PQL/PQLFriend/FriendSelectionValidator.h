#pragma once
#include "..\..\..\SPA\PQL\Validator\Selection\SelectionValidator.h"

class FriendSelectionValidator
{
    SelectionValidator sv = SelectionValidator(NULL);

public:
    FriendSelectionValidator(QueryTree *qtPtrNew);

    string extractRawString(string str);
    QueryTree getQueryTreeCopy();
    QueryTree** getQueryTreeAddress();
};

