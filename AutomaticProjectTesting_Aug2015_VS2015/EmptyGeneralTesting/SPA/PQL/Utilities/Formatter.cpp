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
    unsigned middleDelimPos = firstDelimPos + firstDelim.length();
    unsigned lastDelimPos = str.find(secondDelim);

    return str.substr(middleDelimPos,
        lastDelimPos - middleDelimPos);
}
