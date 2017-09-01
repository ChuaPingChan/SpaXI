#include "QueryValidator.h"

using namespace std;

QueryValidator::QueryValidator()
{
}


QueryValidator::~QueryValidator()
{
}

//Public methods
bool QueryValidator::isValidQuery()
{
    return false;
}

//For Testing Private Methods
bool QueryValidator::isValidEntityTest(string input)
{
    return isValidEnitity(input);
}

bool QueryValidator::isValidSynonymTest(string input)
{
    return isValidSynonym(input);
}


//Private methods

vector<string> QueryValidator::getQueryToBeValidated()
{
    return vector<string>();
}

//Validation of Declaration
bool QueryValidator::isValidDeclaration()
{
    return false;
}

bool QueryValidator::isValidEnitity(string input)
{
    string entityRegexString = "(procedure|stmtLst|stmt|assign|call|while|if|variable|constant|prog_line)";
    regex entityRegex(entityRegexString);

    return regex_match(input, entityRegex);
}

bool QueryValidator::isValidSynonym(string input)
{
    string synonymRegexString = "([[:alpha:]]{1})([[:alpha:]|[:digit:]|#]*)";
    regex synonymRegex(synonymRegexString);

    return regex_match(input, synonymRegex);
}


//Validation of Select
bool QueryValidator::isValidSelect()
{
    return false;
}