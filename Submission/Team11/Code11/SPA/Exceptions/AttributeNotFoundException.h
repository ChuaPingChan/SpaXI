#pragma once
#include <string>
#include <exception>

using namespace std;

/*
* Thrown when Attribute cannot be found
*/
class AttributeNotFoundException : public exception
{
public:
    AttributeNotFoundException();
    AttributeNotFoundException(const string& message);
    ~AttributeNotFoundException();

    virtual const char* what() const throw();

private:
    static const string ATTRIBUTE_NOT_FOUND;
    string msg;
};
