#pragma once

#include <string>
#include <fstream>
#include <regex>
#include <stack>

#include "../PKB/PKBMain.h"

/*
This class's sole purpose in life is to allow unit testing
for the private methods of the Parser class :O

DO NOT use this class in the real SPA.
*/
class Parser
{
public:
    /*********
     * REGEX *
     *********/

    static const std::regex REGEX_VALID_ENTITY_NAME;
    static const std::regex REGEX_VALID_VAR_NAME;
    static const std::regex REGEX_VALID_PROC_NAME;
    static const std::regex REGEX_MATCH_CONSTANT;
    static const std::regex REGEX_EXTRACT_NEXT_TOKEN;
    static const std::regex REGEX_EXTRACT_UP_TO_SEMICOLON;
    static const std::regex REGEX_MATCH_PROCEDURE_KEYWORD;
    static const std::regex REGEX_MATCH_WHILE_KEYWORD;
    static const std::regex REGEX_MATCH_CALL_KEYWORD;
    static const std::regex REGEX_MATCH_IF_KEYWORD;
    static const std::regex REGEX_MATCH_THEN_KEYWORD;
    static const std::regex REGEX_MATCH_ELSE_KEYWORD;
    static const std::regex REGEX_MATCH_OPEN_BRACE;
    static const std::regex REGEX_MATCH_CLOSE_BRACE;
    static const std::regex REGEX_MATCH_OPEN_BRACKET;
    static const std::regex REGEX_MATCH_CLOSE_BRACKET;
    static const std::regex REGEX_MATCH_SEMICOLON;
    static const std::regex REGEX_EXTRACT_BRACKET_WRAPPED_CONTENT;
    static const std::regex REGEX_MATCH_EQUAL;
    static const std::regex REGEX_VALID_OPERATOR;

    Parser(PKBMain* pkbMainPtr);

    bool parse(std::string filename);

protected:

    /************
    * Constants *
    *************/
    static const int INT_INITIAL_STMT_NUMBER;
    static const std::string STRING_EMPTY_STRING;
    static const int INT_INITIAL_PROC_INDEX;

    /*********************
     * Member Attributes *
     *********************/
    int _currentStmtNumber;
    std::string _concatenatedSourceCode;
    std::string _currentTokenPtr;
    bool _isValidSyntax;
    std::stack<int> _parentStack;           //Contains only container stmts
    PKBMain* _pkbMainPtr;
    std::stack<std::stack<int>> _stackOfFollowsStacks;     // To set Follows relation in PKB
    std::string _currentProcName;    //The index of the current procedure being parsed. Needed by set Calls relation
    std::stack<pair<int,int>> _ifElseStmtExitPointsStack;   // To set next after exiting if-else statement
    std::stack<int> _whileStmtStack;
    std::stack<int> _ifElseStmtStack;

    /*********************
     * Protected Methods *
     *********************/
    bool concatenateLines(std::string filename);
    bool incrCurrentTokenPtr();
    bool endOfSourceCodeReached();
    std::vector<std::string> tokenizeString(std::string stringToTokenize);
    bool assertMatchAndIncrementToken(std::regex re);
    bool assertMatchWithoutIncrementToken(std::regex re);
    bool matchToken(std::regex re);
    std::string extractStringUpToSemicolon();
    bool assertIsValidExpression(std::string expression);
    std::string removeAllWhitespaces(std::string targetString);
    bool isBracketedCorrectly(std::string expression);
    void processAndPopTopFollowStack();
    static std::pair<string, string> splitExpressionLhsRhs(std::string expression);

    bool assignmentExpected();
    bool whileExpected();
    bool callStmtExpected();
    bool ifStmtExpected();

    void parseProgram();
    void parseProcedure();
    void parseStmtList();
    void parseStmt();
    void parseAssignment();
    void parseWhileStmt();
    void parseCallStmt();
    void parseIfStmt();

};
