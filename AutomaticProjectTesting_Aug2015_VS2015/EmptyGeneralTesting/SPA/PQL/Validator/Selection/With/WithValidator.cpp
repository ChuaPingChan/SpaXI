#include "WithValidator.h"

WithValidator::WithValidator(QueryTree *qtPtrNew)
{
    this->qtPtr = qtPtrNew;
}

WithValidator::~WithValidator()
{
}

void WithValidator::validate(string str)
{
    string lhs = extractLhs(str);
    string rhs = extractRhs(str);

    if (isValidLhs(lhs) && isValidRhs(rhs) && isLhsSameTypeAsRhs())
    {
        if (lhsEntity == INTEGER && rhsEntity == INTEGER && lhsValue!=rhsValue)
        {
            this->validity = false;
        }
        else if (lhsEntity == IDENT_WITHQUOTES && rhsEntity == IDENT_WITHQUOTES && lhsValue != rhsValue)
        {
            this->validity = false;
        }
        else
        {
            this->validity = true;
        }
    }
    else
    {
        this->validity = false;
    }
}

bool WithValidator::isValid()
{
    return this->validity;
}

WithType WithValidator::getLhsWithType()
{
    return this->lhsWithType;
}

Entity WithValidator::getLhsEntity()
{
    return this->lhsEntity;
}

string WithValidator::getLhsValue()
{
    return this->lhsValue;
}

WithType WithValidator::getRhsWithType()
{
    return this->rhsWithType;
}

Entity WithValidator::getRhsEntity()
{
    return this->rhsEntity;
}

string WithValidator::getRhsValue()
{
    return this->rhsValue;
}

string WithValidator::extractLhs(string str)
{
    return Formatter::getStringBeforeDelim(str, "=");
}

string WithValidator::extractRhs(string str)
{
    return Formatter::getStringAfterDelim(str, "=");
}

bool WithValidator::isValidLhs(string lhs)
{
    if (RegexValidators::isValidAttrRefRegex(lhs))
    {
        string attrRefSynonymStr = getAttrRefSynonymStr(lhs);
        string attrRefAttributeStr = getAttrRefAttributeStr(lhs);
        try {
            Entity entity = getEntityOfSynonym(attrRefSynonymStr);
            WithType withType = getWithType(entity, attrRefAttributeStr);
            this->lhsWithType = withType;
            this->lhsEntity = entity;
            this->lhsValue = attrRefSynonymStr;
            return true;
        }
        catch (SynonymNotFoundException& snfe) {
            return false;
        }
        catch (AttributeNotFoundException& anfe) {
            return false;
        }
    }
    else if (RegexValidators::isValidIntegerRegex(lhs))
    {
        this->lhsWithType = INTEGER_WITH;
        this->lhsEntity = INTEGER;
        this->lhsValue = lhs;
        return true;
    }
    else if (RegexValidators::isValidIdentWithQuotesRegex(lhs))
    {
        string processedLhs = Formatter::removeAllQuotes(lhs);
        this->lhsWithType = STRING_WITH;
        this->lhsEntity = IDENT_WITHQUOTES;
        this->lhsValue = processedLhs;
        return true;
    }
    else if (RegexValidators::isValidSynonymRegex(lhs))
    {
        if (qtPtr->isEntitySynonymExist(lhs, PROG_LINE))
        {
            this->lhsWithType = INTEGER_WITH;
            this->lhsEntity = PROG_LINE;
            this->lhsValue = lhs;
            return true;
        }
    }
    else
    {
        return false;
    }
}

