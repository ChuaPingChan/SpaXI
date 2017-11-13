#include <string>
#include <fstream>
#include <iostream>
#include <stack>
#include <regex>
#include <cassert>

#include "Parser.h"
#include "SyntaxErrorException.h"
#include "../PKB/PKBMain.h"
#include "Windows.h"    // For debugging purposes

using namespace std;

const int Parser::INT_INITIAL_STMT_NUMBER = 0;
const string Parser::STRING_EMPTY_STRING = "";
const int Parser::INT_INITIAL_PROC_INDEX = 0;

/*********
 * REGEX *
 *********/
const regex Parser::REGEX_VALID_ENTITY_NAME = regex("\\s*\\b([A-Za-z][A-Za-z0-9]*)\\b\\s*");
const regex Parser::REGEX_VALID_VAR_NAME = Parser::REGEX_VALID_ENTITY_NAME;
const regex Parser::REGEX_VALID_PROC_NAME = Parser::REGEX_VALID_ENTITY_NAME;
const regex Parser::REGEX_MATCH_CONSTANT = regex("\\s*\\d+\\s*");
const regex Parser::REGEX_EXTRACT_NEXT_TOKEN = regex("\\s*([a-zA-Z][a-zA-Z0-9]*|[^a-zA-Z0-9]|\\d+)[^]*");
const regex Parser::REGEX_EXTRACT_UP_TO_SEMICOLON = regex("\\s*([^;\\s][^;]*)\\s*;[^]*");
const regex Parser::REGEX_MATCH_PROCEDURE_KEYWORD = regex("\\s*procedure\\s*");
const regex Parser::REGEX_MATCH_WHILE_KEYWORD = regex("\\s*while\\s*");
const regex Parser::REGEX_MATCH_CALL_KEYWORD = regex("\\s*call\\s*");
const regex Parser::REGEX_MATCH_IF_KEYWORD = regex("\\s*if\\s*");
const regex Parser::REGEX_MATCH_THEN_KEYWORD = regex("\\s*then\\s*");
const regex Parser::REGEX_MATCH_ELSE_KEYWORD = regex("\\s*else\\s*");
const regex Parser::REGEX_MATCH_OPEN_BRACE = regex("\\s*\\u007B\\s*");
const regex Parser::REGEX_MATCH_CLOSE_BRACE = regex("\\s*\\u007D\\s*");
const regex Parser::REGEX_MATCH_OPEN_BRACKET = regex("\\s*\\(\\s*");
const regex Parser::REGEX_MATCH_CLOSE_BRACKET = regex("\\s*\\)\\s*");
const regex Parser::REGEX_MATCH_SEMICOLON = regex("\\s*;\\s*");
const regex Parser::REGEX_MATCH_BLANK_OR_EMPTY_STRING = regex("\\s*");
const regex Parser::REGEX_MATCH_ANYHING = regex("[^]");
const regex Parser::REGEX_MATCH_POSSIBLE_WHITESPACE = regex("\\s*");

// Char sequence to match should be a statement up to but not including semicolon.
// To extract contents within a wrapping outside bracket. Having outside bracket is assumed.
const regex Parser::REGEX_EXTRACT_BRACKET_WRAPPED_CONTENT = regex("\\s*\\(([^()]+|[^()]*\\([^]+\\)[^()]*)\\)\\s*");
const regex Parser::REGEX_MATCH_EQUAL = regex("\\s*=\\s*");
const regex Parser::REGEX_MATCH_OPERATOR = regex("\\s*[+\\-*/]\\s*");

/***********
 * MESSAGE *
 ***********/
const string Parser::MESSAGE_INVALID_ENTITY_NAME = "Invalid entity name.";
const string Parser::MESSAGE_MISSING_SEMICOLON = "Missing semicolon.";
const string Parser::MESSAGE_INVALID_EXPRESSION = "Invalid expression.";
const string Parser::MESSAGE_INVALID_PROCEDURE_NAME = "Invalid procedure name";
const string Parser::MESSAGE_MISSING_OPEN_BRACE = "Missing open-brace.";
const string Parser::MESSAGE_MISSING_CLOSE_BRACE = "Missing close-brace.";
const string Parser::MESSAGE_MISSING_EQUAL_SIGN = "Assignment expected. Missing equal sign.";
const string Parser::MESSAGE_MISSING_WHILE_KEYWORD = "While-statement expected. Missing 'while' keyword.";
const string Parser::MESSAGE_MISSING_IF_KEYWORD = "If-statement expected. Missing 'if' keyword.";
const string Parser::MESSAGE_MISSING_THEN_KEYWORD = "Missing 'then' keyword.";
const string Parser::MESSAGE_MISSING_ELSE_KEYWORD = "Missing 'else' keyword.";
const string Parser::MESSAGE_MISSING_CALL_KEYWORD = "Missing 'call' keyword.";

