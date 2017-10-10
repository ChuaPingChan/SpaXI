#pragma once
#include <string>
#include <exception>

using namespace std;

/*
* Thrown when Synonym cannot be found
*/
class SynonymNotFoundException : public exception
{
public:
    SynonymNotFoundException();
    SynonymNotFoundException(const string& message);
    ~SynonymNotFoundException();

    virtual const char* what() const throw();

private:
    static const string SYNONYM_NOT_FOUND;
    string msg;
};
