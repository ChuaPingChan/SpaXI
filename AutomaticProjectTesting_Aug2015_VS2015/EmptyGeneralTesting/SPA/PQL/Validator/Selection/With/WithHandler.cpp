#include "WithHandler.h"

WithHandler::WithHandler(QueryTree * qtPtrNew)
{
    this->qtPtr = qtPtrNew;
}

WithHandler::~WithHandler()
{
}

/*
* Pre-cond: str pass ATTRCOMPARE_REGEX
* Post-Cond: If true, With clause stored in QueryTree
* Returns true when with is semantically valid
*/
bool WithHandler::isValidWith(string str)
{
    string processedStr = Formatter::removeAllSpacesAndTabs(str);
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
    return (wv.getLhsWithType() == wv.getRhsWithType()
        && wv.getLhsEntity() == wv.getRhsEntity()
        && wv.getLhsValue() == wv.getRhsValue());
}

WithClause WithHandler::makeWithClause(WithValidator withValidator)
{
    WithType withType = withValidator.getLhsWithType();
    Entity lhsEntity = withValidator.getLhsEntity();
    Entity rhsEntity = withValidator.getRhsEntity();
    string lhsValue = withValidator.getLhsValue();
    string rhsValue = withValidator.getRhsValue();
    return WithClause(withType, lhsEntity, lhsValue, rhsEntity, rhsValue);
}

bool WithHandler::storeInQueryTree(WithClause wc)
{
    qtPtr->insertWith(wc);
    return true;
}