Parser::Parser(PKBMain* pkbMainPtr)
{
    _currentStmtNumber = Parser::INT_INITIAL_STMT_NUMBER;
    _concatenatedSourceCode = Parser::STRING_EMPTY_STRING;
    _currentTokenPtr = Parser::STRING_EMPTY_STRING;
    _isValidSyntax = true;
    _parentStack = stack<int>();
    _pkbMainPtr = pkbMainPtr;
    _stackOfFollowsStacks = stack<stack<int>>();
    _currentProcName = Parser::STRING_EMPTY_STRING;
    _prevReachableStmts = unordered_set<int>();
}

/*
    Parses a SIMPLE source code. Returns false if syntax error is detected.
*/
bool Parser::parse(string filename) {
    _isValidSyntax = true;
    concatenateLines(filename);
    parseProgram();

    _pkbMainPtr->startProcessComplexRelations();

    return _isValidSyntax;
}

/*
    Concatenates the lines of a given filepath and store the concatenated string
    in the _concatenatedSourceCode variable.
*/
bool Parser::concatenateLines(string filename) {
    ifstream infile(filename.c_str());

    string stringAccumulator;

    string line;
    while (getline(infile, line)) {
        stringAccumulator += line;
    }

    _concatenatedSourceCode = regex_replace(stringAccumulator, regex("\\s\\s+"), " ");
    infile.close();
    return true;
}

/*
    Proceed to next token.
    Returns true if token is incremented successfully.
    Returns false when the end of _concatenatedSourceCode is reached.
*/
bool Parser::incrCurrentTokenPtr()
{
    smatch match;
    // At the very beginning of a SIMPLE source file, just increment token pointer.
    if (_currentTokenPtr == ""
        && regex_match(_concatenatedSourceCode, match, Parser::REGEX_EXTRACT_NEXT_TOKEN)
        && match.size() > 1)
    {
        _currentTokenPtr = match.str(1);
        return true;
    }

    // If at the middle of a SIMPLE source file, discard the first token and move to the next.
    if (regex_match(_concatenatedSourceCode, match, Parser::REGEX_EXTRACT_NEXT_TOKEN) && match.size() > 1) {
        _currentTokenPtr = match.str(1);
        _concatenatedSourceCode.erase(0, match.position(1) + match.length(1));
        if (regex_match(_concatenatedSourceCode, match, Parser::REGEX_EXTRACT_NEXT_TOKEN) && match.size() > 1) {
            _currentTokenPtr = match.str(1);
            return true;
        }
    } else {
        _currentTokenPtr = Parser::STRING_EMPTY_STRING;
        return false;
    }
}

/*
    Given a string, this method extracts the foremost token, remove it from the string
    reference and returns the token. If no token is left in the given string, an empty
    string is returned.
*/
std::string Parser::extractNextTokenAndShortenString(std::string &targetString)
{
    smatch match;
    string token;
    if (regex_match(targetString, match, Parser::REGEX_EXTRACT_NEXT_TOKEN) && match.size() > 1)
    {
        token = match.str(1);
        targetString.erase(0, match.position(1) + match.length(1));
    }
    return token;
}

/*
    Given a string, this method extracts and returns the foremost token. If no token is left in the
    given string, an empty string is returned.
*/
std::string Parser::getFirstTokenInString(const std::string &targetString)
{
    smatch match;
    string token;
    if (regex_match(targetString, match, Parser::REGEX_EXTRACT_NEXT_TOKEN) && match.size() > 1)
        token = match.str(1);
    return token;
}

/*
    Checks if end of the source code has been reached.
    Precondition:
    - Source code has to be concatenated into _concatenatedSourceCode.
*/
bool Parser::endOfSourceCodeReached() {
    return regex_match(_concatenatedSourceCode, regex("\\s*"));
}

/*
    If there are statements coming up next, set Next relation using _prevReachableStmts and clear it
*/
void Parser::setNextForUpcomingStmts()
{
    if (moreStmtsExistInStmtList()) {
        for (int prevReachableStmt : _prevReachableStmts) {
            _pkbMainPtr->setNext(prevReachableStmt, _currentStmtNumber + 1);
        }
        _prevReachableStmts.clear();
    }
}

