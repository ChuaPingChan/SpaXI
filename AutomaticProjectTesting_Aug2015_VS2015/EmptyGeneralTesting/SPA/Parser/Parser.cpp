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

// Char sequence to match should be a statement up to but not including semicolon.
// To extract contents within a wrapping outside bracket. Having outside bracket is assumed.
const regex Parser::REGEX_EXTRACT_BRACKET_WRAPPED_CONTENT = regex("\\s*\\(([^()]+|[^()]*\\([^]+\\)[^()]*)\\)\\s*");

const regex Parser::REGEX_MATCH_EQUAL = regex("\\s*=\\s*");
const regex Parser::REGEX_VALID_OPERATOR = regex("\\s*[+\\-*/]\\s*");

Parser::Parser(PKBMain* pkbMainPtr)
{
    _currentStmtNumber = Parser::INT_INITIAL_STMT_NUMBER;
    _concatenatedSourceCode = Parser::STRING_EMPTY_STRING;
    _currentTokenPtr = Parser::STRING_EMPTY_STRING;
    _isValidSyntax = false;
    _parentStack = stack<int>();
    _pkbMainPtr = pkbMainPtr;
    _stackOfFollowsStacks = stack<stack<int>>();
    _currentProcName = Parser::STRING_EMPTY_STRING;
    _prevReachableStmts = unordered_set<int>();
}

