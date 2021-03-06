#pragma once

#include <string>
#include <fstream>
#include <regex>
#include <stack>

#include "../PKB/PKBMain.h"

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
    static const std::regex REGEX_MATCH_BLANK_OR_EMPTY_STRING;
    static const std::regex REGEX_EXTRACT_BRACKET_WRAPPED_CONTENT;
    static const std::regex REGEX_MATCH_EQUAL;
    static const std::regex REGEX_MATCH_OPERATOR;
    static const std::regex REGEX_MATCH_ANYHING;
    static const std::regex REGEX_MATCH_POSSIBLE_WHITESPACE;

    /***********
     * MESSAGE *
     ***********/
    static const std::string MESSAGE_INVALID_ENTITY_NAME;
    static const std::string MESSAGE_MISSING_SEMICOLON;
    static const std::string MESSAGE_INVALID_EXPRESSION;
    static const std::string MESSAGE_INVALID_PROCEDURE_NAME;
    static const std::string MESSAGE_MISSING_OPEN_BRACE;
    static const std::string MESSAGE_MISSING_CLOSE_BRACE;
    static const std::string MESSAGE_MISSING_EQUAL_SIGN;
    static const std::string MESSAGE_MISSING_WHILE_KEYWORD;
    static const std::string MESSAGE_MISSING_IF_KEYWORD;
    static const std::string MESSAGE_MISSING_THEN_KEYWORD;
    static const std::string MESSAGE_MISSING_ELSE_KEYWORD;
    static const std::string MESSAGE_MISSING_CALL_KEYWORD;

    Parser(PKBMain* pkbMainPtr);

    bool parse(std::string filename);

protected:

    /*************
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
    std::unordered_set<int> _prevReachableStmts;    // To store all statements that can arrive at the current statement in one step

    /*********************
     * Protected Methods *
     *********************/

    // Parsing helper methods
    bool concatenateLines(std::string filename);
    bool incrCurrentTokenPtr();
    bool matchToken(std::regex re);
    bool assertMatchAndIncrementToken(std::regex re, std::string errorMsg);
    bool assertMatchWithoutIncrementToken(std::regex re, std::string errorMsg);
    std::string extractBackingStringUpToSemicolon();
    void processAndPopTopFollowStack();
    static std::pair<string, string> splitExpressionLhsRhs(std::string expression);
    bool assertIsValidExpression(std::string expression);
    bool endOfSourceCodeReached();
    void setNextForUpcomingStmts();

    // Predictive methods
    bool assignmentExpected();
    bool whileExpected();
    bool callStmtExpected();
    bool ifStmtExpected();
    bool moreStmtsExistInStmtList();

    // Parse entity methods
    void parseProgram();
    void parseProcedure();
    void parseStmtList();
    void parseStmt();
    void parseAssignment();
    void parseWhileStmt();
    void parseCallStmt();
    void parseIfElseStmt();

    // Utility methods
    static std::vector<std::string> tokenizeString(std::string stringToTokenize);
    static std::string extractNextTokenAndShortenString(std::string &targetString);
    static std::string getFirstTokenInString(const std::string &targetString);
    static std::string removeAllWhitespaces(std::string targetString);
    static bool isBracketedCorrectly(const std::string &expression);
    static std::string trimString(std::string targetString);
};
