#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <regex>

using namespace std;

class Formatter
{
public:
    Formatter();
    ~Formatter();

    static string removeAllSpaces(string str);
    static string removeAllQuotes(string str);
    static string removeAllOccurrencesOf(string str, string from, string to);

    static string getBetweenTwoDelims(const string & str, const string & firstDelim, const string & secondDelim);
    static string getBetweenTwoDelims(const string & str, const string & firstDelim, int firstDelimNumthOccurrence, const string & secondDelim, int secondDelimNumthOccurrenceAfterFirstDelim);
    static string getStringBeforeDelim(const string &str, const string &delim);
    static string getStringAfterDelim(const string &str, const string &delim);
};
