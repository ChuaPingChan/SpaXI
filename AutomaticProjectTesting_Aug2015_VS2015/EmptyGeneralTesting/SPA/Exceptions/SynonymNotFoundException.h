#pragma once
#include <exception>
#include <string>

using namespace std;

class SynonymNotFoundException : public exception
{
public:
    SynonymNotFoundException();
    SynonymNotFoundException(string msg);
    ~SynonymNotFoundException();

    virtual const char* what() const throw()
    {
        string errorMsg = "Synonym not found.\n" + msg;
        return errorMsg.c_str();
    }

private:
    string msg;
};

