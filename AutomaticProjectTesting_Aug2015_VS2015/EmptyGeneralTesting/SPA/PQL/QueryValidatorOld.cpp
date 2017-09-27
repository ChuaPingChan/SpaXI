#include "QueryValidatorOld.h"

using namespace std;

QueryValidatorOld
::QueryValidatorOld()
{
    qtInstance = QueryTree::getInstance();
}

QueryValidatorOld::~QueryValidatorOld()
{
}

/******************** Grammar ********************/
const string QueryValidatorOld::LETTER = "([a-zA-Z])";
const string QueryValidatorOld::DIGIT = "([0-9])";
const string QueryValidatorOld::INTEGER = "(" + DIGIT + "+)";
const string QueryValidatorOld::HASH = "(#)";
const string QueryValidatorOld::UNDERSCORE = "(_)";
const string QueryValidatorOld::IDENT = "(" + LETTER + "(" + LETTER + "|" + DIGIT + "|" + HASH + ")*)";
const string QueryValidatorOld::SYNONYM = IDENT;
const string QueryValidatorOld::STMTREF = "(" + SYNONYM + "|" + UNDERSCORE + "|" + INTEGER + ")";
const string QueryValidatorOld::ENTREF = "(" + SYNONYM + "|" + UNDERSCORE + "|" + "\"" + IDENT + "\"" ")";
const string QueryValidatorOld::NAME = "(" + LETTER + "(" + LETTER + "|" + DIGIT + ")*)";
const string QueryValidatorOld::SPACE_0 = "(\\s*)";
const string QueryValidatorOld::SPACE_1 = "(\\s+)";

/*--------------- Declaration Regex ---------------*/
const string QueryValidatorOld::DESIGN_ENTITY_REGEX = "(procedure|stmtLst|stmt|assign|call|while|if|variable|constant|prog_line)";

/*--------------- Pattern Clause Regex ---------------*/
const string QueryValidatorOld::FACTOR = "(" + NAME + "|" + INTEGER + ")";
const string QueryValidatorOld::EXPRESSION_SPEC = "(" + UNDERSCORE + "|" + UNDERSCORE + "\"" + FACTOR + "\"" + UNDERSCORE + ")";
const string QueryValidatorOld::PATTERN_REGEX = "(" + SPACE_0 + "(pattern)" + SPACE_1 + SYNONYM + SPACE_0 + "[(]" + SPACE_0 + ENTREF + SPACE_0 + "[,]" + SPACE_0 + EXPRESSION_SPEC + SPACE_0 + "[)]" + SPACE_0 + ")";

/*--------------- Relationship Clause Regex ---------------*/
const string QueryValidatorOld::MODIFIES_REGEX = "(" + SPACE_0 + "(Modifies)" + SPACE_0 + "[(]" + SPACE_0 + STMTREF + SPACE_0 + "[,]" + SPACE_0 + ENTREF + SPACE_0 + "[)]" + SPACE_0 + ")";
const string QueryValidatorOld::USES_REGEX = "(" + SPACE_0 + "(Uses)" + SPACE_0 + "[(]" + SPACE_0 + STMTREF + SPACE_0 + "[,]" + SPACE_0 + ENTREF + SPACE_0 + "[)]" + SPACE_0 + ")";
const string QueryValidatorOld::FOLLOWS_REGEX = "(" + SPACE_0 + "(Follows)(\\*)?" + SPACE_0 + "[(]" + SPACE_0 + STMTREF + SPACE_0 + "[,]" + SPACE_0 + STMTREF + SPACE_0 + "[)]" + SPACE_0 + ")";
const string QueryValidatorOld::PARENT_REGEX = "(" + SPACE_0 + "(Parent)(\\*)?" + SPACE_0 + "[(]" + SPACE_0 + STMTREF + SPACE_0 + "[,]" + SPACE_0 + STMTREF + SPACE_0 + "[)]" + SPACE_0 + ")";

/*--------------- Select Regex ---------------*/
const string QueryValidatorOld::SELECT_REGEX = "(Select)" + SPACE_1 + SYNONYM;
const string QueryValidatorOld::RELREF = "(" + MODIFIES_REGEX + "|" + USES_REGEX + "|" + FOLLOWS_REGEX + "|" + PARENT_REGEX + ")";
const string QueryValidatorOld::SUCH_THAT_REGEX = SPACE_0 + "(such)" + SPACE_1 + "(that)" + SPACE_1 + RELREF;
const string QueryValidatorOld::SELECT_OVERALL_REGEX = "^" + SPACE_0 + SELECT_REGEX + SPACE_0 + "(" + SUCH_THAT_REGEX + "|" + PATTERN_REGEX + ")*" + SPACE_0 + "$";

