#include "SelectionValidator.h"

SelectionValidator::SelectionValidator(QueryTree *qtPtrNew) {
    setQueryTree(qtPtrNew);
}

SelectionValidator::~SelectionValidator() {}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TODO: remove this chunk when regex table is done
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
const string FOLLOWS_REGEX = "(" + SPACE_0 + "(Follows)(\\*)?" + SPACE_0 + "[(]" + SPACE_0 + STMTREF + SPACE_0 + "[,]" + SPACE_0 + STMTREF + SPACE_0 + "[)]" + SPACE_0 + ")";
const string PARENT_REGEX = "(" + SPACE_0 + "(Parent)(\\*)?" + SPACE_0 + "[(]" + SPACE_0 + STMTREF + SPACE_0 + "[,]" + SPACE_0 + STMTREF + SPACE_0 + "[)]" + SPACE_0 + ")";

/*--------------- Select Regex ---------------*/
const string SELECT_REGEX = "(Select)" + SPACE_1 + SYNONYM;
const string RELREF = "(" + MODIFIES_REGEX + "|" + USES_REGEX + "|" + FOLLOWS_REGEX + "|" + PARENT_REGEX + ")";
const string SUCH_THAT_REGEX = SPACE_0 + "(such)" + SPACE_1 + "(that)" + SPACE_1 + RELREF;
const string SELECT_OVERALL_REGEX = "^" + SPACE_0 + SELECT_REGEX + SPACE_0 + "(" + SUCH_THAT_REGEX + "|" + PATTERN_REGEX + ")*" + SPACE_0 + "$";
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



bool SelectionValidator::isValidSelection(string str)
{
    if (isValidSelectOverallRegex(str) == false)
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
    regex clauseRegex(RELREF + "|" + PATTERN_REGEX);
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

bool SelectionValidator::isValidSelectOverallRegex(string str)
{
    regex overallSelectRegexCheck(SELECT_OVERALL_REGEX);
    return regex_match(str, overallSelectRegexCheck);
}

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