/*
    Tokenize a given string into a vector of strings.
*/
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
    Returns a string from the current _currentTokenPtr to the character before the first semicolon encountered.
    Indicate SIMPLE syntax error if no semicolon is encountered in the remaining of the string.
    This method assumes there's a semicolon ahead in the _concatenatedSourceCode.
    Note that this method does not remove whitespaces and does not move _currentTokenPtr forward.
*/
string Parser::extractBackingStringUpToSemicolon() {
    smatch match;
    string targetSubstring;
    if (regex_match(_concatenatedSourceCode, match, Parser::REGEX_EXTRACT_UP_TO_SEMICOLON) && match.size() > 1) {
        targetSubstring = match.str(1);
    } else {
        cerr << "Line " << _currentStmtNumber << ": " << Parser::MESSAGE_MISSING_SEMICOLON;
        exit(EXIT_SUCCESS);
        _isValidSyntax = false;
    }
    return targetSubstring;
}

/*
    Asserts that the next token must match the given regex.
    If the match is successful, move current token pointer forward and return true.
    If match is unsuccessful, errMsg is printed and the system will be exited.
*/
bool Parser::assertMatchAndIncrementToken(regex re, string errMsg) {
    if (regex_match(_currentTokenPtr, re)) {
        incrCurrentTokenPtr();
        return true;
    } else {
        cerr << "Line " << _currentStmtNumber << ": " << errMsg;
        exit(EXIT_SUCCESS);
        _isValidSyntax = false;
        return false;
    }
}

/*
    Asserts that the next token must match the given regex.
    Does not move the current token pointer forward.
    If match is unsuccessful, errMsg is printed and the system will be exited.
*/
bool Parser::assertMatchWithoutIncrementToken(regex re, string errMsg) {
    if (regex_match(_currentTokenPtr, re)) {
        return true;
    } else {
        cerr << "Line " << _currentStmtNumber << ": " << errMsg;
        exit(EXIT_SUCCESS);
        _isValidSyntax = false;
        return false;
    }
}

/*
    Matches the given regex with the next token.
    Does not move the current token pointer forward.
*/
bool Parser::matchToken(regex re) {
    return regex_match(_currentTokenPtr, re);
}

void Parser::parseProgram() {
    incrCurrentTokenPtr();

    while (!endOfSourceCodeReached() && _isValidSyntax) {   //While not at the end of _concatednatedSourceCode
        parseProcedure();
    }
}

/*
    Parses a procedure.
    Expects _currentTokenPtr to be "procedure" keyword.
    When this method ends, _currentTokenPtr will be one token past the close
    brace of the procedure.
*/
void Parser::parseProcedure() {
    assertMatchAndIncrementToken(Parser::REGEX_MATCH_PROCEDURE_KEYWORD, Parser::MESSAGE_INVALID_PROCEDURE_NAME);

    string procName;
    if (!(matchToken(Parser::REGEX_VALID_ENTITY_NAME))) {
        cerr << "Line " << _currentStmtNumber << ": " << Parser::MESSAGE_INVALID_ENTITY_NAME;
        exit(EXIT_SUCCESS);
        _isValidSyntax = false;
        return;
    }
    procName = _currentTokenPtr;
    // PKB: Add to ProcToIdxMap
    _pkbMainPtr->addProcedure(procName);
    _currentProcName = procName;

    incrCurrentTokenPtr();
    assertMatchAndIncrementToken(Parser::REGEX_MATCH_OPEN_BRACE, Parser::MESSAGE_MISSING_OPEN_BRACE);
    // Add new stmtList stack to follows stack
    stack<int>* newFollowsStack = new stack<int>();
    _stackOfFollowsStacks.push(*newFollowsStack);

    parseStmtList();

    assertMatchAndIncrementToken(Parser::REGEX_MATCH_CLOSE_BRACE, Parser::MESSAGE_MISSING_CLOSE_BRACE);
    _prevReachableStmts.clear();    // NextGraph is not cross-procedure
    processAndPopTopFollowStack();
}

