#include <string>
#include <fstream>
#include <iostream>
#include <stack>
#include <regex>
#include <cassert>

#include "Parser.h"
#include "SyntaxErrorException.h"

// TODO: Remove this output debug string before submission
#include "Windows.h"

using namespace std;

const int Parser::INT_INITIAL_STMT_NUMBER = 1;
const string Parser::STRING_EMPTY_STRING = "";

const regex Parser::REGEX_VALID_ENTITY_NAME = regex("\\s*\\b([A-Za-z][A-Za-z0-9]*)\\b\\s*");
const regex Parser::REGEX_MATCH_CONSTANT = regex("\\s*\\d+\\s*");
const regex Parser::REGEX_EXTRACT_NEXT_TOKEN = regex("\\s*([a-zA-Z][a-zA-Z0-9]*|[^a-zA-Z0-9]|\\d+).*");
//const regex Parser::REGEX_EXTRACT_UP_TO_SEMICOLON = regex("\\s*([a-zA-Z0-9+\\-*/=][a-zA-Z0-9+\\s\\-*/=]*)\\s*;.*");
const regex Parser::REGEX_EXTRACT_UP_TO_SEMICOLON = regex("\\s*([^;\\s][^;]*)\\s*;.*");
const regex Parser::REGEX_MATCH_PROCEDURE_KEYWORD = regex("\\s*procedure\\s*");
const regex Parser::REGEX_MATCH_WHILE_KEYWORD = regex("\\s*while\\s*");
const regex Parser::REGEX_MATCH_OPEN_BRACE = regex("\\s*\\u007B\\s*");
const regex Parser::REGEX_MATCH_CLOSE_BRACE = regex("\\s*\\u007D\\s*");
const regex Parser::REGEX_MATCH_OPEN_BRACKET = regex("\\s*\\(\\s*");
const regex Parser::REGEX_MATCH_CLOSE_BRACKET = regex("\\s*\\)\\s*");
const regex Parser::REGEX_MATCH_SEMICOLON = regex("\\s*;\\s*");

// Char sequence to match should be a statement up to but not including semicolon.
const regex Parser::REGEX_EXTRACT_ASSIGNMENT_LHS_RHS = regex("\\s*([A-Za-z][A-Za-z0-9]*)\\s*=\\s*([a-zA-Z0-9][ a-zA-Z0-9+\\-*/]*)\\s*");
//const regex Parser::REGEX_VALID_ASSIGNMENT = regex("\\s*[A-Za-z][A-Za-z0-9]*\\s*=\\s*[a-zA-z0-9][ a-zA-Z0-9+\\-*/]*\\s*");
const regex Parser::REGEX_EXTRACT_EXPRESSION_LHS_RHS = regex("\\s*([a-zA-Z][a-zA-Z0-9]*|\\d+)\\s*[+\\-*/]\\s*([a-zA-z0-9][ a-zA-Z0-9+\\-*/]*)\\s*");
// Does not confirm the whole expression is valid. Only checks for: [item1][add/minus/times/divide][item2] OR [item1]
const regex Parser::REGEX_VALID_EXPRESSION = regex("\\s*([a-zA-Z][a-zA-Z0-9]*|\\d+)\\s*[+\\-*/]\\s*([a-zA-z][ a-zA-Z0-9+\\-*/]*)\\s*");

const regex Parser::REGEX_MATCH_EQUAL = regex("\\s*=\\s*");
const regex Parser::REGEX_VALID_OPERATOR = regex("\\s*[+\\-*/]\\s*");

Parser::Parser()
{
    _currentStmtNumber = Parser::INT_INITIAL_STMT_NUMBER;
    _concatenatedSourceCode = Parser::STRING_EMPTY_STRING;
    _currentTokenPtr = Parser::STRING_EMPTY_STRING;
    _isValidSyntax = false;
    _errorMessage = string();
    _callStack = stack<string>();
    _parentStack = stack<int>();
}

