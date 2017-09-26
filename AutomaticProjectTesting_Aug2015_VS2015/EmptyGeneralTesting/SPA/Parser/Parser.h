#pragma once

#include <string>
#include <fstream>
#include <regex>
#include <stack>

#include "../PKB/PKBMain.h"

class Parser
{
public:
    /********
    * REGEX *
    *********/

    static const std::regex REGEX_VALID_ENTITY_NAME;
    static const std::regex REGEX_MATCH_CONSTANT;
    static const std::regex REGEX_EXTRACT_NEXT_TOKEN;
    static const std::regex REGEX_EXTRACT_UP_TO_SEMICOLON;
    static const std::regex REGEX_MATCH_PROCEDURE_KEYWORD;
    static const std::regex REGEX_MATCH_WHILE_KEYWORD;
    static const std::regex REGEX_MATCH_OPEN_BRACE;
    static const std::regex REGEX_MATCH_CLOSE_BRACE;
    static const std::regex REGEX_MATCH_OPEN_BRACKET;
    static const std::regex REGEX_MATCH_CLOSE_BRACKET;
    static const std::regex REGEX_MATCH_SEMICOLON;
    static const std::regex REGEX_EXTRACT_EXPRESSION_LHS_RHS;
    static const std::regex REGEX_VALID_EXPRESSION;
    static const std::regex REGEX_MATCH_EQUAL;
    static const std::regex REGEX_VALID_OPERATOR;

    Parser(PKBMain* pkbMainPtr);

    bool parse(std::string filename);

protected:  // TODO: Temporarily use "protected" to ease unit testing.

    /************
    * Constants *
    *************/
    static const int INT_INITIAL_STMT_NUMBER;
    static const std::string STRING_EMPTY_STRING;

    /********************
    * Member Attributes *
    *********************/
    int _currentStmtNumber;
    std::string _concatenatedSourceCode;
    std::string _currentTokenPtr;
    bool _isValidSyntax;
    std::stack<std::string> _callStack;     //Contains only procedures
    std::stack<int> _parentStack;           //Contains only container stmts
    PKBMain* _pkbMainPtr;
    std::stack<std::stack<int>> _stacksOfFollowsStacks;
    /*
    TODO: New attributes for iteration 2.0
        - _currentProcName      //The current procedure being parsed
    */

    /******************
    * Private Methods *
    *******************/
    bool concatenateLines(std::string filename);
    bool incrCurrentTokenPtr();
    std::vector<std::string> tokenizeString(std::string stringToTokenize);
    bool assertMatchAndIncrementToken(std::regex re);
    bool assertMatchWithoutIncrementToken(std::regex re);
    bool matchToken(std::regex re);
    std::string extractStringUpToSemicolon();
    bool assertIsValidExpression(std::string expression);
    std::string removeAllWhitespaces(std::string targetString);
    std::string removeAllBrackets(std::string targetString);
    bool isBracketedCorrectly(std::string expression);
    void processAndPopTopFollowStack();

    bool assignmentExpected();
    bool whileExpected();

    void parseProgram();
    void parseProcedure();
    void parseStmtList();
    void parseStmt();
    void parseAssignment();
    void parseWhile();

};
