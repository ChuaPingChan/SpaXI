#pragma once
#include "Parser.h"

/*
This class's sole purpose in life is to allow unit testing
for the private methods of the Parser class :O
*/
class ParserChildForTest :
    public Parser
{
public:
    ParserChildForTest();

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

    /**********************************
    * For unit testing, to be removed *
    ***********************************/
    std::vector<std::string> getTokenTest(std::string filename);
    bool matchTokenTest(std::string filename);

};