bool Parser::parse(string filename) {
    // TODO: Implement this when all other methods are tested.
    _isValidSyntax = true;
    concatenateLines(filename);
    parseProgram();
    return _isValidSyntax;
}

bool Parser::concatenateLines(string filename) {
    ifstream infile(filename.c_str());
    
    string stringAccumulator;

    string line;
    while (getline(infile, line)) {
        stringAccumulator += line;
    }
    
    _concatenatedSourceCode = stringAccumulator;
    infile.close();
    return true;
}

// Proceed to next token.
bool Parser::incrCurrentTokenPtr()
{
    smatch match;
    // At the very beginning of a SIMPLE source file, just increment token pointer.
    if (_currentTokenPtr == "" && regex_match(_concatenatedSourceCode, match, Parser::REGEX_EXTRACT_NEXT_TOKEN) && match.size() > 1) {
        _currentTokenPtr = match.str(1);
        return true;
    }
    
    // If at the middle of a SIMPLE source file, discard the first token and move to the next.
    if (regex_match(_concatenatedSourceCode, match, Parser::REGEX_EXTRACT_NEXT_TOKEN) && match.size() > 1) {
        _currentTokenPtr = match.str(1);
        _concatenatedSourceCode.erase(0, match.position(1)+match.length(1));
        if (regex_match(_concatenatedSourceCode, match, Parser::REGEX_EXTRACT_NEXT_TOKEN) && match.size() > 1) {
            _currentTokenPtr = match.str(1);
            return true;
        }
    }
    else {
        _currentTokenPtr = Parser::STRING_EMPTY_STRING;
        return false;
    }
}

// Tokenize a given string into a vector of strings.
vector<string> Parser::tokenizeString(string stringToTokenize)
{
    vector<string> tokenVector;
    smatch match;
    while (regex_match(stringToTokenize, match, Parser::REGEX_EXTRACT_NEXT_TOKEN) && match.size() > 1) {
        tokenVector.push_back(match.str(1));
        stringToTokenize.erase(0, match.position(1) + match.length(1));
    }
    return tokenVector;
}

