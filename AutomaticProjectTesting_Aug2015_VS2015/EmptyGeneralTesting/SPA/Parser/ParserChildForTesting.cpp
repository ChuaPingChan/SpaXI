#include <string>
#include <fstream>
#include <iostream>
#include <stack>
#include <regex>
#include <cassert>
#include <vector>

#include "Parser.h"
#include "ParserChildForTesting.h"
#include "SyntaxErrorException.h"

using namespace std;

ParserChildForTest::ParserChildForTest() {
    _currentStmtNumber = ParserChildForTest::INT_INITIAL_STMT_NUMBER;
    _concatenatedSourceCode = ParserChildForTest::STRING_EMPTY_STRING;
    _nextToken = ParserChildForTest::STRING_EMPTY_STRING;
    _isValidSyntax = true;
    _errorMessage = string();
    _callStack = stack<string>();
    _parentStack = stack<int>();
}

string ParserChildForTest::concatenateLines(string filename) {
    return Parser::concatenateLines(filename);
}

bool ParserChildForTest::getNextToken()
{
    return Parser::getNextToken();
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



/*******************************************************************
* Here on are methods for unit testing, all of them                 *
* are to be removed when permanent non-hacky unit test can be done.*
********************************************************************/
vector<string> ParserChildForTest::getTokenTest(string infile) {
    _concatenatedSourceCode = concatenateLines(infile);
    vector<string> accumulatedToken;

    while (getNextToken()) {
        accumulatedToken.push_back(_nextToken);
    }

    return accumulatedToken;
}

bool ParserChildForTest::matchTokenTest(string infile) {
    _concatenatedSourceCode = concatenateLines(infile);

    // Not strictly necessary, but improves readability
    bool methodIsWorkingFine = true;

    // Manually set this when content of input file changes
    const int numOfValues = 4;

    // Manually set this when content of input file changes
    regex regexArray[numOfValues] = {
        ParserChildForTest::REGEX_MATCH_PROCEDURE_KEYWORD,
        ParserChildForTest::REGEX_MATCH_WHILE_KEYWORD,
        ParserChildForTest::REGEX_MATCH_OPEN_BRACE,
        ParserChildForTest::REGEX_MATCH_CLOSE_BRACE
    };

    for (int i = 0; methodIsWorkingFine && (i < numOfValues); i++) {
        getNextToken();
        if (!(regex_match(_nextToken, regexArray[i]))) {
            methodIsWorkingFine = false;
            return false;
        }
    }

    return methodIsWorkingFine;
}