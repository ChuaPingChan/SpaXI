#include "AssignPatternValidator.h"

AssignPatternValidator::AssignPatternValidator(PatternType patternType, string patternSyn, string paramStr, QueryTree *qtPtrNew)
    :PatternValidator(patternType, patternSyn, paramStr, qtPtrNew)
{
}

AssignPatternValidator::~AssignPatternValidator()
{
}

void AssignPatternValidator::validate()
{
    string firstArg = extractArgOne(paramStr);
    string secondArg = extractArgTwo(paramStr);

    if (isValidArgOne(firstArg) && isValidArgTwo(secondArg)) {
        this->argOne = firstArg;
        this->argTwo = secondArg;
        this->validity = true;
    }
    else {
        this->validity = false;
    }
}

bool AssignPatternValidator::isValid()
{
    return this->validity;
}

bool AssignPatternValidator::isValidArgOne(string &argOne)
{
    QueryTree qt = *(this->qtPtr);
    if (qt.isEntitySynonymExist(argOne, VARIABLE))
    {
        this->argOneType = VARIABLE;
        return true;
    }

    else if (argOne == "_")
    {
        this->argOneType = UNDERSCORE;
        return true;
    }

    else if (RegexValidators::isValidIdentWithQuotesRegex(argOne))
    {
        argOne = Formatter::removeAllQuotes(argOne);
        this->argOneType = IDENT_WITHQUOTES;
        return true;
    }

    else
    {
        return false;
    }
}

bool AssignPatternValidator::isValidArgTwo(string &argTwo)
{
    if (argTwo == "_")
    {
        this->argTwoType = UNDERSCORE;
        return true;
    }
    
    else if (RegexValidators::isValidExpressionSpecPartialRegex(argTwo))
    {
        argTwo = Formatter::removeAllQuotes(argTwo);
        argTwo = Formatter::removeAllUnderscores(argTwo);
        this->argTwoType = EXPRESSION_SPEC_PARTIAL;
        return isWellFormExpr(argTwo);
    }

    else if (RegexValidators::isValidExpressionSpecExactRegex(argTwo))
    {
        argTwo = Formatter::removeAllQuotes(argTwo);
        this->argTwoType = EXPRESSION_SPEC_EXACT;
        return isWellFormExpr(argTwo);
    }

    else
    {
        return false;
    }
}

string AssignPatternValidator::extractArgOne(string str)
{
    string delimFirst = "(";
    string delimSecond = ",";

    return Formatter::getBetweenTwoDelims(str, delimFirst, delimSecond);
}

string AssignPatternValidator::extractArgTwo(string str)
{
    string secondArg = Formatter::getStringAfterDelim(str, ",");
    smatch argTwoMatch;
    regex argTwoRegex(RegexValidators::PATTERN_ASSIGN_SECONDARG_REGEX);
    regex_search(secondArg, argTwoMatch, argTwoRegex);
    return argTwoMatch[0].str();
}

/*
* Pre-cond: str passes EXPRESSION_SPEC regex
* Returns true when expression is well-formed
*/
bool AssignPatternValidator::isWellFormExpr(string str)
{
    int countOpenBracket = 0;
    int countCloseBracket = 0;

    regex bracketRegex(RegexValidators::OPEN_BRACKET_REGEX+ "|" + RegexValidators::CLOSE_BRACKET_REGEX);
    sregex_iterator it(str.cbegin(), str.cend(), bracketRegex);
    sregex_iterator it_end;

    for (; it != it_end; it++)
    {
        string currentBracketType = it->str(0);
        if (RegexValidators::isValidOpenBracketRegex(currentBracketType))
        {
            countOpenBracket++;
        }
        else if (RegexValidators::isValidCloseBracketRegex(currentBracketType))
        {
            countCloseBracket++;
        }

    }

    return countOpenBracket == countCloseBracket;
}