// TODO: Add comprehensive method description
bool Parser::parse(string filename) {
    _isValidSyntax = true;
    concatenateLines(filename);
    parseProgram();

    /*
    PKB TODO: Tell PKB to start design extractor.
    - Compute Follow* and Parents*
    - Compute cross-procedural Uses and Modifies
    - Compute Calls*
    - Compute Next*
    */
    OutputDebugString("PKB: Tell PKB to start design extractor.\n");
    _pkbMainPtr->startProcessComplexRelations();

    /*
    TODO:
    Keep track of actual procedure names with a HashSet<string> (not including
    procedures called by Call-statements). Here, check if the size of the hash
    set is the number of procedures registered in the PKB. If there are more
    procedures registerd in PKB, it means there are call-statements that calls
    procedures that don't exist.
    */

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

    _concatenatedSourceCode = stringAccumulator;
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
Checks if end of the source code has been reached.
Precondition:
- Source code has to be concatenated into _concatenatedSourceCode.
*/
bool Parser::endOfSourceCodeReached() {
    return regex_match(_concatenatedSourceCode, regex("\\s*"));
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
Returns a string from the current _currentTokenPtr to the character before the first semicolon encountered.
Indicate SIMPLE syntax error if no semicolon is encountered in the remaining of the string.
This method assumes there's a semicolon ahead in the _concatenatedSourceCode.
Note that this method does not remove whitespaces and does not move _currentTokenPtr forward.
*/
string Parser::extractStringUpToSemicolon() {
    smatch match;
    string targetSubstring;
    if (regex_match(_concatenatedSourceCode, match, Parser::REGEX_EXTRACT_UP_TO_SEMICOLON) && match.size() > 1) {
        targetSubstring = match.str(1);
    } else {
        _isValidSyntax = false;
        OutputDebugString("WARNING: Invalid line, no semicolon found.\n");
        // TODO: Throw exception.
    }
    return targetSubstring;
}

/*
Asserts that the next token must match the given regex.
If the match is successful, move current token pointer forward and return true.
If match is unsuccessful, indicate syntax error.
*/
bool Parser::assertMatchAndIncrementToken(regex re) {
    if (regex_match(_currentTokenPtr, re)) {
        incrCurrentTokenPtr();
        return true;
    } else {
        // TODO: Throw exception.
        _isValidSyntax = false;
        OutputDebugString("WARNING: Matching of token failed.\n");
        return false;
    }
}

/*
Asserts that the next token must match the given regex.
Does not move the current token pointer forward.
*/
bool Parser::assertMatchWithoutIncrementToken(regex re) {
    if (regex_match(_currentTokenPtr, re)) {
        return true;
    } else {
        // TODO: Throw exception.
        _isValidSyntax = false;
        OutputDebugString("WARNING: Matching of token failed.\n");
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
    OutputDebugString("FINE: End of program reached.\n");
}

/*
Parses a procedure.
Expects _currentTokenPtr to be "procedure" keyword.
When this method ends, _currentTokenPtr will be one token past the close
brace of the procedure.
*/
void Parser::parseProcedure() {
    assertMatchAndIncrementToken(Parser::REGEX_MATCH_PROCEDURE_KEYWORD);
    OutputDebugString("FINE: Parsing procedure.\n");

    string procName;
    if (!(matchToken(Parser::REGEX_VALID_ENTITY_NAME))) {
        //TODO: Throw exception
        _isValidSyntax = false;
        OutputDebugString("WARNING: Invalid procedure name.\n");
        return;
    }
    procName = _currentTokenPtr;
    // PKB: Add to ProcToIdxMap
    OutputDebugString("PKB: Add procedure.\n");
    _pkbMainPtr->addProcedure(procName);
    _currentProcName = procName;

    incrCurrentTokenPtr();
    assertMatchAndIncrementToken(Parser::REGEX_MATCH_OPEN_BRACE);
    OutputDebugString("FINE: Entering procedure...\n");
    // Add new stmtList stack to follows stack
    OutputDebugString("FINE: Push new stmtList stack to follows stack.\n");
    stack<int>* newFollowsStack = new stack<int>();
    _stackOfFollowsStacks.push(*newFollowsStack);

    parseStmtList();

    assertMatchAndIncrementToken(Parser::REGEX_MATCH_CLOSE_BRACE);
    _prevReachableStmts.clear();    // NextGraph is not cross-procedure
    processAndPopTopFollowStack();
    OutputDebugString("FINE: Processing and then pop top follows stack.\n");
    OutputDebugString("FINE: Exiting procedure...\n");
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
    OutputDebugString("FINE: Identifying next statement type...\n");

    // Push current statement to top of the top followsStack
    _stackOfFollowsStacks.top().push(_currentStmtNumber);
    OutputDebugString("FINE: Pushing stmt to top stack of follows stack.\n");

    _pkbMainPtr->addStmtToProc(_currentStmtNumber, _currentProcName);

    // Set parent child relation. 0 if no parent.
    if (_parentStack.empty()) {
        (*_pkbMainPtr).setParentChildRel(0, _currentStmtNumber);
    } else {
        (*_pkbMainPtr).setParentChildRel(_parentStack.top(), _currentStmtNumber);
    }
    OutputDebugString("PKB: Update parent-child relation.\n");

    // Check statement type and call appropriate function
    // (i.e. call, assignment, if-else, while)
    if (Parser::whileExpected()) {
        parseWhileStmt();

        // TODO: Refactor this block since it's repeated 4 times
        if (moreStmtsExistInStmtList()) {
            for (int prevReachableStmt : _prevReachableStmts) {
                _pkbMainPtr->setNext(prevReachableStmt, _currentStmtNumber + 1);
            }
            _prevReachableStmts.clear();
        }
    } else if (Parser::callStmtExpected()) {
        parseCallStmt();

        if (moreStmtsExistInStmtList()) {
            for (int prevReachableStmt : _prevReachableStmts) {
                _pkbMainPtr->setNext(prevReachableStmt, _currentStmtNumber + 1);
            }
            _prevReachableStmts.clear();
        }
    } else if (Parser::ifStmtExpected()) {
        parseIfStmt();

        if (moreStmtsExistInStmtList()) {
            for (int prevReachableStmt : _prevReachableStmts) {
                _pkbMainPtr->setNext(prevReachableStmt, _currentStmtNumber + 1);
            }
            _prevReachableStmts.clear();
        }
    } else {
        // assignment has to be at the last! If not, it'll wrongly capture while/Call/if keywords as variable names
        assert(Parser::assignmentExpected());
        parseAssignment();

        if (moreStmtsExistInStmtList()) {
            for (int prevReachableStmt : _prevReachableStmts) {
                _pkbMainPtr->setNext(prevReachableStmt, _currentStmtNumber + 1);
            }
            _prevReachableStmts.clear();
        }
    }
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
    OutputDebugString("FINE: Assignment statement identified.\n");
    OutputDebugString("PKB: Add assignment to PKB.\n");
    _pkbMainPtr->addAssignmentStmt(_currentStmtNumber);

    // Process LHS
    assertMatchWithoutIncrementToken(Parser::REGEX_VALID_ENTITY_NAME);
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
    OutputDebugString("PKB: Add variable to PKB.\n");
    OutputDebugString("PKB: Update modifies relationship.\n");
    _pkbMainPtr->addVariable(lhsVar);
    _pkbMainPtr->setModTableStmtToVar(_currentStmtNumber, lhsVar);
    // TODO Refactoring: Extract method.
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
    assertMatchAndIncrementToken(Parser::REGEX_MATCH_EQUAL);

    // Process RHS
    string rhsExpression = extractStringUpToSemicolon();
    if (assertIsValidExpression(rhsExpression)) {
        while (!matchToken(Parser::REGEX_MATCH_SEMICOLON)) {
            if (matchToken(Parser::REGEX_VALID_ENTITY_NAME)) {
                string var = _currentTokenPtr;
                /*
                PKB TODO:
                Update VarToIdxMap
                Update UsesTableStmtToVar using currentStmtNumber
                Update UsesTableStmtToVar using parentStack
                Update UsesProcToVar using _currentProcName
                Update UsesTableVar using currentStmtNumber
                Update UsesTableVar using parentStack
                */
                OutputDebugString("PKB: Add variable to PKB.\n");
                OutputDebugString("PKB: Update uses relationship.\n");
                _pkbMainPtr->addVariable(var);
                _pkbMainPtr->setUseTableStmtToVar(_currentStmtNumber, var);
                // TODO Refactoring: Extract method to achieve SLAP.
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
                /*
                PKB TODO:
                Update constants DS
                Update UsesTableStmtToConst using currentStmtNumber
                Update UsesTableStmtToConst using parentStack
                Update UsesProcToConst using _currentProcName
                Update UsesTableConst using currentStmtNumber
                Update UsesTableConst using parentStack
                */
                OutputDebugString("PKB: Add constant to PKB.\n");
                OutputDebugString("PKB: Update uses relationship.\n");
                _pkbMainPtr->addConstant(_currentStmtNumber, constant);
                // TODO Refactoring: Extract method to achieve SLAP.
                if (!_parentStack.empty()) {
                    stack<int> parentStackCopy = _parentStack;
                    while (!parentStackCopy.empty()) {
                        int parentStmt = parentStackCopy.top();
                        _pkbMainPtr->addConstant(parentStmt, constant);     // TODO: Check why parentStmt is needed as argument.
                        parentStackCopy.pop();
                    }
                }
            }
            incrCurrentTokenPtr();
        }
        // PKB: Add LHS var and RHS expression (without whitespace) to pattern table.
        OutputDebugString("PKB: Update pattern table.\n");
        string rhsExpressionNoWhitespace = removeAllWhitespaces(rhsExpression);
        _pkbMainPtr->setPatternRelation(_currentStmtNumber, lhsVar, rhsExpressionNoWhitespace);
    }
    // Update _prevReachableStmts
    assert(_prevReachableStmts.empty());
    _prevReachableStmts.insert(_currentStmtNumber);
    assertMatchAndIncrementToken(Parser::REGEX_MATCH_SEMICOLON);
}

/*
Asserts that an expression is syntactically valid.
*/
bool Parser::assertIsValidExpression(string expression) {

    // Remove outermost bracket (if applicable)
    smatch contentInBracket;
    while (regex_match(expression, contentInBracket, Parser::REGEX_EXTRACT_BRACKET_WRAPPED_CONTENT)
        && contentInBracket.size() > 1) {
        expression = contentInBracket.str(1);
    }

    // Check for bracket correctness. Just for redundancy.
    // Does not guarantee bracketing is correct, just counting.
    // e.g. "4 ( + 3)" will be evaluated as correct even though it's wrong.
    if (!isBracketedCorrectly(expression)) {
        return false;
    }

    // Base case
    if (regex_match(expression, Parser::REGEX_VALID_ENTITY_NAME)
        || regex_match(expression, Parser::REGEX_MATCH_CONSTANT)
        )
    {
        //OutputDebugString("FINE: Expression is valid.\n");
        return true;
    }

    string leftExpression;
    string rightExpression;
    pair<string, string> lhsRhsExpr = Parser::splitExpressionLhsRhs(expression);
    if (lhsRhsExpr != pair<string, string>()) {
        leftExpression = lhsRhsExpr.first;
        rightExpression = lhsRhsExpr.second;
    } else {
        _isValidSyntax = false;
        OutputDebugString("WARNING: Invalid Expression.\n");
        // TODO: Throw exception?
        return false;
    }
    return assertIsValidExpression(leftExpression) && assertIsValidExpression(rightExpression);
}

/*
Splits an expression into two parts, namely the left expression and right expression.
For example,
"3 + 3 - 2"         ==> "3" and "3 - 2"
"(2 + 3) + 6 - 7"   ==> "(2 + 3)" and "6 - 7"
"2 + (6 - 7)"       ==> "2" and "(6 - 7)"
"(2 + 3) + (6 - 7)" ==> "(2 + 3)" and "(6 - 7)"

If the format of the expression given is not splittable as above, an empty pair
of strings will be returned.
*/
std::pair<string, string> Parser::splitExpressionLhsRhs(std::string expression)
{
    string operatorRegex = "[+\\-*/]";
    string possibleWhitespaceRegex = "\\s*";
    string extractEntityRegex = "([A-Za-z][A-Za-z0-9]*|\\d+)";
    //string anyCharRegex = "[\\sa-zA-Z0-9+\\-*/()]";
    string anyCharRegex = "[^]";
    string extractRemainingRegex = "(" + anyCharRegex + "+)";
    string extractBracketWrappedContentRegex = "\\(([^()]+|[^()]*\\(" + anyCharRegex + "+\\)[^()]*)\\)";

    /*
    CASE 1:
    When the left expression has no brackets. E.g "2 + (10 * 3)", "2 + 10"
    */
    regex REGEX_CASE1_EXTRACTOR = regex(possibleWhitespaceRegex
        + extractEntityRegex
        + possibleWhitespaceRegex
        + operatorRegex
        + possibleWhitespaceRegex
        + extractRemainingRegex);

    /*
    CASE 2:
    When the left expression is bracketed. E.g. "(2 + 3) + 4", "(2 + 3) + (4 + 10)"
    */
    regex REGEX_CASE2_EXTRACTOR = regex(possibleWhitespaceRegex
        + extractBracketWrappedContentRegex
        + possibleWhitespaceRegex
        + operatorRegex
        + possibleWhitespaceRegex
        + extractRemainingRegex);

    smatch match;
    string leftExpression;
    string rightExpression;
    if (regex_match(expression, match, REGEX_CASE1_EXTRACTOR) && match.size() > 2) {
        leftExpression = match.str(1);
        rightExpression = match.str(2);
        return pair<string, string>(leftExpression, rightExpression);
    } else if (regex_match(expression, match, REGEX_CASE2_EXTRACTOR) && match.size() > 2) {
        leftExpression = match.str(1);
        rightExpression = match.str(2);
        return pair<string, string>(leftExpression, rightExpression);
    } else {
        return pair<string, string>();
    }
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
bool Parser::isBracketedCorrectly(std::string expression)
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
    OutputDebugString("FINE: While statement identified.\n");
    assertMatchAndIncrementToken(Parser::REGEX_MATCH_WHILE_KEYWORD);

    _parentStack.push(_currentStmtNumber);
    //_containerStack.push(_currentStmtNumber);
    int whileStmtNumber = _currentStmtNumber;   // For setting Next relation

    assertMatchWithoutIncrementToken(Parser::REGEX_VALID_ENTITY_NAME);

    string whileVar = _currentTokenPtr;

    // PKB: Add while stmt to PKB. Must also pass 'control variable'.
    OutputDebugString("PKB: Add while statement to PKB.\n");
    _pkbMainPtr->addWhileStmt(_currentStmtNumber, whileVar);

    /* PKB
    Update VarToIdxMap
    Update UsesTableStmtToVar using currentStmtNumber
    Update UsesTableStmtToVar using parentStack
    Update UsesTableProcToVar using _currentProcName
    Update UsesTableVar using currentStmtNumber
    Update UsesTableVar using parentStack
    */
    OutputDebugString("PKB: Add variable to PKB.\n");
    OutputDebugString("PKB: Update uses relationship.\n");
    _pkbMainPtr->addVariable(whileVar);     // Must add variable first before setting relationships
    _pkbMainPtr->setUseTableStmtToVar(_currentStmtNumber, whileVar);
    // TODO Refactoring: Extract method to achieve SLAP.
    if (!_parentStack.empty()) {
        stack<int> parentStackCopy = _parentStack;
        while (!parentStackCopy.empty()) {
            int parentStmt = parentStackCopy.top();
            _pkbMainPtr->setUseTableStmtToVar(parentStmt, whileVar);
            parentStackCopy.pop();
        }
    }
    _pkbMainPtr->setUseTableProcToVar(_currentProcName, whileVar);

    assertMatchAndIncrementToken(Parser::REGEX_VALID_ENTITY_NAME);

    assertMatchAndIncrementToken(Parser::REGEX_MATCH_OPEN_BRACE);
    OutputDebugString("FINE: Entering while block.\n");
    // Entering new statement list -> Add new stmtList stack to follows stack
    OutputDebugString("Push new stmtList stack to follows stack.\n");
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

    assertMatchAndIncrementToken(Parser::REGEX_MATCH_CLOSE_BRACE);
    OutputDebugString("FINE: Exiting while block.\n");
    processAndPopTopFollowStack();
    OutputDebugString("FINE: Processing and then pop top follows stack.\n");

    _parentStack.pop();
}

/*
Parses an if-else statement. When this method ends,
_currentTokenPtr will be advanced after '}'.
*/
void Parser::parseIfStmt()      // TODO: Rename this to "parseIfElseStmt()"
{
    OutputDebugString("FINE: If-else statement identified.\n");
    assertMatchAndIncrementToken(Parser::REGEX_MATCH_IF_KEYWORD);

    _parentStack.push(_currentStmtNumber);
    int ifElseStmtNum = _currentStmtNumber;     // Store for setting Next relation

    assertMatchWithoutIncrementToken(Parser::REGEX_VALID_ENTITY_NAME);

    string ifVar = _currentTokenPtr;

    // PKB: Add if-else stmt to PKB. Must also pass 'control variable'.
    OutputDebugString("PKB: Add if-else statement to PKB.\n");
    _pkbMainPtr->addIfStmt(_currentStmtNumber, ifVar);

    /* PKB
    Update VarToIdxMap
    Update UsesTableStmtToVar using currentStmtNumber
    Update UsesTableStmtToVar using parentStack
    Update UsesTableProcToVar using _currentProcName
    Update UsesTableVar using currentStmtNumber
    Update UsesTableVar using parentStack
    */
    OutputDebugString("PKB: Add variable to PKB.\n");
    OutputDebugString("PKB: Update uses relationship.\n");
    _pkbMainPtr->addVariable(ifVar);     // Must add variable first before setting relationships
    _pkbMainPtr->setUseTableStmtToVar(_currentStmtNumber, ifVar);
    // TODO Refactoring: Extract method to achieve SLA.
    if (!_parentStack.empty()) {
        stack<int> parentStackCopy = _parentStack;
        while (!parentStackCopy.empty()) {
            int parentStmt = parentStackCopy.top();
            _pkbMainPtr->setUseTableStmtToVar(parentStmt, ifVar);
            parentStackCopy.pop();
        }
    }
    _pkbMainPtr->setUseTableProcToVar(_currentProcName, ifVar);

    assertMatchAndIncrementToken(Parser::REGEX_VALID_ENTITY_NAME);
    assertMatchAndIncrementToken(Parser::REGEX_MATCH_THEN_KEYWORD);

    assertMatchAndIncrementToken(Parser::REGEX_MATCH_OPEN_BRACE);
    OutputDebugString("FINE: Entering if-block.\n");
    // Add new stmtList stack to follows stack
    OutputDebugString("Push new stmtList stack to follows stack.\n");
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

    assertMatchAndIncrementToken(Parser::REGEX_MATCH_CLOSE_BRACE);
    OutputDebugString("FINE: Exiting if-block.\n");
    processAndPopTopFollowStack();
    OutputDebugString("FINE: Processing and then pop top follows stack.\n");

    assertMatchAndIncrementToken(Parser::REGEX_MATCH_ELSE_KEYWORD);

    assertMatchAndIncrementToken(Parser::REGEX_MATCH_OPEN_BRACE);
    OutputDebugString("FINE: Entering else-block.\n");
    // Entering new statement list -> Add new stmtList stack to follows stack
    OutputDebugString("Push new stmtList stack to follows stack.\n");
    newFollowsStack = stack<int>();
    _stackOfFollowsStacks.push(newFollowsStack);

    _pkbMainPtr->setNext(ifElseStmtNum, _currentStmtNumber + 1);
    parseStmtList();

    // _prevReachableStmts should now contain all the exit points of else-block
    // Add exit points of if-block
    for (int stmt : ifBlockExitPoints) {
        _prevReachableStmts.insert(stmt);
    }

    assertMatchAndIncrementToken(Parser::REGEX_MATCH_CLOSE_BRACE);
    OutputDebugString("FINE: Exiting else-block.\n");
    processAndPopTopFollowStack();
    OutputDebugString("FINE: Processing and then pop top follows stack.\n");

    _parentStack.pop();
}

void Parser::processAndPopTopFollowStack()
{
    assert(!_stackOfFollowsStacks.empty() && !_stackOfFollowsStacks.top().empty());
    stack<int> topFollowsStack = _stackOfFollowsStacks.top();

    int stmtAfter = topFollowsStack.top();
    topFollowsStack.pop();
    int stmtBefore = 0;
    while (!topFollowsStack.empty()) {
        stmtBefore = topFollowsStack.top();
        _pkbMainPtr->setFollowsRel(stmtBefore, stmtAfter);
        stmtAfter = stmtBefore;
        topFollowsStack.pop();
    }
    _pkbMainPtr->setFollowsRel(0, stmtAfter);

    _stackOfFollowsStacks.pop();
}

void Parser::parseCallStmt()
{
    OutputDebugString("FINE: Parsing Calls statement.\n");
    assertMatchAndIncrementToken(Parser::REGEX_MATCH_CALL_KEYWORD);
    assertMatchWithoutIncrementToken(Parser::REGEX_VALID_ENTITY_NAME);
    string calledProcName = _currentTokenPtr;

    //PKB: Add calls relation
    OutputDebugString("PKB: Add calls relation.\n");
    _pkbMainPtr->setCallsRel(_currentStmtNumber, _currentProcName, calledProcName);

    assertMatchAndIncrementToken(Parser::REGEX_VALID_ENTITY_NAME);
    assertMatchAndIncrementToken(Parser::REGEX_MATCH_SEMICOLON);

    // Update _prevReachableStmt
    assert(_prevReachableStmts.empty());
    _prevReachableStmts.insert(_currentStmtNumber);
}
