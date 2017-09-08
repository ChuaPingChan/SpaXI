#include <string>
#include <fstream>
#include <iostream>
#include <regex>
#include <cassert>

#include "Parser.h"

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
}

void Parser::parse() {
}

// TODO: For unit testing, to be removed later.
bool Parser::mainForUnitTest() {
    concatenateLines("../UnitTesting/ParserTestDependencies/getTokenTest.txt");
    ofstream outfile("../UnitTesting/ParserTestDependencies/getTokenResult.txt");

    while (getNextToken()) {
        outfile << _nextToken << endl;
    }
    outfile << "end" << endl;
    outfile.close();
    return true;
}

void Parser::concatenateLines(string filename) {
    ifstream infile(filename.c_str());
    
    string line;
    while (getline(infile, line)) {
        _concatenatedSourceCode += line;
    }

    infile.close();
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
