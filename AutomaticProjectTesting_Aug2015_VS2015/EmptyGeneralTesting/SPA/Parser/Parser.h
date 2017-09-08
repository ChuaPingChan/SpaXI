#pragma once

#include <string>
#include <fstream>
#include <regex>

class Parser
{
public:
    Parser();

    void parse();
    bool mainForUnitTest();

    // ***** For unit testing, to be removed *****
    // *******************************************

private:

    static const int INT_INITIAL_STMT_NUMBER = 0;
    static const std::string STRING_EMPTY_STRING;

    static const std::regex REGEX_VALID_ENTITY_NAME;
    static const std::regex REGEX_EXTRACT_NEXT_TOKEN;
    static const std::regex REGEX_VALID_PROCEDURE_KEYWORD;
    static const std::regex REGEX_VALID_WHILE_KEYWORD;
    static const std::regex REGEX_MATCH_OPEN_BRACE;
    static const std::regex REGEX_MATCH_CLOSE_BRACE;
    static const std::regex REGEX_MATCH_SEMICOLON;

    int _currentStmtNumber;
    std::string _concatenatedSourceCode;
    std::string _nextToken;
    bool _isValidSyntax;

    void concatenateLines(std::string);
    bool getNextToken();

    /*
    bool matchToken(string regexPattern);

    void parseProgram();
    void parseProcedure();
    void parseStmtList();
    void parseStmt();

    void parseAssignmentStmt();
    void parseWhileStmt();

    int getStmtTypeIdx();
    bool isAssignmentStmt();
    bool isWhileStmt();
    */

};

