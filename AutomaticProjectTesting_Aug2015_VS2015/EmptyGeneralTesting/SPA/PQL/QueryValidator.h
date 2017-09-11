#pragma once
#include <string>
#include <vector>
#include <unordered_set>
#include <sstream>
#include <regex>

using namespace std;

class QueryValidator
{
public:
    QueryValidator();
    ~QueryValidator();

    bool isValidQuery(vector<string> inputVector);
  

    /*--------------- For Unit Testing ---------------*/
    /*--------------- Grammar Regex Test---------------*/
    bool isValidLetterTest(string str);
    bool isValidIntegerTest(string str);
    bool isValidSynonymTest(string str);
    bool isValidStmtRefTest(string str);
    bool isValidEntRefTest(string str);
    bool isValidNameTest(string str);

    /*--------------- Splitting Query Test---------------*/
    vector<string> initialSplitTest(string query);

    /*--------------- Declaration Test---------------*/
    bool isValidEntityTest(string str);
    bool isValidDeclarationTest(string str);
    void stubMethod();  //Just a placeholder

    /*--------------- Pattern Test---------------*/
    bool isValidFactorTest(string str);
    bool isValidExpressionSpecTest(string str);
    bool isValidPatternRegexTest(string str);
    bool isValidPatternTest(string str);

    /*--------------- Relationship Test---------------*/
    bool isValidModifiesRegexTest(string str);
    bool isValidUsesRegexTest(string str);
    bool isValidFollowsRegexTest(string str);
    bool isValidParentRegexTest(string str);

    bool isValidModifiesTest(string str);
    bool isValidUsesTest(string str);
    bool isValidFollowsTest(string str);
    bool isValidParentTest(string str);

    /*--------------- Select Test---------------*/
    bool isValidSelectTest(string str);
    bool isValidSelectOverallRegexTest(string str);
   

    

private: 
    unordered_set<string> _synonymBank;   //Contains list of used synonyms
    vector<string> _unvalidatedQueryVector;  //Holds unvalidated stmts retreived from query tree

    /*--------------- Splitting Query ---------------*/
    vector<string> initialSplit(string query);

    /*--------------- Remove all spaces ---------------*/
    void removeAllSpaces(string str);

    /*--------------- Validation of Declaration ---------------*/
    bool isValidDeclaration(string str);   
    bool isValidEntity(string str);
    bool isValidSynonym(string str);

    /*--------------- Validation of Select ---------------*/
    bool isValidSelect(string str);

    bool isValidModifies(string str);
    bool isValidUses(string str);
    bool isValidFollows(string str);
    bool isvalidParent(string str);
    bool isValidPattern(string str);

    bool isValidSelectOverallRegex(string str);
    bool isValidModifiesRegex(string str);
    bool isValidUsesRegex(string str);
    bool isValidFollowsRegex(string str);
    bool isValidParentRegex(string str);
    bool isValidPatternRegex(string str);
};

