#include "WithClause.h"
#include "../../Entity.h"

WithClause::WithClause(WithType withType, Entity lhsEntity, string lhsValue, Entity rhsEntity, string rhsValue)
{
    this->withType = withType;
    this->lhsEntity = lhsEntity;
    this->lhsValue = lhsValue;
    this->rhsEntity = rhsEntity;
    this->rhsValue = rhsValue;

    if (entityIsSynonym(lhsEntity)) {
        addSynonym(lhsValue);
    }
    if (entityIsSynonym(rhsEntity)) {
        addSynonym(rhsValue);
    }
}

WithClause::WithClause(WithClause & withClause)
{
    this->withType = withClause.getWithType();
    this->lhsEntity = withClause.getLhsEntity();
    this->lhsValue = withClause.getLhsValue();
    this->rhsEntity = withClause.getRhsEntity();
    this->rhsValue = withClause.getRhsValue();

    setSynonyms(withClause.getSynonyms());
}

WithClause::~WithClause()
{
}

WithType WithClause::getWithType()
{
    return this->withType;
}

Entity WithClause::getLhsEntity()
{
    return this->lhsEntity;
}

Entity WithClause::getRhsEntity()
{
    return this->rhsEntity;
}

string WithClause::getLhsValue()
{
    return this->lhsValue;
}

string WithClause::getRhsValue()
{
    return this->rhsValue;
}
