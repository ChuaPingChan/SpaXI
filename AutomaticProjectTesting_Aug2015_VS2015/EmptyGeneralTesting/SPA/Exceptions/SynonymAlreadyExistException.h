#pragma once
#include <string>
#include <exception>

using namespace std;

/*
* Thrown when Synonym already exist
*/
class SynonymAlreadyExistException : public exception
{
public:
    SynonymAlreadyExistException();
    SynonymAlreadyExistException(const string& message);
    ~SynonymAlreadyExistException();

    virtual const char* what() const throw();

private:
    static const string SYNONYM_ALREADY_EXIST;
    string msg;
};

