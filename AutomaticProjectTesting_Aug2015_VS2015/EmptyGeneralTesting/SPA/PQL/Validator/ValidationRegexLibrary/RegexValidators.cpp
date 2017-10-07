#include "RegexValidators.h"

/********
* REGEX *
********/
/******************** Grammar ********************/
const string RegexValidators::SPACE_0 = "(\\s*)";
const string RegexValidators::SPACE_1 = "(\\s+)";
const string RegexValidators::LETTER_REGEX = "([a-zA-Z])";
const string RegexValidators::DIGIT_REGEX = "([0-9])";
const string RegexValidators::INTEGER_REGEX = "(" + DIGIT_REGEX + "+)";
const string RegexValidators::BOOLEAN_REGEX = "(BOOLEAN)";
const string RegexValidators::HASH_REGEX = "(#)";
const string RegexValidators::UNDERSCORE_REGEX = "(_)";
const string RegexValidators::IDENT_REGEX = "(" + LETTER_REGEX + "(" + LETTER_REGEX + "|" + DIGIT_REGEX + "|" + HASH_REGEX + ")*)";
const string RegexValidators::IDENT_WITH_QUOTES_REGEX = "(\"" + IDENT_REGEX + "\")";
const string RegexValidators::SYNONYM_REGEX = IDENT_REGEX;
const string RegexValidators::STMTREF_REGEX = "(" + SYNONYM_REGEX + "|" + UNDERSCORE_REGEX + "|" + INTEGER_REGEX + ")";
const string RegexValidators::ENTREF_REGEX = "(" + SYNONYM_REGEX + "|" + UNDERSCORE_REGEX + "|" + "\"" + IDENT_REGEX + "\"" ")";
const string RegexValidators::LINEREF_REGEX = "(" + SYNONYM_REGEX + "|" + UNDERSCORE_REGEX + "|" + INTEGER_REGEX + ")";
const string RegexValidators::NAME_REGEX = "(" + LETTER_REGEX + "(" + LETTER_REGEX + "|" + DIGIT_REGEX + ")*)";
const string RegexValidators::ATTRNAME_REGEX = "(procName|varName|value|stmt#)";
const string RegexValidators::ATTRREF_REGEX = "(" + SYNONYM_REGEX + "[.]" + ATTRNAME_REGEX + ")";
const string RegexValidators::ELEM_REGEX = "(" + SYNONYM_REGEX + "|" + ATTRREF_REGEX + ")";
const string RegexValidators::TUPLE_REGEX = "(" + SPACE_0 + ELEM_REGEX + SPACE_0 + "|" + SPACE_0 + "<" + SPACE_0 + ELEM_REGEX + SPACE_0 + "(," + SPACE_0 + ELEM_REGEX + SPACE_0 + ")*" + ">" + SPACE_0 + ")";
const string RegexValidators::DESIGN_ENTITY_REGEX = "(procedure|stmtLst|stmt|assign|call|while|if|variable|constant|prog_line)";

/*--------------- Relationship Clause Regex ---------------*/
const string RegexValidators::MODIFIES_FIRSTARG_REGEX = "(" + SYNONYM_REGEX + "|" + UNDERSCORE_REGEX + "|" + INTEGER_REGEX + "|" + IDENT_WITH_QUOTES_REGEX + ")";
const string RegexValidators::MODIFIES_REGEX = "(" + SPACE_0 + "(Modifies)" + SPACE_0 + "[(]" + SPACE_0 + MODIFIES_FIRSTARG_REGEX + SPACE_0 + "[,]" + SPACE_0 + ENTREF_REGEX + SPACE_0 + "[)]" + SPACE_0 + ")";
const string RegexValidators::USES_FIRSTARG_REGEX = "(" + SYNONYM_REGEX + "|" + UNDERSCORE_REGEX + "|" + INTEGER_REGEX + "|" + IDENT_WITH_QUOTES_REGEX + ")";
const string RegexValidators::USES_REGEX = "(" + SPACE_0 + "(Uses)" + SPACE_0 + "[(]" + SPACE_0 + USES_FIRSTARG_REGEX + SPACE_0 + "[,]" + SPACE_0 + ENTREF_REGEX + SPACE_0 + "[)]" + SPACE_0 + ")";
const string RegexValidators::FOLLOWS_REGEX = "(" + SPACE_0 + "(Follows)(\\*)?" + SPACE_0 + "[(]" + SPACE_0 + STMTREF_REGEX + SPACE_0 + "[,]" + SPACE_0 + STMTREF_REGEX + SPACE_0 + "[)]" + SPACE_0 + ")";
const string RegexValidators::PARENT_REGEX = "(" + SPACE_0 + "(Parent)(\\*)?" + SPACE_0 + "[(]" + SPACE_0 + STMTREF_REGEX + SPACE_0 + "[,]" + SPACE_0 + STMTREF_REGEX + SPACE_0 + "[)]" + SPACE_0 + ")";
const string RegexValidators::RELREF_REGEX = "(" + MODIFIES_REGEX + "|" + USES_REGEX + "|" + FOLLOWS_REGEX + "|" + PARENT_REGEX + ")";
const string RegexValidators::RELCOND_REGEX = "(" + SPACE_0 + RELREF_REGEX + SPACE_0 + "("+ SPACE_1 + "and" + SPACE_1 + RELREF_REGEX + SPACE_0 + ")*" + SPACE_0 + ")";
const string RegexValidators::SUCH_THAT_CL_REGEX = "(" + SPACE_0 + "(such)" + SPACE_1 + "(that)" + SPACE_1 + RELCOND_REGEX + SPACE_0 + ")";
const string RegexValidators::RELATIONSHIP_KEYWORD_REGEX = "(Modifies|Uses|Parent[\\*]|Parent|Follows[\\*]|Follows|Calls[\\*]|Calls|Next[\\*]|Next|Affects[\\*]|Affects)";

