#include "FriendSelectionValidator.h"


FriendSelectionValidator::FriendSelectionValidator(QueryTree *qtPtrNew)
{
    sv = SelectionValidator(qtPtrNew);
}

string FriendSelectionValidator::extractRawString(string str)
{
    return sv.extractSelectRawStr(str);
}

QueryTree FriendSelectionValidator::getQueryTreeCopy()
{
    return *(sv.qtPtr);
}

QueryTree** FriendSelectionValidator::getQueryTreeAddress()
{
    return &(sv.qtPtr);
}
