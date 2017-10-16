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
        return true;
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
    string delimFirst = ",";
    string delimSecond = ")";

    return Formatter::getBetweenTwoDelims(str, delimFirst, delimSecond);
}

bool AssignPatternValidator::isWellFormExpr(string str)
{
    regex exprTokenizerRegex("[0-9a-zA-Z]+|[0-9]+|[a-zA-Z]+|[+]|[-]|[*]|[(]|[)]");
    if (!regex_match(str, exprTokenizerRegex))
    {
        return false;
    }

    sregex_iterator it(str.cbegin(), str.cend(), exprTokenizerRegex);
    sregex_iterator it_end;

    int countOpenBracket = 0;
    int countCloseBracket = 0;

    string firstToken = it->str(0);
    if (!RegexValidators::isValidSynonymRegex(firstToken) && !RegexValidators::isValidOpenBracketRegex(firstToken) && !RegexValidators::isValidIntegerRegex(firstToken))
    {
        return false;
    }
    if (RegexValidators::isValidOpenBracketRegex(firstToken))
    {
        countOpenBracket++;
    }
    string prevToken = firstToken;
    it++;

    while(it != it_end)
    {
        string currentToken = it->str(0);
        prevToken = currentToken;
        if ((RegexValidators::isValidSynonymRegex(currentToken) || RegexValidators::isValidIntegerRegex)
            && !RegexValidators::isValidOperatorRegex(prevToken) && !RegexValidators::isValidOpenBracketRegex(prevToken))
        {
            return false;
        }
        else if (RegexValidators::isValidOperatorRegex(currentToken)
            && !RegexValidators::isValidSynonymRegex(prevToken) && !RegexValidators::isValidIntegerRegex(prevToken) && !RegexValidators::isValidCloseBracketRegex(prevToken))
        {
            return false;
        }
        else if (RegexValidators::isValidOpenBracketRegex(currentToken))
        {
            if (!RegexValidators::isValidOperatorRegex(prevToken) && !RegexValidators::isValidOpenBracketRegex(prevToken))
            {
                return false;
            }
            else
            {
                countOpenBracket++;
            }
        }
        else if (RegexValidators::isValidCloseBracketRegex(currentToken))
        {
            if (!RegexValidators::isValidSynonymRegex(prevToken) && !RegexValidators::isValidIntegerRegex(prevToken) && !RegexValidators::isValidCloseBracketRegex(prevToken))
            {
                return false;
            }
            else
            {
                countCloseBracket++;
            }
        }

        it++;

        if (it == it_end)   //last token
        {
            if (!RegexValidators::isValidSynonymRegex(currentToken) && !RegexValidators::isValidIntegerRegex(currentToken) && !RegexValidators::isValidCloseBracketRegex(currentToken))
            {
                return false;
            }
            else if (RegexValidators::isValidCloseBracketRegex(currentToken))
            {
                countCloseBracket++;
            }
        }
    }

    return countOpenBracket == countOpenBracket;
}
