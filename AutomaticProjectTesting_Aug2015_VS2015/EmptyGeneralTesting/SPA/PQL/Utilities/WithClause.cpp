#include "WithClause.h"
#include "../../Entity.h"
#include "Clause.h"

WithClause::WithClause(WithType withType, Entity lhsEntity, string lhsValue, Entity rhsEntity, string rhsValue)
    : Clause(Clause::ClauseType::WITH)
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

WithClause::~WithClause()
{
}

shared_ptr<WithClause> WithClause::getSharedPtr()
{
    return WithClausePtr(new WithClause(getWithType(), getLhsEntity(),
        getLhsValue(), getRhsEntity(), getRhsValue()));
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
