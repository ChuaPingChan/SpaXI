#include <string>
#include <exception>

using namespace std;

#pragma once
class UnrecognisedTypeException
{
public:
    UnrecognisedTypeException();
    UnrecognisedTypeException(const string& message);
    ~UnrecognisedTypeException();

    virtual const char* what() const throw();

private:
    static const string UNRECOGNISED_TYPE;
    string msg;
};