//string relCond = relRef + "(" + andRegex + relRef + ")*";
//string patternCond = patternRegex + "(" + andRegex + patternRegex + ")*";


/*****************
* Public methods *
*****************/

bool QueryValidatorOld::isValidQuery(string query)
{

    vector<string> inputVector = tokenize(query);

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


/******************
* Private methods *
******************/

/*--------------- Split initial query ---------------*/

//split query using ';' as delimiter
vector<string> QueryValidatorOld::tokenize(string query)
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

string QueryValidatorOld::removeAllSpaces(string str)
{
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

/*--------------- Get string between two delimiters ---------------*/
string QueryValidatorOld::getBetweenTwoStrings(const string &str, const string &firstDelim, const string &secondDelim)
{
    unsigned firstDelimPos = str.find(firstDelim);
    unsigned middleDelimPos = firstDelimPos + firstDelim.length();
    unsigned lastDelimPos = str.find(secondDelim);

    return str.substr(middleDelimPos,
        lastDelimPos - middleDelimPos);
}

/*--------------- Check if argument is in a clause ---------------*/

bool QueryValidatorOld::isArgumentInClause(string arg, vector<string> clause)
{
    if (find(clause.begin(), clause.end(), arg) != clause.end())
        return true;
    else
        return false;
}

/*--------------- Check if string is an integer ---------------*/
bool QueryValidatorOld::isIntegerRegexCheck(string arg)
{
    regex checkInt = regex(INTEGER);
    return regex_match(arg, checkInt);
}

/*--------------- Validation of Declaration ---------------*/
//Pre-Cond: Semi-colon has to be removed
bool QueryValidatorOld::isValidDeclaration(string str)
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
            if (entity == synonym)
                return false;
            qtInstance->insertVariable(entity, synonym);
        }
        else {
            return false;
        }

        counter++;
    }

    expectedNumComma = numWord - 2;

    return numComma == expectedNumComma;
}

bool QueryValidatorOld::isValidEntity(string str)
{
    regex entityRegex(DESIGN_ENTITY_REGEX);
    return regex_match(str, entityRegex);
}

bool QueryValidatorOld::isValidSynonym(string str)
{
    regex synonymRegex(SYNONYM);
    return regex_match(str, synonymRegex);
}

/*--------------- Validation of Select --------------*/
bool QueryValidatorOld::isValidSelect(string str)
{
    if (isValidSelectOverallRegex(str) == false)
        return false;

    /* Extracting the Select portion */
    regex selectRegex(SELECT_REGEX);
    sregex_iterator sel(str.begin(), str.end(), selectRegex);
    sregex_iterator sel_end;

    for (; sel != sel_end; sel++)
    {
        string current = sel->str(0);
        if (!isValidSelectBeginning(current))
            return false;
    }

    /* Extracting the clauses portion */
    regex clauseRegex(RELREF + "|" + PATTERN_REGEX);
    sregex_iterator it(str.cbegin(), str.cend(), clauseRegex);
    sregex_iterator it_end;

    for (; it != it_end; it++)
    {
        string currentClause = it->str(0);

        if (currentClause.find("Follows") != std::string::npos)
        {
            if (!isValidFollows(currentClause))
            {
                return false;
            }
        }
        else if (currentClause.find("Parent") != std::string::npos)
        {
            if (!isValidParent(currentClause))
            {
                return false;
            }
        }
        else if (currentClause.find("Uses") != std::string::npos)
        {
            if (!isValidUses(currentClause))
            {
                return false;
            }
        }
        else if (currentClause.find("Modifies") != std::string::npos)
        {
            if (!isValidModifies(currentClause))
            {
                return false;
            }
        }
        else if (currentClause.find("pattern") != std::string::npos)
        {
            if (!isValidPattern(currentClause))
            {
                return false;
            }
        }
        else
        {
            return false;
        }

    }

    return true;  //stub
}

