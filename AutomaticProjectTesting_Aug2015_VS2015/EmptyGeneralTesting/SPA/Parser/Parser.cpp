#include <string>
#include <fstream>
#include <iostream>
#include <regex>
#include <cassert>

#include "Parser.h"
#include "SyntaxErrorException.h"

using namespace std;

const string Parser::STRING_EMPTY_STRING = "";
const regex Parser::REGEX_VALID_ENTITY_NAME = regex("\b([A-Za-z][A-Za-z0-9]*)[^A-Za-z0-9]\b");
const regex Parser::REGEX_EXTRACT_NEXT_TOKEN = regex("\\s*([a-zA-Z][a-zA-Z0-9]*|[^a-zA-Z0-9\\w]|\\d+).*");
const regex Parser::REGEX_VALID_PROCEDURE_KEYWORD = regex("procedure");
const regex Parser::REGEX_VALID_WHILE_KEYWORD = regex("while");
const regex Parser::REGEX_MATCH_OPEN_BRACE = regex("\\u007B");
const regex Parser::REGEX_MATCH_CLOSE_BRACE = regex("\\u007D");
const regex Parser::REGEX_MATCH_SEMICOLON = regex(";");
//const regex Parser::REGEX_VALID_ASSIGNMENT = regex("\\s*(\\d*|[A-Za-z][A-Za-z0-9]*)\\s*=\\s*(\\d*|[A-Za-z][A-Za-z0-9]*)\\s*[+-*/]\\s*(\\d*|[A-Za-z][A-Za-z0-9]*)\\s*;");

Parser::Parser()
{
    _currentStmtNumber = Parser::INT_INITIAL_STMT_NUMBER;
    _concatenatedSourceCode = Parser::STRING_EMPTY_STRING;
    _nextToken = Parser::STRING_EMPTY_STRING;
    _isValidSyntax = true;
    _errorMessage = string();
}

void Parser::parse(string filename) {
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
Matches a given regex expression to the next token.
If the match is successful, return true and move the next token forward.
*/
bool Parser::matchToken(regex re) {
    if (regex_match(_nextToken, re)) {
        getNextToken();
        return true;
    }
    else {
        _isValidSyntax = false;
        return false;
    }
}


/*
* Hereon are methods for unit testing, all of them
* are to be removed when permanent non-hacky unit test can be done.
*/
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
        Parser::REGEX_VALID_PROCEDURE_KEYWORD,
        Parser::REGEX_VALID_WHILE_KEYWORD,
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

