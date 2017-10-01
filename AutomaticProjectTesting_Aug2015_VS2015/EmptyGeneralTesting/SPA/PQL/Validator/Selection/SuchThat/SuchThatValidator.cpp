#include "SuchThatValidator.h"

SuchThatValidator::SuchThatValidator(int rel, string paramStr, QueryTree * qtPtrNew)
{
    this->rel = rel;
    this->paramStr = paramStr;
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
    return this->validity;
}

int SuchThatValidator::getRel()
{
    return this->rel;
}

int SuchThatValidator::getArgOneType()
{
    return this->argOneType;
}

int SuchThatValidator::getArgTwoType()
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

string SuchThatValidator::extractArgOne(int rel, string str)
{
    string relStr = RELATIONSHIP_STRING[rel];
    string delimFirst = relStr + "(";
    string delimSecond = ",";

    return Formatter::getBetweenTwoStrings(str, delimFirst, delimSecond);
}

string SuchThatValidator::extractArgTwo(string str)
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
