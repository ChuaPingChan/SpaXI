#include "WithHandler.h"

WithHandler::WithHandler(QueryTree * qtPtrNew)
{
}

WithHandler::~WithHandler()
{
}

bool WithHandler::isValidWith(string str)
{
    string processedStr = Formatter::removeAllSpaces(str);
    string lhs;
    string rhs;
    return false;
}

string WithHandler::extractLhs(string str)
{
    return string();
}

bool WithHandler::storeInQueryTree(WithClause wc)
{
    qtPtr->insertWith(wc);
    return true;
}
