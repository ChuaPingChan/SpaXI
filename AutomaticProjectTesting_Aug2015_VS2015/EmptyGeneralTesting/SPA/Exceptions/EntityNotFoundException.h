#pragma once
#include <string>
#include <exception>

using namespace std;

/*
* Thrown when Entity cannot be found
*/

class EntityNotFoundException : public exception
{
public:
    EntityNotFoundException();
    EntityNotFoundException(const string& message);
    ~EntityNotFoundException();

    virtual const char* what() const throw();

private:
    static const string ENTITY_NOT_FOUND;
    string msg;
};
