#include "RegexValidators.h"

/********
* REGEX *
********/
/******************** Entity Strings ********************/
const string RegexValidators::STMT_STRING = "stmt";
const string RegexValidators::ASSIGN_STRING = "assign";
const string RegexValidators::WHILE_STRING = "while";
const string RegexValidators::IF_STRING = "if";
const string RegexValidators::PROG_LINE_STRING = "prog_line";
const string RegexValidators::CALL_STRING = "call";
const string RegexValidators::PROCEDURE_STRING ="procedure";
const string RegexValidators::VARIABLE_STRING = "variable";
const string RegexValidators::CONSTANT_STRING = "constant";
const string RegexValidators::STMTLST_STRING = "stmtlst";

/******************** Attribute Strings ********************/
const string RegexValidators::PROCNAME_STRING = "procName";
const string RegexValidators::STMTNUM_STRING = "stmt#";
const string RegexValidators::VARNAME_STRING = "varName";
const string RegexValidators::VALUE_STRING = "value";

/******************** Grammar ********************/
const string RegexValidators::SPACE_0 = "(\\s*)";
const string RegexValidators::SPACE_1 = "(\\s+)";
const string RegexValidators::OPEN_BRACKET_REGEX = "([(])";
const string RegexValidators::CLOSE_BRACKET_REGEX = "([)])";
const string RegexValidators::PLUS_REGEX = "([+])";
const string RegexValidators::MINUS_REGEX = "([-])";
const string RegexValidators::TIMES_REGEX = "([*])";
const string RegexValidators::OPERATOR_REGEX = "(" + PLUS_REGEX + "|" + MINUS_REGEX + "|" + TIMES_REGEX + ")";
const string RegexValidators::LETTER_REGEX = "([a-zA-Z])";
const string RegexValidators::DIGIT_REGEX = "([0-9])";
const string RegexValidators::INTEGER_REGEX = "(" + DIGIT_REGEX + "+)";
const string RegexValidators::BOOLEAN_REGEX = "(BOOLEAN)";
const string RegexValidators::HASH_REGEX = "(#)";
const string RegexValidators::UNDERSCORE_REGEX = "(_)";
const string RegexValidators::IDENT_REGEX = "(" + LETTER_REGEX + "(" + LETTER_REGEX + "|" + DIGIT_REGEX + "|" + HASH_REGEX + ")*)";
const string RegexValidators::IDENT_WITH_QUOTES_REGEX = "(\"" + SPACE_0 + IDENT_REGEX + SPACE_0 + "\")";
const string RegexValidators::SYNONYM_REGEX = IDENT_REGEX;
const string RegexValidators::STMTREF_REGEX = "(" + SYNONYM_REGEX + "|" + UNDERSCORE_REGEX + "|" + INTEGER_REGEX + ")";
const string RegexValidators::ENTREF_REGEX = "(" + SYNONYM_REGEX + "|" + UNDERSCORE_REGEX + "|" + IDENT_WITH_QUOTES_REGEX + ")";
const string RegexValidators::LINEREF_REGEX = "(" + SYNONYM_REGEX + "|" + UNDERSCORE_REGEX + "|" + INTEGER_REGEX + ")";
const string RegexValidators::NAME_REGEX = "(" + LETTER_REGEX + "(" + LETTER_REGEX + "|" + DIGIT_REGEX + ")*)";
const string RegexValidators::ATTRNAME_REGEX = "(procName|varName|value|stmt#)";
const string RegexValidators::ATTRREF_REGEX = "(" + SPACE_0 + SYNONYM_REGEX + "[.]" + ATTRNAME_REGEX + SPACE_0 + ")";
const string RegexValidators::ELEM_REGEX = "(" + ATTRREF_REGEX +  "|" + SYNONYM_REGEX + ")";
const string RegexValidators::TUPLE_REGEX = "(" + SPACE_1 + ELEM_REGEX + SPACE_0 + "|" + SPACE_0 + "<" + SPACE_0 + ELEM_REGEX + SPACE_0 + "(," + SPACE_0 + ELEM_REGEX + SPACE_0 + ")*" + ">" + SPACE_0 + ")";
const string RegexValidators::DESIGN_ENTITY_REGEX = "(procedure|stmtLst|stmt|assign|call|while|if|variable|constant|prog_line)";

