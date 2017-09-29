#include "RegexValidators.h"

/*--------------- Declaration Regex Methods ---------------*/
bool RegexValidators::isValidEntity(string str)
{
    regex entityRegex(DESIGN_ENTITY_REGEX);
    return regex_match(str, entityRegex);
}

bool RegexValidators::isValidSynonym(string str)
{
    regex synonymRegex(SYNONYM);
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

/*--------------- Pattern Clause Regex Methods ---------------*/
bool RegexValidators::isValidPatternRegex(string str)
{
    regex patternRegexCheck(PATTERN_REGEX);
    return regex_match(str, patternRegexCheck);
}

