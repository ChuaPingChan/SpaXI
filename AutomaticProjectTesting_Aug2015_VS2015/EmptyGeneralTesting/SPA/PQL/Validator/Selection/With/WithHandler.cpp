#include "WithHandler.h"

WithHandler::WithHandler(QueryTree * qtPtrNew)
{
    this->qtPtr = qtPtrNew;
}

WithHandler::~WithHandler()
{
}

bool WithHandler::isValidWith(string str)
{
    string processedStr = Formatter::removeAllSpaces(str);
    WithValidator withValidator = WithValidator(qtPtr);

    withValidator.validate(processedStr);

    if (withValidator.isValid() && !isExactlySameLhsAndRhs(withValidator)) {
        WithClause withClause = makeWithClause(withValidator);
        storeInQueryTree(withClause);
        return true;
    }
    else if (withValidator.isValid() && isExactlySameLhsAndRhs(withValidator)) {
        return true;    //Drop the making of clause as optimisation
    }
    else
    {
        return false;
    }
}

bool WithHandler::isExactlySameLhsAndRhs(WithValidator wv)
{
    return (wv.getLhsAttribute() == wv.getRhsAttribute() && wv.getLhsValue() == wv.getRhsValue());
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
