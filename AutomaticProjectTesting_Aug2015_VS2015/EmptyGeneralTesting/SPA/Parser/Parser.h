#pragma once

#include <string>
#include <fstream>
#include <regex>
#include <stack>

class Parser
{
public:
    Parser();

    void parse(std::string filename);

    /**********************************
    * For unit testing, to be removed *
    ***********************************/
    std::vector<std::string> getTokenTest(std::string filename);
    bool matchTokenTest(std::string filename);

private:

    /************
    * Constants *
    *************/
    static const int INT_INITIAL_STMT_NUMBER;
    static const std::string STRING_EMPTY_STRING;
    
    static const std::regex REGEX_VALID_ENTITY_NAME;
    static const std::regex REGEX_MATCH_CONSTANT;
    static const std::regex REGEX_EXTRACT_NEXT_TOKEN;
    static const std::regex REGEX_EXTRACT_UP_TO_SEMICOLON;
    static const std::regex REGEX_MATCH_PROCEDURE_KEYWORD;
    static const std::regex REGEX_MATCH_WHILE_KEYWORD;
    static const std::regex REGEX_MATCH_OPEN_BRACE;
    static const std::regex REGEX_MATCH_CLOSE_BRACE;
    static const std::regex REGEX_MATCH_SEMICOLON;
    static const std::regex REGEX_EXTRACT_ASSIGNMENT_LHS_RHS;
    //static const std::regex REGEX_VALID_ASSIGNMENT;
    static const std::regex REGEX_EXTRACT_EXPRESSION_LHS_RHS;
    static const std::regex REGEX_VALID_EXPRESSION;
    static const std::regex REGEX_MATCH_EQUAL;
    static const std::regex REGEX_VALID_OPERATOR;

    /********************
    * Member Attributes *
    *********************/
    int _currentStmtNumber;
    std::string _concatenatedSourceCode;
    std::string _nextToken;
    bool _isValidSyntax;
    std::string _errorMessage;
    std::stack<std::string> _callStack;     //Contains only procedures
    std::stack<int> _parentStack;           //Contains only container stmts
    
    /******************
    * Private Methods *
    *******************/
    std::string concatenateLines(std::string filename);
    bool getNextToken();
    bool assertMatchAndIncrementToken(std::regex re);
    bool matchToken(std::regex re);
    std::string extractStringUpToSemicolon();
    bool assertIsValidExpression(std::string expression);

    void parseProgram();
    void parseProcedure();
    void parseStmtList();
    void parseStmt();

    bool assignmentExpected();
    bool whileExpected();
    void parseAssignment();
    void parseWhile();

};

