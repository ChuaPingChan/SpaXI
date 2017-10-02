#include "RegexValidators.h"

/********
* REGEX *
********/
/******************** Grammar ********************/
const string RegexValidators::LETTER_REGEX = "([a-zA-Z])";
const string RegexValidators::DIGIT_REGEX = "([0-9])";
const string RegexValidators::INTEGER_REGEX = "(" + DIGIT_REGEX + "+)";
const string RegexValidators::HASH_REGEX = "(#)";
const string RegexValidators::UNDERSCORE_REGEX = "(_)";
const string RegexValidators::IDENT_REGEX = "(" + LETTER_REGEX + "(" + LETTER_REGEX + "|" + DIGIT_REGEX + "|" + HASH_REGEX + ")*)";
const string RegexValidators::IDENT_WITH_QUOTES_REGEX = "(\"" + IDENT_REGEX + "\")";
const string RegexValidators::SYNONYM_REGEX = IDENT_REGEX;
const string RegexValidators::STMTREF_REGEX = "(" + SYNONYM_REGEX + "|" + UNDERSCORE_REGEX + "|" + INTEGER_REGEX + ")";
const string RegexValidators::ENTREF_REGEX = "(" + SYNONYM_REGEX + "|" + UNDERSCORE_REGEX + "|" + "\"" + IDENT_REGEX + "\"" ")";
const string RegexValidators::NAME_REGEX = "(" + LETTER_REGEX + "(" + LETTER_REGEX + "|" + DIGIT_REGEX + ")*)";
const string RegexValidators::SPACE_0 = "(\\s*)";
const string RegexValidators::SPACE_1 = "(\\s+)";

/*--------------- Declaration Regex ---------------*/
const string RegexValidators::DESIGN_Entity_REGEX = "(procedure|stmtLst|stmt|assign|call|while|if|variable|constant|prog_line)";

/*--------------- Pattern Clause Regex ---------------*/
const string RegexValidators::FACTOR_REGEX = "(" + NAME_REGEX + "|" + INTEGER_REGEX + ")";
const string RegexValidators::EXPRESSION_SPEC = "(" + UNDERSCORE_REGEX + "|" + UNDERSCORE_REGEX + "\"" + FACTOR_REGEX + "\"" + UNDERSCORE_REGEX + ")";
const string RegexValidators::PATTERN_REGEX = "(" + SPACE_0 + "(pattern)" + SPACE_1 + SYNONYM_REGEX + SPACE_0 + "[(]" + SPACE_0 + ENTREF_REGEX + SPACE_0 + "[,]" + SPACE_0 + EXPRESSION_SPEC + SPACE_0 + "[)]" + SPACE_0 + ")";

/*--------------- Relationship Clause Regex ---------------*/
const string RegexValidators::MODIFIES_REGEX = "(" + SPACE_0 + "(Modifies)" + SPACE_0 + "[(]" + SPACE_0 + STMTREF_REGEX + SPACE_0 + "[,]" + SPACE_0 + ENTREF_REGEX + SPACE_0 + "[)]" + SPACE_0 + ")";
const string RegexValidators::USES_REGEX = "(" + SPACE_0 + "(Uses)" + SPACE_0 + "[(]" + SPACE_0 + STMTREF_REGEX + SPACE_0 + "[,]" + SPACE_0 + ENTREF_REGEX + SPACE_0 + "[)]" + SPACE_0 + ")";
const string RegexValidators::FOLLOWS_REGEX = "(" + SPACE_0 + "(Follows)(\\*)?" + SPACE_0 + "[(]" + SPACE_0 + STMTREF_REGEX + SPACE_0 + "[,]" + SPACE_0 + STMTREF_REGEX + SPACE_0 + "[)]" + SPACE_0 + ")";
const string RegexValidators::PARENT_REGEX = "(" + SPACE_0 + "(Parent)(\\*)?" + SPACE_0 + "[(]" + SPACE_0 + STMTREF_REGEX + SPACE_0 + "[,]" + SPACE_0 + STMTREF_REGEX + SPACE_0 + "[)]" + SPACE_0 + ")";

/*--------------- Select Regex ---------------*/
const string RegexValidators::SELECT_REGEX = "(Select)" + SPACE_1 + SYNONYM_REGEX;
const string RegexValidators::RELREF_REGEX = "(" + MODIFIES_REGEX + "|" + USES_REGEX + "|" + FOLLOWS_REGEX + "|" + PARENT_REGEX + ")";
const string RegexValidators::SUCH_THAT_REGEX = SPACE_0 + "(such)" + SPACE_1 + "(that)" + SPACE_1 + RELREF_REGEX;
const string RegexValidators::SELECT_OVERALL_REGEX = "^" + SPACE_0 + SELECT_REGEX + SPACE_0 + "(" + SUCH_THAT_REGEX + "|" + PATTERN_REGEX + ")*" + SPACE_0 + "$";




bool RegexValidators::isValidIntegerRegex(string str)
{
    regex integerRegexCheck = regex(INTEGER_REGEX);
    return regex_match(str, integerRegexCheck);
}

/**********
* METHODS *
**********/
bool RegexValidators::isValidIdentWithQuotesRegex(string str)
{
    regex checkIdentWithInvertedCommas = regex(IDENT_WITH_QUOTES_REGEX);
    return regex_match(str, checkIdentWithInvertedCommas);
}

/*--------------- Declaration Regex Methods ---------------*/
bool RegexValidators::isValidEntityRegex(string str)
{
    regex entityRegex(DESIGN_Entity_REGEX);
    return regex_match(str, entityRegex);
}

bool RegexValidators::isValidSynonymRegex(string str)
{
    regex synonymRegex(SYNONYM_REGEX);
    return regex_match(str, synonymRegex);
}

/*--------------- Select Clause Regex Methods ---------------*/
bool RegexValidators::isValidSelectOverallRegex(string str)
{
    regex overallSelectRegexCheck(SELECT_OVERALL_REGEX);
    return regex_match(str, overallSelectRegexCheck);
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

bool RegexValidators::isValidExpressionSpec(string str)
{
    regex expressionSpecCheck(EXPRESSION_SPEC);
    return regex_match(str, expressionSpecCheck);
}

/*--------------- Pattern Clause Regex Methods ---------------*/
bool RegexValidators::isValidPatternRegex(string str)
{
    regex patternRegexCheck(PATTERN_REGEX);
    return regex_match(str, patternRegexCheck);
}

/*--------------- Select Regex ---------------*/
bool RegexValidators::isValidSelectRegex(string str)
{
    regex selectRegexCheck(SELECT_REGEX);
    return regex_match(str, selectRegexCheck);
}

bool RegexValidators::isValidSuchThatRegex(string str)
{
    regex suchThatRegexCheck(SUCH_THAT_REGEX);
    return regex_match(str, suchThatRegexCheck);
}