/*--------------- Declaration Regex ---------------*/
const string RegexValidators::DECLARATION_EXTRACTED_REGEX = "(" + SPACE_0 + DESIGN_ENTITY_REGEX + SPACE_1 + SYNONYM_REGEX + "(" + SPACE_0 + "[,]" + SPACE_0 + SYNONYM_REGEX + SPACE_0 + ")*" + SPACE_0 + ")";

/*--------------- Relationship Clause Regex ---------------*/
const string RegexValidators::MODIFIES_FIRSTARG_REGEX = "(" + SYNONYM_REGEX + "|" + UNDERSCORE_REGEX + "|" + INTEGER_REGEX + "|" + IDENT_WITH_QUOTES_REGEX + ")";
const string RegexValidators::MODIFIES_REGEX = "(" + SPACE_0 + "(Modifies)" + SPACE_0 + "[(]" + SPACE_0 + MODIFIES_FIRSTARG_REGEX + SPACE_0 + "[,]" + SPACE_0 + ENTREF_REGEX + SPACE_0 + "[)]" + SPACE_0 + ")";
const string RegexValidators::USES_FIRSTARG_REGEX = "(" + SYNONYM_REGEX + "|" + UNDERSCORE_REGEX + "|" + INTEGER_REGEX + "|" + IDENT_WITH_QUOTES_REGEX + ")";
const string RegexValidators::USES_REGEX = "(" + SPACE_0 + "(Uses)" + SPACE_0 + "[(]" + SPACE_0 + USES_FIRSTARG_REGEX + SPACE_0 + "[,]" + SPACE_0 + ENTREF_REGEX + SPACE_0 + "[)]" + SPACE_0 + ")";
const string RegexValidators::FOLLOWS_REGEX = "(" + SPACE_0 + "(Follows)(\\*)?" + SPACE_0 + "[(]" + SPACE_0 + STMTREF_REGEX + SPACE_0 + "[,]" + SPACE_0 + STMTREF_REGEX + SPACE_0 + "[)]" + SPACE_0 + ")";
const string RegexValidators::PARENT_REGEX = "(" + SPACE_0 + "(Parent)(\\*)?" + SPACE_0 + "[(]" + SPACE_0 + STMTREF_REGEX + SPACE_0 + "[,]" + SPACE_0 + STMTREF_REGEX + SPACE_0 + "[)]" + SPACE_0 + ")";
const string RegexValidators::CALLS_REGEX = "(" + SPACE_0 + "(Calls)(\\*)?" + SPACE_0 + "[(]" + SPACE_0 + ENTREF_REGEX + SPACE_0 + "[,]" + SPACE_0 + ENTREF_REGEX + SPACE_0 + "[)]" + SPACE_0 + ")";
const string RegexValidators::NEXT_REGEX = "(" + SPACE_0 + "(Next)(\\*)?" + SPACE_0 + "[(]" + SPACE_0 + LINEREF_REGEX + SPACE_0 + "[,]" + SPACE_0 + LINEREF_REGEX + SPACE_0 + "[)]" + SPACE_0 + ")";
const string RegexValidators::AFFECTS_REGEX = "(" + SPACE_0 + "(Affects)(\\*)?" + SPACE_0 + "[(]" + SPACE_0 + STMTREF_REGEX + SPACE_0 + "[,]" + SPACE_0 + STMTREF_REGEX + SPACE_0 + "[)]" + SPACE_0 + ")";
const string RegexValidators::RELREF_REGEX = "(" + MODIFIES_REGEX + "|" + USES_REGEX + "|" + FOLLOWS_REGEX + "|" + PARENT_REGEX + "|" + CALLS_REGEX + "|" + NEXT_REGEX + "|" + AFFECTS_REGEX + ")";
const string RegexValidators::RELCOND_REGEX = "(" + SPACE_0 + RELREF_REGEX + SPACE_0 + "("+ SPACE_0 + "and" + SPACE_1 + RELREF_REGEX + SPACE_0 + ")*" + SPACE_0 + ")";
const string RegexValidators::SUCH_THAT_Cl_REGEX = "(" + SPACE_0 + "(such that)" + SPACE_1 + RELCOND_REGEX + SPACE_0 + ")";
const string RegexValidators::RELATIONSHIP_KEYWORD_REGEX = "(Modifies|Uses|Parent[\\*]|Parent|Follows[\\*]|Follows|Calls[\\*]|Calls|Next[\\*]|Next|Affects[\\*]|Affects)";