/*
    Parses the statment list within a scope. At the end of this method, _currentTokenPtr is '}'.
*/
void Parser::parseStmtList() {
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

    // Push current statement to top of the top followsStack
    _stackOfFollowsStacks.top().push(_currentStmtNumber);

    _pkbMainPtr->addStmtToProc(_currentStmtNumber, _currentProcName);

    // Set parent child relation. 0 if no parent.
    if (_parentStack.empty()) {
        (*_pkbMainPtr).setParentChildRel(0, _currentStmtNumber);
    } else {
        (*_pkbMainPtr).setParentChildRel(_parentStack.top(), _currentStmtNumber);
    }

    // Check statement type and call appropriate function
    // (i.e. call, assignment, if-else, while)
    if (Parser::whileExpected()) {
        parseWhileStmt();
    } else if (Parser::callStmtExpected()) {
        parseCallStmt();
    } else if (Parser::ifStmtExpected()) {
        parseIfElseStmt();
    } else {
        // assignment has to be at the last! If not, it'll wrongly capture while/Call/if keywords as variable names
        // assert(Parser::assignmentExpected());    // Comment out for submission. For debugging only.
        parseAssignment();
    }
    setNextForUpcomingStmts();
}

/*
    Tells whether the current statement is expected to be an assignment statement or not.
    If next token is a varName, assignment statement is expected.
    When the method ends, _currentTokenPtr is the varName.
*/
bool Parser::assignmentExpected() {
    return matchToken(Parser::REGEX_VALID_ENTITY_NAME);
}

/*
    Tells whether the current statement is expected to be a while statement or not.
    When the method ends, _currentTokenPtr is the 'while' keyword.
*/
bool Parser::whileExpected() {
    return matchToken(Parser::REGEX_MATCH_WHILE_KEYWORD);
}

/*
    Tells whether the current statement is expected to be a call statement or not.
    When the method ends, _currentTokenPtr is the 'call' keyword.
*/
bool Parser::callStmtExpected() {
    return matchToken(Parser::REGEX_MATCH_CALL_KEYWORD);
}

/*
    Tells whether the current statement is expected to be an if-statement or not.
    When the method ends, _currentTokenPtr is the 'if' keyword.
*/
bool Parser::ifStmtExpected() {
    return matchToken(Parser::REGEX_MATCH_IF_KEYWORD);
}

/*
    Tells whether there is an upcoming statement starting from the next token.
    Does not move _currentTokenPtr forward.
*/
bool Parser::moreStmtsExistInStmtList()
{
    /*
        If the upcoming token is '}', it means there are no more statement
        in a given container.
    */
    return !(matchToken(Parser::REGEX_MATCH_CLOSE_BRACE));
}

/*
    Parses an assignment statement. When this method ends,
    _currentTokenPtr will be advanced after ';'.
*/
void Parser::parseAssignment() {
    _pkbMainPtr->addAssignmentStmt(_currentStmtNumber);

    // Process LHS
    assertMatchWithoutIncrementToken(Parser::REGEX_VALID_ENTITY_NAME, Parser::MESSAGE_INVALID_ENTITY_NAME);
    string lhsVar = _currentTokenPtr;

    /*
        PKB:
        Add lhsVar to VarToIdxMap
        Update ModTableStmtToVar using currentStmtNumber
        Update ModTableStmtToVar using parentStack
        Update ModTableProcToVar using _currentProcName
        Update ModTableVar using currentStmtNumber
        Update ModTableVar using parentStack
    */
    _pkbMainPtr->addVariable(lhsVar);
    _pkbMainPtr->setModTableStmtToVar(_currentStmtNumber, lhsVar);
    if (!_parentStack.empty()) {
        stack<int> parentStackCopy = _parentStack;
        while (!parentStackCopy.empty()) {
            int parentStmt = parentStackCopy.top();
            _pkbMainPtr->setModTableStmtToVar(parentStmt, lhsVar);
            parentStackCopy.pop();
        }
    }
    _pkbMainPtr->setModTableProcToVar(_currentProcName, lhsVar);

    incrCurrentTokenPtr();
    assertMatchAndIncrementToken(Parser::REGEX_MATCH_EQUAL, Parser::MESSAGE_MISSING_EQUAL_SIGN);

    // Process RHS
    string rhsExpression = extractBackingStringUpToSemicolon();
    if (assertIsValidExpression(rhsExpression)) {
        while (!matchToken(Parser::REGEX_MATCH_SEMICOLON)) {
            if (matchToken(Parser::REGEX_VALID_ENTITY_NAME)) {
                string var = _currentTokenPtr;
                /*
                    PKB:
                    Update VarToIdxMap
                    Update UsesTableStmtToVar using currentStmtNumber
                    Update UsesTableStmtToVar using parentStack
                    Update UsesProcToVar using _currentProcName
                    Update UsesTableVar using currentStmtNumber
                    Update UsesTableVar using parentStack
                */
                _pkbMainPtr->addVariable(var);
                _pkbMainPtr->setUseTableStmtToVar(_currentStmtNumber, var);
                if (!_parentStack.empty()) {
                    stack<int> parentStackCopy = _parentStack;
                    while (!parentStackCopy.empty()) {
                        int parentStmt = parentStackCopy.top();
                        _pkbMainPtr->setUseTableStmtToVar(parentStmt, var);
                        parentStackCopy.pop();
                    }
                }
                _pkbMainPtr->setUseTableProcToVar(_currentProcName, var);

            } else if (matchToken(Parser::REGEX_MATCH_CONSTANT)) {
                int constant = stoi(_currentTokenPtr);
                _pkbMainPtr->addConstant(constant);
            }
            incrCurrentTokenPtr();
        }
        // PKB: Add LHS var and RHS expression (without whitespace) to pattern table.
        string rhsExpressionNoWhitespace = removeAllWhitespaces(rhsExpression);
        _pkbMainPtr->setPatternRelation(_currentStmtNumber, lhsVar, rhsExpressionNoWhitespace);
    }
    // Update _prevReachableStmts
    assert(_prevReachableStmts.empty());
    _prevReachableStmts.insert(_currentStmtNumber);
    assertMatchAndIncrementToken(Parser::REGEX_MATCH_SEMICOLON, Parser::MESSAGE_MISSING_SEMICOLON);
}

