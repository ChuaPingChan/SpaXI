#pragma once
#include "SuchThatValidator.h"

class FollowsValidator : public SuchThatValidator
{
public:
    FollowsValidator();
    ~FollowsValidator();

    virtual void setNextValidator(SuchThatValidator nextValidator);
    virtual bool isValid(string str);

private:
    SuchThatValidator nextValidatorInLine;
};
