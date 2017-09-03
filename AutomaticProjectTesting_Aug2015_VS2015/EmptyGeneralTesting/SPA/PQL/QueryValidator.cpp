#include "QueryValidator.h"

using namespace std;

QueryValidator::QueryValidator()
{
}

QueryValidator::~QueryValidator()
{
}


/******************** Public methods ********************/

bool QueryValidator::isValidQuery(vector<string> inputVector)
{
    for (vector<string>::iterator iter = inputVector.begin(); iter != inputVector.end(); ++iter) {
        string currentLine = *iter;
        if (currentLine == inputVector.back()) {
            if (!isValidSelect(currentLine)) {
                return false;
            }
        }
        else {
            if (!isValidDeclaration(currentLine)) {
                return false;
            }
        }
    }
    
    return true; // && isValidSelect();
}

/*--------------- For UnitTesting ---------------*/
void QueryValidator::stubMethod()
{
}

bool QueryValidator::isValidDeclarationTest(string str)
{
    return isValidDeclaration(str);
}

bool QueryValidator::isValidEntityTest(string str)
{
    return isValidEntity(str);
}

bool QueryValidator::isValidSynonymTest(string str)
{
    return isValidSynonym(str);
}





/******************** Private methods ********************/

/*--------------- Validation of Declaration ---------------*/
//Pre-Cond: Semi-colon has to be removed
bool QueryValidator::isValidDeclaration(string str)
{
    string entity;
    string synonym;
    int numWord = 0;
    int numComma = 0;
    int expectedNumComma = 0;

    string EVERYTHING_EXCEPT_SPACE = "[^[:space:]]+";
    regex exceptSpaceRegex(EVERYTHING_EXCEPT_SPACE);
    sregex_iterator pos(str.cbegin(), str.cend(), exceptSpaceRegex);
    sregex_iterator end;

    int counter = 0;
    for (; pos != end; pos++) {
        string token = pos->str(0);

        if (counter == 0 && isValidEntity(token)) {
            numWord++;
            entity = token;
            counter++;
            continue;
        }
        else if (counter == 0 && !isValidEntity(token)) {
            return false;
        }

        if (token == ",") {
            numComma++;
            counter++;
            continue;
        }
        else if (token.back() == ',') {
            numComma++;
            regex removeCommaRegex("([[:w:]]+),");
            smatch m;
            regex_search(token, m, removeCommaRegex);
            string extracted = m[1].str();
            if (isValidSynonym(extracted)) {
                numWord++;
                synonym = extracted;
            }
            else {
                return false;
            }
        }
        else if (isValidSynonym(token)) {
            numWord++;
            synonym = token;
        }
        else {
            return false;
        }

        if (_synonymBank.find(synonym) == _synonymBank.end()) {
            _synonymBank.insert(synonym);
            stubMethod();   //Call QueryTree.insertVariable(entity, synonym)
        }
        else {
            return false;
        }

        counter++;
    }

    expectedNumComma = numWord - 2;

    return numComma == expectedNumComma;
}

bool QueryValidator::isValidEntity(string str)
{
    string entityRegexString = "(procedure|stmtLst|stmt|assign|call|while|if|variable|constant|prog_line)";
    regex entityRegex(entityRegexString);

    return regex_match(str, entityRegex);
}

bool QueryValidator::isValidSynonym(string str)
{
    string synonymRegexString = "([[:alpha:]]{1})([[:alpha:]|[:digit:]|#]*)";
    regex synonymRegex(synonymRegexString);

    return regex_match(str, synonymRegex);
}

/*--------------- Validation of Select ---------------*/
bool QueryValidator::isValidSelect(string str)
{
    return true;    //stub
}