bool QueryValidatorOld::isValidSelectBeginning(string str)
{
    size_t f = str.find("Select");
    str.replace(f, std::string("Select").length(), "");

    /* Extracting the synonym */
    regex synonymRegex(SYNONYM);
    sregex_iterator it(str.begin(), str.end(), synonymRegex);
    sregex_iterator it_end;
    string current;
    for (; it != it_end; it++)
    {
        current = it->str(0);
        if (!qtInstance->varExists(current))
            return false;
    }

    array<string, 2> result;
    if (isArgumentInClause(current, qtInstance->getAssigns()))
    {
        result[0] = "assign";
        result[1] = current;
    }
    else  if (isArgumentInClause(current, qtInstance->getWhiles()))
    {
        result[0] = "while";
        result[1] = current;
    }
    else  if (isArgumentInClause(current, qtInstance->getStmts()))
    {
        result[0] = "stmt";
        result[1] = current;
    }
    else  if (isArgumentInClause(current, qtInstance->getVars()))
    {
        result[0] = "var";
        result[1] = current;
    }
    else  if (isArgumentInClause(current, qtInstance->getProgLines()))
    {
        result[0] = "stmt";
        result[1] = current;
    }
    else  if (isArgumentInClause(current, qtInstance->getConsts()))
    {
        result[0] = "const";
        result[1] = current;
    }

    qtInstance->insertSelect(result);
    return true;
}

bool QueryValidatorOld::isValidSelectOverallRegex(string str)
{
    regex overallSelectRegexCheck(SELECT_OVERALL_REGEX);
    return regex_match(str, overallSelectRegexCheck);
}

/*--------------- Validation of Such That clauses ---------------*/
bool QueryValidatorOld::isValidModifiesRegex(string str)
{
    regex modifiesRegexCheck(MODIFIES_REGEX);
    return regex_match(str, modifiesRegexCheck);
}

bool QueryValidatorOld::isValidUsesRegex(string str)
{
    regex usesRegexCheck(USES_REGEX);
    return regex_match(str, usesRegexCheck);
}

bool QueryValidatorOld::isValidFollowsRegex(string str)
{
    regex followsRegexCheck(FOLLOWS_REGEX);
    return regex_match(str, followsRegexCheck);
}

bool QueryValidatorOld::isValidParentRegex(string str)
{
    regex parentRegexCheck(PARENT_REGEX);
    return regex_match(str, parentRegexCheck);
}

//PRE-COND: Modifies(a,b)
bool QueryValidatorOld::isValidModifies(string str)
{
    if (!isValidModifiesRegex(str))
        return false;

    str = removeAllSpaces(str);
    string arg1 = getBetweenTwoStrings(str, "Modifies(", ",");
    string arg2 = getBetweenTwoStrings(str, ",", ")");
    array<string, 4> result;

    if (qtInstance->varExists(arg2) && !isArgumentInClause(arg2, qtInstance->getVars())) //arg2 is a synonym and is NOT a variable
        return false;

    //if arg1 exists in synonym bank or is statement number, then check for arg2 and store in appropriate data type
    if (isArgumentInClause(arg1, qtInstance->getAssigns()) || isArgumentInClause(arg1, qtInstance->getStmts()) || isArgumentInClause(arg1, qtInstance->getWhiles()) || isIntegerRegexCheck(arg1))
    {
        if (isArgumentInClause(arg2, qtInstance->getVars())) { //if arg2 is a variable synonym
            result[2] = "var";
            result[3] = arg2;

            if (isArgumentInClause(arg1, qtInstance->getAssigns()))
            {
                result[0] = "assign";
                result[1] = arg1;

                //store in data type for assignment synonym
            }

            if (isArgumentInClause(arg1, qtInstance->getStmts()))
            {
                result[0] = "stmt";
                result[1] = arg1;

                //store in data type for statement synonym
            }

            if (isArgumentInClause(arg1, qtInstance->getWhiles()))
            {
                result[0] = "while";
                result[1] = arg1;
                //store in data type for whiles synonym
            }

            if (isIntegerRegexCheck(arg1))
            {
                result[0] = "int";
                result[1] = arg1;
                //store in data type for statement number 
            }
            qtInstance->insertModifies(result); //store clause in query tree
            return true;
        }

        else //arg2 is not in synonym bank but is a valid variable

        {
            if (arg2 == "_") {
                result[2] = arg2;
                result[3] = "";
            }
            else
            {
                result[2] = "ident";
                result[3] = arg2;
            }

            if (isArgumentInClause(arg1, qtInstance->getAssigns()))
            {
                result[0] = "assign";
                result[1] = arg1;

                //store in data type for assignment synonym
            }

            if (isArgumentInClause(arg1, qtInstance->getStmts()))
            {
                result[0] = "stmt";
                result[1] = arg1;

                //store in data type for statement synonym
            }

            if (isArgumentInClause(arg1, qtInstance->getWhiles()))
            {
                result[0] = "while";
                result[1] = arg1;
                //store in data type for whiles synonym
            }

            if (isIntegerRegexCheck(arg1))
            {
                result[0] = "int";
                result[1] = arg1;
                //store in data type for statement number 
            }
            qtInstance->insertModifies(result);
            return true;
        }
    }

    return false;

}

