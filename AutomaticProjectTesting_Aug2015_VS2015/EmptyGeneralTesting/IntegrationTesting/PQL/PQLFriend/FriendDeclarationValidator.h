#pragma once
#include "..\..\..\SPA\PQL\Validator\Declaration\DeclarationValidator.h"

class FriendDeclarationValidator
{
    DeclarationValidator dv = DeclarationValidator(NULL);

public:
    FriendDeclarationValidator(QueryTreeStub *qtPtrNew);
    ~FriendDeclarationValidator();

    bool isValidDeclaration(string str);

    QueryTreeStub getQueryTreeCopy();
    QueryTreeStub** getQueryTreeAddress();
};

