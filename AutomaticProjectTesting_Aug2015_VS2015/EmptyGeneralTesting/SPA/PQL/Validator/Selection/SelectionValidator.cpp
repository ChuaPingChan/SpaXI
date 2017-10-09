#include "SelectionValidator.h"

SelectionValidator::SelectionValidator(QueryTree *qtPtrNew) {
    setQueryTree(qtPtrNew);
}

SelectionValidator::~SelectionValidator() {}

bool SelectionValidator::isValidSelection(string str)
{
    if (!RegexValidators::isValidSelectOverallRegex(str))
        return false;

    return isValidSelect(str) && areValidClauses(str);
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

bool SelectionValidator::areValidClauses(string str)
{
    SuchThatHandler stHandler = SuchThatHandler(qtPtr);
    PatternHandler pHandler = PatternHandler(qtPtr);

    /* Extracting the clauses portion */
    regex clauseRegex(RegexValidators::RELREF_REGEX + "|" + RegexValidators::PATTERNREF_REGEX);
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
        /*else if (isWith(currentClause)) {
        if (!wHandler.isValidWith(currentClause)) {
        return false;
        }
        }*/

        /*else
        {
        return false;
        }*/
    }
    return true;
}

bool SelectionValidator::isSuchThat(string str)
{
    if ((str.find(RELATIONSHIP_STRING_ARRAY[CALLS]) != std::string::npos)||
        (str.find(RELATIONSHIP_STRING_ARRAY[FOLLOWS]) != std::string::npos) ||
        (str.find(RELATIONSHIP_STRING_ARRAY[PARENT]) != std::string::npos) ||
        (str.find(RELATIONSHIP_STRING_ARRAY[MODIFIES]) != std::string::npos) ||
        (str.find(RELATIONSHIP_STRING_ARRAY[USES]) != std::string::npos))
    {
        return true;
    }
    else {
        return false;
    }
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