bool QueryValidatorOld::isValidUses(string str)
{
    if (!isValidUsesRegex(str))
        return false;
    str = removeAllSpaces(str);
    string arg1 = getBetweenTwoStrings(str, "Uses(", ",");
    string arg2 = getBetweenTwoStrings(str, ",", ")");
    array<string, 4> result;

    if (qtInstance->varExists(arg2) && !isArgumentInClause(arg2, qtInstance->getVars())) //arg2 is a synonym and is NOT a variable
        return false;

    //if arg1 exists in synonym bank or is statement number, then check for arg2 and store in appropriate data type
    if (isArgumentInClause(arg1, qtInstance->getAssigns()) || isArgumentInClause(arg1, qtInstance->getStmts()) || isArgumentInClause(arg1, qtInstance->getWhiles()) || isIntegerRegexCheck(arg1))
    {
        if (isArgumentInClause(arg2, qtInstance->getVars())) { //if arg2 is a variable synonym
            result[2] = "var";
            result[3] = arg2;

            if (isArgumentInClause(arg1, qtInstance->getAssigns()))
            {
                result[0] = "assign";
                result[1] = arg1;

                //store in data type for assignment synonym
            }

            if (isArgumentInClause(arg1, qtInstance->getStmts()))
            {
                result[0] = "stmt";
                result[1] = arg1;

                //store in data type for statement synonym
            }

            if (isArgumentInClause(arg1, qtInstance->getWhiles()))
            {
                result[0] = "while";
                result[1] = arg1;
                //store in data type for whiles synonym
            }

            if (isIntegerRegexCheck(arg1))
            {
                result[0] = "int";
                result[1] = arg1;
                //store in data type for statement number 
            }
            qtInstance->insertUses(result);
            return true;
        }

        else //arg2 is not in synonym bank but is a valid variable

        {
            if (arg2 == "_") {
                result[2] = arg2;
                result[3] = "";
            }
            else
            {
                result[2] = "ident";
                result[3] = arg2;
            }

            if (isArgumentInClause(arg1, qtInstance->getAssigns()))
            {
                result[0] = "assign";
                result[1] = arg1;

                //store in data type for assignment synonym
            }

            if (isArgumentInClause(arg1, qtInstance->getStmts()))
            {
                result[0] = "stmt";
                result[1] = arg1;

                //store in data type for statement synonym
            }

            if (isArgumentInClause(arg1, qtInstance->getWhiles()))
            {
                result[0] = "while";
                result[1] = arg1;
                //store in data type for whiles synonym
            }

            if (isIntegerRegexCheck(arg1))
            {
                result[0] = "int";
                result[1] = arg1;
                //store in data type for statement number 
            }
            qtInstance->insertUses(result);
            return true;
        }
    }

    return false;
}

