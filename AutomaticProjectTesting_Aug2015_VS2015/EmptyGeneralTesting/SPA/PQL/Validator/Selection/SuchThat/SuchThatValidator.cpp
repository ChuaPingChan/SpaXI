#include "SuchThatValidator.h"

SuchThatValidator::SuchThatValidator(string rel, string paramStr, QueryTree * qtPtrNew)
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

const string SuchThatValidator:: MODIFIES = "Modifies";
const string SuchThatValidator:: USES = "Uses";
const string SuchThatValidator:: PARENT = "Parent";
const string SuchThatValidator:: PARENTSTAR = "Parent*";
const string SuchThatValidator:: FOLLOWS = "Follows";
const string SuchThatValidator:: FOLLOWSSTAR = "Follows*";
const string SuchThatValidator:: CALLS = "Calls";
const string SuchThatValidator:: CALLSSTAR = "Calls*";
const string SuchThatValidator:: NEXT = "Next";
const string SuchThatValidator:: NEXTSTAR = "Next*";
const string SuchThatValidator:: AFFECTS = "Affects";
const string SuchThatValidator:: AFFECTSSTAR = "Affects*";

const string SuchThatValidator:: STMT = "stmt";
const string SuchThatValidator:: ASSIGN = "assign";
const string SuchThatValidator:: WHILE = "while";
const string SuchThatValidator:: IF = "if";
const string SuchThatValidator:: PROG_LINE = "prog_line";
const string SuchThatValidator:: CALL = "call";
const string SuchThatValidator:: PROCEDURE = "procedure";
const string SuchThatValidator:: VARIABLE = "variable";
const string SuchThatValidator:: INTEGER = "int";
const string SuchThatValidator:: UNDERSCORE = "underscore";
const string SuchThatValidator:: IDENT_WITH_QUOTES = "identWithQuotes";
const string SuchThatValidator:: CONSTANT = "constant";

void SuchThatValidator::validate()
{
}

bool SuchThatValidator::isValid()
{
    return this->validity;
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

string SuchThatValidator::extractArgOne(string keyword, string str)
{
    string delimFirst = keyword + "(";
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

bool SuchThatValidator::isIdentWithQuotes(string arg)
{
    string LETTER = "([a-zA-Z])";
    string DIGIT = "([0-9])";
    string HASH = "(#)";
    string IDENT = "(" + LETTER + "(" + LETTER + "|" + DIGIT + "|" + HASH + ")*)";
    string IDENT_WITH_QUOTES = "(\"" + IDENT + "\")";

    regex checkIdentWithInvertedCommas = regex(IDENT_WITH_QUOTES);
    return regex_match(arg, checkIdentWithInvertedCommas);
}
