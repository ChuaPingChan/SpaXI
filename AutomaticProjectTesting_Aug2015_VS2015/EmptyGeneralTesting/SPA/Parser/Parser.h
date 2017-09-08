#pragma once

#include <string>
#include <fstream>

class Parser
{
public:
    Parser();

    void parse();
    void mainForUnitTest();

    // ***** For unit testing, to be removed *****
    // *******************************************

private:

    const int INT_INITIAL_STMT_NUMBER = 0;
    const std::string STRING_EMPTY_STRING = "";

    int _currentStmtNumber;
    std::string _concatenatedSourceCode;
    std::string _nextToken;
    bool _isValidSyntax;

    std::string concatenateLines(std::string);
    std::string getNextToken();

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

