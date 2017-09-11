#include <string>
#include <fstream>
#include <iostream>
#include <stack>
#include <regex>
#include <cassert>

#include "Parser.h"
#include "SyntaxErrorException.h"

using namespace std;

const int Parser::INT_INITIAL_STMT_NUMBER = 1;
const string Parser::STRING_EMPTY_STRING = "";

const regex Parser::REGEX_VALID_ENTITY_NAME = regex("\\s*\\b([A-Za-z][A-Za-z0-9]*)[^A-Za-z0-9]\\b\\s*");
const regex Parser::REGEX_MATCH_CONSTANT = regex("\\s*\\d+\\s*");
const regex Parser::REGEX_EXTRACT_NEXT_TOKEN = regex("\\s*([a-zA-Z][a-zA-Z0-9]*|[^a-zA-Z0-9]|\\d+).*");
const regex Parser::REGEX_EXTRACT_UP_TO_SEMICOLON = regex("\\A\\s*([a-zA-Z0-9 +\\-*/]+)\\s*;.*");
const regex Parser::REGEX_MATCH_PROCEDURE_KEYWORD = regex("\\s*procedure\\s*");
const regex Parser::REGEX_MATCH_WHILE_KEYWORD = regex("\\s*while\\s*");
const regex Parser::REGEX_MATCH_OPEN_BRACE = regex("\\s*\\u007B\\s*");
const regex Parser::REGEX_MATCH_CLOSE_BRACE = regex("\\s*\\u007D\\s*");
const regex Parser::REGEX_MATCH_SEMICOLON = regex("\\s*;\\s*");

// Char sequence to match should be a statement up to but not including semicolon.
const regex Parser::REGEX_EXTRACT_ASSIGNMENT_LHS_RHS = regex("\\s*([A-Za-z][A-Za-z0-9]*)\\s*=\\s*([a-zA-Z0-9][ a-zA-Z0-9+\\-*/]*)\\s*");
//const regex Parser::REGEX_VALID_ASSIGNMENT = regex("\\s*[A-Za-z][A-Za-z0-9]*\\s*=\\s*[a-zA-z0-9][ a-zA-Z0-9+\\-*/]*\\s*");
const regex Parser::REGEX_EXTRACT_EXPRESSION_LHS_RHS = regex("\\s*([a-zA-Z][a-zA-Z0-9]*|\\d+)\\s*[+\\-*/]\\s*([a-zA-z0-9][ a-zA-Z0-9+\\-*/]*)\\s*");
// Does not confirm the whole expression is valid. Only checks for: [item1][add/minus/times/divide][item2] OR [item1]
const regex Parser::REGEX_VALID_EXPRESSION = regex("\\s*([a-zA-Z][a-zA-Z0-9]*|\\d+)\\s*[+\\-*/]\\s*([a-zA-z][ a-zA-Z0-9+\\-*/]*)\\s*");

const regex Parser::REGEX_MATCH_EQUAL = regex("=");
const regex Parser::REGEX_VALID_OPERATOR = regex("[+\\-*/]");

Parser::Parser()
{
    _currentStmtNumber = Parser::INT_INITIAL_STMT_NUMBER;
    _concatenatedSourceCode = Parser::STRING_EMPTY_STRING;
    _nextToken = Parser::STRING_EMPTY_STRING;
    _isValidSyntax = true;
    _errorMessage = string();
    _callStack = stack<string>();
    _parentStack = stack<int>();
}

void Parser::parse(string filename) {
    // TODO: Implement this when all other methods are tested.
}

string Parser::concatenateLines(string filename) {
    ifstream infile(filename.c_str());
    
    string stringAccumulator;

    string line;
    while (getline(infile, line)) {
        stringAccumulator += line;
    }

    infile.close();
    return stringAccumulator;
}

// Proceed to next token.
bool Parser::getNextToken()
{
    smatch match;
    if (regex_match(_concatenatedSourceCode, match, Parser::REGEX_EXTRACT_NEXT_TOKEN) && match.size() > 1) {
        _nextToken = match.str(1);
        _concatenatedSourceCode.erase(0, match.position(1)+match.length(1));
        return true;
    }
    else {
        _nextToken = Parser::STRING_EMPTY_STRING;
        return false;
    }
}

/*
Returns a string from the current _nextToken to the character before the first semicolon encountered.
Indicate SIMPLE syntax error if no semicolon is encountered in the remaining of the string.
Note that this method does not move _nextToken forward.
*/
string Parser::extractStringUpToSemicolon() {
    smatch match;
    string targetSubstring;
    if (regex_match(_concatenatedSourceCode, match, Parser::REGEX_EXTRACT_UP_TO_SEMICOLON) && match.size() > 1) {
        targetSubstring = match.str(1);
    } else {
        _isValidSyntax = false;
        // TODO: Throw exception?
    }
    return targetSubstring;
}

/*
Asserts that the next token must match the given regex.
If the match is successful, move _nextToken forward and return true.
If match is unsuccessful, indicate syntax error.
*/
bool Parser::assertMatchAndIncrementToken(regex re) {
    if (regex_match(_nextToken, re)) {
        getNextToken();
        return true;
    }
    else {
        // TODO: consider throwing exception.
        _isValidSyntax = false;
        return false;
    }
}

/*
Matches the given regex with the next token. Does not proceed to the next token.
*/
bool Parser::matchToken(regex re) {
    return regex_match(_nextToken, re);
}

void Parser::parseProgram() {
    getNextToken();

    //TODO: put this in a while loop after iteration 1.
    parseProcedure();
}

