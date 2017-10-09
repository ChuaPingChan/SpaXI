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
    WithValidator withValidator = WithValidator(qtPtr);
    withValidator.validate(processedStr);

    if (withValidator.isValid()) {
        WithClause withClause = makeWithClause(withValidator);
        storeInQueryTree(withClause);
        return true;
    }
    else
    {
        return false;
    }
}

WithClause WithHandler::makeWithClause(WithValidator withValidator)
{
    Attribute lhsAttribute = withValidator.getLhsAttribute();
    Attribute rhsAttribute = withValidator.getRhsAttribute();
    string lhsValue = withValidator.getLhsValue();
    string rhsValue = withValidator.getRhsValue();
    return WithClause(lhsAttribute, lhsValue, rhsAttribute, rhsValue);
}

bool WithHandler::storeInQueryTree(WithClause wc)
{
    qtPtr->insertWith(wc);
    return true;
}
