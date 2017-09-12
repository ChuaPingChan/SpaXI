#include "QueryValidator.h"

using namespace std;

QueryValidator::QueryValidator()
{
}

QueryValidator::~QueryValidator()
{
}

/******************** Grammar ********************/
const string LETTER = "([a-zA-Z])";
const string DIGIT = "([0-9])";
const string INTEGER = "(" + DIGIT + "+)";
const string HASH = "(#)";
const string UNDERSCORE = "(_)";
const string IDENT = "(" + LETTER + "(" + LETTER + "|" + DIGIT + "|" + HASH + ")*)";
const string SYNONYM = IDENT;
const string STMTREF = "(" + SYNONYM + "|" + UNDERSCORE + "|" + INTEGER + ")";
const string ENTREF = "(" + SYNONYM + "|" + UNDERSCORE + "|" + "\"" + IDENT + "\"" ")";
const string NAME = "(" + LETTER + "(" + LETTER + "|" + DIGIT + ")*)";
const string SPACE_0 = "(\\s*)";
const string SPACE_1 = "(\\s+)";

/*--------------- Declaration Regex ---------------*/
const string DESIGN_ENTITY_REGEX = "(procedure|stmtLst|stmt|assign|call|while|if|variable|constant|prog_line)";

/*--------------- Pattern Clause Regex ---------------*/
const string FACTOR = "(" + NAME + "|" + INTEGER + ")";
const string EXPRESSION_SPEC = "(" + UNDERSCORE + "|" + UNDERSCORE + "\"" + FACTOR + "\"" + UNDERSCORE + ")";
const string PATTERN_REGEX = "(" + SPACE_0 + "(pattern)" + SPACE_1 + SYNONYM + SPACE_0 + "[(]" + SPACE_0 + ENTREF + SPACE_0 + "[,]" + SPACE_0 + EXPRESSION_SPEC + SPACE_0 + "[)]" + SPACE_0 + ")";

/*--------------- Relationship Clause Regex ---------------*/
const string MODIFIES_REGEX = "(" + SPACE_0 + "(Modifies)" + SPACE_0 + "[(]" + SPACE_0 + STMTREF + SPACE_0 + "[,]" + SPACE_0 + ENTREF + SPACE_0 + "[)]" + SPACE_0 + ")";
const string USES_REGEX = "(" + SPACE_0 + "(Uses)" + SPACE_0 + "[(]" + SPACE_0 + STMTREF + SPACE_0 + "[,]" + SPACE_0 + ENTREF + SPACE_0 + "[)]" + SPACE_0 + ")";
const string FOLLOWS_REGEX = "(" + SPACE_0 + "(Follows)(\\*)?" + SPACE_0 + "[(]" + SPACE_0 + STMTREF + SPACE_0 + "[,]" + SPACE_0 + ENTREF + SPACE_0 + "[)]" + SPACE_0 + ")";
const string PARENT_REGEX = "(" + SPACE_0 + "(Parent)(\\*)?" + SPACE_0 + "[(]" + SPACE_0 + STMTREF + SPACE_0 + "[,]" + SPACE_0 + ENTREF + SPACE_0 + "[)]" + SPACE_0 + ")";

/*--------------- Select Regex ---------------*/
const string SELECT_REGEX = "(Select)" + SPACE_1 + SYNONYM;
const string RELREF = "(" + MODIFIES_REGEX + "|" + USES_REGEX + "|" + FOLLOWS_REGEX + "|" + PARENT_REGEX + ")";
const string SUCH_THAT_REGEX = SPACE_0 + "(such)" + SPACE_1 + "(that)" + SPACE_1 + RELREF;
const string SELECT_OVERALL_REGEX = "^" + SPACE_0 + SELECT_REGEX + SPACE_0 + "(" + SUCH_THAT_REGEX + "|" + PATTERN_REGEX + ")*" + SPACE_0 + "$";

