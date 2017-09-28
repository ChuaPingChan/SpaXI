#pragma once
#include "..\..\..\SPA\PQL\Validator\Declaration\DeclarationValidator.h"

class FriendDeclarationValidator
{
    DeclarationValidator dv = DeclarationValidator(NULL);

public:
    FriendDeclarationValidator(QueryTree *qtPtrNew);
    ~FriendDeclarationValidator();

    bool isValidDeclaration(string str);

    QueryTree getQueryTreeCopy();
    QueryTree** getQueryTreeAddress();
};