/*--------------- Pattern Clause Regex ---------------*/
const string RegexValidators::EXPRESSION_SPEC_EXACT_REGEX = "(" + SPACE_0 + "\"\\s*\\(*\\s*(\\d+|[a-zA-Z][a-zA-Z0-9]*)\\s*\\)*\\s*(\\s*[+\\-*]\\s*\\(*\\s*(\\d+|[a-zA-Z][a-zA-Z0-9]*)\\s*\\)*\\s*)+\\s*\"|\"\\s*\\(*\\s*(\\d+|[a-zA-Z][a-zA-Z0-9]*)\\s*\\)*\\s*\"" + SPACE_0 + ")";
const string RegexValidators::EXPRESSION_SPEC_PARTIAL_REGEX = "(" + SPACE_0 + "_" + SPACE_0 + EXPRESSION_SPEC_EXACT_REGEX + SPACE_0 + "_" + SPACE_0 + ")";
const string RegexValidators::EXPRESSION_SPEC = "(" + EXPRESSION_SPEC_PARTIAL_REGEX + "|" + EXPRESSION_SPEC_EXACT_REGEX + ")";
const string RegexValidators::PATTERN_ASSIGN_FIRSTARG_REGEX = "(" + SPACE_0 + ENTREF_REGEX + SPACE_0 + ")";
const string RegexValidators::PATTERN_ASSIGN_SECONDARG_REGEX = "(" + SPACE_0 + EXPRESSION_SPEC + SPACE_0 + "|" + SPACE_0 + UNDERSCORE_REGEX + SPACE_0 + ")";
const string RegexValidators::PATTERN_ASSIGN_REGEX = "(" + SPACE_0 + SYNONYM_REGEX + SPACE_0 + "[(]" + PATTERN_ASSIGN_FIRSTARG_REGEX + "[,]" + PATTERN_ASSIGN_SECONDARG_REGEX + "[)]" + SPACE_0 + ")";
const string RegexValidators::PATTERN_WHILE_REGEX = "(" + SPACE_0 + SYNONYM_REGEX + SPACE_0 + "[(]" + SPACE_0 + ENTREF_REGEX + SPACE_0 + "[,]" + SPACE_0 + UNDERSCORE_REGEX + SPACE_0+ "[)]" + SPACE_0 + ")";
const string RegexValidators::PATTERN_IF_REGEX = "(" + SPACE_0 + SYNONYM_REGEX + SPACE_0 + "[(]" + SPACE_0 + ENTREF_REGEX + SPACE_0 + "[,]" + SPACE_0 + UNDERSCORE_REGEX + SPACE_0 + "[,]" + SPACE_0 + UNDERSCORE_REGEX + SPACE_0 + "[)]" + SPACE_0 + ")";
const string RegexValidators::PATTERNREF_REGEX = "(" + PATTERN_ASSIGN_REGEX + "|" + PATTERN_WHILE_REGEX + "|" + PATTERN_IF_REGEX + ")";
const string RegexValidators::PATTERNCOND_REGEX = "(" + SPACE_0 + PATTERNREF_REGEX + SPACE_0 + "(" + SPACE_0 + "and" + SPACE_1 + PATTERNREF_REGEX + SPACE_0 + ")*" + SPACE_0 + ")";
const string RegexValidators::PATTERN_Cl_REGEX = "(" + SPACE_0 + "(pattern)" + SPACE_1 + PATTERNCOND_REGEX + SPACE_0 + ")";

/*--------------- With Regex ---------------*/
const string RegexValidators::REF_REGEX = "(" + IDENT_WITH_QUOTES_REGEX + "|" + INTEGER_REGEX + "|" + ATTRREF_REGEX + + "|" + SYNONYM_REGEX + ")";
const string RegexValidators::ATTRCOMPARE_REGEX = "(" + SPACE_0 + REF_REGEX + SPACE_0 + "[=]" + SPACE_0 + REF_REGEX + SPACE_0 + ")";
const string RegexValidators::ATTRCOND_REGEX = "(" + SPACE_0 + ATTRCOMPARE_REGEX + SPACE_0 + "(" + SPACE_1 + "and" + SPACE_1 + ATTRCOMPARE_REGEX + SPACE_0 + ")*" + SPACE_0 +  ")";
const string RegexValidators::WITH_Cl_REGEX = "(" + SPACE_0 + "(with)" + SPACE_1 + ATTRCOND_REGEX + SPACE_0 + ")";

