#include "SuchThatHandler.h"

SuchThatHandler::SuchThatHandler(QueryTree *qtPtrNew)
{
    this->qtPtr = qtPtrNew;
}


SuchThatHandler::~SuchThatHandler()
{
}

static const string MODIFIES = "Modifies";
static const string USES = "Uses";
static const string PARENT = "Parent";
static const string PARENTSTAR = "Parent*";
static const string FOLLOWS = "Follows";
static const string FOLLOWSSTAR = "Follows*";
static const string CALLS = "Calls";
static const string CALLSSTAR = "Calls*";
static const string NEXT = "Next";
static const string NEXTSTAR = "Next*";
static const string AFFECTS = "Affects";
static const string AFFECTSSTAR = "Affects*";

static const string STMT = "stmt";
static const string ASSIGN = "assign";
static const string WHILE = "while";
static const string IF = "if";
static const string PROG_LINE = "prog_line";
static const string CALL = "call";
static const string PROCEDURE = "procedure";
static const string VARIABLE = "variable";
static const string INTEGER = "int";
static const string UNDERSCORE = "underscore";
static const string IDENT_WITH_QUOTES = "identWithQuotes";
static const string CONSTANT = "constant";

bool SuchThatHandler::isValidSuchThat(string str)
{
    string processedStr = Formatter::removeAllSpaces(str);
    string rel = getSuchThatKeyWord(processedStr);

    SuchThatValidator suchThatValidator(qtPtr);

    if (rel == "Modifies") {
        suchThatValidator = ModifiesValidator(rel, processedStr);
    }

    if (suchThatValidator.isValid()) {
        SuchThatClause suchThatClause = makeSuchThatClause(suchThatValidator);
        storeInQueryTree(suchThatClause);
        return true;
    }
    else
    {
        return false;
    }
}

//TODO: Put inside regex table (Only the regex part)
string SuchThatHandler::getSuchThatKeyWord(string str)
{
    string SUCH_THAT_KEYWORD = "(Modifies|Uses|Parent|Parent*|Follows|Follows*|Calls|Calls*|Next|Next*|Affects|Affects)";
    regex suchThatKeywordRegex(SUCH_THAT_KEYWORD);
    smatch foundMatch;
    regex_search(str, foundMatch, suchThatKeywordRegex);
    string suchThatKeyword = foundMatch[1];

    return suchThatKeyword;
}

//TODO: Change the index number
int SuchThatHandler::getRelIndex(string rel)
{
    if (rel == "Modifies") {
        return 0;
    }
    return 0;   //stub
}

//TODO: Change the index reference
int SuchThatHandler::getArgTypeIndex(string arg)
{
    if (arg == "int") {
        return 0;
    }
    return 0;   //stub
}

SuchThatClause SuchThatHandler::makeSuchThatClause(SuchThatValidator stv)
{
    int rel = getRelIndex(stv.getRel());
    int argOneType = getArgTypeIndex(stv.getArgOneType());
    int argTwoType = getArgTypeIndex(stv.getArgTwoType());
    string argOne = stv.getArgOne();
    string argTwo = stv.getArgTwo();

    return SuchThatClause(rel, argOneType, argOne, argTwoType, argTwo);
}

bool SuchThatHandler::storeInQueryTree(SuchThatClause stc)
{
    qtPtr->insertSuchThat(stc);
    return true;
}