bool WithValidator::isValidRhs(string rhs)
{
    if (RegexValidators::isValidAttrRefRegex(rhs))
    {
        string attrRefSynonymStr = getAttrRefSynonymStr(rhs);
        string attrRefAttributeStr = getAttrRefAttributeStr(rhs);
        try {
            Entity entity = getEntityOfSynonym(attrRefSynonymStr);
            WithType withType = getWithType(entity, attrRefAttributeStr);
            this->rhsWithType = withType;
            this->rhsEntity = entity;
            this->rhsValue = attrRefSynonymStr;
            return true;
        }
        catch (SynonymNotFoundException& snfe) {
            return false;
        }
        catch (AttributeNotFoundException& anfe) {
            return false;
        }
    }
    else if (RegexValidators::isValidIntegerRegex(rhs))
    {
        this->rhsWithType = INTEGER_WITH;
        this->rhsEntity = INTEGER;
        this->rhsValue = rhs;
        return true;
    }
    else if (RegexValidators::isValidIdentWithQuotesRegex(rhs))
    {
        string processedrhs = Formatter::removeAllQuotes(rhs);
        this->rhsWithType = STRING_WITH;
        this->rhsEntity = IDENT_WITHQUOTES;
        this->rhsValue = processedrhs;
        return true;
    }
    else if (RegexValidators::isValidSynonymRegex(rhs))
    {
        if (qtPtr->isEntitySynonymExist(rhs, PROG_LINE))
        {
            this->rhsWithType = INTEGER_WITH;
            this->rhsEntity = PROG_LINE;
            this->rhsValue = rhs;
            return true;
        }
    }
    else
    {
        return false;
    }
}

bool WithValidator::isLhsSameTypeAsRhs()
{
    return this->lhsWithType == this->rhsWithType;
}

Entity WithValidator::getEntityOfSynonym(string syn)
{
    if (qtPtr->isEntitySynonymExist(syn, PROCEDURE))
    {
        return PROCEDURE;
    }
    else if (qtPtr->isEntitySynonymExist(syn, STMT))
    {
        return STMT;
    }
    else if (qtPtr->isEntitySynonymExist(syn, ASSIGN))
    {
        return ASSIGN;
    }
    else if (qtPtr->isEntitySynonymExist(syn, CALL))
    {
        return CALL;
    }
    else if (qtPtr->isEntitySynonymExist(syn, WHILE))
    {
        return WHILE;
    }
    else if (qtPtr->isEntitySynonymExist(syn, IF))
    {
        return IF;
    }
    else if (qtPtr->isEntitySynonymExist(syn, VARIABLE))
    {
        return VARIABLE;
    }
    else if (qtPtr->isEntitySynonymExist(syn, CONSTANT))
    {
        return CONSTANT;
    }
    else
    {
        throw SynonymNotFoundException("In WithValidator.cpp, when calling getEntityOfSynonym(). Synonym cannot be found in the QueryTree and Entity cannot be assigned. Input string: " + syn);
    }
}

WithType WithValidator::getWithType(Entity entity, string attr)
{
    if (entity == PROCEDURE && RegexValidators::isValidProcNameString(attr)) {
        return STRING_WITH;
    }
    else if (entity == STMT && RegexValidators::isValidStmtNumString(attr)) {
        return INTEGER_WITH;
    }
    else if (entity == ASSIGN && RegexValidators::isValidStmtNumString(attr)) {
        return INTEGER_WITH;
    }
    else if (entity == CALL && RegexValidators::isValidStmtNumString(attr)) {
        return INTEGER_WITH;
    }
    else if (entity == CALL && RegexValidators::isValidProcNameString(attr)) {
        return STRING_WITH;
    }
    else if (entity == WHILE && RegexValidators::isValidStmtNumString(attr)) {
        return INTEGER_WITH;
    }
    else if (entity == IF && RegexValidators::isValidStmtNumString(attr)) {
        return INTEGER_WITH;
    }
    else if (entity == VARIABLE && RegexValidators::isValidVarNameString(attr)) {
        return STRING_WITH;
    }
    else if (entity == CONSTANT && RegexValidators::isValidValueString(attr)) {
        return INTEGER_WITH;
    }
    else {
        throw AttributeNotFoundException("In WithValidator.cpp, when calling getAttributeOfAttrRefAttribute(). Attribute does not match defined attribute or Entity does not have that attribute. Input Entity: " + to_string(entity) + ", Input String: " + attr);
    }
}

string WithValidator::getAttrRefSynonymStr(string str)
{
    return Formatter::getStringBeforeDelim(str, ".");
}

string WithValidator::getAttrRefAttributeStr(string str)
{
    return Formatter::getStringAfterDelim(str, ".");
}
