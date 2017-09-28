#pragma once
#include <string>

using namespace std;

class SuchThatValidator
{
public:
    SuchThatValidator();
    ~SuchThatValidator();

    virtual void setNextValidator(SuchThatValidator nextValidator);

    virtual bool isValid(string str);
};

