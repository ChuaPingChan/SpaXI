#pragma once

#include <string>
#include <fstream>
#include <regex>

class Parser
{
public:
    Parser();

    void parse(std::string filename);

    // ***** For unit testing, to be removed *****
    // *******************************************
    std::vector<std::string> getTokenTest(std::string filename);
    bool matchTokenTest(std::string filename);

private:

    /************
    * Constants *
    *************/
    static const int INT_INITIAL_STMT_NUMBER = 0;

    static const std::string STRING_EMPTY_STRING;
    
    static const std::regex REGEX_VALID_ENTITY_NAME;
    static const std::regex REGEX_EXTRACT_NEXT_TOKEN;
    static const std::regex REGEX_VALID_PROCEDURE_KEYWORD;
    static const std::regex REGEX_VALID_WHILE_KEYWORD;
    static const std::regex REGEX_MATCH_OPEN_BRACE;
    static const std::regex REGEX_MATCH_CLOSE_BRACE;
    static const std::regex REGEX_MATCH_SEMICOLON;

    //static const std::string STRING_ERROR_MSG;

    /********************
    * Member Attributes *
    *********************/
    int _currentStmtNumber;
    std::string _concatenatedSourceCode;
    std::string _nextToken;
    bool _isValidSyntax;
    std::string _errorMessage;

    /**********
    * Methods *
    ***********/
    std::string concatenateLines(std::string filename);
    bool getNextToken();
    bool matchToken(std::regex re);

    /*
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

