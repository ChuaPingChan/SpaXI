#include "SelectionValidator.h"

SelectionValidator::SelectionValidator(QueryTree *qtPtrNew) {
    setQueryTree(qtPtrNew);
}

SelectionValidator::~SelectionValidator() {}

bool SelectionValidator::isValidSelection(string str)
{
    if (RegexValidators::isValidSelectOverallRegex(str) == false)
        return false;

    ///* Extracting the Select portion */
    //regex selectRegex(SELECT_REGEX);
    //sregex_iterator sel(str.begin(), str.end(), selectRegex);
    //sregex_iterator sel_end;

    //for (; sel != sel_end; sel++)
    //{
    //    string current = sel->str(0);
    //    if (!isValidSelectBeginning(current))
    //        return false;
    //}

    SuchThatHandler stHandler = SuchThatHandler(qtPtr);
    PatternHandler pHandler = PatternHandler(qtPtr);

    /* Extracting the clauses portion */
    regex clauseRegex(RegexValidators::RELREF_REGEX + "|" + RegexValidators::PATTERN_REGEX);
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
       
        /*else
        {
            return false;
        }*/

    }

    return true;  //stub
}

bool SelectionValidator::setQueryTree(QueryTree *qtPtrNew)
{
    this->qtPtr = qtPtrNew;
    return true;
}

//bool SelectionValidator::isValidSelectBeginning(string str)
//{
//    size_t f = str.find("Select");
//    str.replace(f, std::string("Select").length(), "");
//
//    /* Extracting the synonym */
//    regex synonymRegex(SYNONYM);
//    sregex_iterator it(str.begin(), str.end(), synonymRegex);
//    sregex_iterator it_end;
//    string current;
//    for (; it != it_end; it++)
//    {
//        current = it->str(0);
//        if (!qtInstance->varExists(current))
//            return false;
//    }
//
//    array<string, 2> result;
//    if (isArgumentInClause(current, qtInstance->getAssigns()))
//    {
//        result[0] = "assign";
//        result[1] = current;
//    }
//    else  if (isArgumentInClause(current, qtInstance->getWhiles()))
//    {
//        result[0] = "while";
//        result[1] = current;
//    }
//    else  if (isArgumentInClause(current, qtInstance->getStmts()))
//    {
//        result[0] = "stmt";
//        result[1] = current;
//    }
//    else  if (isArgumentInClause(current, qtInstance->getVars()))
//    {
//        result[0] = "var";
//        result[1] = current;
//    }
//    else  if (isArgumentInClause(current, qtInstance->getProgLines()))
//    {
//        result[0] = "stmt";
//        result[1] = current;
//    }
//    else  if (isArgumentInClause(current, qtInstance->getConsts()))
//    {
//        result[0] = "const";
//        result[1] = current;
//    }
//
//    qtInstance->insertSelect(result);
//    return true;
//}

bool SelectionValidator::isSuchThat(string str)
{
    if ((str.find("Follows") != std::string::npos) || 
        (str.find("Parent") != std::string::npos) ||
        (str.find("Modifies") != std::string::npos) ||
        (str.find("Uses") != std::string::npos))
    {
        return true;
    }
    else {
        return false;
    }
}

bool SelectionValidator::isPattern(string str)
{
    return (str.find("pattern") != std::string::npos);
}