// Expects _nextToken to be "procedure" keyword
void Parser::parseProcedure() {
    assertMatchAndIncrementToken(Parser::REGEX_MATCH_PROCEDURE_KEYWORD);
    
    string procName;
    if (!(matchToken(Parser::REGEX_VALID_ENTITY_NAME))) {
        // TODO: Throw exception?
        _isValidSyntax = false;
        //TODO: Remove this line after determining how to signal user on syntax error.
        return;
    }
    procName = _nextToken;
    _callStack.push(procName);
    // TODO: Add to ProcToIdxMap
    // TODO: Populate CallsTable using _callStack;

    getNextToken();
    assertMatchAndIncrementToken(Parser::REGEX_MATCH_OPEN_BRACE);
    parseStmtList();
    assertMatchAndIncrementToken(Parser::REGEX_MATCH_CLOSE_BRACE);
    assert(_callStack.top() == procName);
    _callStack.pop();
}

/*
Parses the statment list within a scope. At the end of this method, _nextToken is '}'.
*/
void Parser::parseStmtList() {
    parseStmt();
    assertMatchAndIncrementToken(Parser::REGEX_MATCH_SEMICOLON);
    if (matchToken(Parser::REGEX_MATCH_CLOSE_BRACE)) {
        return;
    } else {
        parseStmtList();
    }
}

/*
Parses a statement. When this method ends, _nextToken is ';'.
*/
void Parser::parseStmt() {
    _currentStmtNumber++;
    // TODO: Updates FollowsTable
    // TODO: Update ParentToChildTable (if applicable)
    // TODO: Update ChildToParentTable (if applicable)

    // Check statement type and call appropriate function
    // (i.e. call, assignment, if-else, while)
    if (Parser::assignmentExpected()) {
        parseAssignment();
    } else if (Parser::whileExpected()) {
        parseWhile();
    }
}

/*
Tells whether the current statement is expected to be an assignment statement or not.
If next token is a varName, assignment statement is expected.
When the method ends, _nextToken is the varName.
*/
bool Parser::assignmentExpected() {
    return matchToken(Parser::REGEX_VALID_ENTITY_NAME);
}

/*
Tells whether the current statement is expected to be a while statement or not.
When the method ends, _nextToken is the 'while' keyword.
*/
bool Parser::whileExpected() {
    return matchToken(Parser::REGEX_MATCH_WHILE_KEYWORD);
}

/*
Parses an assignment statement. When this method ends, _nextToken is ';'.
*/
void Parser::parseAssignment() {
    // LHS
    assert(matchToken(Parser::REGEX_VALID_ENTITY_NAME));
    string lhsVar = _nextToken;
    // TODO: Add lhsVar to VarToIdxMap
    // TODO: Update ModTableStmtToVar using currentStmtNumber
    // TODO: Update ModTableStmtToVar using parentStack
    // TODO: Update ModTableProcToVar using callStack
    // TODO: Update ModTableVar using currentStmtNumber
    // TODO: Update ModTableVar using parentStack
    // TODO: Update ModTableVar using callStack
    
    getNextToken();
    assertMatchAndIncrementToken(Parser::REGEX_MATCH_EQUAL);

    // RHS
    string rhsExpression = extractStringUpToSemicolon();
    if (assertIsValidExpression(rhsExpression)) {
        while (!matchToken(Parser::REGEX_MATCH_SEMICOLON)) {
            if (matchToken(Parser::REGEX_VALID_ENTITY_NAME)) {
                /*
                TODO:
                Update VarToIdxMap
                Update UsesTableStmtToVar using currentStmtNumber
                Update UsesTableStmtToVar using parentStack
                Update UsesProcToVar using callStack
                Update UsesTableVar using currentStmtNumber
                Update UsesTableVar using parentStack
                Update UsesTableVar using callStack
                */
            }
            getNextToken();
        }
        // TODO: Remove whitespace in rhsExpression and add to pattern table.
    }
}

/*
Asserts that an expression is syntactically valid.
*/
bool Parser::assertIsValidExpression(string expression) {
    // Base case
    if (regex_match(expression, Parser::REGEX_VALID_ENTITY_NAME) || regex_match(expression, Parser::REGEX_MATCH_CONSTANT)) {
        return true;
    }

    smatch match;
    string leftExpression;
    string rightExpression;
    if (regex_match(expression, match, Parser::REGEX_EXTRACT_EXPRESSION_LHS_RHS) && match.size() > 2) {
        leftExpression = match.str(1);
        rightExpression = match.str(2);
    } else {
        _isValidSyntax = false;
        // TODO: Throw exception?
        return false;
    }
    return assertIsValidExpression(leftExpression) && assertIsValidExpression(rightExpression);
}

/*
Parses a while statement. When this method ends, _nextToken is ';'.
*/
void Parser::parseWhile() {

}

/*******************************************************************
* Here on are methods for unit testing, all of them                 *
* are to be removed when permanent non-hacky unit test can be done.*
********************************************************************/
vector<string> Parser::getTokenTest(string infile) {
    _concatenatedSourceCode = concatenateLines(infile);
    vector<string> accumulatedToken;

    while (getNextToken()) {
        accumulatedToken.push_back(_nextToken);
    }

    return accumulatedToken;
}

bool Parser::matchTokenTest(string infile) {
    _concatenatedSourceCode = concatenateLines(infile);
    
    // Not strictly necessary, but improves readability
    bool methodIsWorkingFine = true;

    // Manually set this when content of input file changes
    const int numOfValues = 4;

    // Manually set this when content of input file changes
    regex regexArray[numOfValues] = {
        Parser::REGEX_MATCH_PROCEDURE_KEYWORD,
        Parser::REGEX_MATCH_WHILE_KEYWORD,
        Parser::REGEX_MATCH_OPEN_BRACE,
        Parser::REGEX_MATCH_CLOSE_BRACE
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