/*--------------- Select Regex ---------------*/
const string RegexValidators::RESULTCL_REGEX = "(" + SPACE_0 + TUPLE_REGEX + SPACE_0 + "|" + SPACE_0 + BOOLEAN_REGEX + SPACE_0 + ")";
const string RegexValidators::SELECT_REGEX = "(Select)" + SPACE_0 + RESULTCL_REGEX;

/******************** Select Overall ********************/
const string RegexValidators::SELECT_OVERALL_REGEX = "^" + SPACE_0 + SELECT_REGEX + SPACE_0 + "(" + SUCH_THAT_Cl_REGEX + "|" + PATTERN_Cl_REGEX + "|" + WITH_Cl_REGEX + ")*" + SPACE_0 + "$";



/**********
* METHODS *
**********/
/******************** Entity Strings ********************/
bool RegexValidators::isValidStmtString(string str)
{
    regex stmtStringCheck = regex(STMT_STRING);
    return regex_match(str, stmtStringCheck);
}

bool RegexValidators::isValidAssignString(string str)
{
    regex assignStringCheck = regex(ASSIGN_STRING);
    return regex_match(str, assignStringCheck);
}

bool RegexValidators::isValidWhileString(string str)
{
    regex whileStringCheck = regex(WHILE_STRING);
    return regex_match(str, whileStringCheck);
}

bool RegexValidators::isValidIfString(string str)
{
    regex ifStringCheck = regex(IF_STRING);
    return regex_match(str, ifStringCheck);
}

bool RegexValidators::isValidProgLineString(string str)
{
    regex progLineStringCheck = regex(PROG_LINE_STRING);
    return regex_match(str, progLineStringCheck);
}

bool RegexValidators::isValidCallString(string str)
{
    regex callStringCheck = regex(CALL_STRING);
    return regex_match(str, callStringCheck);
}

bool RegexValidators::isValidProcedureString(string str)
{
    regex procedureStringCheck = regex(PROCEDURE_STRING);
    return regex_match(str, procedureStringCheck);
}

bool RegexValidators::isValidVariableString(string str)
{
    regex variableStringCheck = regex(VARIABLE_STRING);
    return regex_match(str, variableStringCheck);
}

bool RegexValidators::isValidConstantString(string str)
{
    regex constantStringCheck = regex(CONSTANT_STRING);
    return regex_match(str, constantStringCheck);
}

bool RegexValidators::isValidStmtLstString(string str)
{
    regex stmtLstStringCheck = regex(STMTLST_STRING);
    return regex_match(str, stmtLstStringCheck);
}

/******************** Attributes ********************/
bool RegexValidators::isValidProcNameString(string str)
{
    regex procNameStringCheck = regex(PROCNAME_STRING);
    return regex_match(str, procNameStringCheck);
}

bool RegexValidators::isValidStmtNumString(string str)
{
    regex stmtNumStringCheck = regex(STMTNUM_STRING);
    return regex_match(str, stmtNumStringCheck);
}

bool RegexValidators::isValidVarNameString(string str)
{
    regex varNameStringCheck = regex(VARNAME_STRING);
    return regex_match(str, varNameStringCheck);
}

bool RegexValidators::isValidValueString(string str)
{
    regex valueStringCheck = regex(VALUE_STRING);
    return regex_match(str, valueStringCheck);
}

bool RegexValidators::isValidOpenBracketRegex(string str)
{
    regex openBracketRegexCheck = regex(OPEN_BRACKET_REGEX);
    return regex_match(str, openBracketRegexCheck);
}

bool RegexValidators::isValidCloseBracketRegex(string str)
{
    regex closeBracketRegexCheck = regex(CLOSE_BRACKET_REGEX);
    return regex_match(str, closeBracketRegexCheck);
}

