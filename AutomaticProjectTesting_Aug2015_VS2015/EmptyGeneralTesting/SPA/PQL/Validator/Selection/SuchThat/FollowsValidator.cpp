#include "FollowsValidator.h"

FollowsValidator::FollowsValidator()
{
}

FollowsValidator::~FollowsValidator()
{
}

void FollowsValidator::setNextValidator(SuchThatValidator nextValidator)
{
    this->nextValidatorInLine = nextValidator;
}

bool FollowsValidator::isValid(string str)
{
    if (str == "") {
        //validate
        return true;
    }
    else {
        nextValidatorInLine.isValid(str);
    }
    return false;
}
