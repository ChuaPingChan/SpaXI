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

bool Parser::mainForUnitTest() {
    concatenateLines("C:/Users/user/Downloads/prototype_sample_SIMPLE_source.txt");
    return _concatenatedSourceCode == "procedure ABC {  i=1; b=200 ;	c= a   ;\u007D";
}

void Parser::concatenateLines(string filename) {
    ifstream infile(filename.c_str());
    
    string line;

    while (getline(infile, line)) {
        _concatenatedSourceCode += line;
    }
}

string Parser::getNextToken()
{
    return "";
}

// ***** For unit testing, to be removed later *****
// *************************************************