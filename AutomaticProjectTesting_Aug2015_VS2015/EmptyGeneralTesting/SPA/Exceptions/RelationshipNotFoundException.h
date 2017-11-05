#pragma once
#include <string>
#include <exception>

using namespace std;

/*
* Thrown when Relationship cannot be found
*/
class RelationshipNotFoundException : public exception
{
public:
    RelationshipNotFoundException();
    RelationshipNotFoundException(const string& message);
    ~RelationshipNotFoundException();

    virtual const char* what() const throw();

private:
    static const string RELATIONSHIP_NOT_FOUND;
    string msg;
};

