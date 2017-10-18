#pragma once
#include<string>
#include<regex>
using namespace std;

class RegexValidators
{
public:
    /********
    * REGEX *
    ********/
    /******************** Entity Strings ********************/
    static const string STMT_STRING;
    static const string ASSIGN_STRING;
    static const string WHILE_STRING;
    static const string IF_STRING;
    static const string PROG_LINE_STRING;
    static const string CALL_STRING;
    static const string PROCEDURE_STRING;
    static const string VARIABLE_STRING;
    static const string CONSTANT_STRING;
    static const string STMTLST_STRING;
    
    /******************** Relationships Strings ********************/
    static const string MODIFIES_STRING;
    static const string USES_STRING;
    static const string PARENT_STRING;
    static const string PARENTSTAR_STRING;
    static const string FOLLOWS_STRING;
    static const string FOLLOWSSTAR_STRING;
    static const string CALLS_STRING;
    static const string CALLSSTAR_STRING;
    static const string NEXT_STRING;
    static const string NEXTSTAR_STRING;
    static const string AFFECTS_STRING;
    static const string AFFECTSSTAR_STRING;

    /******************** Attribute Strings ********************/
    static const string PROCNAME_STRING;
    static const string STMTNUM_STRING;
    static const string VARNAME_STRING;
    static const string VALUE_STRING;


    /******************** Grammar ********************/
    static const string SPACE_0;
    static const string SPACE_1;
    static const string OPEN_BRACKET_REGEX;
    static const string CLOSE_BRACKET_REGEX;
    static const string PLUS_REGEX;
    static const string MINUS_REGEX;
    static const string TIMES_REGEX;
    static const string OPERATOR_REGEX;
    static const string LETTER_REGEX;
    static const string DIGIT_REGEX;
    static const string INTEGER_REGEX;
    static const string BOOLEAN_REGEX;
    static const string HASH_REGEX;
    static const string UNDERSCORE_REGEX;
    static const string IDENT_REGEX;
    static const string IDENT_WITH_QUOTES_REGEX;
    static const string SYNONYM_REGEX;
    static const string STMTREF_REGEX;
    static const string ENTREF_REGEX;
    static const string LINEREF_REGEX;
    static const string NAME_REGEX;
    static const string ATTRNAME_REGEX;
    static const string ATTRREF_REGEX;
    static const string ELEM_REGEX;
    static const string TUPLE_REGEX;

    /*--------------- Declaration Regex ---------------*/
    static const string DESIGN_ENTITY_REGEX;

    /*--------------- Relationship Clause Regex ---------------*/
    static const string MODIFIES_FIRSTARG_REGEX;
    static const string MODIFIES_REGEX;
    static const string USES_FIRSTARG_REGEX;
    static const string USES_REGEX;
    static const string FOLLOWS_REGEX;
    static const string PARENT_REGEX;
    static const string CALLS_REGEX;
    static const string NEXT_REGEX;
    static const string AFFECTS_REGEX;
    static const string RELREF_REGEX;
    static const string RELCOND_REGEX;
    static const string SUCH_THAT_Cl_REGEX;
    static const string RELATIONSHIP_KEYWORD_REGEX;

    /*--------------- Pattern Clause Regex ---------------*/
    static const string EXPRESSION_SPEC_EXACT_REGEX;
    static const string EXPRESSION_SPEC_PARTIAL_REGEX;
    static const string EXPRESSION_SPEC;
    static const string PATTERN_ASSIGN_FIRSTARG_REGEX;
    static const string PATTERN_ASSIGN_SECONDARG_REGEX;
    static const string PATTERN_ASSIGN_REGEX;
    static const string PATTERN_WHILE_REGEX;
    static const string PATTERN_IF_REGEX;
    static const string PATTERNREF_REGEX;
    static const string PATTERNCOND_REGEX;
    static const string PATTERN_Cl_REGEX;

