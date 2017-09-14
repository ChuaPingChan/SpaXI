#pragma once
#include "Parser.h"

/*
This class's sole purpose in life is to allow unit testing
for the private methods of the Parser class :O

DO NOT use this class in the real SPA.
*/
class ParserChildForTest :
    public Parser
{
public:
    ParserChildForTest();

    bool concatenateLines(std::string filename);
    bool incrCurrentTokenPtr();
    std::vector<std::string> tokenizeString(std::string stringToTokenize);
    bool assertMatchAndIncrementToken(std::regex re);
    bool matchToken(std::regex re);
    std::string extractStringUpToSemicolon();
    bool assertIsValidExpression(std::string expression);
    std::string removeAllWhitespaces(std::string targetString);
    bool isBracketedCorrectly(std::string expression);

    void parseProgram();
    void parseProcedure();
    void parseStmtList();
    void parseStmt();

    bool assignmentExpected();
    bool whileExpected();
    void parseAssignment();
    void parseWhile();

};

