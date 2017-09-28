#include "FriendDeclarationValidator.h"


FriendDeclarationValidator::FriendDeclarationValidator(QueryTreeStub *qtPtrNew)
{
    dv = DeclarationValidator(qtPtrNew);
}


FriendDeclarationValidator::~FriendDeclarationValidator()
{
}

bool FriendDeclarationValidator::isValidDeclaration(string str)
{
    return dv.isValidDeclaration(str);
}

QueryTreeStub FriendDeclarationValidator::getQueryTreeCopy()
{
    return *(dv.qtPtr);
}

QueryTreeStub** FriendDeclarationValidator::getQueryTreeAddress()
{
    return &(dv.qtPtr);
}
