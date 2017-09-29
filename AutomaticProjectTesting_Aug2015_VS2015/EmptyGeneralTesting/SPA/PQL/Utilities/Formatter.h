#pragma once
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Formatter
{
public:
    Formatter();
    ~Formatter();

    static string removeAllSpaces(string str);
    static string getBetweenTwoStrings(const string & str, const string & firstDelim, const string & secondDelim);
};