/*
    Asserts that an expression is syntactically valid.
*/
bool Parser::assertIsValidExpression(string expression) {
    const regex REGEX_MATCH_BRACKETED_ENTITY = regex("\\s*\\(\\s*\\b([A-Za-z][A-Za-z0-9]*)\\b\\s*\\)\\s*");

    expression = Parser::trimString(expression);

    /*
        Check for bracket correctness. Just for redundancy.
        Does not guarantee bracketing is correct, just counting.
        e.g. "4 ( + 3)" will be evaluated as correct even though it's wrong.
    */
    if (!isBracketedCorrectly(expression)) {
        return false;
    }

    // Base case
    if (regex_match(expression, Parser::REGEX_VALID_ENTITY_NAME)
        || regex_match(expression, REGEX_MATCH_BRACKETED_ENTITY)
        || regex_match(expression, Parser::REGEX_MATCH_CONSTANT))
    {
        return true;
    }

    string leftExpression;
    string rightExpression;
    pair<string, string> lhsRhsExpr = Parser::splitExpressionLhsRhs(expression);
    if (lhsRhsExpr != pair<string, string>()) {
        leftExpression = lhsRhsExpr.first;
        rightExpression = lhsRhsExpr.second;
    } else {
        cerr << "Line " << _currentStmtNumber << ": " << Parser::MESSAGE_INVALID_EXPRESSION;
        exit(EXIT_SUCCESS);
        _isValidSyntax = false;
        return false;
    }

    if (!rightExpression.empty()) {
        return assertIsValidExpression(leftExpression) && assertIsValidExpression(rightExpression);
    } else {
        return assertIsValidExpression(leftExpression);
    }
}

