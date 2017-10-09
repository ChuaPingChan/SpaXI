#include "Formatter.h"

using namespace std;

Formatter::Formatter()
{
}


Formatter::~Formatter()
{
}

/*--------------- Remove all spaces ---------------*/
string Formatter::removeAllSpaces(string str)
{
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    return str;
}


/*--------------- Get string between two delimiters ---------------*/
string Formatter::getBetweenTwoStrings(const string &str, const string &firstDelim, const string &secondDelim)
{
    unsigned firstDelimPos = str.find(firstDelim);
    unsigned endFirstDelimPos = firstDelimPos + firstDelim.length();

    string substr = str.substr(endFirstDelimPos);

    unsigned lastDelimPos = substr.find(secondDelim);

    return str.substr(endFirstDelimPos, lastDelimPos);
}

/*
* NumthOccurrence must be 1 or more
*/
string Formatter::getBetweenTwoStrings(const string &str, const string &firstDelim, int firstDelimNumthOccurrence, const string &secondDelim, int secondDelimNumthOccurrenceAfterFirstDelim)
{
    string substrFromEndFirstDelimPos = str;
    unsigned firstDelimTempPos;
    unsigned endFirstDelimTempPos;

    for (int i = 0; i < firstDelimNumthOccurrence; i++) {
        firstDelimTempPos = substrFromEndFirstDelimPos.find(firstDelim);
        endFirstDelimTempPos = firstDelimTempPos + firstDelim.length();
        substrFromEndFirstDelimPos = substrFromEndFirstDelimPos.substr(endFirstDelimTempPos);
    }

    int firstDelimPos = str.length() - substrFromEndFirstDelimPos.length();

    string substrFromEndSecondDelimPos = substrFromEndFirstDelimPos;
    unsigned lastDelimTempPos;
    unsigned endLastDelimTempPos;
    for (int j = 0; j < secondDelimNumthOccurrenceAfterFirstDelim; j++) {
        lastDelimTempPos = substrFromEndSecondDelimPos.find(secondDelim);
        endLastDelimTempPos = lastDelimTempPos + secondDelim.length();
        substrFromEndSecondDelimPos = substrFromEndSecondDelimPos.substr(endLastDelimTempPos);
    }   

    int secondDelimPos = str.length() - substrFromEndSecondDelimPos.length();
    int lenOfTargetStr = secondDelimPos - firstDelimPos - 1;

    return str.substr(firstDelimPos, lenOfTargetStr);
}

/*
* Get substring before first occurrence of delimiter
*/
string Formatter::getStringBeforeDelim(const string &str, const string &delim)
{
    unsigned delimPos = str.find(delim);
    return str.substr(0, delimPos);
}

string Formatter::getStringAfterDelim(const string & str, const string & delim)
{
    unsigned delimPos = str.find(delim);
    int endOfDelimPos = delimPos + delim.length();
    int subStrLength = str.length() - delimPos;
    return str.substr(endOfDelimPos, subStrLength);
}