//string relCond = relRef + "(" + andRegex + relRef + ")*";
//string patternCond = patternRegex + "(" + andRegex + patternRegex + ")*";


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

string QueryValidator::removeAllSpacesTest(string str)
{
	return removeAllSpaces(str);
}

/*--------------- Grammar Regex Test---------------*/
bool QueryValidator::isValidLetterTest(string str)
{
    regex letterRegexCheck(LETTER);
    return regex_match(str, letterRegexCheck);
}

bool QueryValidator::isValidIntegerTest(string str)
{
    regex integerRegexCheck(INTEGER);
    return regex_match(str, integerRegexCheck);
}

bool QueryValidator::isValidSynonymTest(string str)
{
    return isValidSynonym(str);
}

bool QueryValidator::isValidStmtRefTest(string str)
{
    regex stmtRefRegexCheck(STMTREF);
    return regex_match(str, stmtRefRegexCheck);
}

bool QueryValidator::isValidEntRefTest(string str)
{
    regex entRefRegexCheck(ENTREF);
    return regex_match(str, entRefRegexCheck);
}

bool QueryValidator::isValidNameTest(string str)
{
    regex nameRegexCheck(NAME);
    return regex_match(str, nameRegexCheck);
}

/*--------------- Splitting Query Test---------------*/

vector<string> QueryValidator::initialSplitTest(string query)
{
    return initialSplit(query);
}

/*--------------- Declaration Test---------------*/
bool QueryValidator::isValidEntityTest(string str)
{
    return isValidEntity(str);
}

bool QueryValidator::isValidDeclarationTest(string str)
{
    return isValidDeclaration(str);
}

void QueryValidator::stubMethod()
{
}

/*--------------- Pattern Test---------------*/
bool QueryValidator::isValidFactorTest(string str)
{
    regex factorRegexCheck(FACTOR);
    return regex_match(str, factorRegexCheck);
}

bool QueryValidator::isValidExpressionSpecTest(string str)
{
    regex expressionSpecRegexCheck(EXPRESSION_SPEC);
    return regex_match(str, expressionSpecRegexCheck);
}

bool QueryValidator::isValidPatternRegexTest(string str)
{
    return isValidPatternRegex(str);
}

bool QueryValidator::isValidPatternTest(string str)
{
    return isValidPattern(str);
}


/*--------------- Relationship Test---------------*/
bool QueryValidator::isValidModifiesRegexTest(string str)
{
    return isValidModifiesRegex(str);
}

bool QueryValidator::isValidUsesRegexTest(string str)
{
    return isValidUsesRegex(str);
}

bool QueryValidator::isValidFollowsRegexTest(string str)
{
    return isValidFollowsRegex(str);
}

bool QueryValidator::isValidParentRegexTest(string str)
{
    return isValidParentRegex(str);
}

bool QueryValidator::isValidModifiesTest(string str)
{
    return isValidModifies(str);
}

bool QueryValidator::isValidUsesTest(string str)
{
    return isValidUses(str);
}

bool QueryValidator::isValidFollowsTest(string str)
{
    return isValidFollows(str);
}

bool QueryValidator::isValidParentTest(string str)
{
    return isValidParent(str);
}

/*--------------- Select Test---------------*/
bool QueryValidator::isValidSelectTest(string str)
{
    return isValidSelect(str);
}

bool QueryValidator::isValidSelectOverallRegexTest(string str)
{
    return isValidSelectOverallRegex(str);
}



/******************** Private methods ********************/

/*--------------- Split initial query ---------------*/

//split query using ';' as delimiter
vector<string> QueryValidator::initialSplit(string query)
{
    char delimiter = ';';
    stringstream ss(query);
    vector<string> tokens;
    string arguments;

    while (getline(ss, arguments, delimiter)) {
        tokens.push_back(arguments);
    }
    return tokens;
}

/*--------------- Remove all spaces ---------------*/

string QueryValidator::removeAllSpaces(string str) 
{ 
	str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
	return str;
}

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
    regex entityRegex(DESIGN_ENTITY_REGEX);
    return regex_match(str, entityRegex);
}