/*--------------- Pattern Clause Regex ---------------*/
const string RegexValidators::FACTOR_REGEX = "(" + SPACE_0 + NAME_REGEX + SPACE_0 + "|" + SPACE_0 + INTEGER_REGEX + SPACE_0 + ")";
const string RegexValidators::EXPRESSION_SPEC = "(" + SPACE_0 + UNDERSCORE_REGEX + SPACE_0 + "|" + SPACE_0 + UNDERSCORE_REGEX + SPACE_0 + "\"" + SPACE_0 + FACTOR_REGEX + SPACE_0 + "\"" + SPACE_0 + UNDERSCORE_REGEX + SPACE_0 + ")";
const string RegexValidators::PATTERN_ASSIGN_REGEX = "(" + SPACE_0 + SYNONYM_REGEX + SPACE_0 + "[(]" + "(" + SPACE_0 + ENTREF_REGEX + SPACE_0 + "[,]" + SPACE_0 + EXPRESSION_SPEC + SPACE_0 + "|" + SPACE_0 + UNDERSCORE_REGEX + SPACE_0 + ")" + "[)]" + SPACE_0 + ")";
const string RegexValidators::PATTERN_WHILE_REGEX = "(" + SPACE_0 + SYNONYM_REGEX + SPACE_0 + "[(]" + SPACE_0 + ENTREF_REGEX + SPACE_0 + "[,]" + SPACE_0 + UNDERSCORE_REGEX + SPACE_0+ "[)]" + SPACE_0 + ")";
const string RegexValidators::PATTERN_REGEX = "(" + SPACE_0 + "(pattern)" + SPACE_1 + SYNONYM_REGEX + SPACE_0 + "[(]" + SPACE_0 + ENTREF_REGEX + SPACE_0 + "[,]" + SPACE_0 + EXPRESSION_SPEC + SPACE_0 + "[)]" + SPACE_0 + ")";

/*--------------- Select Regex ---------------*/
const string RegexValidators::RESULTCL_REGEX = "(" + SPACE_0 + TUPLE_REGEX + SPACE_0 + "|" + SPACE_0 + BOOLEAN_REGEX + SPACE_0 + ")";
const string RegexValidators::SELECT_REGEX = "(Select)" + SPACE_1 + RESULTCL_REGEX;

/******************** Select Overall ********************/
const string RegexValidators::SELECT_OVERALL_REGEX = "^" + SPACE_0 + SELECT_REGEX + SPACE_0 + "(" + SUCH_THAT_CL_REGEX + "|" + PATTERN_REGEX + ")*" + SPACE_0 + "$";



/**********
* METHODS *
**********/

bool RegexValidators::isValidLetterRegex(string str)
{
    regex letterRegexCheck = regex(LETTER_REGEX);
    return regex_match(str, letterRegexCheck);
}

bool RegexValidators::isValidIntegerRegex(string str)
{
    regex integerRegexCheck = regex(INTEGER_REGEX);
    return regex_match(str, integerRegexCheck);
}

bool RegexValidators::isValidBooleanRegex(string str)
{
    regex booleanRegexCheck = regex(BOOLEAN_REGEX);
    return regex_match(str, booleanRegexCheck);
}

bool RegexValidators::isValidIdentWithQuotesRegex(string str)
{
    regex checkIdentWithInvertedCommas = regex(IDENT_WITH_QUOTES_REGEX);
    return regex_match(str, checkIdentWithInvertedCommas);
}

