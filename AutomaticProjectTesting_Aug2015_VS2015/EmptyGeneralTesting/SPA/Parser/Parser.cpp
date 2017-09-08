#include <string>
#include <fstream>
#include <iostream>
#include <regex>

#include "Parser.h"

using namespace std;

Parser::Parser()
{
    _currentStmtNumber = Parser::INT_INITIAL_STMT_NUMBER;
    _concatenatedSourceCode = Parser::STRING_EMPTY_STRING;
    _nextToken = Parser::STRING_EMPTY_STRING;
    _isValidSyntax = true;
}

void Parser::parse() {
}

void Parser::mainForUnitTest() {

}

string Parser::concatenateLines(string filename) {
    ifstream infile(filename.c_str());
    
    string line;
    string concatenatedString;

    while (getline(infile, line)) {
        concatenatedString += line;
    }

    return concatenatedString;
}

string Parser::getNextToken()
{
    return "";
}

// ***** For unit testing, to be removed later *****
// *************************************************