    /*--------------- With Regex ---------------*/
    static const string REF_REGEX;
    static const string ATTRCOMPARE_REGEX;
    static const string ATTRCOND_REGEX;
    static const string WITH_Cl_REGEX;

    /*--------------- Select Regex ---------------*/
    static const string RESULTCL_REGEX;
    static const string SELECT_REGEX;

    /*--------------- Select Overall ---------------*/
    static const string SELECT_OVERALL_REGEX;




    /**********
    * Methods *
    **********/
    /******************** Entity Strings ********************/
    static bool isValidStmtString(string str);
    static bool isValidAssignString(string str);
    static bool isValidWhileString(string str);
    static bool isValidIfString(string str);
    static bool isValidProgLineString(string str);
    static bool isValidCallString(string str);
    static bool isValidProcedureString(string str);
    static bool isValdVariableString(string str);
    static bool isValidConstantString(string str);
    static bool isValidStmtLstString(string str);

    /******************** Relationshipss ********************/
    static bool isValidModifiesString(string str);
    static bool isValidUsesString(string str);
    static bool isValidParentString(string str);
    static bool isValidParentStarString(string str);
    static bool isValidFollowsString(string str);
    static bool isValidFollowsStarString(string str);
    static bool isValidCallsString(string str);
    static bool isValidCallsStarString(string str);
    static bool isValidNextString(string str);
    static bool isValidNextStarString(string str);
    static bool isValidAffectsString(string str);
    static bool isValidAffectsStarString(string str);

    /******************** Attributes ********************/
    static bool isValidProcNameString(string str);
    static bool isValidStmtNumString(string str);
    static bool isValidVarNameString(string str);
    static bool isValidValueString(string str);

    /******************** Grammar ********************/
    static bool isValidOpenBracketRegex(string str);
    static bool isValidCloseBracketRegex(string str);
    static bool isValidOperatorRegex(string str);
    static bool isValidLetterRegex(string str);
    static bool isValidIntegerRegex(string str);
    static bool isValidBooleanRegex(string str);
    static bool isValidUnderscoreRegex(string str);
    static bool isValidIdentWithQuotesRegex(string &str);
    static bool isValidSynonymRegex(string str);
    static bool isValidStmtRefRegex(string str);
    static bool isValidEntRefRegex(string str);
    static bool isValidNameRegex(string str);
    static bool isValidAttrNameRegex(string str);
    static bool isValidAttrRefRegex(string str);
    static bool isValidElemRegex(string str);
    static bool isValidTupleRegex(string str);
    static bool isValidEntityRegex(string str);
    
    /******************** Relationship Clause Regex ********************/
    static bool isValidModifiesRegex(string str);
    static bool isValidUsesRegex(string str);
    static bool isValidFollowsRegex(string str);
    static bool isValidParentRegex(string str);
    static bool isValidCallsRegex(string str);
    static bool isValidNextRegex(string str);
    static bool isValidAffectsRegex(string str);
    static bool isValidRelCondRegex(string str);
    static bool isValidSuchThatClRegex(string str);

    /******************** Pattern Regex ********************/
    static bool isValidExpressionSpecRegex(string str);
    static bool isValidExpressionSpecPartialRegex(string str);
    static bool isValidExpressionSpecExactRegex(string str);
    static bool isValidPatternAssignRegex(string str);
    static bool isValidPatternWhileRegex(string str);
    static bool isValidPatternIfRegex(string str);
    static bool isValidPatternRefRegex(string str);
    static bool isValidPatternCondRegex(string str);
    static bool isValidPatternClRegex(string str);

    /*--------------- With Regex ---------------*/
    static bool isValidRefRegex(string str);
    static bool isValidAttrCompareRegex(string str);
    static bool isValidAttrCondRegex(string str);
    static bool isValidWithClRegex(string str);

    /*--------------- Select Regex ---------------*/
    static bool isValidResultClRegex(string str);
    static bool isValidSelectRegex(string str);
    
    /******************** Select Overall ********************/
    static bool isValidSelectOverallRegex(string str);
};
