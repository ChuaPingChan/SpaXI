#include "FriendDeclarationValidator.h"


FriendDeclarationValidator::FriendDeclarationValidator(QueryTree *qtPtrNew)
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

QueryTree FriendDeclarationValidator::getQueryTreeCopy()
{
    return *(dv.qtPtr);
}

QueryTree** FriendDeclarationValidator::getQueryTreeAddress()
{
    return &(dv.qtPtr);
}
