#include <string>
#include <fstream>
#include <iostream>
#include <stack>
#include <regex>
#include <cassert>
#include <vector>

#include "Parser.h"
#include "ParserChildForTest.h"
#include "SyntaxErrorException.h"

using namespace std;

/*
This class's sole purpose in life is to allow unit testing
for the private methods of the Parser class :O

DO NOT use this class in the real SPA.
*/
ParserChildForTest::ParserChildForTest() {
    _currentStmtNumber = ParserChildForTest::INT_INITIAL_STMT_NUMBER;
    _concatenatedSourceCode = ParserChildForTest::STRING_EMPTY_STRING;
    _currentTokenPtr = ParserChildForTest::STRING_EMPTY_STRING;
    _isValidSyntax = true;
    _errorMessage = string();
    _callStack = stack<string>();
    _parentStack = stack<int>();
}

bool ParserChildForTest::concatenateLines(string filename) {
    return Parser::concatenateLines(filename);
}

bool ParserChildForTest::incrCurrentTokenPtr()
{
    return Parser::incrCurrentTokenPtr();
}

vector<string> ParserChildForTest::tokenizeString(string stringToTokenize)
{
    return Parser::tokenizeString(stringToTokenize);
}

bool ParserChildForTest::assertMatchAndIncrementToken(std::regex re)
{
    return Parser::assertMatchAndIncrementToken(re);
}

bool ParserChildForTest::matchToken(std::regex re)
{
    return Parser::matchToken(re);
}

std::string ParserChildForTest::extractStringUpToSemicolon()
{
    return Parser::extractStringUpToSemicolon();
}

bool ParserChildForTest::assertIsValidExpression(std::string expression)
{
    return Parser::assertIsValidExpression(expression);
}

std::string ParserChildForTest::removeAllWhitespaces(std::string targetString)
{
    return Parser::removeAllWhitespaces(targetString);
}

bool ParserChildForTest::isBracketedCorrectly(std::string expression)
{
    return Parser::isBracketedCorrectly(expression);
}

void ParserChildForTest::parseProgram()
{
    Parser::parseProgram();
}

void ParserChildForTest::parseProcedure()
{
    Parser::parseProcedure();
}

void ParserChildForTest::parseStmtList()
{
    Parser::parseStmtList();
}

void ParserChildForTest::parseStmt()
{
    Parser::parseStmt();
}

bool ParserChildForTest::assignmentExpected()
{
    return Parser::assignmentExpected();
}

bool ParserChildForTest::whileExpected()
{
    return Parser::whileExpected();
}

void ParserChildForTest::parseAssignment()
{
    Parser::parseAssignment();
}

void ParserChildForTest::parseWhile()
{
    Parser::parseWhile();
}
