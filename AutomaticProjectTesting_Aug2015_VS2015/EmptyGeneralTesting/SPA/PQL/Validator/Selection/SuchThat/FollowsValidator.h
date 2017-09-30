#pragma once
#include "SuchThatValidator.h"

class FollowsValidator : public SuchThatValidator
{
public:
    FollowsValidator();
    ~FollowsValidator();

    bool isValid(string str);

};