//PRE-COND: arg1: stmt, assign, while, if, prog_line
bool QueryValidatorOld::isValidFollows(string str)
{
    if (!isValidFollowsRegex(str))
        return false;

    str = removeAllSpaces(str);
    string arg1, arg2;
    array<string, 4> result;

    if (regex_search(str, regex("\\*"))) { //contains *, means it is Follows*
        arg1 = getBetweenTwoStrings(str, "Follows*(", ",");
        arg2 = getBetweenTwoStrings(str, ",", ")");

        if (arg1 == arg2 && arg1 != "_")  //arg1 cannot be the same as arg2. 
            return false;

        // if both args are int, arg1 must be < than arg2
        if (isIntegerRegexCheck(arg1) && isIntegerRegexCheck(arg2))
        {
            int first = stoi(arg1);
            int second = stoi(arg2);
            if (first >= second)
            {
                return false;
            }
        }

        if (isIntegerRegexCheck(arg1)) {
            result[0] = "int";
            result[1] = arg1;
        }
        else if (isArgumentInClause(arg1, qtInstance->getStmts())) {
            result[0] = "stmt";
            result[1] = arg1;
        }
        else if (isArgumentInClause(arg1, qtInstance->getAssigns())) {
            result[0] = "assign";
            result[1] = arg1;
        }
        else if (isArgumentInClause(arg1, qtInstance->getWhiles())) {
            result[0] = "while";
            result[1] = arg1;
        }
        else if (arg1 == "_") {
            result[0] = arg1;
            result[1] = "";
        }
        else {
            return false;
        }

        if (isIntegerRegexCheck(arg2)) {
            result[2] = "int";
            result[3] = arg2;
        }
        else if (isArgumentInClause(arg2, qtInstance->getStmts())) {
            result[2] = "stmt";
            result[3] = arg2;
        }
        else if (isArgumentInClause(arg2, qtInstance->getAssigns())) {
            result[2] = "assign";
            result[3] = arg2;
        }
        else if (isArgumentInClause(arg2, qtInstance->getWhiles())) {
            result[2] = "while";
            result[3] = arg2;
        }
        else if (arg2 == "_") {
            result[2] = arg2;
            result[3] = "";
        }

        else {
            return false;
        }
        qtInstance->insertFollowsStar(result);
        return true;

    }
    else {

        arg1 = getBetweenTwoStrings(str, "Follows(", ",");
        arg2 = getBetweenTwoStrings(str, ",", ")");

        if (arg1 == arg2 && arg1 != "_") //arg1 cannot be the same as arg2
            return false;

        // if both args are int, arg1 must be < than arg2
        if (isIntegerRegexCheck(arg1) && isIntegerRegexCheck(arg2))
        {
            int first = stoi(arg1);
            int second = stoi(arg2);
            if (first >= second)
            {
                return false;
            }
        }

        if (isIntegerRegexCheck(arg1)) {
            result[0] = "int";
            result[1] = arg1;
        }
        else if (isArgumentInClause(arg1, qtInstance->getStmts())) {
            result[0] = "stmt";
            result[1] = arg1;
        }
        else if (isArgumentInClause(arg1, qtInstance->getAssigns())) {
            result[0] = "assign";
            result[1] = arg1;
        }
        else if (isArgumentInClause(arg1, qtInstance->getWhiles())) {
            result[0] = "while";
            result[1] = arg1;
        }
        else if (arg1 == "_") {
            result[0] = arg1;
            result[1] = "";
        }
        else {
            return false;
        }

        if (isIntegerRegexCheck(arg2)) {
            result[2] = "int";
            result[3] = arg2;
        }
        else if (isArgumentInClause(arg2, qtInstance->getStmts())) {
            result[2] = "stmt";
            result[3] = arg2;
        }
        else if (isArgumentInClause(arg2, qtInstance->getAssigns())) {
            result[2] = "assign";
            result[3] = arg2;
        }
        else if (isArgumentInClause(arg2, qtInstance->getWhiles())) {
            result[2] = "while";
            result[3] = arg2;
        }
        else if (arg2 == "_") {
            result[2] = arg2;
            result[3] = "";
        }
        else {
            return false;
        }
        qtInstance->insertFollows(result);
        return true;
        //Store string array into query tree in Follows()
    }
}