/*
    Splits an expression into two parts, namely the left expression and right expression.

    For the following forms:
    "3 + 3 - 2"         ==> "3" and "3 - 2"
    "(2 + 3) + 6 - 7"   ==> "2 + 3" and "6 - 7"
    "2 + (6 - 7)"       ==> "2" and "(6 - 7)"
    "(2 + 3) + (6 - 7)" ==> "2 + 3" and "(6 - 7)"

    If expression is surrounded by othermost bracket:
    "((2 + 3) + (6 - 7))" ==> "(2 + 3) + (6 - 7)" and ""
    Notice that the right expression is empty

    If the format of the expression given is not splittable as above, an empty pair
    of strings will be returned.
*/
std::pair<string, string> Parser::splitExpressionLhsRhs(std::string expression)
{
    string operatorRegex = "[+\\-*/]";
    string possibleWhitespaceRegex = "\\s*";
    string extractEntityRegex = "([A-Za-z][A-Za-z0-9]*|\\d+)";
    string anyCharRegex = "[^]";
    string extractRemainingRegex = "(" + anyCharRegex + "+)";

    regex REGEX_CASE1_EXTRACTOR = regex(possibleWhitespaceRegex
        + extractEntityRegex
        + possibleWhitespaceRegex
        + operatorRegex
        + possibleWhitespaceRegex
        + extractRemainingRegex);

    expression = Parser::trimString(expression);

    smatch match;
    string leftExpression;
    string rightExpression;
    if (regex_match(expression, match, REGEX_CASE1_EXTRACTOR) && match.size() > 2) {
        /*
            CASE 1:
            When the left expression has no brackets. E.g "2 + (10 * 3)", "2 + 10"
        */
        leftExpression = match.str(1);
        rightExpression = match.str(2);
        return pair<string, string>(leftExpression, rightExpression);
    } else if (Parser::getFirstTokenInString(expression) == "(") {
        /*
            CASE 2:
            When the left expression is bracketed.
            E.g. "(2 + 3) + 4", "(2 + 3) + (4 + 10)", "((2 + 3)) + ((6 - 7))"

            Extracts the string starting from after an open bracket, to the last character
            before the matching close bracket. Returns an empty string if matching close
            bracket is not found.

            Pre-condition:
            - First non-whitespace character of targetString is '('

            Example:
            - Given "(3 + (5 * 4) - 2)", the function should return "3 + (5 * 4) - 2"
        */
        string stringInMatchingBracket;
        stack<char> openBracketStack;
        bool matchingBracketFound = false;

        openBracketStack.push(expression[0]);
        expression.erase(expression.begin());
        for (string::iterator charIter = expression.begin();
            charIter != expression.end() && !matchingBracketFound;)
        {
            if (*charIter == '(') {
                openBracketStack.push(*charIter);
            } else if (*charIter == ')') {
                openBracketStack.pop();
                if (openBracketStack.empty()) {
                    matchingBracketFound = true;
                }
            }

            if (!matchingBracketFound) {    // Don't append if token is matching-')'
                stringInMatchingBracket.push_back(*charIter);
            }

            charIter = expression.erase(charIter);     // Processed char required to be removed by later processes
        }

        if (matchingBracketFound) {
            leftExpression = stringInMatchingBracket;
        } else {
            /*
                Leave leftExpression empty if
                1. No matching bracket encountered
                2. No non-whitespace character within bracket (e.g. "(  )")
            */
        }

        string token = Parser::extractNextTokenAndShortenString(expression);
        if (matchingBracketFound && !regex_match(token, Parser::REGEX_MATCH_POSSIBLE_WHITESPACE)
            && !regex_match(token, Parser::REGEX_MATCH_OPERATOR)) {
            // If there are non-whitespace characters that are not operators after ')' -> cannot split
            leftExpression.clear();
            rightExpression.clear();
        } else if (matchingBracketFound && !token.empty()) {
            rightExpression = Parser::trimString(expression);
        }
        return pair<string, string>(leftExpression, rightExpression);
    } else {
        return pair<string, string>();
    }
}

std::string Parser::trimString(std::string targetString)
{
    regex extractTrimmedStringRegex = regex("\\s*([^]*)\\s*");
    smatch match;
    string trimmedString;
    if (regex_match(targetString, match, extractTrimmedStringRegex) && match.size() > 1)
        trimmedString = match.str(1);
    return trimmedString;
}

/*
    Removes all the whitespace in a given string
*/
string Parser::removeAllWhitespaces(string targetString)
{
    return regex_replace(targetString, regex("\\s"), "");
}

/*
    Checks if the brackets in a given string pairs up properly.
    Does not ensure correctness other than brackets pairing.
*/
bool Parser::isBracketedCorrectly(const std::string &expression)
{
    stack<char> openBracketStack;
    string targetString = removeAllWhitespaces(expression);
    for (int i = 0; i < targetString.size(); i++) {
        switch (targetString[i]) {
        case '(':
            openBracketStack.push(targetString[i]);
            break;
        case ')':
            if (openBracketStack.empty()) {
                return false;
            } else {
                openBracketStack.pop();
                break;
            }
        default:
            break;
        }
    }

    if (!openBracketStack.empty()) {
        return false;
    } else {
        return true;
    }
}

