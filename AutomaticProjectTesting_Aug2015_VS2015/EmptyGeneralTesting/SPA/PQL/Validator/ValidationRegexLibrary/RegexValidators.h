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
    static const string NAME_REGEX;
    static const string SPACE_0;
    static const string SPACE_1;

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

    /*--------------- Select Regex ---------------*/
    static const string SELECT_REGEX;
    static const string RELREF_REGEX;
    static const string SUCH_THAT_REGEX;
    static const string SELECT_OVERALL_REGEX;


    /**********
    * Methods *
    **********/
    /******************** Grammar ********************/
    static bool isValidIntegerRegex(string str);
    static bool isValidIdentWithQuotesRegex(string str);
    /******************** Declaration Regex ********************/
    static bool isValidENTITYRegex(string str);
    static bool isValidSynonymRegex(string str);

    /******************** Select Overall ********************/
    static bool isValidSelectOverallRegex(string str);

    /******************** Pattern Regex ********************/
    static bool isValidExpressionSpec(string str);
    static bool isValidPatternRegex(string str);

    /******************** Such That Regex ********************/
    static bool isValidModifiesRegex(string str);
    static bool isValidUsesRegex(string str);
    static bool isValidFollowsRegex(string str);
    static bool isValidParentRegex(string str);

    /*--------------- Select Regex ---------------*/
    static bool isValidSelectRegex(string str);
    static bool isValidSuchThatRegex(string str);
};