bool QueryValidator::isValidSynonym(string str)
{
    regex synonymRegex(SYNONYM);
    return regex_match(str, synonymRegex);
}

/*--------------- Validation of Select --------------*/
bool QueryValidator::isValidSelect(string str)
{
    //TODO: split str into the different clauses
    //TODO: Check each syntactic validity of the cluases
    //TODO: This is true when all the clauses are true

	regex clauseRegex(FOLLOWS_REGEX + "|" + PARENT_REGEX + "|" + USES_REGEX + "|" + MODIFIES_REGEX + "|" + PATTERN_REGEX, regex_constants::icase);
	sregex_iterator it(str.cbegin(), str.cend(), clauseRegex);
	sregex_iterator it_end;

	for (; it != it_end; it++)
	{
		string currentClause = it->str(0);
		bool isCurrentClauseValid;

		if (currentClause.find("Follows") != std::string::npos) 
		{
			isCurrentClauseValid = isValidFollows(currentClause);
			if (!isCurrentClauseValid)
			{
				return false;
			}
		}
		else if (currentClause.find("Parent") != std::string::npos)
		{
			isCurrentClauseValid = isValidParent(currentClause);
			if (!isCurrentClauseValid)
			{
				return false;
			}
		}
		else if (currentClause.find("Uses") != std::string::npos)
		{
			isCurrentClauseValid = isValidUses(currentClause);
			if (!isCurrentClauseValid)
			{
				return false;
			}
		}
		else if (currentClause.find("Modifies") != std::string::npos)
		{
			isCurrentClauseValid = isValidModifies(currentClause);
			if (!isCurrentClauseValid)
			{
				return false;
			}
		}
		else if (currentClause.find("pattern") != std::string::npos)
		{
			isCurrentClauseValid = isValidPattern(currentClause);
			if (!isCurrentClauseValid)
			{
				return false;
			}
		}
		else
		{
			return false;
		}

		return true;

	}
		
    return true;  //stub
}

bool QueryValidator::isValidClause(string str)
{
	return false;
}

//PRE-COND: Modifies(b,c) with any spaces
bool QueryValidator::isValidModifies(string str)
{
    return false;   //stub
                    //TODO: This is to check the overall validity, not just syntax
}

bool QueryValidator::isValidUses(string str)
{
    return false;   //stub
                    //TODO: This is to check the overall validity, not just syntax
}

bool QueryValidator::isValidFollows(string str)
{
    return false;   //stub
                    //TODO: This is to check the overall validity, not just syntax
}

bool QueryValidator::isValidParent(string str)
{
    return false;   //stub
                    //TODO: This is to check the overall validity, not just syntax
}

bool QueryValidator::isValidPattern(string str)
{
    return false;   //stub
                    //TODO: This is to check the overall validity, not just syntax
}

bool QueryValidator::isValidSelectOverallRegex(string str)
{
    regex overallSelectRegexCheck(SELECT_OVERALL_REGEX);
    return regex_match(str, overallSelectRegexCheck);
}

bool QueryValidator::isValidModifiesRegex(string str)
{
    regex modifiesRegexCheck(MODIFIES_REGEX);
    return regex_match(str, modifiesRegexCheck);
}

bool QueryValidator::isValidUsesRegex(string str)
{
    regex usesRegexCheck(USES_REGEX);
    return regex_match(str, usesRegexCheck);
}

bool QueryValidator::isValidFollowsRegex(string str)
{
    regex followsRegexCheck(FOLLOWS_REGEX);
    return regex_match(str, followsRegexCheck);
}

bool QueryValidator::isValidParentRegex(string str)
{
    regex parentRegexCheck(PARENT_REGEX);
    return regex_match(str, parentRegexCheck);
}

bool QueryValidator::isValidPatternRegex(string str)
{
    regex patternRegexCheck(PATTERN_REGEX);
    return regex_match(str, patternRegexCheck);
}
