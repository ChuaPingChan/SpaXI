#pragma once
#include <regex>
#include "QueryValidator.h"

class QueryValidatorFriend
{
    QueryValidator qv;
public:
    QueryValidatorFriend();
    ~QueryValidatorFriend();

    /*--------------- Validation of Grammar Regex ---------------*/
    bool isValidLetter(string str);
    bool isValidInteger(string str);
    bool isValidSynonym(string str);
    bool isValidStmtRef(string str);
    bool isValidEntRef(string str);
    bool isValidName(string str);

    /*--------------- Splitting Query ---------------*/
    vector<string> tokenize(string query);

    /*--------------- Remove all spaces ---------------*/
    string removeAllSpaces(string str);

    /*--------------- Get string between two delimiters ---------------*/
    string getBetweenTwoStrings(const string & str, const string & firstDelim, const string & secondDelim);

    /*--------------- Check if argument is in a clause ---------------*/
    bool isArgumentInClause(string arg, vector<string> clause);

    ///*--------------- Check if string is an integer ---------------*/
    //bool isIntegerRegexCheck(string arg);

    /*--------------- Validation of Declaration ---------------*/
    bool isValidDeclaration(string str);
    bool isValidEntity(string str);

    /*--------------- Validation of Select ---------------*/
    bool isValidSelect(string str);
//    bool isValidSelectBeginning(string str);
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
    bool isValidFactor(string str);
    bool isValidExpressionSpec(string str);

    bool isValidPattern(string str);

    /*--------------- Insert into QueryTree ---------------*/
    void insertSynonymIntoQueryTree(string type1, string arg1);
    void insertSynonymIntoQueryTree(string type1, string arg1, string type2, string arg2);
    void insertSynonymIntoQueryTree(string type1, string arg1, string type2, string arg2, string type3, string arg3);
};
