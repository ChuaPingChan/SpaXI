#include "SelectionValidator.h"

using namespace std;

SelectionValidator::SelectionValidator(QueryTree *qtPtrNew) {
    setQueryTree(qtPtrNew);
}

SelectionValidator::~SelectionValidator() {}

bool SelectionValidator::isValidSelection(string str)
{
    return isValidSelect(str) && RegexValidators::isValidSelectOverallRegex(str) && areValidClauses(str);
}

bool SelectionValidator::setQueryTree(QueryTree *qtPtrNew)
{
    this->qtPtr = qtPtrNew;
    return true;
}

bool SelectionValidator::isValidSelect(string str)
{
    string selectRawStr = extractSelectRawStr(str);

    SelectValidator sv = SelectValidator(qtPtr);
    return sv.isValid(selectRawStr);
}

/*
* Pre-cond: str is syntactically valid
*/
bool SelectionValidator::areValidClauses(string str)
{
    SuchThatHandler stHandler = SuchThatHandler(qtPtr);
    PatternHandler pHandler = PatternHandler(qtPtr);
    WithHandler wHandler = WithHandler(qtPtr);

    /* Extracting the clauses portion */
    regex clauseRegex(RegexValidators::RELREF_REGEX + "|" + RegexValidators::PATTERNREF_REGEX + "|" + RegexValidators::ATTRCOMPARE_REGEX);
    sregex_iterator it(str.cbegin(), str.cend(), clauseRegex);
    sregex_iterator it_end;

    for (; it != it_end; it++)
    {
        string currentClause = it->str(0);

        if (isSuchThat(currentClause)) {
            if (!stHandler.isValidSuchThat(currentClause)) {
                return false;
            }
        }
        else if (isPattern(currentClause)) {
            if (!pHandler.isValidPattern(currentClause)) {
                return false;
            }
        }
        else if (isWith(currentClause)) {
            if (!wHandler.isValidWith(currentClause)) {
            return false;
            }
        }

        /*else
        {
        return false;
        }*/
    }
    return true;
}

bool SelectionValidator::isSuchThat(string str)
{
    bool isValid = false;

    for (pair<string, Relationship> relMap : MAP_STR_TO_REL) {
        if (str.find(relMap.first) != string::npos) {
            isValid = true;
        }
    }
    return isValid;
}

bool SelectionValidator::isPattern(string str)
{
    return RegexValidators::isValidPatternRefRegex(str);
}

bool SelectionValidator::isWith(string str)
{
    return RegexValidators::isValidAttrCompareRegex(str);
}

string SelectionValidator::extractSelectRawStr(string str)
{
    /* Extracting the Select portion */
    regex selectRegex(RegexValidators::SELECT_REGEX);
    sregex_iterator sel(str.begin(), str.end(), selectRegex);
    sregex_iterator sel_end;
    string selectStr;
    for (; sel != sel_end; sel++)
    {
        selectStr = sel->str(0);
    }
    return selectStr;
}
