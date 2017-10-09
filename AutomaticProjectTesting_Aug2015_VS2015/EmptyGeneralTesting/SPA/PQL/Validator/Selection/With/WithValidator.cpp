#include "WithValidator.h"

WithValidator::WithValidator(QueryTree *qtPtrNew)
{
}

WithValidator::~WithValidator()
{
}

void WithValidator::validate(string str)
{
    string lhs = extractLhs(str);
    string rhs = extractRhs(str);

    determineLhsAttributeAndValue(lhs);
    determineRhsAttributeAndValue(rhs);

    if (lhs == rhs) //TODO: Think where to put this code, i cannt return true immediately cos synonym may nt be in tree
    {
        this->validity = true;
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

void WithValidator::determineLhsAttributeAndValue(string lhs)
{
    if (RegexValidators::isValidAttrRefRegex(lhs))
    {
        //TODO: Need check with tree wad entity is this
        //See can the entity have attribute or nt
    }
    else if (RegexValidators::isValidIntegerRegex(lhs))
    {
        this->lhsAttribute = INTEGER_ATTRIBUTE;
        this->lhsValue = lhs;
    }
    else if (RegexValidators::isValidIdentWithQuotesRegex(lhs))
    {
        this->lhsAttribute = IDENT_WITH_QUOTES_ATTRIBUTE;
        string processedLhs = Formatter::removeAllQuotes(lhs);
        this->lhsValue = processedLhs;
    }
    else if (RegexValidators::isValidSynonymRegex(lhs))
    {
        if (qtPtr->isEntitySynonymExist(lhs, PROG_LINE))
        {
            this->lhsAttribute = PROG_LINE_ATTRIBUTE;
            this->lhsValue = lhs;
        }
    }
    //TODO: Else throw exceptions
}

void WithValidator::determineRhsAttributeAndValue(string str)
{
}