bool QueryValidatorOld::isValidParent(string str)
{
    if (!isValidParentRegex(str))
        return false;

    str = removeAllSpaces(str);
    string arg1, arg2;
    array<string, 4> result;

    if (regex_search(str, regex("\\*"))) { //contains *, means it is Parent*
        arg1 = getBetweenTwoStrings(str, "Parent*(", ",");
        arg2 = getBetweenTwoStrings(str, ",", ")");

        if (arg1 == arg2 && arg1 != "_") //arg1 cannot be the same as arg2
            return false;

        // if both args are int, arg1 must be < than arg2
        if (isIntegerRegexCheck(arg1) && isIntegerRegexCheck(arg2))
        {
            int first = stoi(arg1);
            int second = stoi(arg2);
            if (first >= second)
            {
                return false;
            }
        }

        if (isIntegerRegexCheck(arg1)) {
            result[0] = "int";
            result[1] = arg1;
        }
        else if (isArgumentInClause(arg1, qtInstance->getStmts())) {
            result[0] = "stmt";
            result[1] = arg1;
        }
        else if (isArgumentInClause(arg1, qtInstance->getWhiles())) {
            result[0] = "while";
            result[1] = arg1;
        }
        else if (arg1 == "_") {
            result[0] = arg1;
            result[1] = "";
        }
        else {
            return false;
        }

        if (isIntegerRegexCheck(arg2)) {
            result[2] = "int";
            result[3] = arg2;
        }
        else if (isArgumentInClause(arg2, qtInstance->getStmts())) {
            result[2] = "stmt";
            result[3] = arg2;
        }
        else if (isArgumentInClause(arg2, qtInstance->getWhiles())) {
            result[2] = "while";
            result[3] = arg2;
        }
        else if (isArgumentInClause(arg2, qtInstance->getAssigns())) {
            result[2] = "assign";
            result[3] = arg2;
        }
        else if (arg2 == "_") {
            result[2] = arg2;
            result[3] = "";
        }

        else {
            return false;
        }
        qtInstance->insertParentStar(result);
        return true;

    }
    else {

        arg1 = getBetweenTwoStrings(str, "Parent(", ",");
        arg2 = getBetweenTwoStrings(str, ",", ")");

        if (arg1 == arg2 && arg1 != "_") //arg1 cannot be the same as arg2
            return false;

        // if both args are int, arg1 must be < than arg2
        if (isIntegerRegexCheck(arg1) && isIntegerRegexCheck(arg2))
        {
            int first = stoi(arg1);
            int second = stoi(arg2);
            if (first >= second)
            {
                return false;
            }
        }

        if (isIntegerRegexCheck(arg1)) {
            result[0] = "int";
            result[1] = arg1;
        }
        else if (isArgumentInClause(arg1, qtInstance->getStmts())) {
            result[0] = "stmt";
            result[1] = arg1;
        }
        else if (isArgumentInClause(arg1, qtInstance->getWhiles())) {
            result[0] = "while";
            result[1] = arg1;
        }
        else if (arg1 == "_") {
            result[0] = arg1;
            result[1] = "";
        }
        else {
            return false;
        }

        if (isIntegerRegexCheck(arg2)) {
            result[2] = "int";
            result[3] = arg2;
        }
        else if (isArgumentInClause(arg2, qtInstance->getStmts())) {
            result[2] = "stmt";
            result[3] = arg2;
        }
        else if (isArgumentInClause(arg2, qtInstance->getWhiles())) {
            result[2] = "while";
            result[3] = arg2;
        }
        else if (isArgumentInClause(arg2, qtInstance->getAssigns())) {
            result[2] = "assign";
            result[3] = arg2;
        }
        else if (arg2 == "_") {
            result[2] = arg2;
            result[3] = "";
        }
        else {
            return false;
        }
        qtInstance->insertParent(result);
        return true;
        //Store string array into query tree in Parent()
    }
}


/*--------------- Validation of Pattern ---------------*/
bool QueryValidatorOld::isValidPatternRegex(string str)
{
    regex patternRegexCheck(PATTERN_REGEX);
    return regex_match(str, patternRegexCheck);
}

//PRE-COND: patternarg1(arg2,arg3) arg1 = assignment synonym, arg2 = variable synonym/"entRef", arg3 = "EXPRESSION"
bool QueryValidatorOld::isValidPattern(string str)
{
    if (!isValidPatternRegex(str))
        return false;

    str = removeAllSpaces(str);
    string arg1 = getBetweenTwoStrings(str, "pattern", "(");
    string arg2 = getBetweenTwoStrings(str, "(", ",");
    string arg3 = getBetweenTwoStrings(str, ",", ")");
    array<string, 6> result;

    if (qtInstance->varExists(arg3)) //check if argument 3 is a synonym; not allowed.
        return false;

    if (qtInstance->varExists(arg2) && !isArgumentInClause(arg2, qtInstance->getVars())) //check if argument 2 is declared as a synonym other than a variable; not allowed.
        return false;

    if (arg3 == "_")
    {
        result[4] = arg3;
        result[5] = "";
    }
    else
    {
        result[4] = "ident";
        result[5] = arg3;
    }

    if (isArgumentInClause(arg1, qtInstance->getAssigns()))
    {
        result[0] = "assign";
        result[1] = arg1;
        if (isArgumentInClause(arg2, qtInstance->getVars())) {
            //store in appropriate type with VARIABLE synonym
            result[2] = "var";
            result[3] = arg2;
            qtInstance->insertPattern(result);
            return true;
        }
        else {
            //store in appropriate data type without VARIABLE synonym
            if (arg2 == "_")
            {
                result[2] = arg2;
                result[3] = "";
            }
            else
            {
                result[2] = "ident";
                result[3] = arg2;
            }

            qtInstance->insertPattern(result);
            return true;
        }
    }

    else

        return false;

}
