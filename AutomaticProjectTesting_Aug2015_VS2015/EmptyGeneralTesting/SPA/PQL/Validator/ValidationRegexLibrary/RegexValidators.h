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
    /******************** Grammar ********************/
    static const string SPACE_0;
    static const string SPACE_1;
    static const string LETTER_REGEX;
    static const string DIGIT_REGEX;
    static const string INTEGER_REGEX;
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

    /*--------------- Pattern Clause Regex ---------------*/
    static const string FACTOR_REGEX;
    static const string EXPRESSION_SPEC;
    static const string PATTERN_REGEX;

    /*--------------- Relationship Clause Regex ---------------*/
    static const string MODIFIES_REGEX;
    static const string USES_REGEX;
    static const string FOLLOWS_REGEX;
    static const string PARENT_REGEX;
    static const string RELREF_REGEX;
    static const string SUCH_THAT_REGEX;
    static const string RELATIONSHIP_KEYWORD_REGEX;

    /*--------------- Select Regex ---------------*/
    static const string RESULTCL_REGEX;
    static const string SELECT_REGEX;

    /*--------------- Select Overall ---------------*/
    static const string SELECT_OVERALL_REGEX;




    /**********
    * Methods *
    **********/
    /******************** Grammar ********************/
    static bool isValidLetterRegex(string str);
    static bool isValidIntegerRegex(string str);
    static bool isValidIdentWithQuotesRegex(string str);
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
    static bool isValidSuchThatRegex(string str);

    /******************** Pattern Regex ********************/
    static bool isValidFactorRegex(string str);
    static bool isValidExpressionSpecRegex(string str);
    static bool isValidPatternRegex(string str);

    /*--------------- Select Regex ---------------*/
    static bool isValidResultClRegex(string str);
    static bool isValidSelectRegex(string str);
    
    /******************** Select Overall ********************/
    static bool isValidSelectOverallRegex(string str);
};
