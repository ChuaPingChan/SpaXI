#pragma once
#include <string>

using namespace std;

class SuchThatValidator
{
public:
    SuchThatValidator();
    ~SuchThatValidator();

    virtual bool isValid(string str) = 0;
};

