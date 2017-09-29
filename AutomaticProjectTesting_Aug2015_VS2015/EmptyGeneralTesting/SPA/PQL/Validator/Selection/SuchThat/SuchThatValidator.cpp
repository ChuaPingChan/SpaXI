#include "SuchThatValidator.h"



SuchThatValidator::SuchThatValidator(QueryTree *qtPtrNew)
{
    this->qtPtr = qtPtrNew;
}

SuchThatValidator::SuchThatValidator()
{
}

SuchThatValidator::~SuchThatValidator()
{
}

void SuchThatValidator::validate()
{
}

bool SuchThatValidator::isValid()
{
    return false;
}

string SuchThatValidator::getRel()
{
    return this->rel;
}

string SuchThatValidator::getArgOneType()
{
    return this->argOneType;
}

string SuchThatValidator::getArgTwoType()
{
    return this->argTwoType;
}

string SuchThatValidator::getArgOne()
{
    return this->argOne;
}

string SuchThatValidator::getArgTwo()
{
    return this->argTwo;
}

string SuchThatValidator::getArgOne(string keyword, string str)
{
    string delimFirst = keyword + "(";
    string delimSecond = ",";

    return Formatter::getBetweenTwoStrings(str, delimFirst, delimSecond);
}

string SuchThatValidator::getArgTwo(string str)
{
    string delimFirst = ",";
    string delimSecond = ")";

    return Formatter::getBetweenTwoStrings(str, delimFirst, delimSecond);
}

/*--------------- Check if argument is in a clause ---------------*/
bool SuchThatValidator::isArgumentInClause(string arg, unordered_set<string> clause)
{
    if (find(clause.begin(), clause.end(), arg) != clause.end())
        return true;
    else
        return false;
}

//TODO: Remove after implement regex table
bool SuchThatValidator::isIntegerRegexCheck(string arg)
{
    string DIGIT = "([0-9])";
    string INTEGER = "(" + DIGIT + "+)";
    regex checkInt = regex(INTEGER);
    return regex_match(arg, checkInt);
}

bool SuchThatValidator::isIdentWithInvertedCommas(string arg)
{
    string LETTER = "([a-zA-Z])";
    string DIGIT = "([0-9])";
    string HASH = "(#)";
    string IDENT = "(" + LETTER + "(" + LETTER + "|" + DIGIT + "|" + HASH + ")*)";
    string IDENT_WITH_INVERTED_COMMA = "(\"" + IDENT + "\")";

    regex checkIdentWithInvertedCommas = regex(IDENT_WITH_INVERTED_COMMA);
    return regex_match(arg, checkIdentWithInvertedCommas);
}