/*
    Parses a while statement. When this method ends,
    _currentTokenPtr will be advanced after '}'.
*/
void Parser::parseWhileStmt() {
    assertMatchAndIncrementToken(Parser::REGEX_MATCH_WHILE_KEYWORD, Parser::MESSAGE_MISSING_WHILE_KEYWORD);

    _parentStack.push(_currentStmtNumber);
    //_containerStack.push(_currentStmtNumber);
    int whileStmtNumber = _currentStmtNumber;   // For setting Next relation

    assertMatchWithoutIncrementToken(Parser::REGEX_VALID_ENTITY_NAME, Parser::MESSAGE_INVALID_ENTITY_NAME);

    string whileVar = _currentTokenPtr;

    // PKB: Add while stmt to PKB. Must also pass 'control variable'.
    _pkbMainPtr->addWhileStmt(_currentStmtNumber, whileVar);

    /*
        PKB:
        Update VarToIdxMap
        Update UsesTableStmtToVar using currentStmtNumber
        Update UsesTableStmtToVar using parentStack
        Update UsesTableProcToVar using _currentProcName
        Update UsesTableVar using currentStmtNumber
        Update UsesTableVar using parentStack
    */
    _pkbMainPtr->addVariable(whileVar);     // Must add variable first before setting relationships
    _pkbMainPtr->setUseTableStmtToVar(_currentStmtNumber, whileVar);
    if (!_parentStack.empty()) {
        stack<int> parentStackCopy = _parentStack;
        while (!parentStackCopy.empty()) {
            int parentStmt = parentStackCopy.top();
            _pkbMainPtr->setUseTableStmtToVar(parentStmt, whileVar);
            parentStackCopy.pop();
        }
    }
    _pkbMainPtr->setUseTableProcToVar(_currentProcName, whileVar);

    assertMatchAndIncrementToken(Parser::REGEX_VALID_ENTITY_NAME, Parser::MESSAGE_INVALID_ENTITY_NAME);

    assertMatchAndIncrementToken(Parser::REGEX_MATCH_OPEN_BRACE, Parser::MESSAGE_MISSING_OPEN_BRACE);
    // Entering new statement list -> Add new stmtList stack to follows stack
    stack<int> newFollowsStack = stack<int>();
    _stackOfFollowsStacks.push(newFollowsStack);

    assert(whileStmtNumber == _currentStmtNumber);
    _pkbMainPtr->setNext(whileStmtNumber, _currentStmtNumber + 1);
    parseStmtList();

    // Before exiting while-block, update next relation (loop back)
    for (int prevReachableStmt : _prevReachableStmts) {
        _pkbMainPtr->setNext(prevReachableStmt, whileStmtNumber);
    }
    _prevReachableStmts.clear();
    // Store possible exit points of while statement
    _prevReachableStmts.insert(whileStmtNumber);

    assertMatchAndIncrementToken(Parser::REGEX_MATCH_CLOSE_BRACE, Parser::MESSAGE_MISSING_CLOSE_BRACE);
    processAndPopTopFollowStack();

    _parentStack.pop();
}

