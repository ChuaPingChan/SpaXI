#pragma once
#include <string>
#include <vector>
#include <unordered_set>
#include <sstream>
#include <regex>
#include <algorithm>
#include "QueryTree.h"


using namespace std;

class QueryValidatorOld
{
    friend class QueryValidatorFriend;

public:
    QueryValidatorOld();
    ~QueryValidatorOld();

    /******************** Grammar ********************/
    static const string LETTER;
    static const string DIGIT;
    static const string INTEGER;
    static const string HASH;
    static const string UNDERSCORE;
    static const string IDENT;
    static const string SYNONYM;
    static const string STMTREF;
    static const string ENTREF;
    static const string NAME;
    static const string SPACE_0;
    static const string SPACE_1;

    /*--------------- Declaration Regex ---------------*/
    static const string DESIGN_ENTITY_REGEX;

    /*--------------- Pattern Clause Regex ---------------*/
    static const string FACTOR;
    static const string EXPRESSION_SPEC;
    static const string PATTERN_REGEX;

    /*--------------- Relationship Clause Regex ---------------*/
    static const string MODIFIES_REGEX;
    static const string USES_REGEX;
    static const string FOLLOWS_REGEX;
    static const string PARENT_REGEX;

    /*--------------- Select Regex ---------------*/
    static const string SELECT_REGEX;
    static const string RELREF;
    static const string SUCH_THAT_REGEX;
    static const string SELECT_OVERALL_REGEX;

    bool isValidQuery(string query);


private:

    QueryTree* qtInstance;

    unordered_set<string> _synonymBank;   //Contains list of used synonyms
    vector<string> _unvalidatedQueryVector;  //Holds unvalidated stmts retreived from query tree

                                             /*--------------- Splitting Query ---------------*/
    vector<string> tokenize(string query);

    /*--------------- Remove all spaces ---------------*/
    string removeAllSpaces(string str);

    /*--------------- Get string between two delimiters ---------------*/
    string getBetweenTwoStrings(const string & str, const string & firstDelim, const string & secondDelim);

    /*--------------- Check if argument is in a clause ---------------*/
    bool isArgumentInClause(string arg, vector<string> clause);

    /*--------------- Check if string is an integer ---------------*/
    bool isIntegerRegexCheck(string arg);

    /*--------------- Validation of Declaration ---------------*/
    bool isValidDeclaration(string str);
    bool isValidEntity(string str);
    bool isValidSynonym(string str);

    /*--------------- Validation of Select ---------------*/
    bool isValidSelect(string str);
    bool isValidSelectBeginning(string str);
    bool isValidSelectOverallRegex(string str);

    /*--------------- Validation of Such That clauses ---------------*/
    bool isValidModifiesRegex(string str);
    bool isValidUsesRegex(string str);
    bool isValidFollowsRegex(string str);
    bool isValidParentRegex(string str);

    bool isValidModifies(string str);
    bool isValidUses(string str);
    bool isValidFollows(string str);
    bool isValidParent(string str);

    /*--------------- Validation of Pattern ---------------*/
    bool isValidPatternRegex(string str);
    bool isValidPattern(string str);

};