bool RegexValidators::isValidOperatorRegex(string str)
{
    regex operatorRegexCheck = regex(OPERATOR_REGEX);
    return regex_match(str, operatorRegexCheck);
}

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

bool RegexValidators::isValidUnderscoreRegex(string str)
{
    regex underscoreRegexCheck = regex(UNDERSCORE_REGEX);
    return regex_match(str, underscoreRegexCheck);
}

bool RegexValidators::isValidIdentWithQuotesRegex(string &str)
{
    regex IdentWithQuotesRegexCheck = regex(IDENT_WITH_QUOTES_REGEX);
    return regex_match(str, IdentWithQuotesRegexCheck);
}

bool RegexValidators::isValidSynonymRegex(string str)
{
    regex synonymRegexCheck(SYNONYM_REGEX);
    return regex_match(str, synonymRegexCheck);
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

bool RegexValidators::isValidDeclarationExtractedRegex(string str)
{
    regex declarationRegex(DECLARATION_EXTRACTED_REGEX);
    return regex_match(str, declarationRegex);
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

bool RegexValidators::isValidCallsRegex(string str)
{
    regex callsRegexCheck(CALLS_REGEX);
    return regex_match(str, callsRegexCheck);
}

bool RegexValidators::isValidNextRegex(string str)
{
    regex nextRegexCheck(NEXT_REGEX);
    return regex_match(str, nextRegexCheck);
}

bool RegexValidators::isValidAffectsRegex(string str)
{
    regex affectsRegexCheck(AFFECTS_REGEX);
    return regex_match(str, affectsRegexCheck);
}

bool RegexValidators::isValidRelCondRegex(string str)
{
    regex relCondRegexCheck(RELCOND_REGEX);
    return regex_match(str, relCondRegexCheck);
}

bool RegexValidators::isValidSuchThatClRegex(string str)
{
    regex suchThatClRegexCheck(SUCH_THAT_Cl_REGEX);
    return regex_match(str, suchThatClRegexCheck);
}

bool RegexValidators::isValidExpressionSpecRegex(string str)
{
    regex expressionSpecCheck(EXPRESSION_SPEC);
    return regex_match(str, expressionSpecCheck);
}

bool RegexValidators::isValidExpressionSpecPartialRegex(string str)
{
    regex expressionSpecPartialRegexCheck(EXPRESSION_SPEC_PARTIAL_REGEX);
    return regex_match(str, expressionSpecPartialRegexCheck);
}

bool RegexValidators::isValidExpressionSpecExactRegex(string str)
{
    regex expressionSpecExactRegexCheck(EXPRESSION_SPEC_EXACT_REGEX);
    return regex_match(str, expressionSpecExactRegexCheck);
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

bool RegexValidators::isValidPatternIfRegex(string str)
{
    regex patternIfRegexCheck(PATTERN_IF_REGEX);
    return regex_match(str, patternIfRegexCheck);
}

bool RegexValidators::isValidPatternRefRegex(string str)
{
    regex patternRefRegexCheck(PATTERNREF_REGEX);
    return regex_match(str, patternRefRegexCheck);
}

bool RegexValidators::isValidPatternCondRegex(string str)
{
    regex patternCondRegexCheck(PATTERNCOND_REGEX);
    return regex_match(str, patternCondRegexCheck);
}

bool RegexValidators::isValidPatternClRegex(string str)
{
    regex patternClRegexCheck(PATTERN_Cl_REGEX);
    return regex_match(str, patternClRegexCheck);
}


/*--------------- With Regex ---------------*/
bool RegexValidators::isValidRefRegex(string str)
{
    regex refRegexCheck(REF_REGEX);
    return regex_match(str, refRegexCheck);
}

bool RegexValidators::isValidAttrCompareRegex(string str)
{
    regex attrCompareRegexCheck(ATTRCOMPARE_REGEX);
    return regex_match(str, attrCompareRegexCheck);
}

bool RegexValidators::isValidAttrCondRegex(string str)
{
    regex attrCondRegexCheck(ATTRCOND_REGEX);
    return regex_match(str, attrCondRegexCheck);
}

bool RegexValidators::isValidWithClRegex(string str)
{
    regex withClRegexCheck(WITH_Cl_REGEX);
    return regex_match(str, withClRegexCheck);
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
