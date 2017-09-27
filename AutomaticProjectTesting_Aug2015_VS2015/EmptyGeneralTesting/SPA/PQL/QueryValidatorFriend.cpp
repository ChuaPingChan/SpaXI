#include "QueryValidatorFriend.h"

QueryValidatorFriend::QueryValidatorFriend() {}
QueryValidatorFriend::~QueryValidatorFriend() {}

/*--------------- Validation of Grammar Regex ---------------*/
bool QueryValidatorFriend::isValidLetter(string str) {
    regex letterRegexCheck(QueryValidatorOld::LETTER);
    return regex_match(str, letterRegexCheck);
}

bool QueryValidatorFriend::isValidInteger(string str) {
    regex integerRegexCheck(QueryValidatorOld::INTEGER);
    return regex_match(str, integerRegexCheck);
}

bool QueryValidatorFriend::isValidSynonym(string str) {
    return qv.isValidSynonym(str);
}

bool QueryValidatorFriend::isValidStmtRef(string str) {
    regex stmtRefRegexCheck(QueryValidatorOld::STMTREF);
    return regex_match(str, stmtRefRegexCheck);
}

bool QueryValidatorFriend::isValidEntRef(string str) {
    regex entRefRegexCheck(QueryValidatorOld::ENTREF);
    return regex_match(str, entRefRegexCheck);
}

bool QueryValidatorFriend::isValidName(string str) {
    regex nameRegexCheck(QueryValidatorOld::NAME);
    return regex_match(str, nameRegexCheck);
}

/*--------------- Splitting Query ---------------*/
vector<string> QueryValidatorFriend::tokenize(string query) {
    return qv.tokenize(query);
}

/*--------------- Remove all spaces ---------------*/
string QueryValidatorFriend::removeAllSpaces(string str) {
    return qv.removeAllSpaces(str);
}

/*--------------- Get string between two delimiters ---------------*/
string QueryValidatorFriend::getBetweenTwoStrings(const string & str, const string & firstDelim, const string & secondDelim) {
    return qv.getBetweenTwoStrings(str, firstDelim, secondDelim);
}

/*--------------- Check if argument is in a clause ---------------*/
bool QueryValidatorFriend::isArgumentInClause(string arg, vector<string> clause) {
    return qv.isArgumentInClause(arg, clause);
}

/*--------------- Validation of Declaration ---------------*/
bool QueryValidatorFriend::isValidDeclaration(string str) {
    return qv.isValidDeclaration(str);
}

bool QueryValidatorFriend::isValidEntity(string str) {
    return qv.isValidEntity(str);
}

/*--------------- Validation of Select ---------------*/
bool QueryValidatorFriend::isValidSelect(string str) {      //TODO: write unit test for this
    return qv.isValidSelect(str);
}

bool QueryValidatorFriend::isValidSelectOverallRegex(string str) {
    return qv.isValidSelectOverallRegex(str);
}

/*--------------- Validation of Such That clauses ---------------*/
bool QueryValidatorFriend::isValidModifiesRegex(string str) {
    return qv.isValidModifiesRegex(str);
}

bool QueryValidatorFriend::isValidUsesRegex(string str) {
    return qv.isValidUsesRegex(str);
}

bool QueryValidatorFriend::isValidFollowsRegex(string str) {
    return qv.isValidFollowsRegex(str);
}

bool QueryValidatorFriend::isValidParentRegex(string str) {
    return qv.isValidParentRegex(str);
}

bool QueryValidatorFriend::isValidModifies(string str) {
    return qv.isValidModifies(str);
}

bool QueryValidatorFriend::isValidUses(string str) {
    return qv.isValidUses(str);
}

bool QueryValidatorFriend::isValidFollows(string str) {
    return qv.isValidFollows(str);
}

bool QueryValidatorFriend::isValidParent(string str) {
    return qv.isValidParent(str);
}

/*--------------- Validation of Pattern ---------------*/
bool QueryValidatorFriend::isValidPatternRegex(string str) {
    return qv.isValidPatternRegex(str);
}

bool QueryValidatorFriend::isValidFactor(string str) {
    regex factorRegexCheck(QueryValidatorOld::FACTOR);
    return regex_match(str, factorRegexCheck);
}

bool QueryValidatorFriend::isValidExpressionSpec(string str) {
    regex expressionSpecRegexCheck(QueryValidatorOld::EXPRESSION_SPEC);
    return regex_match(str, expressionSpecRegexCheck);
}

bool QueryValidatorFriend::isValidPattern(string str) {
    return qv.isValidPattern(str);
}

/*--------------- Insert into QueryTree ---------------*/
void QueryValidatorFriend::insertSynonymIntoQueryTree(string type1, string arg1) {
    qv.qtInstance = qv.qtInstance->clear();
    qv.qtInstance->insertVariable(type1, arg1);
}

void QueryValidatorFriend::insertSynonymIntoQueryTree(string type1, string arg1, string type2, string arg2) {
    qv.qtInstance = qv.qtInstance->clear();
    qv.qtInstance->insertVariable(type1, arg1);
    qv.qtInstance->insertVariable(type2, arg2);
}

void QueryValidatorFriend::insertSynonymIntoQueryTree(string type1, string arg1, string type2, string arg2, string type3, string arg3) {
    qv.qtInstance = qv.qtInstance->clear();
    qv.qtInstance->insertVariable(type1, arg1);
    qv.qtInstance->insertVariable(type2, arg2);
    qv.qtInstance->insertVariable(type3, arg3);
}
