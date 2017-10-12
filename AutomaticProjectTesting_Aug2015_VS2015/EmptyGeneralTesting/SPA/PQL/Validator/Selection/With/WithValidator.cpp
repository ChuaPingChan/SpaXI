#include "WithValidator.h"

const string WithValidator::ATTRIBUTE_STRING[] = {"procName", "stmt#", "stmt#", "stmt#", "procName", "stmt#", "stmt#", "varName", "value"};

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
        if (lhsAttribute == INTEGER_ATTRIBUTE && rhsAttribute == INTEGER_ATTRIBUTE && lhsValue!=rhsValue)
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

Attribute WithValidator::getLhsAttribute()
{
    return this->lhsAttribute;
}

Attribute WithValidator::getRhsAttribute()
{
    return this->rhsAttribute;
}

string WithValidator::getLhsValue()
{
    return this->lhsValue;
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
            Attribute attribute = getAttributeOfAttrRefAttribute(entity, attrRefAttributeStr);
            this->lhsAttribute = attribute;
            this->lhsValue = attrRefSynonymStr;
            return true;
        }
        catch (SynonymNotFoundException& snfe) {
            //TODO: Log msg from snfe.what()
            return false;
        }
        catch (AttributeNotFoundException& anfe) {
            //TODO: Log msg from anfe.what()
            return false;
        }
    }
    else if (RegexValidators::isValidIntegerRegex(lhs))
    {
        this->lhsAttribute = INTEGER_ATTRIBUTE;
        this->lhsValue = lhs;
        return true;
    }
    else if (RegexValidators::isValidIdentWithQuotesRegex(lhs))
    {
        this->lhsAttribute = IDENT_WITH_QUOTES_ATTRIBUTE;
        string processedLhs = Formatter::removeAllQuotes(lhs);
        this->lhsValue = processedLhs;
        return true;
    }
    else if (RegexValidators::isValidSynonymRegex(lhs))
    {
        if (qtPtr->isEntitySynonymExist(lhs, PROG_LINE))
        {
            this->lhsAttribute = PROG_LINE_ATTRIBUTE;
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
            Attribute attribute = getAttributeOfAttrRefAttribute(entity, attrRefAttributeStr);
            this->rhsAttribute = attribute;
            this->rhsValue = attrRefSynonymStr;
            return true;
        }
        catch (SynonymNotFoundException& snfe) {
            //TODO: Log msg from snfe.what()
            return false;
        }
        catch (AttributeNotFoundException& anfe) {
            //TODO: Log msg from anfe.what()
            return false;
        }
    }
    else if (RegexValidators::isValidIntegerRegex(rhs))
    {
        this->rhsAttribute = INTEGER_ATTRIBUTE;
        this->rhsValue = rhs;
        return true;
    }
    else if (RegexValidators::isValidIdentWithQuotesRegex(rhs))
    {
        this->rhsAttribute = IDENT_WITH_QUOTES_ATTRIBUTE;
        string processedrhs = Formatter::removeAllQuotes(rhs);
        this->rhsValue = processedrhs;
        return true;
    }
    else if (RegexValidators::isValidSynonymRegex(rhs))
    {
        if (qtPtr->isEntitySynonymExist(rhs, PROG_LINE))
        {
            this->rhsAttribute = PROG_LINE_ATTRIBUTE;
            this->rhsValue = rhs;
            return true;
        }
    }
    else
    {
        return false;
    }
}

bool WithValidator::isIntegerType(Attribute attr)
{
    return (attr == STMT_ATTRIBUTE || attr == ASSIGN_ATTRIBUTE || attr == CALL_STMT_ATTRIBUTE
            || attr == WHILE_ATTRIBUTE || attr == IF_ATTRIBUTE || attr == CONSTANT_ATTRIBUTE
            || attr == PROG_LINE_ATTRIBUTE || attr == INTEGER_ATTRIBUTE);
}

bool WithValidator::isStringType(Attribute attr)
{
    return (attr == PROCEDURE_ATTRIBUTE || attr == CALL_PROC_ATTRIBUTE || attr == VARIABLE_ATTRIBUTE || attr == IDENT_WITH_QUOTES_ATTRIBUTE);
}

bool WithValidator::isLhsSameTypeAsRhs()
{
    return (isIntegerType(this->lhsAttribute) && isIntegerType(this->rhsAttribute))
        || (isStringType(this->lhsAttribute) && isStringType(this->rhsAttribute));
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
        throw SynonymNotFoundException("In WithValidator.cpp, when calling getEntityOfSynonym(). Synonym cannot be found in the QueryTree and no Entity can be assigned.");
    }
}

Attribute WithValidator::getAttributeOfAttrRefAttribute(Entity entity, string attr)
{
    if (entity == PROCEDURE && attr == ATTRIBUTE_STRING[PROCEDURE_ATTRIBUTE]) {
        return PROCEDURE_ATTRIBUTE;
    }
    else if (entity == STMT && attr == ATTRIBUTE_STRING[STMT_ATTRIBUTE]) {
        return STMT_ATTRIBUTE;
    }
    else if (entity == ASSIGN && attr == ATTRIBUTE_STRING[ASSIGN_ATTRIBUTE]) {
        return ASSIGN_ATTRIBUTE;
    }
    else if (entity == CALL && attr == ATTRIBUTE_STRING[CALL_STMT_ATTRIBUTE]) {
        return CALL_STMT_ATTRIBUTE;
    }
    else if (entity == CALL && attr == ATTRIBUTE_STRING[CALL_PROC_ATTRIBUTE]) {
        return CALL_PROC_ATTRIBUTE;
    }
    else if (entity == WHILE && attr == ATTRIBUTE_STRING[WHILE_ATTRIBUTE]) {
        return WHILE_ATTRIBUTE;
    }
    else if (entity == IF && attr == ATTRIBUTE_STRING[IF_ATTRIBUTE]) {
        return IF_ATTRIBUTE;
    }
    else if (entity == VARIABLE && attr == ATTRIBUTE_STRING[VARIABLE_ATTRIBUTE]) {
        return VARIABLE_ATTRIBUTE;
    }
    else if (entity == CONSTANT && attr == ATTRIBUTE_STRING[CONSTANT_ATTRIBUTE]) {
        return CONSTANT_ATTRIBUTE;
    }
    else {
        throw AttributeNotFoundException("In WithValidator.cpp, when calling getAttributeOfAttrRefAttribute(). Attribute does not match defined attribute or Entity does not have that attribute");
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
