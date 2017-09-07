#pragma once

#include <string>

class Parser
{
public:
    Parser();

    void parse();

private:
    int _currentStmtNumber;
    std::string _nextToken;

    /*
    std::string getNextToken();
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