bool RegexValidators::isValidSynonymRegex(string str)
{
    regex synonymRegex(SYNONYM_REGEX);
    return regex_match(str, synonymRegex);
}

bool RegexValidators::isValidStmtRefRegex(string str)
{
    regex stmtrefRegexCheck = regex(STMTREF_REGEX);
    return regex_match(str, stmtrefRegexCheck);
}

bool RegexValidators::isValidEntRefRegex(string str)
{
    regex entrefRegexCheck = regex(ENTREF_REGEX);
    return regex_match(str, entrefRegexCheck);
}

bool RegexValidators::isValidNameRegex(string str)
{
    regex nameRegexCheck = regex(NAME_REGEX);
    return regex_match(str, nameRegexCheck);
}

bool RegexValidators::isValidAttrNameRegex(string str)
{
    regex attrNameRegexCheck = regex(ATTRNAME_REGEX);
    return regex_match(str, attrNameRegexCheck);
}

bool RegexValidators::isValidAttrRefRegex(string str)
{
    regex attrRefRegexCheck = regex(ATTRREF_REGEX);
    return regex_match(str, attrRefRegexCheck);
}

bool RegexValidators::isValidElemRegex(string str)
{
    regex elemRegexCheck(ELEM_REGEX);
    return regex_match(str, elemRegexCheck);
}

bool RegexValidators::isValidTupleRegex(string str)
{
    regex tupleRegexCheck(TUPLE_REGEX);
    return regex_match(str, tupleRegexCheck);
}

bool RegexValidators::isValidEntityRegex(string str)
{
    regex entityRegex(DESIGN_ENTITY_REGEX);
    return regex_match(str, entityRegex);
}

/*--------------- Such That Clauses Regex Methods ---------------*/
bool RegexValidators::isValidModifiesRegex(string str)
{
    regex modifiesRegexCheck(MODIFIES_REGEX);
    return regex_match(str, modifiesRegexCheck);
}

bool RegexValidators::isValidUsesRegex(string str)
{
    regex usesRegexCheck(USES_REGEX);
    return regex_match(str, usesRegexCheck);
}

bool RegexValidators::isValidFollowsRegex(string str)
{
    regex followsRegexCheck(FOLLOWS_REGEX);
    return regex_match(str, followsRegexCheck);
}

bool RegexValidators::isValidParentRegex(string str)
{
    regex parentRegexCheck(PARENT_REGEX);
    return regex_match(str, parentRegexCheck);
}

bool RegexValidators::isValidRelCondRegex(string str)
{
    regex relCondRegexCheck(RELCOND_REGEX);
    return regex_match(str, relCondRegexCheck);
}

bool RegexValidators::isValidSuchThatClRegex(string str)
{
    regex suchThatClRegexCheck(SUCH_THAT_CL_REGEX);
    return regex_match(str, suchThatClRegexCheck);
}

bool RegexValidators::isValidFactorRegex(string str)
{
    regex factorRegexCheck(FACTOR_REGEX);
    return regex_match(str, factorRegexCheck);
}

bool RegexValidators::isValidExpressionSpecRegex(string str)
{
    regex expressionSpecCheck(EXPRESSION_SPEC);
    return regex_match(str, expressionSpecCheck);
}

bool RegexValidators::isValidPatternAssignRegex(string str)
{
    regex patternAssignRegexCheck(PATTERN_ASSIGN_REGEX);
    return regex_match(str, patternAssignRegexCheck);
}

bool RegexValidators::isValidPatternWhileRegex(string str)
{
    regex patternWhileRegexCheck(PATTERN_WHILE_REGEX);
    return regex_match(str, patternWhileRegexCheck);
}

/*--------------- Pattern Clause Regex Methods ---------------*/
bool RegexValidators::isValidPatternRegex(string str)
{
    regex patternRegexCheck(PATTERN_REGEX);
    return regex_match(str, patternRegexCheck);
}

/*--------------- Select Regex ---------------*/
bool RegexValidators::isValidResultClRegex(string str)
{
    regex resultClRegexCheck(RESULTCL_REGEX);
    return regex_match(str, resultClRegexCheck);
}

bool RegexValidators::isValidSelectRegex(string str)
{
    regex selectRegexCheck(SELECT_REGEX);
    return regex_match(str, selectRegexCheck);
}

/*--------------- Select Clause Regex Methods ---------------*/
bool RegexValidators::isValidSelectOverallRegex(string str)
{
    regex overallSelectRegexCheck(SELECT_OVERALL_REGEX);
    return regex_match(str, overallSelectRegexCheck);
}