/*
    Parses an if-else statement. When this method ends,
    _currentTokenPtr will be advanced after '}'.
*/
void Parser::parseIfElseStmt()
{
    assertMatchAndIncrementToken(Parser::REGEX_MATCH_IF_KEYWORD, Parser::MESSAGE_MISSING_IF_KEYWORD);

    _parentStack.push(_currentStmtNumber);
    int ifElseStmtNum = _currentStmtNumber;     // Store for setting Next relation

    assertMatchWithoutIncrementToken(Parser::REGEX_VALID_ENTITY_NAME, Parser::MESSAGE_INVALID_ENTITY_NAME);

    string ifVar = _currentTokenPtr;

    // PKB: Add if-else stmt to PKB. Must also pass 'control variable'.
    _pkbMainPtr->addIfStmt(_currentStmtNumber, ifVar);

    /*
        PKB:
        Update VarToIdxMap
        Update UsesTableStmtToVar using currentStmtNumber
        Update UsesTableStmtToVar using parentStack
        Update UsesTableProcToVar using _currentProcName
        Update UsesTableVar using currentStmtNumber
        Update UsesTableVar using parentStack
    */
    _pkbMainPtr->addVariable(ifVar);     // Must add variable first before setting relationships
    _pkbMainPtr->setUseTableStmtToVar(_currentStmtNumber, ifVar);
    if (!_parentStack.empty()) {
        stack<int> parentStackCopy = _parentStack;
        while (!parentStackCopy.empty()) {
            int parentStmt = parentStackCopy.top();
            _pkbMainPtr->setUseTableStmtToVar(parentStmt, ifVar);
            parentStackCopy.pop();
        }
    }
    _pkbMainPtr->setUseTableProcToVar(_currentProcName, ifVar);

    assertMatchAndIncrementToken(Parser::REGEX_VALID_ENTITY_NAME, Parser::MESSAGE_INVALID_ENTITY_NAME);
    assertMatchAndIncrementToken(Parser::REGEX_MATCH_THEN_KEYWORD, Parser::MESSAGE_MISSING_THEN_KEYWORD);

    assertMatchAndIncrementToken(Parser::REGEX_MATCH_OPEN_BRACE, Parser::MESSAGE_MISSING_OPEN_BRACE);
    // Add new stmtList stack to follows stack
    stack<int> newFollowsStack = stack<int>();
    _stackOfFollowsStacks.push(newFollowsStack);

    assert(ifElseStmtNum == _currentStmtNumber);
    _pkbMainPtr->setNext(ifElseStmtNum, _currentStmtNumber + 1);
    parseStmtList();

    unordered_set<int> ifBlockExitPoints; // Store exit points of if-block for setting Next relation
    for (int stmt : _prevReachableStmts) {
        ifBlockExitPoints.insert(stmt);
    }
    _prevReachableStmts.clear();

    assertMatchAndIncrementToken(Parser::REGEX_MATCH_CLOSE_BRACE, Parser::MESSAGE_MISSING_CLOSE_BRACE);
    processAndPopTopFollowStack();

    assertMatchAndIncrementToken(Parser::REGEX_MATCH_ELSE_KEYWORD, Parser::MESSAGE_MISSING_ELSE_KEYWORD);

    assertMatchAndIncrementToken(Parser::REGEX_MATCH_OPEN_BRACE, Parser::MESSAGE_MISSING_OPEN_BRACE);
    // Entering new statement list -> Add new stmtList stack to follows stack
    newFollowsStack = stack<int>();
    _stackOfFollowsStacks.push(newFollowsStack);

    _pkbMainPtr->setNext(ifElseStmtNum, _currentStmtNumber + 1);
    parseStmtList();

    /*
        _prevReachableStmts should now contain all the exit points of else-block
        Add exit points of if-block
    */
    for (int stmt : ifBlockExitPoints) {
        _prevReachableStmts.insert(stmt);
    }

    assertMatchAndIncrementToken(Parser::REGEX_MATCH_CLOSE_BRACE, Parser::MESSAGE_MISSING_CLOSE_BRACE);
    processAndPopTopFollowStack();

    _parentStack.pop();
}

void Parser::processAndPopTopFollowStack()
{
    assert(!_stackOfFollowsStacks.empty() && !_stackOfFollowsStacks.top().empty());
    stack<int> topFollowsStack = _stackOfFollowsStacks.top();

    int stmtAfter = topFollowsStack.top();
    topFollowsStack.pop();

    // If stmtList has only 1 stmt
    if (topFollowsStack.empty()) 
        _pkbMainPtr->addStmtList(stmtAfter);

    int stmtBefore = 0;
    while (!topFollowsStack.empty()) {
        stmtBefore = topFollowsStack.top();
        _pkbMainPtr->setFollowsRel(stmtBefore, stmtAfter);
        stmtAfter = stmtBefore;
        topFollowsStack.pop();
        if (topFollowsStack.empty())    // Means stmtBefore is first stmt in stmtList
            _pkbMainPtr->addStmtList(stmtBefore);
    }
    _pkbMainPtr->setFollowsRel(0, stmtAfter);

    _stackOfFollowsStacks.pop();
}

void Parser::parseCallStmt()
{
    assertMatchAndIncrementToken(Parser::REGEX_MATCH_CALL_KEYWORD, Parser::MESSAGE_MISSING_CALL_KEYWORD);
    assertMatchWithoutIncrementToken(Parser::REGEX_VALID_ENTITY_NAME, Parser::MESSAGE_INVALID_ENTITY_NAME);
    string calledProcName = _currentTokenPtr;

    // PKB: Add calls relation
    _pkbMainPtr->setCallsRel(_currentStmtNumber, _currentProcName, calledProcName);

    assertMatchAndIncrementToken(Parser::REGEX_VALID_ENTITY_NAME, Parser::MESSAGE_INVALID_ENTITY_NAME);
    assertMatchAndIncrementToken(Parser::REGEX_MATCH_SEMICOLON, Parser::MESSAGE_MISSING_SEMICOLON);

    // Update _prevReachableStmt
    assert(_prevReachableStmts.empty());
    _prevReachableStmts.insert(_currentStmtNumber);
}