/*
Returns a string from the current _nextToken to the character before the first semicolon encountered.
Indicate SIMPLE syntax error if no semicolon is encountered in the remaining of the string.
Note that this method does not remove whitespaces and does not move _nextToken forward.
*/
string Parser::extractStringUpToSemicolon() {
    smatch match;
    string targetSubstring;
    if (regex_match(_concatenatedSourceCode, match, Parser::REGEX_EXTRACT_UP_TO_SEMICOLON) && match.size() > 1) {
        targetSubstring = match.str(1);
    } else {
        _isValidSyntax = false;
        OutputDebugString("WARNING: Invalid line, no semicolon found.\n");
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
    if (regex_match(_currentTokenPtr, re)) {
        incrCurrentTokenPtr();
        return true;
    }
    else {
        // TODO: consider throwing exception.
        _isValidSyntax = false;
        OutputDebugString("WARNING: Matching of token failed.\n");
        return false;
    }
}

/*
Matches the given regex with the next token. Does not proceed to the next token.
*/
bool Parser::matchToken(regex re) {
    return regex_match(_currentTokenPtr, re);
}

void Parser::parseProgram() {
    incrCurrentTokenPtr();

    //TODO: put this in a while loop after iteration 1,
    //      when there are multiple procedures.
    parseProcedure();
    OutputDebugString("FINE: End of program reached.\n");
}

// Expects _nextToken to be "procedure" keyword
void Parser::parseProcedure() {
    assertMatchAndIncrementToken(Parser::REGEX_MATCH_PROCEDURE_KEYWORD);
    OutputDebugString("FINE: Parsing procedure.\n");
    
    string procName;
    if (!(matchToken(Parser::REGEX_VALID_ENTITY_NAME))) {
        // TODO: Throw exception?
        _isValidSyntax = false;
        //TODO: Remove this line after determining how to signal user on syntax error.
        OutputDebugString("WARNING: Parsing procedure. Invalid procedure name.\n");
        return;
    }
    procName = _currentTokenPtr;
    _callStack.push(procName);
    // TODO: Add to ProcToIdxMap
    // TODO: Populate CallsTable using _callStack;
    
    incrCurrentTokenPtr();
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
    OutputDebugString("FINE: Entering new statement list.\n");
    parseStmt();    // End of statement characters like ';' and '}' are handled in parseStmt().
    if (matchToken(Parser::REGEX_MATCH_CLOSE_BRACE)) {
        return;
    } else {
        parseStmtList();
    }
}

/*
Parses a statement up to the point after ';' for call and assignment statements,
and '}' for while and if-else statements.
*/
void Parser::parseStmt() {
    _currentStmtNumber++;
    OutputDebugString("FINE: Identifying next statement type...\n");
    
    // TODO: Updates FollowsTable
    // TODO: Update ParentToChildTable (if applicable)
    // TODO: Update ChildToParentTable (if applicable)
    
    // Check statement type and call appropriate function
    // (i.e. call, assignment, if-else, while)
    if (Parser::whileExpected()) {
        parseWhile();
    } else if (Parser::assignmentExpected()) {
        // assignment has to be at the last! If not, it'll wrongly capture while/Call/if keywords
        parseAssignment();
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
Parses an assignment statement. When this method ends,
_currentTokenPtr will be advanced after ';'.
*/
void Parser::parseAssignment() {
    OutputDebugString("FINE: Assignment statement identified.\n");
    // LHS
    assert(matchToken(Parser::REGEX_VALID_ENTITY_NAME));
    string lhsVar = _currentTokenPtr;
    // TODO: Add lhsVar to VarToIdxMap
    // TODO: Update ModTableStmtToVar using currentStmtNumber
    // TODO: Update ModTableStmtToVar using parentStack
    // TODO: Update ModTableProcToVar using callStack
    // TODO: Update ModTableVar using currentStmtNumber
    // TODO: Update ModTableVar using parentStack
    // TODO: Update ModTableVar using callStack
    
    incrCurrentTokenPtr();
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
            incrCurrentTokenPtr();
        }
        // TODO: Remove whitespace in rhsExpression and add to pattern table.
    }
    assertMatchAndIncrementToken(Parser::REGEX_MATCH_SEMICOLON);
}

/*
Asserts that an expression is syntactically valid.
*/
bool Parser::assertIsValidExpression(string expression) {
    OutputDebugString("FINE: Validating expression...\n");
    // Base case
    if (regex_match(expression, Parser::REGEX_VALID_ENTITY_NAME) || regex_match(expression, Parser::REGEX_MATCH_CONSTANT)) {
        OutputDebugString("FINE: Expression is valid.\n");
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
        OutputDebugString("WARNING: Invalid Expression.\n");
        // TODO: Throw exception?
        return false;
    }
    return assertIsValidExpression(leftExpression) && assertIsValidExpression(rightExpression);
}

/*
Parses a while statement. When this method ends,
_currentTokenPtr will be advanced after '}'.
*/
void Parser::parseWhile() {
    OutputDebugString("FINE: While statement identified.\n");
    assertMatchAndIncrementToken(Parser::REGEX_MATCH_WHILE_KEYWORD);
    // TODO: Push currentStmtNumber to parentStack.

    assert(matchToken(Parser::REGEX_VALID_ENTITY_NAME));
    string whileVar = _currentTokenPtr;
    /* TODO
    Update VarToIdxMap
    Update ModTableStmtToVar using currentStmtNumber
    Update ModTableStmtToVar using parentStack
    Update ModTableProcToVar using callStack
    Update ModTableVar using currentStmtNumber
    Update ModTableVar using parentStack
    Update ModTableVar using callStack
    */
    
    assertMatchAndIncrementToken(Parser::REGEX_VALID_ENTITY_NAME);
    assertMatchAndIncrementToken(Parser::REGEX_MATCH_OPEN_BRACE);

    parseStmtList();

    assertMatchAndIncrementToken(Parser::REGEX_MATCH_CLOSE_BRACE);
    // TODO: ParentStack.pop()
}
